////////////////////////////////////////////////////////////////////////
// Build kernel module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "novena_rf_module.h"
#include <linux/fs.h> //struct file

long novena_rf_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    if (cmd == NOVENA_RF_EIM_INIT) return novena_rf_eim_init();
    return 0;
}

int novena_rf_mmap(struct file *filp, struct vm_area_struct *vma)
{
    
}

int novena_rf_open(struct inode *inode, struct file *filp)
{
    //find the base of the data structure by seeing where cdev is stored
    novena_rf_module_t *module = container_of(inode->i_cdev, novena_rf_module_t, c_dev);

    //now store it to private data for other methods
    filp->private_data = module;

    return 0;
}

int novena_rf_release(struct inode *inode, struct file *filp)
{
    
}
