// -----------------------------------------------------------------------------
// FILE: 		    frRxFe.cpp
// DESCRIPTION:	RxFE control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frRxFe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmRxFe *frmRxFe;

//0x0
#define                      DECODE_r00_b11() ((m_psD.cDataR[0x00] & 0x02) >> 1)
#define                          EN_r00_b00() ((m_psD.cDataR[0x00] & 0x01) >> 0)
//0x1
#define             IN1SEL_MIX_RXFE_r01_b77() ((m_psD.cDataR[0x01] & 0x80) >> 7)
#define                DCOFF_I_RXFE_r01_b60() ((m_psD.cDataR[0x01] & 0x7F) >> 0)
//0x2
#define             INLOAD_LNA_RXFE_r02_b77() ((m_psD.cDataR[0x02] & 0x80) >> 7)
#define                DCOFF_Q_RXFE_r02_b60() ((m_psD.cDataR[0x02] & 0x7F) >> 0)
//0x3
#define              XLOAD_LNA_RXFE_r03_b77() ((m_psD.cDataR[0x03] & 0x80) >> 7)
#define              IP2TRIM_I_RXFE_r03_b60() ((m_psD.cDataR[0x03] & 0x7F) >> 0)
//0x4
#define              IP2TRIM_Q_RXFE_r04_b60() ((m_psD.cDataR[0x04] & 0x7F) >> 0)
//0x5
#define                  G_LNA_RXFE_r05_b76() ((m_psD.cDataR[0x05] & 0xC0) >> 6)
#define                 LNASEL_RXFE_r05_b54() ((m_psD.cDataR[0x05] & 0x30) >> 4)
#define                CBE_LNA_RXFE_r05_b30() ((m_psD.cDataR[0x05] & 0x0F) >> 0)
//0x6
#define                RFB_TIA_RXFE_r06_b60() ((m_psD.cDataR[0x06] & 0x7F) >> 0)
//0x7
#define                CFB_TIA_RXFE_r07_b60() ((m_psD.cDataR[0x07] & 0x7F) >> 0)
//0x8
#define             RDLEXT_LNA_RXFE_r08_b50() ((m_psD.cDataR[0x08] & 0x3F) >> 0)
//0x9
#define             RDLINT_LNA_RXFE_r09_b50() ((m_psD.cDataR[0x09] & 0x3F) >> 0)
//0xA
#define                ICT_MIX_RXFE_r0A_b74() ((m_psD.cDataR[0x0A] & 0xF0) >> 4)
#define                ICT_LNA_RXFE_r0A_b30() ((m_psD.cDataR[0x0A] & 0x0F) >> 0)
//0xB
#define                ICT_TIA_RXFE_r0B_b74() ((m_psD.cDataR[0x0B] & 0xF0) >> 4)
#define              ICT_MXLOB_RXFE_r0B_b30() ((m_psD.cDataR[0x0B] & 0x0F) >> 0)
//0xC
#define               LOBN_MIX_RXFE_r0C_b63() ((m_psD.cDataR[0x0C] & 0x78) >> 3)
#define              RINEN_MIX_RXFE_r0C_b22() ((m_psD.cDataR[0x0C] & 0x04) >> 2)
#define            G_FINE_LNA3_RXFE_r0C_b10() ((m_psD.cDataR[0x0C] & 0x03) >> 0)
//0xD
#define                 PD_TIA_RXFE_r0D_b33() ((m_psD.cDataR[0x0D] & 0x08) >> 3)
#define              PD_MXLOB_RXFE2_r0D_b22() ((m_psD.cDataR[0x0D] & 0x04) >> 2)
#define                 PD_MIX_RXFE_r0D_b11() ((m_psD.cDataR[0x0D] & 0x02) >> 1)
#define                 PD_LNA_RXFE_r0D_b00() ((m_psD.cDataR[0x0D] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"

//---------------------------------------------------------------------------
__fastcall TfrmRxFe::TfrmRxFe(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfrmRxFe::~TfrmRxFe(void)
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
void TfrmRxFe::Initialize(char MAddr)
{
	m_cMAddr = MAddr;

	m_psD.iLen = RxFELen;
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
  m_psD.cTestMap[0x0] = 0x03;
  m_psD.cTestMap[0x1] = 0xFF;
  m_psD.cTestMap[0x2] = 0xFF;
  m_psD.cTestMap[0x3] = 0xFF;
  m_psD.cTestMap[0x4] = 0x7F;
  m_psD.cTestMap[0x5] = 0xFF;
  m_psD.cTestMap[0x6] = 0x7F;
  m_psD.cTestMap[0x7] = 0x7F;
  m_psD.cTestMap[0x8] = 0x3F;
  m_psD.cTestMap[0x9] = 0x3F;
  m_psD.cTestMap[0xA] = 0xFF;
  m_psD.cTestMap[0xB] = 0xFF;
  m_psD.cTestMap[0xC] = 0x7F;
  m_psD.cTestMap[0xD] = 0x0F;
  //m_psD.cTestMap[0xE] = 0xFF;
  //m_psD.cTestMap[0xF] = 0xFF;

  SetGuiDefaults();

};

//---------------------------------------------------------------------------
void TfrmRxFe::SetGuiDefaults()
{
	int itmp;
	m_bAllowSend = false;

	//DECODE
  rgrDecode->ItemIndex = 0;
  //EN
  chbPwrRxFeMods->Checked = true;

  //IN1SEL_MIX_RXFE
  cmbIN1SEL_MIX_RXFE->Clear();
  cmbIN1SEL_MIX_RXFE->Items->Add("To Pads");
  cmbIN1SEL_MIX_RXFE->Items->Add("To LNA Out");
  cmbIN1SEL_MIX_RXFE->ItemIndex = 1;

	//DCOFF_I_RXFE[6:0]
  //DCOFF_Q_RXFE[6:0]
	cmbDCOFF_I_RXFE->Clear();
  cmbDCOFF_Q_RXFE->Clear();
  for(int i=0; i<127; i++)
  {
  	cmbDCOFF_I_RXFE->Items->Add(i-63);
    cmbDCOFF_Q_RXFE->Items->Add(i-63);
  };
  cmbDCOFF_I_RXFE->ItemIndex = 63;
  cmbDCOFF_Q_RXFE->ItemIndex = 63;

  //INLOAD_LNA_RXFE
  chkINLOAD_LNA_RXFE->Checked = true;

  //XLOAD_LNA_RXFE
  chkXLOAD_LNA_RXFE->Checked = false;

	//IP2TRIM_I_RXFE[6:0]
  //IP2TRIM_Q_RXFE[6:0]
	cmbIP2TRIM_I_RXFE->Clear();
  cmbIP2TRIM_Q_RXFE->Clear();
  for(int i=0; i<127; i++)
  {
  	cmbIP2TRIM_I_RXFE->Items->Add(i-63);
    cmbIP2TRIM_Q_RXFE->Items->Add(i-63);
  };
  cmbIP2TRIM_I_RXFE->ItemIndex = 63;
  cmbIP2TRIM_Q_RXFE->ItemIndex = 63;

  //G_LNA_RXFE[1:0]
  cmbG_LNA_RXFE->Clear();
  //cmbG_LNA_RXFE->Items->Add("TBC");
  cmbG_LNA_RXFE->Items->Add("Bypass");
  cmbG_LNA_RXFE->Items->Add("Mid Gain");
  cmbG_LNA_RXFE->Items->Add("Max Gain");
  cmbG_LNA_RXFE->ItemIndex = 2;

  //LNASEL_RXFE[1:0]
  cmbLNASEL_RXFE->Clear();
  cmbLNASEL_RXFE->Items->Add("Disabled");
  cmbLNASEL_RXFE->Items->Add("LNA 1");
  cmbLNASEL_RXFE->Items->Add("LNA 2");
  cmbLNASEL_RXFE->Items->Add("LNA 3");
  cmbLNASEL_RXFE->ItemIndex = 1;

	//CBE_LNA_RXFE[3:0]
	cmbCBE_LNA_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbCBE_LNA_RXFE->Items->Add(i);
  };
  cmbCBE_LNA_RXFE->ItemIndex = 0;

	//RFB_TIA_RXFE[6:0]
	cmbRFB_TIA_RXFE->Clear();
  for(int i=0; i<128; i++)
  {
  	cmbRFB_TIA_RXFE->Items->Add(i);
  };
  cmbRFB_TIA_RXFE->ItemIndex = 120;

	//CFB_TIA_RXFE[6:0]
	cmbCFB_TIA_RXFE->Clear();
  for(int i=0; i<128; i++)
  {
  	cmbCFB_TIA_RXFE->Items->Add(i);
  };
  cmbCFB_TIA_RXFE->ItemIndex = 0;

	//RDLEXT_LNA_RXFE[6:0]
  //RDLINT_LNA_RXFE[6:0]
	cmbRDLEXT_LNA_RXFE->Clear();
  cmbRDLINT_LNA_RXFE->Clear();
  for(int i=0; i<64; i++)
  {
  	cmbRDLEXT_LNA_RXFE->Items->Add(i);
    cmbRDLINT_LNA_RXFE->Items->Add(i);
  };
  cmbRDLEXT_LNA_RXFE->ItemIndex = 28;
  cmbRDLINT_LNA_RXFE->ItemIndex = 28;

	//ICT_MIX_RXFE[3:0]
	cmbICT_MIX_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_MIX_RXFE->Items->Add(i);
  };
  cmbICT_MIX_RXFE->ItemIndex = 7;
	//ICT_LNA_RXFE[3:0]
	cmbICT_LNA_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_LNA_RXFE->Items->Add(i);
  };
  cmbICT_LNA_RXFE->ItemIndex = 7;

	//ICT_TIA_RXFE[3:0]
	cmbICT_TIA_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_TIA_RXFE->Items->Add(i);
  };
  cmbICT_TIA_RXFE->ItemIndex = 7;
	//ICT_MXLOB_RXFE[3:0]
	cmbICT_MXLOB_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbICT_MXLOB_RXFE->Items->Add(i);
  };
  cmbICT_MXLOB_RXFE->ItemIndex = 7;

	//LOBN_MIX_RXFE[3:0]
	cmbLOBN_MIX_RXFE->Clear();
  for(int i=0; i<16; i++)
  {
  	cmbLOBN_MIX_RXFE->Items->Add(i);
  };
  cmbLOBN_MIX_RXFE->ItemIndex = 3;
  //RINEN_MIX_RXFE
	chkRINEN_MIX_RXFE->Checked = false;
	//G_FINE_LNA3_RXFE[1:0]
	cmbG_FINE_LNA3_RXFE->Clear();
  cmbG_FINE_LNA3_RXFE->Items->Add("+0 dB");
  cmbG_FINE_LNA3_RXFE->Items->Add("+1 dB");
  cmbG_FINE_LNA3_RXFE->Items->Add("+2 dB");
  cmbG_FINE_LNA3_RXFE->Items->Add("+3 dB");
	cmbG_FINE_LNA3_RXFE->ItemIndex = 0;

  //PD_TIA_RXFE
  chkPD_TIA_RXFE->Checked = true;
  //PD_MXLOB_RXFE
  chkPD_MXLOB_RXFE->Checked = true;
  //PD_MIX_RXFE
  chkPD_MIX_RXFE->Checked = true;
  //PD_LNA_RXFE
  chkPD_LNA_RXFE->Checked = true;


  SetGuiDecode();

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void TfrmRxFe::SetGuiDecode()
{
	if(rgrDecode->ItemIndex == 0)
  {
  	//Decode
  	chbPwrRxFeMods->Enabled = true;

    chkPD_TIA_RXFE->Enabled = false;
    chkPD_MXLOB_RXFE->Enabled = false;
    chkPD_MIX_RXFE->Enabled = false;
    chkPD_LNA_RXFE->Enabled = false;
  }
  else
  {
  	//Direct control
  	chbPwrRxFeMods->Enabled = false;

    chkPD_TIA_RXFE->Enabled = true;
    chkPD_MXLOB_RXFE->Enabled = true;
    chkPD_MIX_RXFE->Enabled = true;
    chkPD_LNA_RXFE->Enabled = true;
  };
};

//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmRxFe::MakeData(int rAddr)
{
	char btmp;
  int itmp;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
	//DECODE
	btmp = (char)rgrDecode->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x00] |= btmp;
	//EN
	btmp = chbPwrRxFeMods->Checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x00] |= btmp;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
  //IN1SEL_MIX_RXFE
	btmp = (char)cmbIN1SEL_MIX_RXFE->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x01] |= btmp;
  //DCOFF_I_RXFE
	//btmp = (char)((cmbDCOFF_I_RXFE->ItemIndex-64)&0x7F);
  itmp = (cmbDCOFF_I_RXFE->ItemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x01] |= btmp;

	//======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
  //INLOAD_LNA_RXFE
	btmp = chkINLOAD_LNA_RXFE->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x02] |= btmp;
  //DCOFF_Q_RXFE
	//btmp = (char)((cmbDCOFF_Q_RXFE->ItemIndex-64)&0x7F);
  itmp = (cmbDCOFF_Q_RXFE->ItemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x02] |= btmp;

	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
  //XLOAD_LNA_RXFE
	btmp = chkXLOAD_LNA_RXFE->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x03] |= btmp;
  //IP2TRIM_I_RXFE
	//btmp = (char)((cmbIP2TRIM_I_RXFE->ItemIndex-64)&0x7F);
  itmp = (cmbIP2TRIM_I_RXFE->ItemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x03] |= btmp;

	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
  //IP2TRIM_Q_RXFE
	//btmp = (char)((cmbIP2TRIM_Q_RXFE->ItemIndex-64)&0x7F);
  itmp = (cmbIP2TRIM_Q_RXFE->ItemIndex-63);
  if(itmp < 0)
  {
    itmp *= -1;
    itmp |= 0x40;
  };
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
  //G_LNA_RXFE
	btmp = (char)cmbG_LNA_RXFE->ItemIndex + 1;
	btmp = btmp << 6; m_psD.cDataW[0x05] |= btmp;
  //LNASEL_RXFE
	btmp = (char)cmbLNASEL_RXFE->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x05] |= btmp;
  //CBE_LNA_RXFE
	btmp = (char)cmbCBE_LNA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
  //RFB_TIA_RXFE
	btmp = (char)cmbRFB_TIA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //CFB_TIA_RXFE
	btmp = (char)cmbCFB_TIA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //RDLEXT_LNA_RXFE
	btmp = (char)cmbRDLEXT_LNA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //RDLINT_LNA_RXFE
	btmp = (char)cmbRDLINT_LNA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
  //ICT_MIX_RXFE[3:0]
	btmp = (char)cmbICT_MIX_RXFE->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0A] |= btmp;
  //ICT_LNA_RXFE[3:0]
	btmp = (char)cmbICT_LNA_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
  //ICT_TIA_RXFE[3:0]
	btmp = (char)cmbICT_TIA_RXFE->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
  //ICT_MXLOB_RXFE[3:0]
	btmp = (char)cmbICT_MXLOB_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
  //LOBN_MIX_RXFE
	btmp = (char)cmbLOBN_MIX_RXFE->ItemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x0C] |= btmp;
  //RINEN_MIX_RXFE
	btmp = chkRINEN_MIX_RXFE->Checked == true ? 1 : 0;
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
	//G_FINE_LNA3_RXFE[1:0]
	btmp = cmbG_FINE_LNA3_RXFE->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	//======= register addr 0x0D =======
	m_psD.cDataW[0x0D] = 0x00;
  //PD_TIA_RXFE
	btmp = chkPD_TIA_RXFE->Checked == true ? 0 : 1;
	btmp = btmp << 3; m_psD.cDataW[0x0D] |= btmp;
  //PD_MXLOB_RXFE
	btmp = chkPD_MXLOB_RXFE->Checked == true ? 0 : 1;
	btmp = btmp << 2; m_psD.cDataW[0x0D] |= btmp;
  //PD_MIX_RXFE
	btmp = chkPD_MIX_RXFE->Checked == true ? 0 : 1;
	btmp = btmp << 1; m_psD.cDataW[0x0D] |= btmp;
  //PD_LNA_RXFE
	btmp = chkPD_LNA_RXFE->Checked == true ? 0 : 1;
	btmp = btmp << 0; m_psD.cDataW[0x0D] |= btmp;



	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{

		//User mode
		case 0x00:
		case 0x01:
			m_psD.iToW = 1;
			m_psD.iWInd[0] = 0x00;
		break;
    
		case 0x02:
		case 0x03:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x01;
		break;

		case 0x04:
		case 0x05:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x02;
		break;

		case 0x06:
		case 0x07:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x03;
		break;

		case 0x08:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x04;
		break;

		case 0x09:
		case 0x0A:
    case 0x0B:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x05;
		break;

    case 0x0C:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x06;
		break;

    case 0x0D:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x07;
		break;

    case 0x0E:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x08;
		break;

    case 0x0F:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x09;
		break;

		case 0x10:
    case 0x11:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0A;
		break;

		case 0x12:
    case 0x13:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0B;
		break;

		case 0x19:
		case 0x1F:
    case 0x1E:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0C;
		break;

    //Test mode
		case 0x1A:
    case 0x1B:
		case 0x1C:
    case 0x1D:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x0D;
		break;

    //Customer Mode
		case 0x80:
			m_psD.iToW = 2;
			m_psD.iWInd[0] = 0x00;
			m_psD.iWInd[1] = 0x05;
		break;

		default:
			m_psD.iToW = 0;
	};
}
void __fastcall TfrmRxFe::rgrDecodeClick(TObject *Sender)
{
	SetGuiDecode();
	if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	

}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chbPwrRxFeModsClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbIN1SEL_MIX_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbDCOFF_I_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkINLOAD_LNA_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x04); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbDCOFF_Q_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkXLOAD_LNA_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x06); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbIP2TRIM_I_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x07); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbIP2TRIM_Q_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x08); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbG_LNA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x09); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbLNASEL_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
  SendMessage(G_hwWindow, CM_UPDATELNA, 0, cmbLNASEL_RXFE->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbCBE_LNA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0B); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbRFB_TIA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbCFB_TIA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbRDLEXT_LNA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbRDLINT_LNA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x0F); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbICT_MIX_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x10); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbICT_LNA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x11); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbICT_TIA_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x12); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbICT_MXLOB_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x13); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbLOBN_MIX_RXFEChange(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x19); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkPD_TIA_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x1A); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkPD_MXLOB_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x1B); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkPD_MIX_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x1C); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };	
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::chkPD_LNA_RXFEClick(TObject *Sender)
{
	if(m_bAllowSend){ MakeData(0x1D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------
void __fastcall TfrmRxFe::cmbG_FINE_LNA3_RXFEChange(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1E); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmRxFe::chkRINEN_MIX_RXFEClick(TObject *Sender)
{
  if(m_bAllowSend){ MakeData(0x1F); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Make all data to write
//----------------------------------------------------------------------------
void TfrmRxFe::MakeWriteAll()
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
bool TfrmRxFe::ChipVsGui(ofstream &out, String Caption, bool bWrAll)
{
  bool bRez = true;
  bool btmp;
	char str[64] = "";
  int itmp, itmpC;

  out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;


  //DECODE
  if((rgrDecode->ItemIndex != DECODE_r00_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode->ItemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
  	if(DECODE_r00_b11()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN
  if((chbPwrRxFeMods->Checked != (bool)EN_r00_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbPwrRxFeMods->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
	  if(EN_r00_b00()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };


  //IN1SEL_MIX_RXFE
  if((cmbIN1SEL_MIX_RXFE->ItemIndex != IN1SEL_MIX_RXFE_r01_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IN1SEL_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbIN1SEL_MIX_RXFE->Items->Strings[cmbIN1SEL_MIX_RXFE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = IN1SEL_MIX_RXFE_r01_b77();
    strcpy(str, cmbIN1SEL_MIX_RXFE->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DCOFF_I_RXFE[6:0]
  itmpC = DCOFF_I_RXFE_r01_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
  //itmpC = (m_psD.cDataR[0x01] & 0x7F)>>0;
  //if(itmpC & 0x40) itmpC = itmpC & 0x3F;
  //else itmpC = itmpC + 64;
  if((cmbDCOFF_I_RXFE->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DCOFF_I_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbDCOFF_I_RXFE->ItemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //INLOAD_LNA_RXFE
  if((chkINLOAD_LNA_RXFE->Checked != (bool)INLOAD_LNA_RXFE_r02_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| INLOAD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkINLOAD_LNA_RXFE->Checked) strcpy(str, "Internal Load Active"); else strcpy(str, "Internal Load Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(INLOAD_LNA_RXFE_r02_b77()) strcpy(str, "Internal Load Active"); else strcpy(str, "Internal Load Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DCOFF_Q_RXFE[6:0]
  itmpC = DCOFF_Q_RXFE_r02_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x02] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbDCOFF_Q_RXFE->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DCOFF_Q_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbDCOFF_Q_RXFE->ItemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //XLOAD_LNA_RXFE
  if((chkXLOAD_LNA_RXFE->Checked != (bool)XLOAD_LNA_RXFE_r03_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| XLOAD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkXLOAD_LNA_RXFE->Checked) strcpy(str, "External Load Active"); else strcpy(str, "External Load Disabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
	  if(XLOAD_LNA_RXFE_r03_b77()) strcpy(str, "External Load Active"); else strcpy(str, "External Load Disabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //IP2TRIM_I_RXFE[6:0]
  itmpC = IP2TRIM_I_RXFE_r03_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x03] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbIP2TRIM_I_RXFE->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IP2TRIM_I_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
  	itmp = ((cmbIP2TRIM_I_RXFE->ItemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmpC;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //IP2TRIM_Q_RXFE[6:0]
  itmpC = IP2TRIM_Q_RXFE_r04_b60();
  if(itmpC & 0x40)
  {
    itmpC &= 0x3F;
    itmpC *= -1;
  };
  itmpC += 63;
//  itmpC = (m_psD.cDataR[0x04] & 0x7F)>>0;
//  if(itmpC & 0x40) itmpC = itmpC & 0x3F;
//  else itmpC = itmpC + 64;
  if((cmbIP2TRIM_Q_RXFE->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| IP2TRIM_Q_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = ((cmbIP2TRIM_Q_RXFE->ItemIndex-64)&0x7F); out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = itmpC; itmp = itmp >> 0; out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //G_LNA_RXFE[1:0]
  if(((cmbG_LNA_RXFE->ItemIndex + 1) != G_LNA_RXFE_r05_b76()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| G_LNA_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbG_LNA_RXFE->Items->Strings[cmbG_LNA_RXFE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = G_LNA_RXFE_r05_b76();
    if(itmp > 0) itmp--;
    else itmp = 0;
    //strcpy(str, cmbG_LNA_RXFE->Items->Strings[itmp-1].c_str());
    strcpy(str, cmbG_LNA_RXFE->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LNASEL_RXFE[1:0]
  if((cmbLNASEL_RXFE->ItemIndex != LNASEL_RXFE_r05_b54()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| LNASEL_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbLNASEL_RXFE->Items->Strings[cmbLNASEL_RXFE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  itmp = LNASEL_RXFE_r05_b54();
    strcpy(str, cmbLNASEL_RXFE->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CBE_LNA_RXFE[3:0]
  if((cmbCBE_LNA_RXFE->ItemIndex != CBE_LNA_RXFE_r05_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CBE_LNA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbCBE_LNA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = CBE_LNA_RXFE_r05_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RFB_TIA_RXFE[6:0]
  if((cmbRFB_TIA_RXFE->ItemIndex != RFB_TIA_RXFE_r06_b60()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RFB_TIA_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRFB_TIA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RFB_TIA_RXFE_r06_b60(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //CFB_TIA_RXFE[6:0]
  if((cmbCFB_TIA_RXFE->ItemIndex != CFB_TIA_RXFE_r07_b60()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| CFB_TIA_RXFE[6:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbCFB_TIA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = CFB_TIA_RXFE_r07_b60(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RDLEXT_LNA_RXFE[5:0]
  if((cmbRDLEXT_LNA_RXFE->ItemIndex != RDLEXT_LNA_RXFE_r08_b50()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RDLEXT_LNA_RXFE[5:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRDLEXT_LNA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RDLEXT_LNA_RXFE_r08_b50(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RDLINT_LNA_RXFE[5:0]
  if((cmbRDLINT_LNA_RXFE->ItemIndex != RDLINT_LNA_RXFE_r09_b50()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| RDLINT_LNA_RXFE[5:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbRDLINT_LNA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = RDLINT_LNA_RXFE_r09_b50(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_MIX_RXFE[3:0]
  if((cmbICT_MIX_RXFE->ItemIndex != ICT_MIX_RXFE_r0A_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_MIX_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_MIX_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_MIX_RXFE_r0A_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_LNA_RXFE[3:0]
  if((cmbICT_LNA_RXFE->ItemIndex != ICT_LNA_RXFE_r0A_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_LNA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_LNA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_LNA_RXFE_r0A_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_TIA_RXFE[3:0]
  if((cmbICT_TIA_RXFE->ItemIndex != ICT_TIA_RXFE_r0B_b74()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_TIA_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_TIA_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_TIA_RXFE_r0B_b74(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //ICT_MXLOB_RXFE[3:0]
  if((cmbICT_MXLOB_RXFE->ItemIndex != ICT_MXLOB_RXFE_r0B_b30()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ICT_MXLOB_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbICT_MXLOB_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = ICT_MXLOB_RXFE_r0B_b30(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //LOBN_MIX_RXFE[3:0]
  if((cmbLOBN_MIX_RXFE->ItemIndex != LOBN_MIX_RXFE_r0C_b63()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| LOBN_MIX_RXFE[3:0]"; out.width(2); out << "|";	out.width(40);
	  itmp = cmbLOBN_MIX_RXFE->ItemIndex; out << hex << showbase << uppercase << itmp;
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = LOBN_MIX_RXFE_r0C_b63(); out << hex << showbase << uppercase;
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RINEN_MIX_RXFE
  if((chkRINEN_MIX_RXFE->Checked != (bool)RINEN_MIX_RXFE_r0C_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| RINEN_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkRINEN_MIX_RXFE->Checked) strcpy(str, "Active"); else strcpy(str, "Inactive");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(RINEN_MIX_RXFE_r0C_b22()) strcpy(str, "Active"); else strcpy(str, "Inactive");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //G_FINE_LNA3_RXFE[1:0]
  if((cmbG_FINE_LNA3_RXFE->ItemIndex != G_FINE_LNA3_RXFE_r0C_b10()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| G_FINE_LNA3_RXFE[1:0]"; out.width(2); out << "|";	out.width(40);
    strcpy(str, cmbG_FINE_LNA3_RXFE->Items->Strings[cmbG_FINE_LNA3_RXFE->ItemIndex].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  itmp = G_FINE_LNA3_RXFE_r0C_b10();
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbG_FINE_LNA3_RXFE->Items->Strings[itmp].c_str());
    out << itmp;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
  };
  
  if((!bRez) || bWrAll)
  {
    out << "| - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - |" << endl;
  };

  //PD_TIA_RXFE
  if((chkPD_TIA_RXFE->Checked == (bool)PD_TIA_RXFE_r0D_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_TIA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkPD_TIA_RXFE->Checked) strcpy(str, "TIA powered up"); else strcpy(str, "TIA powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_TIA_RXFE_r0D_b33()) strcpy(str, "TIA powered down"); else strcpy(str, "TIA powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_MXLOB_RXFE
  if((chkPD_MXLOB_RXFE->Checked == (bool)PD_MXLOB_RXFE2_r0D_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_MXLOB_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkPD_MXLOB_RXFE->Checked) strcpy(str, "MXLOB powered up"); else strcpy(str, "MXLOB powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(PD_MXLOB_RXFE2_r0D_b22()) strcpy(str, "MXLOB powered down"); else strcpy(str, "MXLOB powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_MIX_RXFE
  if((chkPD_MIX_RXFE->Checked == (bool)PD_MIX_RXFE_r0D_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| PD_MIX_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkPD_MIX_RXFE->Checked) strcpy(str, "MIX powered up"); else strcpy(str, "MIX powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(PD_MIX_RXFE_r0D_b11()) strcpy(str, "MIX powered down"); else strcpy(str, "MIX powered up");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //PD_LNA_RXFE
  if((chkPD_LNA_RXFE->Checked == (bool)PD_LNA_RXFE_r0D_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
  	out.width(32); out << "| PD_LNA_RXFE"; out.width(2); out << "|";	out.width(40);
    if(chkPD_LNA_RXFE->Checked) strcpy(str, "LNA powered up"); else strcpy(str, "LNA powered down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
	  memset(str, '\0', sizeof(str));
  	if(PD_LNA_RXFE_r0D_b00()) strcpy(str, "LNA powered down"); else strcpy(str, "LNA powered up");
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
// Writes Register - Value format to the file.
//----------------------------------------------------------------------------
void TfrmRxFe::MakeRVFFile(ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //0x00
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0x03);
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
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x7F);
  out << iRval; out << endl;

  //0x05
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << iRval; out << endl;

  //0x06
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
  out << iRval; out << endl;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0x7F);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x7F);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x3F);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << iRval; out << endl;

  //0x0C
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0x7F);
  out << iRval; out << endl;

  //0x0D
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x7F);
  out << iRval; out << endl;

};

//----------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//----------------------------------------------------------------------------
void TfrmRxFe::MakeRFIFFile(ofstream &out, char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  out << "echo \"Now programming the Lime Rx FE\"" << endl << endl;

  //0x00
  //out << "# Register(s): DECODE, EN" << endl;
  iRval = (iAddr | (0x00 << 8)) | (m_psD.cDataR[0x00] & 0x03);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x01
  //out << "# Register(s): IN1SEL_MIX_RXFE, DCOFF_I_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x01 << 8)) | (m_psD.cDataR[0x01] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x02
  //out << "# Register(s): INLOAD_LNA_RXFE, DCOFF_Q_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x02 << 8)) | (m_psD.cDataR[0x02] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x03
  //out << "# Register(s): XLOAD_LNA_RXFE, IP2TRIM_I_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x03 << 8)) | (m_psD.cDataR[0x03] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x04
  //out << "# Register(s): IP2TRIM_Q_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x04 << 8)) | (m_psD.cDataR[0x04] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x05
  //out << "# Register(s): G_LNA_RXFE[1:0], LNASEL_RXFE[1:0], CBE_LNA_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x05 << 8)) | (m_psD.cDataR[0x05] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x06
  //out << "# Register(s): RFB_TIA_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x06 << 8)) | (m_psD.cDataR[0x06] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x07
  //out << "# Register(s): CFB_TIA_RXFE[6:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): RDLEXT_LNA_RXFE[5:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): RDLINT_LNA_RXFE[5:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x3F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): ICT_MIX_RXFE[3:0], ICT_LNA_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): ICT_TIA_RXFE[3:0], ICT_MXLOB_RXFE[3:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0C
  //out << "# Register(s): LOBN_MIX_RXFE[3:0], RINEN_MIX_RXFE, G_FINE_LNA3_RXFE[1:0]" << endl;
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0D
  //out << "# Register(s): PD_TIA_RXFE, PD_MXLOB_RXFE, PD_MIX_RXFE, PD_LNA_RXFE" << endl;
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  out << endl << "echo \"Rx FE programming complete\"" << endl << endl;

};

//---------------------------------------------------------------------------
// Sets GUI under data from chip
//---------------------------------------------------------------------------
bool TfrmRxFe::SetGUIUnderReadback()
{
  int itmp;
  bool bRez = true;

  m_bAllowSend = false;

  //DECODE
  itmp = DECODE_r00_b11();
  rgrDecode->ItemIndex = itmp;

  //EN
  itmp = EN_r00_b00();
  chbPwrRxFeMods->Checked = itmp;

  //IN1SEL_MIX_RXFE
  itmp = IN1SEL_MIX_RXFE_r01_b77();
  cmbIN1SEL_MIX_RXFE->ItemIndex = itmp;

  //DCOFF_I_RXFE[6:0]
  itmp = DCOFF_I_RXFE_r01_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x01] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbDCOFF_I_RXFE->ItemIndex = itmp;

  //INLOAD_LNA_RXFE
  itmp = INLOAD_LNA_RXFE_r02_b77();
  chkINLOAD_LNA_RXFE->Checked = itmp;

  //DCOFF_Q_RXFE[6:0]
  itmp = DCOFF_Q_RXFE_r02_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x02] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbDCOFF_Q_RXFE->ItemIndex = itmp;

  //XLOAD_LNA_RXFE
  itmp = XLOAD_LNA_RXFE_r03_b77();
  chkXLOAD_LNA_RXFE->Checked = itmp;

  //IP2TRIM_I_RXFE[6:0]
  itmp = IP2TRIM_I_RXFE_r03_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x03] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbIP2TRIM_I_RXFE->ItemIndex = itmp;

  //IP2TRIM_Q_RXFE[6:0]
  itmp = IP2TRIM_Q_RXFE_r04_b60();
  if(itmp & 0x40)
  {
    itmp &= 0x3F;
    itmp *= -1;
  };
  itmp += 63;
//  itmp = m_psD.cDataR[0x04] & 0x7F; itmp = itmp >> 0;
//  if(itmp & 0x40) itmp = itmp & 0x3F;
//  else itmp = itmp + 64;
  cmbIP2TRIM_Q_RXFE->ItemIndex = itmp;

  //G_LNA_RXFE[1:0]
  itmp = G_LNA_RXFE_r05_b76();
  if(itmp > 0) itmp--;
  else itmp = 0;
  cmbG_LNA_RXFE->ItemIndex = itmp;

  //LNASEL_RXFE[1:0]
  itmp = LNASEL_RXFE_r05_b54();
  cmbLNASEL_RXFE->ItemIndex = itmp;

  //CBE_LNA_RXFE[3:0]
  itmp = CBE_LNA_RXFE_r05_b30();
  cmbCBE_LNA_RXFE->ItemIndex = itmp;

  //RFB_TIA_RXFE[6:0]
  itmp = RFB_TIA_RXFE_r06_b60();
  cmbRFB_TIA_RXFE->ItemIndex = itmp;

  //CFB_TIA_RXFE[6:0]
  itmp = CFB_TIA_RXFE_r07_b60();
  cmbCFB_TIA_RXFE->ItemIndex = itmp;

  //RDLEXT_LNA_RXFE[5:0]
  itmp = RDLEXT_LNA_RXFE_r08_b50();
  cmbRDLEXT_LNA_RXFE->ItemIndex = itmp;

  //RDLINT_LNA_RXFE[5:0]
  itmp = RDLINT_LNA_RXFE_r09_b50();
  cmbRDLINT_LNA_RXFE->ItemIndex = itmp;

  //ICT_MIX_RXFE[3:0]
  itmp = ICT_MIX_RXFE_r0A_b74();
  cmbICT_MIX_RXFE->ItemIndex = itmp;

  //ICT_LNA_RXFE[3:0]
  itmp = ICT_LNA_RXFE_r0A_b30();
  cmbICT_LNA_RXFE->ItemIndex = itmp;

  //ICT_TIA_RXFE[3:0]
  itmp = ICT_TIA_RXFE_r0B_b74();
  cmbICT_TIA_RXFE->ItemIndex = itmp;

  //ICT_MXLOB_RXFE[3:0]
  itmp = ICT_MXLOB_RXFE_r0B_b30();
  cmbICT_MXLOB_RXFE->ItemIndex = itmp;

  //LOBN_MIX_RXFE[3:0]
  itmp = LOBN_MIX_RXFE_r0C_b63();
  cmbLOBN_MIX_RXFE->ItemIndex = itmp;

  //RINEN_MIX_RXFE
  itmp = RINEN_MIX_RXFE_r0C_b22();
  chkRINEN_MIX_RXFE->Checked = itmp;

  //G_FINE_LNA3_RXFE[1:0]
  itmp = G_FINE_LNA3_RXFE_r0C_b10();
  cmbG_FINE_LNA3_RXFE->ItemIndex = itmp;

  //PD_TIA_RXFE
  itmp = PD_TIA_RXFE_r0D_b33();
  chkPD_TIA_RXFE->Checked = itmp;
  chkPD_TIA_RXFE->Checked = !chkPD_TIA_RXFE->Checked;

  //PD_MXLOB_RXFE
  itmp = PD_MXLOB_RXFE2_r0D_b22();
  chkPD_MXLOB_RXFE->Checked = itmp;
  chkPD_MXLOB_RXFE->Checked = !chkPD_MXLOB_RXFE->Checked;

  //PD_MIX_RXFE
  itmp = PD_MIX_RXFE_r0D_b11();
  chkPD_MIX_RXFE->Checked = itmp;
  chkPD_MIX_RXFE->Checked = !chkPD_MIX_RXFE->Checked;

  //PD_LNA_RXFE
  itmp = PD_LNA_RXFE_r0D_b00();
  chkPD_LNA_RXFE->Checked = itmp;
  chkPD_LNA_RXFE->Checked = !chkPD_LNA_RXFE->Checked;


  m_bAllowSend = true;
  return bRez;
};

//----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
//----------------------------------------------------------------------------
void TfrmRxFe::MakeRegisterFile(ofstream &out)
{
  int itmp;

  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//


  //DECODE
  out.width(24); out << left; out << "REG 0x70 MASK 01 : 01  =";
  itmp = DECODE_r00_b11();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DECODE"; out << endl;

  //EN
  out.width(24); out << left; out << "REG 0x70 MASK 00 : 00  =";
  itmp = EN_r00_b00();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_EN"; out << endl;

  //IN1SEL_MIX_RXFE
  out.width(24); out << left; out << "REG 0x71 MASK 07 : 07  =";
  itmp = IN1SEL_MIX_RXFE_r01_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_INSEL_MIX"; out << endl;

  //DCOFF_I_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x71 MASK 06 : 00  =";
  itmp = DCOFF_I_RXFE_r01_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DCOFF_I"; out << endl;

  //INLOAD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x72 MASK 07 : 07  =";
  itmp = INLOAD_LNA_RXFE_r02_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_INLOAD_LNA"; out << endl;

  //DCOFF_Q_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x72 MASK 06 : 00  =";
  itmp = DCOFF_Q_RXFE_r02_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_DCIFF_Q"; out << endl;

  //XLOAD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x73 MASK 07 : 07  =";
  itmp = XLOAD_LNA_RXFE_r03_b77();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_XLOAD_LNA"; out << endl;

  //IP2TRIM_I_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x73 MASK 06 : 00  =";
  itmp = IP2TRIM_I_RXFE_r03_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_IP2TRIM_I"; out << endl;

  //IP2TRIM_Q_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x74 MASK 06 : 00  =";
  itmp = IP2TRIM_Q_RXFE_r04_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_IP2TRIM_Q"; out << endl;

  //G_LNA_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x75 MASK 07 : 06  =";
  itmp = G_LNA_RXFE_r05_b76();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_G_LNA"; out << endl;

  //LNASEL_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x75 MASK 05 : 04  =";
  itmp = LNASEL_RXFE_r05_b54();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_LNASEL"; out << endl;

  //CBE_LNA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x75 MASK 03 : 00  =";
  itmp = CBE_LNA_RXFE_r05_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_CBE_LNA"; out << endl;

  //RFB_TIA_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x76 MASK 06 : 00  =";
  itmp = RFB_TIA_RXFE_r06_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RFB_TIA"; out << endl;

  //CFB_TIA_RXFE[6:0]
  out.width(24); out << left; out << "REG 0x77 MASK 06 : 00  =";
  itmp = CFB_TIA_RXFE_r07_b60();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_CFB_TIA"; out << endl;

  //RDLEXT_LNA_RXFE[5:0]
  out.width(24); out << left; out << "REG 0x78 MASK 05 : 00  =";
  itmp = RDLEXT_LNA_RXFE_r08_b50();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RDLEXT_LNA"; out << endl;

  //RDLINT_LNA_RXFE[5:0]
  out.width(24); out << left; out << "REG 0x79 MASK 05 : 00  =";
  itmp = RDLINT_LNA_RXFE_r09_b50();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_RDL_INT_LNA"; out << endl;

  //ICT_MIX_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7A MASK 07 : 04  =";
  itmp = ICT_MIX_RXFE_r0A_b74();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_MIX"; out << endl;

  //ICT_LNA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7A MASK 03 : 00  =";
  itmp = ICT_LNA_RXFE_r0A_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_LNA"; out << endl;

  //ICT_TIA_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7B MASK 07 : 04  =";
  itmp = ICT_TIA_RXFE_r0B_b74();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_TIA"; out << endl;

  //ICT_MXLOB_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7B MASK 03 : 00  =";
  itmp = ICT_MXLOB_RXFE_r0B_b30();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_ICT_MXLOB"; out << endl;

  //LOBN_MIX_RXFE[3:0]
  out.width(24); out << left; out << "REG 0x7C MASK 06 : 03  =";
  itmp = LOBN_MIX_RXFE_r0C_b63();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_LOBN_MIX"; out << endl;

  //RINEN_MIX_RXFE
  out.width(24); out << left; out << "REG 0x7C MASK 02 : 02  =";
  itmp = RINEN_MIX_RXFE_r0C_b22();
  out.width(6); out << right; out << itmp;
  out << "  RINEN_MIX_RXFE"; out << endl;

  //G_FINE_LNA3_RXFE[1:0]
  out.width(24); out << left; out << "REG 0x7C MASK 01 : 00  =";
  itmp = G_FINE_LNA3_RXFE_r0C_b10();
  out.width(6); out << right; out << itmp;
  out << "  G_FINE_LNA3_RXFE"; out << endl;

  //PD_TIA_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 03 : 03  =";
  itmp = PD_TIA_RXFE_r0D_b33();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_TIA"; out << endl;

  //PD_MXLOB_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 02 : 02  =";
  itmp = PD_MXLOB_RXFE2_r0D_b22();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_MXLOB"; out << endl;

  //PD_MIX_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 01 : 01  =";
  itmp = PD_MIX_RXFE_r0D_b11();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_MIX"; out << endl;

  //PD_LNA_RXFE
  out.width(24); out << left; out << "REG 0x7D MASK 00 : 00  =";
  itmp = PD_LNA_RXFE_r0D_b00();
  out.width(6); out << right; out << itmp;
  out << "  RXFE_PD_LNA"; out << endl;


}


//---------------------------------------------------------------------------
void TfrmRxFe::SaveConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

	pini->WriteInteger(Sect, "rgrDecode", rgrDecode->ItemIndex);
  pini->WriteBool(Sect, "chbPwrRxFeMods", chbPwrRxFeMods->Checked);

  pini->WriteInteger(Sect, "cmbIN1SEL_MIX_RXFE", cmbIN1SEL_MIX_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbDCOFF_I_RXFE", cmbDCOFF_I_RXFE->ItemIndex);

  pini->WriteBool(Sect, "chkINLOAD_LNA_RXFE", chkINLOAD_LNA_RXFE->Checked);
  pini->WriteInteger(Sect, "cmbDCOFF_Q_RXFE", cmbDCOFF_Q_RXFE->ItemIndex);

  pini->WriteBool(Sect, "chkXLOAD_LNA_RXFE", chkXLOAD_LNA_RXFE->Checked);
  pini->WriteInteger(Sect, "cmbIP2TRIM_I_RXFE", cmbIP2TRIM_I_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbIP2TRIM_Q_RXFE", cmbIP2TRIM_Q_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbG_LNA_RXFE", cmbG_LNA_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbLNASEL_RXFE", cmbLNASEL_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbCBE_LNA_RXFE", cmbCBE_LNA_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbRFB_TIA_RXFE", cmbRFB_TIA_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbCFB_TIA_RXFE", cmbCFB_TIA_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbRDLEXT_LNA_RXFE", cmbRDLEXT_LNA_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbRDLINT_LNA_RXFE", cmbRDLINT_LNA_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbICT_MIX_RXFE", cmbICT_MIX_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbICT_LNA_RXFE", cmbICT_LNA_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbICT_TIA_RXFE", cmbICT_TIA_RXFE->ItemIndex);
  pini->WriteInteger(Sect, "cmbICT_MXLOB_RXFE", cmbICT_MXLOB_RXFE->ItemIndex);

  pini->WriteInteger(Sect, "cmbLOBN_MIX_RXFE", cmbLOBN_MIX_RXFE->ItemIndex);
  pini->WriteBool(Sect, "chkRINEN_MIX_RXFE", chkRINEN_MIX_RXFE->Checked);
  pini->WriteInteger(Sect, "cmbG_FINE_LNA3_RXFE", cmbG_FINE_LNA3_RXFE->ItemIndex);

  pini->WriteBool(Sect, "chkPD_TIA_RXFE", chkPD_TIA_RXFE->Checked);
  pini->WriteBool(Sect, "chkPD_MXLOB_RXFE", chkPD_MXLOB_RXFE->Checked);
  pini->WriteBool(Sect, "chkPD_MIX_RXFE", chkPD_MIX_RXFE->Checked);
  pini->WriteBool(Sect, "chkPD_LNA_RXFE", chkPD_LNA_RXFE->Checked);
};

//---------------------------------------------------------------------------
void TfrmRxFe::ReadConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr;

  m_bAllowSend = false;

	rgrDecode->ItemIndex = pini->ReadInteger(Sect, "rgrDecode", 0);
  chbPwrRxFeMods->Checked = pini->ReadBool(Sect, "chbPwrRxFeMods", 1);

  cmbIN1SEL_MIX_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbIN1SEL_MIX_RXFE", 1);
  cmbDCOFF_I_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbDCOFF_I_RXFE", 63);

  chkINLOAD_LNA_RXFE->Checked = pini->ReadBool(Sect, "chkINLOAD_LNA_RXFE", 1);
  cmbDCOFF_Q_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbDCOFF_Q_RXFE", 63);

  chkXLOAD_LNA_RXFE->Checked = pini->ReadBool(Sect, "chkXLOAD_LNA_RXFE", 0);
  cmbIP2TRIM_I_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbIP2TRIM_I_RXFE", 63);

  cmbIP2TRIM_Q_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbIP2TRIM_Q_RXFE", 63);

  cmbG_LNA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbG_LNA_RXFE", 2);
  cmbLNASEL_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbLNASEL_RXFE", 1);
  cmbCBE_LNA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbCBE_LNA_RXFE", 0);

  cmbRFB_TIA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbRFB_TIA_RXFE", 120);
  cmbCFB_TIA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbCFB_TIA_RXFE", 0);
  cmbRDLEXT_LNA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbRDLEXT_LNA_RXFE", 28);
  cmbRDLINT_LNA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbRDLINT_LNA_RXFE", 28);

  cmbICT_MIX_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbICT_MIX_RXFE", 7);
  cmbICT_LNA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbICT_LNA_RXFE", 7);

  cmbICT_TIA_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbICT_TIA_RXFE", 7);
  cmbICT_MXLOB_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbICT_MXLOB_RXFE", 7);

  cmbLOBN_MIX_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbLOBN_MIX_RXFE", 3);
  chkRINEN_MIX_RXFE->Checked = pini->ReadBool(Sect, "chkRINEN_MIX_RXFE", 0);
  cmbG_FINE_LNA3_RXFE->ItemIndex = pini->ReadInteger(Sect, "cmbG_FINE_LNA3_RXFE", 0);

  chkPD_TIA_RXFE->Checked = pini->ReadBool(Sect, "chkPD_TIA_RXFE", 1);
  chkPD_MXLOB_RXFE->Checked = pini->ReadBool(Sect, "chkPD_MXLOB_RXFE", 1);
  chkPD_MIX_RXFE->Checked = pini->ReadBool(Sect, "chkPD_MIX_RXFE", 1);
  chkPD_LNA_RXFE->Checked = pini->ReadBool(Sect, "chkPD_LNA_RXFE", 1);               

  SendMessage(G_hwWindow, CM_UPDATELNA, 0, cmbLNASEL_RXFE->ItemIndex); 

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void TfrmRxFe::CustSet_ActiveLNA(int ind)
{
  m_bAllowSend = false;
  cmbLNASEL_RXFE->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x80); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_LNAPowerON()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chkPD_LNA_RXFE->Checked = true;
  m_bAllowSend = true;

  MakeData(0x1D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_LNAPowerOFF()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 1;
  chkPD_LNA_RXFE->Checked = false;
  m_bAllowSend = true;

  MakeData(0x1D); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_PowerOFF()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrRxFeMods->Checked = false;
  m_bAllowSend = true;

  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_PowerON()
{
  m_bAllowSend = false;
  rgrDecode->ItemIndex = 0;
  chbPwrRxFeMods->Checked = true;
  m_bAllowSend = true;

  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_DCOffsetCancellationI(int ind)
{
  m_bAllowSend = false;
  cmbDCOFF_I_RXFE->ItemIndex = ind;
  m_bAllowSend = true;
  
  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

void TfrmRxFe::CustSet_DCOffsetCancellationQ(int ind)
{
  m_bAllowSend = false;
  cmbDCOFF_Q_RXFE->ItemIndex = ind;
  m_bAllowSend = true;

  MakeData(0x05); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

int TfrmRxFe::CustGet_DCOffsetCancellationI()
{
  return cmbDCOFF_I_RXFE->ItemIndex;
};

int TfrmRxFe::CustGet_DCOffsetCancellationQ()
{
  return cmbDCOFF_Q_RXFE->ItemIndex;
};

void TfrmRxFe::CustSet_cmbRDLINT_LNA_RXFE(int Ind)
{
  cmbRDLINT_LNA_RXFE->ItemIndex = Ind;
  cmbRDLINT_LNA_RXFEChange(Application);
};

//---------------------------------------------------------------------------
// Functions for register testing
//---------------------------------------------------------------------------
void TfrmRxFe::RT_SetTestMask(char Mask)
{
  MakeWriteAll();

	for(int i=0; i<m_psD.iToW; i++)
	{
    m_psD.cDataW[m_psD.iWInd[i]] = Mask & m_psD.cTestMap[m_psD.iWInd[i]];
  };

  SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
};

