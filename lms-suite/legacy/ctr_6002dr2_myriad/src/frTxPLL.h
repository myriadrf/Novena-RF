// -----------------------------------------------------------------------------
// FILE: 		    frTxPLL.h
// DESCRIPTION:	Header for frTxPLL.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------


//---------------------------------------------------------------------------
#ifndef frTxPLLH
#define frTxPLLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include "RXSpin.hpp"

#include "frFreqVsCap.h"
#include "common.h"
#include <ComCtrls.hpp>
#include <fstream>
#include <inifiles.hpp>
#include "dlgVcoCapLog.h"
using namespace std;

//---------------------------------------------------------------------------
// Save PLL settings while calibrating LPF CAL Core
//---------------------------------------------------------------------------
struct F320M_Data
{
  int F320M_rgrDecode;
  bool F320M_chbPwrPllMods;
  int F320M_rgrMODE;
  int F320M_cmbVCOCAP;
  int F320M_rgrSELVCO;
  int F320M_rgrFRANGE;
  double F320M_txtDesFreq;
};

//---------------------------------------------------------------------------
class TfrmTxPLL : public TFrame
{
__published:	// IDE-managed Components
	TRadioGroup *rgrDecode;
	TGroupBox *GroupBox2;
	TCheckBox *chbPwrPllMods;
	TCheckBox *chkENLAMP;
	TCheckBox *chkENLOBUF;
	TCheckBox *chkPFDPD;
	TCheckBox *chkENFEEDDIV;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cmbICHP;
	TComboBox *cmbOFFUP;
	TLabel *Label1;
	TComboBox *cmbOFFDOWN;
	TGroupBox *GroupBox4;
	TCheckBox *chkDITHEN;
	TLabel *Label2;
	TComboBox *cmbDITHN;
	TGroupBox *GroupBox5;
	TComboBox *cmbSELOUT;
	TGroupBox *GroupBox9;
	TComboBox *cmbVCOCAP;
  TButton *btnClbr;
  TButton *btnChoose;
  TCheckBox *cmbPD_VCOCOMP_SX;
  TGroupBox *GroupBox11;
  TCheckBox *chkOEN_TSTD_SX;
  TCheckBox *chkPASSEN_TSTOD_SD;
  TGroupBox *GroupBox12;
  TButton *btnReadVtune;
  TLabel *Label15;
  TLabel *Label18;
  TLabel *lblVTUNE_H;
  TLabel *lblVTUNE_L;
  TLabel *Label19;
  TLabel *Label21;
  TLabel *lblAutoTuneStatus;
  TButton *btnTune;
  TCheckBox *chkCapLog;
  TCheckBox *chkPFDCLKP;
  TCheckBox *chkTRI;
  TCheckBox *chkPOL;
  TPanel *Panel1;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TRadioGroup *rgrMODE;
  TGroupBox *grbOutFreq;
  TButton *btnCalc;
  TRxSpinEdit *txtDesFreq;
  TGroupBox *GroupBox8;
  TLabel *Label16;
  TLabel *Label17;
  TComboBox *cmbACODE;
  TComboBox *cmbBCODE;
  TGroupBox *GroupBox7;
  TLabel *Label6;
  TLabel *Label7;
  TLabel *Label8;
  TLabel *Label9;
  TLabel *Label10;
  TLabel *lblNint;
  TLabel *lblNfrac;
  TLabel *lblDiv;
  TLabel *lblROutF;
  TLabel *lblVcoF;
  TGroupBox *GroupBox10;
  TLabel *Label5;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label14;
  TLabel *lblN;
  TLabel *lblFvcoInt;
  TLabel *lblFvco2Int;
  TLabel *lblFvco4Int;
  TLabel *lblFvco8Int;
  TLabel *Label22;
  TLabel *lblFvco16Int;
  TRadioGroup *rgrSELVCO;
  TRadioGroup *rgrFRANGE;
  TTabSheet *TabSheet2;
  TButton *btnBSTART;
  TGroupBox *GroupBox1;
  TLabel *lblBSTATE;
  TButton *btnReadBISTState;
  TGroupBox *GroupBox6;
  TLabel *lblBSIG;
  TButton *Button1;
  TRadioGroup *rgrBCLKSEL;
  TRadioGroup *rgrBINSEL;
  TGroupBox *GroupBox13;
  TComboBox *cmbVOVCOREG;
  TLabel *Label23;
  TGroupBox *GroupBox14;
  TCheckBox *chbBYPVCOREG;
  TCheckBox *chbPDVCOREG;
  TCheckBox *chbFSTVCOBG;
  TCheckBox *chbAUTOBYP;
  TCheckBox *chbEN_PFD_UP;
	void __fastcall btnCalcClick(TObject *Sender);
	void __fastcall chkDITHENClick(TObject *Sender);
	void __fastcall cmbDITHNChange(TObject *Sender);
	void __fastcall chbPwrPllModsClick(TObject *Sender);
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall rgrMODEClick(TObject *Sender);
	void __fastcall rgrSELVCOClick(TObject *Sender);
	void __fastcall rgrFRANGEClick(TObject *Sender);
	void __fastcall cmbSELOUTChange(TObject *Sender);
	void __fastcall cmbICHPChange(TObject *Sender);
	void __fastcall cmbOFFUPChange(TObject *Sender);
	void __fastcall cmbOFFDOWNChange(TObject *Sender);
	void __fastcall cmbVCOCAPChange(TObject *Sender);
	void __fastcall cmbBCODEChange(TObject *Sender);
	void __fastcall cmbACODEChange(TObject *Sender);
	void __fastcall chkENLOBUFClick(TObject *Sender);
	void __fastcall chkENLAMPClick(TObject *Sender);
	void __fastcall chkPFDPDClick(TObject *Sender);
	void __fastcall chkENFEEDDIVClick(TObject *Sender);
  void __fastcall btnClbrClick(TObject *Sender);
  void __fastcall btnChooseClick(TObject *Sender);
  void __fastcall cmbPD_VCOCOMP_SXClick(TObject *Sender);
  void __fastcall chkOEN_TSTD_SXClick(TObject *Sender);
  void __fastcall chkPASSEN_TSTOD_SDClick(TObject *Sender);
  void __fastcall btnReadVtuneClick(TObject *Sender);
  void __fastcall btnTuneClick(TObject *Sender);
  void __fastcall chkPFDCLKPClick(TObject *Sender);
  void __fastcall chkTRIClick(TObject *Sender);
  void __fastcall chkPOLClick(TObject *Sender);
  void __fastcall chbAUTOBYPClick(TObject *Sender);
  void __fastcall chbEN_PFD_UPClick(TObject *Sender);
  void __fastcall chbBYPVCOREGClick(TObject *Sender);
  void __fastcall chbPDVCOREGClick(TObject *Sender);
  void __fastcall chbFSTVCOBGClick(TObject *Sender);
  void __fastcall cmbVOVCOREGChange(TObject *Sender);
  void __fastcall rgrBCLKSELClick(TObject *Sender);
  void __fastcall rgrBINSELClick(TObject *Sender);
  void __fastcall btnReadBISTStateClick(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall btnBSTARTClick(TObject *Sender);

protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;
  TdlgFreqVsCap *dlgFreqVsCap;
  double m_dRefF;
  int m_iPrevVCO;

  F320M_Data m_F320M_Data;

  void MakeData(int rAddr);
  void CalcFreq(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco);
  void CalcFreqDannyWhish(double dDF, double &rdRF, double &dDiv, int &iDInd, int &Nint, int &Nfrac, int &iVCO, double &Fvco);
  void CalcPLLData();
  int AutoSelectVcoCap(double Freq, int iVcoInd);
  void ChooseVcoCap();
  void CalcIntPllData();

public:		// User declarations
	__fastcall TfrmTxPLL(TComponent* Owner);
  __fastcall ~TfrmTxPLL(void);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr);
  sPrData *GetPrData(){return &m_psD;};
  void MakeWriteAll();
  void MakeRVFFile(ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  bool ChipVsGui(ofstream &out, String Caption, bool bWrAll);
  bool SetGUIUnderReadback();
  void MakeRegisterFile(ofstream &out);
  //void UpdateFormData();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);
  void SetRefClk(double RefClk);
  double GetRefClk();
  void UpdateFreq();
  int GetVTuneState();
  void CapAutoTune_D();     //Method according to Danny. Stops, when reaches 0.5V or 2.8V value of Vtune.
  int CapAutoTune_S(TdVcoCapLog *dVcoCapLog);     //Method according to Srdjan. Founds Cap values for 0.5V and 2.8V value of Vtune and then calculates Cap value for Vtune 1.5V.
  int LookForCap(TdVcoCapLog *dVcoCapLog);
  bool CapDecrement(int UntilState, TdVcoCapLog *VcoCapLog);
  bool CapIncrement(int UntilState, TdVcoCapLog *VcoCapLog);
  //void SetCapVal(int cval);
  int GetVTuneState(int vco, int cap);

  void CustSet_ActiveLOBuff(int ind);
  void CustSet_LoadFrequency(double Freq);
  void CustSet_PLLPowerON();
  void CustSet_PLLPowerOFF();
  void CustSet_cmbOFFUP(int Ind);

  void RT_SetTestMask(char Mask);

  bool BIST_GetState();
  void BIST_ShowState(bool State);
  unsigned int BIST_GetSignature();
  void BIST_ShowSignature(int Signature);
  void BIST_Start();

  void SetPLLTo320MHz();
  void RestoreAfterSetPLLTo320MHz();

};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmTxPLL *frmTxPLL;
//---------------------------------------------------------------------------
#endif
