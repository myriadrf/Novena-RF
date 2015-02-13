#include "pnlADDC.h"

//(*InternalHeaders(pnlADDC)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlADDC)
const long pnlADDC::ID_DECODE_ADDC = wxNewId();
const long pnlADDC::ID_EN_ADC_DAC = wxNewId();
const long pnlADDC::ID_EN_ADC_REF = wxNewId();
const long pnlADDC::ID_EN_ADC_I = wxNewId();
const long pnlADDC::ID_EN_DAC = wxNewId();
const long pnlADDC::ID_EN_ADC_Q = wxNewId();
const long pnlADDC::ID_EN_M_REF = wxNewId();
const long pnlADDC::ID_RX_FSYNC_P = wxNewId();
const long pnlADDC::ID_TX_FSYNC_P = wxNewId();
const long pnlADDC::ID_RX_INTER = wxNewId();
const long pnlADDC::ID_TX_INTER = wxNewId();
const long pnlADDC::ID_DAC_CLK_P = wxNewId();
const long pnlADDC::ID_STATICTEXT1 = wxNewId();
const long pnlADDC::ID_STATICTEXT2 = wxNewId();
const long pnlADDC::ID_STATICTEXT3 = wxNewId();
const long pnlADDC::ID_STATICTEXT4 = wxNewId();
const long pnlADDC::ID_STATICTEXT5 = wxNewId();
const long pnlADDC::ID_REF_CTRL0_74 = wxNewId();
const long pnlADDC::ID_REF_CTRL0_30 = wxNewId();
const long pnlADDC::ID_REF_CTRL1_76 = wxNewId();
const long pnlADDC::ID_REF_CTRL1_54 = wxNewId();
const long pnlADDC::ID_REF_CTRL1_30 = wxNewId();
const long pnlADDC::ID_STATICTEXT15 = wxNewId();
const long pnlADDC::ID_TX_CTRL1_64 = wxNewId();
const long pnlADDC::ID_TX_CTRL1_3 = wxNewId();
const long pnlADDC::ID_STATICTEXT16 = wxNewId();
const long pnlADDC::ID_TX_CTRL1_10 = wxNewId();
const long pnlADDC::ID_RX_CTRL2_0 = wxNewId();
const long pnlADDC::ID_STATICTEXT7 = wxNewId();
const long pnlADDC::ID_STATICTEXT6 = wxNewId();
const long pnlADDC::ID_STATICTEXT8 = wxNewId();
const long pnlADDC::ID_STATICTEXT9 = wxNewId();
const long pnlADDC::ID_STATICTEXT10 = wxNewId();
const long pnlADDC::ID_STATICTEXT11 = wxNewId();
const long pnlADDC::ID_RX_CTRL1_76 = wxNewId();
const long pnlADDC::ID_RX_CTRL1_54 = wxNewId();
const long pnlADDC::ID_RX_CTRL1_30 = wxNewId();
const long pnlADDC::ID_RX_CTRL2_32 = wxNewId();
const long pnlADDC::ID_RX_CTRL2_54 = wxNewId();
const long pnlADDC::ID_RX_CTRL2_76 = wxNewId();
const long pnlADDC::ID_STATICTEXT12 = wxNewId();
const long pnlADDC::ID_STATICTEXT13 = wxNewId();
const long pnlADDC::ID_STATICTEXT14 = wxNewId();
const long pnlADDC::ID_RX_CTRL4_54 = wxNewId();
const long pnlADDC::ID_RX_CTRL3_10 = wxNewId();
const long pnlADDC::ID_RX_CTRL3_7 = wxNewId();
const long pnlADDC::ID_RX_CTRL4_76 = wxNewId();
const long pnlADDC::ID_RX_CTRL4_32 = wxNewId();
const long pnlADDC::ID_RX_CTRL4_10 = wxNewId();
const long pnlADDC::ID_RX_CTRL5_32 = wxNewId();
const long pnlADDC::ID_RX_CTRL5_76 = wxNewId();
const long pnlADDC::ID_RX_CTRL5_54 = wxNewId();
const long pnlADDC::ID_RX_CTRL5_10 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlADDC,wxPanel)
	//(*EventTable(pnlADDC)
	//*)
END_EVENT_TABLE()

pnlADDC::pnlADDC(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlADDC::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlADDC)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer10 = new wxFlexGridSizer(0, 1, 5, 0);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_ADDC, _("Decoding"), wxPoint(0,8), wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_ADDC"));
	FlexGridSizer10->Add(rgrDecode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC/DAC Enable Control"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	chbEN_ADC_DAC = new wxCheckBox(this, ID_EN_ADC_DAC, _("ADDC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_ADC_DAC"));
	chbEN_ADC_DAC->SetValue(false);
	FlexGridSizer1->Add(chbEN_ADC_DAC, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_REF = new wxCheckBox(this, ID_EN_ADC_REF, _("ADC Ref Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_ADC_REF"));
	chkEN_ADC_REF->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_REF, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_I = new wxCheckBox(this, ID_EN_ADC_I, _("ADC1 (I) Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_ADC_I"));
	chkEN_ADC_I->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_I, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_DAC = new wxCheckBox(this, ID_EN_DAC, _("DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DAC"));
	chkEN_DAC->SetValue(false);
	FlexGridSizer1->Add(chkEN_DAC, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_ADC_Q = new wxCheckBox(this, ID_EN_ADC_Q, _("ADC2 (Q) Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_ADC_Q"));
	chkEN_ADC_Q->SetValue(false);
	FlexGridSizer1->Add(chkEN_ADC_Q, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	chkEN_M_REF = new wxCheckBox(this, ID_EN_M_REF, _("Master Ref Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_M_REF"));
	chkEN_M_REF->SetValue(false);
	FlexGridSizer1->Add(chkEN_M_REF, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 1);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC/DAC Miscellaneous Control"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 5, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("0"),
		_("1")
	};
	rgrRX_FSYNC_P = new wxRadioBox(this, ID_RX_FSYNC_P, _("Rx Fsync Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_FSYNC_P"));
	FlexGridSizer8->Add(rgrRX_FSYNC_P, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("0"),
		_("1")
	};
	rgrTX_FSYNC_P = new wxRadioBox(this, ID_TX_FSYNC_P, _("Tx Fsync Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TX_FSYNC_P"));
	FlexGridSizer8->Add(rgrTX_FSYNC_P, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("I,Q"),
		_("Q,I")
	};
	rgrRX_INTER = new wxRadioBox(this, ID_RX_INTER, _("Rx Interleave"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_INTER"));
	FlexGridSizer8->Add(rgrRX_INTER, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_("I,Q"),
		_("Q,I")
	};
	rgrTX_INTER = new wxRadioBox(this, ID_TX_INTER, _("Tx Interleave"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TX_INTER"));
	FlexGridSizer8->Add(rgrTX_INTER, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("Pos"),
		_("Neg")
	};
	rgrDAC_CLK_P = new wxRadioBox(this, ID_DAC_CLK_P, _("DAC Edge"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DAC_CLK_P"));
	FlexGridSizer8->Add(rgrDAC_CLK_P, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11 = new wxFlexGridSizer(0, 1, 5, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC_DAC Reference Control"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 5, 0, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Bandgap Temp Coeff:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Bandgap Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Ref Amps Bias Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Ref Amps Bias UP:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Ref Amps Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbBandgapTemp = new ComboBoxMap(this, ID_REF_CTRL0_74, wxEmptyString, wxDefaultPosition, wxSize(110,-1), 0, 0, 0, wxDefaultValidator, _T("ID_REF_CTRL0_74"));
	FlexGridSizer2->Add(cmbBandgapTemp, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbBandgapGain = new ComboBoxMap(this, ID_REF_CTRL0_30, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_REF_CTRL0_30"));
	FlexGridSizer2->Add(cmbBandgapGain, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasAdj = new ComboBoxMap(this, ID_REF_CTRL1_76, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_REF_CTRL1_76"));
	FlexGridSizer2->Add(cmbRefAmpsBiasAdj, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasUp = new ComboBoxMap(this, ID_REF_CTRL1_54, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_REF_CTRL1_54"));
	FlexGridSizer2->Add(cmbRefAmpsBiasUp, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefAmpsBiasDn = new ComboBoxMap(this, ID_REF_CTRL1_30, wxEmptyString, wxDefaultPosition, wxSize(95,-1), 0, 0, 0, wxDefaultValidator, _T("ID_REF_CTRL1_30"));
	FlexGridSizer2->Add(cmbRefAmpsBiasDn, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC Control"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("DAC Internal Output Load Resistor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer6->Add(StaticText15, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDACInternalOutputLoadResistor = new ComboBoxMap(this, ID_TX_CTRL1_64, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TX_CTRL1_64"));
	FlexGridSizer6->Add(cmbDACInternalOutputLoadResistor, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_("Internal"),
		_("External")
	};
	rgrDACReferenceCurrentResistor = new wxRadioBox(this, ID_TX_CTRL1_3, _("DAC Reference Current Resistor"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TX_CTRL1_3"));
	FlexGridSizer5->Add(rgrDACReferenceCurrentResistor, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("DAC Full Scale Output Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer7->Add(StaticText16, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbDACFullScaleOutputCurrent = new ComboBoxMap(this, ID_TX_CTRL1_10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TX_CTRL1_10"));
	FlexGridSizer7->Add(cmbDACFullScaleOutputCurrent, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("ADC Control"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 1, 5, 5);
	chkInputBufferDisable = new wxCheckBox(this, ID_RX_CTRL2_0, _("Input Buffer Disabled"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RX_CTRL2_0"));
	chkInputBufferDisable->SetValue(false);
	FlexGridSizer12->Add(chkInputBufferDisable, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(2, 6, 0, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Ref Bias Res Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer3->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Ref Bias UP:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Ref Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer3->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Ref Buff Boost:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer3->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Common Mode Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer3->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Ref Gain Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer3->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefResistorBiasAdj = new ComboBoxMap(this, ID_RX_CTRL1_76, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL1_76"));
	FlexGridSizer3->Add(cmbRefResistorBiasAdj, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBiasUp = new ComboBoxMap(this, ID_RX_CTRL1_54, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL1_54"));
	FlexGridSizer3->Add(cmbRefBiasUp, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBiasDn = new ComboBoxMap(this, ID_RX_CTRL1_30, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL1_30"));
	FlexGridSizer3->Add(cmbRefBiasDn, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefBufferBoost = new ComboBoxMap(this, ID_RX_CTRL2_32, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL2_32"));
	FlexGridSizer3->Add(cmbRefBufferBoost, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCoomonModeAdj = new ComboBoxMap(this, ID_RX_CTRL2_54, wxEmptyString, wxDefaultPosition, wxSize(95,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL2_54"));
	FlexGridSizer3->Add(cmbCoomonModeAdj, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRefGainAdj = new ComboBoxMap(this, ID_RX_CTRL2_76, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL2_76"));
	FlexGridSizer3->Add(cmbRefGainAdj, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer13->AddGrowableCol(1);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Main Bias DN:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer4->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Clock Non-Overlap Adj:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer4->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("ADC Sampling Phase:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer4->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMainBiasDN = new ComboBoxMap(this, ID_RX_CTRL4_54, wxEmptyString, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL4_54"));
	FlexGridSizer4->Add(cmbMainBiasDN, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbClockNonOverlapAdjust = new ComboBoxMap(this, ID_RX_CTRL3_10, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL3_10"));
	FlexGridSizer4->Add(cmbClockNonOverlapAdjust, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbADCSamplingPhase = new ComboBoxMap(this, ID_RX_CTRL3_7, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_CTRL3_7"));
	FlexGridSizer4->Add(cmbADCSamplingPhase, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_8[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCBiasResistorAdjust = new wxRadioBox(this, ID_RX_CTRL4_76, _("ADC Bias Resistor Adjust, uA"), wxPoint(352,80), wxDefaultSize, 4, __wxRadioBoxChoices_8, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL4_76"));
	FlexGridSizer13->Add(rgrADCBiasResistorAdjust, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer14 = new wxFlexGridSizer(2, 3, 5, 5);
	FlexGridSizer14->AddGrowableCol(0);
	FlexGridSizer14->AddGrowableCol(1);
	FlexGridSizer14->AddGrowableCol(2);
	wxString __wxRadioBoxChoices_9[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp1Stage1BasUp = new wxRadioBox(this, ID_RX_CTRL4_32, _("ADC Amp1 Stage1 Bias Up, uA"), wxPoint(0,128), wxDefaultSize, 4, __wxRadioBoxChoices_9, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL4_32"));
	FlexGridSizer14->Add(rgrADCAmp1Stage1BasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_10[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp24Stage1BasUp = new wxRadioBox(this, ID_RX_CTRL4_10, _("ADC Amp2-4 Stage1 Bias Up, uA"), wxPoint(168,128), wxDefaultSize, 4, __wxRadioBoxChoices_10, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL4_10"));
	FlexGridSizer14->Add(rgrADCAmp24Stage1BasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_11[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrQuantizerBiasUp = new wxRadioBox(this, ID_RX_CTRL5_32, _("Quantizer Bias Up, uA"), wxPoint(352,128), wxDefaultSize, 4, __wxRadioBoxChoices_11, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL5_32"));
	FlexGridSizer14->Add(rgrQuantizerBiasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_12[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp1Stage2BasUp = new wxRadioBox(this, ID_RX_CTRL5_76, _("ADC Amp1 Stage2 Bias Up, uA"), wxPoint(0,184), wxDefaultSize, 4, __wxRadioBoxChoices_12, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL5_76"));
	FlexGridSizer14->Add(rgrADCAmp1Stage2BasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_13[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrADCAmp24Stage2BasUp = new wxRadioBox(this, ID_RX_CTRL5_54, _("ADC Amp2-4 Stage2 Bias Up, uA"), wxPoint(168,184), wxDefaultSize, 4, __wxRadioBoxChoices_13, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL5_54"));
	FlexGridSizer14->Add(rgrADCAmp24Stage2BasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_14[4] =
	{
		_("20"),
		_("40"),
		_("10"),
		_("15")
	};
	rgrInputBufferBiasUp = new wxRadioBox(this, ID_RX_CTRL5_10, _("Input Buffer Bias Up, uA"), wxPoint(352,184), wxDefaultSize, 4, __wxRadioBoxChoices_14, 4, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RX_CTRL5_10"));
	FlexGridSizer14->Add(rgrInputBufferBiasUp, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3->Add(FlexGridSizer12, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(FlexGridSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(this);
	FlexGridSizer9->SetSizeHints(this);

	Connect(ID_DECODE_ADDC,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_ADC_DAC,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_ADC_REF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_ADC_I,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_DAC,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_ADC_Q,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_EN_M_REF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_FSYNC_P,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_TX_FSYNC_P,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_INTER,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_TX_INTER,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_DAC_CLK_P,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_REF_CTRL0_74,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_REF_CTRL0_30,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_REF_CTRL1_76,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_REF_CTRL1_54,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_REF_CTRL1_30,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_TX_CTRL1_64,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_TX_CTRL1_3,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_TX_CTRL1_10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL2_0,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL1_76,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL1_54,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL1_30,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL2_32,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL2_54,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL2_76,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL4_54,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL3_10,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL3_7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL4_76,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL4_32,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL4_10,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL5_32,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL5_76,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL5_54,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	Connect(ID_RX_CTRL5_10,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlADDC::ParameterChangeHandler);
	//*)

    wndId2Enum[ID_DECODE_ADDC] = DECODE_ADC_DAC;
    wndId2Enum[ID_EN_ADC_DAC] = EN_ADC_DAC;
    wndId2Enum[ID_EN_ADC_REF] = MISC_CTRL_1;
    wndId2Enum[ID_EN_ADC_I] = MISC_CTRL_3;
    wndId2Enum[ID_EN_DAC] = MISC_CTRL_4;
    wndId2Enum[ID_EN_ADC_Q] = MISC_CTRL_2;
    wndId2Enum[ID_EN_M_REF] = MISC_CTRL_0;
    wndId2Enum[ID_RX_FSYNC_P] = MISC_CTRL_9;
    wndId2Enum[ID_TX_FSYNC_P] = MISC_CTRL_6;
    wndId2Enum[ID_RX_INTER] = MISC_CTRL_8;
    wndId2Enum[ID_TX_INTER] = MISC_CTRL_5;
    wndId2Enum[ID_DAC_CLK_P] = MISC_CTRL_7;
    wndId2Enum[ID_REF_CTRL0_74] = REF_CTRL0_74;
    wndId2Enum[ID_REF_CTRL0_30] = REF_CTRL0_30;
    wndId2Enum[ID_REF_CTRL1_76] = REF_CTRL1_76;
    wndId2Enum[ID_REF_CTRL1_54] = REF_CTRL1_54;
    wndId2Enum[ID_REF_CTRL1_30] = REF_CTRL1_30;
    wndId2Enum[ID_TX_CTRL1_64] = TX_CTRL1_64;
    wndId2Enum[ID_TX_CTRL1_3] = TX_CTRL1_3;
    wndId2Enum[ID_TX_CTRL1_10] = TX_CTRL1_10;
    wndId2Enum[ID_RX_CTRL2_0] = RX_CTRL2_0;
    wndId2Enum[ID_RX_CTRL1_76] = RX_CTRL1_76;
    wndId2Enum[ID_RX_CTRL1_54] = RX_CTRL1_54;
    wndId2Enum[ID_RX_CTRL1_30] = RX_CTRL1_30;
    wndId2Enum[ID_RX_CTRL2_32] = RX_CTRL2_32;
    wndId2Enum[ID_RX_CTRL2_54] = RX_CTRL2_54;
    wndId2Enum[ID_RX_CTRL2_76] = RX_CTRL2_76;
    wndId2Enum[ID_RX_CTRL4_54] = RX_CTRL4_54;
    wndId2Enum[ID_RX_CTRL3_10] = RX_CTRL3_10;
    wndId2Enum[ID_RX_CTRL3_7] = RX_CTRL3_7;
    wndId2Enum[ID_RX_CTRL4_76] = RX_CTRL4_76;
    wndId2Enum[ID_RX_CTRL4_32] = RX_CTRL4_32;
    wndId2Enum[ID_RX_CTRL4_10] = RX_CTRL4_10;
    wndId2Enum[ID_RX_CTRL5_32] = RX_CTRL5_32;
    wndId2Enum[ID_RX_CTRL5_76] = RX_CTRL5_76;
    wndId2Enum[ID_RX_CTRL5_54] = RX_CTRL5_54;
    wndId2Enum[ID_RX_CTRL5_10] = RX_CTRL5_10;

    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    temp.push_back(_("0 (Nom)"));
    for(int i=1; i<=6; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    temp.push_back(_("7 (Max)"));
    cmbBandgapTemp->Set(temp);
    cmbBandgapGain->Set(temp);

    temp.clear();
    temp.push_back(_("20 uA"));
    temp.push_back(_("40 uA"));
    temp.push_back(_("10 uA"));
    temp.push_back(_("15 uA"));
    cmbRefAmpsBiasAdj->Set(temp);
    cmbRefResistorBiasAdj->Set(temp);

    temp.clear();
    temp.push_back(_("1.0X"));
    temp.push_back(_("1.5X"));
    temp.push_back(_("2.0X"));
    temp.push_back(_("2.5X"));
    cmbRefAmpsBiasUp->Set(temp);
    cmbRefBiasUp->Set(temp);
    cmbRefBufferBoost->Set(temp);

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbRefAmpsBiasDn->Set(temp);
    cmbRefBiasDn->Set(temp);

    temp.clear();
    temp.push_back(_("Open Circuit"));
    temp.push_back(_("100 Ohms"));
    temp.push_back(_("200 Ohms"));
    temp.push_back(_("66 Ohms"));
    temp.push_back(_("200 Ohms"));
    temp.push_back(_("66 Ohms"));
    temp.push_back(_("100 Ohms"));
    temp.push_back(_("50 Ohms"));
    cmbDACInternalOutputLoadResistor->Set(temp);

    temp.clear();
    temp.push_back(_("5 mA"));
    temp.push_back(_("10 mA"));
    temp.push_back(_("2.5 mA"));
    temp.push_back(_("5 mA"));
    cmbDACFullScaleOutputCurrent->Set(temp);

    temp.clear();
    temp.push_back(_("875 mV"));
    temp.push_back(_("960 mV"));
    temp.push_back(_("700 mV"));
    temp.push_back(_("790 mV"));
    cmbCoomonModeAdj->Set(temp);

    temp.clear();
    temp.push_back(_("1.50 V"));
    temp.push_back(_("1.75 V"));
    temp.push_back(_("1.00 V"));
    temp.push_back(_("1.25 V"));
    cmbRefGainAdj->Set(temp);

    temp.clear();
    temp.push_back(_("0 (Nom)"));
    temp.push_back(_("1"));
    temp.push_back(_("2"));
    temp.push_back(_("3 (Min)"));
    cmbMainBiasDN->Set(temp);

    temp.clear();
    temp.push_back(_("Nominal"));
    temp.push_back(_("+450ps"));
    temp.push_back(_("+150ps"));
    temp.push_back(_("+300ps"));
    cmbClockNonOverlapAdjust->Set(temp);

    temp.clear();
    temp.push_back(_("Rising Edge"));
    temp.push_back(_("Falling Edge"));
    cmbADCSamplingPhase->Set(temp);

    SetControlDisables();
}

pnlADDC::~pnlADDC()
{
	//(*Destroy(pnlADDC)
	//*)
}

void pnlADDC::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}

void pnlADDC::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
}

void pnlADDC::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbEN_ADC_DAC->Enable(!enabled);
    chkEN_ADC_I->Enable(enabled);
    chkEN_ADC_Q->Enable(enabled);
    chkEN_ADC_REF->Enable(enabled);
    chkEN_DAC->Enable(enabled);
    chkEN_M_REF->Enable(enabled);
}
