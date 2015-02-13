#ifndef LMS7002M_COMMANDS_H
#define LMS7002M_COMMANDS_H

const int LMS_RST_PULSE = 2;

enum eCMD_LMS
{
    CMD_GET_INFO	= 0x00,
    ///Writes data to SI5356 synthesizer via I2C
    CMD_SI5356_WR 	= 0x11,
    ///Reads data from SI5356 synthesizer via I2C
    CMD_SI5356_RD	= 0x12,
    ///Writes data to SI5351 synthesizer via I2C
    CMD_SI5351_WR = 0x13,
    ///Reads data from SI5351 synthesizer via I2C
    CMD_SI5351_RD = 0x14,
    ///Sets new LMS7002M chip’s RESET pin level (0, 1, pulse)
    CMD_LMS7002_RST	= 0x20,
    ///Writes data to LMS7002M chip via SPI
    CMD_LMS7002_WR	= 0x21,
    ///Reads data from LMS7002M chip via SPI
    CMD_LMS7002_RD	= 0x22,
    ///
    CMD_PROG_MCU = 0x2A,
    ///Writes data to ADF4002 chip via SPI
    CMD_ADF4002_WR	= 0x31,

	CMD_LMS6002_WR = 0x23,
	CMD_LMS6002_RD = 0x24,

	CMD_PE636040_WR = 0x41,
	CMD_PE636040_RD = 0x42,
	CMD_MYRIAD_GPIO_WR = 0x51,
	CMD_MYRIAD_GPIO_RD = 0x52
};

enum eCMD_STATUS
{
    STATUS_UNDEFINED,
    STATUS_COMPLETED_CMD,
    STATUS_UNKNOWN_CMD,
    STATUS_BUSY_CMD,
    STATUS_MANY_BLOCKS_CMD,
    STATUS_ERROR_CMD
};

#endif // LMS7002M_COMMANDS_H

