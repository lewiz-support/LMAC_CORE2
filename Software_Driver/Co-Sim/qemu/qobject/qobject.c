/*
 * QObject
 *
 * Copyright (C) 2015 Red Hat, Inc.
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1
 * or later.  See the COPYING.LIB file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "qapi/qmp/types.h"

static void (*qdestroy[QTYPE__MAX])(QObject *) = {
    [QTYPE_NONE] = NULL,               /* No such object exists */
    [QTYPE_QNULL] = NULL,              /* qnull_ is indestructible */
    [QTYPE_QNUM] = qnum_destroy_obj,
    [QTYPE_QSTRING] = qstring_destroy_obj,
    [QTYPE_QDICT] = qdict_destroy_obj,
    [QTYPE_QLIST] = qlist_destroy_obj,
    [QTYPE_QBOOL] = qbool_destroy_obj,
};

void qobject_destroy(QObject *obj)
{
    assert(!obj->refcnt);
    assert(QTYPE_QNULL < obj->type && obj->type < QTYPE__MAX);
    qdestroy[obj->type](obj);
}


static bool (*qis_equal[QTYPE__MAX])(const QObject *, const QObject *) = {
    [QTYPE_NONE] = NULL,               /* No such object exists */
    [QTYPE_QNULL] = qnull_is_equal,
    [QTYPE_QNUM] = qnum_is_equal,
    [QTYPE_QSTRING] = qstring_is_equal,
    [QTYPE_QDICT] = qdict_is_equal,
    [QTYPE_QLIST] = qlist_is_equal,
    [QTYPE_QBOOL] = qbool_is_equal,
};

bool qobject_is_equal(const QObject *x, const QObject *y)
{
    /* We cannot test x == y because an object does not need to be
     * equal to itself (e.g. NaN floats are not). */

    if (!x && !y) {
        return true;
    }

    if (!x || !y || x->type != y->type) {
        return false;
    }

    assert(QTYPE_NONE < x->type && x->type < QTYPE__MAX);

    return qis_equal[x->type](x, y);
}
