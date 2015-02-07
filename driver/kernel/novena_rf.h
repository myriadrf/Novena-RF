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

//! Arbitrary shift used on offset to pass it into the mmap
#define NOVENA_RF_MAP_SHIFT 16

//! The mmap offset used to specify which address space
#define NOVENA_RF_MAP_OFFSET(page) ((page) << NOVENA_RF_MAP_SHIFT)

//! IOCTL constant used to form IOCTL numbers
#define NOVENA_RF_MAGIC 'n'

//! Initialize the EIM configuration for communication
#define NOVENA_RF_EIM_INIT _IO(NOVENA_RF_MAGIC, 1)
