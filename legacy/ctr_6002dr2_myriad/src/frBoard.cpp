// -----------------------------------------------------------------------------
// FILE: 		    frBoard.cpp
// DESCRIPTION:	Test board control interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frBoard.h"
#include <math.h>
#include "dgRFIFParam.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSpin"
#pragma resource "*.dfm"
//TfrmBoard *frmBoard;


#define FRIF_DIR_W "./rfIf Direct=24,"


//---------------------------------------------------------------------------
__fastcall TfrmBoard::TfrmBoard(TComponent* Owner)
  : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfrmBoard::~TfrmBoard(void)
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
void TfrmBoard::Initialize(char MAddr)
{
	m_cMAddr = MAddr;

	m_psD.iLen = BoardLen;
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
  m_psD.cTestMap[0x2] = 0x00;
  m_psD.cTestMap[0x3] = 0x00;
  m_psD.cTestMap[0x4] = 0x00;
  m_psD.cTestMap[0x5] = 0x00;
  m_psD.cTestMap[0x6] = 0x00;
  m_psD.cTestMap[0x7] = 0x00;
  m_psD.cTestMap[0x8] = 0x00;
  m_psD.cTestMap[0x9] = 0x00;
  m_psD.cTestMap[0xA] = 0x00;
  m_psD.cTestMap[0xB] = 0x00;
  //m_psD.cTestMap[0xC] = 0xFF;
  //m_psD.cTestMap[0xD] = 0xFF;
  //m_psD.cTestMap[0xE] = 0xFF;
  //m_psD.cTestMap[0xF] = 0xFF;

  SetGuiDefaults();

};

//---------------------------------------------------------------------------
void TfrmBoard::SetGuiDefaults()
{
	int itmp;
	m_bAllowSend = false;

  //Reference Counter Latch
  cmbLDP->ItemIndex = 0;
  cmbABW->ItemIndex = 0;
  txtRCnt->Value = 125;

  //N Counter Latch 
  cmbCPG->ItemIndex = 0;
  txtNCnt->Value = 384;

  //Function Latch
  rgrPD2_f->ItemIndex = 0;
  cmbCS2_f->ItemIndex = 7;
  cmbCS1_f->ItemIndex = 7;
  cmbTC_f->ItemIndex = 0;
  cmbFL_f->ItemIndex = 0;
  rgrCPS_f->ItemIndex = 0;
  rgrPDP_f->ItemIndex = 1;
  cmbMOC_f->ItemIndex = 1;
  rgrPD1_f->ItemIndex = 0;
  rgrCR_f->ItemIndex = 0;

  //Initialization Latch
  rgrPD2_i->ItemIndex = 0;
  cmbCS2_i->ItemIndex = 7;
  cmbCS1_i->ItemIndex = 7;
  cmbTC_i->ItemIndex = 0;
  cmbFL_i->ItemIndex = 0;
  rgrCPS_i->ItemIndex = 0;
  rgrPDP_i->ItemIndex = 1;
  cmbMOC_i->ItemIndex = 1;
  rgrPD1_i->ItemIndex = 0;
  rgrCR_i->ItemIndex = 0;

  //SetGuiDecode();
  CalculateRN();

  m_bAllowSend = true;
}

//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmBoard::MakeData(int rAddr)
{
	char btmp;
  unsigned int itmp;

	//======= register addr 0x00 =======
	m_psD.cDataW[0x00] = 0x00;
	//R Value LSB
	itmp = txtRCnt->Value;
  btmp = (char)itmp;
	btmp = btmp << 2; m_psD.cDataW[0x00] |= btmp;
	//Addr
	btmp = 0x00;
	btmp = btmp << 0; m_psD.cDataW[0x00] |= btmp;

	//======= register addr 0x01 =======
	m_psD.cDataW[0x01] = 0x00;
  //R Value MSB
  btmp = (char)(itmp >> 6);
	btmp = btmp << 0; m_psD.cDataW[0x01] |= btmp;

	//======= register addr 0x02 =======
	m_psD.cDataW[0x02] = 0x00;
  //Anti-Backlash
  btmp = (char)cmbABW->ItemIndex;
  if(btmp > 0) btmp++;
	btmp = btmp << 0; m_psD.cDataW[0x02] |= btmp;
  //Lock Detact Precision
  btmp = (char)cmbLDP->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x02] |= btmp;



	//======= register addr 0x03 =======
	m_psD.cDataW[0x03] = 0x00;
	//Addr
	btmp = 0x01;
	btmp = btmp << 0; m_psD.cDataW[0x03] |= btmp;

	//======= register addr 0x04 =======
	m_psD.cDataW[0x04] = 0x00;
	//N Value LSB
	itmp = txtNCnt->Value;
  btmp = (char)itmp;
	btmp = btmp << 0; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	m_psD.cDataW[0x05] = 0x00;
	//N Value MSB
	itmp = txtNCnt->Value;
  btmp = (char)(itmp >> 8);
	btmp = btmp << 0; m_psD.cDataW[0x05] |= btmp;
  //CP Gain
  btmp = (char)cmbCPG->ItemIndex;
  btmp = btmp << 5; m_psD.cDataW[0x05] |= btmp;




	//======= register addr 0x06 =======
	m_psD.cDataW[0x06] = 0x00;
	//Addr
	btmp = 0x02;
	btmp = btmp << 0; m_psD.cDataW[0x06] |= btmp;
  //Counter Reset
  btmp = (char)rgrCR_f->ItemIndex;
  btmp = btmp << 2; m_psD.cDataW[0x06] |= btmp;
  //PD 1
  btmp = (char)rgrPD1_f->ItemIndex;
  btmp = btmp << 3; m_psD.cDataW[0x06] |= btmp;
  //Muxout Control
  btmp = (char)cmbMOC_f->ItemIndex;
  btmp = btmp << 4; m_psD.cDataW[0x06] |= btmp;
  //PD Polarity 
  btmp = (char)rgrPDP_f->ItemIndex;
  btmp = btmp << 7; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //CP State 
  btmp = (char)rgrCPS_f->ItemIndex;
  btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;
  //Fastlock
  btmp = (char)cmbFL_f->ItemIndex;
  if(btmp > 0) btmp++;
  btmp = btmp << 1; m_psD.cDataW[0x07] |= btmp;
  //Timer Counter
  btmp = (char)cmbTC_f->ItemIndex;
  btmp = btmp << 3; m_psD.cDataW[0x07] |= btmp;
  //Current Setting 1 MSB
  btmp = (char)cmbCS1_f->ItemIndex;
  btmp = btmp << 7; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //Current Setting 1 LSB
  btmp = (char)cmbCS1_f->ItemIndex;
  btmp = btmp >> 1; m_psD.cDataW[0x08] |= btmp;
  //Current Setting 2
  btmp = (char)cmbCS2_f->ItemIndex;
  btmp = btmp << 2; m_psD.cDataW[0x08] |= btmp;
  //PD 2
  btmp = (char)rgrPD2_f->ItemIndex;
  btmp = btmp << 5; m_psD.cDataW[0x08] |= btmp;



	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
	//Addr
	btmp = 0x03;
	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;
  //Counter Reset
  btmp = (char)rgrCR_i->ItemIndex;
  btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
  //PD 1
  btmp = (char)rgrPD1_i->ItemIndex;
  btmp = btmp << 3; m_psD.cDataW[0x09] |= btmp;
  //Muxout Control
  btmp = (char)cmbMOC_i->ItemIndex;
  btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
  //PD Polarity 
  btmp = (char)rgrPDP_i->ItemIndex;
  btmp = btmp << 7; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
  //CP State 
  btmp = (char)rgrCPS_i->ItemIndex;
  btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;
  //Fastlock
  btmp = (char)cmbFL_i->ItemIndex;
  if(btmp > 0) btmp++;
  btmp = btmp << 1; m_psD.cDataW[0x0A] |= btmp;
  //Timer Counter
  btmp = (char)cmbTC_i->ItemIndex;
  btmp = btmp << 3; m_psD.cDataW[0x0A] |= btmp;
  //Current Setting 1 MSB
  btmp = (char)cmbCS1_i->ItemIndex;
  btmp = btmp << 7; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
  //Current Setting 1 LSB
  btmp = (char)cmbCS1_i->ItemIndex;
  btmp = btmp >> 1; m_psD.cDataW[0x0B] |= btmp;
  //Current Setting 2
  btmp = (char)cmbCS2_i->ItemIndex;
  btmp = btmp << 2; m_psD.cDataW[0x0B] |= btmp;
  //PD 2
  btmp = (char)rgrPD2_i->ItemIndex;
  btmp = btmp << 5; m_psD.cDataW[0x0B] |= btmp;


	memset(m_psD.iWInd, 0, m_psD.iLen*sizeof(int));
	switch(rAddr)
	{
		case 0x00:
			m_psD.iToW = 3;
			m_psD.iWInd[0] = 0x02;
      m_psD.iWInd[1] = 0x01;
      m_psD.iWInd[2] = 0x00;
		break;

		case 0x01:
			m_psD.iToW = 3;
			m_psD.iWInd[0] = 0x05;
      m_psD.iWInd[1] = 0x04;
      m_psD.iWInd[2] = 0x03;
		break;

		case 0x02:
			m_psD.iToW = 3;
			m_psD.iWInd[0] = 0x08;
      m_psD.iWInd[1] = 0x07;
      m_psD.iWInd[2] = 0x06;
		break;

		case 0x03:
			m_psD.iToW = 3;
			m_psD.iWInd[0] = 0x0B;
      m_psD.iWInd[1] = 0x0A;
      m_psD.iWInd[2] = 0x09;
		break;

		default:
			m_psD.iToW = 0;
	};

}

//----------------------------------------------------------------------------
void TfrmBoard::CalculateRN()
{
  double x = txtFref->Value*1000000;
  double y = txtFvco->Value*1000000;
  double Fcomp;
  while((x!=0) && (y!=0))
  {
    if(x >= y)
    {
      x = fmod(x, y);
    }
    else
    {
      y = fmod(y, x);
    };
  };

  Fcomp = (x + y)/1000000.0;
  double R = ((double)txtFref->Value/Fcomp)+0.5;
  double N = ((double)txtFvco->Value/Fcomp)+0.5;

  txtRCnt->Value = (int)R;
  txtNCnt->Value = (int)N;
  lblFcomp->Caption = Fcomp;
  double dFvco;
  if(txtRCnt->Value != 0) dFvco = txtNCnt->Value * (txtFref->Value)/txtRCnt->Value;
  lblFvco->Caption = dFvco;
};

//----------------------------------------------------------------------------
void __fastcall TfrmBoard::btnCalcClick(TObject *Sender)
{
  m_bAllowSend = false;
  CalculateRN();
  m_bAllowSend = true;

  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);

/*
  double step = 10.0;
  double d = 1000000.0;
  double Fcomp;
  double m1d;
  int m1i, m2i, x;

  x = 1;
  while(x != 0)
  {
    m1d = fmod(txtFref->Value * 1000000.0, d);
    m1i = (int)m1d;
    m2i = (int)(txtFvco->Value * 1000000.0)/d;
    x = m1i + m2i;
    d = d - step;
    if(d<0) x = 0;
  };
  Fcomp = d/1000000.0;
  double R = txtFref->Value/Fcomp;
  double N = txtFvco->Value/Fcomp;
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmBoard::txtRCntChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbABWChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbLDPChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::txtNCntChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbCPGChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrCR_fClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrCPS_fClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPD1_fClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPD2_fClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbMOC_fChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPDP_fClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbTC_fChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbFL_fChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbCS1_fChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbCS2_fChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrCR_iClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrCPS_iClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPD1_iClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPD2_iClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbMOC_iChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::rgrPDP_iClick(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbTC_iChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbFL_iChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbCS1_iChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::cmbCS2_iChange(TObject *Sender)
{
  //if(m_bAllowSend){ MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr); };
}
//---------------------------------------------------------------------------


void __fastcall TfrmBoard::btnDownloadClick(TObject *Sender)
{
  MakeData(0x03); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x02); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x00); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
  MakeData(0x01); SendMessage(G_hwWindow, CM_AUTODOWNLOAD, 0, m_cMAddr);
}
//---------------------------------------------------------------------------

void TfrmBoard::UpdateADFFvco()
{

};
void __fastcall TfrmBoard::txtFrefChange(TObject *Sender)
{
  CalculateRN();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::txtFvcoChange(TObject *Sender)
{
   CalculateRN();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard::btnSaveRFIFClick(TObject *Sender)
{

	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";
	ofstream outf;

  String ValStr;
  TdlgRFIFParam *dlgRFIFParam;

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);

  dlgSave->DefaultExt = "sh";
  dlgSave->FileName = "*.sh";
  dlgSave->Filter = "sh files (*.sh)|*.sh";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;


  dlgRFIFParam = new TdlgRFIFParam(Application);
  if(dlgRFIFParam->ShowModal() == mrOk)
  {
    if(dlgSave->Execute())
    {
      ValStr = dlgRFIFParam->txtValue->Text;
      outf.open(dlgSave->FileName.c_str(), ios::out);
      MakeRFIFFile(outf, ValStr.c_str());
      outf.close();
    };
  };
  delete dlgRFIFParam;
}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//----------------------------------------------------------------------------
void TfrmBoard::MakeRFIFFile(ofstream &out, char *FRIF_SPI_A)
{
  //Reference Counter Latch
  //N Counter Latch
  //Function Latch
  //Initialization Latch

  int iRval;

  out << "#!/bin/bash" << endl;
  out << "echo \"Setting up ADF4002\"" << endl << endl;
  out << "ADF4002_CS=" << FRIF_SPI_A << endl << endl;
  out << "echo" << endl << endl;


  //*** To create file from GUI data instead of chip registers data. Start ***//
  MakeData(0xFF);
  memcpy(m_psD.cDataR, m_psD.cDataW, m_psD.iLen);
  //***  To create file from GUI data instead of chip registers data. End  ***//

  //ADF4002 Address 0x3
  out << "echo \"Initialization Latch\"" << endl;
  out << FRIF_DIR_W;
  out << "0x" << hex << uppercase << noshowbase;
  iRval = m_psD.cDataR[0x0B] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x0A] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x09] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  out << ",$ADF4002_CS"; out << endl;
  out << endl;

  //ADF4002 Function Latch
  out << "echo \"Function Latch\"" << endl;
  out << FRIF_DIR_W;
  out << "0x" << hex << uppercase << noshowbase;
  iRval = m_psD.cDataR[0x08] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x07] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x06] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  out << ",$ADF4002_CS"; out << endl;
  out << endl;

  //ADF4002 Reference Counter Latch
  out << "echo \"Reference Counter Latch\"" << endl;
  out << FRIF_DIR_W;
  out << "0x" << hex << uppercase << noshowbase;
  iRval = m_psD.cDataR[0x02] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x01] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x00] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  out << ",$ADF4002_CS"; out << endl;
  out << endl;

  //ADF4002 N Counter Latch
  out << "echo \"N Counter Latch\"" << endl;
  out << FRIF_DIR_W;
  out << "0x" << hex << uppercase << noshowbase;
  iRval = m_psD.cDataR[0x05] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x04] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  iRval = m_psD.cDataR[0x03] & 0x0FF;
  if(iRval < 15) out << "0";
  out << iRval;
  out << ",$ADF4002_CS"; out << endl;

};
