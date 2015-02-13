#include "UARFCN.h"

CUARFCN::CUARFCN()
{
  //Uplink, RX
  m_sRxUARFCNDef.dFul_low[0] =  19224;  m_sRxUARFCNDef.dFul_high[0] =  19776;  m_sRxUARFCNDef.dFul_offset[0] =      0;
  m_sRxUARFCNDef.dFul_low[1] =  18524;  m_sRxUARFCNDef.dFul_high[1] =  19076;  m_sRxUARFCNDef.dFul_offset[1] =      0;
  m_sRxUARFCNDef.dFul_low[2] =  17124;  m_sRxUARFCNDef.dFul_high[2] =  17826;  m_sRxUARFCNDef.dFul_offset[2] =  15250;
  m_sRxUARFCNDef.dFul_low[3] =  17124;  m_sRxUARFCNDef.dFul_high[3] =  17526;  m_sRxUARFCNDef.dFul_offset[3] =  14500;
  m_sRxUARFCNDef.dFul_low[4] =   8264;  m_sRxUARFCNDef.dFul_high[4] =   8466;  m_sRxUARFCNDef.dFul_offset[4] =      0;
  m_sRxUARFCNDef.dFul_low[5] =   8324;  m_sRxUARFCNDef.dFul_high[5] =   8376;  m_sRxUARFCNDef.dFul_offset[5] =      0;
  m_sRxUARFCNDef.dFul_low[6] =  25024;  m_sRxUARFCNDef.dFul_high[6] =  25676;  m_sRxUARFCNDef.dFul_offset[6] =  21000;
  m_sRxUARFCNDef.dFul_low[7] =   8824;  m_sRxUARFCNDef.dFul_high[7] =   9126;  m_sRxUARFCNDef.dFul_offset[7] =   3400;
  m_sRxUARFCNDef.dFul_low[8] =  17524;  m_sRxUARFCNDef.dFul_high[8] =  17824;  m_sRxUARFCNDef.dFul_offset[8] =      0;
  m_sRxUARFCNDef.dFul_low[9] =  17124;  m_sRxUARFCNDef.dFul_high[9] =  17676;  m_sRxUARFCNDef.dFul_offset[9] =  11350;
  m_sRxUARFCNDef.dFul_low[10] = 14304;  m_sRxUARFCNDef.dFul_high[10] = 14504;  m_sRxUARFCNDef.dFul_offset[10] =  7330;
  m_sRxUARFCNDef.dFul_low[11] =  7004;  m_sRxUARFCNDef.dFul_high[11] =  7136;  m_sRxUARFCNDef.dFul_offset[11] =  -220;
  m_sRxUARFCNDef.dFul_low[12] =  7794;  m_sRxUARFCNDef.dFul_high[12] =  7846;  m_sRxUARFCNDef.dFul_offset[12] =   210;
  m_sRxUARFCNDef.dFul_low[13] =  7904;  m_sRxUARFCNDef.dFul_high[13] =  7956;  m_sRxUARFCNDef.dFul_offset[13] =   120;

  //Downlink, TX
  m_sTxUARFCNDef.dFul_low[0] =  21124;  m_sTxUARFCNDef.dFul_high[0] =  21676;  m_sTxUARFCNDef.dFul_offset[0] =      0;
  m_sTxUARFCNDef.dFul_low[1] =  19324;  m_sTxUARFCNDef.dFul_high[1] =  19876;  m_sTxUARFCNDef.dFul_offset[1] =      0;
  m_sTxUARFCNDef.dFul_low[2] =  18074;  m_sTxUARFCNDef.dFul_high[2] =  18776;  m_sTxUARFCNDef.dFul_offset[2] =  15750;
  m_sTxUARFCNDef.dFul_low[3] =  21124;  m_sTxUARFCNDef.dFul_high[3] =  21526;  m_sTxUARFCNDef.dFul_offset[3] =  18050;
  m_sTxUARFCNDef.dFul_low[4] =   8714;  m_sTxUARFCNDef.dFul_high[4] =   8916;  m_sTxUARFCNDef.dFul_offset[4] =      0;
  m_sTxUARFCNDef.dFul_low[5] =   8774;  m_sTxUARFCNDef.dFul_high[5] =   8826;  m_sTxUARFCNDef.dFul_offset[5] =      0;
  m_sTxUARFCNDef.dFul_low[6] =  26224;  m_sTxUARFCNDef.dFul_high[6] =  26876;  m_sTxUARFCNDef.dFul_offset[6] =  21750;
  m_sTxUARFCNDef.dFul_low[7] =   9274;  m_sTxUARFCNDef.dFul_high[7] =   9576;  m_sTxUARFCNDef.dFul_offset[7] =   3400;
  m_sTxUARFCNDef.dFul_low[8] =  18474;  m_sTxUARFCNDef.dFul_high[8] =  18774;  m_sTxUARFCNDef.dFul_offset[8] =      0;
  m_sTxUARFCNDef.dFul_low[9] =  21124;  m_sTxUARFCNDef.dFul_high[9] =  21676;  m_sTxUARFCNDef.dFul_offset[9] =  14900;
  m_sTxUARFCNDef.dFul_low[10] = 14784;  m_sTxUARFCNDef.dFul_high[10] = 14984;  m_sTxUARFCNDef.dFul_offset[10] =  7360;
  m_sTxUARFCNDef.dFul_low[11] =  7304;  m_sTxUARFCNDef.dFul_high[11] =  7436;  m_sTxUARFCNDef.dFul_offset[11] =  -370;
  m_sTxUARFCNDef.dFul_low[12] =  7484;  m_sTxUARFCNDef.dFul_high[12] =  7536;  m_sTxUARFCNDef.dFul_offset[12] =  -550;
  m_sTxUARFCNDef.dFul_low[13] =  7604;  m_sTxUARFCNDef.dFul_high[13] =  7656;  m_sTxUARFCNDef.dFul_offset[13] =  -630;

  //
  m_bBandEnable[0] = true; m_bBandEnable[1] = true; m_bBandEnable[2] = true; m_bBandEnable[3] = true;
  m_bBandEnable[4] = true; m_bBandEnable[5] = true; m_bBandEnable[6] = true; m_bBandEnable[7] = true;
  m_bBandEnable[8] = true; m_bBandEnable[9] = true; m_bBandEnable[10] = true; m_bBandEnable[11] = true;
  m_bBandEnable[12] = true; m_bBandEnable[13] = true;

  //
  m_sBands[0] = "I"; m_sBands[1] = "II"; m_sBands[2] = "III"; m_sBands[3] = "IV";
  m_sBands[4] = "V"; m_sBands[5] = "VI"; m_sBands[6] = "VII"; m_sBands[7] = "VIII";
  m_sBands[8] = "IX"; m_sBands[9] = "X"; m_sBands[10] = "XI"; m_sBands[11] = "XII";
  m_sBands[12] = "XIII"; m_sBands[13] = "XIV";
};

double CUARFCN::CalculateFrequency(bool ULRX, int band, int channel)
{
    if(ULRX)
        return (2 * channel + m_sRxUARFCNDef.dFul_offset[band]) / 10;
    else
        return (2 * channel + m_sTxUARFCNDef.dFul_offset[band]) / 10;
}

