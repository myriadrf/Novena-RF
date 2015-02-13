// -----------------------------------------------------------------------------
// FILE: 		    clUARFCN.cpp
// DESCRIPTION:	Band selection control
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "clUARFCN.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
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

  cmbULRXBands   = NULL;
  cmbULRXChan    = NULL;
  txtULRXFreq    = NULL;
  btnULRXFChan_B = NULL;
  btnULRXFChan_M = NULL;
  btnULRXFChan_T = NULL;

  cmbDLTXBands   = NULL;
  cmbDLTXChan    = NULL;
  txtDLTXFreq    = NULL;
  btnDLTXFChan_B = NULL;
  btnDLTXFChan_M = NULL;
  btnDLTXFChan_T = NULL;
};

void CUARFCN::Initialize( TComboBox *ULRXBands, TComboBox *ULRXChan, TEdit *ULRXFreq,
                          TSpeedButton *ULRXFChan_B, TSpeedButton *ULRXFChan_M, TSpeedButton *ULRXFChan_T,
                          TComboBox *DLTXBands, TComboBox *DLTXChan, TEdit *DLTXFreq,
                          TSpeedButton *DLTXFChan_B, TSpeedButton *DLTXFChan_M, TSpeedButton *DLTXFChan_T
                          )
{
  cmbULRXBands     = ULRXBands;
  cmbULRXChan      = ULRXChan;
  txtULRXFreq      = ULRXFreq;
  btnULRXFChan_B   = ULRXFChan_B;
  btnULRXFChan_M   = ULRXFChan_M;
  btnULRXFChan_T   = ULRXFChan_T;

  cmbDLTXBands     = DLTXBands;
  cmbDLTXChan      = DLTXChan;
  txtDLTXFreq      = DLTXFreq;
  btnDLTXFChan_B   = DLTXFChan_B;
  btnDLTXFChan_M   = DLTXFChan_M;
  btnDLTXFChan_T   = DLTXFChan_T;

  SetBands(true);   //ULRX
  SetBands(false);  //DLTX

  SetChannels(true);  //ULRX
  SetChannels(false); //DLTX

  SetFrequency(true);   //ULRX
  SetFrequency(false);  //DLTX

  //ULRX
  SetFastChannelsAllUp(true);

  //DLTX
  SetFastChannelsAllUp(false);
};
//---------------------------------------------------------------------------
CUARFCN::~CUARFCN()
{
};

//---------------------------------------------------------------------------
void CUARFCN::SaveConf(TIniFile *pini)
{
  pini->WriteBool("BNDS", "I",    m_bBandEnable[0] );
  pini->WriteBool("BNDS", "II",   m_bBandEnable[1] );
  pini->WriteBool("BNDS", "III",  m_bBandEnable[2] );
  pini->WriteBool("BNDS", "IV",   m_bBandEnable[3] );
  pini->WriteBool("BNDS", "V",    m_bBandEnable[4] );
  pini->WriteBool("BNDS", "VI",   m_bBandEnable[5] );
  pini->WriteBool("BNDS", "VII",  m_bBandEnable[6] );
  pini->WriteBool("BNDS", "VIII", m_bBandEnable[7] );
  pini->WriteBool("BNDS", "IX",   m_bBandEnable[8] );
  pini->WriteBool("BNDS", "X",    m_bBandEnable[9] );
  pini->WriteBool("BNDS", "XI",   m_bBandEnable[10]);
  pini->WriteBool("BNDS", "XII",  m_bBandEnable[11]);
  pini->WriteBool("BNDS", "XIII", m_bBandEnable[12]);
  pini->WriteBool("BNDS", "XIV",  m_bBandEnable[13]);
};

//---------------------------------------------------------------------------
void CUARFCN::SetFastChannelsAllUp(bool ULRX)
{
  TSpeedButton *btnFChan_B;
  TSpeedButton *btnFChan_M;
  TSpeedButton *btnFChan_T;
  if(ULRX)
  {
    btnFChan_B = btnULRXFChan_B;
    btnFChan_M = btnULRXFChan_M;
    btnFChan_T = btnULRXFChan_T;
  }
  else
  {
    btnFChan_B = btnDLTXFChan_B;
    btnFChan_M = btnDLTXFChan_M;
    btnFChan_T = btnDLTXFChan_T;
  };

  if(btnFChan_B) btnFChan_B->Down = false;
  if(btnFChan_M) btnFChan_M->Down = false;
  if(btnFChan_T) btnFChan_T->Down = false;
};

//---------------------------------------------------------------------------
void CUARFCN::ReadConf(TIniFile *pini)
{
  m_bBandEnable[0]  = pini->ReadBool("BNDS", "I",    1);
  m_bBandEnable[1]  = pini->ReadBool("BNDS", "II",   1);
  m_bBandEnable[2]  = pini->ReadBool("BNDS", "III",  1);
  m_bBandEnable[3]  = pini->ReadBool("BNDS", "IV",   1);
  m_bBandEnable[4]  = pini->ReadBool("BNDS", "V",    1);
  m_bBandEnable[5]  = pini->ReadBool("BNDS", "VI",   1);
  m_bBandEnable[6]  = pini->ReadBool("BNDS", "VII",  1);
  m_bBandEnable[7]  = pini->ReadBool("BNDS", "VIII", 1);
  m_bBandEnable[8]  = pini->ReadBool("BNDS", "IX",   1);
  m_bBandEnable[9]  = pini->ReadBool("BNDS", "X",    1);
  m_bBandEnable[10] = pini->ReadBool("BNDS", "XI",   1);
  m_bBandEnable[11] = pini->ReadBool("BNDS", "XII",  1);
  m_bBandEnable[12] = pini->ReadBool("BNDS", "XIII", 1);
  m_bBandEnable[13] = pini->ReadBool("BNDS", "XIV",  1);

  SetBands(true);   //ULRX
  SetBands(false);  //DLTX

  SetChannels(true);  //ULRX
  SetChannels(false); //DLTX

  SetFrequency(true);   //ULRX
  SetFrequency(false);  //DLTX

  //ULRX
  SetFastChannelsAllUp(true);

  //DLTX
  SetFastChannelsAllUp(false);
};

//---------------------------------------------------------------------------
void CUARFCN::SetBands(bool ULRX)
{
  TComboBox *Bands;
  if(ULRX) Bands = cmbULRXBands;
  else Bands = cmbDLTXBands;

  if(!Bands) return;

  Bands->Items->Clear();
  for(int i=0; i<BandN; i++)
  {
    if(m_bBandEnable[i])
    {
      Bands->Items->Add(m_sBands[i]);
    };
  };
  Bands->ItemIndex = 0;
};

//---------------------------------------------------------------------------
int CUARFCN::ChName2ChInd(String ChName)
{
  if(ChName == "I")    return 0;
  if(ChName == "II")   return 1;
  if(ChName == "III")  return 2;
  if(ChName == "IV")   return 3;
  if(ChName == "V")    return 4;
  if(ChName == "VI")   return 5;
  if(ChName == "VII")  return 6;
  if(ChName == "VIII") return 7;
  if(ChName == "IX")   return 8;
  if(ChName == "X")    return 9;
  if(ChName == "XI")   return 10;
  if(ChName == "XII")  return 11;
  if(ChName == "XIII") return 12;
  if(ChName == "XIV")  return 13;
  return -1;
};

//---------------------------------------------------------------------------
void CUARFCN::SetChannels(bool ULRX)
{
  int BandInd;
  int iChFreq;
  int iTmp;
  double *dFul_low;
  double *dFul_high;
  double *dFul_offset;

  TComboBox *Bands;
  TComboBox *Chans;
  if(ULRX)
  {
    Bands = cmbULRXBands;
    Chans = cmbULRXChan;
    dFul_low = m_sRxUARFCNDef.dFul_low;
    dFul_high = m_sRxUARFCNDef.dFul_high;
    dFul_offset = m_sRxUARFCNDef.dFul_offset;
  }
  else
  {
    Bands = cmbDLTXBands;
    Chans = cmbDLTXChan;
    dFul_low = m_sTxUARFCNDef.dFul_low;
    dFul_high = m_sTxUARFCNDef.dFul_high;
    dFul_offset = m_sTxUARFCNDef.dFul_offset;
  };

  if( !Bands || !Chans) return;

  BandInd = ChName2ChInd(Bands->Items->Strings[Bands->ItemIndex]);
  if(BandInd < 0) return;
  Chans->Items->Clear();
  
  iChFreq = dFul_low[BandInd];
  while(iChFreq <= dFul_high[BandInd])
  {
    iTmp = 5 * (iChFreq - dFul_offset[BandInd]);
    iTmp = iTmp/10;
    Chans->Items->Add(iTmp);
    iChFreq += 2;
  };

  Chans->ItemIndex = 0;
};

//---------------------------------------------------------------------------
void CUARFCN::SetFastChannels(bool ULRX)
{
  TSpeedButton *btnFChan_B;
  TSpeedButton *btnFChan_M;
  TSpeedButton *btnFChan_T;
  TComboBox *Chans;
  if(ULRX)
  {
    Chans = cmbULRXChan;
    btnFChan_B = btnULRXFChan_B;
    btnFChan_M = btnULRXFChan_M;
    btnFChan_T = btnULRXFChan_T;
  }
  else
  {
    Chans = cmbDLTXChan;
    btnFChan_B = btnDLTXFChan_B;
    btnFChan_M = btnDLTXFChan_M;
    btnFChan_T = btnDLTXFChan_T;
  };

  if(!Chans || !btnFChan_B || !btnFChan_M || !btnFChan_T) return;

  if(btnFChan_B->Down == true) Chans->ItemIndex = 0;
  if(btnFChan_T->Down == true) Chans->ItemIndex = Chans->Items->Count-1;
  if(btnFChan_M->Down == true) Chans->ItemIndex = (int)(Chans->Items->Count-1)/2;
};

//---------------------------------------------------------------------------
double CUARFCN::SetFrequency(bool ULRX)
{
  int BandInd;
  int iChFreq;
  int iTmp;
  double dtmp;
  double *dFul_low;
  double *dFul_high;
  double *dFul_offset;

  TComboBox *Bands;
  TComboBox *Chans;
  TEdit *txtFreq;
  if(ULRX)
  {
    Bands = cmbULRXBands;
    Chans = cmbULRXChan;
    txtFreq = txtULRXFreq;
    dFul_low = m_sRxUARFCNDef.dFul_low;
    dFul_high = m_sRxUARFCNDef.dFul_high;
    dFul_offset = m_sRxUARFCNDef.dFul_offset;
  }
  else
  {
    Bands = cmbDLTXBands;
    Chans = cmbDLTXChan;
    txtFreq = txtDLTXFreq;
    dFul_low = m_sTxUARFCNDef.dFul_low;
    dFul_high = m_sTxUARFCNDef.dFul_high;
    dFul_offset = m_sTxUARFCNDef.dFul_offset;
  };

  if( !Bands || !Chans) return 0;

  BandInd = ChName2ChInd(Bands->Items->Strings[Bands->ItemIndex]);
  if(BandInd < 0) return 0;

  //dtmp = (10*Channel + 5 * m_sRxUARFCNDef.dFul_offset[BandInd])/50;
  dtmp = (2*Chans->Items->Strings[Chans->ItemIndex].ToInt() + dFul_offset[BandInd])/10;
  txtFreq->Text = dtmp;

  return dtmp;
};
