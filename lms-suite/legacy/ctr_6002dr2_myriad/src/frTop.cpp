// -----------------------------------------------------------------------------
// FILE: 		    frTop.cpp
// DESCRIPTION:	Top control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frTop.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSwitch"
#pragma resource "*.dfm"
//TfrmTop *frmTop;


//0x0
#define             DC_REGVAL_r00_b50() ((m_psD.cDataR[0x00] & 0x3F) >> 0)
//0x1
#define          RCCAL_LPFCAL_r01_b75() ((m_psD.cDataR[0x01] & 0xE0) >> 5)
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
#define                   VER_r04_b74() ((m_psD.cDataR[0x04] & 0xF0) >> 4)
#define                   REV_r04_b30() ((m_psD.cDataR[0x04] & 0x0F) >> 0)
//0x5
#define                DECODE_r05_b77() ((m_psD.cDataR[0x05] & 0x80) >> 7)
#define                SRESET_r05_b55() ((m_psD.cDataR[0x05] & 0x20) >> 5)
#define                    EN_r05_b44() ((m_psD.cDataR[0x05] & 0x10) >> 4)
#define                 STXEN_r05_b33() ((m_psD.cDataR[0x05] & 0x08) >> 3)
#define                 SRXEN_r05_b22() ((m_psD.cDataR[0x05] & 0x04) >> 2)
#define               TFWMODE_r05_b11() ((m_psD.cDataR[0x05] & 0x02) >> 1)
//0x6
#define         CLKSEL_LPFCAL_r06_b33() ((m_psD.cDataR[0x06] & 0x08) >> 3)
#define          PD_CLKLPFCAL_r06_b22() ((m_psD.cDataR[0x06] & 0x04) >> 2)
#define     ENF_EN_CAL_LPFCAL_r06_b11() ((m_psD.cDataR[0x06] & 0x02) >> 1)
#define        RST_CAL_LPFCAL_r06_b00() ((m_psD.cDataR[0x06] & 0x01) >> 0)
//0x7
#define         EN_CAL_LPFCAL_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define FORCE_CODE_CAL_LPFCAL_r07_b64() ((m_psD.cDataR[0x07] & 0x70) >> 4)
#define            BWC_LPFCAL_r07_b30() ((m_psD.cDataR[0x07] & 0x0F) >> 0)
//0x8
#define                 BBBYP_r08_b77() ((m_psD.cDataR[0x08] & 0x80) >> 7)
#define            LBEN_LPFIN_r08_b66() ((m_psD.cDataR[0x08] & 0x40) >> 6)
#define           LBEN_VGA2IN_r08_b55() ((m_psD.cDataR[0x08] & 0x20) >> 5)
#define             LBEN_OPIN_r08_b44() ((m_psD.cDataR[0x08] & 0x10) >> 4)
#define                  LBEN_r08_b64() ((m_psD.cDataR[0x08] & 0x70) >> 4)
#define                LBRFEN_r08_b30() ((m_psD.cDataR[0x08] & 0x0F) >> 0)
//0x9
#define               RXOUTSW_r09_b77() ((m_psD.cDataR[0x09] & 0x80) >> 7)
#define             PLLCLKOUT_r09_b66() ((m_psD.cDataR[0x09] & 0x40) >> 6)
#define               LPF_CAL_r09_b55() ((m_psD.cDataR[0x09] & 0x20) >> 5)
#define         Rx_VGA2_DCCAL_r09_b44() ((m_psD.cDataR[0x09] & 0x10) >> 4)
#define          Rx_LPF_DCCAL_r09_b33() ((m_psD.cDataR[0x09] & 0x08) >> 3)
#define            Rx_DSM_SPI_r09_b22() ((m_psD.cDataR[0x09] & 0x04) >> 2)
#define      Tx_LPF_SPI_DCCAL_r09_b11() ((m_psD.cDataR[0x09] & 0x02) >> 1)
#define            Tx_DSM_SPI_r09_b00() ((m_psD.cDataR[0x09] & 0x01) >> 0)
//0xA
#define                FDDTDD_r0A_b11() ((m_psD.cDataR[0x0A] & 0x02) >> 1)
#define                TDDMOD_r0A_b00() ((m_psD.cDataR[0x0A] & 0x01) >> 0)
//0xB
#define              PDXCOBUF_r0B_b44() ((m_psD.cDataR[0x0B] & 0x10) >> 4)
#define            SLFBXCOBUF_r0B_b33() ((m_psD.cDataR[0x0B] & 0x08) >> 3)
#define             BYPXCOBUF_r0B_b22() ((m_psD.cDataR[0x0B] & 0x04) >> 2)
#define      PD_DCOREF_LPFCAL_r0B_b11() ((m_psD.cDataR[0x0B] & 0x02) >> 1)
#define            RF_LBSW_PD_r0B_b00() ((m_psD.cDataR[0x0B] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"


//---------------------------------------------------------------------------
__fastcall TfrmTop::TfrmTop(TComponent* Owner)
	: TFrame(Owner)
{
}

//---------------------------------------------------------------------------
__fastcall TfrmTop::~TfrmTop(void)
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
void TfrmTop::Initialize(char MAddr)
{
	m_cMAddr = MAddr;
  
	m_psD.iLen = TopLen;
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
  m_psD.cTestMap[0x0] = 0x00;
  m_psD.cTestMap[0x1] = 0x00;
  m_psD.cTestMap[0x2] = 0x3F;
  m_psD.cTestMap[0x3] = 0x3F;
  m_psD.cTestMap[0x4] = 0x00;
  m_psD.cTestMap[0x5] = 0xBE; //0xBC
  m_psD.cTestMap[0x6] = 0x0F;
  m_psD.cTestMap[0x7] = 0xFF;
  m_psD.cTestMap[0x8] = 0xFF;
  m_psD.cTestMap[0x9] = 0xFF;
  m_psD.cTestMap[0xA] = 0x03;
  m_psD.cTestMap[0xB] = 0x1F;
  //m_psD.cTestMap[0xC] = 0x00;
  //m_psD.cTestMap[0xD] = 0x00;
  //m_psD.cTestMap[0xE] = 0x00;
  //m_psD.cTestMap[0xF] = 0x00;

  SetGuiDefaults();
};

//---------------------------------------------------------------------------
void TfrmTop::SetGuiDefaults()
{
	m_bAllowSend = false;

	//DECODE
  rgrDecode->ItemIndex = 0;
  //SRESET
  rgrDsmRst->ItemIndex = 1;
  //EN
  chbPwrTopMods->Checked = true;
  //STXEN
  chbPwrSoftTx->Checked = false;
  //SRXEN
  chbPwrSoftRx->Checked = false;
  //TFWMODE
  rgrSpiMode->ItemIndex = 1;

  //CLKSEL_LPFCAL
  rgrCLKSEL_LPFCAL->ItemIndex = 1;
  //PD_CLKLPFCAL
  chbPD_CLKLPFCAL->Checked = true;
  //ENF_EN_CAL_LPFCAL
  chkLpfCalEnEnf->Checked = false;
  //RST_CAL_LPFCAL
  chkLpfCalRst->Checked = true;

  //EN_CAL_LPFCAL
  chkLpfCalEn->Checked = false;
  //FORCE_CODE_CAL_LPFCAL[2:0]
  cmbLpfCalCode->Clear();
  for(int i=0; i<8; i++)
  {
	  cmbLpfCalCode->Items->Add(i);
  };
  cmbLpfCalCode->ItemIndex = 0;
  //BWC_LPFCAL[3:0]
  cmbLpfCalBw->Clear();
  cmbLpfCalBw->Items->Add("14");
  cmbLpfCalBw->Items->Add("10");
  cmbLpfCalBw->Items->Add("7");
  cmbLpfCalBw->Items->Add("6");
  cmbLpfCalBw->Items->Add("5");
  cmbLpfCalBw->Items->Add("4.375");
  cmbLpfCalBw->Items->Add("3.5");
  cmbLpfCalBw->Items->Add("3");
  cmbLpfCalBw->Items->Add("2.75");
  cmbLpfCalBw->Items->Add("2.5");
  cmbLpfCalBw->Items->Add("1.92");
  cmbLpfCalBw->Items->Add("1.5");
  cmbLpfCalBw->Items->Add("1.375");
  cmbLpfCalBw->Items->Add("1.25");
  cmbLpfCalBw->Items->Add("0.875");
  cmbLpfCalBw->Items->Add("0.75");
  cmbLpfCalBw->ItemIndex = 0;

  //BBBYP_RX
  chbRxTestModeEn->Checked = false;
  //Control changed to radiobuttons instead of checkboxes,
  // while only one should be active at a time:
  //LBEN_LPFIN_RX
  //LBEN_VGA2IN_RX
  //LBEN_OPIN_RX
  rgrBBLB->ItemIndex = 0;
  //LBRFEN_RXFE[3:0]
  rgrRFLB->ItemIndex = 0;

  //RXOUTSW
  rgrRXOUTSW->ItemIndex = 0;
  //CLK_EN[6:0]
  for(int i=0; i<6; i++)
  {
	  chbSpiClkBuf->Checked[i] = false;
  };
  chbSpiClkBuf->Checked[6] = true;

  //FDDTDD
  rgrFDDTDD->ItemIndex = 0;
  //TDDMOD
  rgrTDDMOD->ItemIndex = 0;

  //PDXCOBUF
  chbPDXCOBUF->Checked = false;
  //SLFBXCOBUF
  chbSLFBXCOBUF->Checked = true;
  //BYPXCOBUF
  chbBYPXCOBUF->Checked = false;
  //PD_DCOREF_LPFCAL
  chbPwrLpfCal->Checked = true;
  //RFLBSW_EN
  chbPwrRfLbsw->Checked = false;


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
void TfrmTop::SetGuiDecode()
{
	if(rgrDecode->ItemIndex == 0)
  {
  	//Decode
  	chbPwrTopMods->Enabled = true;

    chbPwrLpfCal->Enabled = false;
    chbPwrRfLbsw->Enabled = false;
  }
  else
  {
  	//Direct control
  	chbPwrTopMods->Enabled = false;

    chbPwrLpfCal->Enabled = true;
    chbPwrRfLbsw->Enabled = true;
  };
};

//---------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmTop::MakeData(int rAddr)
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
	m_psD.cDataW[0x04] = 0x22;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x05] |= btmp;
	//SRESET
	btmp = rgrDsmRst->ItemIndex;
	btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;
	//EN
	btmp = chbPwrTopMods->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
	//STXEN
	btmp = chbPwrSoftTx->Checked == true ? 1 : 0;
	btmp = btmp << 3; m_psD.cDataW[0x05] |= btmp;
	//SRXEN
	btmp = chbPwrSoftRx->Checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
	//TFWMODE
	btmp = rgrSpiMode->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
  m_psD.cDataW[0x06] = 0x00;
	//CLKSEL_LPFCAL
	btmp = rgrCLKSEL_LPFCAL->ItemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x06] |= btmp;
  //PD_CLKLPFCAL
  btmp = chbPD_CLKLPFCAL->Checked == true ? 1 : 0;
  btmp = btmp << 2; m_psD.cDataW[0x06] |= btmp;
  //ENF_EN_CAL
  btmp = chkLpfCalEnEnf->Checked == true ? 1 : 0;
  btmp = btmp << 1; m_psD.cDataW[0x06] |= btmp;
  //RST_CAL_LPFCAL
	btmp = chkLpfCalRst->Checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //EN_CAL_LPFCAL
  btmp = chkLpfCalEn->Checked == true ? 1 : 0;
  btmp = btmp << 7; m_psD.cDataW[0x07] |= btmp;
  //FORCE_CODE_CAL_LPFCAL[2:0]
	btmp = cmbLpfCalCode->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x07] |= btmp;
  //BWC_LPFCAL[3:0]
	btmp = cmbLpfCalBw->ItemIndex;
	m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //BBBYP_RX
  btmp = chbRxTestModeEn->Checked == true ? 1 : 0;
  btmp = btmp << 7; m_psD.cDataW[0x08] |= btmp;
  //LBEN_LPFIN_RX
  //btmp = chbBBLpf->Checked == true ? 1 : 0;
  btmp = rgrBBLB->ItemIndex == 1 ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x08] |= btmp;
  //LBEN_VGA2IN_RX
  //btmp = chbBBRxOut->Checked == true ? 1 : 0;
  btmp = rgrBBLB->ItemIndex == 2 ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x08] |= btmp;
  //LBEN_OPIN_RX
  //btmp = chbBBVga2->Checked == true ? 1 : 0;
  btmp = rgrBBLB->ItemIndex == 3 ? 1 : 0;
  btmp = btmp << 4; m_psD.cDataW[0x08] |= btmp;
  //LBRFEN_RXFE[3:0]
	btmp = rgrRFLB->ItemIndex;
	m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //RXOUTSW
	btmp = rgrRXOUTSW->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[6]
  btmp = chbSpiClkBuf->Checked[6] == true ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[5]
  btmp = chbSpiClkBuf->Checked[5] == true ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[4]
  btmp = chbSpiClkBuf->Checked[4] == true ? 1 : 0;
  btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[3]
  btmp = chbSpiClkBuf->Checked[3] == true ? 1 : 0;
  btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[2]
  btmp = chbSpiClkBuf->Checked[2] == true ? 1 : 0;
  btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[1]
  btmp = chbSpiClkBuf->Checked[1] == true ? 1 : 0;
  btmp = btmp << 1; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[0]
  btmp = chbSpiClkBuf->Checked[0] == true ? 1 : 0;
  btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

 	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
  //FDDTDD
	btmp = rgrFDDTDD->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x0A] |= btmp;
  //TDDMOD
	btmp = rgrTDDMOD->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

 	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
  //PDXCOBUF
  btmp = chbPDXCOBUF->Checked == true ? 1 : 0;
  btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
  //SLFBXCOBUF
  btmp = chbSLFBXCOBUF->Checked == true ? 1 : 0;
  btmp = btmp << 3; m_psD.cDataW[0x0B] |= btmp;
  //BYPXCOBUF
  btmp = chbBYPXCOBUF->Checked == true ? 1 : 0;
  btmp = btmp << 2; m_psD.cDataW[0x0B] |= btmp;
  //PD_DCOREF_LPFCAL
  btmp = chbPwrLpfCal->Checked == true ? 0 : 1;
  btmp = btmp << 1; m_psD.cDataW[0x0B] |= btmp;
  //RFLBSW_EN
  btmp = chbPwrRfLbsw->Checked == true ? 1 : 0;
  m_psD.cDataW[0x0B] |= btmp;

 	//======= register addr 0x0C =======
	//m_psD.cDataW[0x0C] = 0x00;

 	//======= register addr 0x0D =======
	//m_psD.cDataW[0x0D] = 0x00;

 	//======= register addr 0x0E =======
	//m_psD.cDataW[0x0E] = 0x00;

 	//======= register addr 0x0F =======
	//m_psD.cDataW[0x0F] = 0x00;


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
    case 0x03:
    case 0x04:
    case 0x05:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x05;
		break;

		case 0x20:
		case 0x21:
		case 0x06:
		case 0x07:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x06;
		break;

    case 0x0E:
		case 0x0F:
    case 0x10:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x07;
		break;

		case 0x09:
		case 0x0A:
    case 0x0D:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x08;
		break;

    case 0x11:
    case 0x22:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x09;
		break;

		case 0x23:
    case 0x24:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x0A;
		break;

		//Test mode
		case 0x12:
    case 0x15:
    case 0x25:
    case 0x26:
    case 0x27:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x05;
			m_psD.iWInd[1] = 0x0B;
		break;


		default:
			m_psD.iToW = 0;
	};
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrDecodeClick(TObject *Sender)
{
	SetGuiDecode();
  if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrDsmRstClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbPwrTopModsClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbPwrSoftTxClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };

  //1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI.
  chbSpiClkBuf->Checked[0] = chbPwrSoftTx->Checked;
  chbSpiClkBufClick(Application);
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbPwrSoftRxClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x04); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };

  //1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI.
  chbSpiClkBuf->Checked[2] = chbPwrSoftRx->Checked;
  chbSpiClkBufClick(Application);
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrSpiModeClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chkLpfCalEnEnfClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x06); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chkLpfCalRstClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x07); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbRxTestModeEnClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrBBLBClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x0A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrRFLBClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chkLpfCalEnClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::cmbLpfCalCodeChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0F); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::cmbLpfCalBwChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x10); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbSpiClkBufClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x11); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbPwrLpfCalClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x12); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::chbPwrRfLbswClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x15); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::cmbDCCalAddrChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::cmbCalValChange(TObject *Sender)
{
	//if(m_bAllowSend){ MakeData(0xF1); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmTop::rgrCLKSEL_LPFCALClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x20); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::chbPD_CLKLPFCALClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x21); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::rgrRXOUTSWClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x22); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::rgrFDDTDDClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x23); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::rgrTDDMODClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x24); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::chbPDXCOBUFClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x25); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::chbSLFBXCOBUFClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x26); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::chbBYPXCOBUFClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x27); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };  
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::btnDCRstClbrClick(TObject *Sender)
{
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
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::btnDCLoadValClick(TObject *Sender)
{
	char btmp;

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
}
//---------------------------------------------------------------------------

void __fastcall TfrmTop::btnDCStartClbrClick(TObject *Sender)
{
  StartCalibration(cmbDCCalAddr->ItemIndex);
}


//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void TfrmTop::MakeWriteAll()
{
	MakeData(0xFFFF);
	m_psD.iToW = m_psD.iLen;
  //m_psD.iToW = 0xD;
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
};        

//----------------------------------------------------------------------------
// Save the chip configuration to the file
//----------------------------------------------------------------------------
bool TfrmTop::ChipVsGui(ofstream &out, String Caption, bool bWrAll)
{
  bool bRez = true;
  bool btmp;
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
           
  if(bWrAll)
  {
  	//DC_REGVAL[5:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DC_REGVAL[5:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
  	out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    itmp = DC_REGVAL_r00_b50();
  	out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //RCCAL_LPFCAL[2:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RCCAL_LPFCAL[2:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = RCCAL_LPFCAL_r01_b75(); out << hex << showbase << uppercase;
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

    //VER[3:0]
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| VER[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = VER_r04_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;

    //REV[3:0]
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| REV[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, "Read Only");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = REV_r04_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  }


  //DECODE
  if((rgrDecode->ItemIndex != DECODE_r05_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode->ItemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  if(DECODE_r05_b77()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SRESET
  if((rgrDsmRst->ItemIndex != SRESET_r05_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| SRESET"; out.width(2); out << "|";	out.width(40);
    if(rgrDsmRst->ItemIndex == 1) strcpy(str, "Inactive"); else strcpy(str, "Reset State");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(SRESET_r05_b55()) strcpy(str, "Inactive"); else strcpy(str, "Reset State");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN
  if((chbPwrTopMods->Checked != (bool)EN_r05_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrTopMods->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(EN_r05_b44()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //STXEN
  if((chbPwrSoftTx->Checked != (bool)STXEN_r05_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| STXEN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrSoftTx->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(STXEN_r05_b33()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SRXEN
  if((chbPwrSoftRx->Checked != (bool)SRXEN_r05_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| SRXEN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrSoftRx->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(SRXEN_r05_b22()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TFWMODEA
  if((rgrSpiMode->ItemIndex != TFWMODE_r05_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| TFWMODEA"; out.width(2); out << "|";	out.width(40);
    if(rgrSpiMode->ItemIndex == 1) strcpy(str, "4 Wire"); else strcpy(str, "3 Wire");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(TFWMODE_r05_b11()) strcpy(str, "4 Wire"); else strcpy(str, "3 Wire");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLKSEL_LPFCAL
  if((rgrCLKSEL_LPFCAL->ItemIndex != CLKSEL_LPFCAL_r06_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CLKSEL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrCLKSEL_LPFCAL->Items->Strings[rgrSpiMode->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	strcpy(str, rgrCLKSEL_LPFCAL->Items->Strings[CLKSEL_LPFCAL_r06_b33()].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_CLKLPFCAL
  if((chbPD_CLKLPFCAL->Checked != (bool)PD_CLKLPFCAL_r06_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_CLKLPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chbPD_CLKLPFCAL->Checked) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(PD_CLKLPFCAL_r06_b22()) strcpy(str, "Powered Down"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ENF_EN_CAL_LPFCAL
  if((chkLpfCalEnEnf->Checked != (bool)ENF_EN_CAL_LPFCAL_r06_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| ENF_EN_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chkLpfCalEnEnf->Checked) strcpy(str, "Enforce Mode Enabled"); else strcpy(str, "Enforce Mode Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(ENF_EN_CAL_LPFCAL_r06_b11()) strcpy(str, "Enforce Mode Enabled"); else strcpy(str, "Enforce Mode Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RST_CAL_LPFCAL
  if((chkLpfCalRst->Checked != (bool)RST_CAL_LPFCAL_r06_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| RST_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chkLpfCalRst->Checked) strcpy(str, "Reset State"); else strcpy(str, "Normal State");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(RST_CAL_LPFCAL_r06_b00()) strcpy(str, "Normal State"); else strcpy(str, "Reset State");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  }; 

  //EN_CAL_LPFCAL
  if((chkLpfCalEn->Checked != (bool)EN_CAL_LPFCAL_r07_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN_CAL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    if(chkLpfCalEn->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(EN_CAL_LPFCAL_r07_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FORCE_CODE_CAL_LPFCAL[2:0]
  if((cmbLpfCalCode->ItemIndex != FORCE_CODE_CAL_LPFCAL_r07_b64()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| FORCE_CODE_CAL_LPFCAL[2:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbLpfCalCode->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	itmp = FORCE_CODE_CAL_LPFCAL_r07_b64(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BWC_LPFCAL[3:0]
  if((cmbLpfCalBw->ItemIndex != BWC_LPFCAL_r07_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BWC_LPFCAL[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbLpfCalBw->Items->Strings[cmbLpfCalBw->ItemIndex].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	itmp = BWC_LPFCAL_r07_b30();
    strcpy(str, cmbLpfCalBw->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "MHz"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BBBYP_RX
  if((chbRxTestModeEn->Checked != BBBYP_r08_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| BBBYP_RX"; out.width(2); out << "|";	out.width(40);
    if(chbRxTestModeEn->Checked) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(BBBYP_r08_b77()) strcpy(str, "Enabled"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_LPFIN_RX
  if(((rgrBBLB->ItemIndex != 1) && LBEN_LPFIN_r08_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_LPFIN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB->ItemIndex == 1) strcpy(str, "loopbbbxx connected to the LPF input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_LPFIN_r08_b66()) strcpy(str, "loopbbbxx connected to the LPF input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_VGA2IN_RX
  if(((rgrBBLB->ItemIndex != 2) && LBEN_VGA2IN_r08_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_VGA2IN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB->ItemIndex == 2) strcpy(str, "loopbbbxx connected to the VGA2 input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_VGA2IN_r08_b55()) strcpy(str, "loopbbbxx connected to the VGA2 input"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBEN_OPIN_RX
  if(((rgrBBLB->ItemIndex != 3) && LBEN_OPIN_r08_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBEN_OPIN_RX"; out.width(2); out << "|";	out.width(40);
    if(rgrBBLB->ItemIndex == 3) strcpy(str, "loopbbbxx connected to the RX output pins"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LBEN_OPIN_r08_b44()) strcpy(str, "loopbbbxx connected to the RX output pins"); else strcpy(str, "Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LBRFEN_RXFE[3:0]
  if((rgrRFLB->ItemIndex != LBRFEN_r08_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| LBRFEN_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrRFLB->Items->Strings[rgrRFLB->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = LBRFEN_r08_b30();
  	if(itmp > 3) strcpy(str, "WRONG DATA!!!"); else strcpy(str, rgrRFLB->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RXOUTSW
  if((rgrRXOUTSW->ItemIndex != RXOUTSW_r09_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CLKSEL_LPFCAL"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrRXOUTSW->Items->Strings[rgrRXOUTSW->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	strcpy(str, rgrRXOUTSW->Items->Strings[RXOUTSW_r09_b77()].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[6]
  if((chbSpiClkBuf->Checked[6] != (bool)PLLCLKOUT_r09_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[6]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[6]) strcpy(str, "PLLCLKOUT Enabled"); else strcpy(str, "PLLCLKOUT Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(PLLCLKOUT_r09_b66()) strcpy(str, "PLLCLKOUT Enabled"); else strcpy(str, "PLLCLKOUT Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[5]
  if((chbSpiClkBuf->Checked[5] != (bool)LPF_CAL_r09_b55()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[5]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[6]) strcpy(str, "LPF CALCORE Clk Enabled"); else strcpy(str, "LPF CALCORE Clk Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(LPF_CAL_r09_b55()) strcpy(str, "LPF CALCORE Clk Enabled"); else strcpy(str, "LPF CALCORE Clk Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[4]
  if((chbSpiClkBuf->Checked[4] != (bool)Rx_VGA2_DCCAL_r09_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[4]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[4]) strcpy(str, "Rx VGA2 DCCLK Enabled"); else strcpy(str, "Rx VGA2 DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_VGA2_DCCAL_r09_b44()) strcpy(str, "Rx VGA2 DCCLK Enabled"); else strcpy(str, "Rx VGA2 DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[3]
  if((chbSpiClkBuf->Checked[3] != (bool)Rx_LPF_DCCAL_r09_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[3]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[3]) strcpy(str, "Rx LPF DCCLK Enabled"); else strcpy(str, "Rx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_LPF_DCCAL_r09_b33()) strcpy(str, "Rx LPF DCCLK Enabled"); else strcpy(str, "Rx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[2]
  if((chbSpiClkBuf->Checked[2] != (bool)Rx_DSM_SPI_r09_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[2]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[2]) strcpy(str, "Rx DSM SPI Enabled"); else strcpy(str, "Rx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Rx_DSM_SPI_r09_b22()) strcpy(str, "Rx DSM SPI Enabled"); else strcpy(str, "Rx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[1]
  if((chbSpiClkBuf->Checked[1] != (bool)Tx_LPF_SPI_DCCAL_r09_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[1]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[1]) strcpy(str, "Tx LPF DCCLK Enabled"); else strcpy(str, "Tx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Tx_LPF_SPI_DCCAL_r09_b11()) strcpy(str, "Tx LPF DCCLK Enabled"); else strcpy(str, "Tx LPF DCCLK Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CLK_EN[0]
  if((chbSpiClkBuf->Checked[0] != (bool)Tx_DSM_SPI_r09_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| CLK_EN[0]"; out.width(2); out << "|";	out.width(40);
    if(chbSpiClkBuf->Checked[0]) strcpy(str, "Tx DSM SPI Enabled"); else strcpy(str, "Tx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
  	if(Tx_DSM_SPI_r09_b00()) strcpy(str, "Tx DSM SPI Enabled"); else strcpy(str, "Tx DSM SPI Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //FDDTDD
  if((rgrFDDTDD->ItemIndex != FDDTDD_r0A_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| FDDTDD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrFDDTDD->Items->Strings[rgrFDDTDD->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = FDDTDD_r0A_b11();
  	strcpy(str, rgrFDDTDD->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TDDMOD
  if((rgrTDDMOD->ItemIndex != TDDMOD_r0A_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| TDDMOD"; out.width(2); out << "|";	out.width(40);
    strcpy(str, rgrTDDMOD->Items->Strings[rgrTDDMOD->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
    itmp = TDDMOD_r0A_b00();
  	strcpy(str, rgrTDDMOD->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //PDXCOBUF
  if((chbPDXCOBUF->Checked != (bool)PDXCOBUF_r0B_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PDXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbPDXCOBUF->Checked) strcpy(str, "XCO buffer powered down"); else strcpy(str, "XCO buffer powered up");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PDXCOBUF_r0B_b44()) strcpy(str, "XCO buffer powered down"); else strcpy(str, "XCO buffer powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //SLFBXCOBUF
  if((chbSLFBXCOBUF->Checked != (bool)SLFBXCOBUF_r0B_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| SLFBXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbSLFBXCOBUF->Checked) strcpy(str, "XCO buffer self bias enabled"); else strcpy(str, "XCO buffer self bias disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(SLFBXCOBUF_r0B_b33()) strcpy(str, "XCO buffer self bias enabled"); else strcpy(str, "XCO buffer self bias disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //BYPXCOBUF
  if((chbBYPXCOBUF->Checked != (bool)BYPXCOBUF_r0B_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| BYPXCOBUF"; out.width(2); out << "|";	out.width(40);
    if(chbBYPXCOBUF->Checked) strcpy(str, "XCO buffer bypassed"); else strcpy(str, "XCO buffer active");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(BYPXCOBUF_r0B_b22()) strcpy(str, "XCO buffer bypassed"); else strcpy(str, "XCO buffer active");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD[1]
  if((chbPwrLpfCal->Checked == (bool)PD_DCOREF_LPFCAL_r0B_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD[1]"; out.width(2); out << "|";	out.width(40);
    if(chbPwrLpfCal->Checked) strcpy(str, "PD_DCOREF_LPFCAL powered up"); else strcpy(str, "PD_DCOREF_LPFCAL powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_DCOREF_LPFCAL_r0B_b11()) strcpy(str, "PD_DCOREF_LPFCAL powered down"); else strcpy(str, "PD_DCOREF_LPFCAL powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD[0]
  if((chbPwrRfLbsw->Checked != (bool)RF_LBSW_PD_r0B_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD[0]"; out.width(2); out << "|";	out.width(40);
    if(chbPwrRfLbsw->Checked) strcpy(str, "RF loop back switch powered up"); else strcpy(str, "RF loop back switch powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(RF_LBSW_PD_r0B_b00()) strcpy(str, "RF loop back switch powered up"); else strcpy(str, "RF loop back switch powered down");
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

  return bRez;
};

//----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
//----------------------------------------------------------------------------
void TfrmTop::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


	//DC_REGVAL[5:0]
  out.width(24); out << left; out << "REG 0x00 MASK 05 : 00  =";
  itmp = DC_REGVAL_r00_b50();
  out.width(6); out << right; out << itmp;
  out << "  DC_REGVAL"; out << endl;

	//RCCAL_LPFCAL[2:0]
  out.width(24); out << left; out << "REG 0x01 MASK 07 : 05  =";
  itmp = RCCAL_LPFCAL_r01_b75();
  out.width(6); out << right; out << itmp;
  out << "  RCCAL_LPFCAL"; out << endl;

  //DC_LOCK[2:0]
  out.width(24); out << left; out << "REG 0x01 MASK 04 : 02  =";
  itmp = DC_LOCK_r01_b42();
  out.width(6); out << right; out << itmp;
  out << "  DC_LOCK"; out << endl;

  //DC_CLBR_DONE
  out.width(24); out << left; out << "REG 0x01 MASK 01 : 01  =";
  itmp = DC_CLBR_DONE_r01_b11();
  out.width(6); out << right; out << itmp;
  out << "  DC_CLBR_DONE"; out << endl;

  //DC_UD
  out.width(24); out << left; out << "REG 0x01 MASK 00 : 00  =";
  itmp = DC_UD_r01_b00();
  out.width(6); out << right; out << itmp;
  out << "  DC_UD"; out << endl;

  //DC_CNTVAL[5:0]
  out.width(24); out << left; out << "REG 0x02 MASK 05 : 00  =";
  itmp = DC_CNTVAL_r02_b50();
  out.width(6); out << right; out << itmp;
  out << "  DC_CNTVAL"; out << endl;

  //DC_START_CLBR
  out.width(24); out << left; out << "REG 0x03 MASK 05 : 05  =";
  itmp = DC_START_CLBR_r03_b55();
  out.width(6); out << right; out << itmp;
  out << "  DC_START_CLBR"; out << endl;

  //DC_LOAD
  out.width(24); out << left; out << "REG 0x03 MASK 04 : 04  =";
  itmp = DC_LOAD_r03_b44();
  out.width(6); out << right; out << itmp;
  out << "  DC_LOAD"; out << endl;

  //DC_SRESET
  out.width(24); out << left; out << "REG 0x03 MASK 03 : 03  =";
  itmp = DC_SRESET_r03_b33();
  out.width(6); out << right; out << itmp;
  out << "  DC_SRESET"; out << endl;

  //DC_ADDR[2:0]
  out.width(24); out << left; out << "REG 0x03 MASK 02 : 00  =";
  itmp = DC_ADDR_r03_b20();
  out.width(6); out << right; out << itmp;
  out << "  DC_ADDR"; out << endl;

  //VER[3:0]
  out.width(24); out << left; out << "REG 0x04 MASK 07 : 04  =";
  itmp = VER_r04_b74();
  out.width(6); out << right; out << itmp;
  out << "  VER"; out << endl;

  //REV[3:0]
  out.width(24); out << left; out << "REG 0x04 MASK 03 : 00  =";
  itmp = REV_r04_b30();
  out.width(6); out << right; out << itmp;
  out << "  REV"; out << endl;

  //DECODE
  out.width(24); out << left; out << "REG 0x05 MASK 07 : 07  =";
  itmp = DECODE_r05_b77();
  out.width(6); out << right; out << itmp;
  out << "  DECODE"; out << endl;

  //SRESET
  out.width(24); out << left; out << "REG 0x05 MASK 05 : 05  =";
  itmp = SRESET_r05_b55();
  out.width(6); out << right; out << itmp;
  out << "  SRESET"; out << endl;

  //EN
  out.width(24); out << left; out << "REG 0x05 MASK 04 : 04  =";
  itmp = EN_r05_b44();
  out.width(6); out << right; out << itmp;
  out << "  EN"; out << endl;

  //STXEN
  out.width(24); out << left; out << "REG 0x05 MASK 03 : 03  =";
  itmp = STXEN_r05_b33();
  out.width(6); out << right; out << itmp;
  out << "  STXEN"; out << endl;

  //SRXEN
  out.width(24); out << left; out << "REG 0x05 MASK 02 : 02  =";
  itmp = SRXEN_r05_b22();
  out.width(6); out << right; out << itmp;
  out << "  SRXEN"; out << endl;

  //TFWMODE
  out.width(24); out << left; out << "REG 0x05 MASK 01 : 01  =";
  itmp = TFWMODE_r05_b11();
  out.width(6); out << right; out << itmp;
  out << "  TFWMODE"; out << endl;

  //CLKSEL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 03 : 03  =";
  itmp = CLKSEL_LPFCAL_r06_b33();
  out.width(6); out << right; out << itmp;
  out << "  CLKSEL_LPFCAL"; out << endl;

  //PD_CLKLPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 02 : 02  =";
  itmp = PD_CLKLPFCAL_r06_b22();
  out.width(6); out << right; out << itmp;
  out << "  PD_CLKLPFCAL"; out << endl;

  //ENF_EN_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 01 : 01  =";
  itmp = ENF_EN_CAL_LPFCAL_r06_b11();
  out.width(6); out << right; out << itmp;
  out << "  ENF_EN_CAL_LPFCAL"; out << endl;

  //RST_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x06 MASK 00 : 00  =";
  itmp = RST_CAL_LPFCAL_r06_b00();
  out.width(6); out << right; out << itmp;
  out << "  RST_CAL_LPFCAL"; out << endl;

  //EN_CAL_LPFCAL
  out.width(24); out << left; out << "REG 0x07 MASK 07 : 07  =";
  itmp = EN_CAL_LPFCAL_r07_b77();
  out.width(6); out << right; out << itmp;
  out << "  EN_CAL_LPFCAL"; out << endl;

  //FORCE_CODE_CAL_LPFCAL[2:0]
  out.width(24); out << left; out << "REG 0x07 MASK 06 : 04  =";
  itmp = FORCE_CODE_CAL_LPFCAL_r07_b64();
  out.width(6); out << right; out << itmp;
  out << "  FORCE_CODE_CAL_LPFCAL"; out << endl;

  //BWC_LPFCAL[3:0]
  out.width(24); out << left; out << "REG 0x07 MASK 03 : 00  =";
  itmp = BWC_LPFCAL_r07_b30();
  out.width(6); out << right; out << itmp;
  out << "  BWC_LPFCAL"; out << endl;

  //BBBYP_RX
  out.width(24); out << left; out << "REG 0x08 MASK 07 : 07  =";
  itmp = BBBYP_r08_b77();
  out.width(6); out << right; out << itmp;
  out << "  BBBYP_RX"; out << endl;

  //LBEN_LPFIN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 06 : 06  =";
  itmp = LBEN_LPFIN_r08_b66();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_LPFIN_RX"; out << endl;

  //LBEN_VGA2IN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 05 : 05  =";
  itmp = LBEN_VGA2IN_r08_b55();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_VGA2IN_RX"; out << endl;

  //LBEN_OPIN_RX
  out.width(24); out << left; out << "REG 0x08 MASK 04 : 04  =";
  itmp = LBEN_OPIN_r08_b44();
  out.width(6); out << right; out << itmp;
  out << "  LBEN_OPIN_RX"; out << endl;

  //LBRFEN[3:0]
  out.width(24); out << left; out << "REG 0x08 MASK 03 : 00  =";
  itmp = LBRFEN_r08_b30();
  out.width(6); out << right; out << itmp;
  out << "  LBRFEN"; out << endl;

  //RXOUTSW
  out.width(24); out << left; out << "REG 0x09 MASK 07 : 07  =";
  itmp = RXOUTSW_r09_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXOUTSW"; out << endl;

  //CLK_EN[6]
  out.width(24); out << left; out << "REG 0x09 MASK 06 : 06  =";
  itmp = PLLCLKOUT_r09_b66();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[6]"; out << endl;

  //CLK_EN[5]
  out.width(24); out << left; out << "REG 0x09 MASK 05 : 05  =";
  itmp = LPF_CAL_r09_b55();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[5]"; out << endl;

  //CLK_EN[4]
  out.width(24); out << left; out << "REG 0x09 MASK 04 : 04  =";
  itmp = Rx_VGA2_DCCAL_r09_b44();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[4]"; out << endl;

  //CLK_EN[3]
  out.width(24); out << left; out << "REG 0x09 MASK 03 : 03  =";
  itmp = Rx_LPF_DCCAL_r09_b33();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[3]"; out << endl;

  //CLK_EN[2]
  out.width(24); out << left; out << "REG 0x09 MASK 02 : 02  =";
  itmp = Rx_DSM_SPI_r09_b22();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[2]"; out << endl;

  //CLK_EN[1]
  out.width(24); out << left; out << "REG 0x09 MASK 01 : 01  =";
  itmp = Tx_LPF_SPI_DCCAL_r09_b11();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[1]"; out << endl;

  //CLK_EN[0]
  out.width(24); out << left; out << "REG 0x09 MASK 00 : 00  =";
  itmp = Tx_DSM_SPI_r09_b00();
  out.width(6); out << right; out << itmp;
  out << "  CLK_EN[0]"; out << endl;

  //FDDTDD
  out.width(24); out << left; out << "REG 0x0A MASK 01 : 01  =";
  itmp = FDDTDD_r0A_b11();
  out.width(6); out << right; out << itmp;
  out << "  FDDTDD"; out << endl;

  //TDDMOD
  out.width(24); out << left; out << "REG 0x0A MASK 00 : 00  =";
  itmp = TDDMOD_r0A_b00();
  out.width(6); out << right; out << itmp;
  out << "  TDDMOD"; out << endl;

  //PDXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 04 : 04  =";
  itmp = PDXCOBUF_r0B_b44();
  out.width(6); out << right; out << itmp;
  out << "  PDXCOBUF"; out << endl;

  //SLFBXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 03 : 03  =";
  itmp = SLFBXCOBUF_r0B_b33();
  out.width(6); out << right; out << itmp;
  out << "  SLFBXCOBUF"; out << endl;

  //BYPXCOBUF
  out.width(24); out << left; out << "REG 0x0B MASK 02 : 02  =";
  itmp = BYPXCOBUF_r0B_b22();
  out.width(6); out << right; out << itmp;
  out << "  BYPXCOBUF"; out << endl;

  //PD_DCOREF_LPFCAL
  out.width(24); out << left; out << "REG 0x0B MASK 01 : 01  =";
  itmp = PD_DCOREF_LPFCAL_r0B_b11();
  out.width(6); out << right; out << itmp;
  out << "  PD_DCOREF_LPFCAL"; out << endl;

  //RF_LBSW_PD
  out.width(24); out << left; out << "REG 0x0B MASK 00 : 00  =";
  itmp = RF_LBSW_PD_r0B_b00();
  out.width(6); out << right; out << itmp;
  out << "  RF_LBSW_PD"; out << endl;
};

//----------------------------------------------------------------------------
// Writes Register - Value format to the file
//----------------------------------------------------------------------------
void TfrmTop::MakeRVFFile(ofstream &out)
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

  //0x04 - Read Only

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xBE);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x0F);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xFF);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x03);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0x1F);
  out << iRval; out << endl;

};

//----------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//----------------------------------------------------------------------------
void TfrmTop::MakeRFIFFile(ofstream &out, char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  out << "echo \"Now programming the Lime Top modules\"" << endl << endl;

  //0x00 - Read Only

  //0x01 - Read Only

  //0x02
  //out << "# Register(s): DC_CNTVAL[5:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): DC_START_CLBR, DC_ADDR, DC_LOAD, DC_SRESET, DC_ADDR[2:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x04 - Read Only

  //0x05
  //out << "# Register(s): DECODE, SRESET, EN, STXEN, SRXEN, TFWMODE" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xBE);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): CLKSEL_LPFCAL, PD_CLKLPFCAL, ENF_EN_CAL_LPFCAL, RST_CAL_LPFCAL" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x0F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): EN_CAL_LPFCAL, FORCE_CODE_CAL_LPFCAL[2:0], BWC_LPFCAL[3:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): BBBYP, LBEN_LPFIN, LBEN_VGA2IN, LBEN_OPIN, LBRFEN[3:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): RXOUTSW, CLK_EN[6:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): FDDTDD, TDDMOD" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0x03);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): PDXCOBUF, SLFBXCOBUF, BYPXCOBUF, PD[1:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0x1F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  out << endl << "echo \"TopSPI programming complete\"" << endl << endl;
};

//---------------------------------------------------------------------------
// Sets GUI under data from chip
//---------------------------------------------------------------------------
bool TfrmTop::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;

  m_bAllowSend = false;
  
  //DC_REGVAL[5:0]
  itmp = DC_REGVAL_r00_b50();
  lbDC_REGVAL->Caption = itmp;

  //RCCAL_LPFCAL[2:0]
  itmp = RCCAL_LPFCAL_r01_b75();
  lblRCCAL_LPFCAL->Caption = itmp;

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

  //VER[3:0]
  itmp = VER_r04_b74();

  //REV[3:0]
  itmp = REV_r04_b30();

  //DECODE
  itmp = DECODE_r05_b77();
  rgrDecode->ItemIndex = itmp;

  //SRESET
  itmp = SRESET_r05_b55();
  rgrDsmRst->ItemIndex = itmp;

  //EN
  itmp = EN_r05_b44();
  chbPwrTopMods->Checked = itmp;

  //STXEN
  itmp = STXEN_r05_b33();
  chbPwrSoftTx->Checked = itmp;

  //SRXEN
  itmp = SRXEN_r05_b22();
  chbPwrSoftRx->Checked = itmp;

  //TFWMODEA
  itmp = TFWMODE_r05_b11();
  rgrSpiMode->ItemIndex = itmp;

  //CLKSEL_LPFCAL
  itmp = CLKSEL_LPFCAL_r06_b33();
  rgrCLKSEL_LPFCAL->ItemIndex = itmp;

  //PD_CLKLPFCAL
  itmp = PD_CLKLPFCAL_r06_b22();
  chbPD_CLKLPFCAL->Checked = itmp;

  //ENF_EN_CAL_LPFCAL
  itmp = ENF_EN_CAL_LPFCAL_r06_b11();
  chkLpfCalEnEnf->Checked = itmp;

  //RST_CAL_LPFCAL
  itmp = RST_CAL_LPFCAL_r06_b00();
  chkLpfCalRst->Checked = itmp;
  //chkLpfCalRst->Checked = !chkLpfCalRst->Checked;

  //EN_CAL_LPFCAL
  itmp = EN_CAL_LPFCAL_r07_b77();
  chkLpfCalEn->Checked = itmp;

  //FORCE_CODE_CAL_LPFCAL[2:0]
  itmp = FORCE_CODE_CAL_LPFCAL_r07_b64();
  cmbLpfCalCode->ItemIndex = itmp;

  //BWC_LPFCAL[3:0]
  itmp = BWC_LPFCAL_r07_b30();
  cmbLpfCalBw->ItemIndex = itmp;

  //BBBYP_RX
  itmp = BBBYP_r08_b77();
  chbRxTestModeEn->Checked = itmp;


/*
  //LBEN_LPFIN_RX
  itmp = m_psD.cDataR[0x08] & 0x40; itmp = itmp >> 6;
  rgrBBLB->ItemIndex = itmp;

  //LBEN_VGA2IN_RX
  itmp = m_psD.cDataR[0x08] & 0x20; itmp = itmp >> 5;
  rgrBBLB->ItemIndex = itmp;

  //LBEN_OPIN_RX
  itmp = m_psD.cDataR[0x08] & 0x10; itmp = itmp >> 4;
  rgrBBLB->ItemIndex = itmp;
*/

  //LBEN_LPFIN_RX
  //LBEN_VGA2IN_RX
  //LBEN_OPIN_RX
	switch(LBEN_r08_b64())
	{
		case 0x00:	itmp = 0x00;	break;
		case 0x01:	itmp = 0x03;	break;
		case 0x02:	itmp = 0x02;	break;
		case 0x04:	itmp = 0x01;	break;
		default:	itmp = 0; bRez = false;
	};
  rgrBBLB->ItemIndex = itmp;

  //LBRFEN[3:0]
  itmp = LBRFEN_r08_b30();
  if(itmp > 3) {itmp = 3; bRez = false;}
  rgrRFLB->ItemIndex = itmp;

  //RXOUTSW
  itmp = RXOUTSW_r09_b77();
  rgrRXOUTSW->ItemIndex = itmp;

  //SPI_CLK_EN [6]
  itmp = PLLCLKOUT_r09_b66();
  chbSpiClkBuf->Checked[6] = itmp;

  //SPI_CLK_EN [5]
  itmp = LPF_CAL_r09_b55();
  chbSpiClkBuf->Checked[5] = itmp;

  //SPI_CLK_EN [4]
  itmp = Rx_VGA2_DCCAL_r09_b44();
  chbSpiClkBuf->Checked[4] = itmp;

  //SPI_CLK_EN [3]
  itmp = Rx_LPF_DCCAL_r09_b33();
  chbSpiClkBuf->Checked[3] = itmp;

  //SPI_CLK_EN [2]
  itmp = Rx_DSM_SPI_r09_b22();
  chbSpiClkBuf->Checked[2] = itmp;

  //SPI_CLK_EN [1]
  itmp =Tx_LPF_SPI_DCCAL_r09_b11();
  chbSpiClkBuf->Checked[1] = itmp;

  //SPI_CLK_EN [0]
  itmp = Tx_DSM_SPI_r09_b00();
  chbSpiClkBuf->Checked[0] = itmp;

  //FDDTDD
  itmp = FDDTDD_r0A_b11();
  rgrFDDTDD->ItemIndex = itmp;

  //TDDMOD
  itmp = TDDMOD_r0A_b00();
  rgrTDDMOD->ItemIndex = itmp;

  //PDXCOBUF
  itmp = PDXCOBUF_r0B_b44();
  chbPDXCOBUF->Checked = itmp;

  //SLFBXCOBUF
  itmp = SLFBXCOBUF_r0B_b33();
  chbSLFBXCOBUF->Checked = itmp;

  //BYPXCOBUF
  itmp = BYPXCOBUF_r0B_b22();
  chbBYPXCOBUF->Checked = itmp;

  //PD[1]
  itmp = PD_DCOREF_LPFCAL_r0B_b11();
  chbPwrLpfCal->Checked = itmp;
  chbPwrLpfCal->Checked = !chbPwrLpfCal->Checked;

  //PD[0]
  itmp = RF_LBSW_PD_r0B_b00();
  chbPwrRfLbsw->Checked = itmp;
 
  m_bAllowSend = true;
  return bRez;
};

//---------------------------------------------------------------------------
void TfrmTop::UpdateFormData()
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
void TfrmTop::UpdateRCCALData()
{
	int itmp;
  String str;
  
  //RCCAL_LPFCAL[2:0]
	itmp = RCCAL_LPFCAL_r01_b75();
  lblRCCAL_LPFCAL->Caption = itmp;
};

//---------------------------------------------------------------------------
void __fastcall TfrmTop::btnDCReadValClick(TObject *Sender)
{
  MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
	SendMessage(G_hwWindow, CM_READ, 1, m_cMAddr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmTop::btnReadRCCALValClick(TObject *Sender)
{
  MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
	SendMessage(G_hwWindow, CM_READ, 2, m_cMAddr);
}
//---------------------------------------------------------------------------
void TfrmTop::SaveConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;
	pini->WriteInteger(Sect, "cmbDCCalAddr", cmbDCCalAddr->ItemIndex);
  pini->WriteInteger(Sect, "cmbCalVal", cmbCalVal->ItemIndex);
  pini->WriteInteger(Sect, "LPF_dco_CAL", GetCalVal(0x00));


  pini->WriteInteger(Sect, "rgrDecode", rgrDecode->ItemIndex);
  pini->WriteInteger(Sect, "rgrDsmRst", rgrDsmRst->ItemIndex);
  pini->WriteBool(Sect, "chbPwrTopMods", chbPwrTopMods->Checked);
  pini->WriteBool(Sect, "chbPwrSoftTx", chbPwrSoftTx->Checked);
  pini->WriteBool(Sect, "chbPwrSoftRx", chbPwrSoftRx->Checked);
  pini->WriteInteger(Sect, "rgrSpiMode", rgrSpiMode->ItemIndex);

  pini->WriteInteger(Sect, "rgrCLKSEL_LPFCAL", rgrCLKSEL_LPFCAL->ItemIndex);
  pini->WriteBool(Sect, "chbPD_CLKLPFCAL", chbPD_CLKLPFCAL->Checked);
  pini->WriteBool(Sect, "chkLpfCalEnEnf", chkLpfCalEnEnf->Checked);
  pini->WriteBool(Sect, "chkLpfCalRst", chkLpfCalRst->Checked);

  pini->WriteBool(Sect, "chkLpfCalEn", chkLpfCalEn->Checked);
  pini->WriteInteger(Sect, "cmbLpfCalCode", cmbLpfCalCode->ItemIndex);
  pini->WriteInteger(Sect, "cmbLpfCalBw", cmbLpfCalBw->ItemIndex);

  pini->WriteBool(Sect, "chbRxTestModeEn", chbRxTestModeEn->Checked);
  pini->WriteInteger(Sect, "rgrBBLB", rgrBBLB->ItemIndex);
  pini->WriteInteger(Sect, "rgrRFLB", rgrRFLB->ItemIndex);

  pini->WriteInteger(Sect, "rgrRXOUTSW", rgrRXOUTSW->ItemIndex);
  pini->WriteBool(Sect, "chbSpiClkBuf_0", chbSpiClkBuf->Checked[0]);
  pini->WriteBool(Sect, "chbSpiClkBuf_1", chbSpiClkBuf->Checked[1]);
  pini->WriteBool(Sect, "chbSpiClkBuf_2", chbSpiClkBuf->Checked[2]);
  pini->WriteBool(Sect, "chbSpiClkBuf_3", chbSpiClkBuf->Checked[3]);
  pini->WriteBool(Sect, "chbSpiClkBuf_4", chbSpiClkBuf->Checked[4]);
  pini->WriteBool(Sect, "chbSpiClkBuf_5", chbSpiClkBuf->Checked[5]);
  pini->WriteBool(Sect, "chbSpiClkBuf_6", chbSpiClkBuf->Checked[6]);

  pini->WriteInteger(Sect, "rgrFDDTDD", rgrFDDTDD->ItemIndex);
  pini->WriteInteger(Sect, "rgrTDDMOD", rgrTDDMOD->ItemIndex);

  pini->WriteBool(Sect, "chbPDXCOBUF", chbPDXCOBUF->Checked);
  pini->WriteBool(Sect, "chbSLFBXCOBUF", chbSLFBXCOBUF->Checked);
  pini->WriteBool(Sect, "chbBYPXCOBUF", chbBYPXCOBUF->Checked);
  pini->WriteBool(Sect, "chbPwrLpfCal", chbPwrLpfCal->Checked);
  pini->WriteBool(Sect, "chbPwrRfLbsw", chbPwrRfLbsw->Checked);
};

//---------------------------------------------------------------------------
void TfrmTop::ReadConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

  m_bAllowSend = false;

	cmbDCCalAddr->ItemIndex = pini->ReadInteger(Sect, "cmbDCCalAddr", 0);
  cmbCalVal->ItemIndex = pini->ReadInteger(Sect, "cmbCalVal", 31);
  m_DCClbrV[0] = pini->ReadInteger(Sect, "LPF_dco_CAL", 31);


  rgrDecode->ItemIndex = pini->ReadInteger(Sect, "rgrDecode", 0);
  rgrDsmRst->ItemIndex = pini->ReadInteger(Sect, "rgrDsmRst", 1);
  chbPwrTopMods->Checked = pini->ReadBool(Sect, "chbPwrTopMods", 1);
  chbPwrSoftTx->Checked = pini->ReadBool(Sect, "chbPwrSoftTx", 0);
  chbPwrSoftRx->Checked = pini->ReadBool(Sect, "chbPwrSoftRx", 0);
  rgrSpiMode->ItemIndex = pini->ReadInteger(Sect, "rgrSpiMode", 1);

  rgrCLKSEL_LPFCAL->ItemIndex = pini->ReadInteger(Sect, "rgrCLKSEL_LPFCAL", 1);
  chbPD_CLKLPFCAL->Checked = pini->ReadBool(Sect, "chbPD_CLKLPFCAL", 1);
  chkLpfCalEnEnf->Checked = pini->ReadBool(Sect, "chkLpfCalEnEnf", 0);
  chkLpfCalRst->Checked = pini->ReadBool(Sect, "chkLpfCalRst", 1);

  chkLpfCalEn->Checked = pini->ReadBool(Sect, "chkLpfCalEn", 0);
  cmbLpfCalCode->ItemIndex = pini->ReadInteger(Sect, "cmbLpfCalCode", 0);
  cmbLpfCalBw->ItemIndex = pini->ReadInteger(Sect, "cmbLpfCalBw", 0);

  chbRxTestModeEn->Checked = pini->ReadBool(Sect, "chbRxTestModeEn", 0);
  rgrBBLB->ItemIndex = pini->ReadInteger(Sect, "rgrBBLB", 0);
  rgrRFLB->ItemIndex = pini->ReadInteger(Sect, "rgrRFLB", 0);

  rgrRXOUTSW->ItemIndex = pini->ReadInteger(Sect, "rgrRXOUTSW", 0);
  chbSpiClkBuf->Checked[0] = pini->ReadBool(Sect, "chbSpiClkBuf_0", 0);
  chbSpiClkBuf->Checked[1] = pini->ReadBool(Sect, "chbSpiClkBuf_1", 0);
  chbSpiClkBuf->Checked[2] = pini->ReadBool(Sect, "chbSpiClkBuf_2", 0);
  chbSpiClkBuf->Checked[3] = pini->ReadBool(Sect, "chbSpiClkBuf_3", 0);
  chbSpiClkBuf->Checked[4] = pini->ReadBool(Sect, "chbSpiClkBuf_4", 0);
  chbSpiClkBuf->Checked[5] = pini->ReadBool(Sect, "chbSpiClkBuf_5", 0);
  chbSpiClkBuf->Checked[6] = pini->ReadBool(Sect, "chbSpiClkBuf_6", 1);

  rgrFDDTDD->ItemIndex = pini->ReadInteger(Sect, "rgrFDDTDD", 0);
  rgrTDDMOD->ItemIndex = pini->ReadInteger(Sect, "rgrTDDMOD", 0);

  chbPDXCOBUF->Checked = pini->ReadBool(Sect, "chbPDXCOBUF", 0);
  chbSLFBXCOBUF->Checked = pini->ReadBool(Sect, "chbSLFBXCOBUF", 1);
  chbBYPXCOBUF->Checked = pini->ReadBool(Sect, "chbBYPXCOBUF", 0);
  chbPwrLpfCal->Checked = pini->ReadBool(Sect, "chbPwrLpfCal", 1);
  chbPwrRfLbsw->Checked = pini->ReadBool(Sect, "chbPwrRfLbsw", 0);

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void __fastcall TfrmTop::swResetOn(TObject *Sender)
{
	SendMessage(G_hwWindow, CM_RSTACT, 0, m_cMAddr);
}

//---------------------------------------------------------------------------
void __fastcall TfrmTop::swResetOff(TObject *Sender)
{
        SendMessage(G_hwWindow, CM_RSTINACT, 0, m_cMAddr);
}
//---------------------------------------------------------------------------
//Enables all SPI clock buffers
//---------------------------------------------------------------------------
void TfrmTop::EnableAllSPIClocks()
{
 	//======= register addr 0x0A =======
	m_psD.cDataW[0x09] = 0x7F;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x09;

};

//---------------------------------------------------------------------------
//Enables SPI clock buffers by mask
//---------------------------------------------------------------------------
void TfrmTop::EnableSPIClocksByMask(int mask)
{
  char btmp;
  
	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //RXOUTSW
	btmp = rgrRXOUTSW->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[6]
  btmp = chbSpiClkBuf->Checked[6] == true ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[5]
  btmp = chbSpiClkBuf->Checked[5] == true ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[4]
  btmp = chbSpiClkBuf->Checked[4] == true ? 1 : 0;
  btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[3]
  btmp = chbSpiClkBuf->Checked[3] == true ? 1 : 0;
  btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[2]
  btmp = chbSpiClkBuf->Checked[2] == true ? 1 : 0;
  btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[1]
  btmp = chbSpiClkBuf->Checked[1] == true ? 1 : 0;
  btmp = btmp << 1; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[0]
  btmp = chbSpiClkBuf->Checked[0] == true ? 1 : 0;
  btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

  //Set Mask
  m_psD.cDataW[0x09] |= (char)mask;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x09;
  //SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

//---------------------------------------------------------------------------
//Restores SPI clock bufer states according to GUI settings
//---------------------------------------------------------------------------
void TfrmTop::RestoreAllSPIClocks()
{
  char btmp;
  
	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //RXOUTSW
	btmp = rgrRXOUTSW->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[6]
  btmp = chbSpiClkBuf->Checked[6] == true ? 1 : 0;
  btmp = btmp << 6; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[5]
  btmp = chbSpiClkBuf->Checked[5] == true ? 1 : 0;
  btmp = btmp << 5; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[4]
  btmp = chbSpiClkBuf->Checked[4] == true ? 1 : 0;
  btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[3]
  btmp = chbSpiClkBuf->Checked[3] == true ? 1 : 0;
  btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[2]
  btmp = chbSpiClkBuf->Checked[2] == true ? 1 : 0;
  btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[1]
  btmp = chbSpiClkBuf->Checked[1] == true ? 1 : 0;
  btmp = btmp << 1; m_psD.cDataW[0x09] |= btmp;
  //SPI_CLK_EN[0]
  btmp = chbSpiClkBuf->Checked[0] == true ? 1 : 0;
  btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x09;
  //SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

//---------------------------------------------------------------------------
// Set Soft Tx/Rx enable values
// Returns GUI setting for Tx/Rx enable
//---------------------------------------------------------------------------
bool TfrmTop::CustSet_SofTxOnOff(bool On)
{
  char btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x05] |= btmp;
	//SRESET
	btmp = rgrDsmRst->ItemIndex;
	btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;
	//EN
	btmp = chbPwrTopMods->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
	//STXEN
	btmp = On;
	btmp = btmp << 3; m_psD.cDataW[0x05] |= btmp;
	//SRXEN
	btmp = chbPwrSoftRx->Checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
	//TFWMODE
	btmp = rgrSpiMode->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x05] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x05;

  return chbPwrSoftTx->Checked;
};

bool TfrmTop::CustSet_SofRxOnOff(bool On)
{
  char btmp;
  
	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x05] |= btmp;
	//SRESET
	btmp = rgrDsmRst->ItemIndex;
	btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;
	//EN
	btmp = chbPwrTopMods->Checked == true ? 1 : 0;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
	//STXEN
	btmp = chbPwrSoftTx->Checked == true ? 1 : 0;
	btmp = btmp << 3; m_psD.cDataW[0x05] |= btmp;
	//SRXEN
	btmp = On;
	btmp = btmp << 2; m_psD.cDataW[0x05] |= btmp;
	//TFWMODE
	btmp = rgrSpiMode->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x05] |= btmp;

  m_psD.iToW = 1;
  m_psD.iWInd[0] = 0x05;

  return chbPwrSoftRx->Checked;
};

//---------------------------------------------------------------------------
// Activate start calibration command and the deactivate.
//---------------------------------------------------------------------------
void TfrmTop::StartCalibration(int Addr)
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
int TfrmTop::GetCalVal(int Addr)
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
void TfrmTop::SetCalVal(int Addr, int Val)
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
void TfrmTop::SetCalAddr(int Addr)
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
void TfrmTop::DownloadAllDCCalValues()
{
  SetCalVal(0x00, m_DCClbrV[0]);
};

//---------------------------------------------------------------------------
// Returns DC Calibration Chain status (address 0x1)
// Address of DC Calibration Chain should be settled before.
//---------------------------------------------------------------------------
char TfrmTop::GetCalStatus()
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
void TfrmTop::SetCalDefaults()
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
void TfrmTop::CustSet_Tia2OutON()
{
  m_bAllowSend = false;
  chbRxTestModeEn->Checked = true;
  m_bAllowSend = true;

  MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_Tia2OutOFF()
{
  m_bAllowSend = false;
  chbRxTestModeEn->Checked = false;
  m_bAllowSend = true;

  MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_LPFBandwidth(int ind)
{
  m_bAllowSend = false;
  cmbLpfCalBw->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x10); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_SetRFLB(int ind)
{
  m_bAllowSend = false;
  rgrRFLB->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x0D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_SetBBLB(int ind)
{
  m_bAllowSend = false;
  rgrBBLB->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x0A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_TopPowerON(bool On)
{
  m_bAllowSend = false;
  chbPwrTopMods->Checked = On;
  rgrDecode->ItemIndex = 0;
  m_bAllowSend = true;

  MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_EnableLPFCAL(bool On)
{
  m_bAllowSend = false;
  chkLpfCalEn->Checked = On;
  m_bAllowSend = true;

  MakeData(0x0E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustSet_ResetLPFCAL(bool Active)
{
  m_bAllowSend = false;
  chkLpfCalRst->Checked = Active;
  m_bAllowSend = true;

  MakeData(0x07); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmTop::CustGet_LPFCALVal(int &DCCALVal, int &LPFCALVal)
{
  MakeData(0xF0); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
	SendMessage(G_hwWindow, CM_READ, 1, m_cMAddr);

	//DC_REGVAL[5:0]
  DCCALVal = DC_REGVAL_r00_b50();

  //RCCAL_LPFCAL[2:0]
	LPFCALVal = RCCAL_LPFCAL_r01_b75();
};

int TfrmTop::GetLPFTuningClockInd()
{
  return rgrCLKSEL_LPFCAL->ItemIndex;
};

void TfrmTop::SetLPFTuningClockInd(int Ind)
{
  rgrCLKSEL_LPFCAL->ItemIndex = Ind;
  rgrCLKSEL_LPFCALClick(Application);
};

bool TfrmTop::CustGet_PD_CLKLPFCAL()
{
  return chbPD_CLKLPFCAL->Checked;
};

void TfrmTop::CustSet_PD_CLKLPFCAL(bool Val)
{
  chbPD_CLKLPFCAL->Checked = Val;
};

void TfrmTop::CustSet_rgrRXOUTSW(int Ind)
{
  rgrRXOUTSW->ItemIndex = Ind;
};

void TfrmTop::CustSet_PLLCLKOUT(bool Enabled)
{
  chbSpiClkBuf->Checked[6] = Enabled;
  chbSpiClkBufClick(Application);
};


//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void TfrmTop::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
  //for(int i=0; i<m_psD.iLen; i++)
  //for(int i=0; i<5; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  m_psD.cDataW[0x5] = m_psD.cDataW[0x5] | 0x02;
  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};



