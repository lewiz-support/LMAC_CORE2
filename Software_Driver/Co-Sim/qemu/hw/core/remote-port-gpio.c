/*
 * Copyright (c) 2013 Xilinx Inc
 * Written by Edgar E. Iglesias <edgar.iglesias@xilinx.com>
 * Written by Peter Crosthwaite <peter.crosthwaite@xilinx.com>
 *
 * This code is licensed under the GNU GPL.
 */

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "sysemu/sysemu.h"
#include "sysemu/dma.h"
#include "qemu/log.h"
#include "qapi/qmp/qerror.h"
#include "qapi/error.h"
#include "hw/qdev.h"

#include "hw/fdt_generic_util.h"

#include "hw/remote-port.h"
#include "hw/remote-port-proto.h"
#include "hw/remote-port-device.h"
#include "hw/remote-port-gpio.h"

#define CACHE_INVALID -1

static void rp_gpio_handler(void *opaque, int irq, int level)
{
    RemotePortGPIO *s = opaque;
    struct rp_pkt pkt;
    size_t len;
    int64_t clk;
    uint32_t id = rp_new_id(s->rp);
    uint32_t flags = s->posted_updates ? RP_PKT_FLAGS_posted : 0;

    /* If we hit the cache, return early.  */
    if (s->cache[irq] != CACHE_INVALID && s->cache[irq] == level) {
        return;
    }
    /* Update the cache and update the remote peer.  */
    s->cache[irq] = level;

    clk = rp_normalized_vmclk(s->rp);
    len = rp_encode_interrupt_f(id, s->rp_dev, &pkt.interrupt, clk,
                              irq, 0, level, flags);

    if (s->peer->caps.wire_posted_updates && s->posted_updates) {
        rp_rsp_mutex_lock(s->rp);
    }

    rp_write(s->rp, (void *)&pkt, len);

    if (s->peer->caps.wire_posted_updates && s->posted_updates) {
        RemotePortRespSlot *rsp_slot;

        rsp_slot = rp_dev_wait_resp(s->rp, s->rp_dev, id);
        assert(rsp_slot->rsp.pkt->hdr.id == id);
        rp_resp_slot_done(s->rp, rsp_slot);
        rp_rsp_mutex_unlock(s->rp);
    }
}

static void rp_gpio_interrupt(RemotePortDevice *rpdev, struct rp_pkt *pkt)
{
    RemotePortGPIO *s = REMOTE_PORT_GPIO(rpdev);

    qemu_set_irq(s->gpio_out[pkt->interrupt.line], pkt->interrupt.val);

    if (s->peer->caps.wire_posted_updates
        && !(pkt->hdr.flags & RP_PKT_FLAGS_posted)) {
        RemotePortDynPkt rsp = {0};
        size_t len;

        /* Need to reply.  */
        rp_dpkt_alloc(&rsp, sizeof(struct rp_pkt_interrupt));
        len = rp_encode_interrupt_f(pkt->hdr.id, pkt->hdr.dev,
                                    &rsp.pkt->interrupt,
                                    pkt->interrupt.timestamp,
                                    pkt->interrupt.line,
                                    pkt->interrupt.vector,
                                    pkt->interrupt.val,
                                    pkt->hdr.flags | RP_PKT_FLAGS_response);
        rp_write(s->rp, (void *)rsp.pkt, len);
    }
}

static void rp_gpio_reset(DeviceState *dev)
{
    RemotePortGPIO *s = REMOTE_PORT_GPIO(dev);

    /* Mark as invalid.  */
    memset(s->cache, CACHE_INVALID, s->num_gpios);
}

static void rp_gpio_realize(DeviceState *dev, Error **errp)
{
    RemotePortGPIO *s = REMOTE_PORT_GPIO(dev);
    unsigned int i;

    s->peer = rp_get_peer(s->rp);

    s->gpio_out = g_new0(qemu_irq, s->num_gpios);
    qdev_init_gpio_out(dev, s->gpio_out, s->num_gpios);
    qdev_init_gpio_in(dev, rp_gpio_handler, s->num_gpios);

    for (i = 0; i < s->num_gpios; i++) {
        sysbus_init_irq(SYS_BUS_DEVICE(s), &s->gpio_out[i]);
    }
}

static void rp_gpio_init(Object *obj)
{
    RemotePortGPIO *rpms = REMOTE_PORT_GPIO(obj);

    object_property_add_link(obj, "rp-adaptor0", "remote-port",
                             (Object **)&rpms->rp,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
}

static Property rp_properties[] = {
    DEFINE_PROP_UINT32("rp-chan0", RemotePortGPIO, rp_dev, 0),
    DEFINE_PROP_UINT32("num-gpios", RemotePortGPIO, num_gpios, 16),
    DEFINE_PROP_UINT16("cell-offset-irq-num", RemotePortGPIO,
                       cell_offset_irq_num, 0),
    DEFINE_PROP_BOOL("posted-updates", RemotePortGPIO, posted_updates, false),
    DEFINE_PROP_END_OF_LIST(),
};

static int rp_fdt_get_irq(FDTGenericIntc *obj, qemu_irq *irqs,
                          uint32_t *cells, int ncells, int max,
                          Error **errp)
{
    RemotePortGPIO *s = REMOTE_PORT_GPIO(obj);

    if (cells[s->cell_offset_irq_num] >= s->num_gpios) {
        error_setg(errp, "RP-GPIO was setup for %u interrupts: index %"
                   PRIu32 " requested", s->num_gpios,
                   cells[s->cell_offset_irq_num]);
        return 0;
    }

    (*irqs) = qdev_get_gpio_in(DEVICE(obj), cells[s->cell_offset_irq_num]);
    return 1;
};

static void rp_gpio_class_init(ObjectClass *oc, void *data)
{
    RemotePortDeviceClass *rpdc = REMOTE_PORT_DEVICE_CLASS(oc);
    DeviceClass *dc = DEVICE_CLASS(oc);
    FDTGenericIntcClass *fgic = FDT_GENERIC_INTC_CLASS(oc);

    rpdc->ops[RP_CMD_interrupt] = rp_gpio_interrupt;
    dc->reset = rp_gpio_reset;
    dc->realize = rp_gpio_realize;
    dc->props = rp_properties;
    fgic->get_irq = rp_fdt_get_irq;
}

static const TypeInfo rp_info = {
    .name          = TYPE_REMOTE_PORT_GPIO,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(RemotePortGPIO),
    .instance_init = rp_gpio_init,
    .class_init    = rp_gpio_class_init,
    .interfaces    = (InterfaceInfo[]) {
        { TYPE_REMOTE_PORT_DEVICE },
        { TYPE_FDT_GENERIC_INTC },
        { },
    },
};

static void rp_register_types(void)
{
    type_register_static(&rp_info);
}

type_init(rp_register_types)
