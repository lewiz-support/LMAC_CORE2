/*
 * QEMU remote attach
 *
 * Copyright (c) 2013 Xilinx Inc
 * Written by Edgar E. Iglesias <edgar.iglesias@xilinx.com>
 *
 * This code is licensed under the GNU GPL.
 */

#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "hw/sysbus.h"
#include "monitor/monitor.h"
#include "monitor/qdev.h"
#include "qmp-commands.h"
#include "sysemu/arch_init.h"
#include "qapi/qmp/qerror.h"
#include "qemu/config-file.h"
#include "qemu/error-report.h"
#include "qemu/help_option.h"
#include "qemu/cutils.h"

#include "hw/remote-port.h"

/* RP helper function to attach a device to an adaptor.  */
void rp_device_attach(Object *adaptor, Object *dev,
                      int rp_nr, int dev_nr,
                      Error **errp)
{
    Error *err = NULL;
    uint32_t nr_devs;
    char *name;
    int i;

    assert(adaptor);
    assert(dev);

    /* Verify that the adaptor is of Remote Port type.  */
    if (!object_dynamic_cast(adaptor, TYPE_REMOTE_PORT)) {
        error_setg(errp, "%s is not a Remote-Port adaptor!\n",
                   object_get_canonical_path(adaptor));
        return;
    }

    name = g_strdup_printf("rp-adaptor%d", rp_nr);
    object_property_set_link(dev, adaptor, name, &err);
    g_free(name);
    if (err != NULL) {
        error_propagate(errp, err);
        return;
    }

    name = g_strdup_printf("rp-chan%d", rp_nr);
    object_property_set_int(dev, dev_nr, name, &err);
    g_free(name);
    if (err != NULL
        && !object_dynamic_cast(dev, TYPE_REMOTE_PORT_DEVICE)) {
        /*
         * RP devices that only receive requests may not need to
         * know their channel/dev number. If not, treat this as
         * an error.
         */
        error_propagate(errp, err);
        return;
    }
    err = NULL;

    nr_devs = object_property_get_int(dev, "nr-devs", &err);
    if (err) {
        nr_devs = 1;
        err = NULL;
    }

    /* Multi-channel devs use consecutive numbering.  */
    for (i = 0; i < nr_devs; i++) {
        name = g_strdup_printf("remote-port-dev%d", dev_nr + i);
        object_property_set_link(adaptor, dev, name, &err);
        g_free(name);
        if (err != NULL) {
            error_propagate(errp, err);
            return;
        }
    }
}

/* Scan for remote-port links to be setup.  */
void rp_device_add(QemuOpts *opts, DeviceState *dev, Error **errp)
{
    Error *err = NULL;
    Object *adaptor;
    bool ambiguous;
    const char *path;
    char *name;
    int i;

    /*
     * Find the adaptor this remote-port device is connected to.
     * At the moment, we only support one adaptor per device.
     */
    name = g_strdup_printf("rp-adaptor%d", 0);
    path = qemu_opt_get(opts, name);
    g_free(name);
    if (!path) {
        /* This is not a remote-port device.  */
        return;
    }
    adaptor = object_resolve_path(path, &ambiguous);
    if (!adaptor) {
        error_setg(errp, "Did not find rp adaptor %s!\n", path);
        return;
    }

    /*
     * Loop through the channels this device provides and attach
     * them to the adaptor.
     */
    for (i = 0; i < INT_MAX; i++) {
        unsigned long dev_nr;
        const char *dev_nr_str;

        name = g_strdup_printf("rp-chan%d", i);
        dev_nr_str = qemu_opt_get(opts, name);
        g_free(name);

        if (!dev_nr_str) {
            if (i == 0) {
                /* At least one channel must be provided.  */
                error_setg(errp, "Did not find rp-chan%d!\n", i);
            }
            return;
        }

        if (qemu_strtoul(dev_nr_str, NULL, 0, &dev_nr)) {
            error_setg(errp, "Invalid rp-chan%d!\n", i);
            return;
        }

        /* Now, attach the device to the adaptor.  */
        rp_device_attach(adaptor, OBJECT(dev), 0, dev_nr, &err);
        if (err != NULL) {
            error_propagate(errp, err);
            return;
        }
    }
}
