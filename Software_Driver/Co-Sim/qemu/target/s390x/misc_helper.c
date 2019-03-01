/*
 *  S/390 misc helper routines
 *
 *  Copyright (c) 2009 Ulrich Hecht
 *  Copyright (c) 2009 Alexander Graf
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
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qemu/main-loop.h"
#include "cpu.h"
#include "internal.h"
#include "exec/memory.h"
#include "qemu/host-utils.h"
#include "exec/helper-proto.h"
#include "qemu/timer.h"
#include "exec/address-spaces.h"
#include "exec/exec-all.h"
#include "exec/cpu_ldst.h"

#if !defined(CONFIG_USER_ONLY)
#include "sysemu/cpus.h"
#include "sysemu/sysemu.h"
#include "hw/s390x/ebcdic.h"
#include "hw/s390x/s390-virtio-hcall.h"
#include "hw/s390x/sclp.h"
#endif

/* #define DEBUG_HELPER */
#ifdef DEBUG_HELPER
#define HELPER_LOG(x...) qemu_log(x)
#else
#define HELPER_LOG(x...)
#endif

/* Raise an exception dynamically from a helper function.  */
void QEMU_NORETURN runtime_exception(CPUS390XState *env, int excp,
                                     uintptr_t retaddr)
{
    CPUState *cs = CPU(s390_env_get_cpu(env));

    cs->exception_index = EXCP_PGM;
    env->int_pgm_code = excp;
    env->int_pgm_ilen = ILEN_AUTO;

    /* Use the (ultimate) callers address to find the insn that trapped.  */
    cpu_restore_state(cs, retaddr);

    cpu_loop_exit(cs);
}

/* Raise an exception statically from a TB.  */
void HELPER(exception)(CPUS390XState *env, uint32_t excp)
{
    CPUState *cs = CPU(s390_env_get_cpu(env));

    HELPER_LOG("%s: exception %d\n", __func__, excp);
    cs->exception_index = excp;
    cpu_loop_exit(cs);
}

#ifndef CONFIG_USER_ONLY

/* SCLP service call */
uint32_t HELPER(servc)(CPUS390XState *env, uint64_t r1, uint64_t r2)
{
    qemu_mutex_lock_iothread();
    int r = sclp_service_call(env, r1, r2);
    if (r < 0) {
        program_interrupt(env, -r, 4);
        r = 0;
    }
    qemu_mutex_unlock_iothread();
    return r;
}

void HELPER(diag)(CPUS390XState *env, uint32_t r1, uint32_t r3, uint32_t num)
{
    uint64_t r;

    switch (num) {
    case 0x500:
        /* KVM hypercall */
        qemu_mutex_lock_iothread();
        r = s390_virtio_hypercall(env);
        qemu_mutex_unlock_iothread();
        break;
    case 0x44:
        /* yield */
        r = 0;
        break;
    case 0x308:
        /* ipl */
        qemu_mutex_lock_iothread();
        handle_diag_308(env, r1, r3);
        qemu_mutex_unlock_iothread();
        r = 0;
        break;
    case 0x288:
        /* time bomb (watchdog) */
        r = handle_diag_288(env, r1, r3);
        break;
    default:
        r = -1;
        break;
    }

    if (r) {
        program_interrupt(env, PGM_SPECIFICATION, ILEN_AUTO);
    }
}

/* Set Prefix */
void HELPER(spx)(CPUS390XState *env, uint64_t a1)
{
    CPUState *cs = CPU(s390_env_get_cpu(env));
    uint32_t prefix = a1 & 0x7fffe000;

    env->psa = prefix;
    HELPER_LOG("prefix: %#x\n", prefix);
    tlb_flush_page(cs, 0);
    tlb_flush_page(cs, TARGET_PAGE_SIZE);
}

/* Store Clock */
uint64_t HELPER(stck)(CPUS390XState *env)
{
    uint64_t time;

    time = env->tod_offset +
        time2tod(qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) - env->tod_basetime);

    return time;
}

/* Set Clock Comparator */
void HELPER(sckc)(CPUS390XState *env, uint64_t time)
{
    if (time == -1ULL) {
        return;
    }

    env->ckc = time;

    /* difference between origins */
    time -= env->tod_offset;

    /* nanoseconds */
    time = tod2time(time);

    timer_mod(env->tod_timer, env->tod_basetime + time);
}

/* Store Clock Comparator */
uint64_t HELPER(stckc)(CPUS390XState *env)
{
    return env->ckc;
}

/* Set CPU Timer */
void HELPER(spt)(CPUS390XState *env, uint64_t time)
{
    if (time == -1ULL) {
        return;
    }

    /* nanoseconds */
    time = tod2time(time);

    env->cputm = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + time;

    timer_mod(env->cpu_timer, env->cputm);
}

/* Store CPU Timer */
uint64_t HELPER(stpt)(CPUS390XState *env)
{
    return time2tod(env->cputm - qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL));
}

/* Store System Information */
uint32_t HELPER(stsi)(CPUS390XState *env, uint64_t a0,
                      uint64_t r0, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    int cc = 0;
    int sel1, sel2;

    if ((r0 & STSI_LEVEL_MASK) <= STSI_LEVEL_3 &&
        ((r0 & STSI_R0_RESERVED_MASK) || (r1 & STSI_R1_RESERVED_MASK))) {
        /* valid function code, invalid reserved bits */
        program_interrupt(env, PGM_SPECIFICATION, 4);
    }

    sel1 = r0 & STSI_R0_SEL1_MASK;
    sel2 = r1 & STSI_R1_SEL2_MASK;

    /* XXX: spec exception if sysib is not 4k-aligned */

    switch (r0 & STSI_LEVEL_MASK) {
    case STSI_LEVEL_1:
        if ((sel1 == 1) && (sel2 == 1)) {
            /* Basic Machine Configuration */
            struct sysib_111 sysib;
            char type[5] = {};

            memset(&sysib, 0, sizeof(sysib));
            ebcdic_put(sysib.manuf, "QEMU            ", 16);
            /* same as machine type number in STORE CPU ID, but in EBCDIC */
            snprintf(type, ARRAY_SIZE(type), "%X", cpu->model->def->type);
            ebcdic_put(sysib.type, type, 4);
            /* model number (not stored in STORE CPU ID for z/Architecure) */
            ebcdic_put(sysib.model, "QEMU            ", 16);
            ebcdic_put(sysib.sequence, "QEMU            ", 16);
            ebcdic_put(sysib.plant, "QEMU", 4);
            cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
        } else if ((sel1 == 2) && (sel2 == 1)) {
            /* Basic Machine CPU */
            struct sysib_121 sysib;

            memset(&sysib, 0, sizeof(sysib));
            /* XXX make different for different CPUs? */
            ebcdic_put(sysib.sequence, "QEMUQEMUQEMUQEMU", 16);
            ebcdic_put(sysib.plant, "QEMU", 4);
            stw_p(&sysib.cpu_addr, env->core_id);
            cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
        } else if ((sel1 == 2) && (sel2 == 2)) {
            /* Basic Machine CPUs */
            struct sysib_122 sysib;

            memset(&sysib, 0, sizeof(sysib));
            stl_p(&sysib.capability, 0x443afc29);
            /* XXX change when SMP comes */
            stw_p(&sysib.total_cpus, 1);
            stw_p(&sysib.active_cpus, 1);
            stw_p(&sysib.standby_cpus, 0);
            stw_p(&sysib.reserved_cpus, 0);
            cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
        } else {
            cc = 3;
        }
        break;
    case STSI_LEVEL_2:
        {
            if ((sel1 == 2) && (sel2 == 1)) {
                /* LPAR CPU */
                struct sysib_221 sysib;

                memset(&sysib, 0, sizeof(sysib));
                /* XXX make different for different CPUs? */
                ebcdic_put(sysib.sequence, "QEMUQEMUQEMUQEMU", 16);
                ebcdic_put(sysib.plant, "QEMU", 4);
                stw_p(&sysib.cpu_addr, env->core_id);
                stw_p(&sysib.cpu_id, 0);
                cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
            } else if ((sel1 == 2) && (sel2 == 2)) {
                /* LPAR CPUs */
                struct sysib_222 sysib;

                memset(&sysib, 0, sizeof(sysib));
                stw_p(&sysib.lpar_num, 0);
                sysib.lcpuc = 0;
                /* XXX change when SMP comes */
                stw_p(&sysib.total_cpus, 1);
                stw_p(&sysib.conf_cpus, 1);
                stw_p(&sysib.standby_cpus, 0);
                stw_p(&sysib.reserved_cpus, 0);
                ebcdic_put(sysib.name, "QEMU    ", 8);
                stl_p(&sysib.caf, 1000);
                stw_p(&sysib.dedicated_cpus, 0);
                stw_p(&sysib.shared_cpus, 0);
                cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
            } else {
                cc = 3;
            }
            break;
        }
    case STSI_LEVEL_3:
        {
            if ((sel1 == 2) && (sel2 == 2)) {
                /* VM CPUs */
                struct sysib_322 sysib;

                memset(&sysib, 0, sizeof(sysib));
                sysib.count = 1;
                /* XXX change when SMP comes */
                stw_p(&sysib.vm[0].total_cpus, 1);
                stw_p(&sysib.vm[0].conf_cpus, 1);
                stw_p(&sysib.vm[0].standby_cpus, 0);
                stw_p(&sysib.vm[0].reserved_cpus, 0);
                ebcdic_put(sysib.vm[0].name, "KVMguest", 8);
                stl_p(&sysib.vm[0].caf, 1000);
                ebcdic_put(sysib.vm[0].cpi, "KVM/Linux       ", 16);
                cpu_physical_memory_write(a0, &sysib, sizeof(sysib));
            } else {
                cc = 3;
            }
            break;
        }
    case STSI_LEVEL_CURRENT:
        env->regs[0] = STSI_LEVEL_3;
        break;
    default:
        cc = 3;
        break;
    }

    return cc;
}

uint32_t HELPER(sigp)(CPUS390XState *env, uint64_t order_code, uint32_t r1,
                      uint32_t r3)
{
    int cc;

    /* TODO: needed to inject interrupts  - push further down */
    qemu_mutex_lock_iothread();
    cc = handle_sigp(env, order_code & SIGP_ORDER_MASK, r1, r3);
    qemu_mutex_unlock_iothread();

    return cc;
}
#endif

#ifndef CONFIG_USER_ONLY
void HELPER(xsch)(CPUS390XState *env, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_xsch(cpu, r1);
    qemu_mutex_unlock_iothread();
}

void HELPER(csch)(CPUS390XState *env, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_csch(cpu, r1);
    qemu_mutex_unlock_iothread();
}

void HELPER(hsch)(CPUS390XState *env, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_hsch(cpu, r1);
    qemu_mutex_unlock_iothread();
}

void HELPER(msch)(CPUS390XState *env, uint64_t r1, uint64_t inst)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_msch(cpu, r1, inst >> 16);
    qemu_mutex_unlock_iothread();
}

void HELPER(rchp)(CPUS390XState *env, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_rchp(cpu, r1);
    qemu_mutex_unlock_iothread();
}

void HELPER(rsch)(CPUS390XState *env, uint64_t r1)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_rsch(cpu, r1);
    qemu_mutex_unlock_iothread();
}

void HELPER(ssch)(CPUS390XState *env, uint64_t r1, uint64_t inst)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_ssch(cpu, r1, inst >> 16);
    qemu_mutex_unlock_iothread();
}

void HELPER(stsch)(CPUS390XState *env, uint64_t r1, uint64_t inst)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_stsch(cpu, r1, inst >> 16);
    qemu_mutex_unlock_iothread();
}

void HELPER(tsch)(CPUS390XState *env, uint64_t r1, uint64_t inst)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_tsch(cpu, r1, inst >> 16);
    qemu_mutex_unlock_iothread();
}

void HELPER(chsc)(CPUS390XState *env, uint64_t inst)
{
    S390CPU *cpu = s390_env_get_cpu(env);
    qemu_mutex_lock_iothread();
    ioinst_handle_chsc(cpu, inst >> 16);
    qemu_mutex_unlock_iothread();
}
#endif

#ifndef CONFIG_USER_ONLY
void HELPER(per_check_exception)(CPUS390XState *env)
{
    uint32_t ilen;

    if (env->per_perc_atmid) {
        /*
         * FIXME: ILEN_AUTO is most probably the right thing to use. ilen
         * always has to match the instruction referenced in the PSW. E.g.
         * if a PER interrupt is triggered via EXECUTE, we have to use ilen
         * of EXECUTE, while per_address contains the target of EXECUTE.
         */
        ilen = get_ilen(cpu_ldub_code(env, env->per_address));
        program_interrupt(env, PGM_PER, ilen);
    }
}

/* Check if an address is within the PER starting address and the PER
   ending address.  The address range might loop.  */
static inline bool get_per_in_range(CPUS390XState *env, uint64_t addr)
{
    if (env->cregs[10] <= env->cregs[11]) {
        return env->cregs[10] <= addr && addr <= env->cregs[11];
    } else {
        return env->cregs[10] <= addr || addr <= env->cregs[11];
    }
}

void HELPER(per_branch)(CPUS390XState *env, uint64_t from, uint64_t to)
{
    if ((env->cregs[9] & PER_CR9_EVENT_BRANCH)) {
        if (!(env->cregs[9] & PER_CR9_CONTROL_BRANCH_ADDRESS)
            || get_per_in_range(env, to)) {
            env->per_address = from;
            env->per_perc_atmid = PER_CODE_EVENT_BRANCH | get_per_atmid(env);
        }
    }
}

void HELPER(per_ifetch)(CPUS390XState *env, uint64_t addr)
{
    if ((env->cregs[9] & PER_CR9_EVENT_IFETCH) && get_per_in_range(env, addr)) {
        env->per_address = addr;
        env->per_perc_atmid = PER_CODE_EVENT_IFETCH | get_per_atmid(env);

        /* If the instruction has to be nullified, trigger the
           exception immediately. */
        if (env->cregs[9] & PER_CR9_EVENT_NULLIFICATION) {
            CPUState *cs = CPU(s390_env_get_cpu(env));

            env->per_perc_atmid |= PER_CODE_EVENT_NULLIFICATION;
            env->int_pgm_code = PGM_PER;
            env->int_pgm_ilen = get_ilen(cpu_ldub_code(env, addr));

            cs->exception_index = EXCP_PGM;
            cpu_loop_exit(cs);
        }
    }
}
#endif

static uint8_t stfl_bytes[2048];
static unsigned int used_stfl_bytes;

static void prepare_stfl(void)
{
    static bool initialized;
    int i;

    /* racy, but we don't care, the same values are always written */
    if (initialized) {
        return;
    }

    s390_get_feat_block(S390_FEAT_TYPE_STFL, stfl_bytes);
    for (i = 0; i < sizeof(stfl_bytes); i++) {
        if (stfl_bytes[i]) {
            used_stfl_bytes = i + 1;
        }
    }
    initialized = true;
}

#ifndef CONFIG_USER_ONLY
void HELPER(stfl)(CPUS390XState *env)
{
    LowCore *lowcore;

    lowcore = cpu_map_lowcore(env);
    prepare_stfl();
    memcpy(&lowcore->stfl_fac_list, stfl_bytes, sizeof(lowcore->stfl_fac_list));
    cpu_unmap_lowcore(lowcore);
}
#endif

uint32_t HELPER(stfle)(CPUS390XState *env, uint64_t addr)
{
    const uintptr_t ra = GETPC();
    const int count_bytes = ((env->regs[0] & 0xff) + 1) * 8;
    const int max_bytes = ROUND_UP(used_stfl_bytes, 8);
    int i;

    if (addr & 0x7) {
        cpu_restore_state(ENV_GET_CPU(env), ra);
        program_interrupt(env, PGM_SPECIFICATION, 4);
    }

    prepare_stfl();
    for (i = 0; i < count_bytes; ++i) {
        cpu_stb_data_ra(env, addr + i, stfl_bytes[i], ra);
    }

    env->regs[0] = deposit64(env->regs[0], 0, 8, (max_bytes / 8) - 1);
    return count_bytes >= max_bytes ? 0 : 3;
}
