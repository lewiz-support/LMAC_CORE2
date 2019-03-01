/*
 *  Emulator TPM driver
 *
 *  Copyright (c) 2017 Intel Corporation
 *  Author: Amarnath Valluri <amarnath.valluri@intel.com>
 *
 *  Copyright (c) 2010 - 2013 IBM Corporation
 *  Authors:
 *    Stefan Berger <stefanb@us.ibm.com>
 *
 *  Copyright (C) 2011 IAIK, Graz University of Technology
 *    Author: Andreas Niederl
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>
 *
 */

#include "qemu/osdep.h"
#include "qemu/error-report.h"
#include "qemu/sockets.h"
#include "io/channel-socket.h"
#include "sysemu/tpm_backend.h"
#include "tpm_int.h"
#include "hw/hw.h"
#include "hw/i386/pc.h"
#include "tpm_util.h"
#include "tpm_ioctl.h"
#include "migration/blocker.h"
#include "qapi/error.h"
#include "qapi/clone-visitor.h"
#include "chardev/char-fe.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define DEBUG_TPM 0

#define DPRINTF(fmt, ...) do { \
    if (DEBUG_TPM) { \
        fprintf(stderr, "tpm-emulator:"fmt"\n", ## __VA_ARGS__); \
    } \
} while (0)

#define TYPE_TPM_EMULATOR "tpm-emulator"
#define TPM_EMULATOR(obj) \
    OBJECT_CHECK(TPMEmulator, (obj), TYPE_TPM_EMULATOR)

#define TPM_EMULATOR_IMPLEMENTS_ALL_CAPS(S, cap) (((S)->caps & (cap)) == (cap))

/* data structures */
typedef struct TPMEmulator {
    TPMBackend parent;

    TPMEmulatorOptions *options;
    CharBackend ctrl_chr;
    QIOChannel *data_ioc;
    TPMVersion tpm_version;
    ptm_cap caps; /* capabilities of the TPM */
    uint8_t cur_locty_number; /* last set locality */
    Error *migration_blocker;

    QemuMutex mutex;
} TPMEmulator;


static int tpm_emulator_ctrlcmd(TPMEmulator *tpm, unsigned long cmd, void *msg,
                                size_t msg_len_in, size_t msg_len_out)
{
    CharBackend *dev = &tpm->ctrl_chr;
    uint32_t cmd_no = cpu_to_be32(cmd);
    ssize_t n = sizeof(uint32_t) + msg_len_in;
    uint8_t *buf = NULL;
    int ret = -1;

    qemu_mutex_lock(&tpm->mutex);

    buf = g_alloca(n);
    memcpy(buf, &cmd_no, sizeof(cmd_no));
    memcpy(buf + sizeof(cmd_no), msg, msg_len_in);

    n = qemu_chr_fe_write_all(dev, buf, n);
    if (n <= 0) {
        goto end;
    }

    if (msg_len_out != 0) {
        n = qemu_chr_fe_read_all(dev, msg, msg_len_out);
        if (n <= 0) {
            goto end;
        }
    }

    ret = 0;

end:
    qemu_mutex_unlock(&tpm->mutex);
    return ret;
}

static int tpm_emulator_unix_tx_bufs(TPMEmulator *tpm_emu,
                                     const uint8_t *in, uint32_t in_len,
                                     uint8_t *out, uint32_t out_len,
                                     bool *selftest_done,
                                     Error **err)
{
    ssize_t ret;
    bool is_selftest = false;
    const struct tpm_resp_hdr *hdr = NULL;

    if (selftest_done) {
        *selftest_done = false;
        is_selftest = tpm_util_is_selftest(in, in_len);
    }

    ret = qio_channel_write_all(tpm_emu->data_ioc, (char *)in, in_len, err);
    if (ret != 0) {
        return -1;
    }

    ret = qio_channel_read_all(tpm_emu->data_ioc, (char *)out, sizeof(*hdr),
                               err);
    if (ret != 0) {
        return -1;
    }

    hdr = (struct tpm_resp_hdr *)out;
    out += sizeof(*hdr);
    ret = qio_channel_read_all(tpm_emu->data_ioc, (char *)out,
                               be32_to_cpu(hdr->len) - sizeof(*hdr) , err);
    if (ret != 0) {
        return -1;
    }

    if (is_selftest) {
        *selftest_done = (be32_to_cpu(hdr->errcode) == 0);
    }

    return 0;
}

static int tpm_emulator_set_locality(TPMEmulator *tpm_emu, uint8_t locty_number,
                                     Error **errp)
{
    ptm_loc loc;

    DPRINTF("%s : locality: 0x%x", __func__, locty_number);

    if (tpm_emu->cur_locty_number == locty_number) {
        return 0;
    }

    DPRINTF("setting locality : 0x%x", locty_number);
    loc.u.req.loc = locty_number;
    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_SET_LOCALITY, &loc,
                             sizeof(loc), sizeof(loc)) < 0) {
        error_setg(errp, "tpm-emulator: could not set locality : %s",
                   strerror(errno));
        return -1;
    }

    loc.u.resp.tpm_result = be32_to_cpu(loc.u.resp.tpm_result);
    if (loc.u.resp.tpm_result != 0) {
        error_setg(errp, "tpm-emulator: TPM result for set locality : 0x%x",
                   loc.u.resp.tpm_result);
        return -1;
    }

    tpm_emu->cur_locty_number = locty_number;

    return 0;
}

static void tpm_emulator_handle_request(TPMBackend *tb, TPMBackendCmd *cmd)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    TPMIfClass *tic = TPM_IF_GET_CLASS(tb->tpm_state);
    Error *err = NULL;

    DPRINTF("processing TPM command");

    if (tpm_emulator_set_locality(tpm_emu, cmd->locty, &err) < 0) {
        goto error;
    }

    if (tpm_emulator_unix_tx_bufs(tpm_emu, cmd->in, cmd->in_len,
                                  cmd->out, cmd->out_len,
                                  &cmd->selftest_done, &err) < 0) {
        goto error;
    }

    tic->request_completed(TPM_IF(tb->tpm_state));
    return;

error:
    tpm_util_write_fatal_error_response(cmd->out, cmd->out_len);
    error_report_err(err);
}

static int tpm_emulator_probe_caps(TPMEmulator *tpm_emu)
{
    DPRINTF("%s", __func__);
    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_GET_CAPABILITY,
                             &tpm_emu->caps, 0, sizeof(tpm_emu->caps)) < 0) {
        error_report("tpm-emulator: probing failed : %s", strerror(errno));
        return -1;
    }

    tpm_emu->caps = be64_to_cpu(tpm_emu->caps);

    DPRINTF("capabilities : 0x%"PRIx64, tpm_emu->caps);

    return 0;
}

static int tpm_emulator_check_caps(TPMEmulator *tpm_emu)
{
    ptm_cap caps = 0;
    const char *tpm = NULL;

    /* check for min. required capabilities */
    switch (tpm_emu->tpm_version) {
    case TPM_VERSION_1_2:
        caps = PTM_CAP_INIT | PTM_CAP_SHUTDOWN | PTM_CAP_GET_TPMESTABLISHED |
               PTM_CAP_SET_LOCALITY | PTM_CAP_SET_DATAFD;
        tpm = "1.2";
        break;
    case TPM_VERSION_2_0:
        caps = PTM_CAP_INIT | PTM_CAP_SHUTDOWN | PTM_CAP_GET_TPMESTABLISHED |
               PTM_CAP_SET_LOCALITY | PTM_CAP_RESET_TPMESTABLISHED |
               PTM_CAP_SET_DATAFD;
        tpm = "2";
        break;
    case TPM_VERSION_UNSPEC:
        error_report("tpm-emulator: TPM version has not been set");
        return -1;
    }

    if (!TPM_EMULATOR_IMPLEMENTS_ALL_CAPS(tpm_emu, caps)) {
        error_report("tpm-emulator: TPM does not implement minimum set of "
                     "required capabilities for TPM %s (0x%x)", tpm, (int)caps);
        return -1;
    }

    return 0;
}

static int tpm_emulator_startup_tpm(TPMBackend *tb)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    ptm_init init;
    ptm_res res;

    DPRINTF("%s", __func__);
    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_INIT, &init, sizeof(init),
                             sizeof(init)) < 0) {
        error_report("tpm-emulator: could not send INIT: %s",
                     strerror(errno));
        goto err_exit;
    }

    res = be32_to_cpu(init.u.resp.tpm_result);
    if (res) {
        error_report("tpm-emulator: TPM result for CMD_INIT: 0x%x", res);
        goto err_exit;
    }
    return 0;

err_exit:
    return -1;
}

static bool tpm_emulator_get_tpm_established_flag(TPMBackend *tb)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    ptm_est est;

    DPRINTF("%s", __func__);
    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_GET_TPMESTABLISHED, &est,
                             0, sizeof(est)) < 0) {
        error_report("tpm-emulator: Could not get the TPM established flag: %s",
                     strerror(errno));
        return false;
    }
    DPRINTF("established flag: %0x", est.u.resp.bit);

    return (est.u.resp.bit != 0);
}

static int tpm_emulator_reset_tpm_established_flag(TPMBackend *tb,
                                                   uint8_t locty)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    ptm_reset_est reset_est;
    ptm_res res;

    /* only a TPM 2.0 will support this */
    if (tpm_emu->tpm_version != TPM_VERSION_2_0) {
        return 0;
    }

    reset_est.u.req.loc = tpm_emu->cur_locty_number;
    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_RESET_TPMESTABLISHED,
                             &reset_est, sizeof(reset_est),
                             sizeof(reset_est)) < 0) {
        error_report("tpm-emulator: Could not reset the establishment bit: %s",
                     strerror(errno));
        return -1;
    }

    res = be32_to_cpu(reset_est.u.resp.tpm_result);
    if (res) {
        error_report("tpm-emulator: TPM result for rest establixhed flag: 0x%x",
                     res);
        return -1;
    }

    return 0;
}

static void tpm_emulator_cancel_cmd(TPMBackend *tb)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    ptm_res res;

    if (!TPM_EMULATOR_IMPLEMENTS_ALL_CAPS(tpm_emu, PTM_CAP_CANCEL_TPM_CMD)) {
        DPRINTF("Backend does not support CANCEL_TPM_CMD");
        return;
    }

    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_CANCEL_TPM_CMD, &res, 0,
                             sizeof(res)) < 0) {
        error_report("tpm-emulator: Could not cancel command: %s",
                     strerror(errno));
    } else if (res != 0) {
        error_report("tpm-emulator: Failed to cancel TPM: 0x%x",
                     be32_to_cpu(res));
    }
}

static TPMVersion tpm_emulator_get_tpm_version(TPMBackend *tb)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);

    return tpm_emu->tpm_version;
}

static int tpm_emulator_block_migration(TPMEmulator *tpm_emu)
{
    Error *err = NULL;

    error_setg(&tpm_emu->migration_blocker,
               "Migration disabled: TPM emulator not yet migratable");
    migrate_add_blocker(tpm_emu->migration_blocker, &err);
    if (err) {
        error_report_err(err);
        error_free(tpm_emu->migration_blocker);
        tpm_emu->migration_blocker = NULL;

        return -1;
    }

    return 0;
}

static int tpm_emulator_prepare_data_fd(TPMEmulator *tpm_emu)
{
    ptm_res res;
    Error *err = NULL;
    int fds[2] = { -1, -1 };

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0) {
        error_report("tpm-emulator: Failed to create socketpair");
        return -1;
    }

    qemu_chr_fe_set_msgfds(&tpm_emu->ctrl_chr, fds + 1, 1);

    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_SET_DATAFD, &res, 0,
                             sizeof(res)) < 0 || res != 0) {
        error_report("tpm-emulator: Failed to send CMD_SET_DATAFD: %s",
                     strerror(errno));
        goto err_exit;
    }

    tpm_emu->data_ioc = QIO_CHANNEL(qio_channel_socket_new_fd(fds[0], &err));
    if (err) {
        error_prepend(&err, "tpm-emulator: Failed to create io channel: ");
        error_report_err(err);
        goto err_exit;
    }

    closesocket(fds[1]);

    return 0;

err_exit:
    closesocket(fds[0]);
    closesocket(fds[1]);
    return -1;
}

static int tpm_emulator_handle_device_opts(TPMEmulator *tpm_emu, QemuOpts *opts)
{
    const char *value;

    value = qemu_opt_get(opts, "chardev");
    if (value) {
        Error *err = NULL;
        Chardev *dev = qemu_chr_find(value);

        if (!dev) {
            error_report("tpm-emulator: tpm chardev '%s' not found.", value);
            goto err;
        }

        if (!qemu_chr_fe_init(&tpm_emu->ctrl_chr, dev, &err)) {
            error_prepend(&err, "tpm-emulator: No valid chardev found at '%s':",
                          value);
            error_report_err(err);
            goto err;
        }

        tpm_emu->options->chardev = g_strdup(value);
    }

    if (tpm_emulator_prepare_data_fd(tpm_emu) < 0) {
        goto err;
    }

    /* FIXME: tpm_util_test_tpmdev() accepts only on socket fd, as it also used
     * by passthrough driver, which not yet using GIOChannel.
     */
    if (tpm_util_test_tpmdev(QIO_CHANNEL_SOCKET(tpm_emu->data_ioc)->fd,
                             &tpm_emu->tpm_version)) {
        error_report("'%s' is not emulating TPM device. Error: %s",
                      tpm_emu->options->chardev, strerror(errno));
        goto err;
    }

    DPRINTF("TPM Version %s", tpm_emu->tpm_version == TPM_VERSION_1_2 ? "1.2" :
            (tpm_emu->tpm_version == TPM_VERSION_2_0 ?  "2.0" : "Unspecified"));

    if (tpm_emulator_probe_caps(tpm_emu) ||
        tpm_emulator_check_caps(tpm_emu)) {
        goto err;
    }

    return tpm_emulator_block_migration(tpm_emu);

err:
    DPRINTF("Startup error");
    return -1;
}

static TPMBackend *tpm_emulator_create(QemuOpts *opts, const char *id)
{
    TPMBackend *tb = TPM_BACKEND(object_new(TYPE_TPM_EMULATOR));

    tb->id = g_strdup(id);

    if (tpm_emulator_handle_device_opts(TPM_EMULATOR(tb), opts)) {
        goto err_exit;
    }

    return tb;

err_exit:
    object_unref(OBJECT(tb));

    return NULL;
}

static TpmTypeOptions *tpm_emulator_get_tpm_options(TPMBackend *tb)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(tb);
    TpmTypeOptions *options = g_new0(TpmTypeOptions, 1);

    options->type = TPM_TYPE_OPTIONS_KIND_EMULATOR;
    options->u.emulator.data = QAPI_CLONE(TPMEmulatorOptions, tpm_emu->options);

    return options;
}

static const QemuOptDesc tpm_emulator_cmdline_opts[] = {
    TPM_STANDARD_CMDLINE_OPTS,
    {
        .name = "chardev",
        .type = QEMU_OPT_STRING,
        .help = "Character device to use for out-of-band control messages",
    },
    { /* end of list */ },
};

static void tpm_emulator_inst_init(Object *obj)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(obj);

    DPRINTF("%s", __func__);
    tpm_emu->options = g_new0(TPMEmulatorOptions, 1);
    tpm_emu->cur_locty_number = ~0;
    qemu_mutex_init(&tpm_emu->mutex);
}

/*
 * Gracefully shut down the external TPM
 */
static void tpm_emulator_shutdown(TPMEmulator *tpm_emu)
{
    ptm_res res;

    if (tpm_emulator_ctrlcmd(tpm_emu, CMD_SHUTDOWN, &res, 0, sizeof(res)) < 0) {
        error_report("tpm-emulator: Could not cleanly shutdown the TPM: %s",
                     strerror(errno));
    } else if (res != 0) {
        error_report("tpm-emulator: TPM result for sutdown: 0x%x",
                     be32_to_cpu(res));
    }
}

static void tpm_emulator_inst_finalize(Object *obj)
{
    TPMEmulator *tpm_emu = TPM_EMULATOR(obj);

    tpm_emulator_shutdown(tpm_emu);

    object_unref(OBJECT(tpm_emu->data_ioc));

    qemu_chr_fe_deinit(&tpm_emu->ctrl_chr, false);

    qapi_free_TPMEmulatorOptions(tpm_emu->options);

    if (tpm_emu->migration_blocker) {
        migrate_del_blocker(tpm_emu->migration_blocker);
        error_free(tpm_emu->migration_blocker);
    }

    qemu_mutex_destroy(&tpm_emu->mutex);
}

static void tpm_emulator_class_init(ObjectClass *klass, void *data)
{
    TPMBackendClass *tbc = TPM_BACKEND_CLASS(klass);

    tbc->type = TPM_TYPE_EMULATOR;
    tbc->opts = tpm_emulator_cmdline_opts;
    tbc->desc = "TPM emulator backend driver";
    tbc->create = tpm_emulator_create;
    tbc->startup_tpm = tpm_emulator_startup_tpm;
    tbc->cancel_cmd = tpm_emulator_cancel_cmd;
    tbc->get_tpm_established_flag = tpm_emulator_get_tpm_established_flag;
    tbc->reset_tpm_established_flag = tpm_emulator_reset_tpm_established_flag;
    tbc->get_tpm_version = tpm_emulator_get_tpm_version;
    tbc->get_tpm_options = tpm_emulator_get_tpm_options;

    tbc->handle_request = tpm_emulator_handle_request;
}

static const TypeInfo tpm_emulator_info = {
    .name = TYPE_TPM_EMULATOR,
    .parent = TYPE_TPM_BACKEND,
    .instance_size = sizeof(TPMEmulator),
    .class_init = tpm_emulator_class_init,
    .instance_init = tpm_emulator_inst_init,
    .instance_finalize = tpm_emulator_inst_finalize,
};

static void tpm_emulator_register(void)
{
    type_register_static(&tpm_emulator_info);
}

type_init(tpm_emulator_register)
