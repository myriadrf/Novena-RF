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
dd if=$1 of=/dev/spidev2.0 bs=128

echo "turning on clock to FPGA"
*/

void novenaRF_loadFpga(const std::string &fpgaImage)
{
    //check if the FPGA is loaded - TODO

    //reset with GPIO before loading
    gpio_export(FPGA_RESET_GPIO);
    gpio_set_dir(FPGA_RESET_GPIO, 1);
    gpio_set_value(FPGA_RESET_GPIO, 0);
    gpio_set_value(FPGA_RESET_GPIO, 1);

    //open the specified FPGA image
    SoapySDR::logf(SOAPY_SDR_INFO, "Loading FPGA image %s", fpgaImage.c_str());
    FILE *fpga_fp = fopen(fpgaImage.c_str(), "rb");
    if (fpga_fp == NULL)
    {
        perror("open("NOVENA_RF_DEVFS")");
        throw std::runtime_error("Failed to open "+fpgaImage+": " + std::string(strerror(errno)));
    }

    //write the FPGA image to the spi device
    int spi_fd = open(FPGA_LOAD_SPIDEV, O_RDWR);
    if (spi_fd < 0)
    {
        fclose(fpga_fp);
        perror("open("FPGA_LOAD_SPIDEV")");
        throw std::runtime_error("Failed to open "FPGA_LOAD_SPIDEV": " + std::string(strerror(errno)));
    }

    while (true)
    {
        char buff[128];
        int r = fread(buff, 1, sizeof(buff), fpga_fp);
        if (r <= 0) break;
        if (write(spi_fd, buff, r) != r) break;
    }

    fclose(fpga_fp);
    close(spi_fd);
}
