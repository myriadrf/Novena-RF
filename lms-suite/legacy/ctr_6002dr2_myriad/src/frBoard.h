// -----------------------------------------------------------------------------
// FILE: 		    frBoard.h
// DESCRIPTION:	Header for frBoard.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frBoardH
#define frBoardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RXSpin.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <fstream>
#include <iostream>
#include "common.h"
#include <dir.h>


using namespace std;

//---------------------------------------------------------------------------
class TfrmBoard : public TFrame
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TRxSpinEdit *txtRCnt;
  TLabel *Label1;
  TComboBox *cmbABW;
  TLabel *Label16;
  TLabel *Label2;
  TComboBox *cmbLDP;
  TGroupBox *GroupBox3;
  TLabel *Label3;
  TLabel *Label4;
  TRxSpinEdit *txtNCnt;
  TComboBox *cmbCPG;
  TGroupBox *GroupBox5;
  TLabel *Label6;
  TRadioGroup *rgrCR_i;
  TRadioGroup *rgrPD1_i;
  TRadioGroup *rgrPD2_i;
  TComboBox *cmbMOC_i;
  TRadioGroup *rgrPDP_i;
  TRadioGroup *rgrCPS_i;
  TLabel *Label7;
  TComboBox *cmbTC_i;
  TLabel *Label8;
  TComboBox *cmbCS1_i;
  TComboBox *cmbCS2_i;
  TLabel *Label9;
  TGroupBox *GroupBox4;
  TLabel *Label5;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TRadioGroup *rgrCR_f;
  TRadioGroup *rgrPD1_f;
  TRadioGroup *rgrPD2_f;
  TComboBox *cmbMOC_f;
  TRadioGroup *rgrPDP_f;
  TRadioGroup *rgrCPS_f;
  TComboBox *cmbTC_f;
  TComboBox *cmbCS1_f;
  TComboBox *cmbCS2_f;
  TLabel *Label13;
  TComboBox *cmbFL_f;
  TLabel *Label14;
  TComboBox *cmbFL_i;
  TGroupBox *GroupBox6;
  TLabel *Label15;
  TRxSpinEdit *txtFref;
  TRxSpinEdit *txtFvco;
  TLabel *Label17;
  TButton *btnCalc;
  TButton *btnDownload;
  TLabel *Label18;
  TLabel *lblFvco;
  TLabel *lblFcomp;
  TLabel *Label19;
  TLabel *Label20;
  TButton *btnSaveRFIF;
  TSaveDialog *dlgSave;
  void __fastcall btnCalcClick(TObject *Sender);
  void __fastcall txtRCntChange(TObject *Sender);
  void __fastcall cmbABWChange(TObject *Sender);
  void __fastcall cmbLDPChange(TObject *Sender);
  void __fastcall txtNCntChange(TObject *Sender);
  void __fastcall cmbCPGChange(TObject *Sender);
  void __fastcall rgrCR_fClick(TObject *Sender);
  void __fastcall rgrCPS_fClick(TObject *Sender);
  void __fastcall rgrPD1_fClick(TObject *Sender);
  void __fastcall rgrPD2_fClick(TObject *Sender);
  void __fastcall cmbMOC_fChange(TObject *Sender);
  void __fastcall rgrPDP_fClick(TObject *Sender);
  void __fastcall cmbTC_fChange(TObject *Sender);
  void __fastcall cmbFL_fChange(TObject *Sender);
  void __fastcall cmbCS1_fChange(TObject *Sender);
  void __fastcall cmbCS2_fChange(TObject *Sender);
  void __fastcall rgrCR_iClick(TObject *Sender);
  void __fastcall rgrCPS_iClick(TObject *Sender);
  void __fastcall rgrPD1_iClick(TObject *Sender);
  void __fastcall rgrPD2_iClick(TObject *Sender);
  void __fastcall cmbMOC_iChange(TObject *Sender);
  void __fastcall rgrPDP_iClick(TObject *Sender);
  void __fastcall cmbTC_iChange(TObject *Sender);
  void __fastcall cmbFL_iChange(TObject *Sender);
  void __fastcall cmbCS1_iChange(TObject *Sender);
  void __fastcall cmbCS2_iChange(TObject *Sender);
  void __fastcall btnDownloadClick(TObject *Sender);
  void __fastcall txtFrefChange(TObject *Sender);
  void __fastcall txtFvcoChange(TObject *Sender);
  void __fastcall btnSaveRFIFClick(TObject *Sender);
private:	// User declarations
protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;

  void MakeData(int rAddr);
  void UpdateADFFvco();
  void CalculateRN();

public:		// User declarations
  __fastcall TfrmBoard(TComponent* Owner);
  __fastcall ~TfrmBoard(void);

  sPrData *GetPrData(){return &m_psD;};

  void SetGuiDefaults();
  void Initialize(char MAddr);
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmBoard *frmBoard;
//---------------------------------------------------------------------------
#endif
