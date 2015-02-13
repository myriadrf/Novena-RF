/**
@file   Si5356A.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for configuring Si5356A synthesizer
*/
#ifndef SI5356A_MODULE_H
#define SI5356A_MODULE_H

typedef struct Reg_Data{
   unsigned char Reg_Addr;
   unsigned char Reg_Val;
   unsigned char Reg_Mask;
} Reg_Data;

class ConnectionManager;

class Si5356A
{
public:
	Si5356A();
	~Si5356A();
	void Initialize(ConnectionManager *mng);
	bool LoadRegValuesFromFile(const char *FName);
	void SetInvertClock(unsigned int clkID, unsigned int inversion);
	void PowerUpClock(unsigned int clkID, bool powered);
	void EnableClock(unsigned int clkID, bool enabled);
	void SetOutputFormat(unsigned int clkID, unsigned int format);
	void SetFrequency(unsigned int clkID, float refClkMHz, float clkMHz);
	void SetRefClockInput(bool CLKIN);
	void SetCrystalFreq(unsigned int freqID);
	bool ConfigureSi5356A();
	void LmsRead();

private:
    unsigned char GetReg(unsigned int addr);
    void SetReg(unsigned int addr, unsigned char Value);
    ConnectionManager *device;
	bool m_inputCLKIN;
	unsigned int m_crystalFreq;
	float freqMHz;
	float fpfdMHz;

	unsigned int DRVA_INV;
	unsigned int DRVB_INV;
	unsigned int DRVC_INV;
	unsigned int DRVD_INV;

	unsigned int DRVA_FMT;
	unsigned int DRVB_FMT;
	unsigned int DRVC_FMT;
	unsigned int DRVD_FMT;
};

#endif // SI5356A_MODULE_H
