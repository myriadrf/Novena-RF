#include "pnlTxRF.h"

//(*InternalHeaders(pnlTxRF)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlTxRF)
const long pnlTxRF::ID_EN_TXRF = wxNewId();
const long pnlTxRF::ID_PD_DRVAUX = wxNewId();
const long pnlTxRF::ID_PD_PKDET = wxNewId();
const long pnlTxRF::ID_PW_VGA1_I = wxNewId();
const long pnlTxRF::ID_PW_VGA1_Q = wxNewId();
const long pnlTxRF::ID_PD_TXDRV = wxNewId();
const long pnlTxRF::ID_PD_TXLOBUF = wxNewId();
const long pnlTxRF::ID_PD_TXMIX = wxNewId();
const long pnlTxRF::ID_STATICTEXT5 = wxNewId();
const long pnlTxRF::ID_ENVD = wxNewId();
const long pnlTxRF::ID_STATICTEXT6 = wxNewId();
const long pnlTxRF::ID_ENVD2 = wxNewId();
const long pnlTxRF::ID_STATICTEXT7 = wxNewId();
const long pnlTxRF::ID_PKDBW = wxNewId();
const long pnlTxRF::ID_FST_PKDET = wxNewId();
const long pnlTxRF::ID_FST_TXHFBIAS = wxNewId();
const long pnlTxRF::ID_STATICTEXT1 = wxNewId();
const long pnlTxRF::ID_ICT_TXLOBUF = wxNewId();
const long pnlTxRF::ID_STATICTEXT2 = wxNewId();
const long pnlTxRF::ID_VBCAS_TXDRV = wxNewId();
const long pnlTxRF::ID_STATICTEXT3 = wxNewId();
const long pnlTxRF::ID_ICT_TXMIX = wxNewId();
const long pnlTxRF::ID_STATICTEXT4 = wxNewId();
const long pnlTxRF::ID_ICT_TXDRV = wxNewId();
const long pnlTxRF::ID_LOOPBBEN = wxNewId();
const long pnlTxRF::ID_PA = wxNewId();
const long pnlTxRF::ID_DECODE_TXRF = wxNewId();
const long pnlTxRF::ID_STATICTEXT8 = wxNewId();
const long pnlTxRF::ID_STATICTEXT9 = wxNewId();
const long pnlTxRF::ID_VGA1G_U = wxNewId();
const long pnlTxRF::ID_VGA1_DC_I = wxNewId();
const long pnlTxRF::ID_STATICTEXT10 = wxNewId();
const long pnlTxRF::ID_STATICTEXT11 = wxNewId();
const long pnlTxRF::ID_VGA1G_T = wxNewId();
const long pnlTxRF::ID_VGA1_DC_Q = wxNewId();
const long pnlTxRF::ID_STATICTEXT12 = wxNewId();
const long pnlTxRF::ID_STATICTEXT13 = wxNewId();
const long pnlTxRF::ID_VGA2G_U = wxNewId();
const long pnlTxRF::ID_VGA2G_T = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTxRF,wxPanel)
	//(*EventTable(pnlTxRF)
	//*)
END_EVENT_TABLE()

pnlTxRF::pnlTxRF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlTxRF::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTxRF)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrTxRfMods = new wxCheckBox(this, ID_EN_TXRF, _("TxRF Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_TXRF"));
	chbPwrTxRfMods->SetValue(false);
	StaticBoxSizer1->Add(chbPwrTxRfMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_DRVAUX = new wxCheckBox(this, ID_PD_DRVAUX, _("Auxiliary PA Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_DRVAUX"));
	chbPD_DRVAUX->SetValue(false);
	StaticBoxSizer1->Add(chbPD_DRVAUX, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_PKDET = new wxCheckBox(this, ID_PD_PKDET, _("PDED Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_PKDET"));
	chbPD_PKDET->SetValue(false);
	StaticBoxSizer1->Add(chbPD_PKDET, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga1_I = new wxCheckBox(this, ID_PW_VGA1_I, _("VGA1 I Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PW_VGA1_I"));
	chbPwrVga1_I->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga1_I, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga1_Q = new wxCheckBox(this, ID_PW_VGA1_Q, _("VGA1 Q Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PW_VGA1_Q"));
	chbPwrVga1_Q->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga1_Q, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_TXDRV = new wxCheckBox(this, ID_PD_TXDRV, _("PA1, PA2, AUXPA Disabled"), wxDefaultPosition, wxSize(167,13), 0, wxDefaultValidator, _T("ID_PD_TXDRV"));
	chbPD_TXDRV->SetValue(false);
	StaticBoxSizer1->Add(chbPD_TXDRV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPD_TXLOBUF = new wxCheckBox(this, ID_PD_TXLOBUF, _("TxLOBUF Disabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TXLOBUF"));
	chbPD_TXLOBUF->SetValue(false);
	StaticBoxSizer1->Add(chbPD_TXLOBUF, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrVga2 = new wxCheckBox(this, ID_PD_TXMIX, _("MIX and VGA2 Disabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TXMIX"));
	chbPwrVga2->SetValue(false);
	StaticBoxSizer1->Add(chbPwrVga2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("EDPD Control"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Detector Select:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer8->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbENVD = new ComboBoxMap(this, ID_ENVD, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ENVD"));
	FlexGridSizer8->Add(cmbENVD, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Signal for AC Coupling:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer8->Add(StaticText6, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbENVD2 = new ComboBoxMap(this, ID_ENVD2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ENVD2"));
	FlexGridSizer8->Add(cmbENVD2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("PDED Bandwidth:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer8->Add(StaticText7, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbPKDBW = new ComboBoxMap(this, ID_PKDBW, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_PKDBW"));
	FlexGridSizer8->Add(cmbPKDBW, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbFST_PKDET = new wxCheckBox(this, ID_FST_PKDET, _("Short the Resistors in PDED"), wxDefaultPosition, wxSize(158,13), 0, wxDefaultValidator, _T("ID_FST_PKDET"));
	chbFST_PKDET->SetValue(false);
	FlexGridSizer8->Add(chbFST_PKDET, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer4->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Bias Control"));
	chbFST_TXHFBIAS = new wxCheckBox(this, ID_FST_TXHFBIAS, _("Tx HF Bias Resistors Shorted"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FST_TXHFBIAS"));
	chbFST_TXHFBIAS->SetValue(false);
	StaticBoxSizer2->Add(chbFST_TXHFBIAS, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("LO Buffer Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer2->Add(StaticText1, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXLOBUF = new ComboBoxMap(this, ID_ICT_TXLOBUF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TXLOBUF"));
	StaticBoxSizer2->Add(cmbICT_TXLOBUF, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("PA Cascode NPNs Bias:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticBoxSizer2->Add(StaticText2, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVBCAS_TXDRV = new ComboBoxMap(this, ID_VBCAS_TXDRV, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VBCAS_TXDRV"));
	StaticBoxSizer2->Add(cmbVBCAS_TXDRV, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("MIX Bias Current, mA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticBoxSizer2->Add(StaticText3, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXMIX = new ComboBoxMap(this, ID_ICT_TXMIX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TXMIX"));
	StaticBoxSizer2->Add(cmbICT_TXMIX, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("PAs Bias Current, mA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticBoxSizer2->Add(StaticText4, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TXDRV = new ComboBoxMap(this, ID_ICT_TXDRV, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TXDRV"));
	StaticBoxSizer2->Add(cmbICT_TXDRV, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_1[4] =
	{
		_("Switches Open"),
		_("TxLPF Output to BBLB"),
		_("TxVGA1 Output to BBLB"),
		_("PDED Output to BBLB")
	};
	rgrLOOPBBEN = new wxRadioBox(this, ID_LOOPBBEN, _("BB Loop Back Control"), wxPoint(192,224), wxDefaultSize, 4, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LOOPBBEN"));
	FlexGridSizer5->Add(rgrLOOPBBEN, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(3, 1, 5, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 5);
	wxString __wxRadioBoxChoices_2[3] =
	{
		_("PA1 and PA2 Off"),
		_("PA1 Selected"),
		_("PA2 Selected")
	};
	rgrPA = new wxRadioBox(this, ID_PA, _("PA Selection"), wxPoint(368,8), wxDefaultSize, 3, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_PA"));
	rgrPA->SetSelection(0);
	FlexGridSizer7->Add(rgrPA, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_TXRF, _("Decoding"), wxPoint(520,8), wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_TXRF"));
	rgrDecode->SetSelection(0);
	FlexGridSizer7->Add(rgrDecode, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA1 Control"));
	FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("VGA1 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer1->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("LO Leakage I DAC Out, mV:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer1->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	cmbVga1G_u = new ComboBoxMap(this, ID_VGA1G_U, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA1G_U"));
	FlexGridSizer1->Add(cmbVga1G_u, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1DcI = new ComboBoxMap(this, ID_VGA1_DC_I, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA1_DC_I"));
	FlexGridSizer1->Add(cmbVga1DcI, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("VGA1 Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer1->Add(StaticText10, 1, wxTOP|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("LO Leakage Q DAC Out, mV:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer1->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	cmbVga1G_t = new ComboBoxMap(this, ID_VGA1G_T, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA1G_T"));
	FlexGridSizer1->Add(cmbVga1G_t, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga1DcQ = new ComboBoxMap(this, ID_VGA1_DC_Q, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA1_DC_Q"));
	FlexGridSizer1->Add(cmbVga1DcQ, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA2 Control"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("VGA2 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer2->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("VGA2 Gain (Test):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	cmbVga2G_u = new ComboBoxMap(this, ID_VGA2G_U, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2G_U"));
	FlexGridSizer2->Add(cmbVga2G_u, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2G_t = new ComboBoxMap(this, ID_VGA2G_T, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2G_T"));
	FlexGridSizer2->Add(cmbVga2G_t, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(this);
	FlexGridSizer3->SetSizeHints(this);

	Connect(ID_EN_TXRF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PD_DRVAUX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PD_PKDET,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PW_VGA1_I,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PW_VGA1_Q,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PD_TXDRV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PD_TXLOBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PD_TXMIX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_ENVD,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_ENVD2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PKDBW,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_FST_PKDET,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_FST_TXHFBIAS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_ICT_TXLOBUF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VBCAS_TXDRV,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_ICT_TXMIX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_ICT_TXDRV,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_LOOPBBEN,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_PA,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_DECODE_TXRF,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA1G_U,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA1_DC_I,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA1G_T,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA1_DC_Q,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA2G_U,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	Connect(ID_VGA2G_T,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxRF::ParameterChangeHandler);
	//*)

	wndId2Enum[ID_EN_TXRF] = EN_TXRF;
    wndId2Enum[ID_PD_DRVAUX] = PD_DRVAUX;
    wndId2Enum[ID_PD_PKDET] = PD_PKDET;
    wndId2Enum[ID_PW_VGA1_I] = PW_VGA1_I;
    wndId2Enum[ID_PW_VGA1_Q] = PW_VGA1_Q;
    wndId2Enum[ID_PD_TXDRV] = PD_TXDRV;
    wndId2Enum[ID_PD_TXLOBUF] = PD_TXLOBUF;
    wndId2Enum[ID_PD_TXMIX] = PD_TXMIX;
    wndId2Enum[ID_ENVD] = ENVD_10;
    wndId2Enum[ID_ENVD2] = ENVD_2;
    wndId2Enum[ID_PKDBW] = PKDBW;
    wndId2Enum[ID_FST_TXHFBIAS] = FST_TXHFBIAS;
    wndId2Enum[ID_ICT_TXLOBUF] = ICT_TXLOBUF;
    wndId2Enum[ID_VBCAS_TXDRV] = VBCAS_TXDRV;
    wndId2Enum[ID_ICT_TXMIX] = ICT_TXMIX;
    wndId2Enum[ID_ICT_TXDRV] = ICT_TXDRV;
    wndId2Enum[ID_LOOPBBEN] = LOOPBBEN;
    wndId2Enum[ID_PA] = PA_EN;
    wndId2Enum[ID_DECODE_TXRF] = DECODE_TXRF;
    wndId2Enum[ID_VGA1G_U] = VGA1GAIN;
    wndId2Enum[ID_VGA1_DC_I] = VGA1DC_I;
    wndId2Enum[ID_VGA1G_T] = VGA1GAINT;
    wndId2Enum[ID_VGA1_DC_Q] = VGA1DC_Q;
    wndId2Enum[ID_VGA2G_U] = VGA2GAIN_TXVGA2;
    wndId2Enum[ID_VGA2G_T] = G_TXVGA2;
    wndId2Enum[ID_FST_PKDET] = FST_PKDET;

    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbICT_TXLOBUF->Set(temp);
    cmbVBCAS_TXDRV->Set(temp);
    cmbPKDBW->Set(temp);

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbICT_TXMIX->Set(temp);
    cmbICT_TXDRV->Set(temp);

    temp.clear();
    for(int i=-35; i<=-4; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVga1G_u->Set(temp);
    vector< cmbKeyValuePair > keymap;
    keymap.push_back( cmbKeyValuePair(0x06, _("-35")));
    keymap.push_back( cmbKeyValuePair(0x07, _("-34")));
    keymap.push_back( cmbKeyValuePair(0x08, _("-33")));
    keymap.push_back( cmbKeyValuePair(0x09, _("-32")));
    keymap.push_back( cmbKeyValuePair(0x0A, _("-31")));
    keymap.push_back( cmbKeyValuePair(0x0B, _("-30")));
    keymap.push_back( cmbKeyValuePair(0x0D, _("-29")));
    keymap.push_back( cmbKeyValuePair(0x0F, _("-28")));
    keymap.push_back( cmbKeyValuePair(0x11, _("-27")));
    keymap.push_back( cmbKeyValuePair(0x13, _("-26")));
    keymap.push_back( cmbKeyValuePair(0x15, _("-25")));
    keymap.push_back( cmbKeyValuePair(0x18, _("-24")));
    keymap.push_back( cmbKeyValuePair(0x1B, _("-23")));
    keymap.push_back( cmbKeyValuePair(0x1F, _("-22")));
    keymap.push_back( cmbKeyValuePair(0x23, _("-21")));
    keymap.push_back( cmbKeyValuePair(0x27, _("-20")));
    keymap.push_back( cmbKeyValuePair(0x2C, _("-19")));
    keymap.push_back( cmbKeyValuePair(0x32, _("-18")));
    keymap.push_back( cmbKeyValuePair(0x38, _("-17")));
    keymap.push_back( cmbKeyValuePair(0x3F, _("-16")));
    keymap.push_back( cmbKeyValuePair(0x47, _("-15")));
    keymap.push_back( cmbKeyValuePair(0x50, _("-14")));
    keymap.push_back( cmbKeyValuePair(0x5A, _("-13")));
    keymap.push_back( cmbKeyValuePair(0x65, _("-12")));
    keymap.push_back( cmbKeyValuePair(0x71, _("-11")));
    keymap.push_back( cmbKeyValuePair(0x7F, _("-10")));
    keymap.push_back( cmbKeyValuePair(0x8F, _("-9")));
    keymap.push_back( cmbKeyValuePair(0xA0, _("-8")));
    keymap.push_back( cmbKeyValuePair(0xB4, _("-7")));
    keymap.push_back( cmbKeyValuePair(0xCA, _("-6")));
    keymap.push_back( cmbKeyValuePair(0xE3, _("-5")));
    keymap.push_back( cmbKeyValuePair(0xFF, _("-4")));
    cmbVga1G_t->Set(keymap);

    temp.clear();
    for(int i=-16000; i<16000; i+=125)
        {sprintf(ctemp, "%.3f", i/1000.0); temp.push_back( ctemp );}
    cmbVga1DcI->Set(temp);
    cmbVga1DcQ->Set(temp);

    temp.clear();
    for(int i=0; i<=25; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVga2G_u->Set(temp);

    temp.clear();
    for(int i=0; i<512; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVga2G_t->Set(temp);

    temp.clear();
    temp.push_back(_("AUXPA ED output"));
    temp.push_back(_("AUXPA PD output"));
    temp.push_back(_("PA1 ED output"));
    temp.push_back(_("PA2 ED output"));
    cmbENVD->Set(temp);

    temp.clear();
    temp.push_back(_("Reference DC"));
    temp.push_back(_("Detector Average"));
    cmbENVD2->Set(temp);

    SetControlDisables();
}

pnlTxRF::~pnlTxRF()
{
	//(*Destroy(pnlTxRF)
	//*)
}

void pnlTxRF::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
}

void pnlTxRF::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrTxRfMods->Enable(!enabled);
    chbPD_DRVAUX->Enable(enabled);
    //chbPD_PKDET->Enable(enabled);
    chbPwrVga1_I->Enable(enabled);
    chbPwrVga1_Q->Enable(enabled);
    chbPD_TXDRV->Enable(enabled);
    chbPD_TXLOBUF->Enable(enabled);
    chbPwrVga2->Enable(enabled);
    cmbVga1G_t->Enable(enabled);
    cmbVga2G_t->Enable(enabled);
}

void pnlTxRF::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}
