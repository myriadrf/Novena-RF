// -----------------------------------------------------------------------------
// FILE: 		    frTxLpf.h
// DESCRIPTION:	Header for frTxLpf.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frTxLpfH
#define frTxLpfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "common.h"
#include "frADDC.h"
#include <fstream>
#include <inifiles.hpp>
using namespace std;
//---------------------------------------------------------------------------
class TfrmTxLpf : public TFrame
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
	TCheckBox *chbPwrLpfMods;
	TCheckBox *chbPwrLpf;
	TCheckBox *chbPwrDCDac;
	TCheckBox *chbPwrDCRef;
	TCheckBox *chbPwrDCCmpr;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cmbDCOffset;
	TComboBox *cmbRcCal;
	TGroupBox *GroupBox2;
	TComboBox *cmbLpfBw;
	TRadioGroup *rgrLpfByp;
  TCheckBox *chbTX_DACBUF_EN;
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall cmbLpfBwChange(TObject *Sender);
	void __fastcall cmbDCOffsetChange(TObject *Sender);
	void __fastcall cmbRcCalChange(TObject *Sender);
	void __fastcall chbPwrLpfClick(TObject *Sender);
	void __fastcall chbPwrDCDacClick(TObject *Sender);
	void __fastcall chbPwrDCRefClick(TObject *Sender);
	void __fastcall chbPwrDCCmprClick(TObject *Sender);
	void __fastcall cmbDCCalAddrChange(TObject *Sender);
	void __fastcall cmbCalValChange(TObject *Sender);
	void __fastcall btnDCRstClbrClick(TObject *Sender);
	void __fastcall btnDCLoadValClick(TObject *Sender);
	void __fastcall btnDCStartClbrClick(TObject *Sender);
	void __fastcall chbPwrLpfModsClick(TObject *Sender);
	void __fastcall rgrLpfBypClick(TObject *Sender);
	void __fastcall btnDCReadValClick(TObject *Sender);
  void __fastcall chbTX_DACBUF_ENClick(TObject *Sender);
protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;
  int m_DCClbrV[DCClbrCnt];
  TfrmADDC *m_frmADDC;
  char m_cVer;
  char m_cRev;
  char m_cMask;  
  void MakeData(int rAddr);



public:		// User declarations
	__fastcall TfrmTxLpf(TComponent* Owner);
  __fastcall ~TfrmTxLpf(void);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr, TfrmADDC *ADDC);
  sPrData *GetPrData(){return &m_psD;};
  void MakeWriteAll();
  bool ChipVsGui(ofstream &out, String Caption, bool bWrAll);
  void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  bool SetGUIUnderReadback();
  void UpdateFormData();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);
  void MakeRegisterFile(ofstream &out);
  void DownloadAllDCCalValues();
  void JoinADDC(int Message);

  int GetCalVal(int Addr);
  void SetCalVal(int Addr, int Val);
  void SetCalAddr(int Addr);
  void StartCalibration(int Addr);
  char GetCalStatus();
  void SetCalDefaults();

  int  CustGet_DecodeState();
  void CustSet_DecodeState(int ind);
  int  CustGet_LPFTestState();
  void CustSet_LPFTestState(int ind);

  bool CustGet_PwrLpfMods();
  bool CustGet_PwrLpf();
  bool CustGet_PwrDCDac();
  bool CustGet_PwrDCRef();
  bool CustGet_PwrDCCmpr();
  void CustGet_PwrLpfMods(bool state);
  void CustGet_PwrLpf(bool state);
  void CustGet_PwrDCDac(bool state);
  void CustGet_PwrDCRef(bool state);
  void CustGet_PwrDCCmpr(bool state);

  void CustSet_BypassLpfON();
  void CustSet_BypassLpfOFF();
  void CustSet_LpfPowerON();
  void CustSet_LpfPowerOFF();

  void CustSet_EnableDCOffsetCompOnly();
  void CustSet_RestoreDCOffsetCompOnly();
  void CustSet_BypassLPFOnlyOn();
  void CustSet_BypassLPFOnlyOff();
  void CustSet_LPFCALVAL(int Val);
  void CustSet_LPFDCVAL(int Val);

  void RT_SetTestMask(char Mask);
  void UpdateVerRevMask(char Ver, char Rev, char Mask);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmTxLpf *frmTxLpf;
//---------------------------------------------------------------------------
#endif
