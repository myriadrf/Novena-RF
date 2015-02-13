// -----------------------------------------------------------------------------
// FILE: 		    frMain.cpp
// DESCRIPTION:	Integrates all GUI forms
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------


//---------------------------------------------------------------------
#include <vcl.h>
#include <iostream>
#include <fstream>
using namespace std;
#pragma hdrstop

#include "frMain.h"
#include "About.h"
#include <dir.h>
#include "dgRefClk.h"
#include "dlgRegTest.h"
#include <Registry.hpp>
#include "dlgSerPort.h"

#include <Dbt.h>
#include "dgRFIFParam.h"


//---------------------------------------------------------------------
#pragma link "frCustomer"
#pragma link "frADDC"
#pragma link "frTxRf"
#pragma link "frBoard"
#pragma resource "*.dfm"

TfrmMain *frmMain;

//---------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent *AOwner)
	: TForm(AOwner)
{
	G_hwWindow = this->Handle;

  //dPortMaster = new TdPortMaster(Application);
  dSerPort = new TdSerPort(Application);
  if(!dSerPort->PortOpened())
  {
    tbtnDownload->Enabled = false;
    //slLogMesg(14);
  }
  else
  {
    tbtnDownload->Enabled = true;
    //slLogMesg(13);
  };

  m_iRefVCnt = 3;
  m_dFVco1 = new double[m_iRefVCnt];
  m_dFVco2 = new double[m_iRefVCnt];
  m_dFVco3 = new double[m_iRefVCnt];
  m_dFVco4 = new double[m_iRefVCnt];
  m_iCVco1 = new int[m_iRefVCnt];
  m_iCVco2 = new int[m_iRefVCnt];
  m_iCVco3 = new int[m_iRefVCnt];
  m_iCVco4 = new int[m_iRefVCnt];
  memset(m_dFVco1, 0, sizeof(double)*m_iRefVCnt);
  memset(m_dFVco2, 0, sizeof(double)*m_iRefVCnt);
  memset(m_dFVco3, 0, sizeof(double)*m_iRefVCnt);
  memset(m_dFVco4, 0, sizeof(double)*m_iRefVCnt);

  //For interprocess communication
	m_sInterPD.iLen = 1;
	m_sInterPD.cCmdW = new char[m_sInterPD.iLen];
	m_sInterPD.cDataW = new char[m_sInterPD.iLen];
	m_sInterPD.cCmdR = new char[m_sInterPD.iLen];
	m_sInterPD.cDataR = new char[m_sInterPD.iLen];
	m_sInterPD.iRInd = new int[m_sInterPD.iLen];
	m_sInterPD.iWInd = new int[m_sInterPD.iLen];
	memset(m_sInterPD.cCmdW, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cDataW, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cCmdR, 0, m_sInterPD.iLen);
	memset(m_sInterPD.cDataR, 0, m_sInterPD.iLen);
	memset(m_sInterPD.iRInd, 0, m_sInterPD.iLen*sizeof(int));
	memset(m_sInterPD.iWInd, 0, m_sInterPD.iLen*sizeof(int));
	m_sInterPD.iToR = m_sInterPD.iLen;
	m_sInterPD.iToW = m_sInterPD.iLen;

  //sbMain->Panels->Items[1]->Text = " Automatic Download Mode";
  //sbMain->Panels->Items[2]->Text = " Ref. Clock, Hz: 40000000";
  //ShowReferenceClk(40000000);
  ShowReferenceClk(30720000);
	//tvTree->Items[1]->Item->Expanded = true;

  m_sBypCurr = 0;
  m_sBypPrev = -1;
  m_sBBCurr = 0;
  m_sBBPrev = -1;

}

//---------------------------------------------------------------------
void __fastcall TfrmMain::FileNew1Execute(TObject *Sender)
{
	setCurrentFileName("untitled.prj");

	m_frmTop->SetGuiDefaults();
	m_frmTxLpf->SetGuiDefaults();
	m_frmRxLpf->SetGuiDefaults();
  m_frmTxRf->SetGuiDefaults();
  m_frmRxVga2->SetGuiDefaults();
  m_frmRxFe->SetGuiDefaults();
  m_frmTxPLL->SetGuiDefaults();
  m_frmRxPLL->SetGuiDefaults();
  m_frmADDC->SetGuiDefaults();
  m_frmBoard->SetGuiDefaults();

          slLogMesg(1);
       
}

//---------------------------------------------------------------------------
bool TfrmMain::FileIsNotEmpty(String filename)
{
   long curpos, length;
   FILE *stream;

   stream = fopen(filename.c_str(), "r");

   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fclose(stream);

   return (length > 0);
}

//---------------------------------------------------------------------------
void TfrmMain::LoadConfiguration(String sIniName)
{
  TIniFile *ini;
  ini = new TIniFile(sIniName); // we will serialize the data from the file

  //m_TxUARFCNDef.ReadConf(ini);
  //m_RxUARFCNDef.ReadConf(ini);
  m_UARFCNDef.ReadConf(ini);
	m_frmTop->ReadConf(ini);
	m_frmTxLpf->ReadConf(ini);
	m_frmRxLpf->ReadConf(ini);
  m_frmTxRf->ReadConf(ini);
  m_frmRxVga2->ReadConf(ini);
  m_frmRxFe->ReadConf(ini);
  m_frmTxPLL->ReadConf(ini);
  m_frmRxPLL->ReadConf(ini);
  m_frmADDC->ReadConf(ini);

  ShowReferenceClk(m_frmTxPLL->GetRefClk());

  delete ini;
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FileOpen1Execute(TObject *Sender)
{
	TIniFile *ini;
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);

#ifdef CUSTOMER_MODE
  mnuRegTestLong->Visible = false;
#endif

  dlgOpen->DefaultExt = "prj";
  //dlgOpen->FileName = "*.prj";
  dlgOpen->Filter = "Project-Files (*.prj)|*.prj";
  //*DLG dlgOpen->InitialDir = drive;
  //*DLG dlgOpen->InitialDir = dlgOpen->InitialDir + dir;
  if(dlgOpen->Execute())
  {
#ifdef CUSTOMER_MODE

    if(!FileIsNotEmpty(dlgOpen->FileName))
    {
      ShowMessage("Configuration file is corrupt.\n\n\
        Contact Lime Microsystems\n\
        Unit 57 Surrey Tech Centre Occam Road\n\
        The Surrey Research Park Guildford Surrey\n\
        GU2 7YG\n\n\
        Tel: +44 (0)1483 684801, +44(0)142 8653335\n\
        Fax: +44(0) 1428656662\n\n\
        info@limemicro.com");
      return;
    };
#endif
  	setCurrentFileName(dlgOpen->FileName);

    LoadConfiguration(m_sFileName);

    slLogMesg(0);

    tbtnDownload->Click();
	};       
}

//---------------------------------------------------------------------------
void TfrmMain::EnableAllSPIClocks()
{
  //Enable all SPI clocks in TopSPI
  m_frmTop->EnableAllSPIClocks();
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);
};

//---------------------------------------------------------------------------
void TfrmMain::RestoreAllSPIClocks()
{
  //Enable all SPI clocks in TopSPI
  m_frmTop->RestoreAllSPIClocks();
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::tbtnDownloadClick(TObject *Sender)
{
  //==== Perform Global Reset First ===
  dSerPort->SPI_Rst();
  Sleep(5);
  //===================================

	tbtnDownload->Enabled = false;
	m_frmTop->MakeWriteAll();
  m_frmTxLpf->MakeWriteAll();
  m_frmRxLpf->MakeWriteAll();
  m_frmTxRf->MakeWriteAll();
  m_frmRxVga2->MakeWriteAll();
  m_frmRxFe->MakeWriteAll();
  m_frmTxPLL->MakeWriteAll();
  m_frmRxPLL->MakeWriteAll();

  //Enable all SPI clocks in TopSPI
  //EnableAllSPIClocks();

  //TxLpf
	dSerPort->SPI_Wr(m_frmTxLpf->GetPrData());
  m_frmTxLpf->DownloadAllDCCalValues();
  Sleep(5);

  //RxLpf
	dSerPort->SPI_Wr(m_frmRxLpf->GetPrData());
  m_frmRxLpf->DownloadAllDCCalValues();
  Sleep(5);

  //TxRf
  dSerPort->SPI_Wr(m_frmTxRf->GetPrData());
  Sleep(5);

  //RxVga2
  dSerPort->SPI_Wr(m_frmRxVga2->GetPrData());
  m_frmRxVga2->DownloadAllDCCalValues();
  Sleep(5);
  
  //RxFe
  dSerPort->SPI_Wr(m_frmRxFe->GetPrData());
  Sleep(5);

  //TxPLL
  dSerPort->SPI_Wr(m_frmTxPLL->GetPrData());
  Sleep(5);

  //RxPLL
  dSerPort->SPI_Wr(m_frmRxPLL->GetPrData());
  Sleep(5);

  //Top
  m_frmTop->MakeWriteAll();
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);

#ifdef CUSTOMER_MODE
  m_frmTxPLL->btnCalc->Click();
  m_frmRxPLL->btnCalc->Click();
#endif

	tbtnDownload->Enabled = true;
	slLogMesg(5);
  
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::Save(TObject *Sender)
{
	TIniFile *ini;
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
  dlgSave->DefaultExt = "prj";
  dlgSave->FileName = "*.prj";
  dlgSave->Filter = "Project-Files (*.prj)|*.prj";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;

  if(m_sFileName == "untitled.prj")
  {
  	FileSaveAsItemClick(Application);
  }
  else
  {
    	ini = new TIniFile(m_sFileName);   // we will serialize the data into the file

      m_UARFCNDef.SaveConf(ini);
			m_frmTop->SaveConf(ini);
			m_frmTxLpf->SaveConf(ini);
			m_frmRxLpf->SaveConf(ini);
      m_frmTxRf->SaveConf(ini);
      m_frmRxVga2->SaveConf(ini);
      m_frmRxFe->SaveConf(ini);
	    m_frmTxPLL->SaveConf(ini);
  	  m_frmRxPLL->SaveConf(ini);
      m_frmADDC->SaveConf(ini);

			slLogMesg(3);
      delete ini;
  };
        
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FileExit1Execute(TObject *Sender)
{
  Close();        
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::HelpAbout1Execute(TObject *Sender)
{
  TAboutBox *AboutBox = new TAboutBox(Application);
  AboutBox->ShowModal();
  delete AboutBox;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	delete[] m_sInterPD.cCmdW;
	delete[] m_sInterPD.cDataW;
	delete[] m_sInterPD.cCmdR;
	delete[] m_sInterPD.cDataR;
	delete[] m_sInterPD.iRInd;
	delete[] m_sInterPD.iWInd;

  delete[] m_dFVco1;
  delete[] m_dFVco2;
  delete[] m_dFVco3;
  delete[] m_dFVco4;

  delete[] m_iCVco1;
  delete[] m_iCVco2;
  delete[] m_iCVco3;
  delete[] m_iCVco4;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	//Set Handle to be able to communicate with other processes
	SetServer((DWORD)this->Handle);

  //Clear Messages
  lbMsgs->Clear();

  lbMsgs->Align = alClient;
  pcSPIS->Align = alClient;

#ifndef CUSTOMER_MODE
  double Freq = ReadRefClkFromReg();
  ShowReferenceClk(Freq);
  m_frmTxPLL->SetRefClk(Freq);
  m_frmTxPLL->UpdateFreq();
  m_frmRxPLL->SetRefClk(Freq);
  m_frmRxPLL->UpdateFreq();
#endif
        
  m_frmTop->Initialize(TopAddr);
  m_frmRxLpf->Initialize(RxLpfAddr, m_frmADDC);
  m_frmTxLpf->Initialize(TxLpfAddr, NULL);
  m_frmTxRf->Initialize(TxRFAddr);
  m_frmRxVga2->Initialize(RxVGA2Addr);
  m_frmRxFe->Initialize(RxFEAddr);
  m_frmTxPLL->Initialize(TxPllAddr);
  m_frmRxPLL->Initialize(RxPllAddr);
  m_frmADDC->Initialize(RxLpfAddr);
  m_frmCustomer->Initialize(0xFF);
  m_frmBoard->Initialize(BoardAddr);
  //m_frmBoard2->Initialize();
  m_frmBoard2->Initialize(dSerPort->getInBulkPt(), dSerPort->getOutBulkPt(), dSerPort->getInCtrBulkPt(), dSerPort->getOutCtrBulkPt());
  m_frmBoard2->btnConfigureSi5356AClick(Application);


  m_UARFCNDef.Initialize(
    m_frmCustomer->cmbULRXBands,
    m_frmCustomer->cmbULRXChan,
    m_frmCustomer->txtULRXFreq,
    m_frmCustomer->btnULRXFChan_B,
    m_frmCustomer->btnULRXFChan_M,
    m_frmCustomer->btnULRXFChan_T,

    m_frmCustomer->cmbDLTXBands,
    m_frmCustomer->cmbDLTXChan,
    m_frmCustomer->txtDLTXFreq,
    m_frmCustomer->btnDLTXFChan_B,
    m_frmCustomer->btnDLTXFChan_M,
    m_frmCustomer->btnDLTXFChan_T
  );
  //m_UARFCNDef->LoadBands();

  //Project by default
	setCurrentFileName("untitled.prj");


#ifdef CUSTOMER_MODE
  if(FileExists(ChangeFileExt(Application->ExeName,".prj")))
  {
    if(!FileIsNotEmpty(ChangeFileExt(Application->ExeName,".prj")))
    {
      ShowMessage("Configuration file is corrupt.\n\n\
        Contact Lime Microsystems\n\
        Unit 57 Surrey Tech Centre Occam Road\n\
        The Surrey Research Park Guildford Surrey\n\
        GU2 7YG\n\n\
        Tel: +44 (0)1483 684801, +44(0)142 8653335\n\
        Fax: +44(0) 1428656662\n\n\
        info@limemicro.com");
      Application->Terminate();
    };

    setCurrentFileName(ChangeFileExt(Application->ExeName,".prj"));
    LoadConfiguration(m_sFileName);
    tbtnDownload->Click();
  }
  else
  {
    //Close();
    ShowMessage("You need configuration file to run this software.\n\n\
      Contact Lime Microsystems\n\
      Unit 57 Surrey Tech Centre Occam Road\n\
      The Surrey Research Park Guildford Surrey\n\
      GU2 7YG\n\n\
      Tel: +44 (0)1483 684801, +44(0)142 8653335\n\
      Fax: +44(0) 1428656662\n\n\
      info@limemicro.com");

    Application->Terminate();
  };
#endif

  //===============================================================
  LoadAdditionalSettings();
  //===============================================================
  
  slLogMesg(4);
  UpdateVerRevMask();
  pcSPIS->ActivePageIndex = 0;
}

//------------------------------------------------------------------------------
// Overwrite hardware defaults
//------------------------------------------------------------------------------
void TfrmMain::LoadAdditionalSettings()
{
  //Top SPI
  //1.a. When Soft Tx is Enabled it automatically enables Tx DSM SPI
  //  Figured out in event handler;
  //1.b. When Soft Rx is Enabled it automatically enables Rx DSM SPI
  //  Figured out in event handler;
  //1.c. Enable Rx OUT/ADC In Switch
  m_frmTop->CustSet_rgrRXOUTSW(1);
  //1.d. Disable PLLCLKOUT
  m_frmTop->CustSet_PLLCLKOUT(false);

  //Tx/RxPLL SPIs
  //2.a. Set CP Up Offset to 30 uA
  m_frmTxPLL->CustSet_cmbOFFUP(3);
  m_frmRxPLL->CustSet_cmbOFFUP(3);

  //Rx VGA2
  //3.a. VGA2 CM Voltage set to 12.
  //m_frmRxVga2->CustSet_cmbVCM(12);
  m_frmRxVga2->CustSet_cmbVCM(13);

  //Rx FE
  //4.a. LNA Load Resistor set to 55
  m_frmRxFe->CustSet_cmbRDLINT_LNA_RXFE(55);

  //ADC /DAC
  //5.a. ADC Common Mode Adj. set to 960mV
  m_frmADDC->CustSet_cmbCoomonModeAdj(1);

  //Tx RF
  // Set "LO Buffer Bias Current" to 6
  m_frmTxRf->CustSet_cmbICT_TXLOBUF(4);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuAutoDwnldClick(TObject *Sender)
{
	mnuAutoDwnld->Checked = !mnuAutoDwnld->Checked;

	if(mnuAutoDwnld->Checked)
	{
		slLogMesg(11);
    sbMain->Panels->Items[1]->Text = " Automatic Download Mode";
	}
	else
	{
		slLogMesg(12);
    sbMain->Panels->Items[1]->Text = " Manual Download Mode";
	};
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ChipGUI1Click(TObject *Sender)
{
  ofstream outf;
  
  //Lets Read Data from chip
  dSerPort->SPI_Rd(m_frmTop->GetPrData());
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());

  //Lets write read data to the text file
  outf.open("ChipVsGui.txt", ios::out);
  m_frmTop->ChipVsGui(outf, "Top Modules:", false);
  m_frmRxLpf->ChipVsGui(outf, "RxLPF Modules:", false);
  m_frmTxLpf->ChipVsGui(outf, "TxLPF Modules:", false);
  m_frmTxRf->ChipVsGui(outf, "TxRF Modules:", false);
  m_frmRxVga2->ChipVsGui(outf, "RxVGA2 Modules:", false);
  m_frmRxFe->ChipVsGui(outf, "RxFE Modules:", false);
  m_frmTxPLL->ChipVsGui(outf, "TxPLL Modules:", false);
  m_frmRxPLL->ChipVsGui(outf, "RxPLL Modules:", false);
  outf.close();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuReadConfigurationClick(TObject *Sender)
{
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";
	ofstream outf;

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
                                          
  dlgSave->DefaultExt = "rdb";
  dlgSave->FileName = "*.rdb";
  dlgSave->Filter = "rdb files (*.rdb)|*.rdb";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;


  if(dlgSave->Execute())
  {
    //Lets Read Data from chip
    dSerPort->SPI_Rd(m_frmTop->GetPrData());
    dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
    dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
    dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
    dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
    dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());

    //Lets write read data to the text file
    outf.open(dlgSave->FileName.c_str(), ios::out);
    m_frmTop->ChipVsGui(outf, "Top Modules:", true);
    m_frmRxLpf->ChipVsGui(outf, "RxLPF Modules:", true);
    m_frmTxLpf->ChipVsGui(outf, "TxLPF Modules:", true);
    m_frmTxRf->ChipVsGui(outf, "TxRF Modules:", true);
    m_frmRxVga2->ChipVsGui(outf, "RxVGA2 Modules:", true);
    m_frmRxFe->ChipVsGui(outf, "RxFE Modules:", true);
    m_frmTxPLL->ChipVsGui(outf, "TxPLL Modules:", true);
    m_frmRxPLL->ChipVsGui(outf, "RxPLL Modules:", true);
    outf.close();

  };
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMLog(TMessage &Message)
{
  slLogMesg(Message.LParam);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMRead(TMessage &Message)
{
	switch(Message.LParam)
	{
		case TopAddr:
  	  dSerPort->SPI_Rd(m_frmTop->GetPrData());
    	if(Message.WParam == 1) m_frmTop->UpdateFormData();
      else if (Message.WParam == 2) m_frmTop->UpdateRCCALData();
    break;

		case TxLpfAddr:
  	  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
    	if(Message.WParam) m_frmTxLpf->UpdateFormData();
    break;

    case RxLpfAddr:
  	  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
    	if(Message.WParam) m_frmRxLpf->UpdateFormData();
    break;

    case RxVGA2Addr:
  	  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
    	if(Message.WParam) m_frmRxVga2->UpdateFormData();
    break;

    case RxPllAddr:
  	  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
    break;

    case TxPllAddr:
  	  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
    break;
  };
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMAutoDownload(TMessage &Message)
{
	if(!mnuAutoDwnld->Checked) return;

	switch(Message.LParam)
	{
		case TopAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmTop->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

		case TxLpfAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmTxLpf->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;
    
    case RxLpfAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmRxLpf->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case TxRFAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmTxRf->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case RxVGA2Addr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmRxVga2->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case RxFEAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmRxFe->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case TxPllAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmTxPLL->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case RxPllAddr:
    	mnuAutoDwnld->Enabled = false;
  	  dSerPort->SPI_Wr(m_frmRxPLL->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

    case BoardAddr:
    	mnuAutoDwnld->Enabled = false;
      dSerPort->SPI_Wr_ADF(m_frmBoard->GetPrData());
      mnuAutoDwnld->Enabled = true;
    break;

		//case 0x01:	strcpy(str, cmbDet->Items->Strings[1].c_str()); break;
		//case 0x02:	strcpy(str, cmbDet->Items->Strings[2].c_str()); break;
		//case 0x04:	strcpy(str, cmbDet->Items->Strings[3].c_str()); break;
		//case 0x08:	strcpy(str, cmbDet->Items->Strings[4].c_str()); break;
	};

//  lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
}

//----------------------------------------------------------------------------
// Writes to the log
//----------------------------------------------------------------------------
void TfrmMain::slLogMesg(int num)
{
	String message;

	switch(num)
	{
	case 0:
		message =	"Project file opened: ";
    message = message + m_sFileName;
    lbMsgs->Items->Add(message);
  break;

	case 1:
		message =	 "Project file created: ";
    message = message + m_sFileName;
    lbMsgs->Items->Add(message);
	break;

	case 2:
		message =	"Project file saved as: ";
    message = message + m_sFileName;
    lbMsgs->Items->Add(message);
	break;

	case 3:
		message =	"Project file saved: ";
		message = message + m_sFileName;
    lbMsgs->Items->Add(message);
	break;

	case 4:
		message =	"Default configuration loaded to the GUI. ";
    lbMsgs->Items->Add(message);
	break;

	case 5:
		message =	"Configuration downloaded to the hardware.";
    lbMsgs->Items->Add(message);
	break;

	case 6:
		message =	"Parallel port initialized successfully.";
    lbMsgs->Items->Add(message);
	break;

	case 8:
		//message =	"Reset signal sent to the Chip.";
    //lbMsgs->Items->Add(message);
  break;

	case 9:
		message =	"Reset signal is ACTIVE.";
		lbMsgs->Items->Add(message);
  break;

	case 10:
		message =	"Reset signal is INACTIVE.";
		lbMsgs->Items->Add(message);
  break;

	case 11:
		message =	" Automatic Download Mode ";
		lbMsgs->Items->Add(message);
  break;

	case 12:
		message =	" Manual Download Mode ";
		lbMsgs->Items->Add(message);
  break;

	case 13:
		message =	"Serial port initialized successfully.";
    lbMsgs->Items->Add(message);
	break;

	case 14:
		message =	"You are not able to control the board since serial port is not";
    lbMsgs->Items->Add(message);
		message =	"accessable. Check if USB to Serial board is connected to the PC USB port.";
    lbMsgs->Items->Add(message);
		message =	"To be able to download configuration, fix the problem and run software again.";
    lbMsgs->Items->Add(message);
  break;

  };

  lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
};

//----------------------------------------------------------------------------
// Sets name of the current project 
//----------------------------------------------------------------------------
void TfrmMain::setCurrentFileName(String fileName)
{
	this->m_sFileName = fileName;



#ifdef ALTERA_EDITION
  String shownName = "6002Dr2 Altera Edition. ";
#else
  String shownName = "6002Dr2 Test. ";
#endif


	if(fileName.Length() == 0)
		shownName = shownName + "untitled.prj";
	else
		shownName = shownName + fileName;

  shownName = shownName + " - Project File";

  this->Caption = shownName;
}

//----------------------------------------------------------------------------
void __fastcall TfrmMain::FileSaveAsItemClick(TObject *Sender)
{
	TIniFile *ini;
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
  dlgSave->DefaultExt = "prj";
  dlgSave->FileName = "*.prj";
  dlgSave->Filter = "Project-Files (*.prj)|*.prj";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;

  if(dlgSave->Execute())
  {
		setCurrentFileName(dlgSave->FileName);

    ini = new TIniFile(m_sFileName);   // we will serialize the data into the file

    m_UARFCNDef.SaveConf(ini);
		m_frmTop->SaveConf(ini);
		m_frmTxLpf->SaveConf(ini);
		m_frmRxLpf->SaveConf(ini);
    m_frmTxRf->SaveConf(ini);
    m_frmRxVga2->SaveConf(ini);
    m_frmRxFe->SaveConf(ini);
    m_frmTxPLL->SaveConf(ini);
    m_frmRxPLL->SaveConf(ini);
    m_frmADDC->SaveConf(ini);
		//SaveConf(out);

		slLogMesg(2);
    delete ini;
  }
  
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMADDC2LPF(TMessage &Message)
{
  m_frmRxLpf->JoinADDC(Message.LParam);
};

//----------------------------------------------------------------------------
void __fastcall TfrmMain::CMResetAct(TMessage &Message)
{
  dSerPort->SPI_RstAct();
	slLogMesg(9);
};

//----------------------------------------------------------------------------
void __fastcall TfrmMain::CMResetInAct(TMessage &Message)
{
  dSerPort->SPI_RstInact();
	//m_frmTop->SetGuiDefaults();
  //m_frmTxLpf->SetGuiDefaults();
  //m_frmRxLpf->SetGuiDefaults();
  //m_frmTxRf->SetGuiDefaults();
  //m_frmRxVga2->SetGuiDefaults();
  //m_frmRxFe->SetGuiDefaults();
  //m_frmTxPLL->SetGuiDefaults();
  //m_frmRxPLL->SetGuiDefaults();

	m_frmTop->SetCalDefaults();
  m_frmTxLpf->SetCalDefaults();
  m_frmRxLpf->SetCalDefaults();
  m_frmRxVga2->SetCalDefaults();

  slLogMesg(10);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuRefClkClick(TObject *Sender)
{
  TdlgRefClk *dlgRefClk = new TdlgRefClk(m_frmTxPLL->GetRefClk()/1000000, Application);

  if(dlgRefClk->ShowModal() == mrOk)
  {
    //sbMain->Panels->Items[2]->Text = " Ref. Clock, Hz: ";
    //sbMain->Panels->Items[2]->Text = sbMain->Panels->Items[2]->Text + FloatToStr(dlgRefClk->txtRefClk->Value);
    ShowReferenceClk(dlgRefClk->txtRefClk->Value*1000000);
    m_frmTxPLL->SetRefClk(dlgRefClk->txtRefClk->Value*1000000);
    m_frmRxPLL->SetRefClk(dlgRefClk->txtRefClk->Value*1000000);
#ifndef CUSTOMER_MODE
    SaveRefClkToReg(dlgRefClk->txtRefClk->Value*1000000);
#endif
  };

  delete dlgRefClk;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ShowReferenceClk(double Val)
{
  sbMain->Panels->Items[2]->Text = " Ref. Clock, Hz: ";
  sbMain->Panels->Items[2]->Text = sbMain->Panels->Items[2]->Text + FloatToStr(Val);
}

//---------------------------------------------------------------------------
void TfrmMain::SaveRefClkToReg(double Freq)
{
  TRegistry* reg = new TRegistry;
  reg->OpenKey(RegistryString, true);
  reg->WriteFloat("RefClk", Freq);
  delete reg;
};

//---------------------------------------------------------------------------
double TfrmMain::ReadRefClkFromReg(void)
{
  double Freq = 30720000;
  /*TRegistry* reg = new TRegistry;
  if(reg->KeyExists(RegistryString))
  {
    reg->OpenKey(RegistryString, false);
    try
    {
      Freq = reg->ReadFloat("RefClk");
    }
    catch(...)
    {
      Freq = 30720000;
    };
  };
  delete reg; */
  return Freq;
};

//---------------------------------------------------------------------------
// Intercomunication DLL Interface
//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmWriteData(TMessage Msg)
{
	m_sInterPD.iLen = 1;

  //Write Command and Addresses
  m_sInterPD.cCmdW[0] = 1;
  //SPI
	m_sInterPD.cCmdW[0] = m_sInterPD.cCmdW[0] << 3;
	m_sInterPD.cCmdW[0] |= Msg.WParamLo;
  //Register
	m_sInterPD.cCmdW[0] = m_sInterPD.cCmdW[0] << 4;
	m_sInterPD.cCmdW[0] |= Msg.LParamHi;
  //Data
  m_sInterPD.cDataW[0] = Msg.LParamLo;

  m_sInterPD.iWInd[0] = 0x00;

  dSerPort->SPI_Wr(&m_sInterPD);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmReadData(TMessage Msg)
{
  //Read Command and Addresses
	m_sInterPD.cCmdR[0] = 0;
	m_sInterPD.cCmdR[0] = m_sInterPD.cCmdR[0] << 3;
	m_sInterPD.cCmdR[0] |= Msg.WParam;
	m_sInterPD.cCmdR[0] = m_sInterPD.cCmdR[0] << 4;
	m_sInterPD.cCmdR[0] |= Msg.LParam;

	m_sInterPD.iRInd[0] = 0x00;

  dSerPort->SPI_Rd(&m_sInterPD);

  SetValueFromServer((DWORD)m_sInterPD.cDataR[0] & 0x00FF);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmWR_Xil(TMessage Msg)
{
	m_sInterPD.iLen = 1;

  //Write Command and Addresses
  m_sInterPD.cCmdW[0] = 1;
  //SPI
	m_sInterPD.cCmdW[0] = m_sInterPD.cCmdW[0] << 3;
	m_sInterPD.cCmdW[0] |= Msg.WParamLo;
  //Register
	m_sInterPD.cCmdW[0] = m_sInterPD.cCmdW[0] << 4;
	m_sInterPD.cCmdW[0] |= Msg.LParamHi;
  //Data
  m_sInterPD.cDataW[0] = Msg.LParamLo;

  m_sInterPD.iWInd[0] = 0x00;

  dSerPort->SPI_Wr_Xil(&m_sInterPD);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmRD_Xil(TMessage Msg)
{
	//lblA->Caption = Msg.WParam;
  //lblB->Caption = Msg.LParam;


  //Read Command and Addresses
	m_sInterPD.cCmdR[0] = 0;
	m_sInterPD.cCmdR[0] = m_sInterPD.cCmdR[0] << 3;
	m_sInterPD.cCmdR[0] |= Msg.WParam;
	m_sInterPD.cCmdR[0] = m_sInterPD.cCmdR[0] << 4;
	m_sInterPD.cCmdR[0] |= Msg.LParam;

	m_sInterPD.iRInd[0] = 0x00;

  dSerPort->SPI_Rd_Xil(&m_sInterPD);

  SetValueFromServer((DWORD)m_sInterPD.cDataR[0] & 0x00FF);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmWR_AD9552(TMessage Msg)
{
  DWORD tmp;
  sPrData sInterPD;
	sInterPD.iLen = 3;
	sInterPD.cCmdW = new char[sInterPD.iLen];
	sInterPD.cDataW = new char[sInterPD.iLen];
	sInterPD.cCmdR = new char[sInterPD.iLen];
	sInterPD.cDataR = new char[sInterPD.iLen];
	sInterPD.iRInd = new int[sInterPD.iLen];
	sInterPD.iWInd = new int[sInterPD.iLen];
	memset(sInterPD.cCmdW, 0, sInterPD.iLen);
	memset(sInterPD.cDataW, 0, sInterPD.iLen);
	memset(sInterPD.cCmdR, 0, sInterPD.iLen);
	memset(sInterPD.cDataR, 0, sInterPD.iLen);
	memset(sInterPD.iRInd, 0, sInterPD.iLen*sizeof(int));
	memset(sInterPD.iWInd, 0, sInterPD.iLen*sizeof(int));
	sInterPD.iToR = 0;
	sInterPD.iToW = sInterPD.iLen;

  sInterPD.cCmdW[0] = 0;
  tmp = Msg.WParam & 0x01FFF;
  tmp = tmp >> 8;
  sInterPD.cCmdW[0] |= tmp;

  sInterPD.cCmdW[1] = 0;
  tmp = Msg.WParam & 0x0FF;
  sInterPD.cCmdW[1] |= tmp;

  sInterPD.cCmdW[2] = Msg.LParam & 0x0FF;

  dSerPort->SPI_Wr_AD9552(&sInterPD);
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmRD_AD9552(TMessage Msg)
{

};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmWR_AD7691(TMessage Msg)
{
  //There are no write operation support by chip
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::wmRD_AD7691(TMessage Msg)
{
  DWORD tmp;
  sPrData sInterPD;
	sInterPD.iLen = 3;
	sInterPD.cCmdW = new char[sInterPD.iLen];
	sInterPD.cDataW = new char[sInterPD.iLen];
	sInterPD.cCmdR = new char[sInterPD.iLen];
	sInterPD.cDataR = new char[sInterPD.iLen];
	sInterPD.iRInd = new int[sInterPD.iLen];
	sInterPD.iWInd = new int[sInterPD.iLen];
	memset(sInterPD.cCmdW, 0, sInterPD.iLen);
	memset(sInterPD.cDataW, 0, sInterPD.iLen);
	memset(sInterPD.cCmdR, 0, sInterPD.iLen);
	memset(sInterPD.cDataR, 0, sInterPD.iLen);
	memset(sInterPD.iRInd, 0, sInterPD.iLen*sizeof(int));
	memset(sInterPD.iWInd, 0, sInterPD.iLen*sizeof(int));
	sInterPD.iToR = sInterPD.iLen;
	sInterPD.iToW = 1;

  dSerPort->SPI_Rd_AD7691(&sInterPD);

  tmp = sInterPD.cDataR[0];
  tmp = tmp << 8;
  tmp |= (0x00FF & sInterPD.cDataR[1]);
  tmp = tmp << 8;
  tmp |= (0x00FF & sInterPD.cDataR[2]);
  tmp = tmp >> 6;
  SetValueFromServer(tmp & 0x03FFFF);
};

//----------------------------------------------------------------------------
void __fastcall TfrmMain::wmReset(TMessage Msg)
{
  dSerPort->SPI_Rst();
};

//---------------------------------------------------------------------------
// Work around, to not power down TxRF, while after that LO DACs
// doesn't recover.
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMSoftTxPD(TMessage &Message)
{
  //m_frmCustomer->cmbLNASEL_Cust->ItemIndex = Message.LParam;
  //m_frmCustomercmbLNASEL_CustChange(Application);

  //EnableAllSPIClocks();

  if(Message.LParam)
  {
    m_frmTxLpf->CustSet_LpfPowerON();
    m_frmTxPLL->CustSet_PLLPowerON();
  }
  else
  {
    m_frmTxLpf->CustSet_LpfPowerOFF();
    m_frmTxPLL->CustSet_PLLPowerOFF();
  };
  //RestoreAllSPIClocks();
};

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMSPIClkOnMask(TMessage Msg)
{
  EnableSPIClockByMask(Msg.LParam);
};

void TfrmMain::EnableSPIClockByMask(int Mask)
{
  //Enable all SPI clocks in TopSPI
  m_frmTop->EnableSPIClocksByMask(Mask);
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);
};

//---------------------------------------------------------------------------
//
//
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CMSPIClkRestore(TMessage Msg)
{
  RestoreAllSPIClocks();
};

//---------------------------------------------------------------------------
// Functions for customer mode interface
//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbLNASEL_CustChange(TObject *Sender)
{
  //EnableAllSPIClocks();
  SetLnaChain(m_frmCustomer->cmbLNASEL_Cust->ItemIndex);
  //RestoreAllSPIClocks();
}

//----------------------------------------------------------------------------
void __fastcall TfrmMain::CMUpdateLNA(TMessage &Message)
{
  m_frmCustomer->cmbLNASEL_Cust->ItemIndex = Message.LParam;
  m_frmCustomercmbLNASEL_CustChange(Application);
  switch(Message.LParam)
  {
    case 1:
      dSerPort->SetBrdLNA(0x03);  //LNA 1
    break;

    case 2:
      dSerPort->SetBrdLNA(0x01);  //LNA 2
    break;

    case 3:
      dSerPort->SetBrdLNA(0x00);  //LNA 3
    break;
  }; 

};

//----------------------------------------------------------------------------
void __fastcall TfrmMain::CMUpdatePA(TMessage &Message)
{
  dSerPort->SetBrdPA(Message.LParam);
};

//---------------------------------------------------------------------------
// Set current LNA chain
//---------------------------------------------------------------------------
void TfrmMain::SetLnaChain(int iChain)
{
  switch(iChain)
  {
    case 0:
      m_frmRxFe->CustSet_ActiveLNA(0);
      m_frmRxPLL->CustSet_ActiveLOBuff(0);
    break;

    case 1:
      m_frmRxFe->CustSet_ActiveLNA(1);
      m_frmRxPLL->CustSet_ActiveLOBuff(1);
      dSerPort->SetBrdLNA(0x03);  //LNA 1
    break;

    case 2:
      m_frmRxFe->CustSet_ActiveLNA(2);
      m_frmRxPLL->CustSet_ActiveLOBuff(2);
      dSerPort->SetBrdLNA(0x01);  //LNA 2
    break;

    case 3:
      m_frmRxFe->CustSet_ActiveLNA(3);
      m_frmRxPLL->CustSet_ActiveLOBuff(3);
      dSerPort->SetBrdLNA(0x00);  //LNA 3
    break;
  };
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerbtnClbrTxClick(TObject *Sender)
{
  int iTryDone, iTryComplete;
  char cTmp;

  //EnableAllSPIClocks();
  //Enable TxLPF DC CAL Clock
  EnableSPIClockByMask(0x02);


  //Set I Channel DC Calibration chain
  m_frmTxLpf->SetCalAddr(0);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmTxLpf->StartCalibration(0);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmTxLpf->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("I Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmTxLpf->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("I Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };
    Application->ProcessMessages();
  }while(iTryComplete);


  //Q Channel
  m_frmTxLpf->SetCalAddr(1);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmTxLpf->StartCalibration(1);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmTxLpf->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("Q Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmTxLpf->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("Q Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  RestoreAllSPIClocks();

  lbMsgs->Items->Add("Tx Calibration Done");
  lbMsgs->ItemIndex = lbMsgs->Items->Count-1;

}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerbtnClbrRxClick(TObject *Sender)
{
  int iTryDone, iTryComplete;
  char cTmp;
  int iRxVGA2Gain_ind;

  //EnableAllSPIClocks();

//=================== Remember RxVGA2 gain =====================================
  iRxVGA2Gain_ind = m_frmRxVga2->GetRXVGA2Gain();

//=================== Set RxVGA2 gain to 30dB ==================================
  m_frmRxVga2->SetRXVGA2Gain(10);

//=================== Rx LPF DC Calibration Begin ==============================

  //Enable RxLPF DC CAL Clock
  EnableSPIClockByMask(0x08);

  //Set I Channel DC Calibration chain
  m_frmRxLpf->SetCalAddr(0);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxLpf->StartCalibration(0);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxLpf->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxLPF I Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxLpf->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxLPF I Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };
    Application->ProcessMessages();
  }while(iTryComplete);


  //Q Channel
  m_frmRxLpf->SetCalAddr(1);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxLpf->StartCalibration(1);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxLpf->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxLPF Q Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxLpf->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxLPF Q Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //Restore all SPI Clokcs
  RestoreAllSPIClocks();
//=================== Rx LPF DC Calibration End ================================


//=================== Rx VGA2 DC Calibration Begin =============================

  //Enable RxVGA2 DC CAL Clock
  EnableSPIClockByMask(0x10);

  //REF Channel
  m_frmRxVga2->SetCalAddr(0);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxVga2->StartCalibration(0);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxVga2->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxVGA2 REF Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxVga2->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxVGA2 REF Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //dc2a_vga2_i Channel
  m_frmRxVga2->SetCalAddr(1);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxVga2->StartCalibration(1);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxVga2->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxVGA2 DC2A_I Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxVga2->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxVGA2 DC2A_I Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //dc2a_vga2_q Channel
  m_frmRxVga2->SetCalAddr(2);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxVga2->StartCalibration(2);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxVga2->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxVGA2 DC2A_Q Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxVga2->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxVGA2 DC2A_Q Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //dc2b_vga2_i Channel
  m_frmRxVga2->SetCalAddr(3);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxVga2->StartCalibration(3);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxVga2->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxVGA2 DC2B_I Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxVga2->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxVGA2 DC2B_I Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //dc2b_vga2_q Channel
  m_frmRxVga2->SetCalAddr(4);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmRxVga2->StartCalibration(4);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmRxVga2->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("RxVGA2 DC2B_Q Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmRxVga2->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("RxVGA2 DC2B_Q Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };

    Application->ProcessMessages();
  }while(iTryComplete);

  //Restore all SPI Clokcs
  RestoreAllSPIClocks();

//=================== Restore RxVGA2 gain =====================================
  m_frmRxVga2->SetRXVGA2Gain(iRxVGA2Gain_ind);

//=================== Rx VGA2 DC Calibration End ===============================

  //RestoreAllSPIClocks();

  lbMsgs->Items->Add("RxLPF and RxVGA2 Calibration Done");
  lbMsgs->ItemIndex = lbMsgs->Items->Count-1;

}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbBypassChange(TObject *Sender)
{
  SetBypassLoopback();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbLoopbackChange(TObject *Sender)
{
  SetBypassLoopback();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbTxBypassChange(TObject *Sender)
{
  //EnableAllSPIClocks();

  switch(m_frmCustomer->cmbTxBypass->ItemIndex)
  {
    //Turn off all Bypass Modes
    case 0:
      m_frmTxLpf->CustSet_BypassLpfOFF();
    break;

    //Bypass RxLPF:
    //1. Power Down TxLPF;
    //2. Select Bypass Mode.
    case 1:
      //Turn off other bypass

      //Turn on required bypass mode
      m_frmTxLpf->CustSet_BypassLpfON();
    break;
  };

  //RestoreAllSPIClocks();
}

//---------------------------------------------------------------------------
void TfrmMain::SetBypassLoopback()
{
  int iBB = m_frmCustomer->cmbBypass->ItemIndex;
  int iLB = m_frmCustomer->cmbLoopback->ItemIndex;

  //Turn Off all bypass modes
  //EnableAllSPIClocks();
  m_frmTop->CustSet_Tia2OutOFF();
  m_frmRxLpf->CustSet_BypassLpfOFF();
  m_frmRxVga2->CustSet_RxVGA2PowerON();
  //RestoreAllSPIClocks();

  //Turn Off all loopback modes
  //EnableAllSPIClocks();
  m_frmCustomer->cmbLNASEL_Cust->ItemIndex = 1;
  SetLnaChain(m_frmCustomer->cmbLNASEL_Cust->ItemIndex);
  m_frmTop->CustSet_SetRFLB(0);
  m_frmTop->CustSet_SetBBLB(0);
  m_frmRxFe->CustSet_LNAPowerON();
  m_frmRxFe->CustSet_PowerON();
  m_frmRxLpf->CustSet_LpfPowerON();
  m_frmRxVga2->CustSet_RxVGA2PowerON();
  //RestoreAllSPIClocks();

  //RxLPF Bypass, LBEN_LPFIN ON
  if((iLB == 0x01) && (iBB == 0x01))
  {
    //EnableAllSPIClocks();
    m_frmRxLpf->CustSet_BypassLpfON();  //Turns Bypas RxLPF switch ON, powers down LPF
    m_frmRxFe->CustSet_PowerOFF();      //Powers down TIA, RxMIX, RxLNA
    m_frmTop->CustSet_SetBBLB(1);
    //RestoreAllSPIClocks();
    return;
  };

  //RxVGA2 and RxLPF Bypass, LBEN_LPFIN ON
  if((iLB == 0x01) && (iBB == 0x02))
  {
    //EnableAllSPIClocks();
    m_frmRxFe->CustSet_PowerOFF();          //Powers down TIA, RxMIX, RxLNA
    m_frmRxVga2->CustSet_RxVGA2PowerOFF();  //Powers down RxVGA2
    m_frmRxLpf->CustSet_LpfPowerOFF();      //Powers down RxLPF
    m_frmTop->CustSet_Tia2OutON();
    m_frmTop->CustSet_SetBBLB(1);
    //RestoreAllSPIClocks();
    return;
  };

  //Illegal combination
  if(  ((iLB == 0x02) || (iLB == 0x03)) && ((iBB == 0x01) || (iBB == 0x02))  )
  {
    ShowMessage("Illegal Baseband Bypass and Baseband Loopback mode.\n");
    return;
  };


  //
  switch(iBB)
  {
    //Bypass RxLPF:
    //1. Power Down RxLPF;
    //2. Select Bypass Mode.
    case 1:
      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmRxLpf->CustSet_BypassLpfON();
      //RestoreAllSPIClocks();
    break;

    //Bypass RxLPF, RxVGA2:
    //1. Power Down RxLPF;
    //2. Power Down RxVGA2;
    //3. Select RxTIA Connected to Output Pins
    case 2:
      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmRxVga2->CustSet_RxVGA2PowerOFF();
      m_frmRxLpf->CustSet_LpfPowerOFF();
      m_frmTop->CustSet_Tia2OutON();
      //RestoreAllSPIClocks();
    break;
  };


  //
  switch(iLB)
  {
    //To RxLPF input
    case 1:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmRxFe->CustSet_PowerOFF();
      m_frmRxLpf->CustSet_LpfPowerON();
      m_frmRxVga2->CustSet_RxVGA2PowerON();
      m_frmTop->CustSet_SetBBLB(1);
      //RestoreAllSPIClocks();
    break;

    //To RxVGA2 input
    case 2:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmRxFe->CustSet_PowerOFF();
      m_frmRxLpf->CustSet_LpfPowerOFF();
      m_frmRxVga2->CustSet_RxVGA2PowerON();
      m_frmTop->CustSet_SetBBLB(2);
      //RestoreAllSPIClocks();
    break;

    //To output pins
    case 3:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmRxFe->CustSet_PowerOFF();
      m_frmRxLpf->CustSet_LpfPowerOFF();
      m_frmRxVga2->CustSet_RxVGA2PowerOFF();
      m_frmTop->CustSet_SetBBLB(3);
      //RestoreAllSPIClocks();
    break;

    //
    case 4:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmCustomer->cmbLNASEL_Cust->ItemIndex = 1;
      SetLnaChain(m_frmCustomer->cmbLNASEL_Cust->ItemIndex);
      m_frmRxFe->CustSet_LNAPowerOFF();
      m_frmTop->CustSet_SetRFLB(1);
      //RestoreAllSPIClocks();
    break;

    case 5:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmCustomer->cmbLNASEL_Cust->ItemIndex = 2;
      SetLnaChain(m_frmCustomer->cmbLNASEL_Cust->ItemIndex);
      m_frmRxFe->CustSet_LNAPowerOFF();
      m_frmTop->CustSet_SetRFLB(2);
      //RestoreAllSPIClocks();
    break;

    case 6:
      //Turn off other bypass

      //Turn on required bypass mode
      //EnableAllSPIClocks();
      m_frmCustomer->cmbLNASEL_Cust->ItemIndex = 3;
      SetLnaChain(m_frmCustomer->cmbLNASEL_Cust->ItemIndex);
      m_frmRxFe->CustSet_LNAPowerOFF();
      m_frmTop->CustSet_SetRFLB(3);
      //RestoreAllSPIClocks();
    break;
  };


};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbRxBandsChange(TObject *Sender)
{
  double dFreq;
  m_UARFCNDef.SetChannels(true);
  dFreq = m_UARFCNDef.SetFrequency(true);
  m_UARFCNDef.SetFastChannelsAllUp(true);
  if(dFreq > 0) m_frmRxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbULRXChanChange(TObject *Sender)
{
  double dFreq;
  dFreq = m_UARFCNDef.SetFrequency(true);
  m_UARFCNDef.SetFastChannelsAllUp(true);
  if(dFreq > 0) m_frmRxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerbtnFChanULRX_BClick(TObject *Sender)
{
  double dFreq;
  m_UARFCNDef.SetFastChannels(true);
  dFreq = m_UARFCNDef.SetFrequency(true);
  if(dFreq > 0) m_frmRxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbDLTXBandsChange(TObject *Sender)
{
  double dFreq;
  m_UARFCNDef.SetChannels(false);
  dFreq = m_UARFCNDef.SetFrequency(false);
  m_UARFCNDef.SetFastChannelsAllUp(false);
  if(dFreq > 0) m_frmTxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomercmbDLTXChanChange(TObject *Sender)
{
  double dFreq;
  dFreq = m_UARFCNDef.SetFrequency(false);
  m_UARFCNDef.SetFastChannelsAllUp(false);
  if(dFreq > 0) m_frmTxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerbtnDLTXFChan_BClick(TObject *Sender)
{
  double dFreq;
  m_UARFCNDef.SetFastChannels(false);
  dFreq = m_UARFCNDef.SetFrequency(false);
  if(dFreq > 0) m_frmTxPLL->CustSet_LoadFrequency(dFreq/1000);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerbtnCalRxTIAClick(TObject *Sender)
{
  char cTmp;
  ofstream outf;

  //============ Saved and restored values includes: ===========================
  int DCOffsetCancellationI, DCOffsetCancellationQ;
  int DCCalValI, DCCalValQ;
  int RxLPFDecode;
  int RxLPFBypass;
  bool PwrLpfMods, PwrLpf, PwrDCDac, PwrDCRef, PwrDCCmpr;
  // 1. SPI Clock Enables in TopSPI.
  // 2. DCOffsetCancellationI, DCOffsetCancellationQ in RxFESPI.
  // 3. DC Calibration values from RxLPF I and Q channels.
  // 4. "Decode Signals" Control State in RxLPF.
  // 5. LPF Bypass (Test) state.
  // 6. Power Control States.


  outf.open("RxTIAClbr.txt", ios::out);
  outf << left;
	outf << "RxTIA Calibration" << endl;
	outf << endl;
	outf << "------------------" << endl;
	outf.width(6); outf << "| DAC I"; outf.width(3); outf << " | ";
	outf.width(7); outf << "COMP I"; outf.width(1); outf << "|";
	outf << endl;
	outf << "--------+---------" << endl;

  //EnableAllSPIClocks();
  //Read the cmbDCOFF_I_RXFE and cmbDCOFF_Q_RXFE states from RxFESPI
  DCOffsetCancellationI = m_frmRxFe->CustGet_DCOffsetCancellationI();
  DCOffsetCancellationQ = m_frmRxFe->CustGet_DCOffsetCancellationQ();
  DCCalValI = m_frmRxLpf->GetCalVal(0x00);
  DCCalValQ = m_frmRxLpf->GetCalVal(0x01);
  RxLPFDecode = m_frmRxLpf->CustGet_DecodeState();
  RxLPFBypass = m_frmRxLpf->CustGet_LPFTestState();
  PwrLpfMods = m_frmRxLpf->CustGet_PwrLpfMods();
  PwrLpf = m_frmRxLpf->CustGet_PwrLpf();
  PwrDCDac = m_frmRxLpf->CustGet_PwrDCDac();
  PwrDCRef = m_frmRxLpf->CustGet_PwrDCRef();
  PwrDCCmpr = m_frmRxLpf->CustGet_PwrDCCmpr();


  m_frmRxLpf->CustSet_EnableDCOffsetCompOnly();
  m_frmRxLpf->CustSet_BypassLPFOnlyOn();

  //Channel I
  m_frmRxLpf->SetCalAddr(0);
  for(int i=0; i<128; i++)
  {
    m_frmRxFe->CustSet_DCOffsetCancellationI(i);
    cTmp = m_frmRxLpf->GetCalStatus();

  	outf.width(2); outf << "|";	outf.width(5);
    outf << i;	outf.width(3); outf << " | ";	outf.width(6);
	  if(cTmp & 0x01) cTmp = '1';
    else cTmp = '0';
    outf << cTmp;	outf.width(2); outf << " |"; outf << endl;
  };
  outf << "------------------" << endl;


  //Channel Q
	outf << endl;
	outf << "------------------" << endl;
	outf.width(6); outf << "| DAC Q"; outf.width(3); outf << " | ";
	outf.width(7); outf << "COMP Q"; outf.width(1); outf << "|";
	outf << endl;
	outf << "--------+---------" << endl;
  m_frmRxLpf->SetCalAddr(1);
  for(int i=0; i<128; i++)
  {
    m_frmRxFe->CustSet_DCOffsetCancellationQ(i);
    cTmp = m_frmRxLpf->GetCalStatus();

  	outf.width(2); outf << "|";	outf.width(5);
    outf << i;	outf.width(3); outf << " | ";	outf.width(6);
	  if(cTmp & 0x01) cTmp = '1';
    else cTmp = '0';
    outf << cTmp;	outf.width(2); outf << " |"; outf << endl;
  };
  outf << "------------------" << endl;



  outf.close();

  m_frmRxLpf->CustSet_RestoreDCOffsetCompOnly();
  m_frmRxLpf->CustSet_BypassLPFOnlyOff();
  //Restore the cmbDCOFF_I_RXFE and cmbDCOFF_Q_RXFE states from RxFESPI
  m_frmRxFe->CustSet_DCOffsetCancellationI(DCOffsetCancellationI);
  m_frmRxFe->CustSet_DCOffsetCancellationQ(DCOffsetCancellationQ);
  m_frmRxLpf->SetCalVal(0x00, DCCalValI);
  m_frmRxLpf->SetCalVal(0x01, DCCalValQ);
  m_frmRxLpf->CustSet_DecodeState(RxLPFDecode);
  m_frmRxLpf->CustSet_LPFTestState(RxLPFBypass);
  m_frmRxLpf->CustGet_PwrLpfMods(PwrLpfMods);
  m_frmRxLpf->CustGet_PwrLpf(PwrLpf);
  m_frmRxLpf->CustGet_PwrDCDac(PwrDCDac);
  m_frmRxLpf->CustGet_PwrDCRef(PwrDCRef);
  m_frmRxLpf->CustGet_PwrDCCmpr(PwrDCCmpr);

  //RestoreAllSPIClocks();

  lbMsgs->Items->Add("RxTIA Calibration Done");
  lbMsgs->ItemIndex = lbMsgs->Items->Count-1; 
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmCustomerButton1Click(TObject *Sender)
{
  CalLPFCore();
}

//---------------------------------------------------------------------------
// Calibration of LPF CAL CORE
//---------------------------------------------------------------------------
void TfrmMain::CalLPFCore()
{
  int iDCCalValue, iLPFCALValue;
  int iTryDone, iTryComplete;
  int iLPFTuningClockInd;
  char cTmp;
  bool bPD_CLKLPFCAL; //remember Divide TxPLL freq by 8 setting
  bool bSoftTx;

  //=========== I. TOP SPI DC Calibration for CAL Core LPF =====================
  // Steps:
  // 1. Turn off module power supplies in TopSPI;
  // 2. Perform calibration in chain address 0;
  // 3. Read DC Calibration value from DC CAlibration chain number 0 into iDCCalValue variable;
  // 4. Turn on module power supplies in TopSPI;

  //=========== Step 1 =========================================================
  //m_frmTop->CustSet_TopPowerON(false);

  //=========== Step 2 =========================================================
  //Set 0 address DC Calibration chain
  m_frmTop->SetCalAddr(0);
  iTryComplete = 5;

  do{
    iTryComplete--;
    iTryDone = 5;
    //Start calibration
    m_frmTop->StartCalibration(0);

    //Whait for calibration complete
    do{
      iTryDone--;
      cTmp = m_frmTop->GetCalStatus();
      if(((cTmp >> 1)&0x01) ^ 0x01)
      {
        lbMsgs->Items->Add("DC Channel Done OK");
        lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
        break;
      };
      Application->ProcessMessages();
    }while(iTryDone);

    //Check Lock status
    cTmp = m_frmTop->GetCalStatus();
    if( (((cTmp >> 2)&0x07)==0x05) || (((cTmp >> 2)&0x07)==0x02) )
    {
      lbMsgs->Items->Add("DC Channel Lock OK");
      lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
      break;
    };
    Application->ProcessMessages();
  }while(iTryComplete);

  //=========== Step 3 =========================================================
  //iDCCalValue = m_frmTop->GetCalVal(0);

  //=========== Step 4 =========================================================
  //m_frmTop->CustSet_TopPowerON(true);
  

  //========== II. LPF CAL Core Calibration in TOP SPI =========================
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

  //=========== Step 1 =========================================================
  m_frmTop->CustSet_LPFBandwidth(9);

  //=========== Step 2 =========================================================
  //m_frmTop->EnableAllSPIClocks();

  //=========== Step 2.a) ======================================================
  iLPFTuningClockInd = m_frmTop->GetLPFTuningClockInd();

  //=========== Step 2.b) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000)
  {
    m_frmTop->SetLPFTuningClockInd(0);
    //Enable SoftTX
    bSoftTx = m_frmTop->CustSet_SofTxOnOff(true);
    dSerPort->SPI_Wr(m_frmTop->GetPrData());
  };

  //=========== Step 2.c) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000) m_frmTxPLL->SetPLLTo320MHz();

  //=========== Step 2.d) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000) bPD_CLKLPFCAL = m_frmTop->CustGet_PD_CLKLPFCAL();
  if(m_frmTxPLL->GetRefClk()!= 40000000) m_frmTop->CustSet_PD_CLKLPFCAL(false);

  //=========== Step 3 =========================================================
  m_frmTop->CustSet_EnableLPFCAL(true);

  //=========== Step 4 =========================================================
  m_frmTop->CustSet_ResetLPFCAL(true);
  m_frmTop->CustSet_ResetLPFCAL(false);

  //=========== Step 5 =========================================================
  m_frmTop->CustGet_LPFCALVal(iDCCalValue, iLPFCALValue);

  //=========== Step 6 =========================================================
  m_frmTop->CustSet_EnableLPFCAL(false);

  //=========== Step 7 =========================================================
  //m_frmTop->RestoreAllSPIClocks();

  //=========== Step 7.a) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000) m_frmTop->CustSet_PD_CLKLPFCAL(bPD_CLKLPFCAL);

  //=========== Step 7.b) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000) m_frmTop->SetLPFTuningClockInd(iLPFTuningClockInd);

  //=========== Step 7.c) ======================================================
  if(m_frmTxPLL->GetRefClk()!= 40000000)
  {
    m_frmTxPLL->RestoreAfterSetPLLTo320MHz();
    //Restore SoftTX Enable
    m_frmTop->CustSet_SofTxOnOff(bSoftTx);
    dSerPort->SPI_Wr(m_frmTop->GetPrData());
  };


  //========= III. Write Calibration Values to Tx and Rx LPFs ==================
  // Steps:
  // 1. Enable All SPI Clocks in TopSPI;
  // 2. Write "DC Offset Resistor" value to the RxLPF;
  // 3. Write "From TRX_LPF_CAL" value to the RxLPF; 
  // 4. Write "DC Offset Resistor" value to the TxLPF;
  // 5. Write "From TRX_LPF_CAL" value to the TxLPF;
  // 6. Restore All SPI Clocks in TopSPI.

  //=========== Step 1 =========================================================
  //m_frmTop->EnableAllSPIClocks();

  //=========== Step 2 =========================================================
  m_frmRxLpf->CustSet_LPFDCVAL(iDCCalValue);

  //=========== Step 3 =========================================================
  m_frmRxLpf->CustSet_LPFCALVAL(iLPFCALValue);

  //=========== Step 4 =========================================================
  m_frmTxLpf->CustSet_LPFDCVAL(iDCCalValue);

  //=========== Step 5 =========================================================
  m_frmTxLpf->CustSet_LPFCALVAL(iLPFCALValue);

  //=========== Step 6 =========================================================
  //m_frmTop->RestoreAllSPIClocks();



  lbMsgs->Items->Add("LPF Core Calibration Done");
  lbMsgs->ItemIndex = lbMsgs->Items->Count-1;
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_frmToprgrRFLBClick(TObject *Sender)
{
  m_frmTop->rgrRFLBClick(Sender);

}

//---------------------------------------------------------------------------
// dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
//---------------------------------------------------------------------------
void TfrmMain::SaveUnderRVF_Format(int dec)
{
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";
	ofstream outf;

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);

  dlgSave->DefaultExt = "rvf";
  dlgSave->FileName = "*.rvf";
  dlgSave->Filter = "rvf files (*.rvf)|*.rvf";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;


  if(dlgSave->Execute())
  { /*
    //*** Comented to create file from GUI data instead of chip registers data

    //Lets Read Data from chip
    dSerPort->SPI_Rd(m_frmTop->GetPrData());
    dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
    dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
    dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
    dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
    dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
    */
    //Lets write read data to the text file
    outf.open(dlgSave->FileName.c_str(), ios::out);
    if(dec == 1)
    {
      outf.flags(ios::left | ios::dec);
    }
    else
    {
      outf.flags(ios::left | ios::hex | ios::uppercase | ios::showbase);
    };
    m_frmTop->MakeRVFFile(outf);
    m_frmTxPLL->MakeRVFFile(outf);
    m_frmRxPLL->MakeRVFFile(outf);
    m_frmTxLpf->MakeRVFFile(outf);
    m_frmTxRf->MakeRVFFile(outf);
    m_frmRxLpf->MakeRVFFile(outf);
    m_frmRxVga2->MakeRVFFile(outf);
    m_frmRxFe->MakeRVFFile(outf);
    outf.close();

  };
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuReadRVFClick(TObject *Sender)
{
  SaveUnderRVF_Format(1);
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuReadRVF_hexClick(TObject *Sender)
{
  SaveUnderRVF_Format(0);
}

//---------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//---------------------------------------------------------------------------
void TfrmMain::SaveUnderRFIF_Format()
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


  /*
  //*** Comented to create file from GUI data instead of chip registers data

  //Lets Read Data from chip
  dSerPort->SPI_Rd(m_frmTop->GetPrData());
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
  */

  dlgRFIFParam = new TdlgRFIFParam(Application);
  if(dlgRFIFParam->ShowModal() == mrOk)
  {
    if(dlgSave->Execute())
    {
      ValStr = "," + dlgRFIFParam->txtValue->Text;
      //Lets write read data to the text file
      outf.open(dlgSave->FileName.c_str(), ios::out);
      m_frmTop->MakeRFIFFile(outf, ValStr.c_str());
      m_frmTxPLL->MakeRFIFFile(outf, ValStr.c_str());
      m_frmRxPLL->MakeRFIFFile(outf, ValStr.c_str());
      m_frmTxLpf->MakeRFIFFile(outf, ValStr.c_str());
      m_frmTxRf->MakeRFIFFile(outf, ValStr.c_str());
      m_frmRxLpf->MakeRFIFFile(outf, ValStr.c_str());
      m_frmRxVga2->MakeRFIFFile(outf, ValStr.c_str());
      m_frmRxFe->MakeRFIFFile(outf, ValStr.c_str());
      outf.close();
    };
  };
  delete dlgRFIFParam;
}

//----------------------------------------------------------------------------
void __fastcall TfrmMain::mnuReadRVF_rfifClick(TObject *Sender)
{
  SaveUnderRFIF_Format();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuSaveRegistersClick(TObject *Sender)
{
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";
	ofstream outf;

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);

  dlgSave->DefaultExt = "txt";
  dlgSave->FileName = "*.txt";
  dlgSave->Filter = "txt files (*.txt)|*.txt";
  //*DLG dlgSave->InitialDir = drive;
  //*DLG dlgSave->InitialDir = dlgSave->InitialDir + dir;


  if(dlgSave->Execute())
  {
    /*
    //*** Comented to create file from GUI data instead of chip registers data

    //Lets Read Data from chip
    dSerPort->SPI_Rd(m_frmTop->GetPrData());
    dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
    dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
    dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
    dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
    dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
    dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
    */

    //Lets write read data to the text file
    outf.open(dlgSave->FileName.c_str(), ios::out);
    m_frmTop->MakeRegisterFile(outf);
    m_frmTxPLL->MakeRegisterFile(outf);
    m_frmRxPLL->MakeRegisterFile(outf);
    m_frmTxLpf->MakeRegisterFile(outf);
    m_frmTxRf->MakeRegisterFile(outf);
    m_frmRxLpf->MakeRegisterFile(outf);   //Makes register map for ADDC as well.
    m_frmRxVga2->MakeRegisterFile(outf);
    m_frmRxFe->MakeRegisterFile(outf);
    outf.close();
  };
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::ChipGUI2Click(TObject *Sender)
{
  //Lets Read Data from chip
  dSerPort->SPI_Rd(m_frmTop->GetPrData());

  //EnableAllSPIClocks();

  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());

  //RestoreAllSPIClocks();

  //Lets set GUI according read data
  m_frmTop->SetGUIUnderReadback();
  m_frmRxLpf->SetGUIUnderReadback();
  m_frmTxLpf->SetGUIUnderReadback();
  m_frmTxRf->SetGUIUnderReadback();
  m_frmRxVga2->SetGUIUnderReadback();
  m_frmRxFe->SetGUIUnderReadback();
  m_frmTxPLL->SetGUIUnderReadback();
  m_frmRxPLL->SetGUIUnderReadback();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::CommunicationSettings1Click(TObject *Sender)
{
  if(dSerPort->ShowModal() == mrOk)
  {
    if(!dSerPort->PortOpened())
    {
      tbtnDownload->Enabled = false;
      slLogMesg(14);
    }
    else
    {
      tbtnDownload->Enabled = true;
      slLogMesg(13);
    };
  };
}

//---------------------------------------------------------------------------
// Register Map Test
//---------------------------------------------------------------------------
bool TfrmMain::TestRegisters()
{
  bool bSoftTx;
  bool bSoftRx;

  TdRegTest *dRegTest = new TdRegTest(Application);
  dRegTest->Show();

  //Enable SoftTX
  //bool bSoftTx = m_frmTop->CustSet_SofTxOnOff(true);
  //dSerPort->SPI_Wr(m_frmTop->GetPrData());
  //Enable SoftRX
  //bool bSoftRx = m_frmTop->CustSet_SofRxOnOff(true);
  //dSerPort->SPI_Wr(m_frmTop->GetPrData());


  //x EnableAllSPIClocks();



  //Check TxRF
  dRegTest->AddLine("Testing TxRF SPI, Mask 0xAA:");
  m_frmTxRf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dRegTest->Compare(m_frmTxRf->GetPrData());

  dRegTest->AddLine("Testing TxRF SPI, Mask 0x55:");
  m_frmTxRf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dRegTest->Compare(m_frmTxRf->GetPrData());
  dRegTest->AddLine("");

  //Check RxFE
  dRegTest->AddLine("Testing RxFE SPI, Mask 0xAA:");
  m_frmRxFe->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dRegTest->Compare(m_frmRxFe->GetPrData());

  dRegTest->AddLine("Testing RxFE SPI, Mask 0x55:");
  m_frmRxFe->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dRegTest->Compare(m_frmRxFe->GetPrData());
  dRegTest->AddLine("");

  //Check RxVGA2
  dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
  m_frmRxVga2->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dRegTest->Compare(m_frmRxVga2->GetPrData());

  dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
  m_frmRxVga2->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dRegTest->Compare(m_frmRxVga2->GetPrData());
  dRegTest->AddLine("");

  //Check RxLPF
  dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
  m_frmRxLpf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dRegTest->Compare(m_frmRxLpf->GetPrData());

  dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
  m_frmRxLpf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dRegTest->Compare(m_frmRxLpf->GetPrData());
  dRegTest->AddLine("");

  //Check TxLPF
  dRegTest->AddLine("Testing TxLPF SPI, Mask 0xAA:");
  m_frmTxLpf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dRegTest->Compare(m_frmTxLpf->GetPrData());

  dRegTest->AddLine("Testing TxLPF SPI, Mask 0x55:");
  m_frmTxLpf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dRegTest->Compare(m_frmTxLpf->GetPrData());
  dRegTest->AddLine("");

  //Check TxPLL
  dRegTest->AddLine("Testing TxPLL SPI, Mask 0xAA:");
  m_frmTxPLL->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dRegTest->Compare(m_frmTxPLL->GetPrData());

  dRegTest->AddLine("Testing TxPLL SPI, Mask 0x55:");
  m_frmTxPLL->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dRegTest->Compare(m_frmTxPLL->GetPrData());
  dRegTest->AddLine("");

  //Check RxPLL
  dRegTest->AddLine("Testing RxPLL SPI, Mask 0xAA:");
  m_frmRxPLL->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
  dRegTest->Compare(m_frmRxPLL->GetPrData());

  dRegTest->AddLine("Testing RxPLL SPI, Mask 0x55:");
  m_frmRxPLL->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
  dRegTest->Compare(m_frmRxPLL->GetPrData());
  dRegTest->AddLine("");

  //Check Top
  dRegTest->AddLine("Testing Top SPI, Mask 0xAA:");
  m_frmTop->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTop->GetPrData());
  dRegTest->Compare(m_frmTop->GetPrData());

  dRegTest->AddLine("Testing Top SPI, Mask 0x55:");
  m_frmTop->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTop->GetPrData());
  dRegTest->Compare(m_frmTop->GetPrData());
  dRegTest->AddLine("");

  //x RestoreAllSPIClocks();

  //Download current configuration from GUI
  tbtnDownloadClick(Application);


  //==== VTUNE test ====//
  int iCmpMin, iCmpMax;
  //Enable SoftTX
  bSoftTx = m_frmTop->CustSet_SofTxOnOff(true);
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  //Enable TxPLL clock
  EnableSPIClockByMask(0x01);

  //Sleep(1000);


  //Apply reset
  //dSerPort->SPI_Rst();
  //x EnableAllSPIClocks();

  //Enable TxPLL clock
  //EnableSPIClockByMask(0x01);
  //Enable SoftTX
  //bSoftTxRx = m_frmTop->CustSet_SofTxOnOff(true);
  //dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);

  //Check TxPLL VTUNE
  dRegTest->AddLine("Testing TxPLL VTUNE registers:");
  iCmpMin = m_frmTxPLL->GetVTuneState(1, 0);
  iCmpMax = m_frmTxPLL->GetVTuneState(4, 63);
  dRegTest->Comparators(iCmpMin, iCmpMax);
  dRegTest->AddLine("");

  RestoreAllSPIClocks();

  Sleep(5);
  //Restore SoftTX Enable
  m_frmTop->CustSet_SofTxOnOff(bSoftTx);
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  //Enable RxPLL clock
  EnableSPIClockByMask(0x04);
  //Enable SoftRX
  bSoftRx = m_frmTop->CustSet_SofRxOnOff(true);
  dSerPort->SPI_Wr(m_frmTop->GetPrData());
  Sleep(5);

  //Check RxPLL VTUNE
  dRegTest->AddLine("Testing RxPLL VTUNE registers:");
  iCmpMin = m_frmRxPLL->GetVTuneState(1, 0);
  iCmpMax = m_frmRxPLL->GetVTuneState(4, 63);
  dRegTest->Comparators(iCmpMin, iCmpMax);
  dRegTest->AddLine("");

  //Restore SoftRX Enable
  //m_frmTop->CustSet_SofRxOnOff(bSoftTxRx);
  //dSerPort->SPI_Wr(m_frmTop->GetPrData());

  RestoreAllSPIClocks();

  //Download current configuration from GUI
  tbtnDownloadClick(Application);

  //delete dRegTest;
  return true;
};

//---------------------------------------------------------------------------
// Register Map Test
//---------------------------------------------------------------------------
bool TfrmMain::TestRegistersTrial()
{
  TdRegTest *dRegTest = new TdRegTest(Application);
  dRegTest->Show();

  //goto RxPLL;
  
  //x EnableAllSPIClocks();
for(int i=0; i<100; i++)
{
  //Check TxRF
  dRegTest->AddLine("Testing TxRF SPI, Mask 0xAA:");
  m_frmTxRf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dRegTest->Compare(m_frmTxRf->GetPrData());

  dRegTest->AddLine("Testing TxRF SPI, Mask 0x55:");
  m_frmTxRf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxRf->GetPrData());
  dRegTest->Compare(m_frmTxRf->GetPrData());
  dRegTest->AddLine("");

  //Check RxFE
  dRegTest->AddLine("Testing RxFE SPI, Mask 0xAA:");
  m_frmRxFe->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dRegTest->Compare(m_frmRxFe->GetPrData());

  dRegTest->AddLine("Testing RxFE SPI, Mask 0x55:");
  m_frmRxFe->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxFe->GetPrData());
  dRegTest->Compare(m_frmRxFe->GetPrData());
  dRegTest->AddLine("");

  //Check RxVGA2
  dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
  m_frmRxVga2->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dRegTest->Compare(m_frmRxVga2->GetPrData());

  dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
  m_frmRxVga2->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxVga2->GetPrData());
  dRegTest->Compare(m_frmRxVga2->GetPrData());
  dRegTest->AddLine("");

  //Check RxLPF
  dRegTest->AddLine("Testing RxLPF SPI, Mask 0xAA:");
  m_frmRxLpf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dRegTest->Compare(m_frmRxLpf->GetPrData());

  dRegTest->AddLine("Testing RxLPF SPI, Mask 0x55:");
  m_frmRxLpf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxLpf->GetPrData());
  dRegTest->Compare(m_frmRxLpf->GetPrData());
  dRegTest->AddLine("");

  //Check TxLPF
  dRegTest->AddLine("Testing TxLPF SPI, Mask 0xAA:");
  m_frmTxLpf->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dRegTest->Compare(m_frmTxLpf->GetPrData());

  dRegTest->AddLine("Testing TxLPF SPI, Mask 0x55:");
  m_frmTxLpf->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxLpf->GetPrData());
  dRegTest->Compare(m_frmTxLpf->GetPrData());
  dRegTest->AddLine("");

  //Check TxPLL
  dRegTest->AddLine("Testing TxPLL SPI, Mask 0xAA:");
  m_frmTxPLL->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dRegTest->Compare(m_frmTxPLL->GetPrData());

  dRegTest->AddLine("Testing TxPLL SPI, Mask 0x55:");
  m_frmTxPLL->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmTxPLL->GetPrData());
  dRegTest->Compare(m_frmTxPLL->GetPrData());
  dRegTest->AddLine("");

//RxPLL:
//m_frmRxPLL->RT_SetTestMask(0x55);
//m_frmRxPLL->RT_SetTestMask(0xAA);

//for(int i=0; i<100; i++)
//{
  //Check RxPLL
  dRegTest->AddLine("Testing RxPLL SPI, Mask 0xAA:");
  m_frmRxPLL->RT_SetTestMask(0xAA);
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
  dRegTest->Compare(m_frmRxPLL->GetPrData());
//};
//return true;

  dRegTest->AddLine("Testing RxPLL SPI, Mask 0x55:");
  m_frmRxPLL->RT_SetTestMask(0x55);
  dSerPort->SPI_Rd(m_frmRxPLL->GetPrData());
  dRegTest->Compare(m_frmRxPLL->GetPrData());
  dRegTest->AddLine("");


  //x RestoreAllSPIClocks();
};


  //Download current configuration from GUI
  tbtnDownloadClick(Application);

  return true;


  //==== VTUNE test ====//
  int iCmpMin, iCmpMax;

  //Apply reset
  //dSerPort->SPI_Rst();
  Sleep(5);
  //x EnableAllSPIClocks();

  //Check TxPLL VTUNE
  dRegTest->AddLine("Testing TxPLL VTUNE registers:");
  iCmpMin = m_frmTxPLL->GetVTuneState(1, 0);
  iCmpMax = m_frmTxPLL->GetVTuneState(4, 63);
  dRegTest->Comparators(iCmpMin, iCmpMax);
  dRegTest->AddLine("");

  //Check RxPLL VTUNE
  dRegTest->AddLine("Testing RxPLL VTUNE registers:");
  iCmpMin = m_frmRxPLL->GetVTuneState(1, 0);
  iCmpMax = m_frmRxPLL->GetVTuneState(4, 63);
  dRegTest->Comparators(iCmpMin, iCmpMax);
  dRegTest->AddLine("");

  //x RestoreAllSPIClocks();

  //Download current configuration from GUI
  tbtnDownloadClick(Application);

  //delete dRegTest;
  return true;
};

//---------------------------------------------------------------------------
void __fastcall TfrmMain::RegisterTest1Click(TObject *Sender)
{
  TestRegisters();
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuRegTestLongClick(TObject *Sender)
{
  TestRegistersTrial();
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void TfrmMain::UpdateVerRevMask()
{
  char maddr = 0x00;      //Top
  char raddr = 0x04;
  int tmp;
  String Str;

  char cVer;
  char cRev;
  char cMask;

  char rez = dSerPort->SPI_Rd_OneByte(maddr | raddr);

  Str = "Chip Ver: ";
  tmp = (rez >> 4) & 0x0F;
  cVer = (char)tmp;
  Str = Str + tmp;
  Str = Str + " Rev: ";
  tmp = rez & 0x0F;
  cRev = (char)tmp;
  Str = Str + tmp;
  //sbMain->Panels->Items[3]->Text = Str;

  //Read Mask version
  raddr = 0x0E;
  rez = dSerPort->SPI_Rd_OneByte(maddr | raddr);
  cMask = (char)rez;
  Str = Str + " Msk: ";
  tmp = rez;
  Str = Str + tmp;
  sbMain->Panels->Items[3]->Text = Str;


  m_frmRxLpf->UpdateVerRevMask(cVer, cRev, cMask);
  m_frmTxLpf->UpdateVerRevMask(cVer, cRev, cMask);
  m_frmTxRf->UpdateVerRevMask(cVer, cRev, cMask);
  m_frmRxVga2->UpdateVerRevMask(cVer, cRev, cMask);

}
//---------------------------------------------------------------------------

