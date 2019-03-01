/*
 * QEMU model of Arasan Nand Flash Controller
 *
 * Copyright (c) 2013 Xilinx Inc.
 * Copyright (c) 2013 Peter Crosthwaite <peter.crosthwaite@xilinx.com>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "qemu/timer.h"
#include "qemu/bitops.h"
#include "sysemu/sysemu.h"
#include "sysemu/dma.h"
#include "hw/hw.h"
#include "hw/register-dep.h"
#include "hw/sysbus.h"
#include "hw/block/flash.h"
#include "qapi/qmp/qerror.h"
#include "qemu/fifo.h"
#include "sysemu/blockdev.h"
#include "qemu/log.h"
#include "qapi/error.h"

#ifndef ARASAN_NFC_ERR_DEBUG
#define ARASAN_NFC_ERR_DEBUG 0
#endif

#define DB_PRINT_L(level, ...) do { \
    if (ARASAN_NFC_ERR_DEBUG > (level)) { \
        qemu_log_mask(DEV_LOG_NANDC, ": %s: ", __func__); \
        qemu_log_mask(DEV_LOG_NANDC, ## __VA_ARGS__); \
    } \
} while (0);

#define DB_PRINT(...) DB_PRINT_L(0, ## __VA_ARGS__)

#define TYPE_ARASAN_NFC "arasan.nfc"

#define ARASAN_NFC(obj) \
     OBJECT_CHECK(ArasanNFCState, (obj), TYPE_ARASAN_NFC)


/* The TRM has overly long names for everthing. The following substitutions
 * are mechanically (and unconditionally) made for the sake of 80 char sanity.
 * s/ADDR/ADDR
 * s/ENHANCED/ENH
 * s/INTERRUPT/INT
 * s/COMMAND/CMD
 * s/ENABLE/EN
 * s/BUFFER/BUF
 */

DEP_REG32(PACKET, 0x00)
    DEP_FIELD(PACKET, PACKET_SIZE, 11, 0)
    DEP_FIELD(PACKET, PACKET_COUNT, 12, 12)
    #define R_PACKET_RSVD 0xff000800

DEP_REG32(MEMORY_ADDR_1, 0x04)

DEP_REG32(MEMORY_ADDR_2, 0x08)
    DEP_FIELD(MEMORY_ADDR_2, MEMORY_ADDR, 8, 0)
    #define R_MEMORY_ADDR_2_BUS_WIDTH (1 << 24)
    DEP_FIELD(MEMORY_ADDR_2, NFC_BCH_MODE, 3, 25)
    DEP_FIELD(MEMORY_ADDR_2, MODE, 2, 28)
    DEP_FIELD(MEMORY_ADDR_2, CHIP_SELECT, 2, 30)
    #define R_MEMORY_ADDR_2_RSVD 0x00FFFF00

DEP_REG32(CMD, 0x0C)
    DEP_FIELD(CMD, CMD1, 8, 0)
    DEP_FIELD(CMD, CMD2, 8, 8)
    DEP_FIELD(CMD, PAGE_SIZE, 3, 23)
    DEP_FIELD(CMD, DMA_EN, 2, 26)
    /* deviated from TRM name as its overly long and typod */
    DEP_FIELD(CMD, NUM_ADDR_CYCLES, 3, 28)
    #define R_CMD_ECC_ON_OFF (1 << 31)
    #define R_CMD_RSVD 0x007F0000

static uint32_t arasan_nfc_page_size_lookup [] = {
    [0] = 512,
    [1] = 2 * 1024,
    [2] = 4 * 1024,
    [3] = 8 * 1024,
    [4] = 16 * 1024,
    /* dont support 16b flash just at the moment */
    [7] = 0
};

DEP_REG32(PGRAM, 0x10)
    #define R_PGRAM_READ (1 << 0)
    #define R_PGRAM_MULTI_DIE (1 << 1)
    #define R_PGRAM_BLOCK_ERASE (1 << 2)
    #define R_PGRAM_READ_STATUS (1 << 3)
    #define R_PGRAM_PAGE_PROGRAM (1 << 4)
    #define R_PGRAM_MUTLI_DIE_RD (1 << 5)
    #define R_PGRAM_READ_ID (1 << 6)
    #define R_PGRAM_READ_PARAMETER_PAGE (1 << 7)
    #define R_PGRAM_RESET (1 << 8)
    #define R_PGRAM_GET_FEATURES (1 << 9)
    #define R_PGRAM_SET_FEATURES (1 << 10)
    #define R_PGRAM_READ_UNIQUE_ID (1 << 11)
    #define R_PGRAM_READ_STATUS_ENH (1 << 12)
    #define R_PGRAM_READ_INTERLEAVED (1 << 13)
    #define R_PGRAM_CHANGE_READ_COLUMN_ENH (1 << 14)
    #define R_PGRAM_COPY_BACK_INTERLEAVED (1 << 15)
    #define R_PGRAM_READ_CACHE_START (1 << 16)
    #define R_PGRAM_READ_CACHE_SEQUENTIAL (1 << 17)
    #define R_PGRAM_READ_CACHE_RANDOM (1 << 18)
    #define R_PGRAM_READ_CACHE_END (1 << 19)
    #define R_PGRAM_SMALL_DATA_MOVE (1 << 20)
    #define R_PGRAM_CHANGE_ROW_ADDR (1 << 21)
    #define R_PGRAM_CHANGE_ROW_ADDR_END (1 << 22)
    #define R_PGRAM_RESET_LUN (1 << 23)
    #define R_PGRAM_PGM_PG_REG32_CLR (1 << 24)
    #define R_PGRAM_VOLUME_SELECT (1 << 25)
    #define R_PGRAM_ODT_CONFIGURE (1 << 26)
    #define R_PGRAM_RSVD (0x1f << 27)
    
DEP_REG32(INT_STATUS_EN, 0x14)
DEP_REG32(INT_SIGNAL_EN, 0x18)
DEP_REG32(INT_STATUS, 0x1C)
    /* dropped the redundant STS_EN, DEP_REG32 and SIG_EN suffixes from TRM names */
    #define R_INT_BUFF_WR_RDY (1 << 0)
    #define R_INT_BUFF_RD_RDY (1 << 1)
    #define R_INT_TRANS_COMP (1 << 2)
    #define R_INT_MUL_BIT_ERR (1 << 3)
    #define R_INT_ERR_INTRPT (1 << 4)
    #define R_INT_DMA_INT (1 << 6)
    #define R_INT_ERROR_AHB (1 << 7)
    #define R_INT_RSVD 0xFFFFFF00
    #define R_INT_ANY (~(R_INT_RSVD))

DEP_REG32(FLASH_STATUS, 0x28)
    DEP_FIELD(FLASH_STATUS, FLASH_STATUS, 16, 0)
    #define R_FLASH_STATUS_RSVD 0xffff0000

DEP_REG32(TIMING, 0x2C)
    DEP_FIELD(TIMING, TCCS_TIME, 2, 0)
    #define R_TIMING_SLOW_FAST_TCAD (1 << 2)
    DEP_FIELD(TIMING, DQS_BUFF_SEL, 4, 3)
    DEP_FIELD(TIMING, TADL_TIME, 7, 7)

DEP_REG32(BUF_DATA_PORT, 0x30)

DEP_REG32(ECC, 0x34)
    DEP_FIELD(ECC, ECC_ADDR, 16, 0)
    DEP_FIELD(ECC, ECC_SIZE, 11, 16)
    #define R_ECC_SLC_MLC (1 << 25)
    #define R_ECC_RSVD 0xfe000000

DEP_REG32(ECC_ERR_COUNT, 0x38)
    DEP_FIELD(ECC_ERR_COUNT, PACKET_BOUND, 8, 0)
    DEP_FIELD(ECC_ERR_COUNT, PAGE_BOUND, 8, 8)
    #define R_ECC_ERR_COUNT_RSVD 0xFFFF0000

DEP_REG32(ECC_SPARE_CMD, 0x3C)
    DEP_FIELD(ECC_SPARE_CMD, CMD1, 8, 0)
    DEP_FIELD(ECC_SPARE_CMD, CMD2, 8, 8)
    DEP_FIELD(ECC_SPARE_CMD, NUM_ADDR_CYCLES, 3, 28)
    #define R_ECC_SPARE_CMD_RSVD 0x8FFF0000

/* FIXME Finish this */
#define R_ERR_COUNT_1BIT (0x40/4)
#define R_ERR_COUNT_2BIT (0x44/4)
#define R_ERR_COUNT_3BIT (0x48/4)
#define R_ERR_COUNT_4BIT (0x4C/4)
#define R_CPU_RELEASE (0x58/4)
#define R_ERR_COUNT_5BIT (0x5C/4)
#define R_ERR_COUNT_6BIT (0x60/4)
#define R_ERR_COUNT_7BIT (0x64/4)
#define R_ERR_COUNT_8BIT (0x68/4)

DEP_REG32(DMA_SYSTEM_ADDR1, 0x24)
DEP_REG32(DMA_SYSTEM_ADDR0, 0x50)

DEP_REG32(DMA_BUF_BOUNDARY, 0x54)
    #define R_DMA_BUF_BOUNDARY_RSVD (ONES(29) << 3)

DEP_REG32(DATA_INTERFACE,   0x6C)
    DEP_FIELD(DATA_INTERFACE, SDR, 3, 0)
    DEP_FIELD(DATA_INTERFACE, NV_DDR, 3, 3)
    DEP_FIELD(DATA_INTERFACE, NV_DDR2, 3, 6)
    DEP_FIELD(DATA_INTERFACE, DATA_INTF, 2, 9)
    #define R_DATA_INTERFACE_RSVD 0xFFFFF800

#define R_MAX (R_DATA_INTERFACE+1)

/* The codeword size does vary in real hw between 512 and 1024 depding
 * on mode. But since we do not actually model a genuine ECC algorithm,
 * The actual ECC contents are undefined outside the context of QEMU.
 * Therefore it's valid to implement 1024B codeword as 2x512 without
 * consequence. Simplify by fixing the codeword at 512.
 */

#define ECC_CODEWORD_SIZE 512

typedef struct ArasanNFCState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    MemoryRegion *dma_mr;
    AddressSpace *dma_as;
    qemu_irq irq;

    DeviceState *nand[2];
    DeviceState *current;

    /* FIXME: Use a saner size */
    uint8_t ecc_digest[128 * 1024];
    uint8_t ecc_oob[128 * 1024];
    uint32_t ecc_pos, ecc_subpage_offset;

    bool has_mdma;
    bool boot_en;
    uint8_t num_cs;

    uint64_t dma_sar;
    bool dbb_blocked;
    Fifo buffer;

    uint32_t regs[R_MAX];
    DepRegisterInfo regs_info[R_MAX];

} ArasanNFCState;

static inline void arasan_nfc_irq_event(ArasanNFCState *s, uint32_t ev)
{
    DB_PRINT("IRQ event %" PRIx32 " happened\n", ev);
    s->regs[R_INT_STATUS] |= ev & s->regs[R_INT_STATUS_EN];
}

static inline bool arasan_nfc_ecc_enabled(ArasanNFCState *s)
{
    return s->regs[R_CMD] & R_CMD_ECC_ON_OFF;
}

static void arasan_nfc_ecc_init(ArasanNFCState *s)
{
    /* FIXME: Bad performance */
    memset(s->ecc_digest, 0xFF, 16 * 1024);
    s->ecc_pos = 0;
    s->ecc_subpage_offset = 0;
}

/* not an ECC algorithm, but gives a deterministic OOB that
 * depends on the in band data
 */

static void arasan_nfc_ecc_digest(ArasanNFCState *s, uint8_t data)
{
    uint32_t page_size = arasan_nfc_page_size_lookup[DEP_AF_EX32(s->regs, CMD,
                                                             PAGE_SIZE)];
    int ecc_bytes_per_subpage = DEP_AF_EX32(s->regs, ECC, ECC_SIZE) /
                                (page_size / ECC_CODEWORD_SIZE);

    s->ecc_digest[s->ecc_pos++] ^= ~data;
    if (!(s->ecc_pos % ecc_bytes_per_subpage)) {
        s->ecc_pos -= ecc_bytes_per_subpage;
    }

    s->ecc_subpage_offset++;
    if (s->ecc_subpage_offset == ECC_CODEWORD_SIZE) {
        s->ecc_subpage_offset = 0;
        do {
            s->ecc_pos++;
        } while (s->ecc_pos % ecc_bytes_per_subpage);
    }
}

static bool arasan_nfc_ecc_correct(ArasanNFCState *s)
{
    int i;
    uint8_t cef = 0;

    for (i = 0; i < DEP_AF_EX32(s->regs, ECC, ECC_SIZE); ++i) {
        if (s->ecc_oob[i] != s->ecc_digest[i]) {
            arasan_nfc_irq_event(s, R_INT_MUL_BIT_ERR);
            if (DEP_AF_EX32(s->regs, ECC_ERR_COUNT, PAGE_BOUND) != 0xFF) {
                s->regs[R_ECC_ERR_COUNT] +=
                    1 << R_ECC_ERR_COUNT_PAGE_BOUND_SHIFT;
            }
            /* FIXME: All errors in the first packet - not right */
            if (DEP_AF_EX32(s->regs, ECC_ERR_COUNT, PACKET_BOUND) != 0xFF) {
                s->regs[R_ECC_ERR_COUNT] +=
                    1 << R_ECC_ERR_COUNT_PACKET_BOUND_SHIFT;
            }
            DB_PRINT("ECC check failed on ECC byte %#x, %#02" PRIx8 " != %#02"
                     PRIx8 "\n", i, s->ecc_oob[i], s->ecc_digest[i]);
            return true;
        } else {
            cef ^= s->ecc_oob[i];
        }
    }
    /* Fake random successful single bit corrections for hamming */
    for (i = 0; i < 7; ++i) {
        cef = (cef >> 1) ^ (cef & 0x1);
    }
    if ((cef & 0x1) && ((s->regs[R_ECC] & R_ECC_SLC_MLC))) {
        arasan_nfc_irq_event(s, R_INT_ERR_INTRPT);
    }
    DB_PRINT("ECC check passed");
    return false;
}

static void arasan_nfc_do_cmd2(ArasanNFCState *s, bool ecc)
{
    uint8_t cmd;

    nand_setpins(s->current, 1, 0, 0, 1, 0); /* CMD */
    cmd = ecc ? DEP_AF_EX32(s->regs, ECC_SPARE_CMD, CMD2) :
                DEP_AF_EX32(s->regs, CMD, CMD2);
    nand_setio(s->current, cmd);
    DB_PRINT("send second command cycle %#02" PRIx8 "\n", cmd);
}

static void arasan_nfc_do_cmd(ArasanNFCState *s, uint8_t addr_cycles, bool ecc,
                              bool force_addr_cycles)
{
    int i;
    uint8_t num_cycles;
    uint8_t cmd;

    nand_setpins(s->current, 1, 0, 0, 1, 0); /* CMD */
    cmd = ecc ? DEP_AF_EX32(s->regs, ECC_SPARE_CMD, CMD1) :
                DEP_AF_EX32(s->regs, CMD, CMD1);
    nand_setio(s->current, cmd);
    DB_PRINT("send command cycle %#02" PRIx8 "\n", cmd);

    num_cycles = ecc ? DEP_AF_EX32(s->regs, ECC_SPARE_CMD, NUM_ADDR_CYCLES) :
                       DEP_AF_EX32(s->regs, CMD, NUM_ADDR_CYCLES);
    if (force_addr_cycles) {
        num_cycles = addr_cycles;
    } else if (num_cycles != addr_cycles) {
        qemu_log_mask(LOG_GUEST_ERROR, "Mismatched between given (%d) and "
                      "expected(%d) address cycles\n", num_cycles, addr_cycles);
    }

    for (i = 0; i < num_cycles; ++i) {
        uint8_t data;
        if (i < 4) {
            data = s->regs[ecc ? R_ECC : R_MEMORY_ADDR_1] >> (i * 8);
        } else if (i == 4) {
            data = s->regs[R_MEMORY_ADDR_2];
        } else {
            qemu_log_mask(LOG_GUEST_ERROR, "BAD number of NAND addr cycles\n");
            break;
        }
        nand_setpins(s->current, 0, 1, 0, 1, 0); /* address */
        nand_setio(s->current, data);
        DB_PRINT("send addr cycle %#02" PRIx8 "\n", data);
    }
}

static inline void arasan_nfc_sync_dma_addr(ArasanNFCState *s)
{
    s->dma_sar = ((uint64_t)s->regs[R_DMA_SYSTEM_ADDR1] << 32) +
                 s->regs[R_DMA_SYSTEM_ADDR0];
}

static inline void arasan_nfc_do_dma(ArasanNFCState *s, bool rnw)
{
    DMADirection dir = rnw ? DMA_DIRECTION_FROM_DEVICE :
                             DMA_DIRECTION_TO_DEVICE;
    int debug_squelch = 5;

    /* FIXME: Be less dumb */
    while (DEP_AF_EX32(s->regs, CMD, DMA_EN) == 0x2 &&
           !(rnw ? fifo_is_empty : fifo_is_full)(&s->buffer) &&
           !s->dbb_blocked) {
        uint32_t dbb_mask = MAKE_64BIT_MASK(0,
                                            s->regs[R_DMA_BUF_BOUNDARY] + 12);
        uint8_t tmp;

        if (rnw) {
            tmp = fifo_pop8(&s->buffer);
        }

        dma_memory_rw(s->dma_as, s->dma_sar, &tmp, 1, dir);

        if (debug_squelch) {
            DB_PRINT("Doing dma %s with addr %08" PRIx64 " = %02" PRIx8 "\n",
                     rnw ? "read" : "write", s->dma_sar, tmp);
            debug_squelch--;
        }

        if (!rnw) {
            fifo_push8(&s->buffer, tmp);
        }

        if ((s->regs[R_DMA_BUF_BOUNDARY] & 1 << 3) &&
            (s->dma_sar & dbb_mask) == dbb_mask) {
            s->dbb_blocked = true;
	        arasan_nfc_irq_event(s, R_INT_DMA_INT);
        }
        s->dma_sar++;
    }
}

static inline bool arasan_nfc_write_check_ecc(ArasanNFCState *s)
{
  return (s->regs[R_PGRAM] & R_PGRAM_PAGE_PROGRAM) &&
         arasan_nfc_ecc_enabled(s);
}

static uint32_t arasan_nfc_get_packet_size(ArasanNFCState *s, uint32_t pgram) {
    uint32_t packet_size = DEP_AF_EX32(s->regs, PACKET, PACKET_SIZE);

        switch (pgram) {
        case R_PGRAM_SET_FEATURES:
        case R_PGRAM_GET_FEATURES:
        case R_PGRAM_READ_ID:
        case R_PGRAM_READ_STATUS_ENH:
        case R_PGRAM_READ_STATUS:
        if (DEP_AF_EX32(s->regs, DATA_INTERFACE, DATA_INTF)) {
            DB_PRINT("Halving payload size for DDR command\n");
            packet_size /= 2;
        }
    }
    return packet_size;
}

static void arasan_nfc_set_current(ArasanNFCState *s)
{
    int cs_dev = DEP_AF_EX32(s->regs, MEMORY_ADDR_2, CHIP_SELECT);

    /* Lazy-init nand if its not initialised at realize,
     * i.e no pflash arg at command line */
    if (!s->nand[cs_dev]) {
        s->nand[cs_dev] = nand_init(NULL, NAND_MFR_MICRON, 0x44);
    }
    s->current = s->nand[cs_dev];
}

static inline void arasan_nfc_update_state(ArasanNFCState *s)
{
    int i;
    uint32_t packet_size;

    switch (s->regs[R_PGRAM]) {
    case R_PGRAM_READ:
        arasan_nfc_do_dma(s, true);
    case R_PGRAM_GET_FEATURES:
    case R_PGRAM_READ_PARAMETER_PAGE:
    case R_PGRAM_READ_ID:
		if (fifo_is_empty(&s->buffer)) {
		    DB_PRINT("read completed\n");
		    arasan_nfc_irq_event(s, R_INT_TRANS_COMP);
		    s->regs[R_PGRAM] = 0;
		}
        break;
    case R_PGRAM_READ_STATUS:
    case R_PGRAM_READ_STATUS_ENH:
		if (!fifo_is_empty(&s->buffer)) {
            DEP_AF_DP32(s->regs, FLASH_STATUS, FLASH_STATUS, fifo_pop8(&s->buffer));
		    DB_PRINT("read completed\n");
		    arasan_nfc_irq_event(s, R_INT_TRANS_COMP);
		    s->regs[R_PGRAM] = 0;
        }
	}

	if (s->regs[R_PGRAM] & R_PGRAM_PAGE_PROGRAM) {
        arasan_nfc_do_dma(s, false);
    }
	if ((s->regs[R_PGRAM] & R_PGRAM_PAGE_PROGRAM) ||
        (s->regs[R_PGRAM] & R_PGRAM_SET_FEATURES)) {
                arasan_nfc_set_current(s);
		if (fifo_is_full(&s->buffer)) {
			DB_PRINT("write completed\n");
		    arasan_nfc_irq_event(s, R_INT_TRANS_COMP);
		    /* We are slow - do everything at the end */
        	nand_setpins(s->current, 0, 0, 0, 1, 0); /* data */
            if (arasan_nfc_write_check_ecc(s)) {
                arasan_nfc_ecc_init(s);
            }
		    while (!fifo_is_empty(&s->buffer)) {
		    	uint8_t to_write = fifo_pop8(&s->buffer);
                if (arasan_nfc_write_check_ecc(s)) {
                    arasan_nfc_ecc_digest(s, to_write);
                }
		    	nand_setio(s->current, to_write);
				DB_PRINT("write byte %#02" PRIx8 "\n", to_write);
		    }
            if (arasan_nfc_write_check_ecc(s)) {
                arasan_nfc_do_cmd(s, 2, true, false);
                nand_setpins(s->current, 0, 0, 0, 1, 0); /* data */
                for (i = 0; i < DEP_AF_EX32(s->regs, ECC, ECC_SIZE); ++i) {
                    nand_setio(s->current, s->ecc_digest[i]);
                    DB_PRINT("write ecc byte %#02" PRIx8 "\n", s->ecc_digest[i]);
                }
            }
            if (s->regs[R_PGRAM] & R_PGRAM_PAGE_PROGRAM) {
                arasan_nfc_do_cmd2(s, false);
            }
		    s->regs[R_PGRAM] = 0;
    	}
	}

    packet_size = arasan_nfc_get_packet_size(s, s->regs[R_PGRAM]);
    s->regs[R_INT_STATUS] &= ~(R_INT_BUFF_RD_RDY | R_INT_BUFF_WR_RDY);
    s->regs[R_INT_STATUS] |= s->regs[R_INT_STATUS_EN] & (
            (s->buffer.num <= s->buffer.capacity - packet_size ?
                              R_INT_BUFF_WR_RDY : 0) |
            (s->buffer.num >= packet_size && packet_size ?
                              R_INT_BUFF_RD_RDY : 0));

    qemu_set_irq(s->irq, !!(s->regs[R_INT_SIGNAL_EN] &
                            s->regs[R_INT_STATUS]));

}

static void arasan_nfc_update_state_pw(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);

    arasan_nfc_update_state(s);
}

static void arasan_nfc_reset(DeviceState *dev) {
    ArasanNFCState *s = ARASAN_NFC(dev);

    /* Reset the registers */
    arasan_nfc_update_state(s);
}    

static void arasan_nfc_r_unimp_post_write(DepRegisterInfo *reg, uint64_t val)
{
	fprintf(stderr, "unimplemented functionality touched\n");
}

static uint64_t arasan_nfc_r_buffer_data_port_pr(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);
    int i;
    uint8_t buf[4];

    memset(buf, 0, 4);

    for (i = 0; i < 4 && !fifo_is_empty(&s->buffer); ++i) {
        buf[i] = fifo_pop8(&s->buffer);
    }

    arasan_nfc_update_state(s);
    return cpu_to_le32(*((uint32_t *)buf));
}

static void arasan_nfc_r_buffer_data_port_pw(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);
    int i;
    uint8_t buf[4];

    if (!(s->regs[R_PGRAM] & R_PGRAM_PAGE_PROGRAM) &&
        !(s->regs[R_PGRAM] & R_PGRAM_SET_FEATURES)) {
        /* FIXME: Prettyify */
        qemu_log_mask(LOG_GUEST_ERROR, "Write to buffer data port with no data");
        return;
    }

    *((uint32_t *)buf) = le32_to_cpu((uint32_t)val);
    for (i = 0; i < 4; ++i) {
    	fifo_push8(&s->buffer, buf[i]);
    }

	arasan_nfc_update_state(s);
}

static void arasan_nfc_r_dma_system_addr1_pw(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);

    arasan_nfc_sync_dma_addr(s);
}

static void arasan_nfc_r_dma_system_addr_pw(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);

    arasan_nfc_sync_dma_addr(s);
    s->dbb_blocked = false;
	arasan_nfc_update_state(s);
}

static uint64_t r_program_pre_write(DepRegisterInfo *reg, uint64_t val)
{
    ArasanNFCState *s = ARASAN_NFC(reg->opaque);
    int i, j;

    DB_PRINT("val = %#08" PRIx32 "\n", (uint32_t)val);

    if (val && s->regs[R_PGRAM]) {
        qemu_log_mask(LOG_GUEST_ERROR, "%s:CMD already in progress", reg->prefix);
        return 0;
    }

    arasan_nfc_set_current(s);
    for (i = 0; i < 32; ++i) {
        uint32_t pgram = val & (1 << i);
        uint32_t payload_size = arasan_nfc_get_packet_size(s, pgram) *
                                DEP_AF_EX32(s->regs, PACKET, PACKET_COUNT);

        switch (pgram) {
            case R_PGRAM_READ_STATUS_ENH:
            case R_PGRAM_READ_STATUS:
            case R_PGRAM_PAGE_PROGRAM:
            case R_PGRAM_READ_ID:
            case R_PGRAM_SET_FEATURES:
            case R_PGRAM_GET_FEATURES:
            case R_PGRAM_READ_PARAMETER_PAGE:
            case R_PGRAM_READ:
	            fifo_destroy(&s->buffer);
	            fifo_create8(&s->buffer, payload_size);
        }

        switch (pgram) {
        case R_PGRAM_RESET:
            arasan_nfc_do_cmd(s, 0, false, false);
	        val &= ~R_PGRAM_RESET;
		    arasan_nfc_irq_event(s, R_INT_TRANS_COMP);
	        break;
        case R_PGRAM_READ_ID:
	        arasan_nfc_do_cmd(s, 1, false, false);
            break;
        case R_PGRAM_BLOCK_ERASE:
            arasan_nfc_do_cmd(s, 3, false, false);
            arasan_nfc_do_cmd2(s, false);
	        val &= ~R_PGRAM_BLOCK_ERASE;
		    arasan_nfc_irq_event(s, R_INT_TRANS_COMP);
            break;
        case R_PGRAM_READ_STATUS:
            arasan_nfc_do_cmd(s, 0, false, true);
            break;
        case R_PGRAM_READ_STATUS_ENH:
            arasan_nfc_do_cmd(s, 3, false, true);
            break;
        case R_PGRAM_SET_FEATURES:
        case R_PGRAM_GET_FEATURES:
        case R_PGRAM_READ_PARAMETER_PAGE:
            arasan_nfc_do_cmd(s, 1, false, true);
	    break;
        case R_PGRAM_READ:
            arasan_nfc_do_cmd(s, 5, false, false);
            arasan_nfc_do_cmd2(s, false);
	    break;
        case R_PGRAM_PAGE_PROGRAM:
            arasan_nfc_do_cmd(s, 5, false, true);
            break;
        case 0:
            continue;
        default:
	    arasan_nfc_r_unimp_post_write(reg, val);
            qemu_log_mask(LOG_UNIMP, "%s:Unimplemented CMD %" PRIx32, reg->prefix, pgram);
        }

        /* we are fast! Do reads now now now!! */
        switch (pgram) {
        case R_PGRAM_READ_STATUS:
        case R_PGRAM_READ_STATUS_ENH:
        case R_PGRAM_READ_ID:
        case R_PGRAM_GET_FEATURES:
        case R_PGRAM_READ_PARAMETER_PAGE:
        	nand_setpins(s->current, 0, 0, 0, 1, 0); /* data */
            for (j = 0; j < payload_size; ++j) {
            	uint8_t to_read = nand_getio(s->current);
                fifo_push8(&s->buffer, to_read);
                DB_PRINT("read byte %#02" PRIx8 "\n", to_read);
            }
            break;
        case R_PGRAM_READ:
            if (arasan_nfc_ecc_enabled(s)) {
                s->regs[R_ECC_ERR_COUNT] = 0;
                arasan_nfc_ecc_init(s);
            }
            nand_setpins(s->current, 0, 0, 0, 1, 0); /* data */
            for (j = 0; j < payload_size; ++j) {
                uint8_t to_read = nand_getio(s->current);
                if (arasan_nfc_ecc_enabled(s)) {
                    arasan_nfc_ecc_digest(s, to_read);
                }
                fifo_push8(&s->buffer, to_read);
                DB_PRINT("read byte %#02" PRIx8 "\n", to_read);
            }
            /* FIXME: ECC is done backwards for reads, reading the payload
             * first, then the ECC data late. Real HW is the other way round.
             */
            if (arasan_nfc_ecc_enabled(s)) {
                arasan_nfc_do_cmd(s, 2, true, false);
                arasan_nfc_do_cmd2(s, true);
                for (j = 0; j < DEP_AF_EX32(s->regs, ECC, ECC_SIZE); ++j) {
                    s->ecc_oob[j] = nand_getio(s->current);
                    DB_PRINT("read ecc %#02" PRIx8 "\n", s->ecc_oob[j]);
                }
                arasan_nfc_ecc_correct(s);
            }
        }
    }

    return val;
}

static const MemoryRegionOps arasan_nfc_ops = {
    .read = dep_register_read_memory_le,
    .write = dep_register_write_memory_le,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4
    }
};

static const DepRegisterAccessInfo arasan_nfc_regs_info[] = {
    {   .name = "Packet",                   .decode.addr = A_PACKET,
            .rsvd = R_PACKET_RSVD,
            .reset = 0x200 << R_PACKET_PACKET_SIZE_SHIFT,
    },{ .name = "Memory Address 1",         .decode.addr = A_MEMORY_ADDR_1,
    },{ .name = "Memory Address 2",         .decode.addr = A_MEMORY_ADDR_2,
            .rsvd = R_MEMORY_ADDR_2_RSVD,
            .post_write = arasan_nfc_update_state_pw,
    },{ .name = "CMD",                      .decode.addr = A_CMD,
            .rsvd = R_CMD_RSVD,
            .reset = 0x2 << R_CMD_PAGE_SIZE_SHIFT,
    },{ .name = "Program",                  .decode.addr = A_PGRAM,
            .rsvd = R_PGRAM_RSVD,
            .pre_write = r_program_pre_write,
            .post_write = arasan_nfc_update_state_pw,
    },{ .name = "Interrupt Status Enable",  .decode.addr = A_INT_STATUS_EN,
            .rsvd = R_INT_RSVD,
            .post_write = arasan_nfc_update_state_pw,
    },{ .name = "Interrupt Signal Enable",  .decode.addr = A_INT_SIGNAL_EN,
            .rsvd = R_INT_RSVD,
            .post_write = arasan_nfc_update_state_pw,
    },{ .name = "Interrupt Status",         .decode.addr = A_INT_STATUS,
            .rsvd = R_INT_RSVD,
            .w1c = R_INT_ANY,
            .post_write = arasan_nfc_update_state_pw,
    },{ .name = "Flash Status",             .decode.addr = A_FLASH_STATUS,
            .ro = ~0,
    },{ .name = "Timing",                   .decode.addr = A_TIMING,
            .reset = 0x6 << R_TIMING_DQS_BUFF_SEL_SHIFT,
    },{ .name = "Buffer Data Port",         .decode.addr = A_BUF_DATA_PORT,
            .post_write = arasan_nfc_r_buffer_data_port_pw,
            .post_read = arasan_nfc_r_buffer_data_port_pr,
    },{ .name = "ECC",                      .decode.addr = A_ECC,
        .rsvd = R_ECC_RSVD,
    },{ .name = "ECC Error Count",          .decode.addr = A_ECC_ERR_COUNT,
        .rsvd = R_ECC_ERR_COUNT_RSVD,
    },{ .name = "ECC Spare Command",        .decode.addr = A_ECC_SPARE_CMD,
        .rsvd = R_ECC_SPARE_CMD_RSVD,
    },{ .name = "DMA System Addr High",     .decode.addr = A_DMA_SYSTEM_ADDR1,
            .post_write = arasan_nfc_r_dma_system_addr1_pw,
    },{ .name = "DMA System Addr Low",      .decode.addr = A_DMA_SYSTEM_ADDR0,
            .post_write = arasan_nfc_r_dma_system_addr_pw,
    },{ .name = "DMA Buffer Boundary",      .decode.addr = A_DMA_BUF_BOUNDARY,
            .rsvd = R_DMA_BUF_BOUNDARY_RSVD,
    },{ .name = "Data Interface",           .decode.addr = A_DATA_INTERFACE,
            .rsvd = R_DATA_INTERFACE_RSVD,
    },
};

static void arasan_nfc_realize(DeviceState *dev, Error ** errp)
{
    ArasanNFCState *s = ARASAN_NFC(dev);
    const char *prefix = object_get_canonical_path(OBJECT(dev));
    DriveInfo *dinfo;
    int i;

    /* FIXME: add support for multiple chips */
    dinfo = drive_get_next(IF_PFLASH);
    if (dinfo) {
        s->nand[0] = nand_init(dinfo ? blk_by_legacy_dinfo(dinfo) : NULL,
                               NAND_MFR_MICRON, 0x44);
    }
    dinfo = drive_get_next(IF_PFLASH);
    if (dinfo) {
        s->nand[1] = nand_init(dinfo ? blk_by_legacy_dinfo(dinfo) : NULL,
                               NAND_MFR_MICRON, 0x44);
    }
    for (i = 0; i < ARRAY_SIZE(arasan_nfc_regs_info); ++i) {
        DepRegisterInfo *r = &s->regs_info[i];

        *r = (DepRegisterInfo) {
            .data = &s->regs[arasan_nfc_regs_info[i].decode.addr/4],
            .data_size = sizeof(uint32_t),
            .access = &arasan_nfc_regs_info[i],
            .debug = qemu_loglevel_mask(DEV_LOG_NANDC),
            .prefix = prefix,
            .opaque = s,
        };
        memory_region_init_io(&r->mem, OBJECT(dev), &arasan_nfc_ops, r,
                              r->access->name, 4);
        memory_region_add_subregion(&s->iomem, r->access->decode.addr, &r->mem);
    }

    fifo_create8(&s->buffer, 1);

    if (s->dma_mr) {
        s->dma_as = g_malloc0(sizeof(AddressSpace));
        address_space_init(s->dma_as, s->dma_mr, NULL);
    } else {
        s->dma_as = &address_space_memory;
    }
}

static void arasan_nfc_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    ArasanNFCState *s = ARASAN_NFC(obj);

    object_property_add_link(obj, "nand0", TYPE_DEVICE,
                             (Object **)&s->nand[0],
                             object_property_allow_set_link,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
    object_property_add_link(obj, "nand1", TYPE_DEVICE,
                             (Object **)&s->nand[1],
                             object_property_allow_set_link,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);

    sysbus_init_irq(sbd, &s->irq);

    memory_region_init(&s->iomem, obj, "nand", R_MAX*4);
    sysbus_init_mmio(sbd, &s->iomem);

    object_property_add_link(obj, "dma", TYPE_MEMORY_REGION,
                             (Object **)&s->dma_mr,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_UNREF_ON_RELEASE,
                             &error_abort);
}

static Property arasan_nfc_properties[] = {
    DEFINE_PROP_UINT8("num-cs", ArasanNFCState, num_cs, 2),
    DEFINE_PROP_BOOL("has-mdma", ArasanNFCState, has_mdma, true),
    DEFINE_PROP_BOOL("boot-en", ArasanNFCState, boot_en, false),
    DEFINE_PROP_END_OF_LIST(),
};

static const VMStateDescription vmstate_arasan_nfc = {
    .name = TYPE_ARASAN_NFC,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_END_OF_LIST()
    }
};

static void arasan_nfc_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = arasan_nfc_reset;
    dc->realize = arasan_nfc_realize;
    dc->props = arasan_nfc_properties;
    dc->vmsd = &vmstate_arasan_nfc;
}

static TypeInfo arasan_nfc_info = {
    .name           = TYPE_ARASAN_NFC,
    .parent         = TYPE_SYS_BUS_DEVICE,
    .instance_size  = sizeof(ArasanNFCState),
    .class_init     = arasan_nfc_class_init,
    .instance_init  = arasan_nfc_init,
};

static void arasan_nfc_register_types(void)
{
    type_register_static(&arasan_nfc_info);
}

type_init(arasan_nfc_register_types)
