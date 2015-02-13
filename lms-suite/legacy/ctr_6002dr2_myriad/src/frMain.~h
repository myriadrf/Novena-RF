// -----------------------------------------------------------------------------
// FILE: 		    frMain.h
// DESCRIPTION:	Header for frMain.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------


//----------------------------------------------------------------------------
#ifndef frMainH
#define frMainH
//----------------------------------------------------------------------------
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>

#include "frTop.h"
#include "frTxLpf.h"
#include "frTxRf.h"
#include "frRxVGA2.h"
#include "frRxFe.h"
#include "frTxPLL.h"
#include "intercom.h"
#include "frCustomer.h"
#include "clUARFCN.h"
#include "frADDC.h"
#include "frTxRf.h"
#include "frBoard.h"
#include "frBoard2.h"

//#define CUSTOMER_MODE

//----------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:
  TOpenDialog *dlgOpen;
  TSaveDialog *dlgSave;
    TToolBar *ToolBar1;
    TToolButton *ToolButton9;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TActionList *ActionList1;
    TAction *FileNew1;
    TAction *FileOpen1;
    TAction *FileSave1;
    TAction *FileSaveAs1;
    TAction *FileExit1;
    TEditCut *EditCut1;
    TEditCopy *EditCopy1;
    TEditPaste *EditPaste1;
    TAction *HelpAbout1;
  TStatusBar *sbMain;
    TImageList *ImageList1;
    TMainMenu *MainMenu1;
  TMenuItem *file;
  TMenuItem *mnuNew;
    TMenuItem *FileOpenItem;
    TMenuItem *FileSaveItem;
    TMenuItem *FileSaveAsItem;
    TMenuItem *N1;
    TMenuItem *FileExitItem;
    TMenuItem *Edit1;
    TMenuItem *CutItem;
    TMenuItem *CopyItem;
    TMenuItem *PasteItem;
    TMenuItem *Help1;
    TMenuItem *HelpAboutItem;
  TToolButton *ToolButton7;
  TToolButton *tbtnDownload;
  TMenuItem *Options1;
  TMenuItem *mnuAutoDwnld;
  TMenuItem *mnuReadConfiguration;
  TPageControl *pcSPIS;
  TTabSheet *tabTop;
  TfrmTop *m_frmTop;
  TTabSheet *tabTxPLL;
  TTabSheet *tabRxPLL;
  TTabSheet *tabTxLPF;
  TTabSheet *tabTxRF;
  TTabSheet *tabRxLPF;
  TTabSheet *tabRxVGA2;
  TfrmRxVGA2 *m_frmRxVga2;
  TTabSheet *tabRxFE;
  TfrmRxFe *m_frmRxFe;
  TPanel *Panel1;
  TListBox *lbMsgs;
  TMenuItem *mnuRefClk;
  TTabSheet *tabCust;
  TfrmCustomer *m_frmCustomer;
  TMenuItem *N2;
  TMenuItem *ChipGUI1;
  TTabSheet *tabADDC;
  TfrmTxLpf *m_frmRxLpf;
  TMenuItem *mnuSaveRegisters;
  TMenuItem *N3;
  TMenuItem *GUIChip1;
  TMenuItem *ChipGUI2;
  TMenuItem *CommunicationSettings1;
  TMenuItem *Tools1;
  TMenuItem *RegisterTest1;
  TfrmADDC *m_frmADDC;
  TfrmTxRf *m_frmTxRf;
  TTabSheet *tabBoard;
  TMenuItem *mnuRegTestLong;
  TfrmBoard *m_frmBoard;
  TMenuItem *mnuReadRVF;
  TfrmTxPLL *m_frmRxPLL;
  TfrmTxPLL *m_frmTxPLL;
  TfrmTxLpf *m_frmTxLpf;
  TMenuItem *mnuReadRVF_hex;
  TMenuItem *mnuReadRVF_rfif;
  TMenuItem *N4;
        TTabSheet *Board2;
        TfrmBoard2 *m_frmBoard2;
  
  void __fastcall FileNew1Execute(TObject *Sender);
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall Save(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall mnuAutoDwnldClick(TObject *Sender);
  void __fastcall mnuReadConfigurationClick(TObject *Sender);
  void __fastcall tbtnDownloadClick(TObject *Sender);
  void __fastcall FileSaveAsItemClick(TObject *Sender);
  void __fastcall mnuRefClkClick(TObject *Sender);
  void __fastcall m_frmCustomercmbLNASEL_CustChange(TObject *Sender);
  void __fastcall m_frmCustomerbtnClbrTxClick(TObject *Sender);
  void __fastcall m_frmCustomerbtnClbrRxClick(TObject *Sender);
  void __fastcall m_frmCustomercmbBypassChange(TObject *Sender);
  void __fastcall m_frmCustomercmbLoopbackChange(TObject *Sender);
  void __fastcall m_frmCustomercmbTxBypassChange(TObject *Sender);
  void __fastcall m_frmCustomercmbRxBandsChange(TObject *Sender);
  void __fastcall m_frmCustomercmbULRXChanChange(TObject *Sender);
  void __fastcall m_frmCustomerbtnFChanULRX_BClick(TObject *Sender);
  void __fastcall m_frmCustomercmbDLTXBandsChange(TObject *Sender);
  void __fastcall m_frmCustomercmbDLTXChanChange(TObject *Sender);
  void __fastcall m_frmCustomerbtnDLTXFChan_BClick(TObject *Sender);
  void __fastcall m_frmCustomerbtnCalRxTIAClick(TObject *Sender);
  void __fastcall m_frmCustomerButton1Click(TObject *Sender);
  void __fastcall ChipGUI1Click(TObject *Sender);
  void __fastcall m_frmToprgrRFLBClick(TObject *Sender);
  void __fastcall mnuSaveRegistersClick(TObject *Sender);
  void __fastcall ChipGUI2Click(TObject *Sender);
  void __fastcall CommunicationSettings1Click(TObject *Sender);
  void __fastcall RegisterTest1Click(TObject *Sender);
  void __fastcall mnuRegTestLongClick(TObject *Sender);
  void __fastcall mnuReadRVFClick(TObject *Sender);
  void __fastcall mnuReadRVF_hexClick(TObject *Sender);
  void __fastcall mnuReadRVF_rfifClick(TObject *Sender);

public:
    virtual __fastcall TfrmMain(TComponent *AOwner);
    void slLogMesg(int num);

private:
	//ParallelPort *m_pPort;
  //cPortCtr *m_PortCtr;

  sPrData m_sInterPD;			//Interprocess communication data
  String m_sFileName;
  void setCurrentFileName(String fileName);
  void EnableAllSPIClocks();
  void EnableSPIClockByMask(int Mask);
  void RestoreAllSPIClocks();
  void SetLnaChain(int iChain);
  void SetBypassLoopback();
  bool TestRegisters();
  bool TestRegistersTrial();
  void CalLPFCore();

  bool FileIsNotEmpty(String filename);
  void LoadConfiguration(String sIniName);

  void __fastcall ShowReferenceClk(double Val);
  void SaveRefClkToReg(double Freq);
  double ReadRefClkFromReg(void);

  void LoadAdditionalSettings();
  void UpdateVerRevMask();
  void SaveUnderRVF_Format(int dec); //dec = 1 if format is decimal, dec = 0 if format is hexadecimal;
  void SaveUnderRFIF_Format(); 

private:
  CUARFCN m_UARFCNDef;   

private:
  int m_iRefVCnt;
  double *m_dFVco1;
  double *m_dFVco2;
  double *m_dFVco3;
  double *m_dFVco4;
  int *m_iCVco1;
  int *m_iCVco2;
  int *m_iCVco3;
  int *m_iCVco4;

  int m_sBypCurr;
  int m_sBypPrev;
  int m_sBBCurr;
  int m_sBBPrev;


protected:
  void __fastcall CMLog(TMessage &Message);
  void __fastcall CMRead(TMessage &Message);
  void __fastcall CMAutoDownload(TMessage &Message);
  void __fastcall CMResetAct(TMessage &Message);
  void __fastcall CMResetInAct(TMessage &Message);
  void __fastcall CMADDC2LPF(TMessage &Message);
  void __fastcall CMUpdateLNA(TMessage &Message);
  void __fastcall CMUpdatePA(TMessage &Message);
  void __fastcall CMSoftTxPD(TMessage &Message);
  void __fastcall CMSPIClkOnMask(TMessage Msg);
  void __fastcall CMSPIClkRestore(TMessage Msg);
  void __fastcall wmReset(TMessage Msg);
	void __fastcall wmWriteData(TMessage Msg);
  void __fastcall wmReadData(TMessage Msg);
	void __fastcall wmWR_Xil(TMessage Msg);
  void __fastcall wmRD_Xil(TMessage Msg);
	void __fastcall wmWR_AD9552(TMessage Msg);
  void __fastcall wmRD_AD9552(TMessage Msg);
	void __fastcall wmWR_AD7691(TMessage Msg);
  void __fastcall wmRD_AD7691(TMessage Msg);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(CM_LOG, TMessage, CMLog)
  MESSAGE_HANDLER(CM_READ, TMessage, CMRead)
  MESSAGE_HANDLER(CM_AUTODOWNLOAD, TMessage, CMAutoDownload)
  MESSAGE_HANDLER(CM_RSTACT, TMessage, CMResetAct)
  MESSAGE_HANDLER(CM_RSTINACT, TMessage, CMResetInAct)
  MESSAGE_HANDLER(CM_ADDC2LPF, TMessage, CMADDC2LPF)
  MESSAGE_HANDLER(CM_UPDATELNA, TMessage, CMUpdateLNA)
  MESSAGE_HANDLER(CM_UPDATEPA, TMessage, CMUpdatePA)
  MESSAGE_HANDLER(CM_SOFT_TX_PD, TMessage, CMSoftTxPD)
  MESSAGE_HANDLER(CM_SPICLKONMASK, TMessage, CMSPIClkOnMask)
  MESSAGE_HANDLER(CM_SPICLKRESTORE, TMessage, CMSPIClkRestore)
  MESSAGE_HANDLER(WM_Reset, TMessage, wmReset)
	MESSAGE_HANDLER(WM_WriteData, TMessage, wmWriteData)
  MESSAGE_HANDLER(WM_ReadData, TMessage, wmReadData)
	MESSAGE_HANDLER(WM_WR_Xil,    TMessage, wmWR_Xil)
  MESSAGE_HANDLER(WM_RD_Xil,    TMessage, wmRD_Xil)
	MESSAGE_HANDLER(WM_WR_AD9552, TMessage, wmWR_AD9552)
  MESSAGE_HANDLER(WM_RD_AD9552, TMessage, wmRD_AD9552)
	MESSAGE_HANDLER(WM_WR_AD7691, TMessage, wmWR_AD7691)
  MESSAGE_HANDLER(WM_RD_AD7691, TMessage, wmRD_AD7691)

END_MESSAGE_MAP(TControl)

};
//----------------------------------------------------------------------------
extern TfrmMain *frmMain;
//----------------------------------------------------------------------------
#endif
