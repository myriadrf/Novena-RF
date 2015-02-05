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

//devfs registration
static dev_t dev_num;
static struct cdev c_dev;
static struct class *cl;

/***********************************************************************
 * Module entry point
 **********************************************************************/
static int novena_rf_module_init(void)
{
    //register the character device
    if (alloc_chrdev_region(&dev_num, 0, 1, MODULE_NAME) < 0)
    {
        return -1;
    }
    if ((cl = class_create(THIS_MODULE, MODULE_NAME)) == NULL)
    {
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }
    if (device_create(cl, NULL, dev_num, NULL, MODULE_NAME) == NULL)
    {
        class_destroy(cl);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }
    cdev_init(&c_dev, &novena_rf_fops);
    if (cdev_add(&c_dev, dev_num, 1) == -1)
    {
        device_destroy(cl, dev_num);
        class_destroy(cl);
        unregister_chrdev_region(dev_num, 1);
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
    cdev_del(&c_dev);
    device_destroy(cl, dev_num);
    class_destroy(cl);
    unregister_chrdev_region(dev_num, 1);
}

/***********************************************************************
 * Module registration
 **********************************************************************/
MODULE_LICENSE("Dual BSD/GPL");
module_init(novena_rf_module_init);
module_exit(novena_rf_module_exit);
