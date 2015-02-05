////////////////////////////////////////////////////////////////////////
// Build kernel module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#pragma once
#include <linux/cdev.h> //character device

#define MODULE_NAME "novena_rf"

//! IOCTL access for user to control allocations
long novena_rf_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

//! Map DMA and device registers into userspace
int novena_rf_mmap(struct file *filp, struct vm_area_struct *vma);

//! The user calls open on the device node
int novena_rf_open(struct inode *inode, struct file *filp);

//! The user calls close on the device node
int novena_rf_release(struct inode *inode, struct file *filp);
