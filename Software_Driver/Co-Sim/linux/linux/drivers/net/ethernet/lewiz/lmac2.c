/*
 * Driver for the LeWiz LMAC2 with a Xilinx AXI DMA.
 *
 * Copyright (c) 2019 Xilinx Inc.
 * Written by Edgar E. Iglesias.
 *
 * References:
 * https://www.xilinx.com/support/documentation/ip_documentation/axi_dma/v7_1/pg021_axi_dma.pdf
 * https://github.com/lewiz-support/LMAC_CORE2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_mdio.h>
#include <linux/of_net.h>
#include <linux/phy.h>
#include <linux/interrupt.h>

#define DRIVER_NAME		"lmac2"
#define TX_TIMEOUT		(10 * HZ)	/* Tx timeout is 10 seconds. */
#define MAX_FRAME_SIZE		(2 * 1024)

/* DMA TX/RX Base offsets.  */
#define DMA_M2S_OFFSET		0x4000
#define DMA_S2M_OFFSET		0x5000

/* Register offsets and bit-field definitions.  */
#define DMA_CR_RS		(1 << 0)
#define DMA_CR_RESET		(1 << 1)
#define DMA_CR_KEYHOLE		(1 << 2)
#define DMA_CR_CYCLIC_BD	(1 << 3)
#define DMA_CR_IOC_IRQ_EN	(1 << 12)

#define DMA_SR_HALTED		(1 << 0)
#define DMA_SR_IDLE		(1 << 1)
#define DMA_SR_SGINCLD		(1 << 3)
#define DMA_SR_IOC_IRQ		(1 << 12)

#define DMA_R_CR		0x0
#define DMA_R_SR		0x4
#define DMA_R_ADDR		0x18
#define DMA_R_ADDR_MSB		0x1c
#define DMA_R_LENGTH		0x28

#define DEBUG 0

struct net_local {
	struct net_device *ndev;
	void __iomem *base_addr;

	struct {
		int irq;
		struct sk_buff *skb;	/* Allocated SKB for RX.  */
		dma_addr_t phys;	/* Physical address of SKB.  */
	} rx;

	struct {
		spinlock_t lock;

		struct sk_buff *skb;	/* SKB in flight.  */
		dma_addr_t phys;	/* Physical address of SKB.  */
		bool in_flight;		/* True if packet is in flight.  */
	} tx;
};

static inline void lmac2_ack_interrupt(struct net_local *lp,
					unsigned long offset)
{
	u32 r_sr;

	// Ack the IRQ.
	writel(DMA_SR_IOC_IRQ, lp->base_addr + offset + DMA_R_SR);

	smp_mb();
	// When co-simulating there might be a long delay for
	// the interrupt ACK to propagate. Read-back to make sure
	// it has bitten.
	r_sr = readl(lp->base_addr + offset + DMA_R_SR);
	BUG_ON(r_sr & DMA_SR_IOC_IRQ);
}

static void lmac2_tx_timeout(struct net_device *dev)
{
	printk("%s: timeout\n", __func__);
	// TODO: Dump registers, reset everything and start again..
}

/*
 * Prepare the RX path.
 */
static void lmac_prepare_rx(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	unsigned int len;

	/* Allocate an SKB of MAX size.  */
        len = MAX_FRAME_SIZE;
        lp->rx.skb = netdev_alloc_skb(dev, len);
	skb_reserve(lp->rx.skb, NET_IP_ALIGN);

	/* Map to a DMA (physical) address.  */
	lp->rx.phys = dma_map_single(dev->dev.parent,
			lp->rx.skb->data, MAX_FRAME_SIZE,
			DMA_FROM_DEVICE);

	/* Program the DMA address registers.  */
	writel((uint32_t)lp->rx.phys,
		lp->base_addr + DMA_S2M_OFFSET + DMA_R_ADDR);
	writel(lp->rx.phys >> 32,
		lp->base_addr + DMA_S2M_OFFSET + DMA_R_ADDR_MSB);

	/* Enable the DMA.  */
	writel(len,
		lp->base_addr + DMA_S2M_OFFSET + DMA_R_LENGTH);
}

static irqreturn_t lmac2_rx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct net_local *lp = netdev_priv(dev);
	irqreturn_t ret = IRQ_HANDLED;
	u32 rx_sr;

	/* Check the Status Register for pending RX interrupts.  */
	rx_sr = readl(lp->base_addr + DMA_S2M_OFFSET + DMA_R_SR);

	if (rx_sr & DMA_SR_IOC_IRQ) {
		struct sk_buff *skb = lp->rx.skb;
		u32 len;

		lmac2_ack_interrupt(lp, DMA_S2M_OFFSET);

		dma_unmap_single(dev->dev.parent, lp->rx.phys,
				MAX_FRAME_SIZE, DMA_FROM_DEVICE);

		// Read out the length.
		len = readl(lp->base_addr + DMA_S2M_OFFSET + DMA_R_LENGTH);

		// Prepare to recieve a new packet.
		lmac_prepare_rx(dev);

		// Inject the packet into the Linux stack.
		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, dev);
		skb->ip_summed = CHECKSUM_UNNECESSARY;

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;

		netif_rx(skb);
	} else {
		printk("%s: Rx IRQ not handled\n", __func__);
		ret = IRQ_NONE;
	}

	return ret;
}

static irqreturn_t lmac2_tx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct net_local *lp = netdev_priv(dev);
	irqreturn_t ret = IRQ_HANDLED;
	u32 tx_sr;

        spin_lock(&lp->tx.lock);

	tx_sr = readl(lp->base_addr + DMA_M2S_OFFSET + DMA_R_SR);
	if (tx_sr & DMA_SR_IOC_IRQ) {
		lmac2_ack_interrupt(lp, DMA_M2S_OFFSET);

		dma_unmap_single(dev->dev.parent, lp->tx.phys,
				lp->tx.skb->len, DMA_TO_DEVICE);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += lp->tx.skb->len;

		dev_kfree_skb_irq(lp->tx.skb);
		lp->tx.skb = NULL;
		lp->tx.phys = 0;

		netif_trans_update(dev);
		netif_wake_queue(dev);
		lp->tx.in_flight = false;
	} else {
		// FIXME: We have an issue with spurious interrupts.
		// May be related to remote-port IRQ's being posted.
		if (DEBUG) {
			printk("TX IRQ not handled1 tx_sr=%x in_flight=%d\n",
				tx_sr, lp->tx.in_flight);
		}
		ret = IRQ_NONE;
	}

        spin_unlock(&lp->tx.lock);
	return ret;
}

static int lmac2_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	unsigned long flags;
	unsigned int len;

	len = skb->len;

        spin_lock_irqsave(&lp->tx.lock, flags);
	lp->tx.skb = skb;
	lp->tx.phys = dma_map_single(dev->dev.parent,
			skb->data, MAX_FRAME_SIZE,
			DMA_FROM_DEVICE);

	writel((uint32_t)lp->tx.phys,
		lp->base_addr + DMA_M2S_OFFSET + DMA_R_ADDR);
	writel(lp->tx.phys >> 32,
		lp->base_addr + DMA_M2S_OFFSET + DMA_R_ADDR_MSB);
	writel(len,
		lp->base_addr + DMA_M2S_OFFSET + DMA_R_LENGTH);
	lp->tx.in_flight = true;

	dev->stats.tx_bytes += len;
	netif_stop_queue(dev);

	spin_unlock_irqrestore(&lp->tx.lock, flags);
	return 0;
}

static int lmac2_open(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	int retval;

	/* Grab the IRQ */
	retval = request_irq(dev->irq, lmac2_tx_interrupt, IRQF_SHARED,
				dev->name, dev);
	if (retval) {
		dev_err(&lp->ndev->dev, "Could not allocate interrupt %d\n",
			dev->irq);
		return retval;
	}

	retval = request_irq(lp->rx.irq, lmac2_rx_interrupt, IRQF_SHARED,
			dev->name, dev);
	if (retval) {
		dev_err(&lp->ndev->dev, "Could not allocate interrupt %d\n",
			lp->rx.irq);
		return retval;
	}

	lmac_prepare_rx(dev);

	// Enable RX interrupts.
	writel(DMA_CR_IOC_IRQ_EN,
		lp->base_addr + DMA_S2M_OFFSET + DMA_R_CR);
	// Enable TX interrupts.
	writel(DMA_CR_IOC_IRQ_EN,
		lp->base_addr + DMA_M2S_OFFSET + DMA_R_CR);

	/* We're ready to go */
	netif_start_queue(dev);
	return 0;
}

static int lmac2_close(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);

	// Disable interrupts.
	writel(0, lp->base_addr + DMA_S2M_OFFSET + DMA_R_CR);
	writel(0, lp->base_addr + DMA_M2S_OFFSET + DMA_R_CR);

	netif_stop_queue(dev);
	free_irq(dev->irq, dev);
	return 0;
}

static const struct net_device_ops lmac2_netdev_ops;

static int lmac2_of_probe(struct platform_device *ofdev)
{
	struct resource *res;
	struct net_device *ndev = NULL;
	struct net_local *lp = NULL;
	struct device *dev = &ofdev->dev;
	const void *mac_address;

	int rc = 0;

	/* Create an ethernet device instance */
	ndev = alloc_etherdev(sizeof(struct net_local));
	if (!ndev)
		return -ENOMEM;

	dev_set_drvdata(dev, ndev);
	SET_NETDEV_DEV(ndev, &ofdev->dev);

	lp = netdev_priv(ndev);
	lp->ndev = ndev;

        spin_lock_init(&lp->tx.lock);

	/* Get IRQ for the device */
	res = platform_get_resource(ofdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(dev, "no IRQ found\n");
		rc = -ENXIO;
		goto error;
	}

	ndev->irq = res->start;

	res = platform_get_resource(ofdev, IORESOURCE_IRQ, 1);
	if (!res) {
		dev_err(dev, "no IRQ found\n");
		rc = -ENXIO;
		goto error;
	}

	lp->rx.irq = res->start;

	res = platform_get_resource(ofdev, IORESOURCE_MEM, 0);
	lp->base_addr = devm_ioremap_resource(&ofdev->dev, res);
	if (IS_ERR(lp->base_addr)) {
		rc = PTR_ERR(lp->base_addr);
		goto error;
	}

	ndev->mem_start = res->start;
	ndev->mem_end = res->end;

	mac_address = of_get_mac_address(ofdev->dev.of_node);

	if (mac_address) {
		/* Set the MAC address. */
		memcpy(ndev->dev_addr, mac_address, ETH_ALEN);
	} else {
		dev_warn(dev, "No MAC address found, using random\n");
		eth_hw_addr_random(ndev);
	}

	ndev->netdev_ops = &lmac2_netdev_ops;
//	ndev->flags &= ~IFF_MULTICAST;
	ndev->watchdog_timeo = TX_TIMEOUT;

	/* Finally, register the device */
	rc = register_netdev(ndev);
	if (rc) {
		dev_err(dev,
			"Cannot register network device, aborting\n");
		goto error;
	}

	dev_info(dev,
		 "Lewiz TRIAL EDIT at 0x%08X mapped to 0x%08lX, tx-irq=%d rx-irq=%d\n",
		 (unsigned int __force)ndev->mem_start,
		 (unsigned long __force)lp->base_addr, ndev->irq, lp->rx.irq);
	return 0;

error:
	free_netdev(ndev);
	return rc;
}

static int lmac2_of_remove(struct platform_device *of_dev)
{
	struct net_device *ndev = platform_get_drvdata(of_dev);

	unregister_netdev(ndev);

	free_netdev(ndev);
	return 0;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
static void
lmac2_poll_controller(struct net_device *ndev)
{
	disable_irq(ndev->irq);
	lmac2_interrupt(ndev->irq, ndev);
	enable_irq(ndev->irq);
}
#endif

static const struct net_device_ops lmac2_netdev_ops = {
	.ndo_open		= lmac2_open,
	.ndo_stop		= lmac2_close,
	.ndo_start_xmit		= lmac2_start_xmit,
	.ndo_tx_timeout		= lmac2_tx_timeout,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = lmac2_poll_controller,
#endif
};

/* Match table for OF platform binding */
static const struct of_device_id lmac2_of_match[] = {
	{ .compatible = "lewiz,lmac2", },
	{ /* end of list */ },
};
MODULE_DEVICE_TABLE(of, lmac2_of_match);

static struct platform_driver lmac2_of_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.of_match_table = lmac2_of_match,
	},
	.probe		= lmac2_of_probe,
	.remove		= lmac2_of_remove,
};

module_platform_driver(lmac2_of_driver);

MODULE_AUTHOR("Edgar E. Iglesias <edgar.iglesias@xilinx.com>");
MODULE_DESCRIPTION("LeWiz LMAC2 driver");
MODULE_LICENSE("GPL");
