////////////////////////////////////////////////////////////////////////
// Build kernel module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "novena_rf_module.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>

/***********************************************************************
 * Module data structures
 **********************************************************************/
static struct file_operations novena_rf_fops = {
    unlocked_ioctl: novena_rf_ioctl,
    mmap: novena_rf_mmap,
    open: novena_rf_open,
    release: novena_rf_release
};

static novena_rf_module_t module_data;

/***********************************************************************
 * Module entry point
 **********************************************************************/
static int novena_rf_module_init(void)
{
    module_data.eim_configured = 0;
    module_data.eim_memory = 0;

    //register the character device
    if (alloc_chrdev_region(&module_data.dev_num, 0, 1, MODULE_NAME) < 0)
    {
        return -1;
    }
    if ((module_data.cl = class_create(THIS_MODULE, MODULE_NAME)) == NULL)
    {
        unregister_chrdev_region(module_data.dev_num, 1);
        return -1;
    }
    if (device_create(module_data.cl, NULL, module_data.dev_num, NULL, MODULE_NAME) == NULL)
    {
        class_destroy(module_data.cl);
        unregister_chrdev_region(module_data.dev_num, 1);
        return -1;
    }
    cdev_init(&module_data.c_dev, &novena_rf_fops);
    if (cdev_add(&module_data.c_dev, module_data.dev_num, 1) == -1)
    {
        device_destroy(module_data.cl, module_data.dev_num);
        class_destroy(module_data.cl);
        unregister_chrdev_region(module_data.dev_num, 1);
        return -1;
    }
    return 0;
}

/***********************************************************************
 * Module exit point
 **********************************************************************/
static void novena_rf_module_exit(void)
{
    //remove the character device
    cdev_del(&module_data.c_dev);
    device_destroy(module_data.cl, module_data.dev_num);
    class_destroy(module_data.cl);
    unregister_chrdev_region(module_data.dev_num, 1);
}

/***********************************************************************
 * Module registration
 **********************************************************************/
MODULE_LICENSE("Dual BSD/GPL");
module_init(novena_rf_module_init);
module_exit(novena_rf_module_exit);
