// -----------------------------------------------------------------------------
// FILE: 		    frTxRF.h
// DESCRIPTION:	Header for frTxRF.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------


//---------------------------------------------------------------------------
#ifndef frTxRfH
#define frTxRfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "common.h"
#include <fstream>
#include <inifiles.hpp>
using namespace std;
//---------------------------------------------------------------------------
class TfrmTxRf : public TFrame
{
__published:	// IDE-managed Components
	TRadioGroup *rgrDecode;
	TGroupBox *GroupBox1;
	TCheckBox *chbPwrTxRfMods;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TComboBox *cmbVga1G_u;
	TLabel *Label1;
	TComboBox *cmbVga1DcI;
	TLabel *Label2;
	TComboBox *cmbVga1DcQ;
	TLabel *Label4;
	TComboBox *cmbVga1G_t;
	TGroupBox *GroupBox3;
	TLabel *Label5;
	TComboBox *cmbVga2G_u;
	TLabel *Label6;
	TComboBox *cmbVga2G_t;
  TRadioGroup *rgrLOOPBBEN;
  TCheckBox *chbPD_DRVAUX;
  TCheckBox *chbPD_PKDET;
  TRadioGroup *rgrPA;
  TGroupBox *GroupBox4;
  TLabel *Label7;
  TComboBox *cmbENVD;
  TLabel *Label8;
  TComboBox *cmbENVD2;
  TLabel *Label9;
  TComboBox *cmbPKDBW;
  TCheckBox *chbFST_PKDET;
  TGroupBox *GroupBox5;
  TCheckBox *chbFST_TXHFBIAS;
  TLabel *Label10;
  TComboBox *cmbICT_TXLOBUF;
  TLabel *Label11;
  TComboBox *cmbVBCAS_TXDRV;
  TLabel *Label12;
  TComboBox *cmbICT_TXMIX;
  TLabel *Label13;
  TComboBox *cmbICT_TXDRV;
  TCheckBox *chbPwrVga1_I;
  TCheckBox *chbPwrVga1_Q;
  TCheckBox *chbPwrVga2;
  TCheckBox *chbPD_TXLOBUF;
  TCheckBox *chbPD_TXDRV;
	void __fastcall chbPwrTxRfModsClick(TObject *Sender);
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall cmbVga1G_uChange(TObject *Sender);
	void __fastcall cmbVga1DcIChange(TObject *Sender);
	void __fastcall cmbVga1DcQChange(TObject *Sender);
	void __fastcall rgrPAClick(TObject *Sender);
	void __fastcall cmbVga2G_uChange(TObject *Sender);
	void __fastcall chbPwrVga1_IClick(TObject *Sender);
	void __fastcall chbPwrVga2Click(TObject *Sender);
	void __fastcall cmbVga1G_tChange(TObject *Sender);
	void __fastcall cmbVga2G_tChange(TObject *Sender);
  void __fastcall chbPwrVga1_QClick(TObject *Sender);
  void __fastcall rgrLOOPBBENClick(TObject *Sender);
  void __fastcall chbPD_DRVAUXClick(TObject *Sender);
  void __fastcall chbPD_PKDETClick(TObject *Sender);
  void __fastcall cmbENVDChange(TObject *Sender);
  void __fastcall cmbENVD2Change(TObject *Sender);
  void __fastcall cmbPKDBWChange(TObject *Sender);
  void __fastcall chbFST_PKDETClick(TObject *Sender);
  void __fastcall chbFST_TXHFBIASClick(TObject *Sender);
  void __fastcall cmbICT_TXLOBUFChange(TObject *Sender);
  void __fastcall cmbVBCAS_TXDRVChange(TObject *Sender);
  void __fastcall cmbICT_TXMIXChange(TObject *Sender);
  void __fastcall cmbICT_TXDRVChange(TObject *Sender);
  void __fastcall chbPD_TXLOBUFClick(TObject *Sender);
  void __fastcall chbPD_TXDRVClick(TObject *Sender);
protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;
  char m_cVer;
  char m_cRev;
  char m_cMask;
  void MakeData(int rAddr);

public:		// User declarations
	__fastcall TfrmTxRf(TComponent* Owner);
  __fastcall ~TfrmTxRf(void);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr);
  sPrData *GetPrData(){return &m_psD;};
  void MakeWriteAll();
  bool ChipVsGui(ofstream &out, String Caption, bool bWrAll);
  void MakeRegisterFile(ofstream &out);
  void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  bool SetGUIUnderReadback();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);

  void RT_SetTestMask(char Mask);

  void CustSet_cmbICT_TXLOBUF(int Ind);
  void UpdateVerRevMask(char Ver, char Rev, char Mask);

};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmTxRf *frmTxRf;
//---------------------------------------------------------------------------
#endif
