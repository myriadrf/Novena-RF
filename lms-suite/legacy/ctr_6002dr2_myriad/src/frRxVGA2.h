// -----------------------------------------------------------------------------
// FILE: 		    frRxVGA2.h
// DESCRIPTION:	Header for frRxVHA2.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frRxVGA2H
#define frRxVGA2H
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
class TfrmRxVGA2 : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox6;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *lbDC_REGVAL;
	TLabel *lblDC_LOCK;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *lblDC_CLBR_DONE;
	TLabel *Label15;
	TLabel *lblDC_UD;
	TLabel *Label17;
	TButton *btnDCStartClbr;
	TButton *btnDCLoadVal;
	TButton *btnDCRstClbr;
	TComboBox *cmbDCCalAddr;
	TButton *btnDCReadVal;
	TComboBox *cmbCalVal;
	TRadioGroup *rgrDecode;
	TGroupBox *GroupBox1;
	TCheckBox *chbPwrVGA2Mods;
	TCheckBox *chbPwrDCCurrR;
	TCheckBox *chbPwrDCDACB;
	TCheckBox *chbPwrDCCmpB;
	TCheckBox *chbPwrDCDACA;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label4;
	TComboBox *cmbVga2G_u;
	TComboBox *cmbVga2GA_t;
	TComboBox *cmbVga2GB_t;
	TCheckBox *chbPwrDCCmpA;
	TCheckBox *chbPwrBG;
	TCheckBox *chbPwrBypAB;
	TCheckBox *chbPwrBypB;
	TCheckBox *chbPwrBypA;
	TCheckBox *chbPwrCurrRef;
  TGroupBox *GroupBox3;
  TComboBox *cmbVCM;
	void __fastcall chbPwrVGA2ModsClick(TObject *Sender);
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall cmbVga2G_uChange(TObject *Sender);
	void __fastcall chbPwrDCCurrRClick(TObject *Sender);
	void __fastcall chbPwrDCDACBClick(TObject *Sender);
	void __fastcall chbPwrDCCmpBClick(TObject *Sender);
	void __fastcall chbPwrDCDACAClick(TObject *Sender);
	void __fastcall chbPwrDCCmpAClick(TObject *Sender);
	void __fastcall chbPwrBGClick(TObject *Sender);
	void __fastcall chbPwrBypABClick(TObject *Sender);
	void __fastcall chbPwrBypBClick(TObject *Sender);
	void __fastcall chbPwrBypAClick(TObject *Sender);
	void __fastcall chbPwrCurrRefClick(TObject *Sender);
	void __fastcall cmbVga2GB_tChange(TObject *Sender);
	void __fastcall cmbVga2GA_tChange(TObject *Sender);
	void __fastcall cmbDCCalAddrChange(TObject *Sender);
	void __fastcall cmbCalValChange(TObject *Sender);
	void __fastcall btnDCRstClbrClick(TObject *Sender);
	void __fastcall btnDCLoadValClick(TObject *Sender);
	void __fastcall btnDCStartClbrClick(TObject *Sender);
	void __fastcall btnDCReadValClick(TObject *Sender);
  void __fastcall cmbVCMChange(TObject *Sender);
protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;
  int m_DCClbrV[DCClbrCnt];
  char m_cVer;
  char m_cRev;
  char m_cMask;

  void MakeData(int rAddr);
  //int GetCalVal(int Addr);
  //void SetCalVal(int Addr, int Val);

  //VCM code to combobox index recalculation
  int VCM2CMB(int code);
  int CMB2VCM(int code);


public:		// User declarations
	__fastcall TfrmRxVGA2(TComponent* Owner);
  __fastcall ~TfrmRxVGA2(void);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr);
  sPrData *GetPrData(){return &m_psD;};
  void MakeWriteAll();
  bool ChipVsGui(ofstream &out, String Caption, bool bWrAll);
  void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  bool SetGUIUnderReadback();
  void MakeRegisterFile(ofstream &out);
  void UpdateFormData();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);
  void DownloadAllDCCalValues();

  int GetCalVal(int Addr);
  void SetCalVal(int Addr, int Val);
  void SetCalAddr(int Addr);
  void StartCalibration(int Addr);
  char GetCalStatus();
  void SetCalDefaults();

  void CustSet_RxVGA2PowerON();
  void CustSet_RxVGA2PowerOFF();

  void CustSet_cmbVCM(int Ind);

  void RT_SetTestMask(char Mask);

  int GetRXVGA2Gain();
  void SetRXVGA2Gain(int Ind);

  void UpdateVerRevMask(char Ver, char Rev, char Mask);

};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmRxVGA2 *frmRxVGA2;
//---------------------------------------------------------------------------
#endif
