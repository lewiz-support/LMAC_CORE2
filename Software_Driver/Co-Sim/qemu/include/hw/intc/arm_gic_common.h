/*
 * ARM GIC support
 *
 * Copyright (c) 2012 Linaro Limited
 * Written by Peter Maydell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_ARM_GIC_COMMON_H
#define HW_ARM_GIC_COMMON_H

#include "hw/sysbus.h"

/* Maximum number of possible interrupts, determined by the GIC architecture */
#define GIC_MAXIRQ 1020
/* First 32 are private to each CPU (SGIs and PPIs). */
#define GIC_INTERNAL 32
#define GIC_NR_SGIS 16
/* Maximum number of possible CPU interfaces, determined by GIC architecture */
/* Include a vCPU interface per CPU.  */
#define GIC_N_REALCPU 8
#define GIC_NCPU (GIC_N_REALCPU * 2)

#define MAX_NR_GROUP_PRIO 256
#define GIC_NR_APRS (MAX_NR_GROUP_PRIO / 32)
#define GICV_NR_LR 4

typedef struct gic_irq_state {
    /* The enable bits are only banked for per-cpu interrupts.  */
    uint8_t enabled;
    uint8_t pending;
    uint8_t active;
    uint8_t level;
    bool model; /* 0 = N:N, 1 = 1:N */
    bool edge_trigger; /* true: edge-triggered, false: level-triggered  */
    bool group;
} gic_irq_state;

typedef struct GICState {
    /*< private >*/
    SysBusDevice parent_obj;
    /*< public >*/

    qemu_irq parent_irq[GIC_NCPU];
    qemu_irq parent_fiq[GIC_NCPU];
    qemu_irq parent_virq[GIC_NCPU];
    qemu_irq parent_vfiq[GIC_NCPU];
    qemu_irq maint[GIC_N_REALCPU];

    bool enabled;
    bool enabled_grp0;

    struct {
        bool enable_grp[2];
        bool ack_ctl;
        bool fiq_en;
        bool eoirmode;
        bool eoirmode_ns;
    } gicc_ctrl[GIC_NCPU];

    uint32_t ctrl[GIC_NCPU];

    /* GICD_CTLR; for a GIC with the security extensions the NS banked version
     * of this register is just an alias of bit 1 of the S banked version.
     */
    uint32_t ctlr;
    /* GICC_CTLR; again, the NS banked version is just aliases of bits of
     * the S banked register, so our state only needs to store the S version.
     */
    uint32_t cpu_ctlr[GIC_NCPU];

    gic_irq_state irq_state[GIC_MAXIRQ];
    uint8_t irq_target[GIC_MAXIRQ];
    uint8_t priority1[GIC_INTERNAL][GIC_NCPU];
    uint8_t priority2[GIC_MAXIRQ - GIC_INTERNAL];
    uint16_t last_active[GIC_MAXIRQ][GIC_NCPU];
    /* For each SGI on the target CPU, we store 8 bits
     * indicating which source CPUs have made this SGI
     * pending on the target CPU. These correspond to
     * the bytes in the GIC_SPENDSGIR* registers as
     * read by the target CPU.
     */
    uint8_t sgi_pending[GIC_NR_SGIS][GIC_NCPU];

    uint16_t priority_mask[GIC_NCPU];
    uint16_t running_irq[GIC_NCPU];
    uint16_t running_priority[GIC_NCPU];
    uint16_t current_pending[GIC_NCPU];

    /* We present the GICv2 without security extensions to a guest and
     * therefore the guest can configure the GICC_CTLR to configure group 1
     * binary point in the abpr.
     */
    uint8_t  bpr[GIC_NCPU];
    uint8_t  abpr[GIC_NCPU];

    /* The Interface Identification Register.
     * This is implementation defined
     */
    uint32_t c_iidr;

    /* The APR is implementation defined, so we choose a layout identical to
     * the KVM ABI layout for QEMU's implementation of the gic:
     * If an interrupt for preemption level X is active, then
     *   APRn[X mod 32] == 0b1,  where n = X / 32
     * otherwise the bit is clear.
     *
     * TODO: rewrite the interrupt acknowlege/complete routines to use
     * the APR registers to track the necessary information to update
     * s->running_priority[] on interrupt completion (ie completely remove
     * last_active[][] and running_irq[]). This will be necessary if we ever
     * want to support TCG<->KVM migration, or TCG guests which can
     * do power management involving powering down and restarting
     * the GIC.
     */
    /* We don't use all of this space but we allocate all of it.  */
    uint32_t apr[GIC_NR_APRS][GIC_NCPU];
    uint32_t apr_guard[32];

    struct {
        uint32_t hcr[GIC_N_REALCPU];
        uint32_t vtr[GIC_N_REALCPU];
        uint32_t misr[GIC_N_REALCPU];
        uint64_t eisr[GIC_N_REALCPU];
        uint64_t elrsr[GIC_N_REALCPU];
        uint32_t apr[GIC_N_REALCPU];
        uint32_t lr[GIC_N_REALCPU][GICV_NR_LR];

        uint32_t pending_prio[GIC_N_REALCPU];
        uint8_t pending_lrn[GIC_N_REALCPU];
    } gich;

    uint32_t num_cpu;

    MemoryRegion iomem; /* Distributor */
    /* This is just so we can have an opaque pointer which identifies
     * both this GIC and which CPU interface we should be accessing.
     */
    struct GICState *backref[GIC_NCPU];
    MemoryRegion cpuiomem[GIC_NCPU + 1]; /* CPU interfaces */
    MemoryRegion hypiomem[GIC_NCPU + 1]; /* Virtual control interfaces */
    MemoryRegion vcpuiomem; /* Virtual CPU interface */
    uint32_t map_stride;
    uint32_t num_irq;
    uint32_t revision;
    bool security_extn;
    bool irq_reset_nonsecure;
    bool disable_linux_gic_init;
    int dev_fd; /* kvm device fd if backed by kvm vgic support */
} GICState;

#define TYPE_ARM_GIC_COMMON "arm_gic_common"
#define ARM_GIC_COMMON(obj) \
     OBJECT_CHECK(GICState, (obj), TYPE_ARM_GIC_COMMON)
#define ARM_GIC_COMMON_CLASS(klass) \
     OBJECT_CLASS_CHECK(ARMGICCommonClass, (klass), TYPE_ARM_GIC_COMMON)
#define ARM_GIC_COMMON_GET_CLASS(obj) \
     OBJECT_GET_CLASS(ARMGICCommonClass, (obj), TYPE_ARM_GIC_COMMON)

typedef struct ARMGICCommonClass {
    /*< private >*/
    SysBusDeviceClass parent_class;
    /*< public >*/

    void (*pre_save)(GICState *s);
    void (*post_load)(GICState *s);
} ARMGICCommonClass;

void gic_init_irqs_and_mmio(GICState *s, qemu_irq_handler handler,
                            const MemoryRegionOps *ops);

#endif
