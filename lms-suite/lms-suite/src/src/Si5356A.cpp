/**
@file   Si5356A.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Configuring of Si5356A synthesizer
*/
#include "Si5356A.h"
#include "ConnectionManager.h"
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include "CommonUtilities.h"

// ---------------------------------------------------------------------------
// Comands
// I2C FPGA
#define CFG_ADDR 0xAA
#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

// LMS6002D
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

// I2C Si5356A
#define FSN_ADDR 0xE0
#define SI5338_DELAY 12 //12ms

#define LOCK_MASK 0x19
#define LOS_MASK 0x08

//Register map for use with AN428 (JumpStart)
//http://www.silabs.com/clocks
//Copyright 2012 Silicon Laboratories
//#BEGIN_HEADER
//Date = 2012 m. liepos 12 d. 14:35
//File version = 3
//Software Name = ClockBuilder Desktop Software
//Software version = 5.0.0
//Software date = March 17, 2012
//Chip = Si5356
//Part Number = Si5356
//#END_HEADER
//Input Frequency (MHz): 30,720000000

//Input Frequency (MHz) = 30,720000000
//Input Type = OFF
//P1 = 1
//Input Mux = FbClk
//FDBK Input Frequency (MHz) = 30,720000000
//FDBK Input Type = CMOS_SSTL_HSTL
//P2 = 1
//FDBK Mux = FbClk
//PFD Input Frequency (MHz) = 30,720000000
//VCO Frequency (GHz) = 2,200000
//N = 71  59/96  (71,6146)
//Internal feedback enabled
//Maximum Output Clock Frequency (MHz) = VCO / 8 = 275,000000
//Output Clock 0
// Output is off
//Output Clock 1
// Output Frequency (MHz) = 30,000000000
// Mux Selection = IDn
// MultiSynth = 73  1/3  (73,3333)
// R = 1
//Output Clock 2
// Output Frequency (MHz) = 30,000000000
// Mux Selection = IDn
// MultiSynth = 73  1/3  (73,3333)
// R = 1
//Output Clock 3
// Output is off
//Driver 0
// Disabled
// Powered off
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 1
// Enabled
// Powered on
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 2
// Enabled
// Powered on
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Driver 3
// Disabled
// Powered off
// Output voltage = 3,30
// Output type = CMOS_PN_3V3
//Initial phase offset 0 (ns) = 0,000
//Initial phase offset 1 (ns) = 0,000
//Initial phase offset 2 (ns) = 0,000
//Initial phase offset 3 (ns) = 0,000
//SSC is disabled

#define NUM_REGS_MAX 350
///default register values for Si5356A
Reg_Data Reg_Store[NUM_REGS_MAX] = {
{  0,0x00,0x00},
{  1,0x00,0x00},
{  2,0x00,0x00},
{  3,0x00,0x00},
{  4,0x00,0x00},
{  5,0x00,0x00},
{  6,0x04,0x1D},
{  7,0x00,0x00},
{  8,0x70,0x00},
{  9,0x0F,0x00},
{ 10,0x00,0x00},
{ 11,0x00,0x00},
{ 12,0x00,0x00},
{ 13,0x00,0x00},
{ 14,0x00,0x00},
{ 15,0x00,0x00},
{ 16,0x00,0x00},
{ 17,0x00,0x00},
{ 18,0x00,0x00},
{ 19,0x00,0x00},
{ 20,0x00,0x00},
{ 21,0x00,0x00},
{ 22,0x00,0x00},
{ 23,0x00,0x00},
{ 24,0x00,0x00},
{ 25,0x00,0x00},
{ 26,0x00,0x00},
{ 27,0x70,0x80},
{ 28,0x37,0xFF},
{ 29,0x20,0xFF},
{ 30,0xA8,0xFF},
{ 31,0xE3,0xFF},
{ 32,0xC0,0xFF},
{ 33,0xC0,0xFF},
{ 34,0xE3,0xFF},
{ 35,0x00,0xFF},
{ 36,0x00,0x1F},
{ 37,0x0B,0x1F},
{ 38,0x03,0x1F},
{ 39,0x00,0x1F},
{ 40,0xF7,0xFF},
{ 41,0x5E,0x7F},
{ 42,0x37,0x3F},
{ 43,0x00,0x00},
{ 44,0x00,0x00},
{ 45,0x00,0x00},
{ 46,0x00,0x00},
{ 47,0x14,0x3C},
{ 48,0x2E,0x7F},
{ 49,0x90,0x7F},
{ 50,0xDE,0xC0},
{ 51,0x07,0x00},
{ 52,0x10,0x0C},
{ 53,0x00,0xFF},
{ 54,0x00,0xFF},
{ 55,0x00,0xFF},
{ 56,0x00,0xFF},
{ 57,0x00,0xFF},
{ 58,0x00,0xFF},
{ 59,0x00,0xFF},
{ 60,0x00,0xFF},
{ 61,0x00,0xFF},
{ 62,0x00,0x3F},
{ 63,0x10,0x0C},
{ 64,0x00,0xFF},
{ 65,0x35,0xFF},
{ 66,0x00,0xFF},
{ 67,0x00,0xFF},
{ 68,0x00,0xFF},
{ 69,0x00,0xFF},
{ 70,0x01,0xFF},
{ 71,0x00,0xFF},
{ 72,0x00,0xFF},
{ 73,0x00,0x3F},
{ 74,0x10,0x0C},
{ 75,0x00,0xFF},
{ 76,0x35,0xFF},
{ 77,0x00,0xFF},
{ 78,0x00,0xFF},
{ 79,0x00,0xFF},
{ 80,0x00,0xFF},
{ 81,0x01,0xFF},
{ 82,0x00,0xFF},
{ 83,0x00,0xFF},
{ 84,0x00,0x3F},
{ 85,0x10,0x0C},
{ 86,0x00,0xFF},
{ 87,0x00,0xFF},
{ 88,0x00,0xFF},
{ 89,0x00,0xFF},
{ 90,0x00,0xFF},
{ 91,0x00,0xFF},
{ 92,0x00,0xFF},
{ 93,0x00,0xFF},
{ 94,0x00,0xFF},
{ 95,0x00,0x3F},
{ 96,0x10,0x00},
{ 97,0xCE,0xFF},
{ 98,0x21,0xFF},
{ 99,0x00,0xFF},
{100,0x01,0xFF},
{101,0x00,0xFF},
{102,0x00,0xFF},
{103,0x60,0xFF},
{104,0x00,0xFF},
{105,0x00,0xFF},
{106,0x80,0x3F},
{107,0x00,0xFF},
{108,0x00,0x7F},
{109,0x00,0x00},
{110,0x40,0xC0},
{111,0x00,0xFF},
{112,0x00,0x7F},
{113,0x00,0x00},
{114,0x40,0xC0},
{115,0x00,0xFF},
{116,0x80,0x7F},
{117,0x00,0x00},
{118,0x40,0xC0},
{119,0x00,0xFF},
{120,0x00,0xFF},
{121,0x00,0x00},
{122,0x40,0xC0},
{123,0x00,0x00},
{124,0x00,0x00},
{125,0x00,0x00},
{126,0x00,0x00},
{127,0x00,0x00},
{128,0x00,0x00},
{129,0x00,0x0F},
{130,0x00,0x0F},
{131,0x00,0x00},
{132,0x00,0x00},
{133,0x00,0x00},
{134,0x00,0x00},
{135,0x00,0x00},
{136,0x00,0x00},
{137,0x00,0x00},
{138,0x00,0x00},
{139,0x00,0x00},
{140,0x00,0x00},
{141,0x00,0x00},
{142,0x00,0x00},
{143,0x00,0x00},
{144,0x00,0x80},
{145,0x00,0x00},
{146,0xFF,0x00},
{147,0x00,0x00},
{148,0x00,0x00},
{149,0x00,0x00},
{150,0x00,0x00},
{151,0x00,0x00},
{152,0x00,0x00},
{153,0x00,0x00},
{154,0x00,0x00},
{155,0x00,0x00},
{156,0x00,0x00},
{157,0x00,0x00},
{158,0x00,0x0F},
{159,0x00,0x0F},
{160,0x00,0x00},
{161,0x00,0x00},
{162,0x00,0x00},
{163,0x00,0x00},
{164,0x00,0x00},
{165,0x00,0x00},
{166,0x00,0x00},
{167,0x00,0x00},
{168,0x00,0x00},
{169,0x00,0x00},
{170,0x00,0x00},
{171,0x00,0x00},
{172,0x00,0x00},
{173,0x00,0x00},
{174,0x00,0x00},
{175,0x00,0x00},
{176,0x00,0x00},
{177,0x00,0x00},
{178,0x00,0x00},
{179,0x00,0x00},
{180,0x00,0x00},
{181,0x00,0x0F},
{182,0x00,0x00},
{183,0x00,0x00},
{184,0x00,0x00},
{185,0x00,0x00},
{186,0x00,0x00},
{187,0x00,0x00},
{188,0x00,0x00},
{189,0x00,0x00},
{190,0x00,0x00},
{191,0x00,0x00},
{192,0x00,0x00},
{193,0x00,0x00},
{194,0x00,0x00},
{195,0x00,0x00},
{196,0x00,0x00},
{197,0x00,0x00},
{198,0x00,0x00},
{199,0x00,0x00},
{200,0x00,0x00},
{201,0x00,0x00},
{202,0x00,0x00},
{203,0x00,0x0F},
{204,0x00,0x00},
{205,0x00,0x00},
{206,0x00,0x00},
{207,0x00,0x00},
{208,0x00,0x00},
{209,0x00,0x00},
{210,0x00,0x00},
{211,0x00,0x00},
{212,0x00,0x00},
{213,0x00,0x00},
{214,0x00,0x00},
{215,0x00,0x00},
{216,0x00,0x00},
{217,0x00,0x00},
{218,0x00,0x00},
{219,0x00,0x00},
{220,0x00,0x00},
{221,0x0D,0x00},
{222,0x00,0x00},
{223,0x00,0x00},
{224,0xF4,0x00},
{225,0xF0,0x00},
{226,0x00,0x00},
{227,0x00,0x00},
{228,0x00,0x00},
{229,0x00,0x00},
{231,0x00,0x00},
{232,0x00,0x00},
{233,0x00,0x00},
{234,0x00,0x00},
{235,0x00,0x00},
{236,0x00,0x00},
{237,0x00,0x00},
{238,0x14,0x00},
{239,0x00,0x00},
{240,0x00,0x00},
{242,0x00,0x00},
{243,0xF0,0x00},
{244,0x00,0x00},
{245,0x00,0x00},
{247,0x00,0x00},
{248,0x00,0x00},
{249,0xA8,0x00},
{250,0x00,0x00},
{251,0x84,0x00},
{252,0x00,0x00},
{253,0x00,0x00},
{254,0x00,0x00},
{255, 1, 0xFF}, // set page bit to 1
{  0,0x00,0x00},
{  1,0x00,0x00},
{  2,0x00,0x00},
{  3,0x00,0x00},
{  4,0x00,0x00},
{  5,0x00,0x00},
{  6,0x00,0x00},
{  7,0x00,0x00},
{  8,0x00,0x00},
{  9,0x00,0x00},
{ 10,0x00,0x00},
{ 11,0x00,0x00},
{ 12,0x00,0x00},
{ 13,0x00,0x00},
{ 14,0x00,0x00},
{ 15,0x00,0x00},
{ 16,0x00,0x00},
{ 17,0x01,0x00},
{ 18,0x00,0x00},
{ 19,0x00,0x00},
{ 20,0x90,0x00},
{ 21,0x31,0x00},
{ 22,0x00,0x00},
{ 23,0x00,0x00},
{ 24,0x01,0x00},
{ 25,0x00,0x00},
{ 26,0x00,0x00},
{ 27,0x00,0x00},
{ 28,0x00,0x00},
{ 29,0x00,0x00},
{ 30,0x00,0x00},
{ 31,0x00,0xFF},
{ 32,0x00,0xFF},
{ 33,0x01,0xFF},
{ 34,0x00,0xFF},
{ 35,0x00,0xFF},
{ 36,0x90,0xFF},
{ 37,0x31,0xFF},
{ 38,0x00,0xFF},
{ 39,0x00,0xFF},
{ 40,0x01,0xFF},
{ 41,0x00,0xFF},
{ 42,0x00,0xFF},
{ 43,0x00,0x0F},
{ 44,0x00,0x00},
{ 45,0x00,0x00},
{ 46,0x00,0x00},
{ 47,0x00,0xFF},
{ 48,0x00,0xFF},
{ 49,0x01,0xFF},
{ 50,0x00,0xFF},
{ 51,0x00,0xFF},
{ 52,0x90,0xFF},
{ 53,0x31,0xFF},
{ 54,0x00,0xFF},
{ 55,0x00,0xFF},
{ 56,0x01,0xFF},
{ 57,0x00,0xFF},
{ 58,0x00,0xFF},
{ 59,0x00,0x0F},
{ 60,0x00,0x00},
{ 61,0x00,0x00},
{ 62,0x00,0x00},
{ 63,0x00,0xFF},
{ 64,0x00,0xFF},
{ 65,0x01,0xFF},
{ 66,0x00,0xFF},
{ 67,0x00,0xFF},
{ 68,0x90,0xFF},
{ 69,0x31,0xFF},
{ 70,0x00,0xFF},
{ 71,0x00,0xFF},
{ 72,0x01,0xFF},
{ 73,0x00,0xFF},
{ 74,0x00,0xFF},
{ 75,0x00,0x0F},
{ 76,0x00,0x00},
{ 77,0x00,0x00},
{ 78,0x00,0x00},
{ 79,0x00,0xFF},
{ 80,0x00,0xFF},
{ 81,0x00,0xFF},
{ 82,0x00,0xFF},
{ 83,0x00,0xFF},
{ 84,0x90,0xFF},
{ 85,0x31,0xFF},
{ 86,0x00,0xFF},
{ 87,0x00,0xFF},
{ 88,0x01,0xFF},
{ 89,0x00,0xFF},
{ 90,0x00,0xFF},
{ 91,0x00,0x0F},
{ 92,0x00,0x00},
{ 93,0x00,0x00},
{ 94,0x00,0x00},
{255, 0, 0xFF} }; // set page bit to 0
//End of file
//CHECKSUM = 14CFBC138966364B666BF9BF3AA0FACA34D009AF

Si5356A::Si5356A()
{
    m_crystalFreq = 0;
    m_inputCLKIN = 1;
    DRVA_INV = 0;
	DRVB_INV = 0;
	DRVC_INV = 0;
	DRVD_INV = 0;

	DRVA_FMT = 3;
	DRVB_FMT = 3;
	DRVC_FMT = 3;
	DRVD_FMT = 3;
    freqMHz = 10;
	device = NULL;
}
// ---------------------------------------------------------------------------

Si5356A::~Si5356A()
{
}

/** @brief Sends Configuration to Si5356A chip
*/
bool Si5356A::ConfigureSi5356A()
{
	unsigned char out[64];
	unsigned char in[64];
	long length = 64;

	if (!device)
		return false;

	Reg_Data curr;
	char curr_chip_val, clear_curr_val, clear_new_val, combined, reg;

    //Disable outputs
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 230;
	out[5] = 0x10;
	out[6] = 241;
	out[7] = 0xE5; // 0xE5;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// for all the register values in the Reg_Store array
	// get each value and mask and apply it to the Si5338  for(int i=0; i<NUM_REGS_MAX; i++)
	for (int i = 0; i < NUM_REGS_MAX; i++)
	{
		curr = Reg_Store[i];

		memset(out, 0x00, length);
		memset(in, 0x00, length);

		if (curr.Reg_Mask != 0x00)
		{
			if (curr.Reg_Mask == 0xFF)
			{
				// do a write transaction only
				// since the mask is all ones
				// Write data
				out[0] = CMD_CFG_I2C_WR;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;
				out[5] = curr.Reg_Val;

				device->Port_write_direct(out, length);
				device->Port_read_direct(in, length);
				// I2C_ByteWrite(curr.Reg_Addr, curr.Reg_Val);
			}
			else
			{
				// do a read-modify-write
				// Write data
				out[0] = CMD_CFG_I2C_RD;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;

				device->Port_write_direct(out, length);
				device->Port_read_direct(in, length);

				curr_chip_val = in[0];

				// curr_chip_val = 0xFF; //I2C_ByteRead(curr.Reg_Addr);
				clear_curr_val = curr_chip_val&~curr.Reg_Mask;
				clear_new_val = curr.Reg_Val & curr.Reg_Mask;
				combined = clear_new_val | clear_curr_val;

				// I2C_ByteWrite(curr.Reg_Addr, combined);
				// Write data
				out[0] = CMD_CFG_I2C_WR;
				out[1] = FSN_ADDR;
				out[2] = 1;
				//
				out[4] = curr.Reg_Addr;
				out[5] = combined;

				device->Port_write_direct(out, length);
				device->Port_read_direct(in, length);

			}
		}
	};

	// I2C_ByteWrite(246, 2); //soft reset
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 246;
	out[5] = 2;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 230;
	out[5] = 0x00;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	return true;

	// check LOS alarm for the xtal input
	// on IN1 and IN2 (and IN3 if necessary) -
	// change this mask if using inputs on IN4, IN5, IN6
	do
	{
		memset(out, 0x00, length);
		memset(in, 0x00, length);

		// Read data
		out[0] = CMD_CFG_I2C_RD;
		out[1] = FSN_ADDR;
		out[2] = 1;
		//
		out[4] = 218;
		device->Port_write_direct(out, length);
		device->Port_read_direct(in, length);
		reg = in[0] & LOS_MASK;
	}
	while (reg != 0);

	// I2C_ByteWrite(49, I2C_ByteRead(49) & 0x7F); //FCAL_OVRD_EN = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	out[5] = in[0] & 0x7F;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// I2C_ByteWrite(246, 2); //soft reset
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 246;
	out[5] = 2;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// I2C_ByteWrite(241, 0x65); //DIS_LOL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 241;
	out[5] = 0x65;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// wait for Si5338 to be ready after calibration (ie, soft reset)
	// counter = 0;
	// while(counter < SI5338_DELAY) { counter++; }
	milSleep(SI5338_DELAY);
	// counter = 0;
	// while(counter < SI5338_DELAY) { counter++; }
	milSleep(SI5338_DELAY);

	// make sure the device locked by checking PLL_LOL and SYS_CAL
	/*
	 reg = I2C_ByteRead(218) & LOCK_MASK;
	 while(reg != 0)
	 {
	 reg = I2C_ByteRead(218) & LOCK_MASK;
	 }
	 */
	do
	{
		memset(out, 0x00, length);
		memset(in, 0x00, length);

		// Read data
		out[0] = CMD_CFG_I2C_RD;
		out[1] = FSN_ADDR;
		out[2] = 1;
		//
		out[4] = 218;
		device->Port_write_direct(out, length);
		device->Port_read_direct(in, length);
		reg = in[0] & LOCK_MASK;
	}
	while (reg != 0);

	// copy FCAL values
	// I2C_ByteWrite(45, I2C_ByteRead(235));
	// I2C_ByteWrite(46, I2C_ByteRead(236));
	memset(out, 0x00, length);
	memset(in, 0x00, length);

	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 235;
	out[5] = 236;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 45;
	out[5] = in[0];
	out[6] = 46;
	out[7] = in[1];
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// clear bits 0 and 1 from 47 and
	// combine with bits 0 and 1 from 237
	// reg = (I2C_ByteRead(47) & 0xFC) | (I2C_ByteRead(237) & 3);
	// I2C_ByteWrite(47, reg);
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 2;
	//
	out[4] = 47;
	out[5] = 237;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 47;
	out[5] = (in[0] & 0xFC) | (in[1] & 3);
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// I2C_ByteWrite(49, I2C_ByteRead(49) | 0x80); // FCAL_OVRD_EN = 1
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Read data
	out[0] = CMD_CFG_I2C_RD;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 49;
	out[5] = in[0] | 0x80;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
	memset(out, 0x00, length);
	memset(in, 0x00, length);
	// Write data
	out[0] = CMD_CFG_I2C_WR;
	out[1] = FSN_ADDR;
	out[2] = 1;
	//
	out[4] = 230;
	out[5] = 0x00;
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);
}
// ---------------------------------------------------------------------------

void Si5356A::LmsRead()
{
	// int iVal;
	unsigned char out[64];
	unsigned char in[64];
	long length = 64;

	if (!device)
		return;

	// iVal = cmbOvs->ItemIndex;

	// Read data from address 0x04
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_RD;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x04; // SPI Instruction
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// Write 0x0F to address 0x07
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_WR;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x87; // SPI Instruction
	out[5] = 0x0F; // SPI Data
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	// Read data from address 0x07
	memset(out, 0x00, length);
	// Write data
	out[0] = CMD_LMS_RD;
	out[1] = CFG_ADDR;
	out[2] = 1;
	//
	out[4] = 0x07; // SPI Instruction
	device->Port_write_direct(out, length);
	device->Port_read_direct(in, length);

	/*
	 memset(out, 0x00, length);
	 //Write data
	 //out[0] = CMD_CFG_I2C_WR;
	 out[0] = CMD_CFG_I2C_RD;
	 out[1] = CFG_ADDR;
	 out[2] = 1;
	 //
	 out[4] = 0x00;  //SPI Instruction

	 device->Port_write_direct(out, length);
	 device->Port_read_direct(in, length);
	 */

}

/** @brief Sets connection manager to use for data transferring and configures Si5356A
    @param mng connection manager for data transferring
*/
void Si5356A::Initialize(ConnectionManager *mng)
{
	device = mng;
}

/** @brief Loads register values for Si5356A from file
    @param FName input filename
*/
bool Si5356A::LoadRegValuesFromFile(const char *FName)
{
	FILE *in;
	char inStr[128];
	int iEntry = 0;
	int Rez;

	int iReg_Addr;
	int iReg_Val;
	int iReg_Mask;

	if ((in = fopen(FName, "rt")) == NULL)
	{
		return false;
	};

	while (!feof(in))
	{
		fgets(inStr, 127, in);
		if (inStr[0] == '{')
		{
			Rez = sscanf(&inStr[1], "%d,%i,%i", &iReg_Addr, &iReg_Val,
				&iReg_Mask);
			if (Rez == 3)
			{
				Reg_Store[iEntry].Reg_Addr = iReg_Addr;
				Reg_Store[iEntry].Reg_Val = iReg_Val;
				Reg_Store[iEntry].Reg_Mask = iReg_Mask;
			};
			iEntry++;
		};
	};
	fclose(in);
	return true;
}

/** @brief Sets frequency for desired clock
    @param clkID clock id
    @param refClkMHz reference clock frequency in MHz
    @param clkMHz clock output frequency
*/
void Si5356A::SetFrequency(unsigned int clkID, float refClkMHz, float clkMHz)
{
    freqMHz = clkMHz;
    fpfdMHz = refClkMHz;
    //reference clock configuration
    if(m_inputCLKIN)
    {
        for(int i=0; i<4; i++)
        {
            unsigned char cval = 0;
            cval = GetReg(31+i);
            cval &= 0x1F;
            cval |= 0xC0;
            SetReg(31+i, cval);
        }

        if(fpfdMHz > 5 && fpfdMHz <= 40)
        {
            SetReg(28, 0x37);
            SetReg(29, 0x20);
            SetReg(30, 0x08);
        }
        else if(fpfdMHz > 40) //CLKIN > 40 MHz
        {
           /* m_regmap[28] &= 0x37;
            m_regmap[29] &= 0xE0;
            m_regmap[30] &= 0x08; //need to set PDIV*/
        }
    }
    else //xoclk
    {
        if(m_crystalFreq == 0) // xoclk 25MHz
            SetReg(28, 0x36);
        else // xoclk 27MHz
            SetReg(28, 0x37);
        SetReg(29, 0x80);
        SetReg(30, 0x00);
    }

    //configuring PLL parameters
    unsigned int K = 0;
    if( fpfdMHz >= 15)
    {
        K = 925;
        SetReg(49, 0x10); //VCO_GAIN, RSEL, BWSEL
    }
    else if(fpfdMHz >= 8 && fpfdMHz < 15)
    {
        K = 325;
        SetReg(49, 0x15);
    }
    else if(fpfdMHz >= 5 && fpfdMHz < 8)
    {
        K = 185;
        SetReg(49, 0x1E);
    }
    else
    {
        return;
    }
    SetReg(51, 0x07); // MS_PEC[2:0]

    unsigned int PLL_KPHI = round( (1.51 * K)/fpfdMHz );
    SetReg( 48, PLL_KPHI );

    //feedback multisynth
    unsigned int MSN_P1 = floor( 281600/fpfdMHz) - 512;
    SetReg(99, ( (MSN_P1 >> 16) & 0x03  ) );
    SetReg(98, ( (MSN_P1 >> 8) & 0xFF  ) );
    SetReg(97, (MSN_P1 & 0xFF  ));

    unsigned int MSN_P2 = floor( pow(10, 9) * (281600/fpfdMHz - MSN_P1 - 512) );
    MSN_P2 = MSN_P2 << 2;
    SetReg(102, (MSN_P2 >> 24));
    SetReg(101, (MSN_P2 >> 16) & 0xFF);
    SetReg(100, (MSN_P2 >> 8) & 0xFF);
    SetReg(99, MSN_P2 & 0xFC);

    unsigned int MSN_P3 = pow(10, 9);
    SetReg(106, (MSN_P3 >> 24) & 0x3F);
    SetReg(105, (MSN_P3 >> 16) & 0xFF);
    SetReg(104, (MSN_P3 >> 8) & 0xFF);
    SetReg(103, MSN_P3 & 0xFF);

    //Configuring output driver
    //enabling clocks

    unsigned int MSx_P1 = floor( (281600/freqMHz) - 512 );
    unsigned int MSx_P2 = floor( pow(10, 9) * ( 281600/freqMHz - MSx_P1 - 512 ));
    unsigned int MSx_P3 = 0x01;

    unsigned int MSx_P1addr = 53;

    switch(clkID)
    {
    case 0:
        MSx_P1addr = 53;
        break;
    case 1:
        MSx_P1addr = 64;
        break;
    case 2:
        MSx_P1addr = 75;
        break;
    case 3:
        MSx_P1addr = 86;
        break;
    default:
        MSx_P1addr = 53;
    }

    SetReg( MSx_P1addr, MSx_P1 & 0xFF);
    SetReg( MSx_P1addr+1, (MSx_P1 >> 8) & 0xFF);
    SetReg( MSx_P1addr+2, (MSx_P1 >> 16) & 0x03);

    MSx_P2 = MSx_P2 << 2;
    SetReg( MSx_P1addr+2, (MSx_P2 & 0xFC) | ((MSx_P1 >> 16) & 0x03));
    SetReg( MSx_P1addr+3, (MSx_P2 >> 8) & 0xFF);
    SetReg( MSx_P1addr+4, (MSx_P2 >> 16) & 0xFF);
    SetReg( MSx_P1addr+5, (MSx_P2 >> 24) & 0xFF);

    SetReg( MSx_P1addr+6, MSx_P3 & 0xFF);
    SetReg( MSx_P1addr+7, (MSx_P3 >> 8) & 0xFF);
    SetReg( MSx_P1addr+8, (MSx_P3 >> 16) & 0xFF);
    SetReg( MSx_P1addr+9, (MSx_P3 >> 24) & 0x3F);
}

/** @brief Sets clock inversions
    @param clkID clock id
    @param inversion
        - 0 : no inversion
        - 1 : invert even
        - 2 : invert odd
        - 3 : invert both
*/
void Si5356A::SetInvertClock(unsigned int clkID, unsigned int inversion)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 36;
        break;
    case 1:
        addr = 37;
        break;
    case 2:
        addr = 38;
        break;
    case 3:
        addr = 39;
        break;
    default:
        addr = 36;
    }
    val = GetReg(addr);
    val = val & 0x07;
    val |= (inversion << 3);
    SetReg(addr, val);
}

/** @brief Power up clocks by id
    @param clkID clock id
    @param powered power up clock
*/
void Si5356A::PowerUpClock(unsigned int clkID, bool powered)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 31;
        break;
    case 1:
        addr = 32;
        break;
    case 2:
        addr = 33;
        break;
    case 3:
        addr = 34;
        break;
    default:
        addr = 31;
    }
    val = GetReg(addr);
    val = val & 0xFC;
    val |= !powered;
    val |= (!powered) << 1;
    SetReg(addr, val);
}

/** @brief Enables clocks by id
    @param clkID click id
    @param enabled enable clock
*/
void Si5356A::EnableClock(unsigned int clkID, bool enabled)
{
    unsigned char val = 0;
    int addr = 230;
    unsigned char param = !enabled;
    param = param << (clkID);
    unsigned char mask = ~(1 << (clkID));

    val = GetReg(addr);
    val = val & mask;
    val |= param;
    SetReg(addr, val);
}

/** @brief Sets clock output format
    @param clkID clock id
    @param enabled
        - 0 : reserved
        - 1 : even=on, odd=off
        - 2 : even=off, odd=on
        - 3 : even=on, odd=on
*/
void Si5356A::SetOutputFormat(unsigned int clkID, unsigned int format)
{
    unsigned char val = 0;
    int addr = 0;
    switch(clkID)
    {
    case 0:
        addr = 36;
        break;
    case 1:
        addr = 37;
        break;
    case 2:
        addr = 38;
        break;
    case 3:
        addr = 39;
        break;
    default:
        addr = 36;
    }
    val = GetReg(addr);
    val = val & 0xF8;
    val |= format;
    SetReg(addr, val);
}

/** @brief Set reference clock input type
    @param CLKIN true when CLKIN, false when crystal
*/
void Si5356A::SetRefClockInput(bool CLKIN)
{
    m_inputCLKIN = CLKIN;
}

/** @brief Selects crystal frequency
    @param freqID
        - 0 : 25 MHz
        - 1 : 27 MHz
*/
void Si5356A::SetCrystalFreq(unsigned int freqID)
{
    m_crystalFreq = freqID;
}

/** @brief Returns value from registers list
    @param addr register address
    @return register value
*/
unsigned char Si5356A::GetReg(unsigned int addr)
{
    Reg_Data reg;
    reg = Reg_Store[addr];
    return reg.Reg_Val;
}

/** @brief Sets value in registers list
    @param addr register address
    @param Value register value
*/
void Si5356A::SetReg(unsigned int addr, unsigned char Value)
{
    Reg_Data reg;
    reg = Reg_Store[addr];
    reg.Reg_Val = Value;

    Reg_Store[addr] = reg;
}
