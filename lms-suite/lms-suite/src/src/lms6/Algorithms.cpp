/**
@file   Algorithms.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Procedures used for calibrating and tuning operations
*/

#include "Algorithms.h"
#include <string>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include "LMS6002_MainControl.h"
#include "ConnectionManager.h"
#include "MessageLog.h"
#include "LMS_Parameter.h"

using namespace std;
namespace lms6
{

/** @brief Creates calibration algorithms module with given control module
    @param pControl LMS6002 main control module

    pControl will be used to write and read parameters from the chip
*/
Algorithms::Algorithms(LMS6002_MainControl *pControl)
{
    lmsControl = pControl;
    if(lmsControl == NULL)
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
}

Algorithms::~Algorithms()
{
}

int Algorithms::CapAutoTune_S(const bool Rx)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return 0;
    }
    stringstream ss;
	int iInitialCap;
	int iCl = 0;
	int iCh = 0;
	int CapState;
	int Result;
	string Str;

	// ------ Algorithm. Begin. -----------------------------------------------------
	// Read VTUNE_H and VTUNE_L
	CapState = GetVTuneState(Rx);
	iInitialCap = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
	Result = 0;

	switch (CapState)
	{
		// VTUNE_H, VTUNE_L, Value
		// 0        0      0x00
	case 0x00:
		Result = 0x10;
		// Decrement Cap until H=1, L=0
		if (!CapDecrement(Rx, 0x02))
		{
			Result += 0x02;
		};
		iCh = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		// Go to initial value for speeding things up.
		lmsControl->SetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, iInitialCap);
		// Increment Cap until H=0, L=1
		if (!CapIncrement(Rx, 0x01))
		{
			Result += 0x01;
		};
		iCl = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		break;

		// VTUNE_H, VTUNE_L, Value
		// 0        1      0x01
	case 0x01:
		Result = 0x20;
		// Decrement Cap until H=0, L=0
		if (!CapDecrement(Rx, 0x00))
		{
			Result += 0x04;
		};
		iCl = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		// Decrement Cap until H=1, L=0
		if (!CapDecrement(Rx, 0x02))
		{
			Result += 0x02;
		};
		iCh = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        0      0x02
	case 0x02:
		Result = 0x30;
		// Increment Cap until H=0, L=0
		if (!CapIncrement(Rx, 0x00))
		{
			Result += 0x04;
		};
		iCh = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		// Increment Cap until H=0, L=1
		if (!CapIncrement(Rx, 0x01))
		{
			Result += 0x01;
		};
		iCl = lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, true, true);
		break;

		// VTUNE_H, VTUNE_L, Value
		// 1        1      0x03 (ERROR)
	default:
		Result = 7;
	};

	if (Result != 7) // Values are OK, calculate new Cap Value
	{
		lmsControl->SetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, ((int)(((2.0 - 2.5)*(iCh - iCl) / (2.5 - 0.5)) + iCh + 0.5)));
	}
	else // Error occuread. Set Cap Value to initial.
	{
		lmsControl->SetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL, iInitialCap);
	};

	// ------ Algorithm. End. -------------------------------------------------------
	if ((Result == 0x10) || (Result == 0x20) || (Result == 0x30))
	{
		char ctemp[20];
		MessageLog::getInstance()->write("VCO Cap Tuning successful.\n");
		Str = "Cap value for Vtuning 0.5V = ";
		sprintf(ctemp, "%i\n", iCl);
		Str += ctemp;
		//MessageLog::getInstance()->write(Str);
		Str += "Cap value for Vtuning 2.5V = ";
		sprintf(ctemp, "%i\n", iCh);
		Str += ctemp;
		//MessageLog::getInstance()->write(Str);
		Str += "Selected Cap value for Vtuning 1.5V = ";
		sprintf(ctemp, "%li\n", lmsControl->GetParam(Rx?VCOCAP_RXPLL:VCOCAP_TXPLL));
		Str += ctemp;
		//MessageLog::getInstance()->write(Str);
		Str += "Initial Cap value was = ";
		sprintf(ctemp, "%i\n", iInitialCap);
		Str += ctemp;
		MessageLog::getInstance()->write(Str);
	}
	else
	{
		char ctemp[20];
		if (Result == 7)
		{
			MessageLog::getInstance()->write("VCO Cap Tuning UNSUCCESSFUL.\n");
			Str = "Initial Cap value = ";
			sprintf(ctemp, "%i\n", iInitialCap);
			Str += ctemp;
			Str += "Initial comparator value: VTUNE_L = 1; VTUNE_H = 1.\n";
			MessageLog::getInstance()->write(Str);
			MessageLog::getInstance()->write("Check please SPI cable, connecion etc.\n");
		}
		else
		{
			MessageLog::getInstance()->write("VCO Cap Tuning ISSUES.\n");
			Str = "Initial Cap value = ";
			sprintf(ctemp, "%i\n", iInitialCap);
			Str += ctemp;
			Str += "Initial comparator value: \n";
			if (CapState == 0x00)
				Str += "VTUNE_L = 0; VTUNE_H = 0.\n";
			else if (CapState == 0x01)
				Str += "VTUNE_L = 0; VTUNE_H = 1.\n";
			else if (CapState == 0x02)
				Str += "VTUNE_L = 1; VTUNE_H = 0.\n";
			else
				Str += "VTUNE_L = 1; VTUNE_H = 1.\n";
			MessageLog::getInstance()->write(Str);

			if ((Result & 0x01) == 0x01)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 1; VTUNE_H = 0.\n";
				MessageLog::getInstance()->write(Str);
			};
			if ((Result & 0x02) == 0x02)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 0; VTUNE_H = 1.\n";
				MessageLog::getInstance()->write(Str);
			};
			if ((Result & 0x04) == 0x04)
			{
				Str = "Issue: Can not reach state, where VTUNE_L = 0; VTUNE_H = 0.\n";
				MessageLog::getInstance()->write(Str);
			};
		};
	};
	return Result;
}

bool Algorithms::CapIncrement(const bool Rx, int UntilState)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return 0;
    }
    bool bContinue;
	int CurrentState;
    int vcoCapIndex = lmsControl->GetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, true);
	//MessageLog::getInstance()->write("=== Start CAP Incrementing ===\n");
	bContinue = true;
	do
	{
		stringstream Str;
		Str << "State = ";
		CurrentState = GetVTuneState(Rx);
		Str << CurrentState;
		vcoCapIndex = lmsControl->GetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, true);
		if ((CurrentState != UntilState) && ( vcoCapIndex < 63))
		{
			++vcoCapIndex;
			lmsControl->SetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, vcoCapIndex);
		}
		else
		{
			bContinue = false;
		};
		Str << "; CAP = ";
		Str << vcoCapIndex << endl;

		//MessageLog::getInstance()->write(Str.str());
	}
	while (bContinue);

	//MessageLog::getInstance()->write("=== Stop CAP Incrementing ===\n");
	if (CurrentState == UntilState)
		return true;
	else
		return false;
}

bool Algorithms::CapDecrement(const bool Rx, int UntilState)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return 0;
    }
    bool bContinue;
	int CurrentState;
    int vcoCapIndex = lmsControl->GetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, true);
	//MessageLog::getInstance()->write("=== Start CAP Decrementing ===");
	bContinue = true;
	do
	{
		stringstream Str;
		Str << "State = ";
		CurrentState = GetVTuneState(Rx);
		Str << CurrentState;
		vcoCapIndex = lmsControl->GetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, true);
		if ((CurrentState != UntilState) && ( vcoCapIndex > 0))
		{
			--vcoCapIndex;
			lmsControl->SetParam(Rx? VCOCAP_RXPLL:VCOCAP_TXPLL, vcoCapIndex);
		}
		else
		{
			bContinue = false;
		};
		Str << "; CAP = ";
		Str << vcoCapIndex << endl;

        //MessageLog::getInstance()->write(Str.str());
	}
	while (bContinue);

	//MessageLog::getInstance()->write("=== Stop CAP Decrementing ===\n");

	if (CurrentState == UntilState)
		return true;
	else
		return false;
}

// ---------------------------------------------------------------------------
// Enables VCO TUNE comparators
// Selects required VCO and CAP
// Returns VCO TUNE comparator values
// ---------------------------------------------------------------------------
/** @brief Returns VCO TUNE comparator values
    @param Rx true for receiver, false for transmitter
    @return VTUNE values
*/
int Algorithms::GetVTuneState(const bool Rx)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return 0;
    }
    int rez = 0;
	if ( lmsControl->GetParam(Rx ? VTUNE_H_RXPLL : VTUNE_H_TXPLL, true, true) )
		rez = rez | 0x02;

	if (lmsControl->GetParam(Rx ? VTUNE_L_RXPLL : VTUNE_L_TXPLL)) //got updated during VTUNE_H reading
		rez = rez | 0x01;
	return rez;
}

/** @brief Resets DC calibration for selected module
    @param module LM6002 module enumeration
*/
void Algorithms::DCResetCalibration(LMS_MODULE module)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    LMS_Parameter dc_addr = DC_ADDR_TOP;
    switch(module)
    {
    case TOP:
        dc_addr = DC_ADDR_TOP;
        break;
    case TXLPF:
        dc_addr = DC_ADDR_TXLPF;
        break;
    case RXLPF:
        dc_addr = DC_ADDR_RXLPF;
        break;
    case RXVGA2:
        dc_addr = DC_ADDR_RXVGA2;
        break;
    default:
        return;
    }
    char btmp;
    unsigned spiAdr = getModuleAddress(module)+3;
    unsigned value = 0;
	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x00; // Set Reset Active
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = lmsControl->GetParam(dc_addr, true, true);
	value |= btmp;

    lmsControl->getSerPort()->mSPI_write(spiAdr, value);

	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x00; // Set Load Value Inactive
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = lmsControl->GetParam(dc_addr, true, true);
	value |= btmp;

	lmsControl->getSerPort()->mSPI_write(spiAdr, value);
}

/** @brief Loads DC calibration value for selected module from it's DC_CNTVAL register
    @param module LMS6002 module enumeration
*/
void Algorithms::DCLoadValues(LMS_MODULE module)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    LMS_Parameter dc_addr = DC_ADDR_TOP;
    switch(module)
    {
    case TOP:
        dc_addr = DC_ADDR_TOP;
        lmsControl->EnableSPIClocksByMask(0x20);
        break;
    case TXLPF:
        dc_addr = DC_ADDR_TXLPF;
        lmsControl->EnableSPIClocksByMask(0x22);
        break;
    case RXLPF:
        dc_addr = DC_ADDR_RXLPF;
        lmsControl->EnableSPIClocksByMask(0x28);
        break;
    case RXVGA2:
        dc_addr = DC_ADDR_RXVGA2;
        lmsControl->EnableSPIClocksByMask(0x30);
        break;
    default:
        return;
    }
	char btmp;

    unsigned spiAdr = getModuleAddress(module)+3;
	unsigned value = 0;
	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x01; // Load Value
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = lmsControl->GetParam(dc_addr, true, true);
	value |= btmp;

	lmsControl->getSerPort()->mSPI_write(spiAdr, value);

	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_START_CLBR
	btmp = 0x00; // Set Start Calibration Inactive
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x00; // Deactivate Load Value
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = lmsControl->GetParam(dc_addr, true, true);
	value |= btmp;

	lmsControl->getSerPort()->mSPI_write(spiAdr, value);
	lmsControl->RestoreAllSPIClocks();
}

/** @brief Start DC calibration procedure for selected module
    @param module LMS6002 module enumeration
*/
void Algorithms::DCStartCalibration(LMS_MODULE module)
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    LMS_Parameter dc_addr = DC_ADDR_TOP;
    switch(module)
    {
    case TOP:
        dc_addr = DC_ADDR_TOP;
        lmsControl->EnableSPIClocksByMask(0x20);
        break;
    case TXLPF:
        dc_addr = DC_ADDR_TXLPF;
        lmsControl->EnableSPIClocksByMask(0x22);
        break;
    case RXLPF:
        dc_addr = DC_ADDR_RXLPF;
        lmsControl->EnableSPIClocksByMask(0x28);
        break;
    case RXVGA2:
        dc_addr = DC_ADDR_RXVGA2;
        lmsControl->EnableSPIClocksByMask(0x30);
        break;
    default:
        return;
    }

    unsigned spiAdr = getModuleAddress(module)+3;
    unsigned value = 0;
	unsigned Addr = lmsControl->GetParam(dc_addr, true, true);
	char btmp;
	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_LOAD
	btmp = 0x01; // Start Calibration
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x00; // Load Value Inactive
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	value |= btmp;

	lmsControl->getSerPort()->mSPI_write(spiAdr, value);

	// ======= register addr 0x03 =======
	value = 0x00;
	// DC_LOAD
	btmp = 0x00; // Deactivate Start Calibration
	btmp = btmp << 5;
	value |= btmp;
	// DC_LOAD
	btmp = 0x00; // Load Value Inactive
	btmp = btmp << 4;
	value |= btmp;
	// DC_SRESET
	btmp = 0x01; // Set Reset Inactive
	btmp = btmp << 3;
	value |= btmp;
	// DC_ADDR
	btmp = (char)Addr;
	value |= btmp;

	lmsControl->getSerPort()->mSPI_write(spiAdr, value);
	lmsControl->RestoreAllSPIClocks();
}

/**	@brief Performs transmitter calibration.
*/
void Algorithms::CalibrateTx()
{
    MessageLog::getInstance()->write("Tx Calibration started\n", LOG_INFO);
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    if(!lmsControl->getSerPort()->IsOpen())
    {
        MessageLog::getInstance()->write("Board not connected\n", LOG_WARNING);
        return;
    }

	int iTryDone, iTryComplete;
	char cTmp;

	// Enable TxLPF DC CAL Clock
	lmsControl->EnableSPIClocksByMask(0x02);

	// Set I Channel DC Calibration chain
	lmsControl->SetParam(DC_ADDR_TXLPF, 0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(TXLPF);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_TXLPF, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("TXLPF I Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_TXLPF, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("TXLPF I Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "TXLPF I Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// Q Channel
	lmsControl->SetParam(DC_ADDR_TXLPF, 1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(TXLPF);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_TXLPF, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("TXLPF Q Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_TXLPF, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("TXLPF Q Lock OK\n", LOG_INFO);
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "TXLPF Q Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	lmsControl->RestoreAllSPIClocks();
	MessageLog::getInstance()->write("Tx Calibration Done\n");
}


/** @brief Performs receiver calibration.
*/
void Algorithms::CalibrateRx()
{
    MessageLog::getInstance()->write("Rx Calibration started\n", LOG_INFO);
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    if(!lmsControl->getSerPort()->IsOpen())
    {
        MessageLog::getInstance()->write("Board not connected\n", LOG_WARNING);
        return;
    }

	int iTryDone, iTryComplete;
	char cTmp;
	int iRxVGA2Gain_ind;

	// =================== Remember RxVGA2 gain =====================================
	iRxVGA2Gain_ind = lmsControl->GetParam(VGA2GAIN_RXVGA2, true, true);

	// =================== Set RxVGA2 gain to 30dB ==================================
	lmsControl->SetParam(VGA2GAIN_RXVGA2, 10);

	// =================== Rx LPF DC Calibration Begin ==============================

	// Enable RxLPF DC CAL Clock
	lmsControl->EnableSPIClocksByMask(0x08);

	// Set I Channel DC Calibration chain
	lmsControl->SetParam(DC_ADDR_RXLPF, 0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXLPF);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXLPF, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxLPF I Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXLPF, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxLPF I Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RXLPF I Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// Q Channel
	lmsControl->SetParam(DC_ADDR_RXLPF, 1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXLPF);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXLPF, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxLPF Q Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXLPF, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
            MessageLog::getInstance()->write("RxLPF Q Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RXLPF Q Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// Restore all SPI Clokcs
	lmsControl->RestoreAllSPIClocks();
	// =================== Rx LPF DC Calibration End ================================

	// =================== Rx VGA2 DC Calibration Begin =============================

	// Enable RxVGA2 DC CAL Clock
	lmsControl->EnableSPIClocksByMask(0x10);

	// REF Channel
	lmsControl->SetParam(DC_ADDR_RXVGA2, 0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
        DCStartCalibration(RXVGA2);
		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxVGA2 REF Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXVGA2, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxVGA2 REF Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RxVGA2 REF Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	lmsControl->SetParam(DECODE_RXVGA2, 1);
	lmsControl->SetParam(VGA2GAINB, 0);
	lmsControl->SetParam(VGA2GAINA, 6);

	// dc2a_vga2_i Channel
	lmsControl->SetParam(DC_ADDR_RXVGA2, 1);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXVGA2);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxVGA2 DC2A_I Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXVGA2, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxVGA2 DC2A_I Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RxVGA2 DC2A_I Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// dc2a_vga2_q Channel
	lmsControl->SetParam(DC_ADDR_RXVGA2, 2);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXVGA2);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxVGA2 DC2A_Q Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXVGA2, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxVGA2 DC2A_Q Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RxVGA2 DC2A_Q Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

    lmsControl->SetParam(VGA2GAINB, 6);
	lmsControl->SetParam(VGA2GAINA, 0);

	// dc2b_vga2_i Channel
	lmsControl->SetParam(DC_ADDR_RXVGA2, 3);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXVGA2);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxVGA2 DC2B_I Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXVGA2, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxVGA2 DC2B_I Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RxVGA2 DC2B_I Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// dc2b_vga2_q Channel
	lmsControl->SetParam(DC_ADDR_RXVGA2, 4);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
		DCStartCalibration(RXVGA2);

		// Wait for calibration to complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("RxVGA2 DC2B_Q Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_RXVGA2, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("RxVGA2 DC2B_Q Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "RxVGA2 DC2B_Q Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

    lmsControl->SetParam(DECODE_RXVGA2, 0);
	// Restore all SPI Clokcs
	lmsControl->RestoreAllSPIClocks();

	// =================== Restore RxVGA2 gain =====================================
	lmsControl->SetParam(VGA2GAIN_RXVGA2, iRxVGA2Gain_ind);
	// =================== Rx VGA2 DC Calibration End ===============================
	MessageLog::getInstance()->write("RxLPF and RxVGA2 Calibration Done\n");
}

/**	@brief Calibration of LPF CAL CORE.
*/
void Algorithms::CalibrateLPFCore()
{
    MessageLog::getInstance()->write("LPF Core calibration started\n", LOG_INFO);
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module\n", LOG_ERROR);
        return;
    }
    if(!lmsControl->getSerPort()->IsOpen())
    {
        MessageLog::getInstance()->write("Board not connected\n", LOG_WARNING);
        return;
    }

	int iDCCalValue, iLPFCALValue;
	int iTryDone, iTryComplete;
	int iLPFTuningClockInd;
	char cTmp;
	bool bPD_CLKLPFCAL = lmsControl->GetParam(PD_CLKLPFCAL); // remember Divide TxPLL freq by 8 setting
	bool bSoftTx = lmsControl->GetParam(STXEN);

	// =========== I. TOP SPI DC Calibration for CAL Core LPF =====================
	// Steps:
	// 1. Turn off module power supplies in TopSPI;
	// 2. Perform calibration in chain address 0;
	// 3. Read DC Calibration value from DC CAlibration chain number 0 into iDCCalValue variable;
	// 4. Turn on module power supplies in TopSPI;

	// =========== Step 1 =========================================================
	// m_TopModule->CustSet_TopPowerON(false);

	// =========== Step 2 =========================================================
	// Set 0 address DC Calibration chain
	lmsControl->SetParam(DC_ADDR_TOP, 0);
	iTryComplete = 5;

	do
	{
		iTryComplete--;
		iTryDone = 5;
		// Start calibration
        DCStartCalibration(TOP);
		// Wait for calibration complete
		do
		{
			iTryDone--;
			cTmp = lmsControl->GetParam(DC_CLBR_DONE_TOP, true, true);
			if (cTmp == 0)
			{
				MessageLog::getInstance()->write("DC Channel Done OK\n");
				break;
			};
		}
		while (iTryDone);

		// Check Lock status
		cTmp = lmsControl->GetParam(DC_LOCK_TOP, true, true);
		if ((cTmp == 0x05) || (cTmp == 0x02))
		{
			MessageLog::getInstance()->write("DC Channel Lock OK\n");
			break;
		};
		char ctemp[64];
		sprintf(ctemp, "DC Channel Lock %0X\n", cTmp);
		MessageLog::getInstance()->write(ctemp);
	}
	while (iTryComplete);

	// =========== Step 3 =========================================================
	// iDCCalValue = m_TopModule->GetCalVal(0);

	// =========== Step 4 =========================================================
	// m_TopModule->CustSet_TopPowerON(true);

	// ========== II. LPF CAL Core Calibration in TOP SPI =========================
	// Steps:
	// 1. Set 2.5MHz in "LPF Bandwidth:" control in TopSPI;
	// 2. Enable RxPLL SPI Clock in TopSPI;
	// 2.a) Get "LPF Tuning Clock" index;
	// 2.b) If RefCLK != 40MHz, Set "LPF Tuning Clock" index to 0; Enable Soft TX;
	// 2.c) If RefCLK != 40MHz, Set TxPLL for 320MHz;
	// 2.d) If RefCLK != 40MHz, Divide TxPLL freq by 8;
	// 3. Set "Enable LPFCAL" (check) in TopSPI;
	// 4. Toggle "Reset LPFCAL" checkbox (check and uncheck) in TopSPI;
	// 5. Read LPFCAL value from TopSPI into variable .......;
	// 6. Unset "Enable LPFCAL" (uncheck) in TopSPI;
	// 7. Restore Clock Enables in TopSPI
	// 7.a) If RefCLK != 40MHz, Restore Divide TxPLL freq by 8 settings;
	// 7.b) If RefCLK != 40MHz, Restore "LPF Tuning Clock" index;
	// 7.c) If RefCLK != 40MHz, Restore TxPLL settings; Restore SoftTX Enable;

	// =========== Step 1 =========================================================
    lmsControl->SetParam(BWC_LPFCAL, 9);
	// =========== Step 2 =========================================================
    lmsControl->EnableSPIClocksByMask(0xff);

	// =========== Step 2.a) ======================================================
	iLPFTuningClockInd = lmsControl->GetParam(CLKSEL_LPFCAL, true, true);

	// =========== Step 2.b) ======================================================
	//if (m_TxPLLModule->GetRefClk() != 40000000)
	if(lmsControl->GetReferenceFrequency(false)*1000000 != 40000000 )
	{
		lmsControl->SetParam(CLKSEL_LPFCAL, 0);
		// Enable SoftTX
		bSoftTx = lmsControl->GetParam(STXEN, true, true);
		lmsControl->SetParam(STXEN, 1);
	};

	// =========== Step 2.c) ======================================================
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
		SetPLLTo320MHz();

	// =========== Step 2.d) ======================================================
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
		bPD_CLKLPFCAL = lmsControl->GetParam(PD_CLKLPFCAL, true, true);
	//if (m_TxPLLModule->GetRefClk() != 40000000)
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
		lmsControl->SetParam(PD_CLKLPFCAL, 0);

	// =========== Step 3 =========================================================
	lmsControl->SetParam(EN_CAL_LPFCAL, true);

	// =========== Step 4 =========================================================
	lmsControl->SetParam(RST_CAL_LPFCAL, 1);
	lmsControl->SetParam(RST_CAL_LPFCAL, 0);

	// =========== Step 5 =========================================================
	iDCCalValue = lmsControl->GetParam(DC_REGVAL_TOP, true, true);
    iLPFCALValue = lmsControl->GetParam(RCCAL_LPFCAL, true, true);
	// =========== Step 6 =========================================================
	lmsControl->SetParam(EN_CAL_LPFCAL, false);

	// =========== Step 7 =========================================================
	lmsControl->RestoreAllSPIClocks();

	// =========== Step 7.a) ======================================================
	//if (m_TxPLLModule->GetRefClk() != 40000000)
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
		lmsControl->SetParam(PD_CLKLPFCAL, bPD_CLKLPFCAL);

	// =========== Step 7.b) ======================================================
	//if (m_TxPLLModule->GetRefClk() != 40000000)
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
		lmsControl->SetParam(CLKSEL_LPFCAL, iLPFTuningClockInd);

	// =========== Step 7.c) ======================================================
	//if (m_TxPLLModule->GetRefClk() != 40000000)
	if (lmsControl->GetReferenceFrequency(false)*1000000 != 40000000)
	{
		RestoreAfterSetPLLTo320MHz();
		// Restore SoftTX Enable
		lmsControl->SetParam(STXEN, bSoftTx);
	};

	// ========= III. Write Calibration Values to Tx and Rx LPFs ==================
	// Steps:
	// 1. Enable All SPI Clocks in TopSPI;
	// 2. Write "DC Offset Resistor" value to the RxLPF;
	// 3. Write "From TRX_LPF_CAL" value to the RxLPF;
	// 4. Write "DC Offset Resistor" value to the TxLPF;
	// 5. Write "From TRX_LPF_CAL" value to the TxLPF;
	// 6. Restore All SPI Clocks in TopSPI.

	// =========== Step 1 =========================================================
	lmsControl->EnableSPIClocksByMask(0xff);

	// =========== Step 2 =========================================================
	lmsControl->SetParam(DCO_DACCAL_RXLPF, iDCCalValue);

	// =========== Step 3 =========================================================
	lmsControl->SetParam(RCCAL_LPF_RXLPF, iLPFCALValue);

	// =========== Step 4 =========================================================
	lmsControl->SetParam(DCO_DACCAL_TXLPF, iDCCalValue);

	// =========== Step 5 =========================================================
	lmsControl->SetParam(RCCAL_LPF_TXLPF, iLPFCALValue);

	// =========== Step 6 =========================================================
	lmsControl->RestoreAllSPIClocks();

	MessageLog::getInstance()->write("LPF Core Calibration Done\n");
}

/** @brief Sets PLL to 320 MHz frequency and stores previous settings into memory
*/
void Algorithms::SetPLLTo320MHz()
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    m_F320M_Data.F320M_rgrDecode = lmsControl->GetParam(DECODE_TXPLL);
	m_F320M_Data.F320M_chbPwrPllMods = lmsControl->GetParam(EN_TXPLL);
	m_F320M_Data.F320M_rgrMODE = lmsControl->GetParam(MODE_TXPLL);
	m_F320M_Data.F320M_cmbVCOCAP = lmsControl->GetParam(VCOCAP_TXPLL);
	m_F320M_Data.F320M_rgrSELVCO = lmsControl->GetParam(SELVCO_TXPLL);
	m_F320M_Data.F320M_rgrFRANGE = lmsControl->GetParam(FRANGE_TXPLL);
	m_F320M_Data.F320M_DesFreq_MHz = lmsControl->GetFrequency(false);

	lmsControl->SetParam(DECODE_TXPLL, 0);
	lmsControl->SetParam(EN_TXPLL, 1);
	lmsControl->SetParam(MODE_TXPLL, 0);
	double realFreq, vcoFreq;
	unsigned a, b, c;
	int div;
	lmsControl->SetFrequency(false, 320, realFreq, a, b, c, vcoFreq, div);
	lmsControl->Tune(false);
}

/** @brief Restores PLL Settings to values saves when setting to 320 MHz
*/
void Algorithms::RestoreAfterSetPLLTo320MHz()
{
    if(lmsControl == NULL)
    {
        MessageLog::getInstance()->write("Algorithms have no assigned control module", LOG_ERROR);
        return;
    }
    double realFreq, vcoFreq;
	unsigned a, b, c;
	int div;
	lmsControl->SetFrequency(false, m_F320M_Data.F320M_DesFreq_MHz, realFreq, a, b, c, vcoFreq, div);
	lmsControl->SetParam(DECODE_TXPLL, m_F320M_Data.F320M_rgrDecode);
	lmsControl->SetParam(EN_TXPLL, m_F320M_Data.F320M_chbPwrPllMods);
	lmsControl->SetParam(MODE_TXPLL, m_F320M_Data.F320M_rgrMODE);
	lmsControl->SetParam(VCOCAP_TXPLL, m_F320M_Data.F320M_cmbVCOCAP);
	lmsControl->SetParam(SELVCO_TXPLL, m_F320M_Data.F320M_rgrSELVCO);
	lmsControl->SetParam(FRANGE_TXPLL, m_F320M_Data.F320M_rgrFRANGE);
}

}
