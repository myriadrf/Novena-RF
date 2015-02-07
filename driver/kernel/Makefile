########################################################################
## Build kernel module for Novena-RF SDR
##
## Copyright (c) 2015-2015 Lime Microsystems
## Copyright (c) 2015-2015 Andrew "bunnie" Huang
## SPDX-License-Identifier: Apache-2.0
## http://www.apache.org/licenses/LICENSE-2.0
########################################################################
ifndef
	KDIR := /lib/modules/$(shell uname -r)/build
endif

########################################################################
## sources for novena_rf module
########################################################################
NOVENA_RF_MODULE_SOURCES = \
	novena_rf_module.c \
	novena_rf_eim.c \
	novena_rf_fops.c

novena_rf-objs = $(NOVENA_RF_MODULE_SOURCES:.c=.o)

########################################################################
## list of modules built here
########################################################################
obj-m := novena_rf.o

ccflags-y := -std=gnu99 -Wno-declaration-after-statement

########################################################################
## build and clean targets
########################################################################
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
