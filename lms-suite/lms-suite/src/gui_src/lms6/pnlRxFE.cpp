#include "pnlRxFE.h"
#include <vector>
//(*InternalHeaders(pnlRxFE)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace std;
using namespace lms6;

//(*IdInit(pnlRxFE)
const long pnlRxFE::ID_DECODE_RXFE = wxNewId();
const long pnlRxFE::ID_EN_RXFE = wxNewId();
const long pnlRxFE::ID_PD_TIA_RXFE = wxNewId();
const long pnlRxFE::ID_PD_MXLOB_RXFE = wxNewId();
const long pnlRxFE::ID_PD_MIX_RXFE = wxNewId();
const long pnlRxFE::ID_PD_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_RINEN_MIX_RXFE = wxNewId();
const long pnlRxFE::ID_INLOAD_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT1 = wxNewId();
const long pnlRxFE::ID_XLOAD_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_CBE_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT2 = wxNewId();
const long pnlRxFE::ID_STATICTEXT3 = wxNewId();
const long pnlRxFE::ID_G_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_G_FINE_LNA3_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT4 = wxNewId();
const long pnlRxFE::ID_STATICTEXT5 = wxNewId();
const long pnlRxFE::ID_LNASEL_RXFE = wxNewId();
const long pnlRxFE::ID_ICT_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT6 = wxNewId();
const long pnlRxFE::ID_STATICTEXT7 = wxNewId();
const long pnlRxFE::ID_RDLEXT_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_RDLINT_LNA_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT8 = wxNewId();
const long pnlRxFE::ID_ICT_MIX_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT9 = wxNewId();
const long pnlRxFE::ID_IN1SEL_MIX_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT10 = wxNewId();
const long pnlRxFE::ID_ICT_MXLOB_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT11 = wxNewId();
const long pnlRxFE::ID_LOBN_MIX_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT12 = wxNewId();
const long pnlRxFE::ID_STATICTEXT13 = wxNewId();
const long pnlRxFE::ID_IP2TRIM_I_RXFE = wxNewId();
const long pnlRxFE::ID_IP2TRIM_Q_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT14 = wxNewId();
const long pnlRxFE::ID_STATICTEXT15 = wxNewId();
const long pnlRxFE::ID_DCOFF_I_RXFE = wxNewId();
const long pnlRxFE::ID_DCOFF_Q_RXFE = wxNewId();
const long pnlRxFE::ID_STATICTEXT16 = wxNewId();
const long pnlRxFE::ID_STATICTEXT17 = wxNewId();
const long pnlRxFE::ID_STATICTEXT18 = wxNewId();
const long pnlRxFE::ID_RFB_TIA_RXFE = wxNewId();
const long pnlRxFE::ID_CFB_TIA_RXFE = wxNewId();
const long pnlRxFE::ID_ICT_TIA_RXFE = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRxFE,wxPanel)
	//(*EventTable(pnlRxFE)
	//*)
END_EVENT_TABLE()

pnlRxFE::pnlRxFE(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlRxFE::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRxFE)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer6 = new wxFlexGridSizer(0, 4, 5, 5);
	FlexGridSizer7 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer7->AddGrowableRow(1);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_RXFE, _("Decoding"), wxPoint(16,8), wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_RXFE"));
	rgrDecode->SetSelection(0);
	FlexGridSizer7->Add(rgrDecode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrRxFeMods = new wxCheckBox(this, ID_EN_RXFE, _("RxFE Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_RXFE"));
	chbPwrRxFeMods->SetValue(false);
	StaticBoxSizer1->Add(chbPwrRxFeMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_TIA_RXFE = new wxCheckBox(this, ID_PD_TIA_RXFE, _("TIA Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TIA_RXFE"));
	chkPD_TIA_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_TIA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_MXLOB_RXFE = new wxCheckBox(this, ID_PD_MXLOB_RXFE, _("MXLOB Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_MXLOB_RXFE"));
	chkPD_MXLOB_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_MXLOB_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_MIX_RXFE = new wxCheckBox(this, ID_PD_MIX_RXFE, _("MIX Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_MIX_RXFE"));
	chkPD_MIX_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_MIX_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkPD_LNA_RXFE = new wxCheckBox(this, ID_PD_LNA_RXFE, _("LNA Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LNA_RXFE"));
	chkPD_LNA_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkPD_LNA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkRINEN_MIX_RXFE = new wxCheckBox(this, ID_RINEN_MIX_RXFE, _("MIX Term Resistor Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RINEN_MIX_RXFE"));
	chkRINEN_MIX_RXFE->SetValue(false);
	StaticBoxSizer1->Add(chkRINEN_MIX_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LNA Control"));
	FlexGridSizer1 = new wxFlexGridSizer(8, 2, 0, 5);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer1->AddGrowableRow(2);
	FlexGridSizer1->AddGrowableRow(3);
	FlexGridSizer1->AddGrowableRow(4);
	FlexGridSizer1->AddGrowableRow(5);
	FlexGridSizer1->AddGrowableRow(6);
	FlexGridSizer1->AddGrowableRow(7);
	chkINLOAD_LNA_RXFE = new wxCheckBox(this, ID_INLOAD_LNA_RXFE, _("Internal LNA Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_INLOAD_LNA_RXFE"));
	chkINLOAD_LNA_RXFE->SetValue(false);
	FlexGridSizer1->Add(chkINLOAD_LNA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Capacitance to BE:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkXLOAD_LNA_RXFE = new wxCheckBox(this, ID_XLOAD_LNA_RXFE, _("External LNA Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_XLOAD_LNA_RXFE"));
	chkXLOAD_LNA_RXFE->SetValue(false);
	FlexGridSizer1->Add(chkXLOAD_LNA_RXFE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCBE_LNA_RXFE = new ComboBoxMap(this, ID_CBE_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CBE_LNA_RXFE"));
	FlexGridSizer1->Add(cmbCBE_LNA_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("LNA Gain Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("LNA3 Fine Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbG_LNA_RXFE = new ComboBoxMap(this, ID_G_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_LNA_RXFE"));
	FlexGridSizer1->Add(cmbG_LNA_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbG_FINE_LNA3_RXFE = new ComboBoxMap(this, ID_G_FINE_LNA3_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_FINE_LNA3_RXFE"));
	FlexGridSizer1->Add(cmbG_FINE_LNA3_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Active LNA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("LNA Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNASEL_RXFE = new ComboBoxMap(this, ID_LNASEL_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LNASEL_RXFE"));
	FlexGridSizer1->Add(cmbLNASEL_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_LNA_RXFE = new ComboBoxMap(this, ID_ICT_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LNA_RXFE"));
	FlexGridSizer1->Add(cmbICT_LNA_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("LNA Load Resistor,\n External Load (Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("LNA Load Resistor,\n Internal Load(Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer1->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRDLEXT_LNA_RXFE = new ComboBoxMap(this, ID_RDLEXT_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDLEXT_LNA_RXFE"));
	FlexGridSizer1->Add(cmbRDLEXT_LNA_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbRDLINT_LNA_RXFE = new ComboBoxMap(this, ID_RDLINT_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDLINT_LNA_RXFE"));
	FlexGridSizer1->Add(cmbRDLINT_LNA_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("MIX Control"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("MIX Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer9->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_MIX_RXFE = new ComboBoxMap(this, ID_ICT_MIX_RXFE, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_ICT_MIX_RXFE"));
	FlexGridSizer9->Add(cmbICT_MIX_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("MIX Input:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer9->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbIN1SEL_MIX_RXFE = new ComboBoxMap(this, ID_IN1SEL_MIX_RXFE, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_IN1SEL_MIX_RXFE"));
	FlexGridSizer9->Add(cmbIN1SEL_MIX_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("MXLOB Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer9->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_MXLOB_RXFE = new ComboBoxMap(this, ID_ICT_MXLOB_RXFE, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_ICT_MXLOB_RXFE"));
	FlexGridSizer9->Add(cmbICT_MXLOB_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("LO Bias Of The Mix:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer9->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	cmbLOBN_MIX_RXFE = new ComboBoxMap(this, ID_LOBN_MIX_RXFE, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LOBN_MIX_RXFE"));
	FlexGridSizer9->Add(cmbLOBN_MIX_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 5, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("IP2 Cancellation"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Channel I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer2->Add(StaticText12, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Channel Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbIP2TRIM_I_RXFE = new ComboBoxMap(this, ID_IP2TRIM_I_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IP2TRIM_I_RXFE"));
	FlexGridSizer2->Add(cmbIP2TRIM_I_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbIP2TRIM_Q_RXFE = new ComboBoxMap(this, ID_IP2TRIM_Q_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IP2TRIM_Q_RXFE"));
	FlexGridSizer2->Add(cmbIP2TRIM_Q_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("DC Offset Cancellation"));
	FlexGridSizer3 = new wxFlexGridSizer(2, 2, 0, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _("Channel I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer3->Add(StaticText14, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Channel Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer3->Add(StaticText15, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOFF_I_RXFE = new ComboBoxMap(this, ID_DCOFF_I_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFF_I_RXFE"));
	FlexGridSizer3->Add(cmbDCOFF_I_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOFF_Q_RXFE = new ComboBoxMap(this, ID_DCOFF_Q_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFF_Q_RXFE"));
	FlexGridSizer3->Add(cmbDCOFF_Q_RXFE, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VGA1 Control"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 3, 0, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _("Feedback Resistor (Gain):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer4->Add(StaticText16, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Feedback Capacitor (BW):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer4->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _("Bias Current:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer4->Add(StaticText18, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbRFB_TIA_RXFE = new ComboBoxMap(this, ID_RFB_TIA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RFB_TIA_RXFE"));
	FlexGridSizer4->Add(cmbRFB_TIA_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCFB_TIA_RXFE = new ComboBoxMap(this, ID_CFB_TIA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CFB_TIA_RXFE"));
	FlexGridSizer4->Add(cmbCFB_TIA_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbICT_TIA_RXFE = new ComboBoxMap(this, ID_ICT_TIA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TIA_RXFE"));
	FlexGridSizer4->Add(cmbICT_TIA_RXFE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer4, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(StaticBoxSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer5);
	FlexGridSizer5->Fit(this);
	FlexGridSizer5->SetSizeHints(this);

	Connect(ID_DECODE_RXFE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_EN_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_PD_TIA_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_PD_MXLOB_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_PD_MIX_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_PD_LNA_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_RINEN_MIX_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_INLOAD_LNA_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_XLOAD_LNA_RXFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_CBE_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_G_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_G_FINE_LNA3_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_LNASEL_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_ICT_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_RDLEXT_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_RDLINT_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_ICT_MIX_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_IN1SEL_MIX_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_ICT_MXLOB_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_LOBN_MIX_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_IP2TRIM_I_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_IP2TRIM_Q_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_DCOFF_I_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_DCOFF_Q_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_RFB_TIA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_CFB_TIA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	Connect(ID_ICT_TIA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxFE::ParameterChangeHandler);
	//*)

	wndId2Enum[ID_DECODE_RXFE] = DECODE_RXFE;
    wndId2Enum[ID_EN_RXFE] = EN_RXFE;
    wndId2Enum[ID_PD_TIA_RXFE] = PD_TIA_RXFE;
    wndId2Enum[ID_PD_MXLOB_RXFE] = PD_MXLOB_RXFE;
    wndId2Enum[ID_PD_MIX_RXFE] = PD_MIX_RXFE;
    wndId2Enum[ID_PD_LNA_RXFE] = PD_LNA_RXFE;
    wndId2Enum[ID_RINEN_MIX_RXFE] = RINEN_MIX_RXFE;
    wndId2Enum[ID_INLOAD_LNA_RXFE] = INLOAD_LNA_RXFE;
    wndId2Enum[ID_XLOAD_LNA_RXFE] = XLOAD_LNA_RXFE;
    wndId2Enum[ID_CBE_LNA_RXFE] = CBE_LNA_RXFE;
    wndId2Enum[ID_G_LNA_RXFE] = G_LNA_RXFE;
    wndId2Enum[ID_G_FINE_LNA3_RXFE] = G_FINE_LNA3_RXFE;
    wndId2Enum[ID_LNASEL_RXFE] = LNASEL_RXFE;
    wndId2Enum[ID_ICT_LNA_RXFE] = ICT_LNA_RXFE;
    wndId2Enum[ID_RDLEXT_LNA_RXFE] = RDLEXT_LNA_RXFE;
    wndId2Enum[ID_RDLINT_LNA_RXFE] = RDLINT_LNA_RXFE;
    wndId2Enum[ID_ICT_MIX_RXFE] = ICT_MIX_RXFE;
    wndId2Enum[ID_IN1SEL_MIX_RXFE] = IN1SEL_MIX_RXFE;
    wndId2Enum[ID_ICT_MXLOB_RXFE] = ICT_MXLOB_RXFE;
    wndId2Enum[ID_LOBN_MIX_RXFE] = LOBN_MIX_RXFE;
    wndId2Enum[ID_IP2TRIM_I_RXFE] = IP2TRIM_I_RXFE;
    wndId2Enum[ID_IP2TRIM_Q_RXFE] = IP2TRIM_Q_RXFE;
    wndId2Enum[ID_DCOFF_I_RXFE] = DCOFF_I_RXFE;
    wndId2Enum[ID_DCOFF_Q_RXFE] = DCOFF_Q_RXFE;
    wndId2Enum[ID_RFB_TIA_RXFE] = RFB_TIA_RXFE;
    wndId2Enum[ID_CFB_TIA_RXFE] = CFB_TIA_RXFE;
    wndId2Enum[ID_ICT_TIA_RXFE] = ICT_TIA_RXFE;

    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbCBE_LNA_RXFE->Set(temp);
    cmbICT_MIX_RXFE->Set(temp);
    cmbICT_MXLOB_RXFE->Set(temp);
    cmbLOBN_MIX_RXFE->Set(temp);
    cmbICT_TIA_RXFE->Set(temp);
    cmbICT_LNA_RXFE->Set(temp);

    vector<cmbKeyValuePair> signMag;
    for(int i=63; i>0; --i)
        signMag.push_back(cmbKeyValuePair(0x40 | i, wxString::Format("-%i", i)));
    for(int i=0; i<64; ++i)
        signMag.push_back(cmbKeyValuePair(i, wxString::Format("%i", i)));
    cmbIP2TRIM_I_RXFE->Set(signMag);
    cmbIP2TRIM_Q_RXFE->Set(signMag);
    cmbDCOFF_I_RXFE->Set(signMag);
    cmbDCOFF_Q_RXFE->Set(signMag);

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbRDLEXT_LNA_RXFE->Set(temp);
    cmbRDLINT_LNA_RXFE->Set(temp);

    temp.clear();
    for(int i=0; i<128; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbRFB_TIA_RXFE->Set(temp);
    cmbCFB_TIA_RXFE->Set(temp);

    vector<cmbKeyValuePair> keyVals;
    keyVals.push_back(cmbKeyValuePair(1, wxString(_("Bypass"))));
    keyVals.push_back(cmbKeyValuePair(2, wxString(_("Mid gain"))));
    keyVals.push_back(cmbKeyValuePair(3, wxString(_("Max gain"))));
    cmbG_LNA_RXFE->Set(keyVals);

    temp.clear();
    temp.push_back(_("Disabled"));
    temp.push_back(_("LNA 1"));
    temp.push_back(_("LNA 2"));
    temp.push_back(_("LNA 3"));
    cmbLNASEL_RXFE->Set(temp);

    temp.clear();
    temp.push_back(_("To Pads"));
    temp.push_back(_("To LNA Out"));
    cmbIN1SEL_MIX_RXFE->Set(temp);

    temp.clear();
    temp.push_back(_("+0 dB"));
    temp.push_back(_("+1 dB"));
    temp.push_back(_("+2 dB"));
    temp.push_back(_("+3 dB"));
    cmbG_FINE_LNA3_RXFE->Set(temp);

    m_checkboxIDToInvert.insert(ID_PD_TIA_RXFE);
    m_checkboxIDToInvert.insert(ID_PD_MXLOB_RXFE);
    m_checkboxIDToInvert.insert(ID_PD_MIX_RXFE);
    m_checkboxIDToInvert.insert(ID_PD_LNA_RXFE);

    SetControlDisables();
}

pnlRxFE::~pnlRxFE()
{
	//(*Destroy(pnlRxFE)
	//*)
}

void pnlRxFE::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}

void pnlRxFE::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
}

void pnlRxFE::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrRxFeMods->Enable(!enabled);
    chkPD_TIA_RXFE->Enable(enabled);
    chkPD_MXLOB_RXFE->Enable(enabled);
    chkPD_MIX_RXFE->Enable(enabled);
    chkPD_LNA_RXFE->Enable(enabled);
}
