////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include <SoapySDR/Logger.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //close

#include "xilinx_user_gpio.h"

/*
if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    echo "\tusage: fpga_prog.sh 'bitstream_filename.bit'"
    exit 1
fi

echo "Setting export of reset pin"
echo 135 > /sys/class/gpio/export
echo "setting reset pin to out"
echo out > /sys/class/gpio/gpio135/direction
echo "flipping reset"                       
echo 0 > /sys/class/gpio/gpio135/value
echo 1 > /sys/class/gpio/gpio135/value
echo "configuring FPGA"
dd if=$1 of=/dev/spidev2.0 bs=32

echo "turning on clock to FPGA"
devmem2 0x020c8160 w 0x00000D2B
*/

void novenaRF_loadFpga(const std::string &fpgaImage)
{
    //reset with GPIO before loading
    gpio_export(FPGA_RESET_GPIO);
    gpio_set_dir(FPGA_RESET_GPIO, 1);
    gpio_set_value(FPGA_RESET_GPIO, 0);
    usleep(100000);
    gpio_set_value(FPGA_RESET_GPIO, 1);
    usleep(100000);

    //open the specified FPGA image
    SoapySDR::logf(SOAPY_SDR_INFO, "Loading FPGA image %s", fpgaImage.c_str());
    FILE *fpga_fp = fopen(fpgaImage.c_str(), "rb");
    if (fpga_fp == NULL)
    {
        throw std::runtime_error("Failed to open "+fpgaImage+": " + std::string(strerror(errno)));
    }

    //write the FPGA image to the spi device
    int spi_fd = open(FPGA_LOAD_SPIDEV, O_RDWR);
    if (spi_fd < 0)
    {
        fclose(fpga_fp);
        throw std::runtime_error("Failed to open " FPGA_LOAD_SPIDEV ": " + std::string(strerror(errno)));
    }

    while (true)
    {
        char buff[SPIDEV_MAXBUFF];
        int r = fread(buff, 1, sizeof(buff), fpga_fp);
        if (r <= 0) break;
        if (write(spi_fd, buff, r) != r) break;
    }

    fclose(fpga_fp);
    close(spi_fd);
}

//http://www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
//just needed a simple hash algorithm
static unsigned fnv_hash(unsigned char *p, int len)
{
    unsigned h = 2166136261ul;
    for (int i = 0; i < len; i++)
        h = ( h * 16777619ul ) ^ p[i];

    return h;
}

unsigned novenaRF_hashFpga(const std::string &fpgaImage)
{
    //open the specified FPGA image
    FILE *fpga_fp = fopen(fpgaImage.c_str(), "rb");
    if (fpga_fp == NULL)
    {
        throw std::runtime_error("Failed to open "+fpgaImage+": " + std::string(strerror(errno)));
    }

    //just read enough to make a hash that can differentiate images
    unsigned char buff[4096];
    int r = fread(buff, 1, sizeof(buff), fpga_fp);
    fclose(fpga_fp);

    if (r <= 0) throw std::runtime_error("Failed to read "+fpgaImage+": " + std::string(strerror(errno)));

    return fnv_hash(buff, r);
}
