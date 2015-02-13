// -----------------------------------------------------------------------------
// FILE: 		    frADDC.cpp
// DESCRIPTION:	DAC and ADC control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "frADDC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmADDC *frmADDC;

//0x7
#define            EN_ADC_DAC_r07_b77() ((m_psD.cDataR[0x07] & 0x80) >> 7)
#define        DECODE_ADC_DAC_r07_b66() ((m_psD.cDataR[0x07] & 0x40) >> 6)
#define           TX_CTRL1_64_r07_b53() ((m_psD.cDataR[0x07] & 0x38) >> 3)
#define           TX_CTRL1_33_r07_b22() ((m_psD.cDataR[0x07] & 0x04) >> 2)
#define           TX_CTRL1_10_r07_b10() ((m_psD.cDataR[0x07] & 0x03) >> 0)
//0x8
#define            RX_CTRL1_76_r08_b76() ((m_psD.cDataR[0x08] & 0xC0) >> 6)
#define            RX_CTRL1_54_r08_b54() ((m_psD.cDataR[0x08] & 0x30) >> 4)
#define            RX_CTRL1_30_r08_b30() ((m_psD.cDataR[0x08] & 0x0F) >> 0)
//0x9
#define            RX_CTRL2_76_r09_b65() ((m_psD.cDataR[0x09] & 0x60) >> 5)
#define            RX_CTRL2_54_r09_b43() ((m_psD.cDataR[0x09] & 0x18) >> 3)
#define            RX_CTRL2_32_r09_b21() ((m_psD.cDataR[0x09] & 0x06) >> 1)
#define            RX_CTRL2_00_r09_b00() ((m_psD.cDataR[0x09] & 0x01) >> 0)
//0xA
#define           MISC_CTRL_99_r0A_b77() ((m_psD.cDataR[0x0A] & 0x80) >> 7)
#define           MISC_CTRL_88_r0A_b66() ((m_psD.cDataR[0x0A] & 0x40) >> 6)
#define           MISC_CTRL_77_r0A_b55() ((m_psD.cDataR[0x0A] & 0x20) >> 5)
#define           MISC_CTRL_66_r0A_b44() ((m_psD.cDataR[0x0A] & 0x10) >> 4)
#define           MISC_CTRL_55_r0A_b33() ((m_psD.cDataR[0x0A] & 0x08) >> 3)
#define            RX_CTRL3_77_r0A_b22() ((m_psD.cDataR[0x0A] & 0x04) >> 2)
#define            RX_CTRL3_10_r0A_b10() ((m_psD.cDataR[0x0A] & 0x03) >> 0)
//0xB
#define            RX_CTRL4_76_r0B_b76() ((m_psD.cDataR[0x0B] & 0xC0) >> 6)
#define            RX_CTRL4_54_r0B_b54() ((m_psD.cDataR[0x0B] & 0x30) >> 4)
#define            RX_CTRL4_32_r0B_b32() ((m_psD.cDataR[0x0B] & 0x0C) >> 2)
#define            RX_CTRL4_10_r0B_b10() ((m_psD.cDataR[0x0B] & 0x03) >> 0)
//0xC
#define            RX_CTRL5_76_r0C_b76() ((m_psD.cDataR[0x0C] & 0xC0) >> 6)
#define            RX_CTRL5_54_r0C_b54() ((m_psD.cDataR[0x0C] & 0x30) >> 4)
#define            RX_CTRL5_32_r0C_b32() ((m_psD.cDataR[0x0C] & 0x0C) >> 2)
#define            RX_CTRL5_10_r0C_b10() ((m_psD.cDataR[0x0C] & 0x03) >> 0)
//0xD
#define           REF_CTRL0_74_r0D_b74() ((m_psD.cDataR[0x0D] & 0xF0) >> 4)
#define           REF_CTRL0_30_r0D_b30() ((m_psD.cDataR[0x0D] & 0x0F) >> 0)
//0xE
#define           REF_CTRL1_76_r0E_b76() ((m_psD.cDataR[0x0E] & 0xC0) >> 6)
#define           REF_CTRL1_54_r0E_b54() ((m_psD.cDataR[0x0E] & 0x30) >> 4)
#define           REF_CTRL1_30_r0E_b30() ((m_psD.cDataR[0x0E] & 0x0F) >> 0)
//0xF
#define           MISC_CTRL_44_r0F_b44() ((m_psD.cDataR[0x0F] & 0x10) >> 4)
#define           MISC_CTRL_33_r0F_b33() ((m_psD.cDataR[0x0F] & 0x08) >> 3)
#define           MISC_CTRL_22_r0F_b22() ((m_psD.cDataR[0x0F] & 0x04) >> 2)
#define           MISC_CTRL_11_r0F_b11() ((m_psD.cDataR[0x0F] & 0x02) >> 1)
#define           MISC_CTRL_00_r0F_b00() ((m_psD.cDataR[0x0F] & 0x01) >> 0)


#define FRIF_DIR_W "rfIf Direct=16,"
//#define FRIF_SPI_A ",20"

//---------------------------------------------------------------------------
__fastcall TfrmADDC::TfrmADDC(TComponent* Owner)
  : TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void TfrmADDC::Initialize(char MAddr)
{
  m_cMAddr = MAddr;

  SetGuiDefaults();
};

//---------------------------------------------------------------------------
void TfrmADDC::SetGuiDefaults()
{
  m_bAllowSend = false;

  //EN_ADC_DAC
  chbEN_ADC_DAC->Checked = true;

  //Decode
  rgrDecode->ItemIndex = 0;

//============== ENABLE CONTROL REGISTERS ==========

  //Rx Fsync Polarity, frame start
  rgrRX_FSYNC_P->ItemIndex = 0;

  //Rx Interleave Mode
  rgrRX_INTER->ItemIndex = 0;

  //Dac Clk Edge Polarity
  rgrDAC_CLK_P->ItemIndex = 1;

  //Tx Fsync Polarity, frame start
  rgrTX_FSYNC_P->ItemIndex = 0;

  //Tx Interleave Mode
  rgrTX_INTER->ItemIndex = 0;

  //Enable DAC
  chkEN_DAC->Checked = true;

  //Enable ADC1 (I Channel)
  chkEN_ADC_I->Checked = true;

  //Enable ADC2 (Q Channel)
  chkEN_ADC_Q->Checked = true;

  //Enable ADC reference
  chkEN_ADC_REF->Checked = true;

  //Enable master reference
  chkEN_M_REF->Checked = true;

//============== REFERENECE CONTROL REGISTERS 0 ==========
  //Bandgap Temperature Coefficient Control
  cmbBandgapTemp->Items->Clear();
  cmbBandgapTemp->Items->Add("-8 (Min)"); cmbBandgapTemp->Items->Add("-7");
  cmbBandgapTemp->Items->Add("-6");       cmbBandgapTemp->Items->Add("-5");
  cmbBandgapTemp->Items->Add("-4");       cmbBandgapTemp->Items->Add("-3");
  cmbBandgapTemp->Items->Add("-2");       cmbBandgapTemp->Items->Add("-1");
  cmbBandgapTemp->Items->Add(" 0 (Nom)"); cmbBandgapTemp->Items->Add(" 1");
  cmbBandgapTemp->Items->Add(" 2");       cmbBandgapTemp->Items->Add(" 3");
  cmbBandgapTemp->Items->Add(" 4");       cmbBandgapTemp->Items->Add(" 5");
  cmbBandgapTemp->Items->Add(" 6");       cmbBandgapTemp->Items->Add(" 7 (Max)");
  cmbBandgapTemp->ItemIndex = 8;

  //Bandgap Gain Control
  cmbBandgapGain->Items->Clear();
  cmbBandgapGain->Items->Add("-8 (Min)"); cmbBandgapGain->Items->Add("-7");
  cmbBandgapGain->Items->Add("-6");       cmbBandgapGain->Items->Add("-5");
  cmbBandgapGain->Items->Add("-4");       cmbBandgapGain->Items->Add("-3");
  cmbBandgapGain->Items->Add("-2");       cmbBandgapGain->Items->Add("-1");
  cmbBandgapGain->Items->Add(" 0 (Nom)"); cmbBandgapGain->Items->Add(" 1");
  cmbBandgapGain->Items->Add(" 2");       cmbBandgapGain->Items->Add(" 3");
  cmbBandgapGain->Items->Add(" 4");       cmbBandgapGain->Items->Add(" 5");
  cmbBandgapGain->Items->Add(" 6");       cmbBandgapGain->Items->Add(" 7 (Max)");
  cmbBandgapGain->ItemIndex = 8;

//============== REFERENECE CONTROL REGISTERS 1 ==========
  //Reference Amps bias adjust
  cmbRefAmpsBiasAdj->Items->Clear();
  cmbRefAmpsBiasAdj->Items->Add("20uA");  cmbRefAmpsBiasAdj->Items->Add("40uA");
  cmbRefAmpsBiasAdj->Items->Add("10uA");  cmbRefAmpsBiasAdj->Items->Add("15uA");
  cmbRefAmpsBiasAdj->ItemIndex = 0;

  //Reference Amps bias UP
  cmbRefAmpsBiasUp->Items->Clear();
  cmbRefAmpsBiasUp->Items->Add("1.0X");  cmbRefAmpsBiasUp->Items->Add("1.5X");
  cmbRefAmpsBiasUp->Items->Add("2.0X");  cmbRefAmpsBiasUp->Items->Add("2.5X");
  cmbRefAmpsBiasUp->ItemIndex = 0;

  //Reference Amps bias DOWN
  cmbRefAmpsBiasDn->Items->Clear();
  for(int i=0; i<16; i++)
  {
    cmbRefAmpsBiasDn->Items->Add(i);
  };
  cmbRefAmpsBiasDn->ItemIndex = 0;

//============== ADC CONTROL REGISTERS 1 ==========
  //Reference bias resistor adjust
  cmbRefResistorBiasAdj->Items->Clear();
  cmbRefResistorBiasAdj->Items->Add("20uA");  cmbRefResistorBiasAdj->Items->Add("40uA");
  cmbRefResistorBiasAdj->Items->Add("10uA");  cmbRefResistorBiasAdj->Items->Add("15uA");
  cmbRefResistorBiasAdj->ItemIndex = 0;

  //Reference bias UP
  cmbRefBiasUp->Items->Clear();
  cmbRefBiasUp->Items->Add("1.0X");  cmbRefBiasUp->Items->Add("1.5X");
  cmbRefBiasUp->Items->Add("2.0X");  cmbRefBiasUp->Items->Add("2.5X");
  cmbRefBiasUp->ItemIndex = 0;

  //Reference bias DN
  cmbRefBiasDn->Items->Clear();
  for(int i=0; i<16; i++)
  {
    cmbRefBiasDn->Items->Add(i);
  };
  cmbRefBiasDn->ItemIndex = 0;

//============== ADC CONTROL REGISTERS 2 ==========
  //Reference Gain Adjust
  cmbRefGainAdj->Items->Clear();
  cmbRefGainAdj->Items->Add("1.50V");  cmbRefGainAdj->Items->Add("1.75V");
  cmbRefGainAdj->Items->Add("1.00V");  cmbRefGainAdj->Items->Add("1.25V");
  cmbRefGainAdj->ItemIndex = 0;

  //Common Mode Adjust
  cmbCoomonModeAdj->Items->Clear();
  cmbCoomonModeAdj->Items->Add("875mV");  cmbCoomonModeAdj->Items->Add("960mV");
  cmbCoomonModeAdj->Items->Add("700mV");  cmbCoomonModeAdj->Items->Add("790mV");
  cmbCoomonModeAdj->ItemIndex = 0;

  //Reference Buffer Boost
  cmbRefBufferBoost->Items->Clear();
  cmbRefBufferBoost->Items->Add("1.0X");  cmbRefBufferBoost->Items->Add("1.5X");
  cmbRefBufferBoost->Items->Add("2.0X");  cmbRefBufferBoost->Items->Add("2.5X");
  cmbRefBufferBoost->ItemIndex = 0;

  //Input Buffer Disable
  chkInputBufferDisable->Checked = true;

//============== ADC CONTROL REGISTERS 3 ==========
  //ADC Sampling Phase Select
  cmbADCSamplingPhase->Items->Clear();
  cmbADCSamplingPhase->Items->Add("Rising Edge");  cmbADCSamplingPhase->Items->Add("Falling Edge");
  cmbADCSamplingPhase->ItemIndex = 0;

  //Clock Non-Overlap Adjust
  cmbClockNonOverlapAdjust->Items->Clear();
  cmbClockNonOverlapAdjust->Items->Add("Nominal");  cmbClockNonOverlapAdjust->Items->Add("+450ps");
  cmbClockNonOverlapAdjust->Items->Add("+150ps");  cmbClockNonOverlapAdjust->Items->Add("+300ps");
  cmbClockNonOverlapAdjust->ItemIndex = 0;

//============== ADC CONTROL REGISTERS 4 ==========
  //ADC bias resistor adjust
  rgrADCBiasResistorAdjust->ItemIndex = 0;

  //Main bias DOWN
  cmbMainBiasDN->Items->Clear();
  cmbMainBiasDN->Items->Add("0 (Nom)");  cmbMainBiasDN->Items->Add("1");
  cmbMainBiasDN->Items->Add("2");  cmbMainBiasDN->Items->Add("3 (Min)");
  cmbMainBiasDN->ItemIndex = 0;

  //ADC Amp1 stage1 bias UP
  rgrADCAmp1Stage1BasUp->ItemIndex = 0;

  //ADC Amp2-4 stage1 bias UP
  rgrADCAmp24Stage1BasUp->ItemIndex = 0;

//============== ADC CONTROL REGISTERS 5 ==========
  //ADC Amp1 stage2 bias UP
  rgrADCAmp1Stage2BasUp->ItemIndex = 0;

  //ADC Amp2-4 stage2 bias UP
  rgrADCAmp24Stage2BasUp->ItemIndex = 0;

  //Quantizer  bias UP
  rgrQuantizerBiasUp->ItemIndex = 0;

  //Input Buffer bias UP
  rgrInputBufferBiasUp->ItemIndex = 0;

//============== DAC CONTROL REGISTERS 1 ==========
  //DAC Internal Output Load Resistor Control Bits
  cmbDACInternalOutputLoadResistor->Items->Clear();
  cmbDACInternalOutputLoadResistor->Items->Add("Open Circuit");
  cmbDACInternalOutputLoadResistor->Items->Add("100 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add("200 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add(" 66 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add("200 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add(" 66 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add("100 Ohms");
  cmbDACInternalOutputLoadResistor->Items->Add(" 50 Ohms");
  cmbDACInternalOutputLoadResistor->ItemIndex = 2;

  //DAC Reference Current Resistor
  rgrDACReferenceCurrentResistor->ItemIndex = 1;

  //DAC Full Scale Output Current Control (single-ended)
  cmbDACFullScaleOutputCurrent->Items->Clear();
  cmbDACFullScaleOutputCurrent->Items->Add("  5 mA");
  cmbDACFullScaleOutputCurrent->Items->Add(" 10 mA");
  cmbDACFullScaleOutputCurrent->Items->Add("2.5 mA");
  cmbDACFullScaleOutputCurrent->Items->Add("  5 mA");
  cmbDACFullScaleOutputCurrent->ItemIndex = 0;

  SetGuiDecode();

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void TfrmADDC::SetGuiDecode()
{
 	if(rgrDecode->ItemIndex == 0)
  {
  	//Decode
    chbEN_ADC_DAC->Enabled = true;

    chkEN_ADC_I->Enabled = false;
    chkEN_ADC_Q->Enabled = false;
    chkEN_ADC_REF->Enabled = false;
    chkEN_DAC->Enabled = false;
    chkEN_M_REF->Enabled = false;
  }
  else
  {
  	//Direct control
    chbEN_ADC_DAC->Enabled = false;

    chkEN_ADC_I->Enabled = true;
    chkEN_ADC_Q->Enabled = true;
    chkEN_ADC_REF->Enabled = true;
    chkEN_DAC->Enabled = true;
    chkEN_M_REF->Enabled = true;
  };
};

//----------------------------------------------------------------------------
// Make data to download
//----------------------------------------------------------------------------
void TfrmADDC::MakeData(int rAddr)
{
/*
	char btmp;

	//======= register addr 0x04 =======
	//m_psD.cDataW[0x04] = 0x00;
	//EN_M_REF
	btmp = chkEN_M_REF->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x04] |= btmp;
	//EN_ADC_REF
	btmp = chkEN_ADC_REF->Checked == true ? 1 : 0;
	btmp = btmp << 6; m_psD.cDataW[0x04] |= btmp;

	//======= register addr 0x05 =======
	//m_psD.cDataW[0x05] = 0x00;
	//EN_ADC_Q
	btmp = chkEN_ADC_Q->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x05] |= btmp;

	//======= register addr 0x06 =======
	//m_psD.cDataW[0x06] = 0x00;
	//EN_ADC_I
	btmp = chkEN_ADC_I->Checked == true ? 1 : 0;
	btmp = btmp << 7; m_psD.cDataW[0x06] |= btmp;

	//======= register addr 0x07 =======
	m_psD.cDataW[0x07] = 0x00;
  //
	btmp = (char)cmbDACInternalOutputLoadResistor->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x07] |= btmp;
  //
	btmp = (char)rgrDACReferenceCurrentResistor->ItemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x07] |= btmp;
  //
	btmp = (char)cmbDACFullScaleOutputCurrent->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x07] |= btmp;

	//======= register addr 0x08 =======
	m_psD.cDataW[0x08] = 0x00;
  //
	btmp = (char)cmbRefResistorBiasAdj->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x08] |= btmp;
  //
	btmp = (char)cmbRefBiasUp->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x08] |= btmp;
  //
	btmp = (char)cmbRefBiasDn->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x08] |= btmp;

	//======= register addr 0x09 =======
	m_psD.cDataW[0x09] = 0x00;
  //
	btmp = (char)cmbRefGainAdj->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x09] |= btmp;
  //
	btmp = (char)cmbCoomonModeAdj->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x09] |= btmp;
  //
	btmp = (char)cmbRefBufferBoost->ItemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x09] |= btmp;
  //
 	btmp = chkInputBufferDisable->Checked == true ? 0 : 1;
	btmp = btmp << 0; m_psD.cDataW[0x09] |= btmp;

	//======= register addr 0x0A =======
	m_psD.cDataW[0x0A] = 0x00;
  //
 	btmp = cmbADCSamplingPhase->ItemIndex;
	btmp = btmp << 7; m_psD.cDataW[0x0A] |= btmp;
  //
 	btmp = cmbClockNonOverlapAdjust->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0A] |= btmp;

	//======= register addr 0x0B =======
	m_psD.cDataW[0x0B] = 0x00;
  //
 	btmp = rgrADCBiasResistorAdjust->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x0B] |= btmp;
  //
 	btmp = cmbMainBiasDN->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0B] |= btmp;
  //
 	btmp = rgrADCAmp1Stage1BasUp->ItemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x0B] |= btmp;
  //
 	btmp = rgrADCAmp24Stage1BasUp->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0B] |= btmp;

	//======= register addr 0x0C =======
	m_psD.cDataW[0x0C] = 0x00;
  //
 	btmp = rgrADCAmp1Stage2BasUp->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x0C] |= btmp;
  //
 	btmp = rgrADCAmp24Stage2BasUp->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0C] |= btmp;
  //
 	btmp = rgrQuantizerBiasUp->ItemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x0C] |= btmp;
  //
 	btmp = rgrInputBufferBiasUp->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0C] |= btmp;

	//======= register addr 0x0D =======
	m_psD.cDataW[0x0D] = 0x00;
  //
  btmp = m_frmADDC->cmbBandgapTemp->ItemIndex + 8;
  btmp = btmp & 0x0F;
  btmp = btmp << 4; m_psD.cDataW[0x0D] |= btmp;
  //
  btmp = m_frmADDC->cmbBandgapGain->ItemIndex + 8;
  btmp = btmp & 0x0F;
  btmp = btmp << 0; m_psD.cDataW[0x0D] |= btmp;

	//======= register addr 0x0E =======
	m_psD.cDataW[0x0E] = 0x00;
  //
 	btmp = cmbRefAmpsBiasAdj->ItemIndex;
	btmp = btmp << 6; m_psD.cDataW[0x0E] |= btmp;
  //
 	btmp = cmbRefAmpsBiasUp->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0E] |= btmp;
  //
 	btmp = cmbRefAmpsBiasDn->ItemIndex;
	btmp = btmp << 0; m_psD.cDataW[0x0E] |= btmp;

	//======= register addr 0x0F =======
	m_psD.cDataW[0x0F] = 0x00;
  //
 	btmp = rgrRX_FSYNC_P->ItemIndex;
	btmp = btmp << 5; m_psD.cDataW[0x0F] |= btmp;
  //
 	btmp = rgrRX_INTER->ItemIndex;
	btmp = btmp << 4; m_psD.cDataW[0x0F] |= btmp;
  //
 	btmp = rgrDAC_CLK_P->ItemIndex;
	btmp = btmp << 3; m_psD.cDataW[0x0F] |= btmp;
  //
 	btmp = rgrTX_FSYNC_P->ItemIndex;
	btmp = btmp << 2; m_psD.cDataW[0x0F] |= btmp;
  //
 	btmp = rgrTX_INTER->ItemIndex;
	btmp = btmp << 1; m_psD.cDataW[0x0F] |= btmp;
  //
 	btmp = chkEN_DAC->Checked == true ? 1 : 0;
	btmp = btmp << 0; m_psD.cDataW[0x0F] |= btmp;

*/
};
//---------------------------------------------------------------------------
void __fastcall TfrmADDC::rgrRX_FSYNC_PClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x50);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrRX_INTERClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x51);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrDAC_CLK_PClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x52);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrTX_FSYNC_PClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x53);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrTX_INTERClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x54);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkEN_DACClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x55);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkEN_ADC_IClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x56);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkEN_ADC_QClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x57);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkEN_ADC_REFClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x74);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrDecodeClick(TObject *Sender)
{
  SetGuiDecode();
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x75);  //0x54
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkEN_M_REFClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x59);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbBandgapTempChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5A);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbBandgapGainChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5B);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefAmpsBiasAdjChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5C);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefAmpsBiasUpChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5D);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefAmpsBiasDnChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5E);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefResistorBiasAdjChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x5F);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefBiasUpChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x60);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefBiasDnChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x61);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefGainAdjChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x62);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbCoomonModeAdjChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x63);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbRefBufferBoostChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x64);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::chkInputBufferDisableClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x65);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbADCSamplingPhaseChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x66);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbClockNonOverlapAdjustChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x67);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrADCBiasResistorAdjustClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x68);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbMainBiasDNChange(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x69);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrADCAmp1Stage1BasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6A);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrADCAmp24Stage1BasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6B);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrADCAmp1Stage2BasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6C);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrADCAmp24Stage2BasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6D);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrQuantizerBiasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6E);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrInputBufferBiasUpClick(TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x6F);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbDACInternalOutputLoadResistorChange(
      TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x70);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::rgrDACReferenceCurrentResistorClick(
      TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x71);
}
//---------------------------------------------------------------------------

void __fastcall TfrmADDC::cmbDACFullScaleOutputCurrentChange(
      TObject *Sender)
{
  if(m_bAllowSend) SendMessage(G_hwWindow, CM_ADDC2LPF, 0, 0x72);
}
//---------------------------------------------------------------------------

void TfrmADDC::SetGuiDecode(int Decode)
{

};

//---------------------------------------------------------------------------
bool TfrmADDC::ChipVsGui(sPrData &m_psD, ofstream &out, String Caption, bool bWrAll)
{
  bool bRez = true;
  bool btmp;
	char str[64] = "";
  int itmp, itmpC;

  out << left;
	out << Caption.c_str() << endl;
	out << endl;
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out.width(32); out << "| Register"; out.width(2); out << "|";
	out.width(50); out << "Value from PC"; out.width(2); out << "|";
	out.width(50); out << "Value from Chip"; out.width(1); out << "|";
	out << endl;
	out << "--------------------------------+---------------------------------------------------+----------------------------------------------------" << endl;

  //EN_ADC_DAC
  if((chbEN_ADC_DAC->Checked != (bool)EN_ADC_DAC_r07_b77()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| EN"; out.width(2); out << "|";	out.width(40);
    if(chbEN_ADC_DAC->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(EN_ADC_DAC_r07_b77()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //DECODE_ADC_DAC
  if((rgrDecode->ItemIndex != DECODE_ADC_DAC_r07_b66()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DECODE"; out.width(2); out << "|";	out.width(40);
    if(rgrDecode->ItemIndex == 1) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
	  if(DECODE_ADC_DAC_r07_b66()) strcpy(str, "Test Mode"); else strcpy(str, "User Mode");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TX_CTRL1[6:4]
  itmpC = TX_CTRL1_64_r07_b53();
  if((cmbDACInternalOutputLoadResistor->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DAC Internal Out Load Resistor"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbDACInternalOutputLoadResistor->ItemIndex;
    strcpy(str, cmbDACInternalOutputLoadResistor->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbDACInternalOutputLoadResistor->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TX_CTRL1[3]
  itmpC = TX_CTRL1_33_r07_b22();
  if((rgrDACReferenceCurrentResistor->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DAC Ref Current Resistor"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrDACReferenceCurrentResistor->ItemIndex;
    strcpy(str, rgrDACReferenceCurrentResistor->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrDACReferenceCurrentResistor->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //TX_CTRL1[1:0]
  itmpC = TX_CTRL1_10_r07_b10();
  if((cmbDACFullScaleOutputCurrent->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DAC Full Scale Output Control"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbDACFullScaleOutputCurrent->ItemIndex;
    strcpy(str, cmbDACFullScaleOutputCurrent->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbDACFullScaleOutputCurrent->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL1[7:6]
  itmpC = RX_CTRL1_76_r08_b76();
  if((cmbRefResistorBiasAdj->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Bias Resistor Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefResistorBiasAdj->ItemIndex;
    strcpy(str, cmbRefResistorBiasAdj->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefResistorBiasAdj->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL1[5:4]
  itmpC = RX_CTRL1_54_r08_b54();
  if((cmbRefBiasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Bias UP"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefBiasUp->ItemIndex;
    strcpy(str, cmbRefBiasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefBiasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL1[3:0]
  itmpC = RX_CTRL1_30_r08_b30();
  if((cmbRefBiasDn->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Bias Down"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefBiasDn->ItemIndex;
    strcpy(str, cmbRefBiasDn->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefBiasDn->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL2[7:6]
  itmpC = RX_CTRL2_76_r09_b65();
  if((cmbRefGainAdj->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Gain Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefGainAdj->ItemIndex;
    strcpy(str, cmbRefGainAdj->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefGainAdj->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL2[5:4]
  itmpC = RX_CTRL2_54_r09_b43();
  if((cmbCoomonModeAdj->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Common Mode Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbCoomonModeAdj->ItemIndex;
    strcpy(str, cmbCoomonModeAdj->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbCoomonModeAdj->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL2[3:2]
  itmpC = RX_CTRL2_32_r09_b21();
  if((cmbRefBufferBoost->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Buffer Boost"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefBufferBoost->ItemIndex;
    strcpy(str, cmbRefBufferBoost->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefBufferBoost->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL2[0]
  if((chkInputBufferDisable->Checked != (bool)RX_CTRL2_00_r09_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Input Buffer Disable"; out.width(2); out << "|";	out.width(40);
    if(chkInputBufferDisable->Checked) strcpy(str, "Disabled"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(RX_CTRL2_00_r09_b00()) strcpy(str, "Disabled"); else strcpy(str, "Enabled");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //MISC_CTRL[9]
  itmpC = MISC_CTRL_99_r0A_b77();
  if((rgrRX_FSYNC_P->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Rx Fsync Polarity, frame start"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrRX_FSYNC_P->ItemIndex;
    strcpy(str, rgrRX_FSYNC_P->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrRX_FSYNC_P->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //MISC_CTRL[8]
  itmpC = MISC_CTRL_88_r0A_b66();
  if((rgrRX_INTER->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Rx Interleave Mode"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrRX_INTER->ItemIndex;
    strcpy(str, rgrRX_INTER->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrRX_INTER->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //MISC_CTRL[7]
  itmpC = MISC_CTRL_77_r0A_b55();
  if((rgrDAC_CLK_P->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| DAC Clk Edge Polarity "; out.width(2); out << "|";	out.width(40);
  	itmp = rgrDAC_CLK_P->ItemIndex;
    strcpy(str, rgrDAC_CLK_P->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrDAC_CLK_P->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //MISC_CTRL[6]
  itmpC = MISC_CTRL_66_r0A_b44();
  if((rgrTX_FSYNC_P->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Tx Fsync Polarity, frame start"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrTX_FSYNC_P->ItemIndex;
    strcpy(str, rgrTX_FSYNC_P->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrTX_FSYNC_P->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //MISC_CTRL[5]
  itmpC = MISC_CTRL_55_r0A_b33();
  if((rgrTX_INTER->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Tx Interleave Mode"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrTX_INTER->ItemIndex;
    strcpy(str, rgrTX_INTER->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrTX_INTER->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL3[7]
  itmpC = RX_CTRL3_77_r0A_b22();
  if((cmbADCSamplingPhase->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Sampling Phase"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbADCSamplingPhase->ItemIndex;
    strcpy(str, cmbADCSamplingPhase->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbADCSamplingPhase->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //RX_CTRL3[1:0]
  itmpC = RX_CTRL3_10_r0A_b10();
  if((cmbClockNonOverlapAdjust->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Clock Non-Overlap Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbClockNonOverlapAdjust->ItemIndex;
    strcpy(str, cmbClockNonOverlapAdjust->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbClockNonOverlapAdjust->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL4[7:6]
  itmpC = RX_CTRL4_76_r0B_b76();
  if((rgrADCBiasResistorAdjust->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Bias Resistor Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrADCBiasResistorAdjust->ItemIndex;
    strcpy(str, rgrADCBiasResistorAdjust->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrADCBiasResistorAdjust->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //RX_CTRL4[5:4]
  itmpC = RX_CTRL4_54_r0B_b54();
  if((cmbMainBiasDN->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Main Bias Down"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbMainBiasDN->ItemIndex;
    strcpy(str, cmbMainBiasDN->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbMainBiasDN->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL4[3:2]
  itmpC = RX_CTRL4_32_r0B_b32();
  if((rgrADCAmp1Stage1BasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Amp1 Stage1 Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrADCAmp1Stage1BasUp->ItemIndex;
    strcpy(str, rgrADCAmp1Stage1BasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrADCAmp1Stage1BasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL4[1:0]
  itmpC = RX_CTRL4_10_r0B_b10();
  if((rgrADCAmp24Stage1BasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Amp2-4 Stage1 Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrADCAmp24Stage1BasUp->ItemIndex;
    strcpy(str, rgrADCAmp24Stage1BasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrADCAmp24Stage1BasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL5[7:6]
  itmpC = RX_CTRL5_76_r0C_b76();
  if((rgrADCAmp1Stage2BasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Amp1 Stage2 Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrADCAmp1Stage2BasUp->ItemIndex;
    strcpy(str, rgrADCAmp1Stage2BasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrADCAmp1Stage2BasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL5[5:4]
  itmpC = RX_CTRL5_54_r0C_b54();
  if((rgrADCAmp24Stage2BasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| ADC Amp2-4 Stage2 Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrADCAmp24Stage2BasUp->ItemIndex;
    strcpy(str, rgrADCAmp24Stage2BasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrADCAmp24Stage2BasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL5[3:2]
  itmpC = RX_CTRL5_32_r0C_b32();
  if((rgrQuantizerBiasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Quantizer Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrQuantizerBiasUp->ItemIndex;
    strcpy(str, rgrQuantizerBiasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrQuantizerBiasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //RX_CTRL5[1:0]
  itmpC = RX_CTRL5_10_r0C_b10();
  if((rgrInputBufferBiasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Input Buffer Bias Up"; out.width(2); out << "|";	out.width(40);
  	itmp = rgrInputBufferBiasUp->ItemIndex;
    strcpy(str, rgrInputBufferBiasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << "uA"; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, rgrInputBufferBiasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << "uA"; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //REF_CTRL0[7:4]
  itmpC = REF_CTRL0_74_r0D_b74();
  if(itmpC & 0x08) itmpC = itmpC & 0x07;
  else itmpC = itmpC + 8;
  if((cmbBandgapTemp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Bandgap Temperature Coeff"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbBandgapTemp->ItemIndex;
    strcpy(str, cmbBandgapTemp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbBandgapTemp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //REF_CTRL0[3:0]
  itmpC = REF_CTRL0_30_r0D_b30();
  if(itmpC & 0x08) itmpC = itmpC & 0x07;
  else itmpC = itmpC + 8;
  if((cmbBandgapGain->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Bandgap Gain Control"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbBandgapGain->ItemIndex;
    strcpy(str, cmbBandgapGain->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbBandgapGain->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //REF_CTRL1[7:6]
  itmpC = REF_CTRL1_76_r0E_b76();
  if((cmbRefAmpsBiasAdj->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Amps Bias Adjust"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefAmpsBiasAdj->ItemIndex;
    strcpy(str, cmbRefAmpsBiasAdj->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefAmpsBiasAdj->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //REF_CTRL1[5:4]
  itmpC = REF_CTRL1_54_r0E_b54();
  if((cmbRefAmpsBiasUp->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Amps Bias UP"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefAmpsBiasUp->ItemIndex;
    strcpy(str, cmbRefAmpsBiasUp->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefAmpsBiasUp->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //REF_CTRL1[3:0]
  itmpC = REF_CTRL1_30_r0E_b30();
  if((cmbRefAmpsBiasDn->ItemIndex != itmpC) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Reference Amps Bias Down"; out.width(2); out << "|";	out.width(40);
  	itmp = cmbRefAmpsBiasDn->ItemIndex;
    strcpy(str, cmbRefAmpsBiasDn->Items->Strings[itmp].c_str());
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
    memset(str, '\0', sizeof(str));
    strcpy(str, cmbRefAmpsBiasDn->Items->Strings[itmpC].c_str());
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  //MISC_CTRL[4]
  if((chkEN_DAC->Checked != (bool)MISC_CTRL_44_r0F_b44()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Enable DAC"; out.width(2); out << "|";	out.width(40);
    if(chkEN_DAC->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(MISC_CTRL_44_r0F_b44()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_ADC_I
  if((chkEN_ADC_I->Checked != (bool)MISC_CTRL_33_r0F_b33()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Enable ADC1 (I Channel)"; out.width(2); out << "|";	out.width(40);
    if(chkEN_ADC_I->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(MISC_CTRL_33_r0F_b33()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_ADC_Q
  if((chkEN_ADC_Q->Checked != (bool)MISC_CTRL_22_r0F_b22()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Enable ADC2 (Q Channel)"; out.width(2); out << "|";	out.width(40);
    if(chkEN_ADC_Q->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(MISC_CTRL_22_r0F_b22()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_ADC_REF
  if((chkEN_ADC_REF->Checked != (bool)MISC_CTRL_11_r0F_b11()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Enable ADC Reference"; out.width(2); out << "|";	out.width(40);
    if(chkEN_ADC_REF->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(MISC_CTRL_11_r0F_b11()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };

  //EN_M_REF
  if((chkEN_M_REF->Checked != (bool)MISC_CTRL_00_r0F_b00()) || bWrAll)
  {
    memset(str, '\0', sizeof(str));
	  out.width(32); out << "| Enable Master Reference"; out.width(2); out << "|";	out.width(40);
    if(chkEN_M_REF->Checked) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(2); out << "|";	out.width(40);
  	memset(str, '\0', sizeof(str));
	  if(MISC_CTRL_00_r0F_b00()) strcpy(str, "Enabled"); else strcpy(str, "Powered Down");
    out << str;	out.width(10); out << ""; out.width(1); out << "|"; out << endl;
    bRez = false;
  };
  
  if(bRez && (!bWrAll))
  {
  	out.width(136); out << "| CHIP Configuration EQUALS GUI Configuration"; out.width(2); out << "|";
	  out << endl;
  };
	out << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	out << "" << endl;
	out << "" << endl;

  return bRez;

};

//----------------------------------------------------------------------------
// Writes Register - Value format to the file.
//----------------------------------------------------------------------------
void TfrmADDC::MakeRVFFile(sPrData &m_psD, ofstream &out)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //0x07
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << iRval; out << endl;

  //0x08
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << iRval; out << endl;

  //0x09
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x7F);
  out << iRval; out << endl;

  //0x0A
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << iRval; out << endl;

  //0x0B
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << iRval; out << endl;

  //0x0C
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << iRval; out << endl;

  //0x0D - Read Only
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0xFF);
  out << iRval; out << endl;

  //0x0E - Read Only
  iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0xFF);
  out << iRval; out << endl;

  //0x0F - Read Only
  iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0xFF);
  out << iRval; out << endl;

};

//----------------------------------------------------------------------------
// Saves chip configuration using FRIF format
//----------------------------------------------------------------------------
void TfrmADDC::MakeRFIFFile(sPrData &m_psD, ofstream &out, char *FRIF_SPI_A)
{
  int iRval;
  int iAddr = (((1 << 3) | m_cMAddr) << 4) << 8;

  //0x07
  //out << "# Register(s): EN_ADC_DAC, DECODE, TX_CTRL1[6:0]" << endl;
  iRval = (iAddr | (0x07 << 8)) | (m_psD.cDataR[0x07] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x08
  //out << "# Register(s): RX_CTRL1[7:0]" << endl;
  iRval = (iAddr | (0x08 << 8)) | (m_psD.cDataR[0x08] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x09
  //out << "# Register(s): RX_CTRL2[7:0]" << endl;
  iRval = (iAddr | (0x09 << 8)) | (m_psD.cDataR[0x09] & 0x7F);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0A
  //out << "# Register(s): MISC_CTRL[9:5], RX_CTRL3[7], RX_CTRL3[1:0]" << endl;
  iRval = (iAddr | (0x0A << 8)) | (m_psD.cDataR[0x0A] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0B
  //out << "# Register(s): RX_CTRL4[7:0]" << endl;
  iRval = (iAddr | (0x0B << 8)) | (m_psD.cDataR[0x0B] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0C
  //out << "# Register(s): RX_CTRL5[7:0]" << endl;
  iRval = (iAddr | (0x0C << 8)) | (m_psD.cDataR[0x0C] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0D - Read Only
  //out << "# Register(s): REF_CTRL0[7:0]" << endl;
  iRval = (iAddr | (0x0D << 8)) | (m_psD.cDataR[0x0D] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0E - Read Only
  //out << "# Register(s): REF_CTRL1[7:0]" << endl;
  iRval = (iAddr | (0x0E << 8)) | (m_psD.cDataR[0x0E] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;

  //0x0F - Read Only
  //out << "# Register(s): MISC_CTRL[4:0]" << endl;
  iRval = (iAddr | (0x0F << 8)) | (m_psD.cDataR[0x0F] & 0xFF);
  out << FRIF_DIR_W;
  //out << hex << uppercase << showbase << iRval;
  out << "0x" << hex << uppercase << noshowbase << iRval;
  out << FRIF_SPI_A; out << endl;
};

//---------------------------------------------------------------------------
bool TfrmADDC::SetGUIUnderReadback(sPrData &m_psD)
{
  int itmp;

  m_bAllowSend = false;

  //EN
  itmp = EN_ADC_DAC_r07_b77();
  chbEN_ADC_DAC->Checked = itmp;

  //DECODE
  itmp = DECODE_ADC_DAC_r07_b66();
  rgrDecode->ItemIndex = itmp;

  //TX_CTRL1[6:4]
  itmp = TX_CTRL1_64_r07_b53();
  cmbDACInternalOutputLoadResistor->ItemIndex = itmp;

  //TX_CTRL1[3]
  itmp = TX_CTRL1_33_r07_b22();
  rgrDACReferenceCurrentResistor->ItemIndex = itmp;

  //TX_CTRL1[1:0]
  itmp = TX_CTRL1_10_r07_b10();
  cmbDACFullScaleOutputCurrent->ItemIndex = itmp;

  //RX_CTRL1[7:6]
  itmp = RX_CTRL1_76_r08_b76();
  cmbRefResistorBiasAdj->ItemIndex = itmp;

  //RX_CTRL1[5:4]
  itmp = RX_CTRL1_54_r08_b54();
  cmbRefBiasUp->ItemIndex = itmp;

  //RX_CTRL1[3:0]
  itmp = RX_CTRL1_30_r08_b30();
  cmbRefBiasDn->ItemIndex = itmp;

  //RX_CTRL2[7:6]
  itmp = RX_CTRL2_76_r09_b65();
  cmbRefGainAdj->ItemIndex = itmp;

  //RX_CTRL2[5:4]
  itmp = RX_CTRL2_54_r09_b43();
  cmbCoomonModeAdj->ItemIndex = itmp;

  //RX_CTRL2[3:2]
  itmp = RX_CTRL2_32_r09_b21();
  cmbRefBufferBoost->ItemIndex = itmp;

  //RX_CTRL2[0]
  itmp = RX_CTRL2_00_r09_b00();
  chkInputBufferDisable->Checked = itmp;
  //chkInputBufferDisable->Checked = !chkInputBufferDisable->Checked;

  //MISC_CTRL[9]
  itmp = MISC_CTRL_99_r0A_b77();
  rgrRX_FSYNC_P->ItemIndex = itmp;

  //MISC_CTRL[8]
  itmp = MISC_CTRL_88_r0A_b66();
  rgrRX_INTER->ItemIndex = itmp;

  //MISC_CTRL[7]
  itmp = MISC_CTRL_77_r0A_b55();
  rgrDAC_CLK_P->ItemIndex = itmp;

  //MISC_CTRL[6]
  itmp = MISC_CTRL_66_r0A_b44();
  rgrTX_FSYNC_P->ItemIndex = itmp;

  //MISC_CTRL[5]
  itmp = MISC_CTRL_55_r0A_b33();
  rgrTX_INTER->ItemIndex = itmp;

  //RX_CTRL3[7]
  itmp = RX_CTRL3_77_r0A_b22();
  cmbADCSamplingPhase->ItemIndex = itmp;

  //RX_CTRL3[1:0]
  itmp = RX_CTRL3_10_r0A_b10();
  cmbClockNonOverlapAdjust->ItemIndex = itmp;

  //RX_CTRL4[7:6]
  itmp = RX_CTRL4_76_r0B_b76();
  rgrADCBiasResistorAdjust->ItemIndex = itmp;

  //RX_CTRL4[5:4]
  itmp = RX_CTRL4_54_r0B_b54();
  cmbMainBiasDN->ItemIndex = itmp;

  //RX_CTRL4[3:2]
  itmp = RX_CTRL4_32_r0B_b32();
  rgrADCAmp1Stage1BasUp->ItemIndex = itmp;

  //RX_CTRL4[1:0]
  itmp = RX_CTRL4_10_r0B_b10();
  rgrADCAmp24Stage1BasUp->ItemIndex = itmp;

  //RX_CTRL5[7:6]
  itmp = RX_CTRL5_76_r0C_b76();
  rgrADCAmp1Stage2BasUp->ItemIndex = itmp;

  //RX_CTRL5[5:4]
  itmp = RX_CTRL5_54_r0C_b54();
  rgrADCAmp24Stage2BasUp->ItemIndex = itmp;

  //RX_CTRL5[3:2]
  itmp = RX_CTRL5_32_r0C_b32();
  rgrQuantizerBiasUp->ItemIndex = itmp;

  //RX_CTRL5[1:0]
  itmp = RX_CTRL5_10_r0C_b10();
  rgrInputBufferBiasUp->ItemIndex = itmp;

  //REF_CTRL0[7:4]
  itmp = REF_CTRL0_74_r0D_b74();
  if(itmp & 0x08) itmp = itmp & 0x07;
  else itmp = itmp + 8;
  cmbBandgapTemp->ItemIndex = itmp;

  //REF_CTRL0[3:0]
  itmp = REF_CTRL0_30_r0D_b30();
  if(itmp & 0x08) itmp = itmp & 0x07;
  else itmp = itmp + 8;
  cmbBandgapGain->ItemIndex = itmp;

  //REF_CTRL1[7:6]
  itmp = REF_CTRL1_76_r0E_b76();
  cmbRefAmpsBiasAdj->ItemIndex = itmp;

  //REF_CTRL1[5:4]
  itmp = REF_CTRL1_54_r0E_b54();
  cmbRefAmpsBiasUp->ItemIndex = itmp;

  //REF_CTRL1[3:0]
  itmp = REF_CTRL1_30_r0E_b30();
  cmbRefAmpsBiasDn->ItemIndex = itmp;

  //MISC_CTRL[4]
  itmp = MISC_CTRL_44_r0F_b44();
  chkEN_DAC->Checked = itmp;

  //EN_ADC_I
  itmp = MISC_CTRL_33_r0F_b33();
  chkEN_ADC_I->Checked = itmp;

  //EN_ADC_Q
  itmp = MISC_CTRL_22_r0F_b22();
  chkEN_ADC_Q->Checked = itmp;

  //EN_ADC_REF
  itmp = MISC_CTRL_11_r0F_b11();
  chkEN_ADC_REF->Checked = itmp;

  //EN_M_REF
  itmp = MISC_CTRL_00_r0F_b00();
  chkEN_M_REF->Checked = itmp;

  m_bAllowSend = true;

  return true;
};

//----------------------------------------------------------------------------
// Writes register map to the file. According to the customer wish.
//----------------------------------------------------------------------------
void TfrmADDC::MakeRegisterFile(sPrData &m_psD, ofstream &out)
{
  int itmp;

  //EN_ADC_DAC
  out.width(24); out << left; out << "REG 0x57 MASK 07 : 07  =";
  itmp = EN_ADC_DAC_r07_b77();
  out.width(6); out << right; out << itmp;
  out << "  EN_ADC_DAC"; out << endl;

  //DECODE_ADC_DAC
  out.width(24); out << left; out << "REG 0x57 MASK 06 : 06  =";
  itmp = DECODE_ADC_DAC_r07_b66();
  out.width(6); out << right; out << itmp;
  out << "  DECODE_ADC_DAC"; out << endl;

  //TX_CTRL1[6:4]
  out.width(24); out << left; out << "REG 0x57 MASK 05 : 03  =";
  itmp = TX_CTRL1_64_r07_b53();
  out.width(6); out << right; out << itmp;
  out << "  TX_CTRL1[6:4]"; out << endl;

  //TX_CTRL1[3]
  out.width(24); out << left; out << "REG 0x57 MASK 02 : 02  =";
  itmp = TX_CTRL1_33_r07_b22();
  out.width(6); out << right; out << itmp;
  out << "  TX_CTRL1[3]"; out << endl;

  //TX_CTRL1[1:0]
  out.width(24); out << left; out << "REG 0x57 MASK 01 : 00  =";
  itmp = TX_CTRL1_10_r07_b10();
  out.width(6); out << right; out << itmp;
  out << "  TX_CTRL1[1:0]"; out << endl;

  //RX_CTRL1[7:6]
  out.width(24); out << left; out << "REG 0x58 MASK 07 : 06  =";
  itmp = RX_CTRL1_76_r08_b76();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL1[7:6]"; out << endl;

  //RX_CTRL1[5:4]
  out.width(24); out << left; out << "REG 0x58 MASK 05 : 04  =";
  itmp = RX_CTRL1_54_r08_b54();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL1[5:4]"; out << endl;

  //RX_CTRL1[3:0]
  out.width(24); out << left; out << "REG 0x58 MASK 03 : 00  =";
  itmp = RX_CTRL1_30_r08_b30();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL1[3:0]"; out << endl;

  //RX_CTRL2[7:6]
  out.width(24); out << left; out << "REG 0x59 MASK 06 : 05  =";
  itmp = RX_CTRL2_76_r09_b65();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL2[7:6]"; out << endl;

  //RX_CTRL2[5:4]
  out.width(24); out << left; out << "REG 0x59 MASK 04 : 03  =";
  itmp = RX_CTRL2_54_r09_b43();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL2[5:4]"; out << endl;

  //RX_CTRL2[3:2]
  out.width(24); out << left; out << "REG 0x59 MASK 02 : 01  =";
  itmp = RX_CTRL2_32_r09_b21();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL2[3:2]"; out << endl;

  //RX_CTRL2[0]
  out.width(24); out << left; out << "REG 0x59 MASK 00 : 00  =";
  itmp = RX_CTRL2_00_r09_b00();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL2[0]"; out << endl;

  //MISC_CTRL[9]
  out.width(24); out << left; out << "REG 0x5A MASK 07 : 07  =";
  itmp = MISC_CTRL_99_r0A_b77();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[9]"; out << endl;

  //MISC_CTRL[8]
  out.width(24); out << left; out << "REG 0x5A MASK 06 : 06  =";
  itmp = MISC_CTRL_88_r0A_b66();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[8]"; out << endl;

  //MISC_CTRL[7]
  out.width(24); out << left; out << "REG 0x5A MASK 05 : 05  =";
  itmp = MISC_CTRL_77_r0A_b55();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[7]"; out << endl;

  //MISC_CTRL[6]
  out.width(24); out << left; out << "REG 0x5A MASK 04 : 04  =";
  itmp = MISC_CTRL_66_r0A_b44();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[6]"; out << endl;

  //MISC_CTRL[5]
  out.width(24); out << left; out << "REG 0x5A MASK 03 : 03  =";
  itmp = MISC_CTRL_55_r0A_b33();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[5]"; out << endl;

  //RX_CTRL3[7]
  out.width(24); out << left; out << "REG 0x5A MASK 02 : 02  =";
  itmp = RX_CTRL3_77_r0A_b22();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL3[7]"; out << endl;

  //RX_CTRL3[1:0]
  out.width(24); out << left; out << "REG 0x5A MASK 01 : 00  =";
  itmp = RX_CTRL3_10_r0A_b10();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL3[1:0]"; out << endl;

  //RX_CTRL4[7:6]
  out.width(24); out << left; out << "REG 0x5B MASK 07 : 06  =";
  itmp = RX_CTRL4_76_r0B_b76();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL4[7:6]"; out << endl;

  //RX_CTRL4[5:4]
  out.width(24); out << left; out << "REG 0x5B MASK 05 : 04  =";
  itmp = RX_CTRL4_54_r0B_b54();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL4[5:4]"; out << endl;

  //RX_CTRL4[3:2]
  out.width(24); out << left; out << "REG 0x5B MASK 03 : 02  =";
  itmp = RX_CTRL4_32_r0B_b32();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL4[3:2]"; out << endl;

  //RX_CTRL4[1:0]
  out.width(24); out << left; out << "REG 0x5B MASK 01 : 00  =";
  itmp = RX_CTRL4_10_r0B_b10();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL4[1:0]"; out << endl;

  //RX_CTRL5[7:6]
  out.width(24); out << left; out << "REG 0x5C MASK 07 : 06  =";
  itmp = RX_CTRL5_76_r0C_b76();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL5[7:6]"; out << endl;

  //RX_CTRL5[5:4]
  out.width(24); out << left; out << "REG 0x5C MASK 05 : 04  =";
  itmp = RX_CTRL5_54_r0C_b54();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL5[5:4]"; out << endl;

  //RX_CTRL5[3:2]
  out.width(24); out << left; out << "REG 0x5C MASK 03 : 02  =";
  itmp = RX_CTRL5_32_r0C_b32();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL5[3:2]"; out << endl;

  //RX_CTRL5[1:0]
  out.width(24); out << left; out << "REG 0x5C MASK 01 : 00  =";
  itmp = RX_CTRL5_10_r0C_b10();
  out.width(6); out << right; out << itmp;
  out << "  RX_CTRL5[1:0]"; out << endl;

  //REF_CTRL0[7:4]
  out.width(24); out << left; out << "REG 0x5D MASK 07 : 04  =";
  itmp = REF_CTRL0_74_r0D_b74();
  out.width(6); out << right; out << itmp;
  out << "  REF_CTRL0[7:4]"; out << endl;

  //REF_CTRL0[3:0]
  out.width(24); out << left; out << "REG 0x5D MASK 03 : 00  =";
  itmp = REF_CTRL0_30_r0D_b30();
  out.width(6); out << right; out << itmp;
  out << "  REF_CTRL0[3:0]"; out << endl;

  //REF_CTRL1[7:6]
  out.width(24); out << left; out << "REG 0x5E MASK 07 : 06  =";
  itmp = REF_CTRL1_76_r0E_b76();
  out.width(6); out << right; out << itmp;
  out << "  REF_CTRL1[7:6]"; out << endl;

  //REF_CTRL1[5:4]
  out.width(24); out << left; out << "REG 0x5E MASK 05 : 04  =";
  itmp = REF_CTRL1_54_r0E_b54();
  out.width(6); out << right; out << itmp;
  out << "  REF_CTRL1[5:4]"; out << endl;

  //REF_CTRL1[3:0]
  out.width(24); out << left; out << "REG 0x5E MASK 03 : 00  =";
  itmp = REF_CTRL1_30_r0E_b30();
  out.width(6); out << right; out << itmp;
  out << "  REF_CTRL1[3:0]"; out << endl;

  //MISC_CTRL[4]
  out.width(24); out << left; out << "REG 0x5F MASK 04 : 04  =";
  itmp = MISC_CTRL_44_r0F_b44();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[4]"; out << endl;

  //MISC_CTRL[3]
  out.width(24); out << left; out << "REG 0x5F MASK 03 : 03  =";
  itmp = MISC_CTRL_33_r0F_b33();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[3]"; out << endl;

  //MISC_CTRL[2]
  out.width(24); out << left; out << "REG 0x5F MASK 02 : 02  =";
  itmp = MISC_CTRL_22_r0F_b22();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[2]"; out << endl;

  //MISC_CTRL[1]
  out.width(24); out << left; out << "REG 0x5F MASK 01 : 01  =";
  itmp = MISC_CTRL_11_r0F_b11();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[1]"; out << endl;

  //MISC_CTRL[0]
  out.width(24); out << left; out << "REG 0x5F MASK 00 : 00  =";
  itmp = MISC_CTRL_00_r0F_b00();
  out.width(6); out << right; out << itmp;
  out << "  MISC_CTRL[0]"; out << endl;

};
//---------------------------------------------------------------------------
void TfrmADDC::SaveConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr+10;

  pini->WriteBool(Sect, "chbEN_ADC_DAC", chbEN_ADC_DAC->Checked);
  pini->WriteInteger(Sect, "rgrDecode", rgrDecode->ItemIndex);
  pini->WriteInteger(Sect, "cmbDACInternalOutputLoadResistor", cmbDACInternalOutputLoadResistor->ItemIndex);
  pini->WriteInteger(Sect, "rgrDACReferenceCurrentResistor", rgrDACReferenceCurrentResistor->ItemIndex);
  pini->WriteInteger(Sect, "cmbDACFullScaleOutputCurrent", cmbDACFullScaleOutputCurrent->ItemIndex);

  pini->WriteInteger(Sect, "cmbRefResistorBiasAdj", cmbRefResistorBiasAdj->ItemIndex);
  pini->WriteInteger(Sect, "cmbRefBiasUp", cmbRefBiasUp->ItemIndex);
  pini->WriteInteger(Sect, "cmbRefBiasDn", cmbRefBiasDn->ItemIndex);

  pini->WriteInteger(Sect, "cmbRefGainAdj", cmbRefGainAdj->ItemIndex);
  pini->WriteInteger(Sect, "cmbCoomonModeAdj", cmbCoomonModeAdj->ItemIndex);
  pini->WriteInteger(Sect, "cmbRefBufferBoost", cmbRefBufferBoost->ItemIndex);
  pini->WriteBool(Sect, "chkInputBufferDisable", chkInputBufferDisable->Checked);

  pini->WriteInteger(Sect, "rgrRX_FSYNC_P", rgrRX_FSYNC_P->ItemIndex);
  pini->WriteInteger(Sect, "rgrRX_INTER", rgrRX_INTER->ItemIndex);
  pini->WriteInteger(Sect, "rgrDAC_CLK_P", rgrDAC_CLK_P->ItemIndex);
  pini->WriteInteger(Sect, "rgrTX_FSYNC_P", rgrTX_FSYNC_P->ItemIndex);
  pini->WriteInteger(Sect, "rgrTX_INTER", rgrTX_INTER->ItemIndex);
  pini->WriteInteger(Sect, "cmbADCSamplingPhase", cmbADCSamplingPhase->ItemIndex);
  pini->WriteInteger(Sect, "cmbClockNonOverlapAdjust", cmbClockNonOverlapAdjust->ItemIndex);

  pini->WriteInteger(Sect, "rgrADCBiasResistorAdjust", rgrADCBiasResistorAdjust->ItemIndex);
  pini->WriteInteger(Sect, "cmbMainBiasDN", cmbMainBiasDN->ItemIndex);
  pini->WriteInteger(Sect, "rgrADCAmp1Stage1BasUp", rgrADCAmp1Stage1BasUp->ItemIndex);
  pini->WriteInteger(Sect, "rgrADCAmp24Stage1BasUp", rgrADCAmp24Stage1BasUp->ItemIndex);

  pini->WriteInteger(Sect, "rgrADCAmp1Stage2BasUp", rgrADCAmp1Stage2BasUp->ItemIndex);
  pini->WriteInteger(Sect, "rgrADCAmp24Stage2BasUp", rgrADCAmp24Stage2BasUp->ItemIndex);
  pini->WriteInteger(Sect, "rgrQuantizerBiasUp", rgrQuantizerBiasUp->ItemIndex);
  pini->WriteInteger(Sect, "rgrInputBufferBiasUp", rgrInputBufferBiasUp->ItemIndex);

  pini->WriteInteger(Sect, "cmbBandgapTemp", cmbBandgapTemp->ItemIndex);
  pini->WriteInteger(Sect, "cmbBandgapGain", cmbBandgapGain->ItemIndex);

  pini->WriteInteger(Sect, "cmbRefAmpsBiasAdj", cmbRefAmpsBiasAdj->ItemIndex);
  pini->WriteInteger(Sect, "cmbRefAmpsBiasUp", cmbRefAmpsBiasUp->ItemIndex);
  pini->WriteInteger(Sect, "cmbRefAmpsBiasDn", cmbRefAmpsBiasDn->ItemIndex);

  pini->WriteBool(Sect, "chkEN_DAC", chkEN_DAC->Checked);
  pini->WriteBool(Sect, "chkEN_ADC_I", chkEN_ADC_I->Checked);
  pini->WriteBool(Sect, "chkEN_ADC_Q", chkEN_ADC_Q->Checked);
  pini->WriteBool(Sect, "chkEN_ADC_REF", chkEN_ADC_REF->Checked);
  pini->WriteBool(Sect, "chkEN_M_REF", chkEN_M_REF->Checked);
};

//---------------------------------------------------------------------------
void TfrmADDC::ReadConf(TIniFile *pini)
{
	String Sect = (int)m_cMAddr+10;

  m_bAllowSend = false;

  chbEN_ADC_DAC->Checked = pini->ReadBool(Sect, "chbEN_ADC_DAC", 1);
  rgrDecode->ItemIndex = pini->ReadInteger(Sect, "rgrDecode", 0);
  cmbDACInternalOutputLoadResistor->ItemIndex = pini->ReadInteger(Sect, "cmbDACInternalOutputLoadResistor", 2);
  rgrDACReferenceCurrentResistor->ItemIndex = pini->ReadInteger(Sect, "rgrDACReferenceCurrentResistor", 1);
  cmbDACFullScaleOutputCurrent->ItemIndex = pini->ReadInteger(Sect, "cmbDACFullScaleOutputCurrent", 0);

  cmbRefResistorBiasAdj->ItemIndex = pini->ReadInteger(Sect, "cmbRefResistorBiasAdj", 0);
  cmbRefBiasUp->ItemIndex = pini->ReadInteger(Sect, "cmbRefBiasUp", 0);
  cmbRefBiasDn->ItemIndex = pini->ReadInteger(Sect, "cmbRefBiasDn", 0);

  cmbRefGainAdj->ItemIndex = pini->ReadInteger(Sect, "cmbRefGainAdj", 0);
  cmbCoomonModeAdj->ItemIndex = pini->ReadInteger(Sect, "cmbCoomonModeAdj", 0);
  cmbRefBufferBoost->ItemIndex = pini->ReadInteger(Sect, "cmbRefBufferBoost", 0);
  chkInputBufferDisable->Checked = pini->ReadBool(Sect, "chkInputBufferDisable", 1);

  rgrRX_FSYNC_P->ItemIndex = pini->ReadInteger(Sect, "rgrRX_FSYNC_P", 0);
  rgrRX_INTER->ItemIndex = pini->ReadInteger(Sect, "rgrRX_INTER", 0);
  rgrDAC_CLK_P->ItemIndex = pini->ReadInteger(Sect, "rgrDAC_CLK_P", 1);
  rgrTX_FSYNC_P->ItemIndex = pini->ReadInteger(Sect, "rgrTX_FSYNC_P", 0);
  rgrTX_INTER->ItemIndex = pini->ReadInteger(Sect, "rgrTX_INTER", 0);
  cmbADCSamplingPhase->ItemIndex = pini->ReadInteger(Sect, "cmbADCSamplingPhase", 0);
  cmbClockNonOverlapAdjust->ItemIndex = pini->ReadInteger(Sect, "cmbClockNonOverlapAdjust", 0);

  rgrADCBiasResistorAdjust->ItemIndex = pini->ReadInteger(Sect, "rgrADCBiasResistorAdjust", 0);
  cmbMainBiasDN->ItemIndex = pini->ReadInteger(Sect, "cmbMainBiasDN", 0);
  rgrADCAmp1Stage1BasUp->ItemIndex = pini->ReadInteger(Sect, "rgrADCAmp1Stage1BasUp", 0);
  rgrADCAmp24Stage1BasUp->ItemIndex = pini->ReadInteger(Sect, "rgrADCAmp24Stage1BasUp", 0);

  rgrADCAmp1Stage2BasUp->ItemIndex = pini->ReadInteger(Sect, "rgrADCAmp1Stage2BasUp", 0);
  rgrADCAmp24Stage2BasUp->ItemIndex = pini->ReadInteger(Sect, "rgrADCAmp24Stage2BasUp", 0);
  rgrQuantizerBiasUp->ItemIndex = pini->ReadInteger(Sect, "rgrQuantizerBiasUp", 0);
  rgrInputBufferBiasUp->ItemIndex = pini->ReadInteger(Sect, "rgrInputBufferBiasUp", 0);

  cmbBandgapTemp->ItemIndex = pini->ReadInteger(Sect, "cmbBandgapTemp", 8);
  cmbBandgapGain->ItemIndex = pini->ReadInteger(Sect, "cmbBandgapGain", 8);

  cmbRefAmpsBiasAdj->ItemIndex = pini->ReadInteger(Sect, "cmbRefAmpsBiasAdj", 0);
  cmbRefAmpsBiasUp->ItemIndex = pini->ReadInteger(Sect, "cmbRefAmpsBiasUp", 0);
  cmbRefAmpsBiasDn->ItemIndex = pini->ReadInteger(Sect, "cmbRefAmpsBiasDn", 0);

  chkEN_DAC->Checked = pini->ReadBool(Sect, "chkEN_DAC", 1);
  chkEN_ADC_I->Checked = pini->ReadBool(Sect, "chkEN_ADC_I", 1);
  chkEN_ADC_Q->Checked = pini->ReadBool(Sect, "chkEN_ADC_Q", 1);
  chkEN_ADC_REF->Checked = pini->ReadBool(Sect, "chkEN_ADC_REF", 1);
  chkEN_M_REF->Checked = pini->ReadBool(Sect, "chkEN_M_REF", 1);

  m_bAllowSend = true;
};

void TfrmADDC::CustSet_cmbCoomonModeAdj(int Ind)
{
  cmbCoomonModeAdj->ItemIndex = Ind;
  cmbCoomonModeAdjChange(Application);
};

