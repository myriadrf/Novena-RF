# Myriad-RF Module SDR driver

This directory contains the complete SDR driver for the Myriad-RF Module.

## Contents

* fpga/ - fpga project bridging LMS6002D to the EIM bus
* kernel/ - memory mapped access to sample/packet buffers
* host/ - host wrapper through a SoapySDR support module

## Build the FPGA image

Build the FPGA image with Xilinx ISE 14.*.
The project is fpga/novena_rf/novena_rf.xise

## Build the kernel module

This is an out of tree kernel module, it requires a cross arm toolchain
and a build of the linux kernel.

Download one of the available ARM toolchains:
http://boundarydevices.com/toolchains-i-mx6/

Clone the linux kernel branch for Novena:

```
git clone https://github.com/xobs/novena-linux.git
cd novena-linux
git checkout v3.17-rc5-novena-vivante
```

Instructions for building the kernel:
http://boundarydevices.com/cross-compile-i-mx6-kernel-using-ltib-toolchain/

Build the kernel module:

```
cd kernel
make ARCH=arm KDIR=path/to/novena-linux
ls novena_rf.ko #output
```

## Build the SoapySDR module

First install the SoapySDR library:
https://github.com/pothosware/SoapySDR/wiki/BuildGuide

Build and install the Novena RF module:

```
cd host
mkdir build
cd build
cmake ../
make
sudo make install
```

## Licensing

The FPGA RTL, kernel source, and host wrapper are licensed under the Apache License, Version 2.0.
However, please note that this does not extend to any files provided with the Xilinx design tools and see the relevant files for the associated terms and conditions.
