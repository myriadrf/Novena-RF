// -----------------------------------------------------------------------------
// FILE: 		    frADDC.h
// DESCRIPTION:	Header for frADDC.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frADDCH
#define frADDCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "common.h"
#include <fstream.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
class TfrmADDC : public TFrame
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox4;
  TRadioGroup *rgrRX_FSYNC_P;
  TRadioGroup *rgrRX_INTER;
  TRadioGroup *rgrDAC_CLK_P;
  TRadioGroup *rgrTX_FSYNC_P;
  TRadioGroup *rgrTX_INTER;
  TGroupBox *GroupBox5;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label5;
  TLabel *Label8;
  TLabel *Label9;
  TComboBox *cmbBandgapTemp;
  TComboBox *cmbBandgapGain;
  TComboBox *cmbRefAmpsBiasAdj;
  TComboBox *cmbRefAmpsBiasUp;
  TComboBox *cmbRefAmpsBiasDn;
  TGroupBox *GroupBox7;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label14;
  TLabel *Label16;
  TLabel *Label18;
  TLabel *Label19;
  TComboBox *cmbCoomonModeAdj;
  TComboBox *cmbRefGainAdj;
  TComboBox *cmbRefResistorBiasAdj;
  TComboBox *cmbRefBiasUp;
  TComboBox *cmbRefBiasDn;
  TComboBox *cmbRefBufferBoost;
  TRadioGroup *rgrADCAmp1Stage2BasUp;
  TRadioGroup *rgrADCAmp24Stage2BasUp;
  TRadioGroup *rgrQuantizerBiasUp;
  TRadioGroup *rgrInputBufferBiasUp;
  TRadioGroup *rgrADCAmp1Stage1BasUp;
  TRadioGroup *rgrADCAmp24Stage1BasUp;
  TRadioGroup *rgrADCBiasResistorAdjust;
  TGroupBox *GroupBox1;
  TRadioGroup *rgrDACReferenceCurrentResistor;
  TLabel *Label3;
  TComboBox *cmbDACInternalOutputLoadResistor;
  TLabel *Label4;
  TComboBox *cmbDACFullScaleOutputCurrent;
  TLabel *Label6;
  TComboBox *cmbMainBiasDN;
  TLabel *Label7;
  TComboBox *cmbClockNonOverlapAdjust;
  TLabel *Label12;
  TComboBox *cmbADCSamplingPhase;
  TCheckBox *chkInputBufferDisable;
  TGroupBox *GroupBox2;
  TCheckBox *chkEN_ADC_I;
  TCheckBox *chkEN_ADC_Q;
  TCheckBox *chkEN_ADC_REF;
  TCheckBox *chkEN_DAC;
  TCheckBox *chkEN_M_REF;
  TCheckBox *chbEN_ADC_DAC;
  TRadioGroup *rgrDecode;
  void __fastcall rgrRX_FSYNC_PClick(TObject *Sender);
  void __fastcall rgrRX_INTERClick(TObject *Sender);
  void __fastcall rgrDAC_CLK_PClick(TObject *Sender);
  void __fastcall rgrTX_FSYNC_PClick(TObject *Sender);
  void __fastcall rgrTX_INTERClick(TObject *Sender);
  void __fastcall chkEN_DACClick(TObject *Sender);
  void __fastcall chkEN_ADC_IClick(TObject *Sender);
  void __fastcall chkEN_ADC_QClick(TObject *Sender);
  void __fastcall chkEN_ADC_REFClick(TObject *Sender);
  void __fastcall chkEN_M_REFClick(TObject *Sender);
  void __fastcall cmbBandgapTempChange(TObject *Sender);
  void __fastcall cmbBandgapGainChange(TObject *Sender);
  void __fastcall cmbRefAmpsBiasAdjChange(TObject *Sender);
  void __fastcall cmbRefAmpsBiasUpChange(TObject *Sender);
  void __fastcall cmbRefAmpsBiasDnChange(TObject *Sender);
  void __fastcall cmbRefResistorBiasAdjChange(TObject *Sender);
  void __fastcall cmbRefBiasUpChange(TObject *Sender);
  void __fastcall cmbRefBiasDnChange(TObject *Sender);
  void __fastcall cmbRefGainAdjChange(TObject *Sender);
  void __fastcall cmbCoomonModeAdjChange(TObject *Sender);
  void __fastcall cmbRefBufferBoostChange(TObject *Sender);
  void __fastcall chkInputBufferDisableClick(TObject *Sender);
  void __fastcall cmbADCSamplingPhaseChange(TObject *Sender);
  void __fastcall cmbClockNonOverlapAdjustChange(TObject *Sender);
  void __fastcall rgrADCBiasResistorAdjustClick(TObject *Sender);
  void __fastcall cmbMainBiasDNChange(TObject *Sender);
  void __fastcall rgrADCAmp1Stage1BasUpClick(TObject *Sender);
  void __fastcall rgrADCAmp24Stage1BasUpClick(TObject *Sender);
  void __fastcall rgrADCAmp1Stage2BasUpClick(TObject *Sender);
  void __fastcall rgrADCAmp24Stage2BasUpClick(TObject *Sender);
  void __fastcall rgrQuantizerBiasUpClick(TObject *Sender);
  void __fastcall rgrInputBufferBiasUpClick(TObject *Sender);
  void __fastcall cmbDACInternalOutputLoadResistorChange(TObject *Sender);
  void __fastcall rgrDACReferenceCurrentResistorClick(TObject *Sender);
  void __fastcall cmbDACFullScaleOutputCurrentChange(TObject *Sender);
  void __fastcall rgrDecodeClick(TObject *Sender);
private:	// User declarations

protected:
	char m_cMAddr;
	sPrData m_psD;
  bool m_bAllowSend;

  void MakeData(int rAddr);

public:		// User declarations
  __fastcall TfrmADDC(TComponent* Owner);

  void SetGuiDefaults();
  void SetGuiDecode();
  void Initialize(char MAddr);
  void SetGuiDecode(int Decode);

  void SaveConf(TIniFile *pini);
  void ReadConf(TIniFile *pini);
  bool ChipVsGui(sPrData &m_psD, ofstream &out, String Caption, bool bWrAll);
  void MakeRVFFile(sPrData &m_psD, ofstream &out);        //Writes Register - Value format to the file.
  void MakeRFIFFile(sPrData &m_psD, ofstream &out, char *FRIF_SPI_A);        //Writes RFIF register format to the file.
  bool SetGUIUnderReadback(sPrData &m_psD);
  void MakeRegisterFile(sPrData &m_psD, ofstream &out);

  void CustSet_cmbCoomonModeAdj(int Ind);

};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmADDC *frmADDC;
//---------------------------------------------------------------------------
#endif
