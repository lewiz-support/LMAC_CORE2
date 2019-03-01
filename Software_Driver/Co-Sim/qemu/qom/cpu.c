/*
 * QEMU CPU model
 *
 * Copyright (c) 2012-2014 SUSE LINUX Products GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html>
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "qom/cpu.h"
#include "sysemu/hw_accel.h"
#include "qemu/notify.h"
#include "qemu/log.h"
#include "exec/log.h"
#include "exec/cpu-common.h"
#include "qemu/error-report.h"
#include "sysemu/sysemu.h"
#include "hw/boards.h"
#include "hw/qdev-properties.h"
#include "trace-root.h"

CPUInterruptHandler cpu_interrupt_handler;

CPUState *cpu_by_arch_id(int64_t id)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        CPUClass *cc = CPU_GET_CLASS(cpu);

        if (cc->get_arch_id(cpu) == id) {
            return cpu;
        }
    }
    return NULL;
}

bool cpu_exists(int64_t id)
{
    return !!cpu_by_arch_id(id);
}

CPUState *cpu_create(const char *typename)
{
    Error *err = NULL;
    CPUState *cpu = CPU(object_new(typename));
    object_property_set_bool(OBJECT(cpu), true, "realized", &err);
    if (err != NULL) {
        error_report_err(err);
        object_unref(OBJECT(cpu));
        exit(EXIT_FAILURE);
    }
    return cpu;
}

const char *cpu_parse_cpu_model(const char *typename, const char *cpu_model)
{
    ObjectClass *oc;
    CPUClass *cc;
    gchar **model_pieces;
    const char *cpu_type;

    model_pieces = g_strsplit(cpu_model, ",", 2);

    oc = cpu_class_by_name(typename, model_pieces[0]);
    if (oc == NULL) {
        error_report("unable to find CPU model '%s'", model_pieces[0]);
        g_strfreev(model_pieces);
        exit(EXIT_FAILURE);
    }

    cpu_type = object_class_get_name(oc);
    cc = CPU_CLASS(oc);
    cc->parse_features(cpu_type, model_pieces[1], &error_fatal);
    g_strfreev(model_pieces);
    return cpu_type;
}

CPUState *cpu_generic_init(const char *typename, const char *cpu_model)
{
    /* TODO: all callers of cpu_generic_init() need to be converted to
     * call cpu_parse_features() only once, before calling cpu_generic_init().
     */
    return cpu_create(cpu_parse_cpu_model(typename, cpu_model));
}

bool cpu_paging_enabled(const CPUState *cpu)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    return cc->get_paging_enabled(cpu);
}

static bool cpu_common_get_paging_enabled(const CPUState *cpu)
{
    return false;
}

void cpu_get_memory_mapping(CPUState *cpu, MemoryMappingList *list,
                            Error **errp)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    cc->get_memory_mapping(cpu, list, errp);
}

static void cpu_common_get_memory_mapping(CPUState *cpu,
                                          MemoryMappingList *list,
                                          Error **errp)
{
    error_setg(errp, "Obtaining memory mappings is unsupported on this CPU.");
}

/* Resetting the IRQ comes from across the code base so we take the
 * BQL here if we need to.  cpu_interrupt assumes it is held.*/
void cpu_reset_interrupt(CPUState *cpu, int mask)
{
    bool need_lock = !qemu_mutex_iothread_locked();

    if (need_lock) {
        qemu_mutex_lock_iothread();
    }
    cpu->interrupt_request &= ~mask;
    if (need_lock) {
        qemu_mutex_unlock_iothread();
    }
}

void cpu_exit(CPUState *cpu)
{
    atomic_set(&cpu->exit_request, 1);
    /* Ensure cpu_exec will see the exit request after TCG has exited.  */
    smp_wmb();
    atomic_set(&cpu->icount_decr.u16.high, -1);
}

int cpu_write_elf32_qemunote(WriteCoreDumpFunction f, CPUState *cpu,
                             void *opaque)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    return (*cc->write_elf32_qemunote)(f, cpu, opaque);
}

static int cpu_common_write_elf32_qemunote(WriteCoreDumpFunction f,
                                           CPUState *cpu, void *opaque)
{
    return 0;
}

int cpu_write_elf32_note(WriteCoreDumpFunction f, CPUState *cpu,
                         int cpuid, void *opaque)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    return (*cc->write_elf32_note)(f, cpu, cpuid, opaque);
}

static int cpu_common_write_elf32_note(WriteCoreDumpFunction f,
                                       CPUState *cpu, int cpuid,
                                       void *opaque)
{
    return -1;
}

int cpu_write_elf64_qemunote(WriteCoreDumpFunction f, CPUState *cpu,
                             void *opaque)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    return (*cc->write_elf64_qemunote)(f, cpu, opaque);
}

static int cpu_common_write_elf64_qemunote(WriteCoreDumpFunction f,
                                           CPUState *cpu, void *opaque)
{
    return 0;
}

int cpu_write_elf64_note(WriteCoreDumpFunction f, CPUState *cpu,
                         int cpuid, void *opaque)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    return (*cc->write_elf64_note)(f, cpu, cpuid, opaque);
}

static int cpu_common_write_elf64_note(WriteCoreDumpFunction f,
                                       CPUState *cpu, int cpuid,
                                       void *opaque)
{
    return -1;
}


static int cpu_common_gdb_read_register(CPUState *cpu, uint8_t *buf, int reg)
{
    return 0;
}

static int cpu_common_gdb_write_register(CPUState *cpu, uint8_t *buf, int reg)
{
    return 0;
}

static bool cpu_common_debug_check_watchpoint(CPUState *cpu, CPUWatchpoint *wp)
{
    /* If no extra check is required, QEMU watchpoint match can be considered
     * as an architectural match.
     */
    return true;
}

bool target_words_bigendian(void);
static bool cpu_common_virtio_is_big_endian(CPUState *cpu)
{
    return target_words_bigendian();
}

static void cpu_common_noop(CPUState *cpu)
{
}

static bool cpu_common_exec_interrupt(CPUState *cpu, int int_req)
{
    return false;
}

GuestPanicInformation *cpu_get_crash_info(CPUState *cpu)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);
    GuestPanicInformation *res = NULL;

    if (cc->get_crash_info) {
        res = cc->get_crash_info(cpu);
    }
    return res;
}

void cpu_dump_state(CPUState *cpu, FILE *f, fprintf_function cpu_fprintf,
                    int flags)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    if (cc->dump_state) {
        cpu_synchronize_state(cpu);
        cc->dump_state(cpu, f, cpu_fprintf, flags);
    }
}

void cpu_dump_statistics(CPUState *cpu, FILE *f, fprintf_function cpu_fprintf,
                         int flags)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);

    if (cc->dump_statistics) {
        cc->dump_statistics(cpu, f, cpu_fprintf, flags);
    }
}

void cpu_reset(CPUState *cpu)
{
    CPUClass *klass = CPU_GET_CLASS(cpu);

    if (klass->reset != NULL) {
        (*klass->reset)(cpu);
    }

    trace_guest_cpu_reset(cpu);
}

static void cpu_common_reset(CPUState *cpu)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);
    bool old_halt = cpu->halt_pin;
    bool old_reset = cpu->reset_pin;

    if (qemu_loglevel_mask(CPU_LOG_RESET)) {
        qemu_log("CPU Reset (CPU %d)\n", cpu->cpu_index);
        log_cpu_state(cpu, cc->reset_dump_flags);
    }

    cpu->interrupt_request = 0;
    cpu->halted = 0;
    cpu->mem_io_pc = 0;
    cpu->mem_io_vaddr = 0;
    cpu->icount_extra = 0;
    cpu->icount_decr.u32 = 0;
    cpu->can_do_io = 1;
    cpu->exception_index = -1;
    cpu->crash_occurred = false;
    cpu->cflags_next_tb = -1;
    memset(cpu->tb_jmp_cache, 0, TB_JMP_CACHE_SIZE * sizeof(void *));
    cpu_halt_gpio(cpu, 0, old_halt);
    cpu_reset_gpio(cpu, 0, old_reset);

    if (tcg_enabled()) {
        cpu_tb_jmp_cache_clear(cpu);

        tcg_flush_softmmu_tlb(cpu);
    }
}

static bool cpu_common_has_work(CPUState *cs)
{
    return false;
}

static void cpu_device_reset(DeviceState *dev)
{
    cpu_reset(CPU(dev));
}

ObjectClass *cpu_class_by_name(const char *typename, const char *cpu_model)
{
    CPUClass *cc;

    if (!cpu_model) {
        return NULL;
    }
    cc = CPU_CLASS(object_class_by_name(typename));

    return cc->class_by_name(cpu_model);
}

static ObjectClass *cpu_common_class_by_name(const char *cpu_model)
{
    return NULL;
}

static void cpu_common_parse_features(const char *typename, char *features,
                                      Error **errp)
{
    char *featurestr; /* Single "key=value" string being parsed */
    char *val;
    static bool cpu_globals_initialized;

    /* TODO: all callers of ->parse_features() need to be changed to
     * call it only once, so we can remove this check (or change it
     * to assert(!cpu_globals_initialized).
     * Current callers of ->parse_features() are:
     * - cpu_generic_init()
     */
    if (cpu_globals_initialized) {
        return;
    }
    cpu_globals_initialized = true;

    featurestr = features ? strtok(features, ",") : NULL;

    while (featurestr) {
        val = strchr(featurestr, '=');
        if (val) {
            GlobalProperty *prop = g_new0(typeof(*prop), 1);
            *val = 0;
            val++;
            prop->driver = typename;
            prop->property = g_strdup(featurestr);
            prop->value = g_strdup(val);
            prop->errp = &error_fatal;
            qdev_prop_register_global(prop);
        } else {
            error_setg(errp, "Expected key=value format, found %s.",
                       featurestr);
            return;
        }
        featurestr = strtok(NULL, ",");
    }
}

static void cpu_common_realizefn(DeviceState *dev, Error **errp)
{
    CPUState *cpu = CPU(dev);
    Object *machine = qdev_get_machine();

    /* qdev_get_machine() can return something that's not TYPE_MACHINE
     * if this is one of the user-only emulators; in that case there's
     * no need to check the ignore_memory_transaction_failures board flag.
     */
    if (object_dynamic_cast(machine, TYPE_MACHINE)) {
        ObjectClass *oc = object_get_class(machine);
        MachineClass *mc = MACHINE_CLASS(oc);

        if (mc) {
            cpu->ignore_memory_transaction_failures =
                mc->ignore_memory_transaction_failures;
        }
    }

    if (dev->hotplugged) {
        cpu_synchronize_post_init(cpu);
        cpu_resume(cpu);
    }

    /* NOTE: latest generic point where the cpu is fully realized */
    trace_init_vcpu(cpu);
}

static void cpu_common_unrealizefn(DeviceState *dev, Error **errp)
{
    CPUState *cpu = CPU(dev);
    /* NOTE: latest generic point before the cpu is fully unrealized */
    trace_fini_vcpu(cpu);
    cpu_exec_unrealizefn(cpu);
}

static void cpu_common_initfn(Object *obj)
{
    CPUState *cpu = CPU(obj);
    CPUClass *cc = CPU_GET_CLASS(obj);

    cpu->cpu_index = UNASSIGNED_CPU_INDEX;
    cpu->gdb_num_regs = cpu->gdb_num_g_regs = cc->gdb_num_core_regs;
    /* *-user doesn't have configurable SMP topology */
    /* the default value is changed by qemu_init_vcpu() for softmmu */
    cpu->nr_cores = 1;
    cpu->nr_threads = 1;

    qemu_mutex_init(&cpu->work_mutex);
    QTAILQ_INIT(&cpu->breakpoints);
    QTAILQ_INIT(&cpu->watchpoints);

    /* Xilinx: The GPIO lines we use */
    qdev_init_gpio_in_named(DEVICE(obj), cpu_reset_gpio, "reset", 1);
    qdev_init_gpio_in_named(DEVICE(obj), cpu_halt_gpio, "halt", 1);

    cpu_exec_initfn(cpu);
}

static void cpu_common_finalize(Object *obj)
{
}

static int64_t cpu_common_get_arch_id(CPUState *cpu)
{
    return cpu->cpu_index;
}

static vaddr cpu_adjust_watchpoint_address(CPUState *cpu, vaddr addr, int len)
{
    return addr;
}

static void generic_handle_interrupt(CPUState *cpu, int mask)
{
    cpu->interrupt_request |= mask;

    if (!qemu_cpu_is_self(cpu)) {
        qemu_cpu_kick(cpu);
    }
}

CPUInterruptHandler cpu_interrupt_handler = generic_handle_interrupt;

static void cpu_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    CPUClass *k = CPU_CLASS(klass);

    k->class_by_name = cpu_common_class_by_name;
    k->parse_features = cpu_common_parse_features;
    k->reset = cpu_common_reset;
    k->get_arch_id = cpu_common_get_arch_id;
    k->has_work = cpu_common_has_work;
    k->get_paging_enabled = cpu_common_get_paging_enabled;
    k->get_memory_mapping = cpu_common_get_memory_mapping;
    k->write_elf32_qemunote = cpu_common_write_elf32_qemunote;
    k->write_elf32_note = cpu_common_write_elf32_note;
    k->write_elf64_qemunote = cpu_common_write_elf64_qemunote;
    k->write_elf64_note = cpu_common_write_elf64_note;
    k->gdb_read_register = cpu_common_gdb_read_register;
    k->gdb_write_register = cpu_common_gdb_write_register;
    k->virtio_is_big_endian = cpu_common_virtio_is_big_endian;
    k->debug_excp_handler = cpu_common_noop;
    k->debug_check_watchpoint = cpu_common_debug_check_watchpoint;
    k->cpu_exec_enter = cpu_common_noop;
    k->cpu_exec_exit = cpu_common_noop;
    k->cpu_exec_interrupt = cpu_common_exec_interrupt;
    dc->reset = cpu_device_reset;
    k->adjust_watchpoint_address = cpu_adjust_watchpoint_address;
    set_bit(DEVICE_CATEGORY_CPU, dc->categories);
    dc->realize = cpu_common_realizefn;
    dc->unrealize = cpu_common_unrealizefn;
    dc->props = cpu_common_props;
    /*
     * Reason: CPUs still need special care by board code: wiring up
     * IRQs, adding reset handlers, halting non-first CPUs, ...
     */
    dc->user_creatable = false;
}

static const TypeInfo cpu_type_info = {
    .name = TYPE_CPU,
    .parent = TYPE_DEVICE,
    .instance_size = sizeof(CPUState),
    .instance_init = cpu_common_initfn,
    .instance_finalize = cpu_common_finalize,
    .abstract = true,
    .class_size = sizeof(CPUClass),
    .class_init = cpu_class_init,
};

static void cpu_register_types(void)
{
    type_register_static(&cpu_type_info);
}

type_init(cpu_register_types)
