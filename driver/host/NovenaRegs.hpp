////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

/***********************************************************************
 * Configuration settings
 **********************************************************************/
#define NOVENA_RF_DEVFS "/dev/novena_rf"

#define FPGA_IMAGE_PATH "/lib/firmware/novena_rf.bit"

#define FPGA_RESET_GPIO 135
#define FPGA_LOAD_SPIDEV "/dev/spidev2.0"
#define SPIDEV_MAXBUFF 32 //maximum number of bytes per transaction

#define LMS_CLOCK_RATE 30.72e6

//GPIO4_IO28 - DISP0_DAT7 - ECSPI3_MISO
#define FPGA_IRQ_GPIO 124

/***********************************************************************
 * FPGA register #defines -- from the VHDL
 **********************************************************************/
#define REG_SENTINEL_VALUE 0x5246
#define REG_VERSION_VALUE 0x0001
#define REG_SENTINEL_ADDR 0
#define REG_VERSION_ADDR 2
#define REG_RESET_ADDR 4
#define REG_LOOPBACK_ADDR 6
#define REG_LMS_GPIO_ADDR 8
#define REG_TIME_LO_ADDR 20
#define REG_TIME_ME_ADDR 22
#define REG_TIME_HI_ADDR 24
#define REG_TIME_EX_ADDR 26
#define REG_TIME_CTRL_ADDR 28

//--control registers: write to push into DMA control fifo
//--status registers: read to query value without removal,
//--and write to pop the value from the DMA status fifo.
#define REG_S2MM_FRAMER0_CTRL_ADDR 32
#define REG_S2MM_FRAMER0_STAT_ADDR 34
#define REG_MM2S_FRAMER0_CTRL_ADDR 36
#define REG_MM2S_FRAMER0_STAT_ADDR 38
#define REG_S2MM_DEFRAMER0_CTRL_ADDR 40
#define REG_S2MM_DEFRAMER0_STAT_ADDR 42
#define REG_MM2S_DEFRAMER0_CTRL_ADDR 44
#define REG_MM2S_DEFRAMER0_STAT_ADDR 46
//--read-only register to query the FIFO readiness
#define REG_DMA_FIFO_RDY_CTRL_ADDR 48

//--write-only registers to configure irq from stat valids
#define REG_DMA_SET_IRQ_MASK_ADDR 50
#define REG_DMA_CLR_IRQ_MASK_ADDR 52

//filter bypasses for configurable sample rate
#define REG_DECIM_FILTER_BYPASS 54
#define REG_INTERP_FILTER_BYPASS 56
#define REG_DECIM_CORDIC_PHASE_LO 58
#define REG_DECIM_CORDIC_PHASE_HI 60
#define REG_INTERP_CORDIC_PHASE_LO 62
#define REG_INTERP_CORDIC_PHASE_HI 64
#define REG_ENABLE_DC_REMOVAL 66
#define REG_LMS_TRX_LOOPBACK 70
#define REG_TX_IDLE_LEVEL_LO 72
#define REG_TX_IDLE_LEVEL_HI 74

#define NUM_FILTERS 5
#define TEST0_BRAM_NUM_ENTRIES 16
#define FRAMER0_FIFO_NUM_ENTRIES 1024*16
#define FRAMER0_S2MM_NUM_ENTRIES 4096
#define FRAMER0_MM2S_NUM_ENTRIES 64
#define DEFRAMER0_FIFO_NUM_ENTRIES 1024*16
#define DEFRAMER0_S2MM_NUM_ENTRIES 64
#define DEFRAMER0_MM2S_NUM_ENTRIES 4096

/***********************************************************************
 * Memory mapped #defines
 * The page numbers are defined in the FPGA by their mux ports
 * The number of frames is a user-defined partition of the BRAM
 **********************************************************************/
#define NOVENA_RF_REGS_PAGE_NO 0
#define NOVENA_RF_REGS_PAGE_SIZE 256

#define NOVENA_RF_TEST0_PAGE_NO 1
#define NOVENA_RF_TEST0_PAGE_SIZE TEST0_BRAM_NUM_ENTRIES*sizeof(uint16_t)

#define NOVENA_RF_FRAMER0_PAGE_NO 2
#define NOVENA_RF_FRAMER0_PAGE_SIZE FRAMER0_S2MM_NUM_ENTRIES*sizeof(uint32_t)
#define NOVENA_RF_FRAMER0_NUM_FRAMES 4

#define NOVENA_RF_DEFRAMER0_PAGE_NO 3
#define NOVENA_RF_DEFRAMER0_PAGE_SIZE DEFRAMER0_MM2S_NUM_ENTRIES*sizeof(uint32_t)
#define NOVENA_RF_DEFRAMER0_NUM_FRAMES 4
