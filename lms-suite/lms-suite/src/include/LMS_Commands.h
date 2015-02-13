/**
@file   LMS_Commands.h
@author Lime Microsystems (www.limemicro.com)
@brief  LMS commands and device enumerations
*/
#ifndef LMS_COMMANDS_H
#define LMS_COMMANDS_H

const int LMS_RST_DEACTIVATE = 0;
const int LMS_RST_ACTIVATE = 1;
const int LMS_RST_PULSE = 2;

enum eLMS_DEV{LMS_DEV_UNKNOWN, LMS_DEV_EVB6, LMS_DEV_DIGIGREEN, LMS_DEV_DIGIRED,
            LMS_DEV_EVB7, LMS_DEV_ZIPPER, LMS_DEV_SOCKETBOARD, LMS_DEV_EVB7V2,
            LMS_DEV_STREAM, LMS_DEV_NOVENA, LMS_DEV_COUNT};
const char LMS_DEV_NAMES[][80] = { "UNKNOWN", "EVB6", "DigiGreen", "DigiRed",
            "EVB7", "ZIPPER", "Socket Board", "EVB7_v2",
            "Stream", "Novena"};
enum eEXP_BOARD {EXP_BOARD_UNKNOWN, EXP_BOARD_UNSUPPORTED, EXP_BOARD_NO,
            EXP_BOARD_MYRIAD1, EXP_BOARD_MYRIAD2, EXP_BOARD_MYRIAD_NOVENA,
            EXP_BOARD_HPM1000, EXP_BOARD_COUNT};
const char EXP_BOARD_NAMES[][80] = { "UNKNOWN", "UNSUPPORTED", "NOT AVAILABLE",
            "Myriad1", "Myriad2", "Novena", "HPM1000"};

enum eCMD_LMS
{
    CMD_GET_INFO	= 0x00,
    CMD_LMS6002_RST = 0x10,
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
	CMD_LMS6002_WR = 0x23,
	CMD_LMS6002_RD = 0x24,
	CMD_LMS_LNA = 0x2A,
	CMD_LMS_PA = 0x2B,

    CMD_PROG_MCU = 0x2C,
    ///Writes data to ADF4002 chip via SPI
    CMD_ADF4002_WR	= 0x31,

    CMD_PE636040_WR = 0x41,
	CMD_PE636040_RD = 0x42,

	CMD_MYRIAD_GPIO_WR = 0x51,
	CMD_MYRIAD_GPIO_RD = 0x52,

	CMD_ALTERA_FPGA_GW_WR = 0x53,
	CMD_ALTERA_FPGA_GW_RD = 0x54,

	CMD_MYRIAD_RST = 0x80,
	CMD_MYRIAD_WR = 0x81,
	CMD_MYRIAD_RD = 0x82,
	CMD_MYRIAD_PROG = 0x8C
};

enum eCMD_STATUS
{
    STATUS_UNDEFINED,
    STATUS_COMPLETED_CMD,
    STATUS_UNKNOWN_CMD,
    STATUS_BUSY_CMD,
    STATUS_MANY_BLOCKS_CMD,
    STATUS_ERROR_CMD,
    STATUS_WRONG_ORDER_CMD,
    STATUS_COUNT
};

static const char  status_text[][32]= {"Undefined/Failure", "Completed", "Unknown command", "Busy", "Too many blocks", "Error", "Wrong order"};

static const char* status2string(const int status)
{
    if(status >= 0 && status < STATUS_COUNT)
        return status_text[status];
    else
        return "Unknown status";
}
#endif // LMS_COMMANDS_H

