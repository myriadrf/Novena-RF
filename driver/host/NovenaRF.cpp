////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Logger.hpp>
#include <SoapySDR/Modules.hpp>

#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h> //mmap
#include <unistd.h> //close

/***********************************************************************
 * Device interface
 **********************************************************************/
class NovenaRF : public SoapySDR::Device
{
public:
    NovenaRF(void):
        _novena_fd(-1)
    {
        //open the file descriptor for the novena rf module
        _novena_fd = open(NOVENA_RF_DEVFS, O_RDWR | O_SYNC);
        if (_novena_fd <= 0)
        {
            perror("open("NOVENA_RF_DEVFS")");
            throw std::runtime_error("Failed to open "NOVENA_RF_DEVFS": " + std::string(strerror(errno)));
        }
    }

    ~NovenaRF(void)
    {
        close(_novena_fd);
    }

    /*******************************************************************
     * Identification API
     ******************************************************************/
    std::string getDriverKey(void) const
    {
        return "NOVENA-RF";
    }

    std::string getHardwareKey(void) const
    {
        return "NOVENA";
    }

    /*******************************************************************
     * Channels API
     ******************************************************************/

    /*******************************************************************
     * Stream API
     ******************************************************************/

    /*******************************************************************
     * Antenna API
     ******************************************************************/

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/

    /*******************************************************************
     * Gain API
     ******************************************************************/

    /*******************************************************************
     * Frequency API
     ******************************************************************/

    /*******************************************************************
     * Sample Rate API
     ******************************************************************/

    /*******************************************************************
     * Clocking API
     ******************************************************************/

    /*******************************************************************
     * Time API
     ******************************************************************/

    /*******************************************************************
     * Sensor API
     ******************************************************************/

    /*******************************************************************
     * Register API
     ******************************************************************/

    /*******************************************************************
     * Settings API
     ******************************************************************/

    /*******************************************************************
     * GPIO API
     ******************************************************************/

    /*******************************************************************
     * I2C API
     ******************************************************************/

    /*******************************************************************
     * SPI API
     ******************************************************************/

    /*******************************************************************
     * UART API
     ******************************************************************/

private:
    int _novena_fd; //novena_rf kernel module
};

/***********************************************************************
 * Find available devices
 **********************************************************************/
std::vector<SoapySDR::Kwargs> findNovenaRF(const SoapySDR::Kwargs &args)
{
    //always discovery "args" -- the sdr is the board itself
    std::vector<SoapySDR::Kwargs> discovered;
    discovered.push_back(args);
    return discovered;
}

/***********************************************************************
 * Make device instance
 **********************************************************************/
SoapySDR::Device *makeNovenaRF(const SoapySDR::Kwargs &args)
{
    if (args.count("fpga") != 0) novenaRF_loadFpga(args.at("fpga"));
    else novenaRF_loadFpga(SoapySDR::getRootPath() + FPGA_PATH_SUFFIX);
    return new NovenaRF();
}

/***********************************************************************
 * Registration
 **********************************************************************/
static SoapySDR::Registry registerNovenaRF("novena", &findNovenaRF, &makeNovenaRF, SOAPY_SDR_ABI_VERSION);
