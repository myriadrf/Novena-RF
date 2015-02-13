/**
@file   ConnectionSPI.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Data communications through SPI for NOVENA board
*/

#include "ConnectionSPI.h"
#include "MessageLog.h"
#include <fstream>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#if defined(__GNUC__) || defined(__GNUG__)
#include <unistd.h>
#include <getopt.h>
#endif

#ifdef __unix__
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#endif

/** @brief Tries to read EEPROM for Novena board signature
    @return true if Novena board
*/
bool IsNovenaBoard()
{
#ifdef __unix__
    char data[8];
    int count = 6;
    memset(data, 0, 8);
    int addr = 0;
    struct i2c_rdwr_ioctl_data session;
    struct i2c_msg messages[2];
    char set_addr_buf[2];
    memset(set_addr_buf, 0, sizeof(set_addr_buf));
    memset(data, 0, count);
    set_addr_buf[0] = addr>>8;
    set_addr_buf[1] = addr;
    messages[0].addr = 0xac>>1;
    messages[0].flags = 0;
    messages[0].len = sizeof(set_addr_buf);
    messages[0].buf = set_addr_buf;
    messages[1].addr = 0xac>>1;
    messages[1].flags = I2C_M_RD;
    messages[1].len = count;
    messages[1].buf = data;
    session.msgs = messages;
    session.nmsgs = 2;

    bool isNovena = false;

    int fd = open("/dev/i2c-2", O_RDWR);
    if(fd > 0)
    {
        if(ioctl(fd, I2C_RDWR, &session) < 0)
        {
            perror("Unable to communicate with i2c device");
            isNovena = false;
        }
        if(strcmp("Novena", data) == 0)
            isNovena = true;
    }
    close(fd);
    return isNovena;
#else
    return false;
#endif
}

#include <fstream>
#include <sstream>
#include "CommonUtilities.h"

ConnectionSPI::ConnectionSPI() : cSPI_SPEED_HZ(4000000)
{
    fd = -1;
    m_connectionType = SPI_PORT;
    std::fstream gpio;
    //export SEN pin
    gpio.open("/sys/class/gpio/export", ios::out);
    if(gpio.good())
    {
        gpio << 122;
        gpio.flush();
        gpio.close();
        gpio.open("/sys/class/gpio/gpio122/direction", ios::out);
        gpio << "out";
        gpio.flush();
        gpio.close();
        m_SEN.open("/sys/class/gpio/gpio122/value", ios::out);
        m_SEN<< 1;
        m_SEN.flush();
        cout << "GPIO122: set to 1" << endl;
    }
    memset(rxbuf, 0, cSPI_BUF_SIZE);
}

ConnectionSPI::~ConnectionSPI()
{
    Close();
    m_SEN.close();
}

bool ConnectionSPI::Open()
{
    Close();
#ifdef __unix__
    fd = open("/dev/spidev2.0", O_RDWR);
	if (fd < 0)
	{
        MessageLog::getInstance()->write("SPI PORT: device not found\n", LOG_ERROR);
		return false;
	}
	int mode = SPI_MODE_0;
	int ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		printf("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		printf("can't get spi mode");

	/*
	 * bits per word
	 */
	 int bits = 8;
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		printf("can't get bits per word");

	/*
	 * max speed hz
	 */
	 int speed = cSPI_SPEED_HZ;
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't get max speed hz");

	printf("spi mode: 0x%x\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
    return true;
#else
    return false;
#endif
}

bool ConnectionSPI::Open(int i)
{
    return Open();
}

void ConnectionSPI::Close()
{
#ifdef __unix__
    close(fd);
    fd = -1;
#endif
}

bool ConnectionSPI::IsOpen()
{
    return (fd >= 0);
}

int ConnectionSPI::SendData(const unsigned char* buffer, unsigned long length, unsigned long timeout_ms)
{
#ifdef __unix__
    if(fd < 0)
        return 0;
    m_SEN << 0;
    m_SEN.flush();
    unsigned long bytesWritten = 0;
    memset(rxbuf, 0, 1024);
    int bytesReceived = 0;
    while(bytesWritten < length)
    {
        int toWrite = length > cSPI_BUF_SIZE ? cSPI_BUF_SIZE : length;
        for(int i=0; i<toWrite; i+=2)
        {
            if(buffer[i] < 0x80)
            {
                write(fd, &buffer[i], 1);
                read(fd, &rxbuf[i+1], 1);
                ++bytesReceived;
            }
            else
            {
                write(fd, &buffer[i], 2);
            }
        }

        stringstream ss;
        ss << "write(" << toWrite << "): ";
        for(int i=0; i<toWrite; ++i)
            ss << int2hex(buffer[bytesWritten+i], 1) << " ";
        ss << endl;
        if(bytesReceived > 0)
        {
            ss << " read(" << toWrite << "): ";
            for(int i=0; i<toWrite; ++i)
                ss << int2hex(rxbuf[bytesWritten+i], 1) << " ";
            ss << endl;
        }
        MessageLog::getInstance()->write(ss.str(), LOG_DATA);

        bytesWritten += toWrite;
        length -= toWrite;
    }
    m_SEN << 1;
    m_SEN.flush();
    return bytesWritten;
#else
    return 0;
#endif
}

int ConnectionSPI::ReadData(unsigned char* buffer, unsigned long length, unsigned long timeout_ms)
{
#ifdef __unix__
    if(fd < 0)
        return 0;
    //because transfer is done in full duplex, function returns data from last transfer
    int tocpy = length > cSPI_BUF_SIZE ? cSPI_BUF_SIZE : length;
    memcpy(buffer, rxbuf, tocpy);
    memset(rxbuf, 0, sizeof(rxbuf));
    return tocpy;
#else
    return 0;
#endif
}

std::vector<std::string> ConnectionSPI::GetDeviceNames()
{
    std::vector<std::string> name;
#ifdef __unix__
    int spidev = open("/dev/spidev2.0", O_RDWR);
	if (spidev >= 0)
	{
	    if(IsNovenaBoard() == true)
            name.push_back("Novena");
        else
            name.push_back("SPI");
	}
    close(spidev);
#endif
    return name;
}

void ConnectionSPI::FindDevices()
{
}

void ConnectionSPI::ClearComm()
{
}
