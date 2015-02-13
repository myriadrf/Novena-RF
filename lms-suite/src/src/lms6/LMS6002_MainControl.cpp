/**
@file   LMS6002_MainControl.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Main functions for controlling LMS6002 chip
*/

#include "LMS6002_MainControl.h"
#include "ConnectionManager.h"
#include "RegistersMap.h"
#include "Algorithms.h"
//#include "MessageLog.h"
#include "CommonUtilities.h"
#include <math.h>
#include <sstream>
#include <iomanip>
#include "iniParser.h"
#include "Si5351C.h"
#include "Si5356A.h"
#include "ADF_module.h"
using namespace std;
namespace lms6
{

/** @brief changes index value to SELVCO acctual value
    @param i index
    (0:all powered down, 1:lowFreq, 2:midLowFreq, 3:midHighFreq, 4:highFreq)
    (0:all powered down, 1:Fvco/2, 2:Fvco/4, 3:Fvco/8, 4:Fvco/16)
    @return SELVCO value
*/
int indexToSELVCO_FRANGE(int i)
{
    switch(i)
    {
    case 0:
        return 0;
    case 1:
        return 4;
    case 2:
        return 5;
    case 3:
        return 6;
    case 4:
        return 7;
    default:
        return 0;
    }
}

/** @brief Changes SELVCO and FRANGE values to index value
    @param value SELVCO or FRANGE value
    @return index
*/
int SELVCO_FRANGE_ToIndex(int value)
{
    switch(value)
    {
    case 0:
        return 0;
    case 4:
        return 1;
    case 5:
        return 2;
    case 6:
        return 3;
    case 7:
        return 4;
    default:
        return 0;
    }
}

/** @brief Handles incoming messages
    @param msg message about event
*/
void LMS6002_MainControl::HandleMessage(const LMS_Message &msg)
{
    //currently just relay all incoming messages to main control listeners
    if(msg.type == MSG_REGISTER_TEST)
    {
        //MessageLog::getInstance()->write(msg.text, LOG_INFO);
    }
    Notify(msg);
}

/** @brief Creates and initializes control modules and registers map
*/
LMS6002_MainControl::LMS6002_MainControl(ConnectionManager* serPort)
{
    if(serPort == NULL)
        printf("LMS6002 MainControl: connection manager is NULL\n");
    m_device = serPort;
    m_GPIO = 0;
    algorithms = new Algorithms(this);
    //default reference frequency
    m_FreqRx_MHz = 2199;
    m_FreqTx_MHz = 2200;
    m_registersMap = new RegistersMap(m_device);

    Initialize();
    LoadAdditionalSettings();

    //listen for events from device manager
    m_device->RegisterForNotifications(this);
}

/** @brief Initializes control modules
*/
void LMS6002_MainControl::Initialize()
{
    LMS_Message msg;
    msg.text = "LMS6002 Main control initialized\n";
    msg.type = MSG_INFO;
    Notify(msg);
}

/** @brief Deletes all control modules
*/
LMS6002_MainControl::~LMS6002_MainControl()
{
    m_device->UnregisterFromNotifications(this);
    delete algorithms;
    delete m_device;
}

/** @brief Loads register values from file
    @param filename file to load
    @return true if success
*/
bool LMS6002_MainControl::LoadFromFile(const char *filename)
{
    bool status = false;
    bool loadFromBinary = false;
    char temp[128];
    ifstream fin;
    fin.open(filename, ios::in | ios::binary);

    memset(temp,0,128);
    fin.read( temp, 7);
    if(strcmp(temp, "LMS6002") == 0) //check if file type is binary
        loadFromBinary = true;

    if(loadFromBinary)
    {
        fin.seekg(0, ios::beg); // reset to file beginning
        status = m_registersMap->LoadFromStream(fin);
        fin.read(temp, 12);
    }
    fin.close();

    if(!loadFromBinary)
    {
        bool autoUploadState = GetAutoUpload();
        SetAutoUpload(false);
        iniParser parser;
        parser.Open(filename);
        parser.SelectSection("FILE INFO");
        string type = "";
        type = parser.Get("type", "undefined");
        stringstream ss;
        if(type != "LMS6002 configuration")
        {
            ss << "File " << filename << " not recognized" << endl;
            //MessageLog::getInstance()->write(ss.str(), LOG_ERROR);
            Notify( LMS_Message(MSG_ERROR, ss.str(), 0, 0) );
            return false;
        }

        int fileVersion = 0;
        fileVersion = parser.Get("version", 0);

        if(fileVersion == 1)
        {
            map<string, string>::iterator pairs;
            parser.SelectSection("LMS6002 registers");
            map<string, string> regValues = parser.GetCurrentSection();

            unsigned int addr = 0;
            unsigned int value = 0;
            for(pairs = regValues.begin(); pairs != regValues.end(); ++pairs)
            {
                sscanf(pairs->first.c_str(), "%x", &addr);
                sscanf(pairs->second.c_str(), "%x", &value);
                m_registersMap->SetRegisterValue(addr, value);
            }

            parser.SelectSection("Frequencies");
            m_FreqTx_MHz = parser.Get("FreqTx_MHz", 2.14);
            m_FreqRx_MHz = parser.Get("FreqRx_MHz", 2.13);

            parser.SelectSection("Reference clocks");
            double refClk;
            refClk = parser.Get("Tx reference clock MHz", 30.72);
            SetReferenceFrequency(refClk, false);
            refClk = parser.Get("Rx reference clock MHz", 30.72);
            SetReferenceFrequency(refClk, true);
        }
        SetAutoUpload(autoUploadState);
        status = true;
    }

    return status;
}

/** @brief Saves register values to file
    @param filename file to save into
    @param binary binary or text file
    @return true if success
*/
bool LMS6002_MainControl::SaveToFile(const char *filename, bool binary)
{
    bool status = false;
    if(binary)
    {
        return false;
        //status = m_registersMap->SaveToFile(filename, binary);
        ofstream fout;
        fout.open(filename, ios::out | ios::binary);
        m_registersMap->SaveToStream(fout);
        fout.close();
    }
    else
    {
        iniParser parser;
        parser.SelectSection("FILE INFO");
        parser.Set("type", "LMS6002 configuration");
        parser.Set("version", 1);

        map<valType, Register>::iterator pairs;
        pairs = getRegistersMap()->m_registers.begin();
        parser.SelectSection("LMS6002 registers");

        char addr[80];
        char value[80];

        for(pairs = getRegistersMap()->m_registers.begin(); pairs != getRegistersMap()->m_registers.end(); ++pairs)
        {
            sprintf(addr, "0x%02X", pairs->first);
            sprintf(value, "0x%02X", pairs->second.value);
            parser.Set(addr,value);
        }

        parser.SelectSection("Frequencies");
        parser.Set("FreqTx_MHz", m_FreqTx_MHz);
        parser.Set("FreqRx_MHz", m_FreqRx_MHz);

        parser.SelectSection("Reference clocks");
        double refClk = 0;
        refClk = GetReferenceFrequency(false);
        parser.Set("Tx reference clock MHz", refClk);
        refClk = GetReferenceFrequency(false);
        parser.Set("Rx reference clock MHz", refClk);

        parser.Save(filename);
        status = true;
    }
    return status;
}

/** @brief Discovers all connected chips
*/
void LMS6002_MainControl::FindDevices()
{
    m_device->FindDevices();
}

/** @brief Sends reset signal to chip
    @param action Reset type
        0 - deactivate reset
        1 - activate reset
        2 - pulse reset
    @return 1 : success
            0 : failure
            -1 : board not connected

*/
int LMS6002_MainControl::ResetChip(int action)
{
    LMS_Message msg;
    if(m_device->IsOpen() == false)
    {
        msg.text = "Reset: board not connected\n";
        msg.type = MSG_ERROR;
        Notify(msg);
        return -1;
    }
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_RST;
    pkt.outBuffer[0] = action;
    pkt.outLen = 1;
    if( m_device->TransferPacket(pkt) == STATUS_COMPLETED_CMD )
    {
        switch(action)
        {
        case LMS_RST_DEACTIVATE:
            msg.text = "Chip Reset deactivated\n";
            break;
        case LMS_RST_ACTIVATE:
            msg.text = "Chip Reset activated\n";
            break;
        case LMS_RST_PULSE:
            msg.text = "Chip Reset pulse\n";
            break;
        default:
            msg.text = "Unknown reset type (available types: deactivate, activate, pulse)\n";
            msg.type = MSG_ERROR;
            Notify(msg);
            return 0;
        }
        //MessageLog::getInstance()->write(msg.text, LOG_INFO);
        msg.type = MSG_INFO;
        Notify(msg);
        return 1;
    }
    msg.text = "Failed to change reset state\n";
    msg.type = MSG_WARNING;
    Notify(msg);
    return 0;
}

/** @brief Sends all configuration to the chip
    @return true if success
*/
bool LMS6002_MainControl::UploadAll()
{
    LMS_Message msg;
    int status = m_registersMap->UploadAll();
    //set pa and lna, to update gpio values
    SetParam(PA_EN, GetParam(PA_EN));
    SetParam(LNASEL_RXFE, GetParam(LNASEL_RXFE));
    if(status == 1)
    {
        msg.type = MSG_INFO;
        msg.text = "Uploaded all configuration\n";
        return true;
    }
    else
    {
        if(status == 0)
        {
            msg.type = MSG_ERROR;
            msg.text = "Failed to upload all configuration\n";
        }
        else if(status == -1)
        {
            msg.type = MSG_WARNING;
            msg.text = "Board not connected\n";
        }
        return false;
    }
}

/** @brief Reads all configuration from the chip
    @return true if success
*/
bool LMS6002_MainControl::DownloadAll()
{
    LMS_Message msg;
    int status = m_registersMap->DownloadAll();
    if(status == 1)
    {
        msg.type = MSG_INFO;
        msg.text = "Downloaded all configuration\n";
        return true;
    }
    else
    {
        if(status == 0)
        {
            msg.type = MSG_ERROR;
            msg.text = "Failed to download all configuration\n";
        }
        else if(status == -1)
        {
            msg.type = MSG_WARNING;
            msg.text = "Board not connected\n";
        }
        return false;
    }
}

/** @brief Set chosen parameter to given value
    @param param LMS7002 parameter
    @param value new parameter value
    @return true if success
*/
bool LMS6002_MainControl::SetParam(LMS_Parameter param, const long value)
{
    int N; double intFvco;
    bool status = m_registersMap->SetParameterValue(param, value);
    if(param == ACODE_RXPLL || param == BCODE_RXPLL)
        CalcIntPllData(true, intFvco, N);
    else if(param == ACODE_TXPLL || param == BCODE_TXPLL)
        CalcIntPllData(false, intFvco, N);
    else if(param == STXEN)
        m_registersMap->SetParameterValue(CLK_EN_0, value > 0);
    else if(param == SRXEN)
        m_registersMap->SetParameterValue(CLK_EN_2, value > 0);
    else if(param == LNASEL_RXFE)
    {
        m_registersMap->SetParameterValue(SELOUT_RXPLL, value);
        unsigned char buf[1];
        switch(value)
        {
            case 1:
                buf[0] = 0x03;
                break;
            case 2:
                buf[0] = 0x01;
                break;
            case 3:
                buf[0] = 0x00;
                break;
            default:
                buf[0] = 0x03;
                break;
        }
        GenericPacket pkt;
        if(m_device->GetExpansionBoardType() != EXP_BOARD_HPM1000)
        {
            if(m_device->GetConnectedDeviceType() == LMS_DEV_ZIPPER)
                SetGPIO(1, 0, buf[0]);
            else
            {
                pkt.cmd = CMD_LMS_LNA;
                pkt.outLen = 1;
                pkt.outBuffer[0] = buf[0];
                m_device->TransferPacket(pkt);
            }
        }
    }
    else if(param == PA_EN)
    {
        unsigned char buf[1];
        switch(value)
        {
            case 1:
                buf[0] = 0x00;
                break;
            case 2:
                buf[0] = 0x01;
                break;
            default:
                buf[0] = 0;
                break;
        }

        if(m_device->GetExpansionBoardType() != EXP_BOARD_HPM1000)
        {
            if(m_device->GetConnectedDeviceType() == LMS_DEV_ZIPPER)
                SetGPIO(2, 2, buf[0]);
            else
            {
                GenericPacket pkt;
                pkt.cmd = CMD_LMS_PA;
                pkt.outLen = 1;
                pkt.outBuffer[0] = buf[0];
                m_device->TransferPacket(pkt);
            }
        }
    }
    return status;
}

/** @brief Returns value of chosen parameter
    @param param LMS7002 parameter
    @return parameter value
*/
long LMS6002_MainControl::GetParam(LMS_Parameter param, const bool fromChip, const bool updateLocal) const
{
    return m_registersMap->GetParameterValue(param, fromChip, updateLocal);
}

RegistersMap* LMS6002_MainControl::getRegistersMap() const
{
    return m_registersMap;
}

ConnectionManager* LMS6002_MainControl::getSerPort() const
{
    return m_device;
}

/** @brief Enables or disables auto download mode
    @param enabled auto download enable
    When auto download is enabled each GetParam() call will read register value
    from chip, otherwise the returned value will be from local program memory
*/
void LMS6002_MainControl::SetAutoDownload(const bool enabled)
{
    m_registersMap->SetAutoDownload(enabled);
}

/** @brief Returns auto download state
    @return auto download enabled
*/
bool LMS6002_MainControl::GetAutoDownload() const
{
    return m_registersMap->GetAutoDownload();
}

/** @brief Enables or disables auto uploading
    @param enabled auto upload enable
    When auto upload is enabled each SetParam call will write register value to
    the chip, otherwise value is written to local memory for later writing.
*/
void LMS6002_MainControl::SetAutoUpload(const bool enabled)
{
    m_registersMap->SetAutoUpload(enabled);
}

/** @brief Returns auto upload state
    @return auto upload enabled
*/
bool LMS6002_MainControl::GetAutoUpload() const
{
    return m_registersMap->GetAutoUpload();
}

/** @brief Sets reference frequency
    @param freq_MHz reference frequency in MHz
    @param Rx true for receiver, false for transmitter
    @return true if success
*/
bool LMS6002_MainControl::SetReferenceFrequency(const double freq_MHz, const bool Rx)
{
    if(Rx)
        m_RxPLL.SetReferenceFrequency(freq_MHz);
    else
        m_TxPLL.SetReferenceFrequency(freq_MHz);
    return true;
}

/** @brief Returns reference frequency
    @param Rx true for receiver, false for transmitter
    @return reference frequency in MHz
*/
double LMS6002_MainControl::GetReferenceFrequency(const bool Rx) const
{
    if(Rx)
        return m_RxPLL.GetReferenceFrequency();
    else
        return m_TxPLL.GetReferenceFrequency();
}

/** @brief Sets transmitter or receiver to desired frequency and returns configuration values
    @param Rx true for receiver, false for transmitter
    @param desFreq_MHz desired frequency in MHz
    @param realFreq_MHz frequency that was set
    @param iVCO VCO index
    @param fVCO VCO frequency in MHz
    @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range. Set to closest available frequency
*/
int LMS6002_MainControl::SetFrequency(const bool Rx, const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco_MHz, int &Divider)
{
	int iCap;
    int status = 0;

    PLL* pll = NULL;
    if(Rx)
        pll = &m_RxPLL;
    else
        pll = &m_TxPLL;

    status = pll->FreqParams(desFreq_MHz, realFreq_MHz, Nint, Nfrac, iVCO, Fvco_MHz, Divider);
    if(status == -1) //can't deliver frequency
    {
        LMS_Message msg;
        msg.type = MSG_ERROR;
        stringstream ss;
        ss << (Rx ? "Rx:":"Tx:") << " Cannot deliver requested frequency (" << desFreq_MHz << " MHz)\n";
        msg.text = ss.str();
        Notify(msg);
        return status;
    }

	if(Rx)
        m_FreqRx_MHz = desFreq_MHz;
    else
        m_FreqTx_MHz = desFreq_MHz;

	SetParam(Rx ? FRANGE_RXPLL : FRANGE_TXPLL, indexToSELVCO_FRANGE(Divider));
    SetParam(Rx ? NINT_RXPLL : NINT_TXPLL, Nint);
	SetParam(Rx ? NFRAC_RXPLL : NFRAC_TXPLL, Nfrac);
	SetParam(Rx ? SELVCO_RXPLL : SELVCO_TXPLL, indexToSELVCO_FRANGE(iVCO));

    iCap = pll->AutoSelectVcoCap(Fvco_MHz, iVCO);

	if ((iCap > 61) && ((iVCO == 2) || (iVCO == 3) || (iVCO == 4)))
	{
		iVCO--;
        iCap = pll->AutoSelectVcoCap(Fvco_MHz, iVCO);
	};
	SetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, iCap);
    int N;
    double intFvco;
	CalcIntPllData(Rx, intFvco, N);

    LMS_Message msg;
    stringstream ss;
	if(status == 1)
    {
        msg.type = MSG_WARNING;
        ss << (Rx ? "Rx:":"Tx:") << " Requested frequency(" << desFreq_MHz << " MHz) is out of range. Configuring to closest available frequency\n";
    }
    else
    {
        msg.type = MSG_INFO;
        ss << (Rx ? "Rx:":"Tx:") << " Frequency set to " << realFreq_MHz << " MHz\n";
    }
    msg.text = ss.str();
    Notify(msg);
	return status;
}

/** @brief Returns frequency of transmitter or receiver
    @param Rx true for receiver, false for transmitter
    @return Frequency in MHz
*/
double LMS6002_MainControl::GetFrequency(const bool Rx) const
{
    if(Rx)
        return m_FreqRx_MHz;
    else
        return m_FreqTx_MHz;
}

/** @brief Tunes transmitter or receiver
    @param Rx true for receiver, false for transmitter
    @return 0 : failure
            1 : success
*/
int LMS6002_MainControl::Tune(const bool Rx)
{
    if(m_device->IsOpen() == false)
    {
        Notify( LMS_Message(MSG_ERROR, "Tune: Board not connected\n", 0, 0) );
        return 0;
    }
    int iCap00;
	int iCap63;
	int iInitCap;
	int iInitVco;

	// Remember the initial states of CAP and VCO
	iInitCap = GetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, true, true);
	iInitVco = SELVCO_FRANGE_ToIndex(GetParam(Rx ? SELVCO_RXPLL : SELVCO_TXPLL, true, true));

	for (int i = 1; i <= 4; i++)
	{
		stringstream Str;
		Str << "=== Trying VCO Nr. ";
		Str << (5 - i);
		Str << " ===" << endl;
		Notify( LMS_Message(MSG_INFO, Str.str(), 0, 0) );
		Str.str("");

		// Choose VCO
		SetParam(Rx ? SELVCO_RXPLL : SELVCO_TXPLL, indexToSELVCO_FRANGE(i));

		// Set CAP to '0'
		SetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, 0);

		// See what the values of Vh and Vl are
		int vh = GetParam(Rx?VTUNE_H_RXPLL:VTUNE_H_TXPLL, true, true);
		int vl = GetParam(Rx?VTUNE_L_RXPLL:VTUNE_L_TXPLL); //gets updated when reading VTUNE_H
		iCap00 = vh << 1 | vl;

		// Set CAP to '63'
        SetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, 63);
		// See what are the values of Vh and Vl
		vh = GetParam(Rx?VTUNE_H_RXPLL:VTUNE_H_TXPLL, true, true);
		vl = GetParam(Rx?VTUNE_L_RXPLL:VTUNE_L_TXPLL, true);
		iCap63 = vh << 1 | vl;

		Str << "Vtune for CAP=0 is ";
		Str << iCap00 << endl;
		Str << "Vtune for CAP=63 is ";
		Str << iCap63 << endl;
		Notify( LMS_Message(MSG_INFO, Str.str(), 0, 0) );
		Str.str("");

		if (( SELVCO_FRANGE_ToIndex(GetParam(Rx?SELVCO_RXPLL:SELVCO_TXPLL, true, true)) == 4) && (iCap00 == 0x02) && (iCap63 == 0x02))
		{
			break;
		};

		if ((iCap00 == 0x02) && (iCap63 == 0x01))
		{
			Notify( LMS_Message(MSG_INFO, "VCO can deliver required frequency.\n", 0, 0) );
			//Notify( LMS_Message(MSG_INFO, "Starting Procedure.\n", 0, 0) );

			// Set CAP in the middle of the range
			SetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, 31);

			// Try to Tune
			algorithms->CapAutoTune_S(Rx);

			Str << "Selected CAP = ";
			Str << GetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, true, true) << endl;
			Notify( LMS_Message(MSG_INFO, Str.str(), 0, 0) );
			Str.str("");
			//return iCapTuneRes;
			return 1;
		};
		Notify( LMS_Message(MSG_INFO, "VCO is not suitable.\n", 0, 0) );
	};
	string str = "Tune: VCO can not deliver required frequency.\n\
Communication problems?\n\
Please check SPI cable, connection etc.\n\n\
VCO and CAP changed back to initial values\n";
	Notify( LMS_Message(MSG_ERROR, str, 0, 0) );

	// Set CAP and VCO to initial values
	SetParam(Rx ? VCOCAP_RXPLL : VCOCAP_TXPLL, iInitCap);
	SetParam(Rx ? SELVCO_RXPLL : SELVCO_TXPLL, indexToSELVCO_FRANGE(iInitVco));
	return 0;
}

/** @brief Sets CLK_EN by mask
    @param mask enabled clocks bits
*/
void LMS6002_MainControl::EnableSPIClocksByMask(const unsigned int mask)
{
    unsigned value = GetParam(CLK_EN, true, true);
    m_SPIclocksBackup = value;
    value |= mask;
    SetParam(CLK_EN, value);
}

void LMS6002_MainControl::RestoreAllSPIClocks()
{
    SetParam(CLK_EN, m_SPIclocksBackup);
}

/** @brief Calculates Values for Integer mode, returns VCO frequency and divider
    @param Rx true for receiver, false for transmitter
    @param fVCO_MHz VCO frequency in MHz
    @param divider frequency divider
*/
void LMS6002_MainControl::CalcIntPllData(const bool Rx, double &fVCO_MHz, int &divider)
{
	int Bvalue;
	int itmp1 = 0;
	switch (GetParam(Rx?BCODE_RXPLL:BCODE_TXPLL))
	{
	case 0x3F:
		itmp1 = 35;
		break;
	case 0x3E:
		itmp1 = 34;
		break;
	case 0x3C:
		itmp1 = 33;
		break;
	case 0x38:
		itmp1 = 32;
		break;
	case 0x39:
		itmp1 = 31;
		break;
	case 0x3B:
		itmp1 = 30;
		break;
	case 0x37:
		itmp1 = 29;
		break;
	case 0x36:
		itmp1 = 28;
		break;
	case 0x34:
		itmp1 = 27;
		break;
	case 0x30:
		itmp1 = 26;
		break;
	case 0x31:
		itmp1 = 25;
		break;
	case 0x33:
		itmp1 = 24;
		break;
	case 0x27:
		itmp1 = 23;
		break;
	case 0x26:
		itmp1 = 22;
		break;
	case 0x24:
		itmp1 = 21;
		break;
	case 0x20:
		itmp1 = 20;
		break;
	case 0x21:
		itmp1 = 19;
		break;
	case 0x23:
		itmp1 = 18;
		break;
	case 0x07:
		itmp1 = 17;
		break;
	case 0x06:
		itmp1 = 16;
		break;
	case 0x04:
		itmp1 = 15;
		break;
	case 0x00:
		itmp1 = 14;
		break;
	case 0x01:
		itmp1 = 13;
		break;
	case 0x03:
		itmp1 = 12;
		break;
	case 0x0F:
		itmp1 = 11;
		break;
	case 0x0E:
		itmp1 = 10;
		break;
	case 0x0C:
		itmp1 = 9;
		break;
	case 0x08:
		itmp1 = 8;
		break;
	case 0x09:
		itmp1 = 7;
		break;
    default:
        itmp1 = 7;
		break;
	}
	Bvalue = itmp1;

	int Avalue = 0;
	switch (GetParam(Rx?ACODE_RXPLL:ACODE_TXPLL))
	{
	case 0x0F:
		itmp1 = 7;
		break;
	case 0x0E:
		itmp1 = 6;
		break;
	case 0x0C:
		itmp1 = 5;
		break;
	case 0x08:
		itmp1 = 4;
		break;
	case 0x00:
		itmp1 = 3;
		break;
	case 0x01:
		itmp1 = 2;
		break;
	case 0x03:
		itmp1 = 1;
		break;
	case 0x07:
		itmp1 = 0;
        break;
    default:
        itmp1 = 0;
        break;
	}
	Avalue = itmp1;

	int N = 8 * Bvalue + Avalue + 34;
    divider = N;
    char ctemp[40];

	//lblN_info = (N);
	sprintf(ctemp, "%i", N);
	m_textVariables[Rx?"_lblN_RXPLL":"_lblN_TXPLL"] = ctemp;
	double Fvco_MHz = GetReferenceFrequency(Rx) * N;
	fVCO_MHz = Fvco_MHz;
	double lblFvcoInt_info = (Fvco_MHz/1000);
	sprintf(ctemp, "%g", lblFvcoInt_info);
	m_textVariables[Rx?"_lblFvcoInt_RXPLL":"_lblFvcoInt_TXPLL"] = ctemp;
	double lblFvco2Int_info = (Fvco_MHz / 2);
	sprintf(ctemp, "%g", lblFvco2Int_info);
	m_textVariables[Rx?"_lblFvco2Int_RXPLL":"_lblFvco2Int_TXPLL"] = ctemp;
	double lblFvco4Int_info = (Fvco_MHz / 4);
	sprintf(ctemp, "%g", lblFvco4Int_info);
	m_textVariables[Rx?"_lblFvco4Int_RXPLL":"_lblFvco4Int_TXPLL"] = ctemp;
	double lblFvco8Int_info = (Fvco_MHz / 8);
	sprintf(ctemp, "%g", lblFvco8Int_info);
	m_textVariables[Rx?"_lblFvco8Int_RXPLL":"_lblFvco8Int_TXPLL"] = ctemp;
	double lblFvco16Int_info = (Fvco_MHz / 16);
	sprintf(ctemp, "%g", lblFvco16Int_info);
	m_textVariables[Rx?"_lblFvco16Int_RXPLL":"_lblFvco16Int_TXPLL"] = ctemp;
}

/**
*/
void LMS6002_MainControl::LoadAdditionalSettings()
{
	// Top SPI
	// 1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI
	// Figured out in event handler;
	// 1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI
	// Figured out in event handler;
	// 1.c. Enable Rx OUT/ADC In Switch
	SetParam(RXOUTSW, 1);
	// 1.d. Disable PLLCLKOUT
	SetParam(CLK_EN_6, 0);

	// Tx/RxPLL SPIs
	// 2.a. Set CP Up Offset to 30 uA
	SetParam(OFFUP_TXPLL, 3);
	SetParam(OFFUP_RXPLL, 3);

	// Rx VGA2
	// 3.a. VGA2 CM Voltage set to 12.
	// m_RxVga2Module->CustSet_cmbVCM(12);
	//m_RxVga2Module->CustSet_cmbVCM(13);
	//m_RxVga2Module->setVCM(9); // 9 was index
	SetParam(VCM_RXVGA2, 13); // 13 is code

	// Rx FE
	// 4.a. LNA Load Resistor set to 55
	SetParam(RDLINT_LNA_RXFE, 55);

	// ADC /DAC
	// 5.a. ADC Common Mode Adj. set to 960mV
	SetParam(RX_CTRL2_54, 1);
	SetParam(RX_CTRL2_76, 1);

	// Tx RF
	// Set "LO Buffer Bias Current" to 6
	SetParam(ICT_TXLOBUF, 4);
}

/** @brief Resets registers to default values and loads additional settings
*/
void LMS6002_MainControl::NewProject()
{
    m_registersMap->SetDefaultValues();
    LoadAdditionalSettings();
}

/** @brief Performs registers test, and reuploads all configuration
    @return true if success
*/
int LMS6002_MainControl::RegistersTest()
{
    int status = m_registersMap->RegistersTest();
    UploadAll();
    return status;
}

void LMS6002_MainControl::SetGPIO(unsigned int msb, unsigned int lsb, int value)
{
    unsigned int mask = 0;
    for(unsigned i=0; i<=msb-lsb; ++i)
    {
        mask = mask << 1;
        mask |= 1;
    }
    mask = mask << lsb;
    m_GPIO = m_GPIO & (~mask);
    unsigned int newValue = 0;
    newValue = value;
    newValue = newValue << lsb;
    newValue = newValue & mask;
    m_GPIO |= newValue;

    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_GPIO_WR;
    pkt.outLen = 1;
    pkt.outBuffer[0] = m_GPIO;
    getSerPort()->TransferPacket(pkt);
}


}
