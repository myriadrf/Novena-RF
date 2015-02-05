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

#define FPGA_PATH_SUFFIX "/share/SoapySDR/novena_rf.bit"

#define FPGA_RESET_GPIO 135
#define FPGA_LOAD_SPIDEV "/dev/spidev2.0"

/***********************************************************************
 * Utility functions
 **********************************************************************/
void novenaRF_loadFpga(const std::string &fpgaImage);
