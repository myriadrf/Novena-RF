#!/bin/bash
########################################################################
## Run this script on the novena to install binary files,
## and to set proper permissions for the Novena RF driver.
## Usage: sudo ./prepare_novena_rf.sh
########################################################################

DIR="$( cd "$( dirname "$0" )" && pwd )"
set -x #echo on

#create the firmware directory and copy over the bit file
mkdir -p /lib/firmware
cp ${DIR}/novena_rf.bit /lib/firmware/novena_rf.bit
chmod a+r /lib/firmware/novena_rf.bit

#load the novena_rf module (unload if left loaded)
if [ -e "/dev/novena_rf" ]
then
    rmmod novena_rf
fi
insmod ${DIR}/novena_rf.ko

#set permissions on all devices used
chmod a+rw /dev/novena_rf
chmod a+rw /dev/spidev2.0

#export GPIOs that need userspace control
if [ -e "/sys/class/gpio/gpio135" ]
then
    echo 135 > /sys/class/gpio/unexport
fi
echo 135 > /sys/class/gpio/export

if [ -e "/sys/class/gpio/gpio124" ]
then
    echo 124 > /sys/class/gpio/unexport
fi
echo 124 > /sys/class/gpio/export

if [ -e "/sys/class/gpio/gpio122" ]
then
    echo 122 > /sys/class/gpio/unexport
fi
echo 122 > /sys/class/gpio/export

#set permissions on these GPIOs
chmod a+rw /sys/class/gpio/gpio135/direction
chmod a+rw /sys/class/gpio/gpio135/value

chmod a+rw /sys/class/gpio/gpio124/direction
chmod a+rw /sys/class/gpio/gpio124/value
chmod a+rw /sys/class/gpio/gpio124/edge

chmod a+rw /sys/class/gpio/gpio122/direction
chmod a+rw /sys/class/gpio/gpio122/value

