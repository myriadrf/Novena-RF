// -----------------------------------------------------------------------------
// FILE: 		    frRxFe.h
// DESCRIPTION:	Header for frRxFe.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frRxFeH
#define frRxFeH
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
class TfrmRxFe : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cmbDCOFF_I_RXFE;
	TComboBox *cmbDCOFF_Q_RXFE;
	TGroupBox *GroupBox3;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cmbIP2TRIM_I_RXFE;
	TComboBox *cmbIP2TRIM_Q_RXFE;
	TRadioGroup *rgrDecode;
	TGroupBox *GroupBox6;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TComboBox *cmbICT_MIX_RXFE;
	TComboBox *cmbICT_MXLOB_RXFE;
	TComboBox *cmbLOBN_MIX_RXFE;
	TGroupBox *GroupBox1;
	TCheckBox *chbPwrRxFeMods;
	TGroupBox *GroupBox4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TCheckBox *chkINLOAD_LNA_RXFE;
	TCheckBox *chkXLOAD_LNA_RXFE;
	TComboBox *cmbG_LNA_RXFE;
	TComboBox *cmbLNASEL_RXFE;
	TComboBox *cmbRDLEXT_LNA_RXFE;
	TComboBox *cmbRDLINT_LNA_RXFE;
	TComboBox *cmbICT_LNA_RXFE;
	TComboBox *cmbCBE_LNA_RXFE;
	TGroupBox *GroupBox5;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TComboBox *cmbRFB_TIA_RXFE;
	TComboBox *cmbCFB_TIA_RXFE;
	TComboBox *cmbICT_TIA_RXFE;
	TCheckBox *chkPD_TIA_RXFE;
	TCheckBox *chkPD_MXLOB_RXFE;
	TCheckBox *chkPD_LNA_RXFE;
	TCheckBox *chkPD_MIX_RXFE;
	TLabel *Label19;
	TComboBox *cmbIN1SEL_MIX_RXFE;
  TCheckBox *chkRINEN_MIX_RXFE;
  TComboBox *cmbG_FINE_LNA3_RXFE;
  TLabel *Label20;
	void __fastcall rgrDecodeClick(TObject *Sender);
	void __fastcall chbPwrRxFeModsClick(TObject *Sender);
	void __fastcall cmbIN1SEL_MIX_RXFEChange(TObject *Sender);
	void __fastcall cmbDCOFF_I_RXFEChange(TObject *Sender);
	void __fastcall chkINLOAD_LNA_RXFEClick(TObject *Sender);
	void __fastcall cmbDCOFF_Q_RXFEChange(TObject *Sender);
	void __fastcall chkXLOAD_LNA_RXFEClick(TObject *Sender);
	void __fastcall cmbIP2TRIM_I_RXFEChange(TObject *Sender);
	void __fastcall cmbIP2TRIM_Q_RXFEChange(TObject *Sender);
	void __fastcall cmbG_LNA_RXFEChange(TObject *Sender);
	void __fastcall cmbLNASEL_RXFEChange(TObject *Sender);
	void __fastcall cmbCBE_LNA_RXFEChange(TObject *Sender);
	void __fastcall cmbRFB_TIA_RXFEChange(TObject *Sender);
	void __fastcall cmbCFB_TIA_RXFEChange(TObject *Sender);
	void __fastcall cmbRDLEXT_LNA_RXFEChange(TObject *Sender);
	void __fastcall cmbRDLINT_LNA_RXFEChange(TObject *Sender);
	void __fastcall cmbICT_MIX_RXFEChange(TObject *Sender);
	void __fastcall cmbICT_LNA_RXFEChange(TObject *Sender);
	void __fastcall cmbICT_TIA_RXFEChange(TObject *Sender);
	void __fastcall cmbICT_MXLOB_RXFEChange(TObject *Sender);
	void __fastcall cmbLOBN_MIX_RXFEChange(TObject *Sender);
	void __fastcall chkPD_TIA_RXFEClick(TObject *Sender);
	void __fastcall chkPD_MXLOB_RXFEClick(TObject *Sender);
	void __fastcall chkPD_MIX_RXFEClick(TObject *Sender);
	void __fastcall chkPD_LNA_RXFEClick(TObject *Sender);
  void __fastcall chkRINEN_MIX_RXFEClick(TObject *Sender);
  void __fastcall cmbG_FINE_LNA3_RXFEChange(TObject *Sender);
protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;

  void MakeData(int rAddr);

public:		// User declarations
	__fastcall TfrmRxFe(TComponent* Owner);
  __fastcall ~TfrmRxFe(void);

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
  //void UpdateFormData();
  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);

  void CustSet_ActiveLNA(int ind);
  void CustSet_LNAPowerON();
  void CustSet_LNAPowerOFF();
  void CustSet_PowerOFF();
  void CustSet_PowerON();
  void CustSet_cmbRDLINT_LNA_RXFE(int Ind);

  void CustSet_DCOffsetCancellationI(int ind);
  void CustSet_DCOffsetCancellationQ(int ind);
  int  CustGet_DCOffsetCancellationI();
  int  CustGet_DCOffsetCancellationQ();

  void RT_SetTestMask(char Mask);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmRxFe *frmRxFe;
//---------------------------------------------------------------------------
#endif
