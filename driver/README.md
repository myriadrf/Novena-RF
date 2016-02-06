# Myriad-RF Module SDR driver

This directory contains the complete SDR driver for the Myriad-RF Module.

## Contents

* fpga/ - FPGA project bridging LMS6002D to the EIM bus
* kernel/ - memory mapped access to sample/packet buffers
* host/ - host wrapper through a SoapySDR support module
* binary/ - pre-built FPGA image and kernel module

## Driver properties

### Configurable sample rates

* Max rate: 15.36 Msps
* Decimations: 1, 2, 4, 8, 16
* Interpolations: 1, 2, 4, 8, 16

### Selectable TX antenna switches

* "HB" - High band output (1500 - 3800 MHz)
* "BB" - Broadband output

The names for these switches can be used in the setAntenna() API call.

### Selectable RX antenna switches

* "LB" - Low band input (300 - 2200 MHz)
* "HB" - High band input (1500 - 3800MHz)
* "BB" - Broadband input

The names for these switches can be used in the setAntenna() API call.

### TX and RX Baseband filters

* 1.5 MHz to 28.0 MHz

### Adjustable transmit gain

* Overall: 0.0 to 56.0  dB
* "VGA1": -35.0 to -4.0 dB
* "VGA2": 0.0 to 25.0 dB

The names for these gain elements can be used in the setGain() API call.

### Adjustable receive gain

* Overall: 0.0  to 36.0  dB
* "VGA2": 0.0  to 30.0  dB
* "VGA1": 0.0  to 30.0  dB
* "LNA": 0.0  to 6.0  dB

The names for these gain elements can be used in the setGain() API call.

## Installing drivers

The following instructions allow one to build the driver for NovenaRF.
The instructions are intended for building locally on the device (for now).

### Dependencies

```
sudo apt-get install cmake g++ libusb-1.0-0-dev git
sudo apt-get remove libi2c-dev #fixes build issue
```

### Build the host driver

SoapySDR is a modular library and API for SDR devices.
First install the SoapySDR library:
https://github.com/pothosware/SoapySDR/wiki/BuildGuide

Then build and install the Novena RF support module:

```
git clone https://github.com/myriadrf/Novena-RF.git
cd Novena-RF/driver/host
mkdir build
cd build
cmake ../
make
sudo make install
sudo ldconfig
```

### Setup permissions and resources

There is a compiled FPGA image and kernel module in binary/
To install the files and to set the system permissions:

```
cd Novena-RF/driver/binary
sudo ./prepare_novena_rf.sh
```

Note: this script should be run after each reboot to set permissions and to load the module.

If, upon running the script, you get the error “could not insert module novena\_rf.ko: Invalid module format”, this means that the prebuilt `novena_rf.ko` doesn't match your kernel. Run `uname -a` to get the full version of your running kernel and `ls novena_rf.ko.*` to see if there's a matching version that you can copy over `novena_rf.ko`. If not, see the section below on building the kernel module.

## Hello Novena RF

Check that the installation detects NovenaRF support:

```
SoapySDRUtil --make="driver=novena"
```

## Platforms

### GNU Radio

Use the NovenaRF in GNU Radio through the gr-osmosdr API.
The user will have to install GNU Radio and SoapySDR first,
then install gr-osmosdr through the official project.
Make sure that soapy is one of the enabled components:

```
git clone git://git.osmocom.org/gr-osmosdr
cd gr-osmosdr/
```

## Pothos

Use the NovenaRF through Pothos SDR source and sink blocks
which support advanced timed streaming and burst controls.
Install SoapySDR first before following the build guide:
https://github.com/pothosware/pothos/wiki/BuildGuide

## osmo-trx

This is a branch of osmo-trx with novena support:
https://github.com/pothosware/osmo-trx/tree/novena\_support

## Advanced

### Build the FPGA image

Build the FPGA image with Xilinx ISE 14.\*.
The project is fpga/novena\_rf/novena\_rf.xise

### Build the kernel module

This is an out of tree kernel module and needs a full build of the kernel to compile against. Since a full kernel build can take a long time on the Novena, these instructions are for cross-compiling the kernel on another (more powerful) machine.

Download one of the available ARM toolchains:
http://boundarydevices.com/toolchains-i-mx6/. For example, the toolchain used below can be found [here](https://launchpad.net/linaro-toolchain-binaries/+milestone/2012.04).

Clone the linux kernel branch for Novena:

```
git clone https://github.com/xobs/novena-linux.git
cd novena-linux
```

You need to build a kernel that matches the one that you're running as closely as possible. Run `apt-cache show linux-image-novena | grep Version` to get the version number, which should look something like `3.19-novena-r39`. Then run `git tag | grep novena` to list the available tags and match the running version, hopefully exactly.

Instructions for building the kernel have been borrowed from this site:
http://boundarydevices.com/cross-compile-i-mx6-kernel-using-ltib-toolchain/


```
export PATH=/opt/toolchains/gcc-linaro-arm-linux-gnueabi-2012.04-20120426_linux/bin/:$PATH
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
make novena_defconfig
make -j5 zImage modules
```

Now build the kernel module from `Novena-RF/driver`:

```
cd kernel
make ARCH=arm KDIR=path/to/novena-linux
ls novena_rf.ko #output
```

## Licensing

The FPGA RTL, kernel source, and host wrapper are licensed under the Apache License, Version 2.0.
However, please note that this does not extend to any files provided with the Xilinx design tools and see the relevant files for the associated terms and conditions.
