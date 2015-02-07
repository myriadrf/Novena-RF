////////////////////////////////////////////////////////////////////////
// Build kernel module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <linux/ioctl.h>
#include <linux/types.h>

//! The mmap offset used to specify the register space
#define NOVENA_RF_REGS_OFF 0

//! The size of the register space in bytes
#define NOVENA_RF_REGS_SIZE 256

//! Initialize the EIM configuration for communication
#define NOVENA_RF_EIM_INIT _IO('n', 3)
