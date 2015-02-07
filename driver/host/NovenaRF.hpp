////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

/***********************************************************************
 * Configuration settings
 **********************************************************************/
#define NOVENA_RF_DEVFS "/dev/novena_rf"

#define FPGA_IMAGE_PATH "/lib/firmware/novena_rf.bit"

#define FPGA_RESET_GPIO 135
#define FPGA_LOAD_SPIDEV "/dev/spidev2.0"

/***********************************************************************
 * Memory mapped #defines
 **********************************************************************/
#define NOVENA_RF_REGS_PAGE_NO 0
#define NOVENA_RF_REGS_PAGE_SIZE 256

#define NOVENA_RF_TEST_PAGE_NO 1
#define NOVENA_RF_TEST_PAGE_SIZE 16

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

/***********************************************************************
 * Utility functions
 **********************************************************************/
void novenaRF_loadFpga(const std::string &fpgaImage);
