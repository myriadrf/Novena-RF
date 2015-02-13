// -----------------------------------------------------------------------------
// FILE: 		    frTxPLL.cpp
// DESCRIPTION:	Tx/Rx control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frTxPLL.h"
#include <values.h>


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "RXSpin"
#pragma resource "*.dfm"
//TfrmTxPLL *frmTxPLL;


//0x0
#define                 NINT81_r00_b70() ((m_psD.cDataR[0x00] & 0xFF) >> 0)
//0x1
#define                 NINT00_r01_b77() ((m_psD.cDataR[0x01] & 0x80) >> 7)
#define                           NINT() ((NINT81_r00_b70() << 1) + NINT00_r01_b77())
#define              NFRAC2216_r01_b60() ((m_psD.cDataR[0x01] & 0x7F) >> 0)
//0x2
#define               NFRAC158_r02_b70() ((m_psD.cDataR[0x02] & 0xFF) >> 0)
//0x3
#define                NFRAC70_r03_b70() ((m_psD.cDataR[0x03] & 0xFF) >> 0)
#define                          NFRAC()  ((((NFRAC2216_r01_b60() << 8) + NFRAC158_r02_b70()) << 8) + NFRAC70_r03_b70())
//0x4
#define                 DITHEN_r04_b77() ((m_psD.cDataR[0x04] & 0x80) >> 7)
#define                  DITHN_r04_b64() ((m_psD.cDataR[0x04] & 0x70) >> 4)
#define                     EN_r04_b33() ((m_psD.cDataR[0x04] & 0x08) >> 3)
#define                AUTOBYP_r04_b22() ((m_psD.cDataR[0x04] & 0x04) >> 2)
#define                 DECODE_r04_b11() ((m_psD.cDataR[0x04] & 0x02) >> 1)
#define                   MODE_r04_b00() ((m_psD.cDataR[0x04] & 0x01) >> 0)
//0x5
#define                 SELVCO_r05_b75() ((m_psD.cDataR[0x05] & 0xE0) >> 5)
#define                 FRANGE_r05_b42() ((m_psD.cDataR[0x05] & 0x1C) >> 2)
#define                 SELOUT_r05_b10() ((m_psD.cDataR[0x05] & 0x03) >> 0)
//0x6
#define              EN_PFD_UP_r06_b77() ((m_psD.cDataR[0x06] & 0x80) >> 7)
#define            OEN_TSTD_SX_r06_b66() ((m_psD.cDataR[0x06] & 0x40) >> 6)
#define        PASSEN_TSTOD_SD_r06_b55() ((m_psD.cDataR[0x06] & 0x20) >> 5)
#define                   ICHP_r06_b40() ((m_psD.cDataR[0x06] & 0x1F) >> 0)
//0x7
#define              BYPVCOREG_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define               PDVCOREG_r07_b66() ((m_psD.cDataR[0x07] & 0x40) >> 6)
#define               FSTVCOBG_r07_b55() ((m_psD.cDataR[0x07] & 0x20) >> 5)
#define                  OFFUP_r07_b40() ((m_psD.cDataR[0x07] & 0x1F) >> 0)
//0x8
#define             VOVCOREG31_r08_b75() ((m_psD.cDataR[0x08] & 0xE0) >> 5)
#define                OFFDOWN_r08_b40() ((m_psD.cDataR[0x08] & 0x1F) >> 0)
//0x9
#define             VOVCOREG00_r09_b77() ((m_psD.cDataR[0x09] & 0x80) >> 7)
#define                       VOVCOREG() ((VOVCOREG31_r08_b75() << 1) + (VOVCOREG00_r09_b77()))
#define                 VCOCAP_r09_b50() ((m_psD.cDataR[0x09] & 0x3F) >> 0)
//0xA
#define                VTUNE_H_r0A_b77() ((m_psD.cDataR[0x0A] & 0x80) >> 7)
#define                VTUNE_L_r0A_b66() ((m_psD.cDataR[0x0A] & 0x40) >> 6)
#define                  BCODE_r0A_b50() ((m_psD.cDataR[0x0A] & 0x3F) >> 0)
//0xB
#define                  ACODE_r0B_b74() ((m_psD.cDataR[0x0B] & 0xF0) >> 4)
#define          PD_VCOCOMP_SX_r0B_b33() ((m_psD.cDataR[0x0B] & 0x08) >> 3)
#define                ENLOBUF_r0B_b22() ((m_psD.cDataR[0x0B] & 0x04) >> 2)
#define                 ENLAMP_r0B_b11() ((m_psD.cDataR[0x0B] & 0x02) >> 1)
#define                    TRI_r0B_b00() ((m_psD.cDataR[0x0B] & 0x01) >> 0)
//0xC
#define                    POL_r0C_b77() ((m_psD.cDataR[0x0C] & 0x80) >> 7)
#define                  PFDPD_r0C_b66() ((m_psD.cDataR[0x0C] & 0x40) >> 6)
#define              ENFEEDDIV_r0C_b55() ((m_psD.cDataR[0x0C] & 0x20) >> 5)
#define                PFDCLKP_r0C_b44() ((m_psD.cDataR[0x0C] & 0x10) >> 4)
#define                BCLKSEL_r0C_b32() ((m_psD.cDataR[0x0C] & 0x0C) >> 2)
#define                 BINSEL_r0C_b11() ((m_psD.cDataR[0x0C] & 0x02) >> 1)
#define                 BSTART_r0C_b00() ((m_psD.cDataR[0x0C] & 0x01) >> 0)
//0xD
#define                 BSTATE_r0D_b77() ((m_psD.cDataR[0x0D] & 0x80) >> 7)
#define               BSIG2216_r0D_b60() ((m_psD.cDataR[0x0D] & 0x7F) >> 0)
//0xE
#define                BSIG158_r0E_b70() ((m_psD.cDataR[0x0E] & 0xFF) >> 0)
//0xF
#define                 BSIG70_r0F_b70() ((m_psD.cDataR[0x0F] & 0xFF) >> 0)
#define                           BSIG() ((((BSIG2216_r0D_b60() << 8) | BSIG158_r0E_b70()) << 8) | BSIG70_r0F_b70())


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A_TX ",20"
//#define FRIF_SPI_A_RX ",20"

//---------------------------------------------------------------------------
__fastcall TfrmTxPLL::TfrmTxPLL(TComponent* Owner)
	: TFrame(Owner)
{
  dlgFreqVsCap = new TdlgFreqVsCap(Application);
  m_dRefF = 30720000;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TfrmTxPLL::~TfrmTxPLL(void)
{
	delete[] m_psD.cCmdW;
	delete[] m_psD.cDataW;
	delete[] m_psD.cCmdR;
	delete[] m_psD.cDataR;
	delete[] m_psD.iRInd;
	delete[] m_psD.iWInd;
  delete[] m_psD.cTestMap;
  //delete dlgFreqVsCap;
}

//---------------------------------------------------------------------------
void TfrmTxPLL::Initialize(char MAddr)
{
	m_cMAddr = MAddr;

  if(m_cMAddr == TxPllAddr)
  {
    cmbSELOUT->Enabled = false;
    dlgFreqVsCap->Initialize("TxVCOFile");
  }
  else
  {
    dlgFreqVsCap->Initialize("RxVCOFile");
  };

	m_psD.iLen = TxPllLen;
	m_psD.cCmdW = new char[m_psD.iLen];
	m_psD.cDataW = new char[m_psD.iLen];
	m_psD.cCmdR = new char[m_psD.iLen];
	m_psD.cDataR = new char[m_psD.iLen];
	m_psD.iRInd = new int[m_psD.iLen];
	m_psD.iWInd = new int[m_psD.iLen];
  m_psD.cTestMap = new char[m_psD.iLen];  //RT//
	memset(m_psD.cCmdW, 0, m_psD.iLen);
	memset(m_psD.cDataW, 0, m_psD.iLen);
	memset(m_psD.cCmdR, 0, m_psD.iLen);
	memset(m_psD.cDataR, 0, m_psD.iLen);
	memset(m_psD.iRInd, 0, m_psD.iLen*sizeof(int));
	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
  memset(m_psD.cTestMap, 0, m_psD.iLen);  //RT//
	m_psD.iToR = m_psD.iLen;
	m_psD.iToW = 0;
	for(int i=0; i<m_psD.iLen; i++)
	{
		//Write Command and Addresses
		m_psD.cCmdW[i] = 1;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 3;
		m_psD.cCmdW[i] |= m_cMAddr;
		m_psD.cCmdW[i] = m_psD.cCmdW[i] << 4;
		m_psD.cCmdW[i] |= i;
		//Read Command and Addresses
		m_psD.cCmdR[i] = 0;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 3;
		m_psD.cCmdR[i] |= m_cMAddr;
		m_psD.cCmdR[i] = m_psD.cCmdR[i] << 4;
		m_psD.cCmdR[i] |= i;

		m_psD.iRInd[i] = i;
	};

  //Register test mask //RT//
  m_psD.cTestMap[0x0] = 0xFF;
  m_psD.cTestMap[0x1] = 0xFF;
  m_psD.cTestMap[0x2] = 0xFF;
  m_psD.cTestMap[0x3] = 0xFF;
  m_psD.cTestMap[0x4] = 0xFF;
  m_psD.cTestMap[0x5] = 0xFF;
  m_psD.cTestMap[0x6] = 0xFF;
  m_psD.cTestMap[0x7] = 0xFF;
  m_psD.cTestMap[0x8] = 0xFF;
  m_psD.cTestMap[0x9] = 0xBF;
  m_psD.cTestMap[0xA] = 0x3F;
  m_psD.cTestMap[0xB] = 0xFF;
  m_psD.cTestMap[0xC] = 0xFF;
  m_psD.cTestMap[0xD] = 0x00;
  m_psD.cTestMap[0xE] = 0x00;
  m_psD.cTestMap[0xF] = 0x00;

  SetGuiDefaults();
};

//---------------------------------------------------------------------------
void TfrmTxPLL::SetGuiDefaults()
{
	int itmp;
  double dtmp;
	m_bAllowSend = false;

//==== 0x04 ==========================
  //DITHEN
  chkDITHEN->Checked = true;
  //DITHN[2:0]
  cmbDITHN->Clear();
  for(int i=0; i<8; i++)
  {
    cmbDITHN->Items->Add(i+1);
  };
  cmbDITHN->ItemIndex = 0;
  //EN
  chbPwrPllMods->Checked = true;
  //AUTOBYP
  chbAUTOBYP->Checked = false;
	//DECODE
  rgrDecode->ItemIndex = 0;
  //MODE
  rgrMODE->ItemIndex = 0;

//==== 0x05 ==========================
  //SELVCO[2:0]
  rgrSELVCO->ItemIndex = 2;
  m_iPrevVCO = rgrSELVCO->ItemIndex;
  //FRANGE[2:0]
  rgrFRANGE->ItemIndex = 1;
  //SELOUT[1:0]
  cmbSELOUT->ItemIndex = 1;
//==== 0x06 ==========================
  //EN_PFD_UP
  chbEN_PFD_UP->Checked = true;
  //OEN_TSTD_SX
  chkOEN_TSTD_SX->Checked = false;
  //PASSEN_TSTOD_SD
  chkPASSEN_TSTOD_SD->Checked = false;
  //ICHP[4:0]
  cmbICHP->Clear();
  itmp = 0;
  for(int i=0; i<25; i++)
  {
    cmbICHP->Items->Add(itmp);
    itmp += 100;
  };
  cmbICHP->ItemIndex = 12;
//==== 0x07 ==========================
  //BYPVCOREG
  chbBYPVCOREG->Checked = true;
  //PDVCOREG
  chbPDVCOREG->Checked = true;
  //FSTVCOBG
  chbFSTVCOBG->Checked = true;
  //OFFUP[4:0]
  cmbOFFUP->Clear();
  itmp = 0;
  for(int i=0; i<25; i++)
  {
    cmbOFFUP->Items->Add(itmp);
    itmp += 10;
  };
  cmbOFFUP->ItemIndex = 0;
//==== 0x08 ==========================
  //VOVCOREG
  cmbVOVCOREG->Clear();
  dtmp = 1.4;
  for(int i=0; i<13; i++)
  {
    cmbVOVCOREG->Items->Add(dtmp);
    dtmp += 0.1;
  };
  cmbVOVCOREG->ItemIndex = 5;
  //OFFDOWN[4:0]
  cmbOFFDOWN->Clear();
  itmp = 0;
  for(int i=0; i<25; i++)
  {
    cmbOFFDOWN->Items->Add(itmp);
    itmp += 10;
  };
  cmbOFFDOWN->ItemIndex = 0;
//==== 0x09 ==========================
  //VCOCAP[5:0]
  cmbVCOCAP->Clear();
  for(int i=0; i<64; i++)
  {
    cmbVCOCAP->Items->Add(i);
  };
  cmbVCOCAP->ItemIndex = 20;
//==== 0x0A ==========================
  //BCODE[5:0]
  cmbBCODE->Clear();
  for(int i=7; i<36; i++)
  {
    cmbBCODE->Items->Add(i);
  };
  cmbBCODE->ItemIndex = 5;
//==== 0x0B ==========================
  //ACODE[3:0]
  cmbACODE->Clear();
  for(int i=0; i<8; i++)
  {
    cmbACODE->Items->Add(i);
  };
  cmbACODE->ItemIndex = 0;
  //PD_VCOCOMP_SX
  cmbPD_VCOCOMP_SX->Checked = true;
  //ENLOBUF
  chkENLOBUF->Checked = true;
  //ENLAMP
  chkENLAMP->Checked = true;
  //TRI
  chkTRI->Checked = false;
//==== 0x0C ==========================
  //POL
  chkPOL->Checked = false;
  //PFDPD
  chkPFDPD->Checked = true;
  //ENFEEDDIV
  chkENFEEDDIV->Checked = true;
  //PFDCLKP
  chkPFDCLKP->Checked = true;
  //BCLKSEL
  rgrBCLKSEL->ItemIndex = 2;
  //BINSEL
  rgrBINSEL->ItemIndex = 0;

  //Set frequency
  if(m_cMAddr == RxPllAddr)
  {
    txtDesFreq->Value = 1.950;
  }
  else
  {
    txtDesFreq->Value = 2.140;
  };


  lblBSTATE->Caption = "Not Running";
  lblBSIG->Caption = "0x000000";


  SetGuiDecode();
  CalcIntPllData();
  CalcPLLData();

#ifdef HIDE_FREQ
//  grbFreq->Width = 160;
//  grbFreq->Height = 104;
//  grbOutFreq->Top = 16;
  rgrMODE->Visible = false;
#else
//  grbFreq->Width = 545;
//  grbFreq->Height = 273;
#endif

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void TfrmTxPLL::SetGuiDecode()
{
	if(rgrDecode->ItemIndex == 0)
  {
  	//Decode
  	chbPwrPllMods->Enabled = true;

    chkENLOBUF->Enabled = false;
    chkENLAMP->Enabled = false;
    //rgrTRI->Enabled = false;
    chkTRI->Enabled = false;
    //rgrPOL->Enabled = false;
    chkPOL->Enabled = false;
    chkPFDPD->Enabled = false;
    chkENFEEDDIV->Enabled = false;
    //rgrPFDCLKP->Enabled = false;
    chkPFDCLKP->Enabled = false;
    cmbPD_VCOCOMP_SX->Enabled = false;
  }
  else
  {
  	//Direct control
  	chbPwrPllMods->Enabled = false;

    chkENLOBUF->Enabled = true;
    chkENLAMP->Enabled = true;
    //rgrTRI->Enabled = true;
    chkTRI->Enabled = true;
    //rgrPOL->Enabled = true;
    chkPOL->Enabled = true;
    chkPFDPD->Enabled = true;
    chkENFEEDDIV->Enabled = true;
    //rgrPFDCLKP->Enabled = true;
    chkPFDCLKP->Enabled = true;
    cmbPD_VCOCOMP_SX->Enabled = true;
  };
};


//----------------------------------------------------------------------------
// Calculates real frequency, Nint, Nfrac, VCO selection and VCO frequency
//----------------------------------------------------------------------------
void TfrmTxPLL::CalcFreq(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco)
{
	double dMul = 1;
	double dFvco;
	double dN;
	double dTmp;
	int iNint;
	int iNfrac;

  //VCO 4-5GHz
  if     ((dDF >= (dlgFreqVsCap->sVco1.dFreq[0]/2.0)) && (dDF < (dlgFreqVsCap->sVco1.dFreq[dlgFreqVsCap->sVco1.iRef-1]/2)))   { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 1; }
  else if((dDF >= (dlgFreqVsCap->sVco1.dFreq[0]/4.0)) && (dDF < (dlgFreqVsCap->sVco1.dFreq[dlgFreqVsCap->sVco1.iRef-1]/4)))   { dMul = (double) 4.0 / 1.0; iDInd = 2; iVCO = 1; }
  else if((dDF >= (dlgFreqVsCap->sVco1.dFreq[0]/8.0)) && (dDF < (dlgFreqVsCap->sVco1.dFreq[dlgFreqVsCap->sVco1.iRef-1]/8)))   { dMul = (double) 8.0 / 1.0; iDInd = 3; iVCO = 1; }
  else if((dDF >= (dlgFreqVsCap->sVco1.dFreq[0]/16.0)) && (dDF < (dlgFreqVsCap->sVco1.dFreq[dlgFreqVsCap->sVco1.iRef-1]/16))) { dMul = (double) 16.0/ 1.0; iDInd = 4; iVCO = 1; }

  //VCO 5-6GHz
  else if((dDF >= (dlgFreqVsCap->sVco2.dFreq[0]/2.0)) && (dDF < (dlgFreqVsCap->sVco2.dFreq[dlgFreqVsCap->sVco2.iRef-1]/2)))   { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 2; }
  else if((dDF >= (dlgFreqVsCap->sVco2.dFreq[0]/4.0)) && (dDF < (dlgFreqVsCap->sVco2.dFreq[dlgFreqVsCap->sVco2.iRef-1]/4)))   { dMul = (double) 4.0 / 1.0; iDInd = 2; iVCO = 2; }
  else if((dDF >= (dlgFreqVsCap->sVco2.dFreq[0]/8.0)) && (dDF < (dlgFreqVsCap->sVco2.dFreq[dlgFreqVsCap->sVco2.iRef-1]/8)))   { dMul = (double) 8.0 / 1.0; iDInd = 3; iVCO = 2; }
  else if((dDF >= (dlgFreqVsCap->sVco2.dFreq[0]/16.0)) && (dDF < (dlgFreqVsCap->sVco2.dFreq[dlgFreqVsCap->sVco2.iRef-1]/16))) { dMul = (double) 16.0/ 1.0; iDInd = 4; iVCO = 2; }

  //VCO 6-7-Hz
  else if((dDF >= (dlgFreqVsCap->sVco3.dFreq[0]/2.0)) && (dDF < (dlgFreqVsCap->sVco3.dFreq[dlgFreqVsCap->sVco3.iRef-1]/2)))   { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 3; }
  else if((dDF >= (dlgFreqVsCap->sVco3.dFreq[0]/4.0)) && (dDF < (dlgFreqVsCap->sVco3.dFreq[dlgFreqVsCap->sVco3.iRef-1]/4)))   { dMul = (double) 4.0 / 1.0; iDInd = 2; iVCO = 3; }
  else if((dDF >= (dlgFreqVsCap->sVco3.dFreq[0]/8.0)) && (dDF < (dlgFreqVsCap->sVco3.dFreq[dlgFreqVsCap->sVco3.iRef-1]/8)))   { dMul = (double) 8.0 / 1.0; iDInd = 3; iVCO = 3; }
  else if((dDF >= (dlgFreqVsCap->sVco3.dFreq[0]/16.0)) && (dDF < (dlgFreqVsCap->sVco3.dFreq[dlgFreqVsCap->sVco3.iRef-1]/16))) { dMul = (double) 16.0/ 1.0; iDInd = 4; iVCO = 3; }

  //VCO 7-8-Hz
  //else if((dDF >= (dlgFreqVsCap->sVco4.dFreq[0]/2.0)) && (dDF < (dlgFreqVsCap->sVco4.dFreq[dlgFreqVsCap->sVco4.iRef-1]/2))) { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 4; }
  else if((dDF >= (dlgFreqVsCap->sVco4.dFreq[0]/2.0)))                                                                        { dMul = (double) 2.0 / 1.0; iDInd = 1; iVCO = 4; }
  else if((dDF >= (dlgFreqVsCap->sVco4.dFreq[0]/4.0)) && (dDF < (dlgFreqVsCap->sVco4.dFreq[dlgFreqVsCap->sVco4.iRef-1]/4)))   { dMul = (double) 4.0 / 1.0; iDInd = 2; iVCO = 4; }
  else if((dDF >= (dlgFreqVsCap->sVco4.dFreq[0]/8.0)) && (dDF < (dlgFreqVsCap->sVco4.dFreq[dlgFreqVsCap->sVco4.iRef-1]/8)))   { dMul = (double) 8.0 / 1.0; iDInd = 3; iVCO = 4; }
  else if((dDF >= (dlgFreqVsCap->sVco4.dFreq[0]/16.0)) && (dDF < (dlgFreqVsCap->sVco4.dFreq[dlgFreqVsCap->sVco4.iRef-1]/16))) { dMul = (double) 16.0/ 1.0; iDInd = 4; iVCO = 4; }

	dFvco = dMul * dDF;
	Fvco = dFvco;
  dN = 1000000000/m_dRefF;
  dN *= dFvco;

  //Because 203 = double 202.9999999999... and double casting to int gives 202, not 203!!!
  if((int)dN < (int)(dN + 1/pow(2, 23))) dN += 1/pow(2, 23);

	iNint = (int)dN;
	iNfrac = (double)(dN - iNint) * pow(2, 23);
	Nint = iNint;
	Nfrac = iNfrac;

	dTmp = (double)iNfrac/(double)pow(2, 23);
	dDiv = (double)(dTmp + (double)iNint);
  rdRF = (m_dRefF/1000000000)*(1.0/dMul)*dDiv;

};

//----------------------------------------------------------------------------
// Accoerding to Danny's Whish
// Calculates real frequency, Nint, Nfrac, VCO frequency
//----------------------------------------------------------------------------
void TfrmTxPLL::CalcFreqDannyWhish(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco)
{
	double dMul;
	double dFvco;
	double dN;
	double dTmp;
	int iNint;
	int iNfrac;


  //VCO 7-8-Hz
  dMul = (double) 4.0/1.0; iDInd = 2; iVCO = 4;

	dFvco = dMul * dDF;
	Fvco = dFvco;
  dN = 1000000000/m_dRefF;
  dN *= dFvco;

  //Because 203 = double 202.9999999999... and double casting to int gives 202, not 203!!!
  if((int)dN < (int)(dN + 1/pow(2, 23))) dN += 1/pow(2, 23);

	iNint = (int)dN;
	iNfrac = (double)(dN - iNint) * pow(2, 23);
	Nint = iNint;
	Nfrac = iNfrac;

	dTmp = (double)iNfrac/(double)pow(2, 23);
	dDiv = (double)(dTmp + (double)iNint);
  rdRF = (m_dRefF/1000000000)*(1.0/dMul)*dDiv;
};

//----------------------------------------------------------------------------
// PLL fractional mode values calculation 
//----------------------------------------------------------------------------
void TfrmTxPLL::CalcPLLData()
{
	double dReal;
	double dDiv;
  int iDivInd;
	int iNint;
	int iNfrac;
	int iVCO;
  int iCap;
	double dVCO;
	String Str;

	CalcFreq(txtDesFreq->Value, dReal, dDiv, iDivInd, iNint, iNfrac, iVCO, dVCO);
  lblROutF->Caption = dReal;
  lblDiv->Caption = dDiv;
  lblNint->Caption = iNint;
  lblNfrac->Caption = iNfrac;
  lblVcoF->Caption = dVCO;

  m_bAllowSend = false;
  rgrFRANGE->ItemIndex = iDivInd;

  iCap = AutoSelectVcoCap(dVCO, iVCO);

  if((iCap > 61) && ((iVCO==2)||(iVCO==3)||(iVCO==4)))
  {
    iVCO--;
    iCap = AutoSelectVcoCap(dVCO, iVCO);
  };
  rgrSELVCO->ItemIndex = iVCO;
  cmbVCOCAP->ItemIndex = iCap;
	m_bAllowSend = true;
};

//----------------------------------------------------------------------------
// PLL integer mode values calculation 
//----------------------------------------------------------------------------
void TfrmTxPLL::CalcIntPllData()
{
  int N = 8*(cmbBCODE->ItemIndex+7) + cmbACODE->ItemIndex + 34;
  lblN->Caption = N;
  double Fvco = (m_dRefF/1000000000)*N;
  lblFvcoInt->Caption = Fvco;
  lblFvco2Int->Caption = Fvco/2;
  lblFvco4Int->Caption = Fvco/4;
  lblFvco8Int->Caption = Fvco/8;
  lblFvco16Int->Caption = Fvco/16;
};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
int TfrmTxPLL::AutoSelectVcoCap(double Freq, int iVcoInd)
{
  int iCInd;
	switch(iVcoInd)
	{
    case 1:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco1.iRef, dlgFreqVsCap->sVco1.dFreq, dlgFreqVsCap->sVco1.iCap, Freq);
		break;
    case 2:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco2.iRef, dlgFreqVsCap->sVco2.dFreq, dlgFreqVsCap->sVco2.iCap, Freq);
		break;
    case 3:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco3.iRef, dlgFreqVsCap->sVco3.dFreq, dlgFreqVsCap->sVco3.iCap, Freq);
		break;
    case 4:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco4.iRef, dlgFreqVsCap->sVco4.dFreq, dlgFreqVsCap->sVco4.iCap, Freq);
		break;
    default:
      iCInd = 0;
	};

  if(iCInd < 0) iCInd = 0;
  if(iCInd > 63) iCInd = 63;
  return iCInd;
};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void TfrmTxPLL::ChooseVcoCap()
{
  int iCInd;
	switch(rgrSELVCO->ItemIndex)
	{
    case 1:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco1.iRef, dlgFreqVsCap->sVco1.dFreq, dlgFreqVsCap->sVco1.iCap, lblVcoF->Caption.ToDouble());
		break;
    case 2:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco2.iRef, dlgFreqVsCap->sVco2.dFreq, dlgFreqVsCap->sVco2.iCap, lblVcoF->Caption.ToDouble());
		break;
    case 3:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco3.iRef, dlgFreqVsCap->sVco3.dFreq, dlgFreqVsCap->sVco3.iCap, lblVcoF->Caption.ToDouble());
		break;
    case 4:
      iCInd = QuadraticInterpol(dlgFreqVsCap->sVco4.iRef, dlgFreqVsCap->sVco4.dFreq, dlgFreqVsCap->sVco4.iCap, lblVcoF->Caption.ToDouble());
		break;
    default:
      iCInd = 0;
	};

  m_bAllowSend = false;
  if(iCInd < 0) iCInd = 0;
  if(iCInd > 63) iCInd = 63;
  cmbVCOCAP->ItemIndex = iCInd;
  m_bAllowSend = true;

  MakeData(0x00);
};
//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmTxPLL::MakeData(int rAddr)
{
	char btmp;
  int itmp;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
  //NINT[8:1]
  itmp = lblNint->Caption.ToInt();
  itmp = itmp >> 1; m_psD.cDataW[0x00] |= itmp;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
  //NINT[0]
  itmp = lblNint->Caption.ToInt();
  itmp = itmp & 0x01;
  itmp = itmp << 7; m_psD.cDataW[0x01] |= itmp;
  //NFRAC[22:16]
	itmp = 0x7F0000 & lblNfrac->Caption.ToInt();
	itmp = itmp >> 16;
	m_psD.cDataW[0x01] |= (char)itmp;

	//======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
  //NFRAC[15:8]
	itmp = 0xFF00 & lblNfrac->Caption.ToInt();
	itmp = itmp >> 8;
	m_psD.cDataW[0x02] |= (char)itmp;

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //NFRAC[7:0]
	itmp = 0xFF & lblNfrac->Caption.ToInt();
	m_psD.cDataW[0x03] |= (char)itmp;

	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
  //DITHEN
	btmp = chkDITHEN->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x04] |= btmp;
	//DITHN[2:0]
	btmp = (char)cmbDITHN->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x04] |= btmp;
	//EN
	btmp = chbPwrPllMods->Checked == true ? 1 : 0;
	btmp = btmp << 3; m_psD.cDataW[0x04] |= btmp;
  //AUTOBYP
	btmp = chbAUTOBYP->Checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x04] |= btmp;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x04] |= btmp;
  //MODE
	btmp = rgrMODE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//SELVCO[2:0]
	switch(rgrSELVCO->ItemIndex)
	{
    case 0:
    	btmp = 0x00;
		break;
    case 1:
    	btmp = 0x04;
		break;
    case 2:
    	btmp = 0x05;
		break;
    case 3:
    	btmp = 0x06;
		break;
    case 4:
    	btmp = 0x07;
		break;
    default:
    	btmp = 0x00;
	};
  btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;
	//FRANGE[2:0]
	switch(rgrFRANGE->ItemIndex)
	{
    case 0:
    	btmp = 0x00;
		break;
    case 1:
    	btmp = 0x04;
		break;
    case 2:
    	btmp = 0x05;
		break;
    case 3:
    	btmp = 0x06;
		break;
    case 4:
    	btmp = 0x07;
		break;
    default:
    	btmp = 0x00;
	};
  btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
	//SELOUT[1:0]
	btmp = (char)cmbSELOUT->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
  //EN_PFD_UP
  btmp = chbEN_PFD_UP->Checked == true ? 1 : 0;
  btmp = btmp << 7; m_psD.cDataW[0x06] |= btmp;
  //OEN_TSTD_SX
  btmp = chkOEN_TSTD_SX->Checked == true ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x06] |= btmp;
  //PASSEN_TSTOD_SD
  btmp = chkPASSEN_TSTOD_SD->Checked == true ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x06] |= btmp;
	//ICHP[4:0]
	btmp = (char)cmbICHP->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //BYPVCOREG
  btmp = chbBYPVCOREG->Checked == true ? 1 : 0;
  btmp = btmp << 7; m_psD.cDataW[0x07] |= btmp;
  //PDVCOREG
  btmp = chbPDVCOREG->Checked == true ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x07] |= btmp;
  //FSTVCOBG
  btmp = chbFSTVCOBG->Checked == true ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x07] |= btmp;
	//OFFUP[4:0]
	btmp = (char)cmbOFFUP->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //VOVCOREG[3:1]
	btmp = (char)cmbVOVCOREG->ItemIndex;
  btmp = btmp >> 1;
	btmp = btmp << 5; m_psD.cDataW[0x08] |= btmp;
  //cmbOFFDOWN[4:0]
	btmp = (char)cmbOFFDOWN->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //VOVCOREG[0]
	btmp = (char)cmbVOVCOREG->ItemIndex;
  btmp = btmp & 0x01;
	btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;
  //VCOCAP[5:0]
  btmp = 0x3F & cmbVCOCAP->ItemIndex;


	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
	//BCODE[5:0]
	btmp = 0x00;
	switch(cmbBCODE->ItemIndex)
	{
    case 0x0:
    	btmp = 0x09;
		break;
    case 0x1:
    	btmp = 0x08;
		break;
    case 0x2:
    	btmp = 0x0C;
		break;
    case 0x3:
    	btmp = 0x0E;
		break;
    case 0x4:
    	btmp = 0x0F;
		break;
    case 0x5:
    	btmp = 0x03;
		break;
    case 0x6:
    	btmp = 0x01;
		break;
    case 0x7:
    	btmp = 0x00;
		break;
    case 0x8:
    	btmp = 0x04;
		break;
    case 0x9:
    	btmp = 0x06;
		break;
    case 0xA:
    	btmp = 0x07;
		break;
    case 0xB:
    	btmp = 0x23;
		break;
    case 0xC:
    	btmp = 0x21;
		break;
    case 0x0D:
    	btmp = 0x20;
		break;
    case 0x0E:
    	btmp = 0x24;
		break;
    case 0x0F:
    	btmp = 0x26;
		break;
    case 0x10:
    	btmp = 0x27;
		break;
    case 0x11:
    	btmp = 0x33;
		break;
    case 0x12:
    	btmp = 0x31;
		break;
    case 0x13:
    	btmp = 0x30;
		break;
    case 0x14:
    	btmp = 0x34;
		break;
    case 0x15:
    	btmp = 0x36;
		break;
    case 0x16:
    	btmp = 0x37;
		break;
    case 0x17:
    	btmp = 0x3B;
		break;
    case 0x18:
    	btmp = 0x39;
		break;
    case 0x19:
    	btmp = 0x38;
		break;
    case 0x1A:
    	btmp = 0x3C;
		break;
    case 0x1B:
    	btmp = 0x3E;
		break;
    case 0x1C:
    	btmp = 0x3F;
		break;
  };
  btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
	//ACODE[3:0]
	btmp = 0x00;
	switch(cmbACODE->ItemIndex)
	{
  	//DC Calibration
    case 0x0:
    	btmp = 0x07;
		break;
    case 0x1:
    	btmp = 0x03;
		break;
    case 0x2:
    	btmp = 0x01;
		break;
    case 0x3:
    	btmp = 0x00;
		break;
    case 0x4:
    	btmp = 0x08;
		break;
    case 0x5:
    	btmp = 0x0C;
		break;
    case 0x6:
    	btmp = 0x0E;
		break;
    case 0x7:
    	btmp = 0x0F;
		break;
  };
  btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
  //PD_VCOCOMP_SX
  btmp = cmbPD_VCOCOMP_SX->Checked == true ? 0 : 1;
  btmp = btmp << 3; m_psD.cDataW[0x0B] |= btmp;
	//ENLOBUF
	btmp = chkENLOBUF->Checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x0B] |= btmp;
	//ENLAMP
	btmp = chkENLAMP->Checked == true ? 1 : 0;
	btmp = btmp << 1; m_psD.cDataW[0x0B] |= btmp;
	//TRI
  btmp = chkTRI->Checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	//POL
  btmp = chkPOL->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x0C] |= btmp;
	//PFDPD
	btmp = chkPFDPD->Checked == true ? 0 : 1;
	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
	//ENFEEDDIV
	btmp = chkENFEEDDIV->Checked == true ? 1 : 0;
	btmp = btmp << 5; m_psD.cDataW[0x0C] |= btmp;
	//PFDCLKP
	btmp = chkPFDCLKP->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
  //BCLKSEL
	btmp = (char)(rgrBCLKSEL->ItemIndex & 0x03);
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
  //BINSEL
	btmp = (char)(rgrBINSEL->ItemIndex & 0x01);
	btmp = btmp << 1; m_psD.cDataW[0x0C] |= btmp;
  //BSTART
	btmp = 0x00;
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;


	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{
		//User mode
		case 0x00:
			m_psD.iToW = 5;
			m_psD.iWInd[0] = 0x00;
      m_psD.iWInd[1] = 0x01;
      m_psD.iWInd[2] = 0x02;
      m_psD.iWInd[3] = 0x03;
      m_psD.iWInd[4] = 0x05;
		break;

		case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x1B:
			m_psD.iToW = 1;
      m_psD.iWInd[0] = 0x04;
		break;

		case 0x06:
    case 0x07:
    case 0x08:
			m_psD.iToW = 1;
      m_psD.iWInd[0] = 0x05;
		break;

		case 0x09:
    case 0x19:
    case 0x1A:
    case 0x1C:
			m_psD.iToW = 1;
      m_psD.iWInd[0] = 0x06;
		break;

    case 0x0A:
    case 0x1D:
    case 0x1E:
    case 0x1F:
			m_psD.iToW = 1;
      m_psD.iWInd[0] = 0x07;
		break;

    case 0x0B:
    case 0x0C:
    case 0x20:
			m_psD.iToW = 2;
      m_psD.iWInd[0] = 0x08;
      m_psD.iWInd[1] = 0x09;
		break;

    //Test mode
		case 0x0D:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0A;
		break;

		case 0x0E:
    case 0x0F:
    case 0x18:
    case 0x10:
    case 0x11:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0B;
		break;

    case 0x12:
    case 0x13:
    case 0x15:
    case 0x17:
    case 0x21:
    case 0x22:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0C;
		break;

    //Customer Mode
		case 0x80:
			m_psD.iToW = 1;
      m_psD.iWInd[0] = 0x05;
		break;

		default:
			m_psD.iToW = 0;
	};
}

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::btnCalcClick(TObject *Sender)
{
  //if((txtDesFreq->Value < 0.25) || (txtDesFreq->Value > 4.5))
  double dDesFreq = (double)txtDesFreq->Value;
  if((dDesFreq < 0.2) || (dDesFreq > 4.5))
  {
    //ShowMessage("Incorrect Frequency Value.\nShould be between 0.25 and 4.5GHz.");
    ShowMessage("Incorrect Frequency Value.\nShould be between 0.2 and 4.5GHz.");
    return;
  };

	CalcPLLData();
  if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };

  //Download VCO Cap as well
  if(m_bAllowSend){ MakeData(0x0C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

void __fastcall TfrmTxPLL::chkDITHENClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbDITHNChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chbPwrPllModsClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::rgrDecodeClick(TObject *Sender)
{
	SetGuiDecode();
	if(m_bAllowSend){ MakeData(0x04); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::rgrMODEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::rgrSELVCOClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x06); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::rgrFRANGEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x07); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbSELOUTChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x08); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbICHPChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbOFFUPChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbOFFDOWNChange(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x0B); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbVCOCAPChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbBCODEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  CalcIntPllData();	
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::cmbACODEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  CalcIntPllData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkENLOBUFClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0F); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkENLAMPClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x10); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkTRIClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x11); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkPOLClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x12); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkPFDPDClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x13); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chkENFEEDDIVClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x15); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chkPFDCLKPClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x17); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::cmbPD_VCOCOMP_SXClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x18); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chkOEN_TSTD_SXClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x19); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chkPASSEN_TSTOD_SDClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chbAUTOBYPClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1B); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chbEN_PFD_UPClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::chbBYPVCOREGClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chbPDVCOREGClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::chbFSTVCOBGClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1F); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::cmbVOVCOREGChange(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x20); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::rgrBCLKSELClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x21); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTxPLL::rgrBINSELClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x22); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//--------------------------------------------------------------------------- 


//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void TfrmTxPLL::MakeWriteAll()
{
	MakeData(0xFFFF);
/*
	m_psD.iToW = m_psD.iLen;
	for(int i=0; i<m_psD.iLen; i++)
	{
		m_psD.iWInd[i] = i;
	};
*/
  m_psD.iToW = 0xD;
  m_psD.iWInd[0x0] = 0x00;
  m_psD.iWInd[0x1] = 0x01;
  m_psD.iWInd[0x2] = 0x02;
  m_psD.iWInd[0x3] = 0x03;
  m_psD.iWInd[0x4] = 0x04;
  m_psD.iWInd[0x5] = 0x05;
  m_psD.iWInd[0x6] = 0x06;
  m_psD.iWInd[0x7] = 0x07;
  m_psD.iWInd[0x8] = 0x08;
  m_psD.iWInd[0x9] = 0x09;
  m_psD.iWInd[0xA] = 0x0A;
  m_psD.iWInd[0xB] = 0x0B;
  m_psD.iWInd[0xC] = 0x0C;
  //m_psD.iWInd[0xD] = 0x0F;
};

//----------------------------------------------------------------------------
// Save the chip configuration to the file
//----------------------------------------------------------------------------
bool TfrmTxPLL::ChipVsGui(ofstream &out, String Caption, bool bWrAll)
{
  bool bRez = true;
	char str[64] = "";
  char str1[64] = "";
  int itmp, itmp1;

  out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;


  //NINT[8:0]
  //x itmp = 0;
  //x itmp = m_psD.cDataR[0x00] & 0xFF;
  //x itmp = itmp << 1;
  //x itmp = itmp | ((m_psD.cDataR[0x01] & 0x80) >> 7);
  itmp = NINT();
  if((lblNint->Caption.ToInt() != itmp) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| NINT[8:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, lblNint->Caption.c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //NFRAC[22:0]
  //x itmp = 0;
  //x itmp = 0x7F & m_psD.cDataR[0x01];
  //x itmp = itmp << 8;
  //x itmp = itmp | (0xFF & m_psD.cDataR[0x02]);
  //x itmp = itmp << 8;
  //x itmp = itmp | (0xFF & m_psD.cDataR[0x03]);
  itmp = NFRAC();
  if((lblNfrac->Caption.ToInt() != itmp) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| NFRAC[22:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, lblNfrac->Caption.c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DITHEN
  if((chkDITHEN->Checked != (bool)DITHEN_r04_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DITHEN"; out.width(2); out << "|";	out.width(40);
    if(chkDITHEN->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(DITHEN_r04_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DITHN[2:0]
  if(((cmbDITHN->ItemIndex) != DITHN_r04_b64()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DITHN[2:0]"; out.width(2); out << "|";	out.width(40);
    itmp = cmbDITHN->ItemIndex + 1;
    out << itmp;	out.width(10); out << "Bit(s)"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = DITHN_r04_b64(); itmp++;
    out << itmp;	out.width(10); out << "Bit(s)"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN
  if((chbPwrPllMods->Checked != (bool)EN_r04_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrPllMods->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(EN_r04_b33()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //AUTOBYP
  if((chbAUTOBYP->Checked != (bool)AUTOBYP_r04_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| AUTOBYP"; out.width(2); out << "|";	out.width(40);
    if(chbAUTOBYP->Checked) strcpy(str, "Disabled"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(AUTOBYP_r04_b22()) strcpy(str, "Disabled"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DECODE
  if((rgrDecode->ItemIndex != DECODE_r04_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode->ItemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	if(DECODE_r04_b11()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //MODE
  if((rgrMODE->ItemIndex != MODE_r04_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| MODE"; out.width(2); out << "|";	out.width(40);
    if(rgrMODE->ItemIndex == 1) strcpy(str, "Integer Mode"); else strcpy(str, "Fractional Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  if(MODE_r04_b00()) strcpy(str, "Integer Mode"); else strcpy(str, "Fractional Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SELVCO[2:0]
  memset(str1, '\0', sizeof(str1));
  //x itmp = m_psD.cDataR[0x05] & 0xE0;
  //x itmp = itmp >> 5;
  itmp = SELVCO_r05_b75();
  switch(itmp)
	{
    case 0x00:
  	  strcpy(str1, rgrSELVCO->Items->Strings[0].c_str());
      itmp1 = 0;
  	break;
    case 0x04:
    	strcpy(str1, rgrSELVCO->Items->Strings[1].c_str());
      itmp1 = 1;
  	break;
    case 0x05:
    	strcpy(str1, rgrSELVCO->Items->Strings[2].c_str());
      itmp1 = 2;
  	break;
    case 0x06:
    	strcpy(str1, rgrSELVCO->Items->Strings[3].c_str());
      itmp1 = 3;
  	break;
    case 0x07:
    	strcpy(str1, rgrSELVCO->Items->Strings[4].c_str());
      itmp1 = 4;
  	break;
    default:
    	strcpy(str1, "WRONG DATA!!!");
      itmp1 = -2;
  };

  if((rgrSELVCO->ItemIndex != itmp1) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| SELVCO[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrSELVCO->Items->Strings[rgrSELVCO->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    out << str1;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FRANGE[2:0]
  memset(str1, '\0', sizeof(str1));
	//x itmp = m_psD.cDataR[0x05] & 0x1C;
  //x itmp = itmp >> 2;
  itmp = FRANGE_r05_b42();
	switch(itmp)
  {
    case 0x00:
    	strcpy(str1, rgrFRANGE->Items->Strings[0].c_str());
      itmp = 0;
  	break;
    case 0x04:
    	strcpy(str1, rgrFRANGE->Items->Strings[1].c_str());
      itmp = 1;
  	break;
    case 0x05:
    	strcpy(str1, rgrFRANGE->Items->Strings[2].c_str());
      itmp = 2;
  	break;
    case 0x06:
    	strcpy(str1, rgrFRANGE->Items->Strings[3].c_str());
      itmp = 3;
  	break;
    case 0x07:
    	strcpy(str1, rgrFRANGE->Items->Strings[4].c_str());
      itmp = 4;
  	break;
    default:
      itmp = -2;
    	strcpy(str, "WRONG DATA!!!");
	};
  if((itmp != rgrFRANGE->ItemIndex) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| FRANGE[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrFRANGE->Items->Strings[rgrFRANGE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    out << str1;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SELOUT[1:0]
  if((cmbSELOUT->ItemIndex != SELOUT_r05_b10()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| SELOUT[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbSELOUT->Items->Strings[cmbSELOUT->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = SELOUT_r05_b10();
    strcpy(str, cmbSELOUT->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_PFD_UP
  if((chbEN_PFD_UP->Checked != (bool)EN_PFD_UP_r06_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| EN_PFD_UP"; out.width(2); out << "|";	out.width(40);
    if(chbEN_PFD_UP->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(EN_PFD_UP_r06_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //OEN_TSTD_SX
  if((chkOEN_TSTD_SX->Checked != (bool)OEN_TSTD_SX_r06_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| OEN_TSTD_SX"; out.width(2); out << "|";	out.width(40);
    if(chkOEN_TSTD_SX->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(OEN_TSTD_SX_r06_b66()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PASSEN_TSTOD_SD
  if((chkPASSEN_TSTOD_SD->Checked != (bool)PASSEN_TSTOD_SD_r06_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PASSEN_TSTOD_SD"; out.width(2); out << "|";	out.width(40);
    if(chkPASSEN_TSTOD_SD->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PASSEN_TSTOD_SD_r06_b55()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICHP[4:0]
  if((cmbICHP->ItemIndex != ICHP_r06_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| ICHP[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbICHP->Items->Strings[cmbICHP->ItemIndex].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = ICHP_r06_b40();
    strcpy(str, cmbICHP->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BYPVCOREG
  if((chbBYPVCOREG->Checked != (bool)BYPVCOREG_r07_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BYPVCOREG"; out.width(2); out << "|";	out.width(40);
    if(chbBYPVCOREG->Checked) strcpy(str, "Bypassed"); else strcpy(str, "Not Bypassed");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(BYPVCOREG_r07_b77()) strcpy(str, "Bypassed"); else strcpy(str, "Not Bypassed");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PDVCOREG
  if((chbPDVCOREG->Checked != (bool)PDVCOREG_r07_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PDVCOREG"; out.width(2); out << "|";	out.width(40);
    if(chbPDVCOREG->Checked) strcpy(str, "Powered Down"); else strcpy(str, "Powered Up");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PDVCOREG_r07_b66()) strcpy(str, "Powered Down"); else strcpy(str, "Powered Up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FSTVCOBG
  if((chbFSTVCOBG->Checked != (bool)FSTVCOBG_r07_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| FSTVCOBG"; out.width(2); out << "|";	out.width(40);
    if(chbFSTVCOBG->Checked) strcpy(str, "Resistor Shorted"); else strcpy(str, "Switch Open");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(FSTVCOBG_r07_b55()) strcpy(str, "Resistor Shorted"); else strcpy(str, "Switch Open");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  }; 

  //OFFUP[4:0]
  if((cmbOFFUP->ItemIndex != OFFUP_r07_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| OFFUP[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbOFFUP->Items->Strings[cmbOFFUP->ItemIndex].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = OFFUP_r07_b40();
    strcpy(str, cmbOFFUP->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VOVCOREG[3:0]
  if((cmbVOVCOREG->ItemIndex != VOVCOREG()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| VOVCOREG[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVOVCOREG->Items->Strings[cmbVOVCOREG->ItemIndex].c_str());
    out << str;	out.width(10); out << "V"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = VOVCOREG();
    strcpy(str, cmbVOVCOREG->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "V"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //OFFDOWN[4:0]
  if((cmbOFFDOWN->ItemIndex != OFFDOWN_r08_b40()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| OFFDOWN[4:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbOFFDOWN->Items->Strings[cmbOFFDOWN->ItemIndex].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = OFFDOWN_r08_b40();
    strcpy(str, cmbOFFDOWN->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //VCOCAP[5:0]
  //itmp1  = m_psD.cDataR[0x0F] & 0x01;
  //itmp1  = itmp1 << 5;
  //itmp1 |= m_psD.cDataR[0x09] & 0x1F;
  itmp1 = VCOCAP_r09_b50();
  if((cmbVCOCAP->ItemIndex != itmp1) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| VCOCAP[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbVCOCAP->Items->Strings[cmbVCOCAP->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbVCOCAP->Items->Strings[itmp1].c_str());
    out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };


  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  if(bWrAll)
  {
    //VTUNE_H
    memset(str, '\0', sizeof(str));
    out.width(32); out << "| VTUNE_H"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
 	  memset(str, '\0', sizeof(str));
    if(VTUNE_H_r0A_b77()) strcpy(str, "1"); else strcpy(str, "0");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //VTUNE_L
    memset(str, '\0', sizeof(str));
    out.width(32); out << "| VTUNE_L"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
 	  memset(str, '\0', sizeof(str));
    if(VTUNE_L_r0A_b66()) strcpy(str, "1"); else strcpy(str, "0");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  };

  //BCODE[5:0]
  memset(str1, '\0', sizeof(str1));
  itmp = BCODE_r0A_b50();
	switch(itmp)
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
      itmp1 = -2;
    	strcpy(str1, "WRONG DATA!!!");
	};
  if(((itmp1 < 0) || (itmp1-7 != cmbBCODE->ItemIndex)) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BCODE[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbBCODE->Items->Strings[cmbBCODE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    if(itmp1 > 0) out << itmp1;
    else out << str1;
    out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ACODE[3:0]
  itmp = ACODE_r0B_b74();
	switch(itmp)
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
      itmp1 = -2;
    	strcpy(str1, "WRONG DATA!!!");
	};
  if(((itmp1 < 0) || (itmp1 != cmbACODE->ItemIndex)) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ACODE[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbACODE->Items->Strings[cmbACODE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    //memset(str, '\0', sizeof(str));
    if(itmp1 > 0) out << itmp1;
    else out << str1;
    out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_VCOCOMP_SX
  if((cmbPD_VCOCOMP_SX->Checked == (bool)PD_VCOCOMP_SX_r0B_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_VCOCOMP_SX"; out.width(2); out << "|";	out.width(40);
    if(cmbPD_VCOCOMP_SX->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_VCOCOMP_SX_r0B_b33()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENLOBUF
  if((chkENLOBUF->Checked != (bool)ENLOBUF_r0B_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ENLOBUF"; out.width(2); out << "|";	out.width(40);
    if(chkENLOBUF->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(ENLOBUF_r0B_b22()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENLAMP
  if((chkENLAMP->Checked != (bool)ENLAMP_r0B_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| ENLAMP"; out.width(2); out << "|";	out.width(40);
    if(chkENLAMP->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(ENLAMP_r0B_b11()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TRI
  if((chkTRI->Checked != (bool)TRI_r0B_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| TRI"; out.width(2); out << "|";	out.width(40);
    if(chkTRI->Checked) strcpy(str, "Tri-State Mode"); else strcpy(str, "Normal Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(TRI_r0B_b00()) strcpy(str, "Tri-State Mode"); else strcpy(str, "Normal Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //POL
  if((chkPOL->Checked != (bool)POL_r0C_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| POL"; out.width(2); out << "|";	out.width(40);
    if(chkPOL->Checked) strcpy(str, "Inverted"); else strcpy(str, "Normal");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(POL_r0C_b77()) strcpy(str, "Inverted"); else strcpy(str, "Normal");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PFDPD
  if((chkPFDPD->Checked == (bool)PFDPD_r0C_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PFDPD"; out.width(2); out << "|";	out.width(40);
    if(chkPFDPD->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PFDPD_r0C_b66()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENFEEDDIV
  if((chkENFEEDDIV->Checked != (bool)ENFEEDDIV_r0C_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ENFEEDDIV"; out.width(2); out << "|";	out.width(40);
    if(chkENFEEDDIV->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(ENFEEDDIV_r0C_b55()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PFDCLKP
  if((chkPFDCLKP->Checked != (bool)PFDCLKP_r0C_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ENFEEDDIV"; out.width(2); out << "|";	out.width(40);
    if(chkPFDCLKP->Checked) strcpy(str, "Inverted"); else strcpy(str, "In Phase");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PFDCLKP_r0C_b44()) strcpy(str, "Inverted"); else strcpy(str, "In Phase");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //BCLKSEL[1:0]
  itmp1 = BCLKSEL_r0C_b32();
  if((rgrBCLKSEL->ItemIndex != itmp1) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BCLKSEL[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrBCLKSEL->Items->Strings[rgrBCLKSEL->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    if(itmp1 > 2) { itmp1 = 2; false; };
    strcpy(str, rgrBCLKSEL->Items->Strings[itmp1].c_str());
    out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BINSEL
  itmp1 = BINSEL_r0C_b11();
  if((rgrBINSEL->ItemIndex != itmp1) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BINSEL"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrBINSEL->Items->Strings[rgrBINSEL->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrBINSEL->Items->Strings[itmp1].c_str());
    out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if(bWrAll)
  {
    //BSTART
    memset(str, '\0', sizeof(str));
    out.width(32); out << "| BSTART"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
 	  memset(str, '\0', sizeof(str));
    if(BSTART_r0C_b00()) strcpy(str, "1"); else strcpy(str, "0");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //BSTATE
    memset(str, '\0', sizeof(str));
    out.width(32); out << "| BSTATE"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
 	  memset(str, '\0', sizeof(str));
    if(BSTATE_r0D_b77()) strcpy(str, "1"); else strcpy(str, "0");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

  	//BSIG[22:16]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BSIG[22:16]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = BSIG2216_r0D_b60();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

  	//BSIG[15:8]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BSIG[15:8]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = BSIG158_r0E_b70();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

  	//BSIG[7:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BSIG[7:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = BSIG70_r0F_b70();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  };

  if(bRez && (!bWrAll))
  {
  	out.width(136); out << "| CHIP Configuration EQUALS GUI Configuration"; out.width(2); out << "|";
	  out << endl;
  };
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "" << endl;
	out << "" << endl;

  return bRez;
};

//----------------------------------------------------------------------------
// Writes Register - Value format to the file.
//----------------------------------------------------------------------------
void TfrmTxPLL::MakeRVFFile(ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //0x00
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0xFF);
  out << iRval; out << endl;

  //0x01
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
  out << iRval; out << endl;

  //0x02
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << iRval; out << endl;

  //0x03
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << iRval; out << endl;

  //0x04
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0xFF);
  out << iRval; out << endl;

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xBF);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x3F);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << iRval; out << endl;

  //0x0C
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << iRval; out << endl;

  //0x0D - Read Only

  //0x0E - Read Only

  //0x0F - Read Only

};

//----------------------------------------------------------------------------
// Writes RFIF register format to the file.
//----------------------------------------------------------------------------
void TfrmTxPLL::MakeRFIFFile(ofstream &out, char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  if(m_cMAddr == TxPllAddr) out << "echo \"Now programming the Lime Tx PLL\"" << endl << endl;
  else                      out << "echo \"Now programming the Lime Rx PLL\"" << endl << endl;

  //0x00
  //out << "# Register(s): NINT[8:1]" << endl;
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x01
  //out << "# Register(s): NINT[0], NFRAC[22:16]" << endl;
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x02
  //out << "# Register(s): NFRAC[15:8]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): NFRAC[7:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x04
  //out << "# Register(s): DITHEN, DITHN[2:0], EN, AUTOBYP, DECODE, MODE" << endl;
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x05
  //out << "# Register(s): SELVCO[2:0], FRANGE[2:0], SELOUT[1:0]" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): EN_PFD_UP, OEN_TSTD_SX, PASSEN_TSTOD_SD, ICHP[4:0]" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): BYPVCOREG, PDVCOREG, FSTVCOBG, OFFUP[4:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): VOVCOREG[3:1], OFFDOWN[4:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): VOVCOREG[0], VCOCAP[5:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xBF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): BCODE[5:0]" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): ACODE[3:0], PD_VCOCOMP_SX, ENLOBUF, ENLAMP, TRI" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x0C
  //out << "# Register(s): POL, PFDPD, ENFEEDDIV, PFDCLKP, BCLKSEL[1:0], BINSEL, BSTART" << endl;
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x0D - Read Only

  //0x0E - Read Only

  //0x0F - Read Only

  if(m_cMAddr == TxPllAddr) out << endl << "echo \"Tx PLL programming complete\"" << endl << endl;
  else                      out << endl << "echo \"Rx PLL programming complete\"" << endl << endl;

};

//---------------------------------------------------------------------------
// Sets GUI under data from chip
//---------------------------------------------------------------------------
bool TfrmTxPLL::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;
  int iNint;
  int iFrac;
  double dFreq;


  m_bAllowSend = false;

  //NINT[8:0]
  //itmp = 0;
  //itmp = m_psD.cDataR[0x00] & 0xFF;
  //itmp = itmp << 1;
  //itmp = itmp | ((m_psD.cDataR[0x01] & 0x80) >> 7);
  itmp = NINT(); 
  lblNint->Caption = itmp;
  iNint = itmp;

  //NFRAC[22:0]
	//itmp = 0;
	//itmp = 0x7F & m_psD.cDataR[0x01];
	//itmp = itmp << 8;
	//itmp = itmp | (0xFF & m_psD.cDataR[0x02]);
	//itmp = itmp << 8;
	//itmp = itmp | (0xFF & m_psD.cDataR[0x03]);
  itmp = NFRAC(); 
  lblNfrac->Caption = itmp;
  iFrac = itmp;

  //DITHEN
  itmp = DITHEN_r04_b77();
  chkDITHEN->Checked = itmp;

  //DITHN[2:0]
  itmp = DITHN_r04_b64(); //itmp++;
  cmbDITHN->ItemIndex = itmp;

  //EN
  itmp = EN_r04_b33();
  chbPwrPllMods->Checked = itmp;

  //AUTOBYP
  itmp = AUTOBYP_r04_b22();
  chbAUTOBYP->Checked = itmp;

  //DECODE
  itmp = DECODE_r04_b11();
  rgrDecode->ItemIndex = itmp;

  //MODE
  itmp = MODE_r04_b00();
  rgrMODE->ItemIndex = itmp;

  //SELVCO[2:0]
	itmp = SELVCO_r05_b75();
	switch(itmp)
	{
    case 0x00:
    	rgrSELVCO->ItemIndex = 0;
		break;
    case 0x04:
    	rgrSELVCO->ItemIndex = 1;
		break;
    case 0x05:
    	rgrSELVCO->ItemIndex = 2;
		break;
    case 0x06:
    	rgrSELVCO->ItemIndex = 3;
		break;
    case 0x07:
    	rgrSELVCO->ItemIndex = 4;
		break;
    default:
    	rgrSELVCO->ItemIndex = 4;
      bRez = false;
	}; 

  //FRANGE[2:0]
	itmp = FRANGE_r05_b42();
  dFreq = (double)iNint + ((double)iFrac/pow(2, 23));
  dFreq = (double)dFreq/(1000000000/m_dRefF); 
	switch(itmp)
	{
    case 0x00:
    	rgrFRANGE->ItemIndex = 0;
		break;
    case 0x04:
    	rgrFRANGE->ItemIndex = 1;
      dFreq = dFreq/2.0;
		break;
    case 0x05:
    	rgrFRANGE->ItemIndex = 2;
      dFreq = dFreq/4.0;
		break;
    case 0x06:
    	rgrFRANGE->ItemIndex = 3;
      dFreq = dFreq/8.0;
		break;
    case 0x07:
    	rgrFRANGE->ItemIndex = 4;
      dFreq = dFreq/16.0;
		break;
    default:
    	rgrFRANGE->ItemIndex = 4;
      dFreq = dFreq/16.0;
      bRez = false;
	};
  txtDesFreq->Value = dFreq;

  //SELOUT[1:0]
  itmp = SELOUT_r05_b10();
  cmbSELOUT->ItemIndex = itmp;

  //EN_PFD_UP
  itmp = EN_PFD_UP_r06_b77();
  chbEN_PFD_UP->Checked = itmp;

  //OEN_TSTD_SX
  itmp = OEN_TSTD_SX_r06_b66();
  chkOEN_TSTD_SX->Checked = itmp;

  //PASSEN_TSTOD_SD
  itmp = PASSEN_TSTOD_SD_r06_b55();
  chkPASSEN_TSTOD_SD->Checked = itmp;

  //ICHP[4:0]
  itmp = ICHP_r06_b40();
  cmbICHP->ItemIndex = itmp;

  //BYPVCOREG
  itmp = BYPVCOREG_r07_b77();
  chbBYPVCOREG->Checked = itmp;

  //PDVCOREG
  itmp = PDVCOREG_r07_b66();
  chbPDVCOREG->Checked = itmp;

  //FSTVCOBG
  itmp = FSTVCOBG_r07_b55();
  chbFSTVCOBG->Checked = itmp;  

  //OFFUP[4:0]
  itmp = OFFUP_r07_b40();
  if(itmp > 24) {itmp = 24; bRez = false;}
  cmbOFFUP->ItemIndex = itmp;

  //VOVCOREG[3:0]
  itmp = VOVCOREG();
  if(itmp > 0x0C) {itmp = 0x0C; bRez = false;}
  cmbVOVCOREG->ItemIndex = itmp;

  //OFFDOWN[4:0]
  itmp = OFFDOWN_r08_b40();
  if(itmp > 24) {itmp = 24; bRez = false;}
  cmbOFFDOWN->ItemIndex = itmp;

  //VCOCAP[5:0]
  itmp = VCOCAP_r09_b50();
  cmbVCOCAP->ItemIndex = itmp;

  //VTUNE_H
  itmp = VTUNE_H_r0A_b77();
  if(itmp) lblVTUNE_H->Caption = "1";
  else lblVTUNE_H->Caption = "0";

  //VTUNE_L
  itmp = VTUNE_L_r0A_b66();
  if(itmp) lblVTUNE_L->Caption = "1";
  else lblVTUNE_L->Caption = "0";

  //BCODE[5:0]
  itmp = BCODE_r0A_b50();
	switch(itmp)
	{
    case 0x3F:
    	cmbBCODE->ItemIndex = 35 - 7;
		break;
    case 0x3E:
    	cmbBCODE->ItemIndex = 34 - 7;
		break;
    case 0x3C:
    	cmbBCODE->ItemIndex = 33 - 7;
		break;
    case 0x38:
    	cmbBCODE->ItemIndex = 32 - 7;
		break;
    case 0x39:
    	cmbBCODE->ItemIndex = 31 - 7;
		break;
    case 0x3B:
    	cmbBCODE->ItemIndex = 30 - 7;
		break;
    case 0x37:
    	cmbBCODE->ItemIndex = 29 - 7;
		break;
    case 0x36:
    	cmbBCODE->ItemIndex = 28 - 7;
		break;
    case 0x34:
    	cmbBCODE->ItemIndex = 27 - 7;
		break;
    case 0x30:
    	cmbBCODE->ItemIndex = 26 - 7;
		break;
    case 0x31:
    	cmbBCODE->ItemIndex = 25 - 7;
		break;
    case 0x33:
    	cmbBCODE->ItemIndex = 24 - 7;
		break;
    case 0x27:
    	cmbBCODE->ItemIndex = 23 - 7;
		break;
    case 0x26:
    	cmbBCODE->ItemIndex = 22 - 7;
		break;
    case 0x24:
    	cmbBCODE->ItemIndex = 21 - 7;
		break;
    case 0x20:
    	cmbBCODE->ItemIndex = 20 - 7;
		break;
    case 0x21:
    	cmbBCODE->ItemIndex = 19 - 7;
		break;
    case 0x23:
    	cmbBCODE->ItemIndex = 18 - 7;
		break;
    case 0x07:
    	cmbBCODE->ItemIndex = 17 - 7;
		break;
    case 0x06:
    	cmbBCODE->ItemIndex = 16 - 7;
		break;
    case 0x04:
    	cmbBCODE->ItemIndex = 15 - 7;
		break;
    case 0x00:
    	cmbBCODE->ItemIndex = 14 - 7;
		break;
    case 0x01:
    	cmbBCODE->ItemIndex = 13 - 7;
		break;
    case 0x03:
    	cmbBCODE->ItemIndex = 12 - 7;
		break;
    case 0x0F:
    	cmbBCODE->ItemIndex = 11 - 7;
		break;
    case 0x0E:
    	cmbBCODE->ItemIndex = 10 - 7;
		break;
    case 0x0C:
    	cmbBCODE->ItemIndex = 9 - 7;
		break;
    case 0x08:
    	cmbBCODE->ItemIndex = 8 - 7;
		break;
    case 0x09:
    	cmbBCODE->ItemIndex = 7 - 7;
		break;
    default:
    	cmbBCODE->ItemIndex = 35 - 7;
    	bRez = false;
	};

  //ACODE[3:0]
  itmp = ACODE_r0B_b74();
	switch(itmp)
	{
    case 0x0F:
    	cmbACODE->ItemIndex = 7;
		break;
    case 0x0E:
    	cmbACODE->ItemIndex = 6;
		break;
    case 0x0C:
    	cmbACODE->ItemIndex = 5;
		break;
    case 0x08:
    	cmbACODE->ItemIndex = 4;
		break;
    case 0x00:
    	cmbACODE->ItemIndex = 3;
		break;
    case 0x01:
    	cmbACODE->ItemIndex = 2;
		break;
    case 0x03:
    	cmbACODE->ItemIndex = 1;
		break;
    case 0x07:
    	cmbACODE->ItemIndex = 0;
		break;
    default:
    	cmbACODE->ItemIndex = 7;
      bRez = false;
	};

  //PD_VCOCOMP_SX
  itmp = PD_VCOCOMP_SX_r0B_b33();
  cmbPD_VCOCOMP_SX->Checked = itmp;
  cmbPD_VCOCOMP_SX->Checked = !cmbPD_VCOCOMP_SX->Checked;

  //ENLOBUF
  itmp = ENLOBUF_r0B_b22();
  chkENLOBUF->Checked = itmp;

  //ENLAMP
  itmp = ENLAMP_r0B_b11();
  chkENLAMP->Checked = itmp;

  //TRI
  itmp = TRI_r0B_b00();
  chkTRI->Checked = itmp;

  //POL
  itmp = POL_r0C_b77();
  chkPOL->Checked = itmp;

  //PFDPD
  itmp = PFDPD_r0C_b66();
  chkPFDPD->Checked = itmp;
  chkPFDPD->Checked = !chkPFDPD->Checked;

  //ENFEEDDIV
  itmp = ENFEEDDIV_r0C_b55();
  chkENFEEDDIV->Checked = itmp;

  //PFDCLKP
  itmp = PFDCLKP_r0C_b44();
  chkPFDCLKP->Checked = itmp;

  //BCLKSEL
  itmp = BCLKSEL_r0C_b32();
  if(itmp > 2) { itmp = 2; bRez = false; };
  rgrBCLKSEL->ItemIndex = itmp;

  //BINSEL
  itmp = BINSEL_r0C_b11();
  rgrBINSEL->ItemIndex = itmp;

  //BSTART
  itmp = BSTART_r0C_b00();

  //BSTATE
  BIST_ShowState(BSTATE_r0D_b77());

  //BSIG
  BIST_ShowSignature(BSIG());

  m_bAllowSend = true;
  return bRez;
};

//----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
//----------------------------------------------------------------------------
void TfrmTxPLL::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


	//PLL_NINT[8:1]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x10 MASK 07 : 00  =";
  else                      out << "REG 0x20 MASK 07 : 00  =";
  itmp = NINT81_r00_b70();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_NINT[8:1]";
  else                      out << "  RXPLL_NINT[8:1]";
  out << endl;

	//PLL_NINT[0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x11 MASK 07 : 07  =";
  else                      out << "REG 0x21 MASK 07 : 07  =";
  itmp = NINT00_r01_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_NINT[0]";
  else                      out << "  RXPLL_NINT[0]";
  out << endl;

	//PLL_NFRAC[22:16]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x11 MASK 06 : 00  =";
  else                      out << "REG 0x21 MASK 06 : 00  =";
  itmp = NFRAC2216_r01_b60();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_NFRAC[22:16]";
  else                      out << "  RXPLL_NFRAC[22:16]";
  out << endl;

	//PLL_NFRAC[15:8]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x12 MASK 07 : 00  =";
  else                      out << "REG 0x22 MASK 07 : 00  =";
  itmp = NFRAC158_r02_b70();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_NFRAC[15:8]";
  else                      out << "  RXPLL_NFRAC[15:8]";
  out << endl;

	//PLL_NFRAC[7:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x13 MASK 07 : 00  =";
  else                      out << "REG 0x23 MASK 07 : 00  =";
  itmp = NFRAC70_r03_b70();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_NFRAC[7:0]";
  else                      out << "  RXPLL_NFRAC[7:0]";
  out << endl;

  //DITHEN
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 07 : 07  =";
  else                      out << "REG 0x24 MASK 07 : 07  =";
  itmp = DITHEN_r04_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_DITHEN";
  else                      out << "  RXPLL_DITHEN";
  out << endl;

  //DITHN[2:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 06 : 04  =";
  else                      out << "REG 0x24 MASK 06 : 04  =";
  itmp = DITHN_r04_b64();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_DITHN";
  else                      out << "  RXPLL_DITHN";
  out << endl;

  //EN
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 03 : 03  =";
  else                      out << "REG 0x24 MASK 03 : 03  =";
  itmp = EN_r04_b33();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_EN";
  else                      out << "  RXPLL_EN";
  out << endl;

  //AUTOBYP
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 02 : 02  =";
  else                      out << "REG 0x24 MASK 02 : 02  =";
  itmp = AUTOBYP_r04_b22();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_AUTOBYP";
  else                      out << "  RXPLL_AUTOBYP";
  out << endl;

  //DECODE
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 01 : 01  =";
  else                      out << "REG 0x24 MASK 01 : 01  =";
  itmp = DECODE_r04_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_DECODE";
  else                      out << "  RXPLL_DECODE";
  out << endl;

  //MODE
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x14 MASK 00 : 00  =";
  else                      out << "REG 0x24 MASK 00 : 00  =";
  itmp = MODE_r04_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_MODE";
  else                      out << "  RXPLL_MODE";
  out << endl;

  //FREQSEL[7:2]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x15 MASK 07 : 02  =";
  else                      out << "REG 0x25 MASK 07 : 02  =";
  itmp = m_psD.cDataR[0x05] & 0xFC; itmp = itmp >> 2;
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_FREQSEL";
  else                      out << "  RXPLL_FREQSEL";
  out << endl;

  //SELOUT[1:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x15 MASK 01 : 00  =";
  else                      out << "REG 0x25 MASK 01 : 00  =";
  itmp = SELOUT_r05_b10();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_SELOUT";
  else                      out << "  RXPLL_SELOUT";
  out << endl;

  //EN_PFD_UP
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x16 MASK 07 : 07  =";
  else                      out << "REG 0x26 MASK 07 : 07  =";
  itmp = EN_PFD_UP_r06_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_EN_PFD_UP";
  else                      out << "  RXPLL_EN_PFD_UP";
  out << endl;

  //OEN_TSTD_SX
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x16 MASK 06 : 06  =";
  else                      out << "REG 0x26 MASK 06 : 06  =";
  itmp = OEN_TSTD_SX_r06_b66();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_OEN_TSTD_SX";
  else                      out << "  RXPLL_OEN_TSTD_SX";
  out << endl;

  //PASSEN_TSTOD_SD
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x16 MASK 05 : 05  =";
  else                      out << "REG 0x26 MASK 05 : 05  =";
  itmp = PASSEN_TSTOD_SD_r06_b55();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_PASSEN_TSTOD_SD";
  else                      out << "  RXPLL_PASSEN_TSTOD_SD";
  out << endl;

  //ICHP[4:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x16 MASK 04 : 00  =";
  else                      out << "REG 0x26 MASK 04 : 00  =";
  itmp = ICHP_r06_b40();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_ICHP";
  else                      out << "  RXPLL_ICHP";
  out << endl;

  //BYPVCOREG
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x17 MASK 07 : 07  =";
  else                      out << "REG 0x27 MASK 07 : 07  =";
  itmp = BYPVCOREG_r07_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BYPVCOREG";
  else                      out << "  RXPLL_BYPVCOREG";
  out << endl;

  //PDVCOREG
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x17 MASK 06 : 06  =";
  else                      out << "REG 0x27 MASK 06 : 06  =";
  itmp = PDVCOREG_r07_b66();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_PDVCOREG";
  else                      out << "  RXPLL_PDVCOREG";
  out << endl;

  //FSTVCOBG
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x17 MASK 05 : 05  =";
  else                      out << "REG 0x27 MASK 05 : 05  =";
  itmp = FSTVCOBG_r07_b55();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_FSTVCOBG";
  else                      out << "  RXPLL_FSTVCOBG";
  out << endl; 

  //OFFUP[4:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x17 MASK 04 : 00  =";
  else                      out << "REG 0x27 MASK 04 : 00  =";
  itmp = OFFUP_r07_b40();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_OFFUP";
  else                      out << "  RXPLL_OFFUP";
  out << endl;

  //VOVCOREG[3:1]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x18 MASK 07 : 05  =";
  else                      out << "REG 0x28 MASK 07 : 05  =";
  itmp = VOVCOREG31_r08_b75();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_VOVCOREG[3:1]";
  else                      out << "  RXPLL_VOVCOREG[3:1]";
  out << endl;

  //OFFDOWN[4:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x18 MASK 04 : 00  =";
  else                      out << "REG 0x28 MASK 04 : 00  =";
  itmp = OFFDOWN_r08_b40();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_OFFDOWN";
  else                      out << "  RXPLL_OFFDOWN";
  out << endl;

  //VOVCOREG[0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x19 MASK 07 : 07  =";
  else                      out << "REG 0x29 MASK 07 : 07  =";
  itmp = VOVCOREG00_r09_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_VOVCOREG[0]";
  else                      out << "  RXPLL_VOVCOREG[0]";
  out << endl; 

  //VCOCAP[5:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x19 MASK 05 : 00  =";
  else                      out << "REG 0x29 MASK 05 : 00  =";
  itmp = VCOCAP_r09_b50();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_VCOCAP[5:0]";
  else                      out << "  RXPLL_VCOCAP[5:0]";
  out << endl;

  //VTUNE_H
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1A MASK 07 : 07  =";
  else                      out << "REG 0x2A MASK 07 : 07  =";
  itmp = VTUNE_H_r0A_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_VTUNE_H";
  else                      out << "  RXPLL_VTUNE_H";
  out << endl;

  //VTUNE_L
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1A MASK 06 : 06  =";
  else                      out << "REG 0x2A MASK 06 : 06  =";
  itmp = VTUNE_L_r0A_b66();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_VTUNE_L";
  else                      out << "  RXPLL_VTUNE_L";
  out << endl;

  //BCODE[5:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1A MASK 05 : 00  =";
  else                      out << "REG 0x2A MASK 05 : 00  =";
  itmp = BCODE_r0A_b50();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BCODE[5:0]";
  else                      out << "  RXPLL_BCODE[5:0]";
  out << endl;

  //ACODE[3:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1B MASK 07 : 04  =";
  else                      out << "REG 0x2B MASK 07 : 04  =";
  itmp = ACODE_r0B_b74();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_ACODE[3:0]";
  else                      out << "  RXPLL_ACODE[3:0]";
  out << endl;

  //PD_VCOCOMP_SX
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1B MASK 03 : 03  =";
  else                      out << "REG 0x2B MASK 03 : 03  =";
  itmp = PD_VCOCOMP_SX_r0B_b33();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_PD_VCOCOMP_SX";
  else                      out << "  RXPLL_PD_VCOCOMP_SX";
  out << endl;

  //ENLOBUF
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1B MASK 02 : 02  =";
  else                      out << "REG 0x2B MASK 02 : 02  =";
  itmp = ENLOBUF_r0B_b22();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_ENLOBUF";
  else                      out << "  RXPLL_ENLOBUF";
  out << endl;

  //ENLAMP
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1B MASK 01 : 01  =";
  else                      out << "REG 0x2B MASK 01 : 01  =";
  itmp = ENLAMP_r0B_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_ENLAMP";
  else                      out << "  RXPLL_ENLAMP";
  out << endl;

  //TRI
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1B MASK 00 : 00  =";
  else                      out << "REG 0x2B MASK 00 : 00  =";
  itmp = TRI_r0B_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_TRI";
  else                      out << "  RXPLL_TRI";
  out << endl;

  //POL
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 07 : 07  =";
  else                      out << "REG 0x2C MASK 07 : 07  =";
  itmp = POL_r0C_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_POL";
  else                      out << "  RXPLL_POL";
  out << endl;

  //PFDPD
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 06 : 06  =";
  else                      out << "REG 0x2C MASK 06 : 06  =";
  itmp = PFDPD_r0C_b66();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_PFDPD";
  else                      out << "  RXPLL_PFDPD";
  out << endl;

  //ENFEEDDIV
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 05 : 05  =";
  else                      out << "REG 0x2C MASK 05 : 05  =";
  itmp = ENFEEDDIV_r0C_b55();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_ENFEEDDIV";
  else                      out << "  RXPLL_ENFEEDDIV";
  out << endl;

  //PFDCLKP
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 04 : 04  =";
  else                      out << "REG 0x2C MASK 04 : 04  =";
  itmp = PFDCLKP_r0C_b44();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_PFDCLKP";
  else                      out << "  RXPLL_PFDCLKP";
  out << endl;

  //BCLKSEL[1:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 03 : 02  =";
  else                      out << "REG 0x2C MASK 03 : 02  =";
  itmp = BCLKSEL_r0C_b32();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BCLKSEL";
  else                      out << "  RXPLL_BCLKSEL";
  out << endl;

  //BINSEL
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 01 : 01  =";
  else                      out << "REG 0x2C MASK 01 : 01  =";
  itmp = BINSEL_r0C_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BINSEL";
  else                      out << "  RXPLL_BINSEL";
  out << endl;

  //BSTART
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1C MASK 00 : 00  =";
  else                      out << "REG 0x2C MASK 00 : 00  =";
  itmp = BSTART_r0C_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BSTART";
  else                      out << "  RXPLL_BSTART";
  out << endl;

  //BSTATE
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1D MASK 07 : 07  =";
  else                      out << "REG 0x2D MASK 07 : 07  =";
  itmp = BSTATE_r0D_b77();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BSTATE";
  else                      out << "  RXPLL_BSTATE";
  out << endl;

  //BSIG[22:16]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1D MASK 06 : 00  =";
  else                      out << "REG 0x2D MASK 06 : 00  =";
  itmp = BSIG2216_r0D_b60();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BSIG[22:16]";
  else                      out << "  RXPLL_BSIG[22:16]";
  out << endl;

  //BSIG[15:8]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1E MASK 07 : 00  =";
  else                      out << "REG 0x2E MASK 07 : 00  =";
  itmp = BSIG158_r0E_b70();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BSIG[15:8]";
  else                      out << "  RXPLL_BSIG[15:8]";
  out << endl;

  //BSIG[7:0]
  out.width(24); out << left;
  if(m_cMAddr == TxPllAddr) out << "REG 0x1F MASK 07 : 00  =";
  else                      out << "REG 0x2F MASK 07 : 00  =";
  itmp = BSIG70_r0F_b70();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxPllAddr) out << "  TXPLL_BSIG[7:0]";
  else                      out << "  RXPLL_BSIG[7:0]";
  out << endl;
};

//---------------------------------------------------------------------------
void TfrmTxPLL::SaveConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

  pini->WriteFloat(Sect, "txtDesFreq", txtDesFreq->Value);

  pini->WriteBool(Sect, "chkDITHEN", chkDITHEN->Checked);
  pini->WriteInteger(Sect, "cmbDITHN", cmbDITHN->ItemIndex);
  pini->WriteBool(Sect, "chbPwrPllMods", chbPwrPllMods->Checked);
  pini->WriteBool(Sect, "chbAUTOBYP", chbAUTOBYP->Checked);
  pini->WriteInteger(Sect, "rgrDecode", rgrDecode->ItemIndex);
  pini->WriteInteger(Sect, "rgrMODE", rgrMODE->ItemIndex);

  pini->WriteInteger(Sect, "rgrSELVCO", rgrSELVCO->ItemIndex);
  pini->WriteInteger(Sect, "rgrFRANGE", rgrFRANGE->ItemIndex);
  pini->WriteInteger(Sect, "cmbSELOUT", cmbSELOUT->ItemIndex);

  pini->WriteBool(Sect, "chbEN_PFD_UP", chbEN_PFD_UP->Checked);
  pini->WriteBool(Sect, "chkOEN_TSTD_SX", chkOEN_TSTD_SX->Checked);
  pini->WriteBool(Sect, "chkPASSEN_TSTOD_SD", chkPASSEN_TSTOD_SD->Checked);
  pini->WriteInteger(Sect, "cmbICHP", cmbICHP->ItemIndex);

  pini->WriteBool(Sect, "chbBYPVCOREG", chbBYPVCOREG->Checked);
  pini->WriteBool(Sect, "chbPDVCOREG", chbPDVCOREG->Checked);
  pini->WriteBool(Sect, "chbFSTVCOBG", chbFSTVCOBG->Checked);
  pini->WriteInteger(Sect, "cmbOFFUP", cmbOFFUP->ItemIndex);

  pini->WriteInteger(Sect, "cmbVOVCOREG", cmbVOVCOREG->ItemIndex);
  pini->WriteInteger(Sect, "cmbOFFDOWN", cmbOFFDOWN->ItemIndex);

  pini->WriteInteger(Sect, "cmbVCOCAP", cmbVCOCAP->ItemIndex);

  pini->WriteInteger(Sect, "cmbBCODE", cmbBCODE->ItemIndex);

  pini->WriteInteger(Sect, "cmbACODE", cmbACODE->ItemIndex);
  pini->WriteBool(Sect, "cmbPD_VCOCOMP_SX", cmbPD_VCOCOMP_SX->Checked);
  pini->WriteBool(Sect, "chkENLOBUF", chkENLOBUF->Checked);
  pini->WriteBool(Sect, "chkENLAMP", chkENLAMP->Checked);
  pini->WriteInteger(Sect, "chkTRI", chkTRI->Checked);

  pini->WriteInteger(Sect, "chkPOL", chkPOL->Checked);
  pini->WriteBool(Sect, "chkPFDPD", chkPFDPD->Checked);
  pini->WriteBool(Sect, "chkENFEEDDIV", chkENFEEDDIV->Checked);
  pini->WriteInteger(Sect, "chkPFDCLKP", chkPFDCLKP->Checked);
  pini->WriteInteger(Sect, "rgrBCLKSEL", rgrBCLKSEL->ItemIndex);
  pini->WriteInteger(Sect, "rgrBINSEL", rgrBINSEL->ItemIndex);

  pini->WriteFloat(Sect, "RefClk", m_dRefF);
};

//---------------------------------------------------------------------------
void TfrmTxPLL::ReadConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

  m_bAllowSend = false;

  txtDesFreq->Value = pini->ReadFloat(Sect, "txtDesFreq", 5.21);

  chkDITHEN->Checked = pini->ReadBool(Sect, "chkDITHEN", 1);
  cmbDITHN->ItemIndex = pini->ReadInteger(Sect, "cmbDITHN", 0);
  chbPwrPllMods->Checked = pini->ReadBool(Sect, "chbPwrPllMods", 1);
  chbAUTOBYP->Checked = pini->ReadBool(Sect, "chbAUTOBYP", 0);
  rgrDecode->ItemIndex = pini->ReadInteger(Sect, "rgrDecode", 0);
  rgrMODE->ItemIndex = pini->ReadInteger(Sect, "rgrMODE", 0);

  rgrSELVCO->ItemIndex = pini->ReadInteger(Sect, "rgrSELVCO", 2);
  rgrFRANGE->ItemIndex = pini->ReadInteger(Sect, "rgrFRANGE", 1);
  cmbSELOUT->ItemIndex = pini->ReadInteger(Sect, "cmbSELOUT", 1);

  chbEN_PFD_UP->Checked = pini->ReadBool(Sect, "chbEN_PFD_UP", 1);
  chkOEN_TSTD_SX->Checked = pini->ReadBool(Sect, "chkOEN_TSTD_SX", 0);
  chkPASSEN_TSTOD_SD->Checked = pini->ReadBool(Sect, "chkPASSEN_TSTOD_SD", 0);
  cmbICHP->ItemIndex = pini->ReadInteger(Sect, "cmbICHP", 12);

  chbBYPVCOREG->Checked = pini->ReadBool(Sect, "chbBYPVCOREG", 1);
  chbPDVCOREG->Checked = pini->ReadBool(Sect, "chbPDVCOREG", 1);
  chbFSTVCOBG->Checked = pini->ReadBool(Sect, "chbFSTVCOBG", 1);
  cmbOFFUP->ItemIndex = pini->ReadInteger(Sect, "cmbOFFUP", 0);

  cmbVOVCOREG->ItemIndex = pini->ReadInteger(Sect, "cmbVOVCOREG", 5);
  cmbOFFDOWN->ItemIndex = pini->ReadInteger(Sect, "cmbOFFDOWN", 0);

  cmbVCOCAP->ItemIndex = pini->ReadInteger(Sect, "cmbVCOCAP", 20);

  cmbBCODE->ItemIndex = pini->ReadInteger(Sect, "cmbBCODE", 5);

  cmbACODE->ItemIndex = pini->ReadInteger(Sect, "cmbACODE", 0);
  cmbPD_VCOCOMP_SX->Checked = pini->ReadBool(Sect, "cmbPD_VCOCOMP_SX", 1);
  chkENLOBUF->Checked = pini->ReadBool(Sect, "chkENLOBUF", 1);
  chkENLAMP->Checked = pini->ReadBool(Sect, "chkENLAMP", 1);
  chkTRI->Checked = pini->ReadInteger(Sect, "chkTRI", 0);

  chkPOL->Checked = pini->ReadInteger(Sect, "chkPOL", 0);
  chkPFDPD->Checked = pini->ReadBool(Sect, "chkPFDPD", 0);
  chkENFEEDDIV->Checked = pini->ReadBool(Sect, "chkENFEEDDIV", 1);
  chkPFDCLKP->Checked = pini->ReadInteger(Sect, "chkPFDCLKP", 1);
  rgrBCLKSEL->ItemIndex = pini->ReadInteger(Sect, "rgrBCLKSEL", 1);
  rgrBINSEL->ItemIndex = pini->ReadInteger(Sect, "rgrBINSEL", 2);

  m_dRefF = pini->ReadFloat(Sect, "RefClk", 30720000);

  CalcPLLData();
  CalcIntPllData();

  //Not to override by CalcPLLData()
  cmbVCOCAP->ItemIndex = pini->ReadInteger(Sect, "cmbVCOCAP", 20);

  m_bAllowSend = true;
};

void __fastcall TfrmTxPLL::btnClbrClick(TObject *Sender)
{
  dlgFreqVsCap->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TfrmTxPLL::btnChooseClick(TObject *Sender)
{
  ChooseVcoCap();
  if(m_bAllowSend){ MakeData(0x0C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void TfrmTxPLL::SetRefClk(double RefClk)
{
  m_dRefF = RefClk;
};
//---------------------------------------------------------------------------
double TfrmTxPLL::GetRefClk()
{
  return m_dRefF;
};
//---------------------------------------------------------------------------
void TfrmTxPLL::UpdateFreq()
{
  m_bAllowSend = false;
  // Comented, to set not to defaults, but tu have BAND I Middle frequency.
  //txtDesFreq->Value = m_dRefF*130.25/2.0/1000000000;
  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void TfrmTxPLL::CustSet_ActiveLOBuff(int ind)
{
  m_bAllowSend = false;
  cmbSELOUT->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x80); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void TfrmTxPLL::CustSet_LoadFrequency(double Freq)
{
  txtDesFreq->Value = Freq;
  btnCalcClick(Application);
};

void TfrmTxPLL::CustSet_PLLPowerON()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrPllMods->Checked = true;
  m_bAllowSend = true;

  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxPLL::CustSet_PLLPowerOFF()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrPllMods->Checked = false;
  m_bAllowSend = true;

  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxPLL::CustSet_cmbOFFUP(int Ind)
{
  cmbOFFUP->ItemIndex = Ind;
  cmbOFFUPChange(Application);
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::btnReadVtuneClick(TObject *Sender)
{
/*
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

  if(m_psD.cDataR[0x0A] & 0x80) lblVTUNE_H->Caption = "1";
  else lblVTUNE_H->Caption = "0";

  if(m_psD.cDataR[0x0A] & 0x40) lblVTUNE_L->Caption = "1";
  else lblVTUNE_L->Caption = "0";
*/
  int State = GetVTuneState();
  switch(State)
  {
    case 0x00:
      lblVTUNE_H->Caption = "0";
      lblVTUNE_L->Caption = "0";
    break;

    case 0x01:
      lblVTUNE_H->Caption = "0";
      lblVTUNE_L->Caption = "1";
    break;

    case 0x02:
      lblVTUNE_H->Caption = "1";
      lblVTUNE_L->Caption = "0";
    break;

    default:
      lblVTUNE_H->Caption = "1";
      lblVTUNE_L->Caption = "1";
  };

}

//---------------------------------------------------------------------------
// VTUNE_H, VTUNE_L, Returns
//   0        0        0x00
//   0        1        0x01
//   1        0        0x02
//   1        1        0x03 (ERROR)
//---------------------------------------------------------------------------
int TfrmTxPLL::GetVTuneState()
{
  int rez = 0;
  
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

  //VTUNE_H
  //if(m_psD.cDataR[0x0A] & 0x80) rez = rez | 0x02;
  if(VTUNE_H_r0A_b77()) rez = rez | 0x02;

  //VTUNE_L
  //if(m_psD.cDataR[0x0A] & 0x40) rez = rez | 0x01;
  if(VTUNE_L_r0A_b66()) rez = rez | 0x01;

  return rez;
};

//---------------------------------------------------------------------------
// Method according to Danny. Stops, when reaches 0.5V or 2.8V value of Vtune
//---------------------------------------------------------------------------
void TfrmTxPLL::CapAutoTune_D()
{
  bool bContinue;
  bool bPD_VCOCOMP_SX_state;
  int irgrDecode_state;

  //Remember the PD_VCOCOMP_SX state
  bPD_VCOCOMP_SX_state = cmbPD_VCOCOMP_SX->Checked;
  //Remember decode state
  irgrDecode_state = rgrDecode->ItemIndex;

  //Check DECODE and enable if neccessary
  if(rgrDecode->ItemIndex == 0)
  {
    rgrDecode->ItemIndex = 1;
    rgrDecodeClick(Application);
  };

  //Check PD_VCOCOMP_SX and enable if neccessary
  if(!cmbPD_VCOCOMP_SX->Checked)
  {
    cmbPD_VCOCOMP_SX->Checked = true;
    cmbPD_VCOCOMP_SXClick(Application);
  };

  //Read VTUNE_H and VTUNE_L
  int State = GetVTuneState();
  switch(State)
  {
    // VTUNE_H, VTUNE_L, Value
    //   0        0      0x00
    case 0x00:
      //lblVTUNE_H->Caption = "0";
      //lblVTUNE_L->Caption = "0";
      lblAutoTuneStatus->Caption = "0 - OK";
    break;

    // VTUNE_H, VTUNE_L, Value
    //   0        1      0x01
    case 0x01:
      //lblVTUNE_H->Caption = "0";
      //lblVTUNE_L->Caption = "1";
      bContinue = true;
      do
      {
        State = GetVTuneState();
        if( (State != 0x00) && (cmbVCOCAP->ItemIndex > 0) )
        {
          cmbVCOCAP->ItemIndex--;
          cmbVCOCAPChange(Application);
        }
        else
        {
          bContinue = false;
        };
      } while(bContinue);

      if(State == 0x00)
      {
        lblAutoTuneStatus->Caption = "1 - OK";
      }
      else
      {
        lblAutoTuneStatus->Caption = "1 - Err";
      };
    break;

    // VTUNE_H, VTUNE_L, Value
    //   1        0      0x02
    case 0x02:
      //lblVTUNE_H->Caption = "1";
      //lblVTUNE_L->Caption = "0";
      bContinue = true;
      do
      {
        State = GetVTuneState();
        if( (State != 0x00) && (cmbVCOCAP->ItemIndex < 63) )
        {
          cmbVCOCAP->ItemIndex++;
          cmbVCOCAPChange(Application);
        }
        else
        {
          bContinue = false;
        };
      } while(bContinue);

      if(State == 0x00)
      {
        lblAutoTuneStatus->Caption = "2 - OK";
      }
      else
      {
        lblAutoTuneStatus->Caption = "2 - Err";
      };
    break;

    // VTUNE_H, VTUNE_L, Value
    //   1        1      0x03 (ERROR)
    default:
      //lblVTUNE_H->Caption = "1";
      //lblVTUNE_L->Caption = "1";
      lblAutoTuneStatus->Caption = "3 - Err";
  };

  //Set back PD_VCOCOMP_SX if neccessary
  if(!bPD_VCOCOMP_SX_state)
  {
    cmbPD_VCOCOMP_SX->Checked = false;
    cmbPD_VCOCOMP_SXClick(Application);
  };

  //Set back DECODE if neccessary
  if(irgrDecode_state == 0)
  {
    rgrDecode->ItemIndex = 0;
    rgrDecodeClick(Application);
  };
};

//---------------------------------------------------------------------------
bool TfrmTxPLL::CapIncrement(int UntilState, TdVcoCapLog *VcoCapLog)
{
  bool bContinue;
  int CurrentState;
  String Str;

  if(VcoCapLog) VcoCapLog->memLogText->Lines->Add("=== Start CAP Incrementing ===");

  bContinue = true;
  do
  {
    Str = "State = ";
    //Sleep(10);
    CurrentState = GetVTuneState();
    Str = Str + CurrentState;
    if( (CurrentState != UntilState) && (cmbVCOCAP->ItemIndex < 63) )
    {
      cmbVCOCAP->ItemIndex++;
      cmbVCOCAPChange(Application);
    }
    else
    {
      bContinue = false;
    };
    Str = Str + "; CAP = ";
    Str = Str + cmbVCOCAP->ItemIndex;
    if(VcoCapLog) VcoCapLog->memLogText->Lines->Add(Str);
  } while(bContinue);

  if(VcoCapLog) VcoCapLog->memLogText->Lines->Add("=== Stop CAP Incrementing ===");

  if(CurrentState == UntilState)  return true;
  else                            return false;
};

//---------------------------------------------------------------------------
bool TfrmTxPLL::CapDecrement(int UntilState, TdVcoCapLog *VcoCapLog)
{
  bool bContinue;
  int CurrentState;
  String Str;

  if(VcoCapLog) VcoCapLog->memLogText->Lines->Add("=== Start CAP Decrementing ===");

  bContinue = true;
  do
  {
    Str = "State = ";
    //Sleep(10);
    CurrentState = GetVTuneState();
    Str = Str + CurrentState;
    if( (CurrentState != UntilState) && (cmbVCOCAP->ItemIndex > 0) )
    {
      cmbVCOCAP->ItemIndex--;
      cmbVCOCAPChange(Application);
    }
    else
    {
      bContinue = false;
    };
    Str = Str + "; CAP = ";
    Str = Str + cmbVCOCAP->ItemIndex;
    if(VcoCapLog) VcoCapLog->memLogText->Lines->Add(Str);
  } while(bContinue);

  if(VcoCapLog) VcoCapLog->memLogText->Lines->Add("=== Stop CAP Decrementing ===");

  if(CurrentState == UntilState)  return true;
  else                            return false;
};


//---------------------------------------------------------------------------
// Method according to Srdjan. Founds Cap values for 0.5V and 2.5V value of
//   Vtune and then calculates Cap value for Vtune 1.5V.
//---------------------------------------------------------------------------
int TfrmTxPLL::CapAutoTune_S(TdVcoCapLog *dVcoCapLog)
{
  bool bContinue;
  bool bPD_VCOCOMP_SX_state;
  int irgrDecode_state;
  int iInitialCap;
  int iCl;
  int iCh;
  int CapState;
  int Result;
  String Str;

//------ Remember Controls state. Begin. ---------------------------------------
/* For 6002D version
  //Remember the PD_VCOCOMP_SX state
  bPD_VCOCOMP_SX_state = cmbPD_VCOCOMP_SX->Checked;
  //Remember decode state
  irgrDecode_state = rgrDecode->ItemIndex;

  //Check DECODE and enable if neccessary
  if(rgrDecode->ItemIndex == 0)
  {
    rgrDecode->ItemIndex = 1;
    rgrDecodeClick(Application);
  };

  //Check PD_VCOCOMP_SX and enable if neccessary
  if(!cmbPD_VCOCOMP_SX->Checked)
  {
    cmbPD_VCOCOMP_SX->Checked = true;
    cmbPD_VCOCOMP_SXClick(Application);
  };
*/
//------ Remember Controls state. End. -----------------------------------------


//------ Algorithm. Begin. -----------------------------------------------------
  //Read VTUNE_H and VTUNE_L
  CapState = GetVTuneState();
  iInitialCap = cmbVCOCAP->ItemIndex;
  Result = 0;

  switch(CapState)
  {
    // VTUNE_H, VTUNE_L, Value
    //   0        0      0x00
    case 0x00:
      //lblVTUNE_H->Caption = "0";
      //lblVTUNE_L->Caption = "0";

      Result = 0x10;
      //Decrement Cap until H=1, L=0
      if(!CapDecrement(0x02, dVcoCapLog))
      {
        Result += 0x02;
        //break;
      };
      iCh = cmbVCOCAP->ItemIndex;

      //Go to initial value for speeding things up.
      cmbVCOCAP->ItemIndex = iInitialCap;
      //cmbVCOCAPChange(Application);

      //Increment Cap until H=0, L=1
      if(!CapIncrement(0x01, dVcoCapLog))
      {
        Result += 0x01;
        //break;
      };
      iCl = cmbVCOCAP->ItemIndex;
    break;

    // VTUNE_H, VTUNE_L, Value
    //   0        1      0x01
    case 0x01:
      //lblVTUNE_H->Caption = "0";
      //lblVTUNE_L->Caption = "1";

      Result = 0x20;
      //Decrement Cap until H=0, L=0
      if(!CapDecrement(0x00, dVcoCapLog))
      {
        Result += 0x04;
        //break;
      };
      iCl = cmbVCOCAP->ItemIndex;
      //Decrement Cap until H=1, L=0
      if(!CapDecrement(0x02, dVcoCapLog))
      {
        Result += 0x02;
        //break;
      };
      iCh = cmbVCOCAP->ItemIndex;
    break;

    // VTUNE_H, VTUNE_L, Value
    //   1        0      0x02
    case 0x02:
      //lblVTUNE_H->Caption = "1";
      //lblVTUNE_L->Caption = "0";

      Result = 0x30;
      //Increment Cap until H=0, L=0
      if(!CapIncrement(0x00, dVcoCapLog))
      {
        Result += 0x04;
        //break;
      };
      iCh = cmbVCOCAP->ItemIndex;
      //Increment Cap until H=0, L=1
      if(!CapIncrement(0x01, dVcoCapLog))
      {
        Result += 0x01;
        //break;
      };
      iCl = cmbVCOCAP->ItemIndex;
    break;

    // VTUNE_H, VTUNE_L, Value
    //   1        1      0x03 (ERROR)
    default:
      //lblVTUNE_H->Caption = "1";
      //lblVTUNE_L->Caption = "1";
      Result = 7;
  };

  if(Result != 7)  //Values are OK, calculate new Cap Value
  {
    cmbVCOCAP->ItemIndex = (int)(((2.0-2.5)*(iCh-iCl)/(2.5-0.5)) + iCh + 0.5);
    cmbVCOCAPChange(Application);
  }
  else        //Error occuread. Set Cap Value to initial.
  {
    cmbVCOCAP->ItemIndex = iInitialCap;
    cmbVCOCAPChange(Application);
  };

//------ Algorithm. End. -------------------------------------------------------


//------ Set Back Controls state. Begin. ---------------------------------------
/* For 6002D version
  //Set back PD_VCOCOMP_SX if neccessary
  if(!bPD_VCOCOMP_SX_state)
  {
    cmbPD_VCOCOMP_SX->Checked = false;
    cmbPD_VCOCOMP_SXClick(Application);
  };

  //Set back DECODE if neccessary
  if(irgrDecode_state == 0)
  {
    rgrDecode->ItemIndex = 0;
    rgrDecodeClick(Application);
  };
*/
//------ Set Back Controls state. End. -----------------------------------------

  // Form Logo
  if(chkCapLog->Checked)
  {
    if((Result == 0x10) || (Result == 0x20) || (Result == 0x30))
    {
        dVcoCapLog->memLogText->Lines->Add("VCO Cap Tuning successful.");
        Str = "Cap value for Vtuning 0.5V = "; Str = Str + iCl;
        dVcoCapLog->memLogText->Lines->Add(Str);
        Str = "Cap value for Vtuning 2.5V = "; Str = Str + iCh;
        dVcoCapLog->memLogText->Lines->Add(Str);
        Str = "Selected Cap value for Vtuning 1.5V = "; Str = Str + cmbVCOCAP->ItemIndex;
        dVcoCapLog->memLogText->Lines->Add(Str);
        Str = "Initial Cap value was = "; Str = Str + iInitialCap;
        dVcoCapLog->memLogText->Lines->Add(Str);
    }
    else
    {
      if(Result == 7)
      {
        dVcoCapLog->memLogText->Lines->Add("VCO Cap Tuning UNSUCCESSFUL.");
        Str = "Initial Cap value = "; Str = Str + iInitialCap;
        dVcoCapLog->memLogText->Lines->Add(Str);
        Str = "Initial comparator value: VTUNE_L = 1; VTUNE_H = 1.";
        dVcoCapLog->memLogText->Lines->Add(Str);
        dVcoCapLog->memLogText->Lines->Add("");
        dVcoCapLog->memLogText->Lines->Add("Check please SPI cable, connecion etc.");
      }
      else
      {
        dVcoCapLog->memLogText->Lines->Add("VCO Cap Tuning ISSUES.");
        Str = "Initial Cap value = "; Str = Str + iInitialCap;
        dVcoCapLog->memLogText->Lines->Add(Str);

        Str = "Initial comparator value: ";
        if(CapState == 0x00) Str = Str + "VTUNE_L = 0; VTUNE_H = 0.";
        else if(CapState == 0x01) Str = Str + "VTUNE_L = 0; VTUNE_H = 1.";
        else if(CapState == 0x02) Str = Str + "VTUNE_L = 1; VTUNE_H = 0.";
        else Str = Str + "VTUNE_L = 1; VTUNE_H = 1.";
        dVcoCapLog->memLogText->Lines->Add(Str);

        if((Result & 0x01) == 0x01)
        {
          Str = "Issue: Can not raech state, where VTUNE_L = 1; VTUNE_H = 0.";
          dVcoCapLog->memLogText->Lines->Add(Str);
        };
        if((Result & 0x02) == 0x02)
        {
          Str = "Issue: Can not raech state, where VTUNE_L = 0; VTUNE_H = 1.";
          dVcoCapLog->memLogText->Lines->Add(Str);
        };
        if((Result & 0x04) == 0x04)
        {
          Str = "Issue: Can not raech state, where VTUNE_L = 0; VTUNE_H = 0.";
          dVcoCapLog->memLogText->Lines->Add(Str);
        };
      };
    };
  };

  return Result;
}

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::btnTuneClick(TObject *Sender)
{
  int iCapTunRes;
  int CapState;
  int iInitialCap;
  bool bContinue;
  String Str;
  int iTry;
  TdVcoCapLog *dVcoCapLog = NULL;
  dVcoCapLog = new TdVcoCapLog(Application);

  LookForCap(dVcoCapLog);
  if(chkCapLog->Checked) dVcoCapLog->ShowModal();
  if(dVcoCapLog) delete dVcoCapLog;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int TfrmTxPLL::LookForCap(TdVcoCapLog *dVcoCapLog)
{
  int iCap00;
  int iCap63;
  int iCapTuneRes;
  String Str;
  int iInitCap;
  int iInitVco;

  //Remember the initial states of CAP and VCO
  iInitCap = cmbVCOCAP->ItemIndex;
  iInitVco = rgrSELVCO->ItemIndex;

  //for(int i=4; i>=1; i--)
  for(int i=1; i<=4; i++)
  {
    Str = "=== Trying VCO Nr. ";    Str = Str + (5-i);    Str = Str + " ===";
    dVcoCapLog->memLogText->Lines->Add(Str);

    //Choose VCO
    rgrSELVCO->ItemIndex = i;

    //Set CAP to '0'
    cmbVCOCAP->ItemIndex = 0;
    cmbVCOCAPChange(Application);

    //See what the values of Vh and Vl are
    iCap00 = GetVTuneState();

    //Set CAP to '63'
    cmbVCOCAP->ItemIndex = 63;
    cmbVCOCAPChange(Application);

    //See what are the values of Vh and Vl
    iCap63 = GetVTuneState();

    Str = "Vtune for CAP=0 is ";    Str = Str + iCap00;
    dVcoCapLog->memLogText->Lines->Add(Str);
    Str = "Vtune for CAP=63 is ";    Str = Str + iCap63;
    dVcoCapLog->memLogText->Lines->Add(Str);

    if((rgrSELVCO->ItemIndex == 4) && (iCap00 == 0x02) && (iCap63 == 0x02))
    {
      break;
    };

    if((iCap00 == 0x02) && (iCap63 == 0x01))
    {
      dVcoCapLog->memLogText->Lines->Add("VCO can deliver required frequency.");
      dVcoCapLog->memLogText->Lines->Add("Starting Procedure.");

      //Set CAP in the middle of the range
      cmbVCOCAP->ItemIndex = 31;
      cmbVCOCAPChange(Application);

      //Try to Tune
      iCapTuneRes = CapAutoTune_S(dVcoCapLog);

      Str = "Selected CAP = ";    Str = Str + cmbVCOCAP->ItemIndex;
      dVcoCapLog->memLogText->Lines->Add(Str);

      return iCapTuneRes;
    };
    dVcoCapLog->memLogText->Lines->Add("VCO is not suitable.");
    dVcoCapLog->memLogText->Lines->Add("");
  };

  dVcoCapLog->memLogText->Lines->Add("Any VCO can not deliver required frequency.");
  dVcoCapLog->memLogText->Lines->Add("Communication problems?");
  dVcoCapLog->memLogText->Lines->Add("Check please SPI cable, connecion etc.");
  dVcoCapLog->memLogText->Lines->Add("Setting VCO and CAP back to initial values");

  //Set CAP and VCO to initial values
  cmbVCOCAP->ItemIndex = iInitCap;
  cmbVCOCAPChange(Application); 
  rgrSELVCO->ItemIndex = iInitVco;

  return 0;
};

//---------------------------------------------------------------------------
// Enables VCO TUNE comparators;
// Selects required VCO and CAP
// Returns VCO TUNE comparator values
//---------------------------------------------------------------------------
int TfrmTxPLL::GetVTuneState(int vco, int cap)
{
  int iVCOState;
  int iCAPState;
  int result;

  //Remember VCO and CAP
  iVCOState = rgrSELVCO->ItemIndex;
  iCAPState = cmbVCOCAP->ItemIndex;

  //Set VCO
  rgrSELVCO->ItemIndex = vco;

  //Set CAP
  cmbVCOCAP->ItemIndex = cap;
  cmbVCOCAPChange(Application);

  result = GetVTuneState();

  //Restore VCO and CAP
  rgrSELVCO->ItemIndex = iVCOState;
  cmbVCOCAP->ItemIndex = iCAPState;
  cmbVCOCAPChange(Application);

  return result;
};

//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void TfrmTxPLL::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};


//---------------------------------------------------------------------------
// BIST Functions
//---------------------------------------------------------------------------
bool TfrmTxPLL::BIST_GetState()
{
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);
  return (bool)BSTATE_r0D_b77();
};

//---------------------------------------------------------------------------
void TfrmTxPLL::BIST_ShowState(bool State)
{
  if(State)
  {
    lblBSTATE->Caption = "In Progress";
  }
  else
  {
    lblBSTATE->Caption = "Not Running";
  };
};

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::btnReadBISTStateClick(TObject *Sender)
{
  BIST_ShowState(BIST_GetState());
}

//---------------------------------------------------------------------------
unsigned int TfrmTxPLL::BIST_GetSignature()
{
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);
  return (unsigned int) BSIG();
};

//---------------------------------------------------------------------------
void TfrmTxPLL::BIST_ShowSignature(int Signature)
{
  //lblBSIG->Caption = IntToHex(Signature, 6);
  if(Signature == 0x1B256D)
  {
    lblBSIG->Caption = "0x" + IntToHex(Signature, 6) + " - OK";
  }
  else
  {
    lblBSIG->Caption = "0x" + IntToHex(Signature, 6) + " - Failed";
  };
};

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::Button1Click(TObject *Sender)
{
  int iBS = BIST_GetSignature();
  BIST_ShowSignature(iBS);
}
//---------------------------------------------------------------------------
// Activate start BIST command and the deactivate.
//---------------------------------------------------------------------------
void TfrmTxPLL::BIST_Start()
{
  char btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	//POL
  btmp = chkPOL->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x0C] |= btmp;
	//PFDPD
	btmp = chkPFDPD->Checked == true ? 0 : 1;
	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
	//ENFEEDDIV
	btmp = chkENFEEDDIV->Checked == true ? 1 : 0;
	btmp = btmp << 5; m_psD.cDataW[0x0C] |= btmp;
	//PFDCLKP
	btmp = chkPFDCLKP->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
  //BCLKSEL
	btmp = (char)(rgrBCLKSEL->ItemIndex & 0x03);
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
  //BINSEL
	btmp = (char)(rgrBINSEL->ItemIndex & 0x01);
	btmp = btmp << 1; m_psD.cDataW[0x0C] |= btmp;
  //BSTART
	btmp = 0x00;                                      //DEACTIVATE START BIST
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x0C;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);


	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	//POL
  btmp = chkPOL->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x0C] |= btmp;
	//PFDPD
	btmp = chkPFDPD->Checked == true ? 0 : 1;
	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
	//ENFEEDDIV
	btmp = chkENFEEDDIV->Checked == true ? 1 : 0;
	btmp = btmp << 5; m_psD.cDataW[0x0C] |= btmp;
	//PFDCLKP
	btmp = chkPFDCLKP->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
  //BCLKSEL
	btmp = (char)(rgrBCLKSEL->ItemIndex & 0x03);
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
  //BINSEL
	btmp = (char)(rgrBINSEL->ItemIndex & 0x01);
	btmp = btmp << 1; m_psD.cDataW[0x0C] |= btmp;
  //BSTART
	btmp = 0x01;                                      //START BIST!!!
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x0C;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
	//POL
  btmp = chkPOL->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x0C] |= btmp;
	//PFDPD
	btmp = chkPFDPD->Checked == true ? 0 : 1;
	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
	//ENFEEDDIV
	btmp = chkENFEEDDIV->Checked == true ? 1 : 0;
	btmp = btmp << 5; m_psD.cDataW[0x0C] |= btmp;
	//PFDCLKP
	btmp = chkPFDCLKP->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
  //BCLKSEL
	btmp = (char)(rgrBCLKSEL->ItemIndex & 0x03);
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
  //BINSEL
	btmp = (char)(rgrBINSEL->ItemIndex & 0x01);
	btmp = btmp << 1; m_psD.cDataW[0x0C] |= btmp;
  //BSTART
	btmp = 0x00;                                      //DEACTIVATE START BIST
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x0C;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

};

//---------------------------------------------------------------------------
void __fastcall TfrmTxPLL::btnBSTARTClick(TObject *Sender)
{
  BIST_Start();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Procedure used from Main form, when calibrating LPF CAL Core
// and Ref frequency is not 40MHz
//---------------------------------------------------------------------------
void TfrmTxPLL::SetPLLTo320MHz()
{
  m_F320M_Data.F320M_rgrDecode      = rgrDecode->ItemIndex;
  m_F320M_Data.F320M_chbPwrPllMods  = chbPwrPllMods->Checked;
  m_F320M_Data.F320M_rgrMODE        = rgrMODE->ItemIndex;
  m_F320M_Data.F320M_cmbVCOCAP      = cmbVCOCAP->ItemIndex;
  m_F320M_Data.F320M_rgrSELVCO      = rgrSELVCO->ItemIndex;
  m_F320M_Data.F320M_rgrFRANGE      = rgrFRANGE->ItemIndex;
  m_F320M_Data.F320M_txtDesFreq     = txtDesFreq->Value;

  rgrDecode->ItemIndex = 0;
  chbPwrPllMods->Checked = true;
  rgrMODE->ItemIndex = 0;
  txtDesFreq->Value = 0.32;
  btnCalcClick(Application);

};

//---------------------------------------------------------------------------
// Restore GUI values changed by SetPLLTo320MHz()
//---------------------------------------------------------------------------
void TfrmTxPLL::RestoreAfterSetPLLTo320MHz()
{
  txtDesFreq->Value = m_F320M_Data.F320M_txtDesFreq;
  btnCalcClick(Application);

  rgrDecode->ItemIndex = m_F320M_Data.F320M_rgrDecode;
  chbPwrPllMods->Checked = m_F320M_Data.F320M_chbPwrPllMods;
  rgrMODE->ItemIndex = m_F320M_Data.F320M_rgrMODE;
  cmbVCOCAP->ItemIndex = m_F320M_Data.F320M_cmbVCOCAP;
  cmbVCOCAPChange(Application);
  rgrSELVCO->ItemIndex = m_F320M_Data.F320M_rgrSELVCO;
  rgrFRANGE->ItemIndex = m_F320M_Data.F320M_rgrFRANGE;
};

