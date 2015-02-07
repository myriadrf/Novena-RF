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
#include <linux/mm.h> //mmap

long novena_rf_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    novena_rf_module_t *module = (novena_rf_module_t *)filp->private_data;
    if (cmd == NOVENA_RF_EIM_INIT) return novena_rf_eim_init(module);
    return -ENOTTY;
}

int novena_rf_mmap(struct file *filp, struct vm_area_struct *vma)
{
    //require that the EIM registers are configured before mapping
    novena_rf_module_t *module = (novena_rf_module_t *)filp->private_data;
    if (module->eim_configured == 0) return -EACCES;
    if (module->eim_memory == 0) return -EACCES;

    //offset is a user argument, convert it to an eim location
    const size_t offset = vma->vm_pgoff << PAGE_SHIFT;

    //extract the page argument using the shift constant
    const size_t eim_page = offset >> NOVENA_RF_MAP_SHIFT;
    if (eim_page > 7) return -EACCES;

    //calculate the actual offset in bytes to the bits 18:16
    const size_t eim_off = (eim_page & 0x7) << 16;

    //calculate the actual physical start address
    const size_t eim_phs = (module->eim_memory + eim_off);

    //since we mux on bits 18:16, the max size is 1 << 16
    #define MAX_EIM_MMAP_SIZE (1 << 16)
    size_t size = vma->vm_end - vma->vm_start;
    if (size > MAX_EIM_MMAP_SIZE) size = MAX_EIM_MMAP_SIZE;

    //set non-cached on this mmap region
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

    return remap_pfn_range(vma, vma->vm_start, eim_phs >> PAGE_SHIFT, size, vma->vm_page_prot);
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
    return 0;
}
