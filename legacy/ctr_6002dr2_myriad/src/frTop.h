// -----------------------------------------------------------------------------
// FILE: 		    frTop.h
// DESCRIPTION:	Header for frTop.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frTopH
#define frTopH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include "common.h"
#include "RXSwitch.hpp"
#include <fstream>
#include <inifiles.hpp>
using namespace std;

//---------------------------------------------------------------------------
class TfrmTop : public TFrame
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
	TGroupBox *GroupBox1;
	TCheckBox *chbPwrTopMods;
	TCheckBox *chbPwrSoftTx;
	TCheckBox *chbPwrSoftRx;
	TCheckBox *chbPwrLpfCal;
	TCheckBox *chbPwrRfLbsw;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *Label2;
	TCheckBox *chkLpfCalRst;
	TCheckBox *chkLpfCalEnEnf;
	TCheckBox *chkLpfCalEn;
	TComboBox *cmbLpfCalCode;
	TComboBox *cmbLpfCalBw;
	TRadioGroup *rgrDecode;
	TRadioGroup *rgrSpiMode;
	TRadioGroup *rgrDsmRst;
	TGroupBox *GroupBox4;
	TCheckBox *chbRxTestModeEn;
	TRadioGroup *rgrRFLB;
	TGroupBox *GroupBox7;
	TCheckListBox *chbSpiClkBuf;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox8;
	TRxSwitch *swReset;
  TLabel *Label8;
  TRadioGroup *rgrBBLB;
  TCheckBox *chbPDXCOBUF;
  TCheckBox *chbSLFBXCOBUF;
  TCheckBox *chbBYPXCOBUF;
  TRadioGroup *rgrRXOUTSW;
  TRadioGroup *rgrFDDTDD;
  TRadioGroup *rgrTDDMOD;
  TCheckBox *chbPD_CLKLPFCAL;
  TRadioGroup *rgrCLKSEL_LPFCAL;
  TGroupBox *GroupBox5;
  TButton *btnReadRCCALVal;
  TLabel *Label9;
  TLabel *lblRCCAL_LPFCAL;
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall rgrSpiModeClick(TObject *Sender);
	void __fastcall rgrDsmRstClick(TObject *Sender);
	void __fastcall chbRxTestModeEnClick(TObject *Sender);
	void __fastcall chbSpiClkBufClick(TObject *Sender);
	void __fastcall rgrRFLBClick(TObject *Sender);
	void __fastcall chkLpfCalRstClick(TObject *Sender);
	void __fastcall chkLpfCalEnClick(TObject *Sender);
	void __fastcall chkLpfCalEnEnfClick(TObject *Sender);
	void __fastcall cmbLpfCalCodeChange(TObject *Sender);
	void __fastcall cmbLpfCalBwChange(TObject *Sender);
	void __fastcall chbPwrTopModsClick(TObject *Sender);
	void __fastcall chbPwrSoftTxClick(TObject *Sender);
	void __fastcall chbPwrSoftRxClick(TObject *Sender);
	void __fastcall chbPwrLpfCalClick(TObject *Sender);
	void __fastcall chbPwrRfLbswClick(TObject *Sender);
	void __fastcall cmbDCCalAddrChange(TObject *Sender);
	void __fastcall cmbCalValChange(TObject *Sender);
	void __fastcall btnDCRstClbrClick(TObject *Sender);
	void __fastcall btnDCLoadValClick(TObject *Sender);
	void __fastcall btnDCStartClbrClick(TObject *Sender);
	void __fastcall btnDCReadValClick(TObject *Sender);
	void __fastcall swResetOn(TObject *Sender);
	void __fastcall swResetOff(TObject *Sender);
  void __fastcall rgrBBLBClick(TObject *Sender);
  void __fastcall rgrCLKSEL_LPFCALClick(TObject *Sender);
  void __fastcall chbPD_CLKLPFCALClick(TObject *Sender);
  void __fastcall rgrRXOUTSWClick(TObject *Sender);
  void __fastcall rgrFDDTDDClick(TObject *Sender);
  void __fastcall rgrTDDMODClick(TObject *Sender);
  void __fastcall chbPDXCOBUFClick(TObject *Sender);
  void __fastcall chbSLFBXCOBUFClick(TObject *Sender);
  void __fastcall chbBYPXCOBUFClick(TObject *Sender);
  void __fastcall btnReadRCCALValClick(TObject *Sender);
private:	// User declarations

protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;
  int m_DCClbrV[DCClbrCnt];

  void MakeData(int rAddr);

public:		// User declarations
	__fastcall TfrmTop(TComponent* Owner);
  __fastcall ~TfrmTop(void);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr);
  sPrData *GetPrData(){return &m_psD;};
  void MakeWriteAll();
  void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  void MakeRegisterFile(ofstream &out);   //Writes register map to the file. According to the customer wish.
  bool ChipVsGui(ofstream &out, String Caption, bool bWrAll); //When bWrAll = false, it writes the differences between Chip and GUI, when true, writes all configuration.
  bool SetGUIUnderReadback();
  void UpdateFormData();
  void UpdateRCCALData();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);
  void DownloadAllDCCalValues();

  int GetCalVal(int Addr);
  void SetCalVal(int Addr, int Val);
  void SetCalAddr(int Addr);
  void StartCalibration(int Addr);
  char GetCalStatus();
  void SetCalDefaults();

  void EnableAllSPIClocks();    //Enables all SPI clock buffers
  void EnableSPIClocksByMask(int mask);    //Enables all SPI clock buffers by mask
  void RestoreAllSPIClocks();   //Restores SPI clock bufer states according to GUI settings

  void CustSet_Tia2OutON();
  void CustSet_Tia2OutOFF();
  void CustSet_LPFBandwidth(int ind);
  void CustSet_SetRFLB(int ind);
  void CustSet_SetBBLB(int ind);
  void CustSet_TopPowerON(bool On);
  void CustSet_EnableLPFCAL(bool On);
  void CustSet_ResetLPFCAL(bool Active);
  void CustGet_LPFCALVal(int &DCCALVal, int &LPFCALVal);
  bool CustGet_PD_CLKLPFCAL();
  void CustSet_PD_CLKLPFCAL(bool Val);
  void CustSet_rgrRXOUTSW(int Ind);
  void CustSet_PLLCLKOUT(bool Enabled);
  bool CustSet_SofTxOnOff(bool On);
  bool CustSet_SofRxOnOff(bool On);

  int GetLPFTuningClockInd();
  void SetLPFTuningClockInd(int Ind);

  void RT_SetTestMask(char Mask);
  //int  CustSet_Get

};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmTop *frmTop;
//---------------------------------------------------------------------------
#endif
