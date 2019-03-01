/*
 * QEMU I2C bus interface.
 *
 * Copyright (c) 2007 CodeSourcery.
 * Written by Paul Brook
 *
 * This code is licensed under the LGPL.
 */

#include "qemu/osdep.h"
#include "hw/i2c/i2c.h"
#include "hw/fdt_generic_util.h"

typedef struct I2CNode I2CNode;

struct I2CNode {
    I2CSlave *elt;
    QLIST_ENTRY(I2CNode) next;
};

#define I2C_BROADCAST 0x00

static Property i2c_props[] = {
    DEFINE_PROP_UINT8("address", struct I2CSlave, address, 0),
    DEFINE_PROP_UINT8("address-range", struct I2CSlave, address_range, 1),
    DEFINE_PROP_END_OF_LIST(),
};

#define TYPE_I2C_BUS "i2c-bus"
#define I2C_BUS(obj) OBJECT_CHECK(I2CBus, (obj), TYPE_I2C_BUS)

static const TypeInfo i2c_bus_info = {
    .name = TYPE_I2C_BUS,
    .parent = TYPE_BUS,
    .instance_size = sizeof(I2CBus),
};

static int i2c_bus_pre_save(void *opaque)
{
    I2CBus *bus = opaque;

    bus->saved_address = -1;
    if (!QLIST_EMPTY(&bus->current_devs)) {
        if (!bus->broadcast) {
            bus->saved_address = QLIST_FIRST(&bus->current_devs)->elt->address;
        } else {
            bus->saved_address = I2C_BROADCAST;
        }
    }

    return 0;
}

static const VMStateDescription vmstate_i2c_bus = {
    .name = "i2c_bus",
    .version_id = 1,
    .minimum_version_id = 1,
    .pre_save = i2c_bus_pre_save,
    .fields = (VMStateField[]) {
        VMSTATE_UINT8(saved_address, I2CBus),
        VMSTATE_END_OF_LIST()
    }
};

/* Create a new I2C bus.  */
I2CBus *i2c_init_bus(DeviceState *parent, const char *name)
{
    I2CBus *bus;

    bus = I2C_BUS(qbus_create(TYPE_I2C_BUS, parent, name));
    QLIST_INIT(&bus->current_devs);
    vmstate_register(NULL, -1, &vmstate_i2c_bus, bus);
    return bus;
}

void i2c_set_slave_address(I2CSlave *dev, uint8_t address)
{
    dev->address = address;
}

/* Return nonzero if bus is busy.  */
int i2c_bus_busy(I2CBus *bus)
{
    return !QLIST_EMPTY(&bus->current_devs);
}

/* TODO: Make this handle multiple masters.  */
/*
 * Start or continue an i2c transaction.  When this is called for the
 * first time or after an i2c_end_transfer(), if it returns an error
 * the bus transaction is terminated (or really never started).  If
 * this is called after another i2c_start_transfer() without an
 * intervening i2c_end_transfer(), and it returns an error, the
 * transaction will not be terminated.  The caller must do it.
 *
 * This corresponds with the way real hardware works.  The SMBus
 * protocol uses a start transfer to switch from write to read mode
 * without releasing the bus.  If that fails, the bus is still
 * in a transaction.
 */
int i2c_start_transfer(I2CBus *bus, uint8_t address, int recv)
{
    BusChild *kid;
    I2CSlaveClass *sc;
    I2CNode *node;
    bool bus_scanned = false;

    if (address == I2C_BROADCAST) {
        /*
         * This is a broadcast, the current_devs will be all the devices of the
         * bus.
         */
        bus->broadcast = true;
    }

    /*
     * If there are already devices in the list, that means we are in
     * the middle of a transaction and we shouldn't rescan the bus.
     *
     * This happens with any SMBus transaction, even on a pure I2C
     * device.  The interface does a transaction start without
     * terminating the previous transaction.
     */
    if (QLIST_EMPTY(&bus->current_devs)) {
        QTAILQ_FOREACH(kid, &bus->qbus.children, sibling) {
            DeviceState *qdev = kid->child;
            I2CSlave *candidate = I2C_SLAVE(qdev);
            if ((candidate->address <= address &&
                 address < candidate->address + candidate->address_range) ||
                (bus->broadcast)) {
                /* If the device is mux/switch, probe for required slave.
                 * decode_address probes the requested slave and returns 1
                 * on failure, and returns 0 if a slave is found (or)
                 * address mached itself.
                 */
                if (candidate->address == 0 && !bus->broadcast) {
                    sc = I2C_SLAVE_GET_CLASS(candidate);
                    if (sc->decode_address) {
                        if (sc->decode_address(candidate, address)) {
                            continue;
                        }
                    }
                }
                node = g_malloc(sizeof(struct I2CNode));
                node->elt = candidate;
                QLIST_INSERT_HEAD(&bus->current_devs, node, next);
                if (!bus->broadcast) {
                    break;
                }
            }
        }
        bus_scanned = true;
    }

    if (QLIST_EMPTY(&bus->current_devs)) {
        return 1;
    }

    QLIST_FOREACH(node, &bus->current_devs, next) {
        int rv;

        sc = I2C_SLAVE_GET_CLASS(node->elt);
        /* If the bus is already busy, assume this is a repeated
           start condition.  */

        if (sc->event) {
            rv = sc->event(node->elt, recv ? I2C_START_RECV : I2C_START_SEND);
            if (rv && !bus->broadcast) {
                if (bus_scanned) {
                    /* First call, terminate the transfer. */
                    i2c_end_transfer(bus);
                }
                return rv;
            }
        }
        if (sc->decode_address) {
            if (sc->decode_address(node->elt, address)) {
                return 1;
            }
        }
    }
    return 0;
}

void i2c_end_transfer(I2CBus *bus)
{
    I2CSlaveClass *sc;
    I2CNode *node, *next;

    if (QLIST_EMPTY(&bus->current_devs)) {
        return;
    }

    QLIST_FOREACH_SAFE(node, &bus->current_devs, next, next) {
        sc = I2C_SLAVE_GET_CLASS(node->elt);
        if (sc->event) {
            sc->event(node->elt, I2C_FINISH);
        }
        QLIST_REMOVE(node, next);
        g_free(node);
    }
    bus->broadcast = false;
}

int i2c_send_recv(I2CBus *bus, uint8_t *data, bool send)
{
    I2CSlaveClass *sc;
    I2CNode *node;
    int ret = 0;

    if (send) {
        QLIST_FOREACH(node, &bus->current_devs, next) {
            sc = I2C_SLAVE_GET_CLASS(node->elt);
            if (sc->send) {
                ret = ret || sc->send(node->elt, *data);
            } else {
                ret = -1;
            }
        }
        return ret ? -1 : 0;
    } else {
        if ((QLIST_EMPTY(&bus->current_devs)) || (bus->broadcast)) {
            return -1;
        }

        sc = I2C_SLAVE_GET_CLASS(QLIST_FIRST(&bus->current_devs)->elt);
        if (sc->recv) {
            ret = sc->recv(QLIST_FIRST(&bus->current_devs)->elt);
            if (ret < 0) {
                return ret;
            } else {
                *data = ret;
                return 0;
            }
        }
        return -1;
    }
}

int i2c_send(I2CBus *bus, uint8_t data)
{
    return i2c_send_recv(bus, &data, true);
}

int i2c_recv(I2CBus *bus)
{
    uint8_t data;
    int ret = i2c_send_recv(bus, &data, false);

    return ret < 0 ? ret : data;
}

void i2c_nack(I2CBus *bus)
{
    I2CSlaveClass *sc;
    I2CNode *node;

    if (QLIST_EMPTY(&bus->current_devs)) {
        return;
    }

    QLIST_FOREACH(node, &bus->current_devs, next) {
        sc = I2C_SLAVE_GET_CLASS(node->elt);
        if (sc->event) {
            sc->event(node->elt, I2C_NACK);
        }
    }
}

static int i2c_slave_post_load(void *opaque, int version_id)
{
    I2CSlave *dev = opaque;
    I2CBus *bus;
    I2CNode *node;

    bus = I2C_BUS(qdev_get_parent_bus(DEVICE(dev)));
    if ((bus->saved_address == dev->address) ||
        (bus->saved_address == I2C_BROADCAST)) {
        node = g_malloc(sizeof(struct I2CNode));
        node->elt = dev;
        QLIST_INSERT_HEAD(&bus->current_devs, node, next);
    }
    return 0;
}

const VMStateDescription vmstate_i2c_slave = {
    .name = "I2CSlave",
    .version_id = 1,
    .minimum_version_id = 1,
    .post_load = i2c_slave_post_load,
    .fields = (VMStateField[]) {
        VMSTATE_UINT8(address, I2CSlave),
        VMSTATE_UINT8(address_range, I2CSlave),
        VMSTATE_BOOL(broadcast, I2CBus),
        VMSTATE_END_OF_LIST()
    }
};

static int i2c_slave_qdev_init(DeviceState *dev)
{
    I2CSlave *s = I2C_SLAVE(dev);
    I2CSlaveClass *sc = I2C_SLAVE_GET_CLASS(s);

    if (sc->init) {
        return sc->init(s);
    }

    return 0;
}

DeviceState *i2c_create_slave(I2CBus *bus, const char *name, uint8_t addr)
{
    DeviceState *dev;

    dev = qdev_create(&bus->qbus, name);
    qdev_prop_set_uint8(dev, "address", addr);
    qdev_init_nofail(dev);
    return dev;
}

static bool i2c_slave_parse_reg(FDTGenericMMap *obj, FDTGenericRegPropInfo reg,
                                Error **errp)
{
    DeviceState *parent;
    I2CSlave *slave;

    slave = I2C_SLAVE(obj);

    slave->address = reg.a[0];
    parent = (DeviceState *)object_dynamic_cast(reg.parents[0], TYPE_DEVICE);

    if (!parent) {
            return false;
    }

    if (!parent->realized) {
        return true;
    }

    qdev_set_parent_bus(DEVICE(obj), qdev_get_child_bus(parent, "i2c"));

    return false;
}

static void i2c_slave_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *k = DEVICE_CLASS(klass);
    FDTGenericMMapClass *fmc = FDT_GENERIC_MMAP_CLASS(klass);
    k->init = i2c_slave_qdev_init;
    set_bit(DEVICE_CATEGORY_MISC, k->categories);
    k->bus_type = TYPE_I2C_BUS;
    k->props = i2c_props;
    fmc->parse_reg = i2c_slave_parse_reg;
}

static const TypeInfo i2c_slave_type_info = {
    .name = TYPE_I2C_SLAVE,
    .parent = TYPE_DEVICE,
    .instance_size = sizeof(I2CSlave),
    .abstract = true,
    .class_size = sizeof(I2CSlaveClass),
    .class_init = i2c_slave_class_init,
    .interfaces = (InterfaceInfo []) {
        { TYPE_FDT_GENERIC_MMAP },
        { },
    },
};

static void i2c_slave_register_types(void)
{
    type_register_static(&i2c_bus_info);
    type_register_static(&i2c_slave_type_info);
}

type_init(i2c_slave_register_types)
