/**
@file   RegistersMap.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  LMS6002 registers map configuring
*/

#include "RegistersMap.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "CommonUtilities.h"
using namespace std;
namespace lms6
{

/** @brief Checks if there are no overlapping parameters in registers
    @return true if overlapping parameters are found
*/
bool RegistersMap::CheckForOverlays()
{
    cout << "Checking for overlapping bits" << endl;
    bool status = false;
    SetAutoUpload(false); //write and read locally from memory
    SetAutoDownload(false);
    //set all memory to zeros
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
        SetParameterValue((LMS_Parameter)i, 0);
    //read parameter and check if all bits are zeros, then fill with ones
    unsigned long value = 0;
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
    {
        value = 0;
        value = GetParameterValue((LMS_Parameter)i);
        if(value != 0)
        {
            cout << "Register bits overlapping at address " << (m_parameterList[(LMS_Parameter)i].registers[0].addr) << " " << m_parameterList[(LMS_Parameter)i].name << endl;
            value = GetParameterValue((LMS_Parameter)i);
            status = true;
        }

        unsigned long mask = 0xffffffff;
        mask = mask << m_parameterList[(LMS_Parameter)i].bitsCount;
        mask = ~mask;
        SetParameterValue((LMS_Parameter)i, mask);

        //readback to ensure correct writing
        value = 0;
        value = GetParameterValue((LMS_Parameter)i);
        if(value != mask)
        {
            cout << "writing failed at address " << m_parameterList[(LMS_Parameter)i].registers[0].addr << "   set value " << mask << "  read value " << value << " " << m_parameterList[(LMS_Parameter)i].name<< endl;
            SetParameterValue((LMS_Parameter)i, mask);
            value = GetParameterValue((LMS_Parameter)i);
        }
    }
    cout << "Overlay checking finished" << endl;
    return status;
}

/** @brief Creates registers map and initializes all parameters info
    @param pMng Connection manager for data transferring

    Initializes each parameter name, registers bits and default values
*/
RegistersMap::RegistersMap(ConnectionManager *pMng)
{
    m_autoDownload = false;
    m_autoUpload = true;

    m_serPort = pMng;
    m_parameterList[DC_REGVAL_TOP] = Parameter(5, 0, 0x00, 0, "DC_REGVAL_TOP");
    m_parameterList[RCCAL_LPFCAL] = Parameter(7, 5, 0x01, 0, "RCCAL_LPFCAL");
    m_parameterList[DC_LOCK_TOP] = Parameter(4, 2, 0x01, 0, "DC_LOCK_TOP");
    m_parameterList[DC_CLBR_DONE_TOP] = Parameter(1, 1, 0x01, 0, "DC_CLBR_DONE_TOP");
    m_parameterList[DC_UD_TOP] = Parameter(0, 0, 0x01, 0, "DC_UD_TOP");
    m_parameterList[DC_CNTVAL_TOP] = Parameter(5, 0, 0x02, 0x1F, "DC_CNTVAL_TOP");
    m_parameterList[DC_START_CLBR_TOP] = Parameter(5, 5, 0x03, 0, "DC_START_CLBR_TOP");
    m_parameterList[DC_LOAD_TOP] = Parameter(4, 4, 0x03, 0, "DC_LOAD_TOP");
    m_parameterList[DC_SRESET_TOP] = Parameter(3, 3, 0x03, 1, "DC_SRESET_TOP");
    m_parameterList[DC_ADDR_TOP] = Parameter(2, 0, 0x03, 0, "DC_ADDR_TOP");
    m_parameterList[VER] = Parameter(7, 4, 0x04, 2, "VER");
    m_parameterList[REV] = Parameter(3, 0, 0x04, 0, "REV");
    m_parameterList[DECODE_TOP] = Parameter(7, 7, 0x05, 0, "DECODE_TOP");
    m_parameterList[SRESET] = Parameter(5, 5, 0x05, 1, "SRESET");
    m_parameterList[EN_TOP] = Parameter(4, 4, 0x05, 1, "EN_TOP");
    m_parameterList[STXEN] = Parameter(3, 3, 0x05, 0, "STXEN");
    m_parameterList[SRXEN] = Parameter(2, 2, 0x05, 0, "SRXEN");
    m_parameterList[TFWMODE] = Parameter(1, 1, 0x05, 1, "TFWMODE");
    m_parameterList[CLKSEL_LPFCAL] = Parameter(3, 3, 0x06, 1, "CLKSEL_LPFCAL");
    m_parameterList[PD_CLKLPFCAL] = Parameter(2, 2, 0x06, 1, "PD_CLKLPFCAL");
    m_parameterList[ENF_EN_CAL_LPFCAL] = Parameter(1, 1, 0x06, 0, "ENF_EN_CAL_LPFCAL");
    m_parameterList[RST_CAL_LPFCAL] = Parameter(0, 0, 0x06, 1, "RST_CAL_LPFCAL");
    m_parameterList[EN_CAL_LPFCAL] = Parameter(7, 7, 0x07, 0, "EN_CAL_LPFCAL");
    m_parameterList[FORCE_CODE_CAL_LPFCAL] = Parameter(6, 4, 0x07, 0, "FORCE_CODE_CAL_LPFCAL");
    m_parameterList[BWC_LPFCAL] = Parameter(3, 0, 0x07, 0, "BWC_LPFCAL");
    m_parameterList[BBBYP] = Parameter(7, 7, 0x08, 0, "BBBYP");
    m_parameterList[LBEN_LPFIN] = Parameter(6, 6, 0x08, 0, "LBEN_LPFIN");
    m_parameterList[LBEN_VGA2IN] = Parameter(5, 5, 0x08, 0, "LBEN_VGA2IN");
    m_parameterList[LBEN_OPIN] = Parameter(4, 4, 0x08, 0, "LBEN_OPIN");
    m_parameterList[LBRFEN] = Parameter(3, 0, 0x08, 0, "LBRFEN");
    m_parameterList[RXOUTSW] = Parameter(7, 7, 0x09, 0, "RXOUTSW");
    m_parameterList[CLK_EN] = Parameter(6, 0, 0x09, 0x40, "CLK_EN");

    m_parameterList[CLK_EN_6] = Parameter(6, 6, 0x09, 1, "CLK_EN_6");
    m_parameterList[CLK_EN_5] = Parameter(5, 5, 0x09, 0, "CLK_EN_5");
    m_parameterList[CLK_EN_4] = Parameter(4, 4, 0x09, 0, "CLK_EN_4");
    m_parameterList[CLK_EN_3] = Parameter(3, 3, 0x09, 0, "CLK_EN_3");
    m_parameterList[CLK_EN_2] = Parameter(2, 2, 0x09, 0, "CLK_EN_2");
    m_parameterList[CLK_EN_1] = Parameter(1, 1, 0x09, 0, "CLK_EN_1");
    m_parameterList[CLK_EN_0] = Parameter(0, 0, 0x09, 0, "CLK_EN_0");

    m_parameterList[FDDTDD] = Parameter(1, 1, 0x0A, 0, "FDDTDD");
    m_parameterList[TDDMOD] = Parameter(0, 0, 0x0A, 0, "TDDMOD");
    m_parameterList[PDXCOBUF] = Parameter(4, 4, 0x0B, 0, "PDXCOBUF");
    m_parameterList[SLFBXCOBUF] = Parameter(3, 3, 0x0B, 1, "SLFBXCOBUF");
    m_parameterList[BYPXCOBUF] = Parameter(2, 2, 0x0B, 0, "BYPXCOBUF");
    m_parameterList[PD_1_TOP] = Parameter(1, 1, 0x0B, 0, "PD_1_TOP");
    m_parameterList[PD_0_TOP] = Parameter(0, 0, 0x0B, 0, "PD_0_TOP");
    m_parameterList[MASK] = Parameter(7, 0, 0x0E, 0, "MASK");

    unsigned int addroffset = 0x10;
    RegPiece nint_rxpll[] = { {0x10+addroffset, 7, 0}, {0x11+addroffset, 7, 7} };
    m_parameterList[NINT_RXPLL] = Parameter(nint_rxpll, 2, 130, "NINT_RXPLL");
    RegPiece frac_rxpll[] = { {0x11+addroffset, 6, 0}, {0x12+addroffset, 7, 0}, {0x13+addroffset, 7, 0} };
    m_parameterList[NFRAC_RXPLL] = Parameter(frac_rxpll, 3, 0, "NFRAC_RXPLL");

    m_parameterList[DITHEN_RXPLL] = Parameter(7, 7, 0x14+addroffset, 1, "DITHEN_RXPLL");
    m_parameterList[DITHN_RXPLL] = Parameter(6, 4, 0x14+addroffset, 0, "DITHN_RXPLL");
    m_parameterList[EN_RXPLL] = Parameter(3, 3, 0x14+addroffset, 1, "EN_RXPLL");
    m_parameterList[AUTOBYP_RXPLL] = Parameter(2, 2, 0x14+addroffset, 0, "AUTOBYP_RXPLL");
    m_parameterList[DECODE_RXPLL] = Parameter(1, 1, 0x14+addroffset, 0, "DECODE_RXPLL");
    m_parameterList[MODE_RXPLL] = Parameter(0, 0, 0x14+addroffset, 0, "MODE_RXPLL");
    m_parameterList[SELVCO_RXPLL] = Parameter(7, 5, 0x15+addroffset, 5, "SELVCO_RXPLL");
    m_parameterList[FRANGE_RXPLL] = Parameter(4, 2, 0x15+addroffset, 4, "FRANGE_RXPLL");
    m_parameterList[SELOUT_RXPLL] = Parameter(1, 0, 0x15+addroffset, 1, "SELOUT_RXPLL");
    m_parameterList[EN_PFD_UP_RXPLL] = Parameter(7, 7, 0x16+addroffset, 1, "EN_PFD_UP_RXPLL");
    m_parameterList[OEN_TSTD_SX_RXPLL] = Parameter(6, 6, 0x16+addroffset, 0, "OEN_TSTD_SX_RXPLL");
    m_parameterList[PASSEN_TSTOD_SD_RXPLL] = Parameter(5, 5, 0x16+addroffset, 0, "PASSEN_TSTOD_SD_RXPLL");
    m_parameterList[ICHP_RXPLL] = Parameter(4, 0, 0x16+addroffset, 12, "ICHP_RXPLL");
    m_parameterList[BYPVCOREG_RXPLL] = Parameter(7, 7, 0x17+addroffset, 1, "BYPVCOREG_RXPLL");
    m_parameterList[PDVCOREG_RXPLL] = Parameter(6, 6, 0x17+addroffset, 1, "PDVCOREG_RXPLL");
    m_parameterList[FSTVCOBG_RXPLL] = Parameter(5, 5, 0x17+addroffset, 1, "FSTVCOBG_RXPLL");
    m_parameterList[OFFUP_RXPLL] = Parameter(4, 0, 0x17+addroffset, 0, "OFFUP_RXPLL");

    RegPiece vovcoreg_rxpll[] = { {0x18+addroffset, 7, 5}, {0x19+addroffset, 7, 7} };
    m_parameterList[VOVCOREG_RXPLL] = Parameter(vovcoreg_rxpll, 2, 5, "VOVCOREG_RXPLL");

    m_parameterList[OFFDOWN_RXPLL] = Parameter(4, 0, 0x18+addroffset, 0, "OFFDOWN_RXPLL");
    m_parameterList[VCOCAP_RXPLL] = Parameter(5, 0, 0x19+addroffset, 20, "VCOCAP_RXPLL");
    m_parameterList[VTUNE_H_RXPLL] = Parameter(7, 7, 0x1A+addroffset, 0, "VTUNE_H_RXPLL");
    m_parameterList[VTUNE_L_RXPLL] = Parameter(6, 6, 0x1A+addroffset, 0, "VTUNE_L_RXPLL");
    m_parameterList[BCODE_RXPLL] = Parameter(5, 0, 0x1A+addroffset, 3, "BCODE_RXPLL");
    m_parameterList[ACODE_RXPLL] = Parameter(7, 4, 0x1B+addroffset, 7, "ACODE_RXPLL");
    m_parameterList[PD_VCOCOMP_SX_RXPLL] = Parameter(3, 3, 0x1B+addroffset, 0, "PD_VCOCOMP_SX_RXPLL");
    m_parameterList[ENLOBUF_RXPLL] = Parameter(2, 2, 0x1B+addroffset, 1, "ENLOBUF_RXPLL");
    m_parameterList[ENLAMP_RXPLL] = Parameter(1, 1, 0x1B+addroffset, 1, "ENLAMP_RXPLL");
    m_parameterList[TRI_RXPLL] = Parameter(0, 0, 0x1B+addroffset, 0, "TRI_RXPLL");

    m_parameterList[POL_RXPLL] = Parameter(7, 7, 0x1C+addroffset, 0, "POL_RXPLL");
    m_parameterList[PFDPD_RXPLL] = Parameter(6, 6, 0x1C+addroffset, 0, "PFDPD_RXPLL");
    m_parameterList[ENFEEDDIV_RXPLL] = Parameter(5, 5, 0x1C+addroffset, 1, "ENFEEDDIV_RXPLL");
    m_parameterList[PFDCLKP_RXPLL] = Parameter(4, 4, 0x1C+addroffset, 1, "PFDCLKP_RXPLL");
    m_parameterList[BCLKSEL_RXPLL] = Parameter(3, 2, 0x1C+addroffset, 2, "BCLKSEL_RXPLL");
    m_parameterList[BINSEL_RXPLL] = Parameter(1, 1, 0x1C+addroffset, 0, "BINSEL_RXPLL");
    m_parameterList[BSTART_RXPLL] = Parameter(0, 0, 0x1C+addroffset, 0, "BSTART_RXPLL");
    m_parameterList[BSTATE_RXPLL] = Parameter(7, 7, 0x1D+addroffset, 0, "BSTATE_RXPLL");

    RegPiece bsig_rxpll[] = { {0x1D+addroffset, 6, 0}, {0x1E +addroffset, 7, 0}, {0x1F+addroffset, 7, 0} };
    m_parameterList[BSIG_RXPLL] = Parameter(bsig_rxpll, 3, 0, "BSIG_RXPLL");

    addroffset = 0x00;
    RegPiece nint_TXPLL[] = { {0x10+addroffset, 7, 0}, {0x11+addroffset, 7, 7} };
    m_parameterList[NINT_TXPLL] = Parameter(nint_TXPLL, 2, 130, "NINT_TXPLL");
    RegPiece frac_TXPLL[] = { {0x11+addroffset, 6, 0}, {0x12+addroffset, 7, 0}, {0x13+addroffset, 7, 0} };
    m_parameterList[NFRAC_TXPLL] = Parameter(frac_TXPLL, 3, 0, "NFRAC_TXPLL");

    m_parameterList[DITHEN_TXPLL] = Parameter(7, 7, 0x14+addroffset, 1, "DITHEN_TXPLL");
    m_parameterList[DITHN_TXPLL] = Parameter(6, 4, 0x14+addroffset, 0, "DITHN_TXPLL");
    m_parameterList[EN_TXPLL] = Parameter(3, 3, 0x14+addroffset, 1, "EN_TXPLL");
    m_parameterList[AUTOBYP_TXPLL] = Parameter(2, 2, 0x14+addroffset, 0, "AUTOBYP_TXPLL");
    m_parameterList[DECODE_TXPLL] = Parameter(1, 1, 0x14+addroffset, 0, "DECODE_TXPLL");
    m_parameterList[MODE_TXPLL] = Parameter(0, 0, 0x14+addroffset, 0, "MODE_TXPLL");
    m_parameterList[SELVCO_TXPLL] = Parameter(7, 5, 0x15+addroffset, 5, "SELVCO_TXPLL");
    m_parameterList[FRANGE_TXPLL] = Parameter(4, 2, 0x15+addroffset, 4, "FRANGE_TXPLL");
    m_parameterList[SELOUT_TXPLL] = Parameter(1, 0, 0x15+addroffset, 1, "SELOUT_TXPLL");
    m_parameterList[EN_PFD_UP_TXPLL] = Parameter(7, 7, 0x16+addroffset, 1, "EN_PFD_UP_TXPLL");
    m_parameterList[OEN_TSTD_SX_TXPLL] = Parameter(6, 6, 0x16+addroffset, 0, "OEN_TSTD_SX_TXPLL");
    m_parameterList[PASSEN_TSTOD_SD_TXPLL] = Parameter(5, 5, 0x16+addroffset, 0, "PASSEN_TSTOD_SD_TXPLL");
    m_parameterList[ICHP_TXPLL] = Parameter(4, 0, 0x16+addroffset, 12, "ICHP_TXPLL");
    m_parameterList[BYPVCOREG_TXPLL] = Parameter(7, 7, 0x17+addroffset, 1, "BYPVCOREG_TXPLL");
    m_parameterList[PDVCOREG_TXPLL] = Parameter(6, 6, 0x17+addroffset, 1, "PDVCOREG_TXPLL");
    m_parameterList[FSTVCOBG_TXPLL] = Parameter(5, 5, 0x17+addroffset, 1, "FSTVCOBG_TXPLL");
    m_parameterList[OFFUP_TXPLL] = Parameter(4, 0, 0x17+addroffset, 0, "OFFUP_TXPLL");

    RegPiece vovcoreg_TXPLL[] = { {0x18+addroffset, 7, 5}, {0x19+addroffset, 7, 7} };
    m_parameterList[VOVCOREG_TXPLL] = Parameter(vovcoreg_TXPLL, 2, 5, "VOVCOREG_TXPLL");

    m_parameterList[OFFDOWN_TXPLL] = Parameter(4, 0, 0x18+addroffset, 0, "OFFDOWN_TXPLL");
    m_parameterList[VCOCAP_TXPLL] = Parameter(5, 0, 0x19+addroffset, 20, "VCOCAP_TXPLL");
    m_parameterList[VTUNE_H_TXPLL] = Parameter(7, 7, 0x1A+addroffset, 0, "VTUNE_H_TXPLL");
    m_parameterList[VTUNE_L_TXPLL] = Parameter(6, 6, 0x1A+addroffset, 0, "VTUNE_L_TXPLL");
    m_parameterList[BCODE_TXPLL] = Parameter(5, 0, 0x1A+addroffset, 3, "BCODE_TXPLL");
    m_parameterList[ACODE_TXPLL] = Parameter(7, 4, 0x1B+addroffset, 7, "ACODE_TXPLL");
    m_parameterList[PD_VCOCOMP_SX_TXPLL] = Parameter(3, 3, 0x1B+addroffset, 0, "PD_VCOCOMP_SX_TXPLL");
    m_parameterList[ENLOBUF_TXPLL] = Parameter(2, 2, 0x1B+addroffset, 1, "ENLOBUF_TXPLL");
    m_parameterList[ENLAMP_TXPLL] = Parameter(1, 1, 0x1B+addroffset, 1, "ENLAMP_TXPLL");
    m_parameterList[TRI_TXPLL] = Parameter(0, 0, 0x1B+addroffset, 0, "TRI_TXPLL");

    m_parameterList[POL_TXPLL] = Parameter(7, 7, 0x1C+addroffset, 0, "POL_TXPLL");
    m_parameterList[PFDPD_TXPLL] = Parameter(6, 6, 0x1C+addroffset, 0, "PFDPD_TXPLL");
    m_parameterList[ENFEEDDIV_TXPLL] = Parameter(5, 5, 0x1C+addroffset, 1, "ENFEEDDIV_TXPLL");
    m_parameterList[PFDCLKP_TXPLL] = Parameter(4, 4, 0x1C+addroffset, 1, "PFDCLKP_TXPLL");
    m_parameterList[BCLKSEL_TXPLL] = Parameter(3, 2, 0x1C+addroffset, 2, "BCLKSEL_TXPLL");
    m_parameterList[BINSEL_TXPLL] = Parameter(1, 1, 0x1C+addroffset, 0, "BINSEL_TXPLL");
    m_parameterList[BSTART_TXPLL] = Parameter(0, 0, 0x1C+addroffset, 0, "BSTART_TXPLL");
    m_parameterList[BSTATE_TXPLL] = Parameter(7, 7, 0x1D+addroffset, 0, "BSTATE_TXPLL");

    RegPiece bsig_TXPLL[] = { {0x1D+addroffset, 6, 0}, {0x1E +addroffset, 7, 0}, {0x1F+addroffset, 7, 0} };
    m_parameterList[BSIG_TXPLL] = Parameter(bsig_TXPLL, 3, 0, "BSIG_TXPLL");

	//TXLPF
    m_parameterList[DC_REGVAL_TXLPF] = Parameter(5, 0, 0x30, 0, "DC_REGVAL_TXLPF");
    m_parameterList[DC_LOCK_TXLPF] = Parameter(4, 2, 0x31, 0, "DC_LOCK_TXLPF");
    m_parameterList[DC_CLBR_DONE_TXLPF] = Parameter(1, 1, 0x31, 0, "DC_CLBR_DONE_TXLPF");
    m_parameterList[DC_UD_TXLPF] = Parameter(0, 0, 0x31, 0, "DC_UD_TXLPF");
    m_parameterList[DC_CNTVAL_TXLPF] = Parameter(5, 0, 0x32, 0x1F, "DC_CNTVAL_TXLPF");
    m_parameterList[DC_START_CLBR_TXLPF] = Parameter(5, 5, 0x33, 0, "DC_START_CLBR_TXLPF");
    m_parameterList[DC_LOAD_TXLPF] = Parameter(4, 4, 0x33, 0, "DC_LOAD_TXLPF");
    m_parameterList[DC_SRESET_TXLPF] = Parameter(3, 3, 0x33, 1, "DC_SRESET_TXLPF");
    m_parameterList[DC_ADDR_TXLPF] = Parameter(2, 0, 0x33, 0, "DC_ADDR_TXLPF");
    m_parameterList[BWC_LPF_TXLPF] = Parameter(5, 2, 0x34, 0, "BWC_LPF_TXLPF");
    m_parameterList[EN_TXLPF] = Parameter(1, 1, 0x34, 1, "EN_TXLPF");
    m_parameterList[DECODE_TXLPF] = Parameter(0, 0, 0x34, 0, "DECODE_TXLPF");
    m_parameterList[BYP_EN_LPF_TXLPF] = Parameter(6, 6, 0x35, 0, "BYP_EN_LPF_TXLPF");
    m_parameterList[DCO_DACCAL_TXLPF] = Parameter(5, 0, 0x35, 0xC, "DCO_DACCAL_TXLPF");
    m_parameterList[TX_DACBUF_PD_TXLPF] = Parameter(7, 7, 0x36, 0, "TX_DACBUF_PD_TXLPF");
    m_parameterList[RCCAL_LPF_TXLPF] = Parameter(6, 4, 0x36, 0x3, "RCCAL_LPF_TXLPF");

    //m_parameterList[PD_DCOCMP_LPF_TXLPF] = Parameter(3, 3, 0x36, 0, "PD_DCOCMP_LPF_TXLPF"); //only in mask set v0
    m_parameterList[PD_DCOCMP_LPF_TXLPF] = Parameter(7, 7, 0x3F, 0, "PD_DCOCMP_LPF_TXLPF"); //only in mask set v1

    m_parameterList[PD_DCODAC_LPF_TXLPF] = Parameter(2, 2, 0x36, 0, "PD_DCODAC_LPF_TXLPF");
    m_parameterList[PD_DCOREF_LPF_TXLPF] = Parameter(1, 1, 0x36, 0, "PD_DCOREF_LPF_TXLPF");
    m_parameterList[PD_FIL_LPF_TXLPF] = Parameter(0, 0, 0x36, 0, "PD_FIL_LPF_TXLPF");

	//RXLPF,ADC,DAC
	m_parameterList[DC_REGVAL_RXLPF] = Parameter(5, 0, 0x50, 0, "DC_REGVAL_RXLPF");
	m_parameterList[DC_LOCK_RXLPF] = Parameter(4, 2, 0x51, 0, "DC_LOCK_RXLPF");
	m_parameterList[DC_CLBR_DONE_RXLPF] = Parameter(1, 1, 0x51, 0, "DC_CLBR_DONE_RXLPF");
	m_parameterList[DC_UD_RXLPF] = Parameter(0, 0, 0x51, 0, "DC_UD_RXLPF");
	m_parameterList[DC_CNTVAL_RXLPF] = Parameter(5, 0, 0x52, 0x1f, "DC_CNTVAL_RXLPF");
	m_parameterList[DC_START_CLBR_RXLPF] = Parameter(5, 5, 0x53, 0, "DC_START_CLBR_RXLPF");
	m_parameterList[DC_LOAD_RXLPF] = Parameter(4, 4, 0x53, 0, "DC_LOAD_RXLPF");
	m_parameterList[DC_SRESET_RXLPF] = Parameter(3, 3, 0x53, 1, "DC_SRESET_RXLPF");
	m_parameterList[DC_ADDR_RXLPF] = Parameter(2, 0, 0x53, 0, "DC_ADDR_RXLPF");
	m_parameterList[BWC_LPF_RXLPF] = Parameter(5, 2, 0x54, 0, "BWC_LPF_RXLPF");
	m_parameterList[EN_RXLPF] = Parameter(1, 1, 0x54, 1, "EN_RXLPF");
	m_parameterList[DECODE_RXLPF] = Parameter(0, 0, 0x54, 0, "DECODE_RXLPF");
	m_parameterList[BYP_EN_LPF_RXLPF] = Parameter(6, 6, 0x55, 0, "BYP_EN_LPF_RXLPF");
	m_parameterList[DCO_DACCAL_RXLPF] = Parameter(5, 0, 0x55, 0xC, "DCO_DACCAL_RXLPF");

	m_parameterList[RCCAL_LPF_RXLPF] = Parameter(6, 4, 0x56, 0x3, "RCCAL_LPF_RXLPF");
	m_parameterList[PD_DCOCMP_LPF_RXLPF] = Parameter(3, 3, 0x56, 0, "PD_DCOCMP_LPF_RXLPF");
	m_parameterList[PD_DCODAC_LPF_RXLPF] = Parameter(2, 2, 0x56, 0, "PD_DCODAC_LPF_RXLPF");
	m_parameterList[PD_DCOREF_LPF_RXLPF] = Parameter(1, 1, 0x56, 0, "PD_DCOREF_LPF_RXLPF");
	m_parameterList[PD_FIL_LPF_RXLPF] = Parameter(0, 0, 0x56, 0, "PD_FIL_LPF_RXLPF");

	m_parameterList[EN_ADC_DAC] = Parameter(7, 7, 0x57, 1, "EN_ADC_DAC");
	m_parameterList[DECODE_ADC_DAC] = Parameter(6, 6, 0x57, 0, "DECODE_ADC_DAC");
	m_parameterList[TX_CTRL1_64] = Parameter(5, 3, 0x57, 0x2, "TX_CTRL1_64");
	m_parameterList[TX_CTRL1_3] = Parameter(2, 2, 0x57, 1, "TX_CTRL1_3");
	m_parameterList[TX_CTRL1_10] = Parameter(1, 0, 0x57, 0, "TX_CTRL1_10");

	m_parameterList[RX_CTRL1_76] = Parameter(7, 6, 0x58, 0, "RX_CTRL1_76");
	m_parameterList[RX_CTRL1_54] = Parameter(5, 4, 0x58, 0, "RX_CTRL1_54");
	m_parameterList[RX_CTRL1_30] = Parameter(3, 0, 0x58, 0, "RX_CTRL1_30");

	m_parameterList[RX_CTRL2_76] = Parameter(6, 5, 0x59, 0, "RX_CTRL2_76");
	m_parameterList[RX_CTRL2_54] = Parameter(4, 3, 0x59, 0, "RX_CTRL2_54");
	m_parameterList[RX_CTRL2_32] = Parameter(2, 1, 0x59, 0, "RX_CTRL2_32");
	m_parameterList[RX_CTRL2_0] = Parameter(0, 0, 0x59, 1, "RX_CTRL2_0");

	m_parameterList[MISC_CTRL_9] = Parameter(7, 7, 0x5A, 0, "MISC_CTRL_9");
	m_parameterList[MISC_CTRL_8] = Parameter(6, 6, 0x5A, 0, "MISC_CTRL_8");
	m_parameterList[MISC_CTRL_7] = Parameter(5, 5, 0x5A, 1, "MISC_CTRL_7");
	m_parameterList[MISC_CTRL_6] = Parameter(4, 4, 0x5A, 0, "MISC_CTRL_6");
	m_parameterList[MISC_CTRL_5] = Parameter(3, 3, 0x5A, 0, "MISC_CTRL_5");
	m_parameterList[RX_CTRL3_7] = Parameter(2, 2, 0x5A, 0, "RX_CTRL3_7");
	m_parameterList[RX_CTRL3_10] = Parameter(1, 0, 0x5A, 0, "RX_CTRL3_10");

	m_parameterList[RX_CTRL4_76] = Parameter(7, 6, 0x5B, 0, "RX_CTRL4_76");
	m_parameterList[RX_CTRL4_54] = Parameter(5, 4, 0x5B, 0, "RX_CTRL4_54");
	m_parameterList[RX_CTRL4_32] = Parameter(3, 2, 0x5B, 0, "RX_CTRL4_32");
	m_parameterList[RX_CTRL4_10] = Parameter(1, 0, 0x5B, 0, "RX_CTRL4_10");

	m_parameterList[RX_CTRL5_76] = Parameter(7, 6, 0x5C, 0, "RX_CTRL5_76");
	m_parameterList[RX_CTRL5_54] = Parameter(5, 4, 0x5C, 0, "RX_CTRL5_54");
	m_parameterList[RX_CTRL5_32] = Parameter(3, 2, 0x5C, 0, "RX_CTRL5_32");
	m_parameterList[RX_CTRL5_10] = Parameter(1, 0, 0x5C, 0, "RX_CTRL5_10");

	m_parameterList[REF_CTRL0_74] = Parameter(7, 4, 0x5D, 0, "REF_CTRL0_74");
	m_parameterList[REF_CTRL0_30] = Parameter(3, 0, 0x5D, 0, "REF_CTRL0_30");

	m_parameterList[REF_CTRL1_76] = Parameter(7, 6, 0x5E, 0, "REF_CTRL1_76");
	m_parameterList[REF_CTRL1_54] = Parameter(5, 4, 0x5E, 0, "REF_CTRL1_54");
	m_parameterList[REF_CTRL1_30] = Parameter(3, 0, 0x5E, 0, "REF_CTRL1_30");

	m_parameterList[PD_DCOCMP_LPF_RXLPF] = Parameter(7, 7, 0x5F, 0, "PD_DCOCMP_LPF_RXLPF"); //only when mask set v1
	m_parameterList[MISC_CTRL_4] = Parameter(4, 4, 0x5F, 1, "MISC_CTRL_4");
	m_parameterList[MISC_CTRL_3] = Parameter(3, 3, 0x5F, 1, "MISC_CTRL_3");
	m_parameterList[MISC_CTRL_2] = Parameter(2, 2, 0x5F, 1, "MISC_CTRL_2");
	m_parameterList[MISC_CTRL_1] = Parameter(1, 1, 0x5F, 1, "MISC_CTRL_1");
	m_parameterList[MISC_CTRL_0] = Parameter(0, 0, 0x5F, 1, "MISC_CTRL_0");

    //TXRF
    m_parameterList[EN_TXRF] = Parameter(1, 1, 0x40, 1, "EN_TXRF");
    m_parameterList[DECODE_TXRF] = Parameter(0, 0, 0x40, 0, "DECODE_TXRF");
    m_parameterList[VGA1GAIN] = Parameter(4, 0, 0x41, 0x15, "VGA1GAIN");
    m_parameterList[VGA1DC_I] = Parameter(7, 0, 0x42, 0x80, "VGA1DC_I");
    m_parameterList[VGA1DC_Q] = Parameter(7, 0, 0x43, 0x80, "VGA1DC_Q");

    m_parameterList[PA_EN] = Parameter(4, 3, 0x44, 1, "PA_EN");

    m_parameterList[PD_DRVAUX] = Parameter(1, 1, 0x44, 1, "PD_DRVAUX");
    m_parameterList[VGA2GAIN_TXVGA2] = Parameter(7, 3, 0x45, 0, "VGA2GAIN_TXVGA2");
    m_parameterList[ENVD_2] = Parameter(2, 2, 0x45, 0, "ENVD_2");
    m_parameterList[ENVD_10] = Parameter(1, 0, 0x45, 0, "ENVD_10");
    m_parameterList[PKDBW] = Parameter(7, 4, 0x46, 0, "PKDBW");
    m_parameterList[LOOPBBEN] = Parameter(3, 2, 0x46, 0, "LOOPBBEN");
    m_parameterList[FST_PKDET] = Parameter(1, 1, 0x46, 0, "FST_PKDET");
    m_parameterList[FST_TXHFBIAS] = Parameter(0, 0, 0x46, 0, "FST_TXHFBIAS");
    m_parameterList[ICT_TXLOBUF] = Parameter(7, 4, 0x47, 6, "ICT_TXLOBUF");
    m_parameterList[VBCAS_TXDRV] = Parameter(3, 0, 0x47, 0, "VBCAS_TXDRV");
    m_parameterList[ICT_TXMIX] = Parameter(4, 0, 0x48, 12, "ICT_TXMIX");
    m_parameterList[ICT_TXDRV] = Parameter(4, 0, 0x49, 12, "ICT_TXDRV");
    m_parameterList[PW_VGA1_I] = Parameter(4, 4, 0x4A, 1, "PW_VGA1_I");
    m_parameterList[PW_VGA1_Q] = Parameter(3, 3, 0x4A, 1, "PW_VGA1_Q");
    m_parameterList[PD_TXDRV] = Parameter(2, 2, 0x4A, 0, "PD_TXDRV");
    m_parameterList[PD_TXLOBUF] = Parameter(1, 1, 0x4A, 0, "PD_TXLOBUF");
    m_parameterList[PD_TXMIX] = Parameter(0, 0, 0x4A, 0, "PD_TXMIX");

    m_parameterList[VGA1GAINT] = Parameter(7, 0, 0x4B, 0x50, "VGA1GAINT");
    RegPiece g_txvga2[] = { {0x4C, 7, 0}, {0x4D, 7, 7} };
    m_parameterList[G_TXVGA2] = Parameter(g_txvga2, 2, 0, "G_TXVGA2");

    m_parameterList[PD_PKDET] = Parameter(7, 7, 0x4E, 0, "PD_PKDET"); //mask set v1, not used in v0

    //RXVGA2
    m_parameterList[DC_REGVAL_RXVGA2] = Parameter(5, 0, 0x60, 0, "DC_REGVAL_RXVGA2");
    m_parameterList[DC_LOCK_RXVGA2] = Parameter(4, 2, 0x61, 0, "DC_LOCK_RXVGA2");
    m_parameterList[DC_CLBR_DONE_RXVGA2] = Parameter(1, 1, 0x61, 0, "DC_CLBR_DONE_RXVGA2");
    m_parameterList[DC_UD_RXVGA2] = Parameter(0, 0, 0x61, 0, "DC_UD_RXVGA2");

    m_parameterList[DC_CNTVAL_RXVGA2] = Parameter(5, 0, 0x62, 0x1F, "DC_CNTVAL_RXVGA2");

    m_parameterList[DC_START_CLBR_RXVGA2] = Parameter(5, 5, 0x63, 0, "DC_START_CLBR_RXVGA2");
    m_parameterList[DC_LOAD_RXVGA2] = Parameter(4, 4, 0x63, 0, "DC_LOAD_RXVGA2");
    m_parameterList[DC_SRESET_RXVGA2] = Parameter(3, 3, 0x63, 1, "DC_SRESET_RXVGA2");
    m_parameterList[DC_ADDR_RXVGA2] = Parameter(2, 0, 0x63, 0, "DC_ADDR_RXVGA2");
    m_parameterList[VCM_RXVGA2] = Parameter(5, 2, 0x64, 7, "VCM_RXVGA2");
    m_parameterList[EN_RXVGA2] = Parameter(1, 1, 0x64, 1, "EN_RXVGA2");
    m_parameterList[DECODE_RXVGA2] = Parameter(0, 0, 0x64, 0, "DECODE_RXVGA2");

    m_parameterList[VGA2GAIN_RXVGA2] = Parameter(4, 0, 0x65, 1, "VGA2GAIN_RXVGA2");

    m_parameterList[PD_9] = Parameter(5, 5, 0x66, 0, "PD_9");
    m_parameterList[PD_8] = Parameter(4, 4, 0x66, 0, "PD_8");
    //m_parameterList[PD_7] = Parameter(3, 3, 0x66, 0, "PD_7");//not used in v1
    m_parameterList[PD_7] = Parameter(7, 7, 0x6E, 0, "PD_7"); //used in v1
    m_parameterList[PD_6] = Parameter(2, 2, 0x66, 0, "PD_6");
    //m_parameterList[PD_5] = Parameter(1, 1, 0x66, 0, "PD_5");//not used in v1
    m_parameterList[PD_5] = Parameter(6, 6, 0x6E, 0, "PD_5"); //used in v1
    m_parameterList[PD_4] = Parameter(0, 0, 0x66, 0, "PD_4");
    m_parameterList[PD_3] = Parameter(3, 3, 0x67, 0, "PD_3");
    m_parameterList[PD_2] = Parameter(2, 2, 0x67, 0, "PD_2");
    m_parameterList[PD_1] = Parameter(1, 1, 0x67, 0, "PD_1");
    m_parameterList[PD_0] = Parameter(0, 0, 0x67, 0, "PD_0");
    m_parameterList[VGA2GAINB] = Parameter(7, 4, 0x68, 0, "VGA2GAINB");
    m_parameterList[VGA2GAINA] = Parameter(3, 0, 0x68, 1, "VGA2GAINA");

    //RX FE
    m_parameterList[DECODE_RXFE] = Parameter(1, 1, 0x70, 0, "DECODE_RXFE");
    m_parameterList[EN_RXFE] = Parameter(0, 0, 0x70, 1, "EN_RXFE");
    m_parameterList[IN1SEL_MIX_RXFE] = Parameter(7, 7, 0x71, 1, "IN1SEL_MIX_RXFE");
    m_parameterList[DCOFF_I_RXFE] = Parameter(6, 0, 0x71, 0, "DCOFF_I_RXFE");
    m_parameterList[INLOAD_LNA_RXFE] = Parameter(7, 7, 0x72, 1, "INLOAD_LNA_RXFE");
    m_parameterList[DCOFF_Q_RXFE] = Parameter(6, 0, 0x72, 0, "DCOFF_Q_RXFE");
    m_parameterList[XLOAD_LNA_RXFE] = Parameter(7, 7, 0x73, 0, "XLOAD_LNA_RXFE");
    m_parameterList[IP2TRIM_I_RXFE] = Parameter(6, 0, 0x73, 0, "IP2TRIM_I_RXFE");
    m_parameterList[IP2TRIM_Q_RXFE] = Parameter(6, 0, 0x74, 0, "IP2TRIM_Q_RXFE");
    m_parameterList[G_LNA_RXFE] = Parameter(7, 6, 0x75, 3, "G_LNA_RXFE");
    m_parameterList[LNASEL_RXFE] = Parameter(5, 4, 0x75, 1, "LNASEL_RXFE");
    m_parameterList[CBE_LNA_RXFE] = Parameter(3, 0, 0x75, 0, "CBE_LNA_RXFE");
    m_parameterList[RFB_TIA_RXFE] = Parameter(6, 0, 0x76, 120, "RFB_TIA_RXFE");
    m_parameterList[CFB_TIA_RXFE] = Parameter(6, 0, 0x77, 0, "CFB_TIA_RXFE");
    m_parameterList[RDLEXT_LNA_RXFE] = Parameter(5, 0, 0x78, 0x1C, "RDLEXT_LNA_RXFE");
    m_parameterList[RDLINT_LNA_RXFE] = Parameter(5, 0, 0x79, 0x1C, "RDLINT_LNA_RXFE");
    m_parameterList[ICT_MIX_RXFE] = Parameter(7, 4, 0x7A, 7, "ICT_MIX_RXFE");
    m_parameterList[ICT_LNA_RXFE] = Parameter(3, 0, 0x7A, 7, "ICT_LNA_RXFE");
    m_parameterList[ICT_TIA_RXFE] = Parameter(7, 4, 0x7B, 7, "ICT_TIA_RXFE");
    m_parameterList[ICT_MXLOB_RXFE] = Parameter(3, 0, 0x7B, 7, "ICT_MXLOB_RXFE");
    m_parameterList[LOBN_MIX_RXFE] = Parameter(6, 3, 0x7C, 3, "LOBN_MIX_RXFE");
    m_parameterList[RINEN_MIX_RXFE] = Parameter(2, 2, 0x7C, 0, "RINEN_MIX_RXFE");
    m_parameterList[G_FINE_LNA3_RXFE] = Parameter(1, 0, 0x7C, 0, "G_FINE_LNA3_RXFE");
    m_parameterList[PD_TIA_RXFE] = Parameter(3, 3, 0x7D, 0, "PD_TIA_RXFE");
    m_parameterList[PD_MXLOB_RXFE] = Parameter(2, 2, 0x7D, 0, "PD_MXLOB_RXFE");
    m_parameterList[PD_MIX_RXFE] = Parameter(1, 1, 0x7D, 0, "PD_MIX_RXFE");
    m_parameterList[PD_LNA_RXFE] = Parameter(0, 0, 0x7D, 0, "PD_LNA_RXFE");

    //set masks for readonly
    m_registers[0x00].mask = 0x00;
    m_registers[0x01].mask = 0x00;
    m_registers[0x04].mask = 0x00;

    m_registers[0x1a].mask = 0x3f;
    m_registers[0x1d].mask = 0x00;
    m_registers[0x1e].mask = 0x00;
    m_registers[0x1f].mask = 0x00;

    m_registers[0x2a].mask = 0x3f;
    m_registers[0x2d].mask = 0x00;
    m_registers[0x2e].mask = 0x00;
    m_registers[0x2f].mask = 0x00;

    m_registers[0x30].mask = 0x00;
    m_registers[0x31].mask = 0x00;

    m_registers[0x50].mask = 0x00;
    m_registers[0x51].mask = 0x00;

    m_registers[0x60].mask = 0x00;
    m_registers[0x61].mask = 0x00;

    map<LMS_Parameter, Parameter>::iterator iter;
    int p = 0;
    for(iter=m_parameterList.begin(); iter!=m_parameterList.end(); ++iter)
    {
        SetParameterValue(iter->first, iter->second.defaultValue);
        ++p;
    }
    //setup default register values
    map<valType, Register>::iterator regIter;
    for(regIter = m_registers.begin(); regIter!=m_registers.end(); ++regIter)
    {
        regIter->second.defaultValue = regIter->second.value;
    }
    //if ( CheckForOverlays() )
    //    cout << "ERRORS IN REGISTER DESCRIPTIONS" << endl;
}

RegistersMap::~RegistersMap()
{

}

/** @brief Sets selected parameter to given value
    @param cp LMS6002 control parameter
    @param value parameter value
    @return true if success
*/
bool RegistersMap::SetParameterValue(const LMS_Parameter cp, unsigned long value)
{
    if(cp <= LMS_PARAM_UNDEFINED || LMS_PARAMETER_COUNT <= cp )
    {
        m_serPort->Notify( LMS_Message(MSG_WARNING, "SetParameterValue: invalid control parameter\n", 0, 0));
        return false;
    }
    const long startingValue = value;
    Parameter param = m_parameterList[cp];
    valType tempVal = 0;
    valType tempAddr = 0;
    valType tempMask = 0;
    for(int i=0; i<param.piecesCount; ++i)
    {
        tempAddr = param.registers[i].addr;
        tempVal = m_registers[tempAddr].value;
        tempMask = makeMask(param.registers[i].msb, param.registers[i].lsb);
        tempVal = tempVal & ~tempMask;
        tempVal |= (value << param.registers[i].lsb) & tempMask;
        SetRegisterValue(tempAddr, tempVal);
        value = value >> (param.registers[i].msb - param.registers[i].lsb +1);
        m_registers[tempAddr].value = tempVal;
    }
    return true;
}

/** @brief Returns selected parameter value
    @param cp LMS6002 control parameter
    @param fromChip read directly from chip
    @param updateLocal update local copy of registers with read value
    @return parameter value
*/
unsigned long RegistersMap::GetParameterValue(const LMS_Parameter cp, bool fromChip, bool updateLocal)
{
    Parameter param = m_parameterList[cp];
    valType tempVal = 0;
    valType tempAddr = 0;
    valType tempMask = 0;
    unsigned long value = 0;
    int bitsAdded = 0;
    for(int i=param.piecesCount-1; i>=0; --i)
    {
        tempAddr = param.registers[i].addr;
        if(fromChip || m_autoDownload)
            tempVal = GetRegisterValue(tempAddr, fromChip, updateLocal);
        else
            tempVal = m_registers[tempAddr].value;
        tempMask = makeMask(param.registers[i].msb, param.registers[i].lsb);
        tempVal = (tempVal & tempMask) >> param.registers[i].lsb;
        value = value << (param.registers[i].msb - param.registers[i].lsb + 1);
        value |= (tempVal);
        bitsAdded += param.registers[i].msb - param.registers[i].lsb + 1;
    }
    return value;
}

/** @brief Return register value of selected address
    @param address register address
    @param fromChip read directly from chip
    @param updateLocal update local registers map with read value
*/
valType RegistersMap::GetRegisterValue(const valType address, bool fromChip, bool updateLocal)
{
    valType dataToReturn = 0;
	if((m_serPort->IsOpen() && m_autoDownload) || (m_serPort->IsOpen() && fromChip))
    {
        GenericPacket pkt;
        pkt.cmd = CMD_LMS6002_RD;
        pkt.outBuffer[0] = address;
        pkt.outLen = 1;
        if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD)
        {
            if(updateLocal)
                m_registers[address].value = pkt.inBuffer[1];
            dataToReturn = pkt.inBuffer[1];
        }
    }
    else
        dataToReturn = m_registers[address].value;
    return dataToReturn;
}

/** @brief Sets selected register value
    @param address register address
    @param value register's new value
    @return true is success
*/
bool RegistersMap::SetRegisterValue(const valType address, const valType value)
{
    if(m_serPort->IsOpen() && m_autoUpload)
    {
        GenericPacket pkt;
        pkt.cmd = CMD_LMS6002_WR;
        pkt.outLen = 2;
        pkt.outBuffer[0] = address;
        pkt.outBuffer[1] = value;
        if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD )
        {
            m_registers[address].value = value;
            return true;
        }
        else
            return false;
    }
    else
        m_registers[address].value = value;
    return true;
}

/** @brief prints all register address value pair to standard output
*/
void RegistersMap::printOut()
{
    char ctemp[80];
    for(map<valType, Register>::iterator it = m_registers.begin(); it!=m_registers.end(); it++)
    {
        sprintf(ctemp, "0x%X", it->first);
        cout << ctemp << " : ";
        sprintf(ctemp, "0x%X", it->second.value);
        cout << ctemp << endl;
    }
}

/** @brief Writes all registers to the chip
    @return 1 : success
            0 : failure
            -1 : port not connected
*/
int RegistersMap::UploadAll()
{
    if(!m_serPort->IsOpen())
        return -1;

    vector<valType> DataToWrite;
    map<valType, Register>::iterator registers;
    for(registers = m_registers.begin(); registers!=m_registers.end(); ++registers)
    {
        DataToWrite.push_back( registers->first );
        DataToWrite.push_back( registers->second.value );
    }
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outLen = DataToWrite.size();
    memcpy(pkt.outBuffer, &DataToWrite[0], pkt.outLen);

    int status = m_serPort->TransferPacket(pkt);
    //additionaly set PA and LNASEL parameters to set GPIOs
    SetParameterValue(PA_EN, GetParameterValue(PA_EN));
    SetParameterValue(LNASEL_RXFE, GetParameterValue(LNASEL_RXFE));

    if(status == STATUS_COMPLETED_CMD)
        return 1;
    else
        return 0;
}

/** @brief Reads all registers from the chip
    @return 1 : success
            0 : failure
            -1 : port not connected
*/
int RegistersMap::DownloadAll()
{
    if(!m_serPort->IsOpen())
        return -1;

    vector<valType> addrToRead;
    map<valType, Register>::iterator registers;
    for(registers = m_registers.begin(); registers!=m_registers.end(); ++registers)
        addrToRead.push_back( registers->first );

    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_RD;
    pkt.outLen = addrToRead.size();
    memcpy(pkt.outBuffer, &addrToRead[0], pkt.outLen);

    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        for(unsigned i=0; i<addrToRead.size() && 2*i < pkt.inLen; ++i)
            m_registers[addrToRead[i]].value = pkt.inBuffer[2*i+1];
        return 1;
    }
    else
        return 0;
}

/** @brief Converts parameter name to parameter enumeration
    @param name parameter name
    @return parameter enumeration
*/
LMS_Parameter RegistersMap::GetParamIDbyName(const char *name)
{
    map<LMS_Parameter, Parameter>::iterator iter;
    int p = 0;
    for(iter=m_parameterList.begin(); iter!=m_parameterList.end(); ++iter)
    {
        if( strcmp(iter->second.name.c_str(), name) == 0)
        {
            return (LMS_Parameter)p;
        }
        ++p;
    }
    return LMS_PARAM_UNDEFINED;
}

/** @brief Sets all registers to their default values
*/
void RegistersMap::SetDefaultValues()
{
    //setup default register values
    map<valType, Register>::iterator regIter;
    for(regIter = m_registers.begin(); regIter!=m_registers.end(); ++regIter)
    {
        SetRegisterValue(regIter->first, regIter->second.defaultValue);
    }
}

/** @brief Performs register testing
    @return 1 : success, 0 : failed, -1 timeout
*/
int RegistersMap::RegistersTest()
{
    m_cancelRegisterTest = false;
    const int testsCommonCount = 8;
    RegTestPlan testsCommon[testsCommonCount] =
    {
        RegTestPlan("TOP", 0x00, 0x10-1, true),
        RegTestPlan("TX PLL", 0x10, 0x20-1, true),
        RegTestPlan("RX PLL", 0x20, 0x30-1, true),
        RegTestPlan("TX LPF", 0x30, 0x40-1, true),
        RegTestPlan("TX RF", 0x40, 0x50-1, true),
        RegTestPlan("RX LPF, DAC/ADC", 0x50, 0x60-1, true),
        RegTestPlan("RX VGA2", 0x60, 0x70-1, true),
        RegTestPlan("RX FE", 0x70, 0x80-1, true),
    };

    if(!m_serPort->IsOpen())
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test cancelled: control port not connected.\n", 0, 0));
        return 0;
    }

    bool status = true;
    int retVal = 0;
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register test started\n", 0, 0));

    for(int i=0; i<testsCommonCount && !m_cancelRegisterTest ; ++i)
    {
        string name = testsCommon[i].name;
        unsigned short sadr = testsCommon[i].startAddr;
        unsigned short eadr = testsCommon[i].endAddr;
        char ctemp[128];
        sprintf(ctemp, " %s interval [%#.2x : %#.2x]\n", name.c_str(), sadr, eadr);
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ctemp, 0, 0));
        bool bused = testsCommon[i].onlyUsedAddresses;
        retVal = RegisterTestBatch( name.c_str(), sadr, eadr, 0xff, bused);
        if( retVal >= 0)
            status &= retVal;
        else
            return retVal;
        retVal = RegisterTestBatch( name.c_str(), sadr, eadr, 0xaa, bused);
        if( retVal >= 0)
            status &= retVal;
        else
            return retVal;
    }

    if(m_cancelRegisterTest)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test canceled.\n", 0, 0));
        return 0;
    }

    UploadAll();

    // ==== VTUNE test ====//
    int selvcoState;
    int vcocapState;

	int iCmpMin, iCmpMax;
	// Enable SoftTX
	bool txState = GetParameterValue(STXEN);
	bool rxState = GetParameterValue(SRXEN);
	SetParameterValue(STXEN, true);
	// Enable TxPLL clock
	bool pllClkState = GetParameterValue(CLK_EN_0);
	SetParameterValue(CLK_EN_0, 1);
	// Apply reset
	// m_serPort->SPI_Rst();
	// x EnableAllSPIClocks();

	// Enable TxPLL clock
	// EnableSPIClockByMask(0x01);
	// Enable SoftTX
	milSleep(5);
	// Check TxPLL VTUNE
	m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Testing TxPLL VTUNE registers:\n", 0, 0));

	selvcoState = GetParameterValue(SELVCO_TXPLL);
	vcocapState = GetParameterValue(VCOCAP_TXPLL);

	SetParameterValue(SELVCO_TXPLL, 4);
	SetParameterValue(VCOCAP_TXPLL, 0);
	iCmpMin = ((GetParameterValue(VTUNE_H_TXPLL, true, true) << 1) | GetParameterValue(VTUNE_L_TXPLL, true, true));
	//m_TxPLLModule->GetVTuneState(1, 0);

	SetParameterValue(SELVCO_TXPLL, 7);
	SetParameterValue(VCOCAP_TXPLL, 63);
	iCmpMax = ((GetParameterValue(VTUNE_H_TXPLL, true, true) << 1) | GetParameterValue(VTUNE_L_TXPLL, true, true));
	status &= Comparators(iCmpMin, iCmpMax);

    SetParameterValue(SELVCO_TXPLL, selvcoState);
    SetParameterValue(VCOCAP_TXPLL, vcocapState);
	SetParameterValue(CLK_EN_0, pllClkState);

	milSleep(5);
	// Restore SoftTX Enable
	SetParameterValue(STXEN, txState);

    SetParameterValue(SRXEN, true);
	pllClkState = GetParameterValue(CLK_EN_2);
	SetParameterValue(CLK_EN_2, true);
	// Check RxPLL VTUNE
	m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Testing RxPLL VTUNE registers:\n", 0, 0));

	selvcoState = GetParameterValue(SELVCO_RXPLL);
	vcocapState = GetParameterValue(VCOCAP_RXPLL);

	SetParameterValue(SELVCO_RXPLL, 4);
	SetParameterValue(VCOCAP_RXPLL, 0);
	iCmpMin = ((GetParameterValue(VTUNE_H_RXPLL, true, true) << 1) | GetParameterValue(VTUNE_L_RXPLL, true, true));

	SetParameterValue(SELVCO_RXPLL, 7);
	SetParameterValue(VCOCAP_RXPLL, 63);
	iCmpMax = ((GetParameterValue(VTUNE_H_RXPLL, true, true) << 1) | GetParameterValue(VTUNE_L_RXPLL, true, true));
	status &= Comparators(iCmpMin, iCmpMax);

    SetParameterValue(SELVCO_RXPLL, selvcoState);
    SetParameterValue(VCOCAP_RXPLL, vcocapState);
	SetParameterValue(CLK_EN_2, pllClkState);

	milSleep(5);
	// Restore SoftTX Enable
	SetParameterValue(SRXEN, rxState);

	UploadAll();

    if(status == true)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test PASSED\n", 0, 0));
        return 1;
    }
    else
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test FAILED\n", 0, 0));
        return 0;
    }
}

/** @brief Signals to stop registers test if it is running
*/
void RegistersMap::CancelRegisterTest()
{
    m_cancelRegisterTest = true;
}

/** @brief Tests registers within given address range
    @param name test name
    @param addr1 starting address
    @param addr2 end address
    @param pattern data pattern to write for testing
    @param onlyUsed whether test only used registers or all available registers
    @return -1 timeout, 0 failed, 1 passed
*/
int RegistersMap::RegisterTestBatch(const char *name, const unsigned short addr1, const unsigned short addr2, const unsigned short pattern, const bool onlyUsed)
{
    bool testResult = true;
    int status;
    //find registers within range
    vector<valType> usedRegs;
    if(onlyUsed)
    {
        std::map<valType, Register>::iterator iter;
        for (iter = m_registers.begin(); iter != m_registers.end(); ++iter)
        {
            if(iter->first > addr2)
                break;

            if(iter->first >= addr1)
                usedRegs.push_back(iter->first);
        }
    }
    else
    {
        for(int i=0; i<=addr2-addr1; ++i)
            usedRegs.push_back( addr1+i );
    }

    //write data
    vector<valType> writtenBuffer;
    valType *inBuffer = new valType[usedRegs.size()*2];
    memset(inBuffer, 0, usedRegs.size()*2*sizeof(valType));

    testResult = true;
    writtenBuffer.clear();
    for(unsigned i=0; i<usedRegs.size(); ++i)
    {
        writtenBuffer.push_back(usedRegs[i]);
        writtenBuffer.push_back(pattern & m_registers[usedRegs[i]].mask);
    }
    unsigned long bytesToSend, bytesToRead;
    bytesToSend = writtenBuffer.size()*sizeof(valType);
    bytesToRead = bytesToSend;

    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outLen = bytesToSend;
    memcpy(pkt.outBuffer, &writtenBuffer[0], pkt.outLen);

    status = m_serPort->TransferPacket(pkt);
    if(status != STATUS_COMPLETED_CMD)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error writing data.", 0, 0));
        return -1;
    }
    vector<valType> outBuffer;
    for(unsigned i=0; i<usedRegs.size(); ++i)
        outBuffer.push_back(usedRegs[i]);
    bytesToSend = outBuffer.size()*sizeof(valType);
    bytesToRead = 2*bytesToSend;

    pkt.cmd = CMD_LMS6002_RD;
    pkt.outLen = bytesToSend;
    memcpy(pkt.outBuffer, &outBuffer[0], bytesToSend);
    status = m_serPort->TransferPacket(pkt);
    if(status != STATUS_COMPLETED_CMD)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error reading data.", 0, 0));
        return -1;
    }
    memcpy(inBuffer, pkt.inBuffer, bytesToRead);
    //compare results
    stringstream ssr;
    ssr.clear();
    ssr.str( string() );
    for(unsigned int i=0; i<outBuffer.size(); ++i)
    {
        if( (inBuffer[1+i*2] & m_registers[usedRegs[i]].mask) != writtenBuffer[1+i*2])
        {
            ssr << "address 0x" << int2hex(outBuffer[i],sizeof(valType)) << " (write/read) : " << int2hex(writtenBuffer[1+i*2], sizeof(valType)) << "/" << int2hex(inBuffer[1+i*2], sizeof(valType)) << endl;
            testResult = false;
        }
    }

    if(testResult == 1)
    {
        ssr.clear();
        ssr.str( string() );
        ssr << "Registers OK : (write/read) : " << int2hex(pattern, sizeof(valType)) << "/" << int2hex(pattern, sizeof(valType)) << endl;
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }
    else
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }

    delete inBuffer;
    inBuffer = NULL;
    return testResult;
}

/** @brief Tests comparator values
    @param Min VTUNE values when VCO set to min value
    @param Max VTUNE values when VCO set to max value
    @return true if VTUNE registers are OK
*/
bool RegistersMap::Comparators(int Min, int Max)
{
	string Str;
    if((Min == 0x2) && (Max == 0x1))
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "VTUNE registers are OK.\n\n", 0, 0));
        return true;
    }
    else
    {
        Str = "Some problems with VTUNE registers:\n";
        Str += "VTUNE_H (should be/acctual): 1/";
        Str += (Min & 0x02) ? "1" : "0";Str += "\n";
        Str += "VTUNE_H (should be/acctual): 0/";
        Str += (Max & 0x02) ? "1" : "0";Str += "\n";
        Str += "VTUNE_L (should be/acctual): 1/";
        Str += (Min & 0x01) ? "1" : "0";Str += "\n";
        Str += "VTUNE_L (should be/acctual): 0/";
        Str += (Max & 0x01) ? "1" : "0";Str += "\n";
        Str += "\n";
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, Str.c_str(), 0, 0));
        return false;
    };
}

/** @brief Returns parameter description
*/
const Parameter RegistersMap::getParameterInfo(const LMS_Parameter param )
{
    return m_parameterList[param];
}

/** @brief Saves register values to given stream
    @param fout output stream
    @return true if success
*/
bool RegistersMap::SaveToStream(ofstream &fout)
{
    valType addr;
    valType value;
    map<valType, Register>::iterator iter;
    vector<valType> data;

    char carr[16];
    memset(carr, 0, sizeof(carr));
    sprintf(carr, "%s" , "LMS6002 CONFIG");
    fout.write(carr, 16);

    unsigned short blockCount = 0;
    memset(carr, 0, sizeof(carr));
    sprintf(carr, "Registers");
    fout.write(carr, 14);
    for (iter = m_registers.begin(); iter != m_registers.end(); ++iter)
    {
        addr = iter->first;
        value = m_registers[addr].value;
        data.push_back(addr);
        data.push_back(value);
        ++blockCount;
    }
    fout.write((const char*)&blockCount, sizeof(blockCount));
    fout.write((const char*)&data[0], data.size()*sizeof(unsigned char));
    return true;
}

/** @brief Loads register values from given stream input
    @param fin input stream
    @return true if success
*/
bool RegistersMap::LoadFromStream(ifstream &fin)
{
    valType addr;
    valType value;
    map<valType, Register>::iterator iter;

    unsigned short pairCount;
    char carr[16];
    memset(carr,0, 16);
    fin.read(carr, 16); // Text header

    memset(carr,0, 16);
    fin.read(carr, 14); // channel text header
    fin.read((char*)&pairCount, 2); //number of address value pairs
    for(int j=0; j<pairCount; ++j)
    {
        fin.read((char*)&addr, 2); // register address
        fin.read((char*)&value, 2);// register value
        m_registers[addr].value = value;
    }
    return true;
}

}
