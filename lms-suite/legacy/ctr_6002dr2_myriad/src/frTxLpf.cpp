// -----------------------------------------------------------------------------
// FILE: 		    frTxLpf.cpp
// DESCRIPTION:	TxLPF control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frTxLpf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmTxLpf *frmTxLpf;

//0x0
#define             DC_REGVAL_r00_b50() ((m_psD.cDataR[0x00] & 0x3F) >> 0)
//0x1
#define               DC_LOCK_r01_b42() ((m_psD.cDataR[0x01] & 0x1C) >> 2)
#define          DC_CLBR_DONE_r01_b11() ((m_psD.cDataR[0x01] & 0x02) >> 1)
#define                 DC_UD_r01_b00() ((m_psD.cDataR[0x01] & 0x01) >> 0)
//0x2
#define             DC_CNTVAL_r02_b50() ((m_psD.cDataR[0x02] & 0x3F) >> 0)
//0x3
#define         DC_START_CLBR_r03_b55() ((m_psD.cDataR[0x03] & 0x20) >> 5)
#define               DC_LOAD_r03_b44() ((m_psD.cDataR[0x03] & 0x10) >> 4)
#define             DC_SRESET_r03_b33() ((m_psD.cDataR[0x03] & 0x08) >> 3)
#define               DC_ADDR_r03_b20() ((m_psD.cDataR[0x03] & 0x07) >> 0)
//0x4
#define               BWC_LPF_r04_b52() ((m_psD.cDataR[0x04] & 0x3C) >> 2)
#define                    EN_r04_b11() ((m_psD.cDataR[0x04] & 0x02) >> 1)
#define                DECODE_r04_b00() ((m_psD.cDataR[0x04] & 0x01) >> 0)
//0x5
#define            BYP_EN_LPF_r05_b66() ((m_psD.cDataR[0x05] & 0x40) >> 6)
#define            DCO_DACCAL_r05_b50() ((m_psD.cDataR[0x05] & 0x3F) >> 0)
//0x6
#define          TX_DACBUF_PD_r06_b77() ((m_psD.cDataR[0x06] & 0x80) >> 7)
#define          RCCAL_LPF_PD_r06_b64() ((m_psD.cDataR[0x06] & 0x70) >> 4)
//#define         PD_DCOCMP_LPF_r06_b33() ((m_psD.cDataR[0x06] & 0x08) >> 3)
#define         PD_DCOCMP_LPF_r06_b33_v0() ((m_psD.cDataR[0x06] & 0x08) >> 3) //When Ver=2, Rev=2, Mask=0
#define         PD_DCOCMP_LPF_r0F_b77_v1() ((m_psD.cDataR[0x0F] & 0x80) >> 7) //When Ver=2, Rev=2, Mask=1
#define         PD_DCODAC_LPF_r06_b22() ((m_psD.cDataR[0x06] & 0x04) >> 2)
#define         PD_DCOREF_LPF_r06_b11() ((m_psD.cDataR[0x06] & 0x02) >> 1)
#define            PD_FIL_LPF_r06_b00() ((m_psD.cDataR[0x06] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A_TX ",20"
//#define FRIF_SPI_A_RX ",20"

//---------------------------------------------------------------------------
__fastcall TfrmTxLpf::TfrmTxLpf(TComponent* Owner)
	: TFrame(Owner)
{
  m_frmADDC = NULL;
  m_cVer = 2;
  m_cRev = 2;
  m_cMask = 0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TfrmTxLpf::~TfrmTxLpf(void)
{
	delete[] m_psD.cCmdW;
	delete[] m_psD.cDataW;
	delete[] m_psD.cCmdR;
	delete[] m_psD.cDataR;
	delete[] m_psD.iRInd;
	delete[] m_psD.iWInd;
  delete[] m_psD.cTestMap; //RT//
}

//---------------------------------------------------------------------------
void TfrmTxLpf::Initialize(char MAddr, TfrmADDC *ADDC)
{
	m_cMAddr = MAddr;
  m_frmADDC = ADDC;


	if(m_cMAddr == TxLpfAddr) m_psD.iLen = TxLpfLen;
  else m_psD.iLen = RxLpfLen;


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
	for(int i=0; i<m_psD.iLen; i++)
	{
    m_psD.cTestMap[i] = 0x00;
  };
  m_psD.cTestMap[0x0] = 0x00;
  m_psD.cTestMap[0x1] = 0x00;
  m_psD.cTestMap[0x2] = 0x3F;
  m_psD.cTestMap[0x3] = 0x3F;
  m_psD.cTestMap[0x4] = 0x3F;
  m_psD.cTestMap[0x5] = 0x7F;
	if(m_cMAddr == TxLpfAddr)
  {
    m_psD.cTestMap[0x6] = 0xFF;
  }
  else
  {
    m_psD.cTestMap[0x6] = 0x7F;
    m_psD.cTestMap[0x7] = 0xFF;    
    m_psD.cTestMap[0x8] = 0xFF;
    m_psD.cTestMap[0x9] = 0x7F;
    m_psD.cTestMap[0xA] = 0xFF;
    m_psD.cTestMap[0xB] = 0xFF;
    m_psD.cTestMap[0xC] = 0xFF;
    m_psD.cTestMap[0xD] = 0xFF;
    m_psD.cTestMap[0xE] = 0xFF;
    m_psD.cTestMap[0xF] = 0x1F;
  };

  SetGuiDefaults();

};

//---------------------------------------------------------------------------
void TfrmTxLpf::SetGuiDefaults()
{
	m_bAllowSend = false;

  //BWC_LPF[3:0]
  cmbLpfBw->Clear();
  cmbLpfBw->Items->Add("14 MHz");
  cmbLpfBw->Items->Add("10 MHz");
  cmbLpfBw->Items->Add("7 MHz");
  cmbLpfBw->Items->Add("6 MHz");
  cmbLpfBw->Items->Add("5 MHz");
  cmbLpfBw->Items->Add("4.375 MHz");
  cmbLpfBw->Items->Add("3.5 MHz");
  cmbLpfBw->Items->Add("3 MHz");
  cmbLpfBw->Items->Add("2.75 MHz");
  cmbLpfBw->Items->Add("2.5 MHz");
  cmbLpfBw->Items->Add("1.92 MHz");
  cmbLpfBw->Items->Add("1.5 MHz");
  cmbLpfBw->Items->Add("1.375 MHz");
  cmbLpfBw->Items->Add("1.25 MHz");
  cmbLpfBw->Items->Add("0.875 MHz");
  cmbLpfBw->Items->Add("0.75 MHz");
  cmbLpfBw->ItemIndex = 0;
  //EN
  chbPwrLpfMods->Checked = true;
	//DECODE
  rgrDecode->ItemIndex = 0;

  //BYP_EN_LPF
  rgrLpfByp->ItemIndex = 0;
  //DCO_DACCAL_LPF[5:0]
	cmbDCOffset->Clear();
  for(int i=0; i<64; i++)
  {
  	cmbDCOffset->Items->Add(i);
  };
  cmbDCOffset->ItemIndex = 0x0C;

  //TX_DACBUF_EN
  if(m_cMAddr == TxLpfAddr)
  {
    chbTX_DACBUF_EN->Enabled = true;
    chbTX_DACBUF_EN->Checked = true;
    chbTX_DACBUF_EN->Visible = true;
  }
  else
  {
    chbTX_DACBUF_EN->Enabled = false;
    chbTX_DACBUF_EN->Visible = false;
  };
  //RCCAL_LPF[2:0]
  cmbRcCal->Clear();
  for(int i=0; i<8; i++)
  {
	  cmbRcCal->Items->Add(i);
  };
  cmbRcCal->ItemIndex = 3;
  //PD_DCOCMP_LPF
  chbPwrDCCmpr->Checked = true;
  //PD_DCODAC_LPF
  chbPwrDCDac->Checked = true;
  //PD_DCOREF_LPF
  chbPwrDCRef->Checked = true;
  //PD_FIL_LPF
  chbPwrLpf->Checked = true;


	//DC_ADDR[3:0]
	cmbDCCalAddr->Clear();
  for(int i=0; i<5; i++)
  {
  	cmbDCCalAddr->Items->Add(i);
  };
  cmbDCCalAddr->ItemIndex = 0;

	//DC_CNTVAL[5:0]
	cmbCalVal->Clear();
  for(int i=0; i<64; i++)
  {
  	cmbCalVal->Items->Add(i);
  };
  cmbCalVal->ItemIndex = 31;

  m_DCClbrV[0] = 31;
  m_DCClbrV[1] = 31;
  m_DCClbrV[2] = 31;
  m_DCClbrV[3] = 31;
  m_DCClbrV[4] = 31;

  SetGuiDecode();

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------

void TfrmTxLpf::SetGuiDecode()
{
	if(rgrDecode->ItemIndex == 0)
  {
  	//Decode
  	chbPwrLpfMods->Enabled = true;

    chbPwrLpf->Enabled = false;
    chbPwrDCDac->Enabled = false;
    chbPwrDCRef->Enabled = false;
    if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
    {
      chbPwrDCCmpr->Enabled = true;
    }
    else
    {
      chbPwrDCCmpr->Enabled = false;
    };
    chbTX_DACBUF_EN->Enabled = false;
  }
  else
  {
  	//Direct control
  	chbPwrLpfMods->Enabled = false;

    chbPwrLpf->Enabled = true;
    chbPwrDCDac->Enabled = true;
    chbPwrDCRef->Enabled = true;
    chbPwrDCCmpr->Enabled = true;
    chbTX_DACBUF_EN->Enabled = true;
  };

  //if(m_frmADDC) m_frmADDC->SetGuiDecode(rgrDecode->ItemIndex);
};
//----------------------------------------------------------------------------
// Set GUI according to the chip version, revision and mask
//----------------------------------------------------------------------------
void TfrmTxLpf::UpdateVerRevMask(char Ver, char Rev, char Mask)
{
  m_cVer = Ver;
  m_cRev = Rev;
  m_cMask = Mask;

  m_bAllowSend = false;
  SetGuiDecode();
  m_bAllowSend = true;

  //Edit Register Test masks
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    m_psD.cTestMap[0xF] += 0x80;  //DC Offset comparator address is different when Mask=1
    m_psD.cTestMap[0x6] -= 0x08;
  };

};

//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmTxLpf::MakeData(int rAddr)
{
	char btmp;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;

  //======= register addr 0x02 =======
  m_psD.cDataW[0x02] = 0x00;
  btmp = (char)cmbCalVal->ItemIndex;
  m_psD.cDataW[0x02] |= btmp;

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x08;  //Not to reset calibration modules
	//DC_ADDR
  btmp = (char)cmbDCCalAddr->ItemIndex;
  m_psD.cDataW[0x03] |= btmp;


	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
  //BWC_LPF[3:0]
	btmp = cmbLpfBw->ItemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x04] |= btmp;
	//EN
	btmp = chbPwrLpfMods->Checked == true ? 1 : 0;
	btmp = btmp << 1; m_psD.cDataW[0x04] |= btmp;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//BYP_EN_LPF
	btmp = (char)rgrLpfByp->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x05] |= btmp;
	//DCO_DACCAL_LPF[5:0]
	btmp = (char)cmbDCOffset->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
  m_psD.cDataW[0x06] = 0x00;
  if(m_cMAddr == TxLpfAddr)
  {
    //TX_DACBUF_PD
  	btmp = chbTX_DACBUF_EN->Checked == true ? 0 : 1;
	  btmp = btmp << 7; m_psD.cDataW[0x06] |= btmp;
  }
	//RCCAL_LPF[2:0]
	btmp = (char)cmbRcCal->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x06] |= btmp;
	//PD_DCOCMP_LPF
	btmp = chbPwrDCCmpr->Checked == true ? 0 : 1;
	btmp = btmp << 3; m_psD.cDataW[0x06] |= btmp;
	//PD_DCODAC_LPF
	btmp = chbPwrDCDac->Checked == true ? 0 : 1;
	btmp = btmp << 2; m_psD.cDataW[0x06] |= btmp;
  //PD_DCOREF_LPF
	btmp = chbPwrDCRef->Checked == true ? 0 : 1;
	btmp = btmp << 1; m_psD.cDataW[0x06] |= btmp;
  //PD_FIL_LPF
	btmp = chbPwrLpf->Checked == true ? 0 : 1;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_frmADDC)
    {
    	//======= register addr 0x07 =======
    	m_psD.cDataW[0x07] = 0x00;
      //EN_ADC_DAC
    	btmp = m_frmADDC->chbEN_ADC_DAC->Checked == true ? 1 : 0;
	    btmp = btmp << 7; m_psD.cDataW[0x07] |= btmp;
      //DECODE
    	btmp = (char)m_frmADDC->rgrDecode->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x07] |= btmp;
      //TX_CTRL1[6:4]
    	btmp = (char)m_frmADDC->cmbDACInternalOutputLoadResistor->ItemIndex;
    	btmp = btmp << 3; m_psD.cDataW[0x07] |= btmp;
      //TX_CTRL1[3]
    	btmp = (char)m_frmADDC->rgrDACReferenceCurrentResistor->ItemIndex;
    	btmp = btmp << 2; m_psD.cDataW[0x07] |= btmp;
      //TX_CTRL1[1:0]
    	btmp = (char)m_frmADDC->cmbDACFullScaleOutputCurrent->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

    	//======= register addr 0x08 =======
    	m_psD.cDataW[0x08] = 0x00;
      //RX_CTRL1[7:6]
    	btmp = (char)m_frmADDC->cmbRefResistorBiasAdj->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x08] |= btmp;
      //RX_CTRL1[5:4]
    	btmp = (char)m_frmADDC->cmbRefBiasUp->ItemIndex;
    	btmp = btmp << 4; m_psD.cDataW[0x08] |= btmp;
      //RX_CTRL1[3:0]
    	btmp = (char)m_frmADDC->cmbRefBiasDn->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

    	//======= register addr 0x09 =======
    	m_psD.cDataW[0x09] = 0x00;
      //RX_CTRL2[7:6]
    	btmp = (char)m_frmADDC->cmbRefGainAdj->ItemIndex;
    	btmp = btmp << 5; m_psD.cDataW[0x09] |= btmp;
      //RX_CTRL2[5:4]
    	btmp = (char)m_frmADDC->cmbCoomonModeAdj->ItemIndex;
    	btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
      //RX_CTRL2[3:2]
    	btmp = (char)m_frmADDC->cmbRefBufferBoost->ItemIndex;
    	btmp = btmp << 1; m_psD.cDataW[0x09] |= btmp;
      //RX_CTRL2[0]
     	btmp = m_frmADDC->chkInputBufferDisable->Checked == true ? 1 : 0;
    	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

    	//======= register addr 0x0A =======
    	m_psD.cDataW[0x0A] = 0x00;
      //MISC_CTRL[9]
     	btmp = m_frmADDC->rgrRX_FSYNC_P->ItemIndex;
    	btmp = btmp << 7; m_psD.cDataW[0x0A] |= btmp;
      //MISC_CTRL[8]
     	btmp = m_frmADDC->rgrRX_INTER->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x0A] |= btmp;
      //MISC_CTRL[7]
     	btmp = m_frmADDC->rgrDAC_CLK_P->ItemIndex;
    	btmp = btmp << 5; m_psD.cDataW[0x0A] |= btmp;
      //MISC_CTRL[6]
     	btmp = m_frmADDC->rgrTX_FSYNC_P->ItemIndex;
    	btmp = btmp << 4; m_psD.cDataW[0x0A] |= btmp;
      //MISC_CTRL[5]
     	btmp = m_frmADDC->rgrTX_INTER->ItemIndex;
    	btmp = btmp << 3; m_psD.cDataW[0x0A] |= btmp;
      //RX_CTRL3[7]
     	btmp = m_frmADDC->cmbADCSamplingPhase->ItemIndex;
    	btmp = btmp << 2; m_psD.cDataW[0x0A] |= btmp;
      //RX_CTRL3[1:0]
     	btmp = m_frmADDC->cmbClockNonOverlapAdjust->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	    //======= register addr 0x0B =======
    	m_psD.cDataW[0x0B] = 0x00;
      //RX_CTRL4[7:6]
     	btmp = m_frmADDC->rgrADCBiasResistorAdjust->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x0B] |= btmp;
      //RX_CTRL4[5:4]
     	btmp = m_frmADDC->cmbMainBiasDN->ItemIndex;
      btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
      //RX_CTRL4[3:2]
     	btmp = m_frmADDC->rgrADCAmp1Stage1BasUp->ItemIndex;
    	btmp = btmp << 2; m_psD.cDataW[0x0B] |= btmp;
      //RX_CTRL4[1:0]
     	btmp = m_frmADDC->rgrADCAmp24Stage1BasUp->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	    //======= register addr 0x0C =======
    	m_psD.cDataW[0x0C] = 0x00;
      //RX_CTRL5[7:6]
     	btmp = m_frmADDC->rgrADCAmp1Stage2BasUp->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
      //RX_CTRL5[5:4]
     	btmp = m_frmADDC->rgrADCAmp24Stage2BasUp->ItemIndex;
    	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
      //RX_CTRL5[3:2]
     	btmp = m_frmADDC->rgrQuantizerBiasUp->ItemIndex;
    	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
      //RX_CTRL5[1:0]
     	btmp = m_frmADDC->rgrInputBufferBiasUp->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	    //======= register addr 0x0D =======
    	m_psD.cDataW[0x0D] = 0x00;
      //REF_CTRL0[7:4]
     	btmp = m_frmADDC->cmbBandgapTemp->ItemIndex + 8;
      btmp = btmp & 0x0F;
    	btmp = btmp << 4; m_psD.cDataW[0x0D] |= btmp;
      //REF_CTRL0[3:0]
     	btmp = m_frmADDC->cmbBandgapGain->ItemIndex + 8;
      btmp = btmp & 0x0F;
    	btmp = btmp << 0; m_psD.cDataW[0x0D] |= btmp;

    	//======= register addr 0x0E =======
    	m_psD.cDataW[0x0E] = 0x00;
      //REF_CTRL1[7:6]
     	btmp = m_frmADDC->cmbRefAmpsBiasAdj->ItemIndex;
    	btmp = btmp << 6; m_psD.cDataW[0x0E] |= btmp;
      //REF_CTRL1[5:4]
     	btmp = m_frmADDC->cmbRefAmpsBiasUp->ItemIndex;
    	btmp = btmp << 4; m_psD.cDataW[0x0E] |= btmp;
      //REF_CTRL1[3:0]
     	btmp = m_frmADDC->cmbRefAmpsBiasDn->ItemIndex;
    	btmp = btmp << 0; m_psD.cDataW[0x0E] |= btmp;

    	//======= register addr 0x0F =======
    	m_psD.cDataW[0x0F] = 0x00;
      //MISC_CTRL[4]
     	btmp = m_frmADDC->chkEN_DAC->Checked == true ? 1 : 0;
    	btmp = btmp << 4; m_psD.cDataW[0x0F] |= btmp;
    	//EN_ADC_I
    	btmp = m_frmADDC->chkEN_ADC_I->Checked == true ? 1 : 0;
	    btmp = btmp << 3; m_psD.cDataW[0x0F] |= btmp;
    	//EN_ADC_Q
    	btmp = m_frmADDC->chkEN_ADC_Q->Checked == true ? 1 : 0;
	    btmp = btmp << 2; m_psD.cDataW[0x0F] |= btmp;
  	  //EN_ADC_REF
    	btmp = m_frmADDC->chkEN_ADC_REF->Checked == true ? 1 : 0;
	    btmp = btmp << 1; m_psD.cDataW[0x0F] |= btmp;
    	//EN_M_REF
	    btmp = m_frmADDC->chkEN_M_REF->Checked == true ? 1 : 0;
  	  btmp = btmp << 0; m_psD.cDataW[0x0F] |= btmp;
    };
  };

  //To solve Ver=2 Rev=2 Mask=1 case
  //PD_DCOCMP_LPF
  btmp = chbPwrDCCmpr->Checked == true ? 0 : 1;
 	btmp = btmp << 7; m_psD.cDataW[0x0F] |= btmp;

  
	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{
  	//DC Calibration
    case 0xF0:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x03;
		break;

    case 0xF1:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x02;
		break;

		//User mode
		case 0x00:
		case 0x01:
		case 0x02:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x04;
		break;

		case 0x03:
		case 0x04:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x05;
		break;

    //Test mode
		case 0x05:
		case 0x06:
    case 0x07:
		case 0x08:
    case 0x09:
    case 0x0A:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x04;
			m_psD.iWInd[1] = 0x06;
		break;

    case 0x091:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0F;
		break;

		case 0x74:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x75:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x07;
		break;

		case 0x5F:
    case 0x60:
    case 0x61:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x08;
		break;

    case 0x62:
		case 0x63:
    case 0x64:
    case 0x65:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x09;
		break;

		case 0x50:
		case 0x51:
    case 0x52:
		case 0x53:
    case 0x54:
    case 0x66:
    case 0x67:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0A;
		break;

    case 0x68:
		case 0x69:
    case 0x6A:
    case 0x6B:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0B;
		break;

    case 0x6C:
		case 0x6D:
    case 0x6E:
    case 0x6F:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0C;
		break;
    
    case 0x5A:
    case 0x5B:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0D;
		break;

		case 0x5C:
    case 0x5D:
    case 0x5E:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0E;
		break;

    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0F;
		break;

    //Customer Mode
		case 0x80:
			m_psD.iToW = 2;
      m_psD.iWInd[0] = 0x04;
      m_psD.iWInd[1] = 0x05;
		break;

		default:
			m_psD.iToW = 0;
	};
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::cmbLpfBwChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbPwrLpfModsClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::rgrDecodeClick(TObject *Sender)
{
	SetGuiDecode();
  if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::rgrLpfBypClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::cmbDCOffsetChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x04); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::cmbRcCalChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbPwrLpfClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x06); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbPwrDCDacClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x07); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbPwrDCRefClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x08); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbPwrDCCmprClick(TObject *Sender)
{
//	if(m_bAllowSend){ MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if(m_bAllowSend){ MakeData(0x091); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  }
  else
  {
    if(m_bAllowSend){ MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::chbTX_DACBUF_ENClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::cmbDCCalAddrChange(TObject *Sender)
{
  //Enable DC CAL clock
/*
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x08); };
  }
  else
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x02); };
  };
*/
	if(m_bAllowSend){ MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };

  //Restore DC CAL clock
  //if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKRESTORE, 0, 0); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::cmbCalValChange(TObject *Sender)
{
	//if(m_bAllowSend){ MakeData(0xF1); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void TfrmTxLpf::JoinADDC(int Message)
{
  MakeData(Message); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::btnDCRstClbrClick(TObject *Sender)
{
  //Enable DC CAL clock
/*
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x08); };
  }
  else
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x02); };
  };
*/
	char btmp;
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Set Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x00;	//Set Reset Active
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)cmbDCCalAddr->ItemIndex;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Set Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)cmbDCCalAddr->ItemIndex;
  m_psD.cDataW[0x03] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  m_DCClbrV[0] = 31;
  m_DCClbrV[1] = 31;
  m_DCClbrV[2] = 31;
  m_DCClbrV[3] = 31;
  m_DCClbrV[4] = 31;

  //Restore DC CAL clock
  //if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKRESTORE, 0, 0); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::btnDCLoadValClick(TObject *Sender)
{
	char btmp;

  //Enable DC CAL clock
/*
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x08); };
  }
  else
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x02); };
  };
*/
	if(m_bAllowSend){ MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  if(m_bAllowSend){ MakeData(0xF1); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };


	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x01;	//Load Value
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)cmbDCCalAddr->ItemIndex;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);



	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Deactivate Load Value
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)cmbDCCalAddr->ItemIndex;
  m_psD.cDataW[0x03] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  m_DCClbrV[cmbDCCalAddr->ItemIndex] = cmbCalVal->ItemIndex;

  //Restore DC CAL clock
  //if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKRESTORE, 0, 0); };
}
//---------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void TfrmTxLpf::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
	for(int i=0; i<m_psD.iLen; i++)
	{
		m_psD.iWInd[i] = i;
	};
};

//----------------------------------------------------------------------------
// Save the chip configuration to the file
//----------------------------------------------------------------------------
bool TfrmTxLpf::ChipVsGui(ofstream &out, String Caption, bool bWrAll)
{
  bool bRez = true;
  bool btmp;
	char str[64] = "";
  int itmp;

  out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;

  if(bWrAll)
  {
  	//DC_REGVAL[5:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_REGVAL[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = DC_REGVAL_r00_b50();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_LOCK[2:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_LOCK[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = DC_LOCK_r01_b42(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_CLBR_DONE
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_CLBR_DONE"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	if(DC_CLBR_DONE_r01_b11()) strcpy(str, "Calibration in Progress"); else strcpy(str, "Calibration Done");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_UD
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_UD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_UD_r01_b00()) strcpy(str, "Counting Up"); else strcpy(str, "Counting Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_CNTVAL[5:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_CNTVAL[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = DC_CNTVAL_r02_b50(); out << dec;// << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_START_CLBR
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_START_CLBR"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_START_CLBR_r03_b55()) strcpy(str, "Start Active"); else strcpy(str, "Start Not Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_LOAD
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_LOAD"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	if(DC_LOAD_r03_b44()) strcpy(str, "Load Active"); else strcpy(str, "Load Not Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_SRESET
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_SRESET"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  if(DC_SRESET_r03_b33()) strcpy(str, "Reset Not Active"); else strcpy(str, "Reset Active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //DC_ADDR[2:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DC_ADDR[2:0]"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = DC_ADDR_r03_b20(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  };

  //BWC_LPF[3:0]
  if((cmbLpfBw->ItemIndex != BWC_LPF_r04_b52()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BWC_LPF[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbLpfBw->Items->Strings[cmbLpfBw->ItemIndex].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = BWC_LPF_r04_b52();
    strcpy(str, cmbLpfBw->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN
  if((chbPwrLpfMods->Checked != (bool)EN_r04_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrLpfMods->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(EN_r04_b11()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DECODE
  if((rgrDecode->ItemIndex != DECODE_r04_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode->ItemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  if(DECODE_r04_b00()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BYP_EN_LPF
  if((rgrLpfByp->ItemIndex != BYP_EN_LPF_r05_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BYP_EN_LPF"; out.width(2); out << "|";	out.width(40);
    if(rgrLpfByp->ItemIndex == 1) strcpy(str, "Bypass LPF"); else strcpy(str, "Normal Operation");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(BYP_EN_LPF_r05_b66()) strcpy(str, "Bypass LPF"); else strcpy(str, "Normal Operation");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DCO_DACCAL_LPF[5:0]
  if((cmbDCOffset->ItemIndex != DCO_DACCAL_r05_b50()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DCO_DACCAL_LPF[5:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbDCOffset->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = DCO_DACCAL_r05_b50(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //TX_DACBUF_EN
  if(m_cMAddr == TxLpfAddr)
  {
    if((chbTX_DACBUF_EN->Checked == (bool)TX_DACBUF_PD_r06_b77()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
  	  out.width(32); out << "| TX_DACBUF_EN"; out.width(2); out << "|";	out.width(40);
      if(chbTX_DACBUF_EN->Checked) strcpy(str, "TX DAC Buffers powered up"); else strcpy(str, "TX DAC Buffers powered down");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
	    if(TX_DACBUF_PD_r06_b77()) strcpy(str, "TX DAC Buffers powered down"); else strcpy(str, "TX DAC Buffers powered up");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  };

  //RCCAL_LPF[2:0]
  if((cmbRcCal->ItemIndex != RCCAL_LPF_PD_r06_b64()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RCCAL_LPF[2:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRcCal->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = RCCAL_LPF_PD_r06_b64(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };


  //PD_DCOCMP_LPF
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    if((chbPwrDCCmpr->Checked == (bool)PD_DCOCMP_LPF_r0F_b77_v1()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_DCOCMP_LPF"; out.width(2); out << "|";	out.width(40);
      if(chbPwrDCCmpr->Checked) strcpy(str, "DC Offset Comparator powered up"); else strcpy(str, "DC Offset Comparator powered down");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_DCOCMP_LPF_r0F_b77_v1()) strcpy(str, "DC Offset Comparator powered down"); else strcpy(str, "DC Offset Comparator powered up");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  }
  else
  {
    if((chbPwrDCCmpr->Checked == (bool)PD_DCOCMP_LPF_r06_b33_v0()) || bWrAll)
    {
      memset(str, '\0', sizeof(str));
	    out.width(32); out << "| PD_DCOCMP_LPF"; out.width(2); out << "|";	out.width(40);
      if(chbPwrDCCmpr->Checked) strcpy(str, "DC Offset Comparator powered up"); else strcpy(str, "DC Offset Comparator powered down");
      out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    	memset(str, '\0', sizeof(str));
  	  if(PD_DCOCMP_LPF_r06_b33_v0()) strcpy(str, "DC Offset Comparator powered down"); else strcpy(str, "DC Offset Comparator powered up");
      out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
      bRez = false;
    };
  };


  //PD_DCODAC_LPF
  if((chbPwrDCDac->Checked == (bool)PD_DCODAC_LPF_r06_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_DCODAC_LPF"; out.width(2); out << "|";	out.width(40);
    if(chbPwrDCDac->Checked) strcpy(str, "DC Offset DAC powered up"); else strcpy(str, "DC Offset DAC powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_DCODAC_LPF_r06_b22()) strcpy(str, "DC Offset DAC powered down"); else strcpy(str, "DC Offset DAC powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_DCOREF_LPF
  if((chbPwrDCRef->Checked == (bool)PD_DCOREF_LPF_r06_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_DCOREF_LPF"; out.width(2); out << "|";	out.width(40);
    if(chbPwrDCRef->Checked) strcpy(str, "DC DAC Reference powered up"); else strcpy(str, "DC DAC Reference powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_DCOREF_LPF_r06_b11()) strcpy(str, "DC DAC Reference powered down"); else strcpy(str, "DC DAC Reference powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_FIL_LPF
  if((chbPwrLpf->Checked == (bool)PD_FIL_LPF_r06_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_FIL_LPF"; out.width(2); out << "|";	out.width(40);
    if(chbPwrLpf->Checked) strcpy(str, "LPF powered up"); else strcpy(str, "LPF powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_FIL_LPF_r06_b00()) strcpy(str, "LPF powered down"); else strcpy(str, "LPF powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  }; 

  if(bRez && (!bWrAll))
  {
  	out.width(136); out << "| CHIP Configuration EQUALS GUI Configuration"; out.width(2); out << "|";
	  out << endl;
  };
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "" << endl;
	out << "" << endl;

  if(m_frmADDC) m_frmADDC->ChipVsGui(m_psD, out, "ADDC Modules:", bWrAll);

  return bRez;
};

//----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
//----------------------------------------------------------------------------
void TfrmTxLpf::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


	//DC_REGVAL[5:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x30 MASK 05 : 00  =";
  else                      out << "REG 0x50 MASK 05 : 00  =";
  itmp = DC_REGVAL_r00_b50();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_REGVAL";
  else                      out << "  RXLPF_DC_REGVAL";
  out << endl;

  //DC_LOCK[2:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x31 MASK 04 : 02  =";
  else                      out << "REG 0x51 MASK 04 : 02  =";
  itmp = DC_LOCK_r01_b42();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_LOCK";
  else                      out << "  RXLPF_DC_LOCK";
  out << endl;

  //DC_CLBR_DONE
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x31 MASK 01 : 01  =";
  else                      out << "REG 0x51 MASK 01 : 01  =";
  itmp = DC_CLBR_DONE_r01_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_CLBR_DONE";
  else                      out << "  RXLPF_DC_CLBR_DONE";
  out << endl;

  //DC_UD
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x31 MASK 00 : 00  =";
  else                      out << "REG 0x51 MASK 00 : 00  =";
  itmp = DC_UD_r01_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_UD";
  else                      out << "  RXLPF_DC_UD";
  out << endl;

  //DC_CNTVAL[5:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x32 MASK 05 : 00  =";
  else                      out << "REG 0x52 MASK 05 : 00  =";
  itmp = DC_CNTVAL_r02_b50();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_CNTVAL";
  else                      out << "  RXLPF_DC_CNTVAL";
  out << endl;

  //DC_START_CLBR
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x33 MASK 05 : 05  =";
  else                      out << "REG 0x53 MASK 05 : 05  =";
  itmp = DC_START_CLBR_r03_b55();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_START";
  else                      out << "  RXLPF_DC_START";
  out << endl;

  //DC_LOAD
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x33 MASK 04 : 04  =";
  else                      out << "REG 0x53 MASK 04 : 04  =";
  itmp = DC_LOAD_r03_b44();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_LOAD";
  else                      out << "  RXLPF_DC_LOAD";
  out << endl;

  //DC_SRESET
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x33 MASK 03 : 03  =";
  else                      out << "REG 0x53 MASK 03 : 03  =";
  itmp = DC_SRESET_r03_b33();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_SRESET";
  else                      out << "  RXLPF_DC_SRESET";
  out << endl;

  //DC_ADDR[2:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x33 MASK 02 : 00  =";
  else                      out << "REG 0x53 MASK 02 : 00  =";
  itmp = DC_ADDR_r03_b20();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DC_ADDR";
  else                      out << "  RXLPF_DC_ADDR";
  out << endl;

  //BWC_LPF[3:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x34 MASK 05 : 02  =";
  else                      out << "REG 0x54 MASK 05 : 02  =";
  itmp = BWC_LPF_r04_b52();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_BWC_LPF";
  else                      out << "  RXLPF_BWC_LPF";
  out << endl;

  //EN
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x34 MASK 01 : 01  =";
  else                      out << "REG 0x54 MASK 01 : 01  =";
  itmp = EN_r04_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_EN";
  else                      out << "  RXLPF_EN";
  out << endl;

  //DECODE
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x34 MASK 00 : 00  =";
  else                      out << "REG 0x54 MASK 00 : 00  =";
  itmp = DECODE_r04_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DECODE";
  else                      out << "  RXLPF_DECODE";
  out << endl;

  //BYP_EN_LPF
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x35 MASK 06 : 06  =";
  else                      out << "REG 0x55 MASK 06 : 06  =";
  itmp = BYP_EN_LPF_r05_b66();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_BYP_EN";
  else                      out << "  RXLPF_BYP_EN";
  out << endl;

  //DCO_DACCAL_LPF[5:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x35 MASK 05 : 00  =";
  else                      out << "REG 0x55 MASK 05 : 00  =";
  itmp = DCO_DACCAL_r05_b50();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DCO_DACCAL";
  else                      out << "  RXLPF_DCO_DACCAL";
  out << endl;

  //TX_DACBUF_PD
  if(m_cMAddr == TxLpfAddr)
  {
    out.width(24); out << left; out << "REG 0x36 MASK 07 : 07  =";
    itmp = TX_DACBUF_PD_r06_b77();
    out.width(6); out << right; out << itmp;
    out << "  TX_DACBUF_PD"; out << endl;
  };

  //RCCAL_LPF[2:0]
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x36 MASK 06 : 04  =";
  else                      out << "REG 0x56 MASK 06 : 04  =";
  itmp = RCCAL_LPF_PD_r06_b64();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_RCCAL";
  else                      out << "  RXLPF_RCCAL";
  out << endl;

  //PD_DCOCMP_LPF
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    out.width(24); out << left;
    if(m_cMAddr == TxLpfAddr) out << "REG 0x3F MASK 80 : 80  =";
    else                      out << "REG 0x5F MASK 80 : 80  =";
    itmp = PD_DCOCMP_LPF_r0F_b77_v1();
    out.width(6); out << right; out << itmp;
    if(m_cMAddr == TxLpfAddr) out << "  TXLPF_PD_DCOCMP";
    else                      out << "  RXLPF_PD_DCOCMP";
    out << endl;
  }
  else
  {
    out.width(24); out << left;
    if(m_cMAddr == TxLpfAddr) out << "REG 0x36 MASK 03 : 03  =";
    else                      out << "REG 0x56 MASK 03 : 03  =";
    itmp = PD_DCOCMP_LPF_r06_b33_v0();
    out.width(6); out << right; out << itmp;
    if(m_cMAddr == TxLpfAddr) out << "  TXLPF_PD_DCOCMP";
    else                      out << "  RXLPF_PD_DCOCMP";
    out << endl;
  };

  //PD_DCODAC_LPF
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x36 MASK 02 : 02  =";
  else                      out << "REG 0x56 MASK 02 : 02  =";
  itmp = PD_DCODAC_LPF_r06_b22();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DCODAC";
  else                      out << "  RXLPF_DCODAC";
  out << endl;

  //PD_DCOREF_LPF
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x36 MASK 01 : 01  =";
  else                      out << "REG 0x56 MASK 01 : 01  =";
  itmp = PD_DCOREF_LPF_r06_b11();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_DCOREF";
  else                      out << "  RXLPF_DCOREF";
  out << endl;

  //PD_FIL_LPF
  out.width(24); out << left;
  if(m_cMAddr == TxLpfAddr) out << "REG 0x36 MASK 00 : 00  =";
  else                      out << "REG 0x56 MASK 00 : 00  =";
  itmp = PD_FIL_LPF_r06_b00();
  out.width(6); out << right; out << itmp;
  if(m_cMAddr == TxLpfAddr) out << "  TXLPF_PD_FIL";
  else                      out << "  RXLPF_PD_FIL";
  out << endl;




  if(m_cMAddr == RxLpfAddr)
  {
    m_frmADDC->MakeRegisterFile(m_psD, out);
  };
}

//----------------------------------------------------------------------------
// Writes Register - Value format to the file.
//----------------------------------------------------------------------------
void TfrmTxLpf::MakeRVFFile(ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //0x00 - Read Only

  //0x01 - Read Only

  //0x02
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
  out << iRval; out << endl;

  //0x03
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
  out << iRval; out << endl;

  //0x04
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x3F);
  out << iRval; out << endl;

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0x7F);
  out << iRval; out << endl;

  //0x06
  if(m_cMAddr == TxLpfAddr)
  {
    iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
    out << iRval; out << endl;
  }
  else
  {
    iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
    out << iRval; out << endl;
  };

  if(m_cMAddr == RxLpfAddr)
  {
    m_frmADDC->MakeRVFFile(m_psD, out);
  };

  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1) && (m_cMAddr == RxLpfAddr))
  {
    iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0x80);
    out << iRval; out << endl;
  };
};


//----------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//----------------------------------------------------------------------------
void TfrmTxLpf::MakeRFIFFile(ofstream &out, char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  if(m_cMAddr == TxLpfAddr) out << "echo \"Now programming the Lime Tx LPF\"" << endl << endl;
  else                      out << "echo \"Now programming the Lime Rx LPF\"" << endl << endl;


  //0x00 - Read Only

  //0x01 - Read Only

  //0x02
  //out << "# Register(s): DC_CNTVAL[5:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): DC_START_CLBR, DC_ADDR, DC_LOAD, DC_SRESET, DC_ADDR[2:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x04
  //out << "# Register(s): BWC_LPF[3:0], EN, DECODE" << endl;
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x05
  //out << "# Register(s): BYP_EN_LPF, DCO_DACCAL[5:0]" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
  //else                      out << FRIF_SPI_A_RX;
  //out << endl;
  out << FRIF_SPI_A; out << endl;

  //0x06
  if(m_cMAddr == TxLpfAddr)
  {
    //out << "# Register(s): TX_DACBUF_PD, RCCAL_LPF[2:0], PD_DCOCMP_LPF, PD_DCODAC_LPF, PD_DCOREF_LPF, PD_FIL_LPF" << endl;

    //To resolove Ver=2 Rev=2 Mask=1 version
    if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
    {
      iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xF7);
    }
    else
    {
      iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0xFF);
    };

    out << FRIF_DIR_W;
    //out << hex << uppercase << showbase << iRval;
    out << "0x" << hex << uppercase << noshowbase << iRval;
    //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
    //else                      out << FRIF_SPI_A_RX;
    //out << endl;
    out << FRIF_SPI_A; out << endl;
  }
  else
  {
    //out << "# Register(s): RCCAL_LPF[2:0], PD_DCOCMP_LPF, PD_DCODAC_LPF, PD_DCOREF_LPF, PD_FIL_LPF" << endl;
    //out << "# Register(s): " << endl;
    iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
    out << FRIF_DIR_W;
    //out << hex << uppercase << showbase << iRval;
    out << "0x" << hex << uppercase << noshowbase << iRval;
    //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
    //else                      out << FRIF_SPI_A_RX;
    //out << endl;
    out << FRIF_SPI_A; out << endl;
  };

  if(m_cMAddr == RxLpfAddr)
  {
    m_frmADDC->MakeRFIFFile(m_psD, out, FRIF_SPI_A);
  }
  else
  {
    //0x0F
    //out << "# Register(s): PD_DCOCMP_LPF" << endl;
    iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0x80);
    out << FRIF_DIR_W;
    //out << hex << uppercase << showbase << iRval;
    out << "0x" << hex << uppercase << noshowbase << iRval;
    //if(m_cMAddr == TxPllAddr) out << FRIF_SPI_A_TX;
    //else                      out << FRIF_SPI_A_RX;
    //out << endl;
    out << FRIF_SPI_A; out << endl;
  };

  if(m_cMAddr == TxLpfAddr) out << endl << "echo \"Tx LPF programming complete\"" << endl << endl;
  else                      out << endl << "echo \"Rx LPF programming complete\"" << endl << endl;
};


//---------------------------------------------------------------------------
// Sets GUI under data from chip
//---------------------------------------------------------------------------
bool TfrmTxLpf::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;

  m_bAllowSend = false;

  //DC_REGVAL[5:0]
  itmp = DC_REGVAL_r00_b50();
  lbDC_REGVAL->Caption = itmp;

  //DC_LOCK[2:0]
  itmp = DC_LOCK_r01_b42();
  lblDC_LOCK->Caption = itmp;

  //DC_CLBR_DONE
  itmp = DC_CLBR_DONE_r01_b11();
  lblDC_CLBR_DONE->Caption = itmp;

  //DC_UD
  itmp = DC_UD_r01_b00();
  lblDC_UD->Caption = itmp;

  //DC_CNTVAL[5:0]
  itmp = DC_CNTVAL_r02_b50();
  cmbCalVal->ItemIndex = itmp;

  //DC_START_CLBR
  itmp = DC_START_CLBR_r03_b55();

  //DC_LOAD
  itmp = DC_LOAD_r03_b44();

  //DC_SRESET
  itmp = DC_SRESET_r03_b33();

  //DC_ADDR[2:0]
  itmp = DC_ADDR_r03_b20();
  if(itmp > 4) {itmp = 4; bRez = false;}
  cmbDCCalAddr->ItemIndex = itmp;

  //BWC_LPF[3:0]
  itmp = BWC_LPF_r04_b52();
  cmbLpfBw->ItemIndex = itmp;

  //EN
  itmp = EN_r04_b11();
  chbPwrLpfMods->Checked = itmp;

  //DECODE
  itmp = DECODE_r04_b00();
  rgrDecode->ItemIndex = itmp;

  //BYP_EN_LPF
  itmp = BYP_EN_LPF_r05_b66();
  rgrLpfByp->ItemIndex = itmp;

  //DCO_DACCAL_LPF[5:0]
  itmp = DCO_DACCAL_r05_b50();
  cmbDCOffset->ItemIndex = itmp;

  //TX_DACBUF_EN
  if(m_cMAddr == TxLpfAddr)
  {
    itmp = TX_DACBUF_PD_r06_b77();
    chbTX_DACBUF_EN->Checked = itmp;
    chbTX_DACBUF_EN->Checked = !chbTX_DACBUF_EN->Checked;
  };

  //RCCAL_LPF[2:0]
  itmp = RCCAL_LPF_PD_r06_b64();
  cmbRcCal->ItemIndex = itmp;


  //PD_DCOCMP_LPF
  //To resolove Ver=2 Rev=2 Mask=1 version
  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    itmp = PD_DCOCMP_LPF_r0F_b77_v1();
  }
  else
  {
    itmp = PD_DCOCMP_LPF_r06_b33_v0();
  };
  chbPwrDCCmpr->Checked = itmp;
  chbPwrDCCmpr->Checked = !chbPwrDCCmpr->Checked;


  //PD_DCODAC_LPF
  itmp = PD_DCODAC_LPF_r06_b22();
  chbPwrDCDac->Checked = itmp;
  chbPwrDCDac->Checked = !chbPwrDCDac->Checked;

  //PD_DCOREF_LPF
  itmp = PD_DCOREF_LPF_r06_b11();
  chbPwrDCRef->Checked = itmp;
  chbPwrDCRef->Checked = !chbPwrDCRef->Checked;

  //PD_FIL_LPF
  itmp = PD_FIL_LPF_r06_b00();
  chbPwrLpf->Checked = itmp;
  chbPwrLpf->Checked = !chbPwrLpf->Checked;


  m_bAllowSend = true;

  if(m_frmADDC) m_frmADDC->SetGUIUnderReadback(m_psD);

  return bRez;
};

//---------------------------------------------------------------------------
void TfrmTxLpf::UpdateFormData()
{
	int itmp;
  String str;
  
	//DC_REGVAL[5:0]
  itmp = DC_REGVAL_r00_b50();
  lbDC_REGVAL->Caption = itmp;

  //DC_LOCK[2:0]
	itmp = DC_LOCK_r01_b42();
  lblDC_LOCK->Caption = itmp;

  //DC_CLBR_DONE
	if(DC_CLBR_DONE_r01_b11()) str = "In Progress"; else str = "Done";
  lblDC_CLBR_DONE->Caption = str;

  //DC_UD
	if(DC_UD_r01_b00()) str = "Up"; else str = "Down";
  lblDC_UD->Caption = str;
};

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TfrmTxLpf::SaveConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;
	pini->WriteInteger(Sect, "cmbDCCalAddr", cmbDCCalAddr->ItemIndex);
  pini->WriteInteger(Sect, "cmbCalVal", cmbCalVal->ItemIndex);
  pini->WriteInteger(Sect, "LPF_dco_I", GetCalVal(0x00));
  pini->WriteInteger(Sect, "LPF_dco_Q", GetCalVal(0x01));


  pini->WriteInteger(Sect, "cmbLpfBw", cmbLpfBw->ItemIndex);
  pini->WriteBool(Sect, "chbPwrLpfMods", chbPwrLpfMods->Checked);
  pini->WriteInteger(Sect, "rgrDecode", rgrDecode->ItemIndex);

  pini->WriteInteger(Sect, "rgrLpfByp", rgrLpfByp->ItemIndex);
  pini->WriteInteger(Sect, "cmbDCOffset", cmbDCOffset->ItemIndex);

  pini->WriteBool(Sect, "chbTX_DACBUF_EN", chbTX_DACBUF_EN->Checked);
  pini->WriteInteger(Sect, "cmbRcCal", cmbRcCal->ItemIndex);
  pini->WriteBool(Sect, "chbPwrDCCmpr", chbPwrDCCmpr->Checked);
  pini->WriteBool(Sect, "chbPwrDCDac", chbPwrDCDac->Checked);
  pini->WriteBool(Sect, "chbPwrDCRef", chbPwrDCRef->Checked);
  pini->WriteBool(Sect, "chbPwrLpf", chbPwrLpf->Checked);   
};

//---------------------------------------------------------------------------
void TfrmTxLpf::ReadConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

  m_bAllowSend = false;

	cmbDCCalAddr->ItemIndex = pini->ReadInteger(Sect, "cmbDCCalAddr", 0);
  cmbCalVal->ItemIndex = pini->ReadInteger(Sect, "cmbCalVal", 31);
  m_DCClbrV[0] = pini->ReadInteger(Sect, "LPF_dco_I", 31);
  m_DCClbrV[1] = pini->ReadInteger(Sect, "LPF_dco_Q", 31);
  

  cmbLpfBw->ItemIndex = pini->ReadInteger(Sect, "cmbLpfBw", 0);
  chbPwrLpfMods->Checked = pini->ReadBool(Sect, "chbPwrLpfMods", 1);
  rgrDecode->ItemIndex = pini->ReadInteger(Sect, "rgrDecode", 0);

  rgrLpfByp->ItemIndex = pini->ReadInteger(Sect, "rgrLpfByp", 0);
  cmbDCOffset->ItemIndex = pini->ReadInteger(Sect, "cmbDCOffset", 12);

  chbTX_DACBUF_EN->Checked = pini->ReadBool(Sect, "chbTX_DACBUF_EN", 1);
  cmbRcCal->ItemIndex = pini->ReadInteger(Sect, "cmbRcCal", 3);
  chbPwrDCCmpr->Checked = pini->ReadBool(Sect, "chbPwrDCCmpr", 1);
  chbPwrDCDac->Checked = pini->ReadBool(Sect, "chbPwrDCDac", 1);
  chbPwrDCRef->Checked = pini->ReadBool(Sect, "chbPwrDCRef", 1);
  chbPwrLpf->Checked = pini->ReadBool(Sect, "chbPwrLpf", 1);

  m_bAllowSend = true;
};




//if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };


void __fastcall TfrmTxLpf::btnDCReadValClick(TObject *Sender)
{
  //Enable DC CAL clock
/*
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x08); };
  }
  else
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x02); };
  };
*/
  MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
	SendMessage(G_hwWindow, CM_READ, 1, m_cMAddr);

  //Restore DC CAL clock
  //if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKRESTORE, 0, 0); };
}

//---------------------------------------------------------------------------
// Activate start calibration command and then deactivate.
//---------------------------------------------------------------------------
void __fastcall TfrmTxLpf::btnDCStartClbrClick(TObject *Sender)
{
  //Enable DC CAL clock
/*
  if(m_cMAddr == RxLpfAddr)
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x08); };
  }
  else
  {
    if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKONMASK, 0, 0x02); };
  };
*/
  StartCalibration(cmbDCCalAddr->ItemIndex);

  //Restore DC CAL clock
  //if(m_bAllowSend){ SendMessage(G_hwWindow, CM_SPICLKRESTORE, 0, 0); };
}
void TfrmTxLpf::StartCalibration(int Addr)
{
	char btmp;
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_LOAD
  btmp = 0x01;	//Start Calibration
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  //btmp = (char)cmbDCCalAddr->ItemIndex;
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_LOAD
  btmp = 0x00;	//Deactivate Start Calibration
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  //btmp = (char)cmbDCCalAddr->ItemIndex;
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  //m_DCClbrV[cmbDCCalAddr->ItemIndex] = GetCalVal(cmbDCCalAddr->ItemIndex);
  m_DCClbrV[Addr] = GetCalVal(Addr);

};

//---------------------------------------------------------------------------
// Read DC Calibration value
//---------------------------------------------------------------------------
int TfrmTxLpf::GetCalVal(int Addr)
{
	char btmp;

  // Change address to Addr
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Set Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  //Read SPI configuration
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

  //Return value
	//DC_REGVAL[5:0]
  return (m_psD.cDataR[0x00] & 0x3F);
};

//---------------------------------------------------------------------------
// Write DC Calibration value
//---------------------------------------------------------------------------
void TfrmTxLpf::SetCalVal(int Addr, int Val)
{
  char btmp;
  
  // Change address to Addr
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_START_CLBR
  btmp = 0x00;	//Set Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  //Write Value to DC_CNTVAL[5:0] register
  //======= register addr 0x02 =======
  m_psD.cDataW[0x02] = 0x00;
  btmp = (char)Val;
  m_psD.cDataW[0x02] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x02;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

  //Perform Load Operation
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x01;	//Load Value Active
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); 

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_LOAD
  btmp = 0x00;	//Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

};


//---------------------------------------------------------------------------
// Set calibration chain address
//---------------------------------------------------------------------------
void TfrmTxLpf::SetCalAddr(int Addr)
{
  char btmp;
  
  // Change address to Addr
	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //DC_START_CLBR
  btmp = 0x00;	//Set Start Calibration Inactive
  btmp = btmp << 5; m_psD.cDataW[0x03] |= btmp;
  //DC_START_CLBR
  btmp = 0x00;	//Set Load Value Inactive
  btmp = btmp << 4; m_psD.cDataW[0x03] |= btmp;
  //DC_SRESET
  btmp = 0x01;	//Set Reset Inactive
  btmp = btmp << 3; m_psD.cDataW[0x03] |= btmp;
	//DC_ADDR
  btmp = (char)Addr;
  m_psD.cDataW[0x03] |= btmp;

	m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x03;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

//---------------------------------------------------------------------------
// Write All DC Calibration values
//---------------------------------------------------------------------------
void TfrmTxLpf::DownloadAllDCCalValues()
{
  SetCalVal(0x00, m_DCClbrV[0]);
  SetCalVal(0x01, m_DCClbrV[1]);
};

//---------------------------------------------------------------------------
// Returns DC Calibration Chain status (address 0x1)
// Address of DC Calibration Chain should be settled before.
//---------------------------------------------------------------------------
char TfrmTxLpf::GetCalStatus()
{
  //Read SPI configuration
  SendMessage(G_hwWindow, CM_READ, 0, m_cMAddr);

  //Return value
	//DC_REGVAL[5:0]
  return m_psD.cDataR[0x01];
};

//---------------------------------------------------------------------------
// Set DC Calibration values in the Class to defaults
//---------------------------------------------------------------------------
void TfrmTxLpf::SetCalDefaults()
{
  m_DCClbrV[0] = 31;
  m_DCClbrV[1] = 31;
  m_DCClbrV[2] = 31;
  m_DCClbrV[3] = 31;
  m_DCClbrV[4] = 31;
};

//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void TfrmTxLpf::CustSet_BypassLpfON()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrLpfMods->Checked = false;
  rgrLpfByp->ItemIndex = 1;
  m_bAllowSend = true;

  MakeData(0x80); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_BypassLpfOFF()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrLpfMods->Checked = true;
  rgrLpfByp->ItemIndex = 0;
  m_bAllowSend = true;

  MakeData(0x80); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_LpfPowerON()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrLpfMods->Checked = true;
  m_bAllowSend = true;

  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_LpfPowerOFF()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrLpfMods->Checked = false;
  m_bAllowSend = true;

  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_EnableDCOffsetCompOnly()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 1;
  chbPwrLpf->Checked = false;
  chbPwrDCDac->Checked = false;
  chbPwrDCRef->Checked = false;
  chbPwrDCCmpr->Checked = true;
  m_bAllowSend = true;

  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    MakeData(0x091); 
  }
  else
  {
    MakeData(0x09);
  };
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};


void TfrmTxLpf::CustSet_RestoreDCOffsetCompOnly()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrDCCmpr->Checked = false;
  m_bAllowSend = true;

  if((m_cVer == 2) && (m_cRev == 2) && (m_cMask == 1))
  {
    MakeData(0x091); 
  }
  else
  {
    MakeData(0x09);
  };
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_BypassLPFOnlyOn()
{
  m_bAllowSend = false;
  rgrLpfByp->ItemIndex = 1;
  m_bAllowSend = true;

  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_BypassLPFOnlyOff()
{
  m_bAllowSend = false;
  rgrLpfByp->ItemIndex = 0;
  m_bAllowSend = true;

  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_LPFCALVAL(int Val)
{
  m_bAllowSend = false;
  cmbRcCal->ItemIndex = Val;
  m_bAllowSend = true;

  MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTxLpf::CustSet_LPFDCVAL(int Val)
{
  m_bAllowSend = false;
  cmbDCOffset->ItemIndex = Val;
  m_bAllowSend = true;

  MakeData(0x04); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

int TfrmTxLpf::CustGet_DecodeState()
{
  return rgrDecode->ItemIndex;
};

void TfrmTxLpf::CustSet_DecodeState(int ind)
{
  rgrDecode->ItemIndex = ind;
  rgrDecodeClick(Application);
};

int TfrmTxLpf::CustGet_LPFTestState()
{
  return rgrLpfByp->ItemIndex;
};

void TfrmTxLpf::CustSet_LPFTestState(int ind)
{
  rgrLpfByp->ItemIndex = ind;
  rgrLpfBypClick(Application);
};

bool TfrmTxLpf::CustGet_PwrLpfMods()
{
  return chbPwrLpfMods->Checked;
};

bool TfrmTxLpf::CustGet_PwrLpf()
{
  return chbPwrLpf->Checked;
};

bool TfrmTxLpf::CustGet_PwrDCDac()
{
  return chbPwrDCDac->Checked;
};

bool TfrmTxLpf::CustGet_PwrDCRef()
{
  return chbPwrDCRef->Checked;
};

bool TfrmTxLpf::CustGet_PwrDCCmpr()
{
  return chbPwrDCCmpr->Checked;
};

void TfrmTxLpf::CustGet_PwrLpfMods(bool state)
{
  chbPwrLpfMods->Checked = state;
  chbPwrLpfModsClick(Application);
};

void TfrmTxLpf::CustGet_PwrLpf(bool state)
{
  chbPwrLpf->Checked = state;
  chbPwrLpfClick(Application);
};

void TfrmTxLpf::CustGet_PwrDCDac(bool state)
{
  chbPwrDCDac->Checked = state;
  chbPwrDCDacClick(Application);
};

void TfrmTxLpf::CustGet_PwrDCRef(bool state)
{
  chbPwrDCRef->Checked = state;
  chbPwrDCRefClick(Application);
};

void TfrmTxLpf::CustGet_PwrDCCmpr(bool state)
{
  chbPwrDCCmpr->Checked = state;
  chbPwrDCCmprClick(Application);
};

//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void TfrmTxLpf::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};


