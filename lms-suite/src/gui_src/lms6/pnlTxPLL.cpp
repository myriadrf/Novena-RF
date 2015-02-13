#include "pnlTxPLL.h"
#include "dlgFreqVsCap.h"
//(*InternalHeaders(pnlTxPLL)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlTxPLL)
const long pnlTxPLL::ID_DECODE_PLL = wxNewId();
const long pnlTxPLL::ID_OEN_TSTD_SX = wxNewId();
const long pnlTxPLL::ID_PASSEN_TSTOD_SD = wxNewId();
const long pnlTxPLL::ID_BUTTON3 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT3 = wxNewId();
const long pnlTxPLL::ID_VCOCAP = wxNewId();
const long pnlTxPLL::ID_BUTTON2 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT4 = wxNewId();
const long pnlTxPLL::ID_VOVCOREG = wxNewId();
const long pnlTxPLL::ID_BYPVCOREG = wxNewId();
const long pnlTxPLL::ID_PDVCOREG = wxNewId();
const long pnlTxPLL::ID_FSTVCOBG = wxNewId();
const long pnlTxPLL::ID_STATICTEXT5 = wxNewId();
const long pnlTxPLL::ID_VTUNE_H = wxNewId();
const long pnlTxPLL::ID_STATICTEXT7 = wxNewId();
const long pnlTxPLL::ID_VTUNE_L = wxNewId();
const long pnlTxPLL::ID_BUTTON4 = wxNewId();
const long pnlTxPLL::ID_EN = wxNewId();
const long pnlTxPLL::ID_PFDPD = wxNewId();
const long pnlTxPLL::ID_ENLOBUF = wxNewId();
const long pnlTxPLL::ID_PD_VCOCOMP_SX = wxNewId();
const long pnlTxPLL::ID_ENLAMP = wxNewId();
const long pnlTxPLL::ID_AUTOBYP = wxNewId();
const long pnlTxPLL::ID_ENFEEDDIV = wxNewId();
const long pnlTxPLL::ID_EN_PFD_UP = wxNewId();
const long pnlTxPLL::ID_PFDCLKP = wxNewId();
const long pnlTxPLL::ID_TRI = wxNewId();
const long pnlTxPLL::ID_POL = wxNewId();
const long pnlTxPLL::ID_STATICTEXT33 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT35 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT34 = wxNewId();
const long pnlTxPLL::ID_ICHP = wxNewId();
const long pnlTxPLL::ID_OFFUP = wxNewId();
const long pnlTxPLL::ID_OFFDOWN = wxNewId();
const long pnlTxPLL::ID_SELOUT = wxNewId();
const long pnlTxPLL::ID_DITHEN = wxNewId();
const long pnlTxPLL::ID_STATICTEXT36 = wxNewId();
const long pnlTxPLL::ID_DITHN = wxNewId();
const long pnlTxPLL::ID_MODE = wxNewId();
const long pnlTxPLL::ID_TEXTCTRL1 = wxNewId();
const long pnlTxPLL::ID_SPINBUTTON1 = wxNewId();
const long pnlTxPLL::ID_BUTTON5 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT11 = wxNewId();
const long pnlTxPLL::ID_NINT = wxNewId();
const long pnlTxPLL::ID_STATICTEXT13 = wxNewId();
const long pnlTxPLL::ID_NFRAC = wxNewId();
const long pnlTxPLL::ID_STATICTEXT15 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT16 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT17 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT19 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT18 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT20 = wxNewId();
const long pnlTxPLL::ID_SELVCO = wxNewId();
const long pnlTxPLL::ID_STATICTEXT9 = wxNewId();
const long pnlTxPLL::ID_ACODE = wxNewId();
const long pnlTxPLL::ID_STATICTEXT10 = wxNewId();
const long pnlTxPLL::ID_BCODE = wxNewId();
const long pnlTxPLL::ID_STATICTEXT21 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT22 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT23 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT24 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT25 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT26 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT27 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT28 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT29 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT30 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT31 = wxNewId();
const long pnlTxPLL::ID_STATICTEXT32 = wxNewId();
const long pnlTxPLL::ID_FRANGE = wxNewId();
const long pnlTxPLL::ID_PANEL4 = wxNewId();
const long pnlTxPLL::ID_BSTATE = wxNewId();
const long pnlTxPLL::ID_BUTTON6 = wxNewId();
const long pnlTxPLL::ID_BSIG = wxNewId();
const long pnlTxPLL::ID_BUTTON7 = wxNewId();
const long pnlTxPLL::ID_BCLKSEL = wxNewId();
const long pnlTxPLL::ID_BINSEL = wxNewId();
const long pnlTxPLL::ID_BUTTON8 = wxNewId();
const long pnlTxPLL::ID_PANEL7 = wxNewId();
const long pnlTxPLL::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTxPLL,wxPanel)
	//(*EventTable(pnlTxPLL)
	//*)
END_EVENT_TABLE()

pnlTxPLL::pnlTxPLL(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    m_Rx = false;
	BuildContent(parent,id,pos,size);
}

void pnlTxPLL::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTxPLL)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxFlexGridSizer* FlexGridSizer19;
	wxStaticBoxSizer* StaticBoxSizer12;
	wxStaticBoxSizer* StaticBoxSizer15;
	wxStaticBoxSizer* StaticBoxSizer14;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer9;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer13;
	wxStaticBoxSizer* StaticBoxSizer10;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer18;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer21;
	wxFlexGridSizer* FlexGridSizer14;
	wxStaticBoxSizer* StaticBoxSizer11;
	wxFlexGridSizer* FlexGridSizer20;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxFlexGridSizer* FlexGridSizer17;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("id"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 5, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 6, 0, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_PLL, _("Decoding"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_PLL"));
	FlexGridSizer1->Add(rgrDecode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Test Signals"));
	chkOEN_TSTD_SX = new wxCheckBox(this, ID_OEN_TSTD_SX, _("Buffer Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_OEN_TSTD_SX"));
	chkOEN_TSTD_SX->SetValue(false);
	StaticBoxSizer1->Add(chkOEN_TSTD_SX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkPASSEN_TSTOD_SD = new wxCheckBox(this, ID_PASSEN_TSTOD_SD, _("Pass Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PASSEN_TSTOD_SD"));
	chkPASSEN_TSTOD_SD->SetValue(false);
	StaticBoxSizer1->Add(chkPASSEN_TSTOD_SD, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO Capacitance"));
	FlexGridSizer19 = new wxFlexGridSizer(0, 4, 5, 5);
	btnTune = new wxButton(this, ID_BUTTON3, _("Tune"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer19->Add(btnTune, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer19->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	cmbVCOCAP = new ComboBoxMap(this, ID_VCOCAP, wxEmptyString, wxDefaultPosition, wxSize(70,-1), 0, 0, 0, wxDefaultValidator, _T("ID_VCOCAP"));
	FlexGridSizer19->Add(cmbVCOCAP, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	btnClbr = new wxButton(this, ID_BUTTON2, _("Calibration"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer19->Add(btnClbr, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer2->Add(FlexGridSizer19, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("VCO Output"));
	FlexGridSizer21 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Voltage, V:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer21->Add(StaticText3, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	cmbVOVCOREG = new ComboBoxMap(this, ID_VOVCOREG, wxEmptyString, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_VOVCOREG"));
	FlexGridSizer21->Add(cmbVOVCOREG, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer21, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Various VCO Controls"));
	chbBYPVCOREG = new wxCheckBox(this, ID_BYPVCOREG, _("VCO Reg. Bypass"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYPVCOREG"));
	chbBYPVCOREG->SetValue(false);
	StaticBoxSizer4->Add(chbBYPVCOREG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	chbPDVCOREG = new wxCheckBox(this, ID_PDVCOREG, _("VCO Reg. PD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PDVCOREG"));
	chbPDVCOREG->SetValue(false);
	StaticBoxSizer4->Add(chbPDVCOREG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	chbFSTVCOBG = new wxCheckBox(this, ID_FSTVCOBG, _("BG Res. Shorted"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FSTVCOBG"));
	chbFSTVCOBG->SetValue(false);
	StaticBoxSizer4->Add(chbFSTVCOBG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer1->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO Comparators"));
	FlexGridSizer17 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer17->AddGrowableRow(0);
	FlexGridSizer18 = new wxFlexGridSizer(0, 4, 0, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("High:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer18->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	lblVTUNE_H = new wxStaticText(this, ID_VTUNE_H, _("0"), wxDefaultPosition, wxSize(24,13), 0, _T("ID_VTUNE_H"));
	FlexGridSizer18->Add(lblVTUNE_H, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT7, _("Low:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer18->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	lblVTUNE_L = new wxStaticText(this, ID_VTUNE_L, _("0"), wxDefaultPosition, wxSize(22,13), 0, _T("ID_VTUNE_L"));
	FlexGridSizer18->Add(lblVTUNE_L, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer17->Add(FlexGridSizer18, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnReadVtune = new wxButton(this, ID_BUTTON4, _("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer17->Add(btnReadVtune, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticBoxSizer5->Add(FlexGridSizer17, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer8 = new wxFlexGridSizer(3, 1, 5, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	FlexGridSizer13 = new wxFlexGridSizer(0, 2, 0, 5);
	chbPwrPllMods = new wxCheckBox(this, ID_EN, _("PLL Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN"));
	chbPwrPllMods->SetValue(true);
	FlexGridSizer13->Add(chbPwrPllMods, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkPFDPD = new wxCheckBox(this, ID_PFDPD, _("PFD/CP En."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PFDPD"));
	chkPFDPD->SetValue(true);
	FlexGridSizer13->Add(chkPFDPD, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkENLOBUF = new wxCheckBox(this, ID_ENLOBUF, _("LO Buffer Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ENLOBUF"));
	chkENLOBUF->SetValue(true);
	FlexGridSizer13->Add(chkENLOBUF, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkPD_VCOCOMP_SX = new wxCheckBox(this, ID_PD_VCOCOMP_SX, _("VCO COMP En."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_VCOCOMP_SX"));
	chkPD_VCOCOMP_SX->SetValue(false);
	FlexGridSizer13->Add(chkPD_VCOCOMP_SX, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkENLAMP = new wxCheckBox(this, ID_ENLAMP, _("Input limiter Amp. En."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ENLAMP"));
	chkENLAMP->SetValue(true);
	FlexGridSizer13->Add(chkENLAMP, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chbAUTOBYP = new wxCheckBox(this, ID_AUTOBYP, _("DSMN Auto Byp."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_AUTOBYP"));
	chbAUTOBYP->SetValue(false);
	FlexGridSizer13->Add(chbAUTOBYP, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkENFEEDDIV = new wxCheckBox(this, ID_ENFEEDDIV, _("Feedback Divider En."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ENFEEDDIV"));
	chkENFEEDDIV->SetValue(true);
	FlexGridSizer13->Add(chkENFEEDDIV, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chbEN_PFD_UP = new wxCheckBox(this, ID_EN_PFD_UP, _("PFD Up Pulses"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_PFD_UP"));
	chbEN_PFD_UP->SetValue(false);
	FlexGridSizer13->Add(chbEN_PFD_UP, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer12->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkPFDCLKP = new wxCheckBox(this, ID_PFDCLKP, _("PFD Clk Inverted (Unchecked-in Phase)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PFDCLKP"));
	chkPFDCLKP->SetValue(false);
	FlexGridSizer12->Add(chkPFDCLKP, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkTRI = new wxCheckBox(this, ID_TRI, _("CP Out Mode: Tri-state (Unchecked-Normal)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TRI"));
	chkTRI->SetValue(false);
	FlexGridSizer12->Add(chkTRI, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkPOL = new wxCheckBox(this, ID_POL, _("CP Out Inverted (Unchecked-Normal)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_POL"));
	chkPOL->SetValue(false);
	FlexGridSizer12->Add(chkPOL, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticBoxSizer6->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("CP Current and Offset"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT33, _("Current, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	FlexGridSizer4->Add(StaticText11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT35, _("Up Offset, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
	FlexGridSizer4->Add(StaticText18, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT34, _("Dn Offset, uA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	FlexGridSizer4->Add(StaticText16, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbICHP = new ComboBoxMap(this, ID_ICHP, wxEmptyString, wxDefaultPosition, wxSize(78,-1), 0, 0, 0, wxDefaultValidator, _T("ID_ICHP"));
	FlexGridSizer4->Add(cmbICHP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbOFFUP = new ComboBoxMap(this, ID_OFFUP, wxEmptyString, wxDefaultPosition, wxSize(83,-1), 0, 0, 0, wxDefaultValidator, _T("ID_OFFUP"));
	FlexGridSizer4->Add(cmbOFFUP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbOFFDOWN = new ComboBoxMap(this, ID_OFFDOWN, wxEmptyString, wxDefaultPosition, wxSize(75,-1), 0, 0, 0, wxDefaultValidator, _T("ID_OFFDOWN"));
	FlexGridSizer4->Add(cmbOFFDOWN, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer11->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer11, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer14 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticBoxSizer12 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Output Buffer"));
	cmbSELOUT = new ComboBoxMap(this, ID_SELOUT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_SELOUT"));
	StaticBoxSizer12->Add(cmbSELOUT, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer14->Add(StaticBoxSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer13 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Dithering Control"));
	FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 5);
	chkDITHEN = new wxCheckBox(this, ID_DITHEN, _("Use"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DITHEN"));
	chkDITHEN->SetValue(false);
	FlexGridSizer15->Add(chkDITHEN, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer16 = new wxFlexGridSizer(0, 1, 0, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT36, _("Bits Dither:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
	FlexGridSizer16->Add(StaticText20, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	cmbDITHN = new ComboBoxMap(this, ID_DITHN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DITHN"));
	FlexGridSizer16->Add(cmbDITHN, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer15->Add(FlexGridSizer16, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer13->Add(FlexGridSizer15, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer14->Add(StaticBoxSizer13, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(296,112), wxDefaultSize, wxNO_BORDER, _T("ID_NOTEBOOK1"));
	Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer9 = new wxFlexGridSizer(2, 3, 5, 5);
	FlexGridSizer10 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer10->AddGrowableRow(1);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Fractional"),
		_("Integer")
	};
	rgrMODE = new wxRadioBox(Panel4, ID_MODE, _("PLL Mode"), wxPoint(8,8), wxDefaultSize, 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_MODE"));
	rgrMODE->SetSelection(0);
	FlexGridSizer10->Add(rgrMODE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxVERTICAL, Panel4, _("Output Frequency, GHz"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	txtDesFreq = new wxTextCtrl(Panel4, ID_TEXTCTRL1, _("2.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer5->Add(txtDesFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinFreqbtn = new wxSpinButton(Panel4, ID_SPINBUTTON1, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL|wxSP_ARROW_KEYS, _T("ID_SPINBUTTON1"));
	spinFreqbtn->SetRange(0, 100);
	FlexGridSizer5->Add(spinFreqbtn, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer7->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnCalc = new wxButton(Panel4, ID_BUTTON5, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	StaticBoxSizer7->Add(btnCalc, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer10->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Calculated Values for Fractional Mode"));
	FlexGridSizer2 = new wxFlexGridSizer(5, 2, 5, 0);
	StaticText8 = new wxStaticText(Panel4, ID_STATICTEXT11, _("N Integer:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer2->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblNint = new wxStaticText(Panel4, ID_NINT, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_NINT"));
	FlexGridSizer2->Add(lblNint, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(Panel4, ID_STATICTEXT13, _("N Fractional:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer2->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblNfrac = new wxStaticText(Panel4, ID_NFRAC, _("\?"), wxDefaultPosition, wxSize(64,13), 0, _T("ID_NFRAC"));
	FlexGridSizer2->Add(lblNfrac, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(Panel4, ID_STATICTEXT15, _("Divider:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer2->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblDiv = new wxStaticText(Panel4, ID_STATICTEXT16, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer2->Add(lblDiv, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText14 = new wxStaticText(Panel4, ID_STATICTEXT17, _("Real Output Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer2->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblROutF = new wxStaticText(Panel4, ID_STATICTEXT19, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer2->Add(lblROutF, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(Panel4, ID_STATICTEXT18, _("VCO Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer2->Add(StaticText15, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblVcoF = new wxStaticText(Panel4, ID_STATICTEXT20, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer2->Add(lblVcoF, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer9->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer9, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_3[5] =
	{
		_("All Powered Down"),
		_("Low Frequency"),
		_("Mid Low Frequency"),
		_("Mid High Frequency"),
		_("High Frequency")
	};
	rgrSELVCO = new RadioGroupMap(Panel4, ID_SELVCO, _("Current VCO"), wxPoint(368,8), wxDefaultSize, 5, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SELVCO"));
	rgrSELVCO->SetSelection(2);
	FlexGridSizer9->Add(rgrSELVCO, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, Panel4, _("A and B Counter Values"));
	FlexGridSizer20 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText6 = new wxStaticText(Panel4, ID_STATICTEXT9, _("Counter A Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer20->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbACODE = new ComboBoxMap(Panel4, ID_ACODE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ACODE"));
	FlexGridSizer20->Add(cmbACODE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText7 = new wxStaticText(Panel4, ID_STATICTEXT10, _("Counter B Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer20->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbBCODE = new ComboBoxMap(Panel4, ID_BCODE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_BCODE"));
	FlexGridSizer20->Add(cmbBCODE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer8->Add(FlexGridSizer20, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(StaticBoxSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Calculated Values for Integer Mode"));
	FlexGridSizer3 = new wxFlexGridSizer(6, 2, 2, 0);
	StaticText9 = new wxStaticText(Panel4, ID_STATICTEXT21, _("Divider N:"), wxDefaultPosition, wxSize(112,13), 0, _T("ID_STATICTEXT21"));
	FlexGridSizer3->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblN = new wxStaticText(Panel4, ID_STATICTEXT22, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer3->Add(lblN, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(Panel4, ID_STATICTEXT23, _("Fvco, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer3->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvcoInt = new wxStaticText(Panel4, ID_STATICTEXT24, _("\?"), wxDefaultPosition, wxSize(64,13), 0, _T("ID_STATICTEXT24"));
	FlexGridSizer3->Add(lblFvcoInt, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(Panel4, ID_STATICTEXT25, _("Fvco/2, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	FlexGridSizer3->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco2Int = new wxStaticText(Panel4, ID_STATICTEXT26, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	FlexGridSizer3->Add(lblFvco2Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(Panel4, ID_STATICTEXT27, _("Fvco/4, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	FlexGridSizer3->Add(StaticText19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco4Int = new wxStaticText(Panel4, ID_STATICTEXT28, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	FlexGridSizer3->Add(lblFvco4Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(Panel4, ID_STATICTEXT29, _("Fvco/8, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	FlexGridSizer3->Add(StaticText21, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco8Int = new wxStaticText(Panel4, ID_STATICTEXT30, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	FlexGridSizer3->Add(lblFvco8Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(Panel4, ID_STATICTEXT31, _("Fvco/16, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	FlexGridSizer3->Add(StaticText23, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco16Int = new wxStaticText(Panel4, ID_STATICTEXT32, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	FlexGridSizer3->Add(lblFvco16Int, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer10->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(StaticBoxSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_4[5] =
	{
		_("All Powered Down"),
		_("Fvco/2"),
		_("Fvco/4"),
		_("Fvco/8"),
		_("Fvco/16")
	};
	rgrFRANGE = new RadioGroupMap(Panel4, ID_FRANGE, _("MUX/DIV Selection"), wxPoint(368,128), wxDefaultSize, 5, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_FRANGE"));
	rgrFRANGE->SetSelection(1);
	FlexGridSizer9->Add(rgrFRANGE, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel4->SetSizer(FlexGridSizer9);
	FlexGridSizer9->Fit(Panel4);
	FlexGridSizer9->SetSizeHints(Panel4);
	Panel7 = new wxPanel(Notebook1, ID_PANEL7, wxPoint(295,67), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 4, 0, 5);
	StaticBoxSizer14 = new wxStaticBoxSizer(wxVERTICAL, Panel7, _("BIST State"));
	lblBSTATE = new wxStaticText(Panel7, ID_BSTATE, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSTATE"));
	StaticBoxSizer14->Add(lblBSTATE, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btnReadBISTState = new wxButton(Panel7, ID_BUTTON6, _("Read BIST State"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	StaticBoxSizer14->Add(btnReadBISTState, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer11->Add(StaticBoxSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer15 = new wxStaticBoxSizer(wxVERTICAL, Panel7, _("BIST Signature"));
	lblBSIG = new wxStaticText(Panel7, ID_BSIG, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIG"));
	StaticBoxSizer15->Add(lblBSIG, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btnReadSignature = new wxButton(Panel7, ID_BUTTON7, _("Read Signature"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	StaticBoxSizer15->Add(btnReadSignature, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer11->Add(StaticBoxSizer15, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_5[3] =
	{
		_("Clock Disabled"),
		_("Ref Clk for BIST"),
		_("Feedback Div Out")
	};
	rgrBCLKSEL = new wxRadioBox(Panel7, ID_BCLKSEL, _("DSMN/BIST Clock"), wxPoint(236,8), wxDefaultSize, 3, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_BCLKSEL"));
	FlexGridSizer11->Add(rgrBCLKSEL, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("NINT/NFRAC"),
		_("LFSR")
	};
	rgrBINSEL = new wxRadioBox(Panel7, ID_BINSEL, _("DSMN/BIST Input"), wxPoint(356,8), wxSize(103,80), 2, __wxRadioBoxChoices_6, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_BINSEL"));
	FlexGridSizer11->Add(rgrBINSEL, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnStartBIST = new wxButton(Panel7, ID_BUTTON8, _("Start BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	FlexGridSizer11->Add(btnStartBIST, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel7->SetSizer(FlexGridSizer11);
	FlexGridSizer11->Fit(Panel7);
	FlexGridSizer11->SetSizeHints(Panel7);
	Notebook1->AddPage(Panel4, _("Frequency Control"), false);
	Notebook1->AddPage(Panel7, _("BIST Control"), false);
	FlexGridSizer7->Add(Notebook1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(this);
	FlexGridSizer6->SetSizeHints(this);

	Connect(ID_DECODE_PLL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_OEN_TSTD_SX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_PASSEN_TSTOD_SD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnTune);
	Connect(ID_VCOCAP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnbtnClbrClick);
	Connect(ID_VOVCOREG,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BYPVCOREG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_PDVCOREG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_FSTVCOBG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnbtnReadVtuneClick);
	Connect(ID_EN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_PFDPD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_ENLOBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_PD_VCOCOMP_SX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_ENLAMP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_AUTOBYP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_ENFEEDDIV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_EN_PFD_UP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_PFDCLKP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_TRI,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_POL,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_ICHP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_OFFUP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_OFFDOWN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_SELOUT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_DITHEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_DITHN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_MODE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&pnlTxPLL::OnspinFreqbtnChangeUp);
	Connect(ID_SPINBUTTON1,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&pnlTxPLL::OnspinFreqbtnChangeDown);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnCalculate);
	Connect(ID_SELVCO,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_ACODE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BCODE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_FRANGE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnbtnReadBISTStateClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnbtnReadSignatureClick);
	Connect(ID_BCLKSEL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BINSEL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxPLL::ParameterChangeHandler);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxPLL::OnbtnStartBISTClick);
	//*)

	char ctemp[80];
    wxArrayString temp;

    temp.push_back( _("Disabled"));
    temp.push_back( _("First"));
    temp.push_back( _("Second"));
    temp.push_back( _("Third"));
	cmbSELOUT->Append(temp);

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVCOCAP->Set(temp);

    temp.clear();
    for(int i=14; i<=26; ++i)
        {sprintf(ctemp, "%.1f", i/10.0); temp.push_back( ctemp );}
    cmbVOVCOREG->Set(temp);

    temp.clear();
    for(int i=0; i<=24; ++i)
        {sprintf(ctemp, "%i", i*100); temp.push_back( ctemp );}
    cmbICHP->Set(temp);

    temp.clear();
    for(int i=0; i<=24; ++i)
        {sprintf(ctemp, "%i", i*10); temp.push_back( ctemp );}
    cmbOFFUP->Set(temp);
    cmbOFFDOWN->Set(temp);

    temp.clear();
    vector<cmbKeyValuePair> acodes;
    acodes.push_back(cmbKeyValuePair(7, _("0")));
    acodes.push_back(cmbKeyValuePair(3, _("1")));
    acodes.push_back(cmbKeyValuePair(1, _("2")));
    acodes.push_back(cmbKeyValuePair(0, _("3")));
    acodes.push_back(cmbKeyValuePair(8, _("4")));
    acodes.push_back(cmbKeyValuePair(12, _("5")));
    acodes.push_back(cmbKeyValuePair(14, _("6")));
    acodes.push_back(cmbKeyValuePair(15, _("7")));
    cmbACODE->Set(acodes);

    temp.clear();
    vector<cmbKeyValuePair> bcodes;
    bcodes.push_back(cmbKeyValuePair(9, _("7")));
    bcodes.push_back(cmbKeyValuePair(8, _("8")));
    bcodes.push_back(cmbKeyValuePair(12, _("9")));
    bcodes.push_back(cmbKeyValuePair(14, _("10")));
    bcodes.push_back(cmbKeyValuePair(15, _("11")));
    bcodes.push_back(cmbKeyValuePair(3, _("12")));
    bcodes.push_back(cmbKeyValuePair(1, _("13")));
    bcodes.push_back(cmbKeyValuePair(0, _("14")));
    bcodes.push_back(cmbKeyValuePair(4, _("15")));
    bcodes.push_back(cmbKeyValuePair(6, _("16")));
    bcodes.push_back(cmbKeyValuePair(7, _("17")));
    bcodes.push_back(cmbKeyValuePair(35, _("18")));
    bcodes.push_back(cmbKeyValuePair(33, _("19")));
    bcodes.push_back(cmbKeyValuePair(32, _("20")));
    bcodes.push_back(cmbKeyValuePair(36, _("21")));
    bcodes.push_back(cmbKeyValuePair(38, _("22")));
    bcodes.push_back(cmbKeyValuePair(39, _("23")));
    bcodes.push_back(cmbKeyValuePair(51, _("24")));
    bcodes.push_back(cmbKeyValuePair(49, _("25")));
    bcodes.push_back(cmbKeyValuePair(48, _("26")));
    bcodes.push_back(cmbKeyValuePair(52, _("27")));
    bcodes.push_back(cmbKeyValuePair(54, _("28")));
    bcodes.push_back(cmbKeyValuePair(55, _("29")));
    bcodes.push_back(cmbKeyValuePair(59, _("30")));
    bcodes.push_back(cmbKeyValuePair(57, _("31")));
    bcodes.push_back(cmbKeyValuePair(56, _("32")));
    bcodes.push_back(cmbKeyValuePair(60, _("33")));
    bcodes.push_back(cmbKeyValuePair(62, _("34")));
    bcodes.push_back(cmbKeyValuePair(63, _("35")));
    cmbBCODE->Set(bcodes);

    temp.clear();
    for(int i=1; i<=8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbDITHN->Set(temp);

    int selvco_values[] = {0, 4, 5, 6, 7};
    rgrSELVCO->SetIndexValues(selvco_values, 5);
    rgrSELVCO->SetSelection(5);
    int frange_values[] = {0, 4, 5, 6, 7};
    rgrFRANGE->SetIndexValues(frange_values, 5);
    rgrFRANGE->SetSelection(4);

    m_checkboxIDToInvert.insert(ID_PFDPD);
    m_checkboxIDToInvert.insert(ID_PD_VCOCOMP_SX);

    txtDesFreq->SetValue(wxString::Format(_("%.9f"), 2.14));

    SetControlDisables();
}

pnlTxPLL::~pnlTxPLL()
{
	//(*Destroy(pnlTxPLL)
	//*)
}

void pnlTxPLL::SetType(const bool Rx)
{
    m_Rx = Rx;
    if(Rx)
    {
        wndId2Enum[ID_DECODE_PLL] = DECODE_RXPLL;
        wndId2Enum[ID_OEN_TSTD_SX] = OEN_TSTD_SX_RXPLL;
        wndId2Enum[ID_PASSEN_TSTOD_SD] = PASSEN_TSTOD_SD_RXPLL;
        wndId2Enum[ID_VCOCAP] = VCOCAP_RXPLL;
        wndId2Enum[ID_VOVCOREG] = VOVCOREG_RXPLL;
        wndId2Enum[ID_BYPVCOREG] = BYPVCOREG_RXPLL;
        wndId2Enum[ID_PDVCOREG] = PDVCOREG_RXPLL;
        wndId2Enum[ID_FSTVCOBG] = FSTVCOBG_RXPLL;
        wndId2Enum[ID_EN] = EN_RXPLL;
        wndId2Enum[ID_PFDPD] = PFDPD_RXPLL;
        wndId2Enum[ID_ENLOBUF] = ENLOBUF_RXPLL;
        wndId2Enum[ID_PD_VCOCOMP_SX] = PD_VCOCOMP_SX_RXPLL;
        wndId2Enum[ID_ENLAMP] = ENLAMP_RXPLL;
        wndId2Enum[ID_AUTOBYP] = AUTOBYP_RXPLL;
        wndId2Enum[ID_ENFEEDDIV] = ENFEEDDIV_RXPLL;
        wndId2Enum[ID_EN_PFD_UP] = EN_PFD_UP_RXPLL;
        wndId2Enum[ID_PFDCLKP] = PFDCLKP_RXPLL;
        wndId2Enum[ID_TRI] = TRI_RXPLL;
        wndId2Enum[ID_POL] = POL_RXPLL;
        wndId2Enum[ID_ICHP] = ICHP_RXPLL;
        wndId2Enum[ID_OFFUP] = OFFUP_RXPLL;
        wndId2Enum[ID_OFFDOWN] = OFFDOWN_RXPLL;
        wndId2Enum[ID_SELOUT] = SELOUT_RXPLL;
        wndId2Enum[ID_DITHEN] = DITHEN_RXPLL;
        wndId2Enum[ID_DITHN] = DITHN_RXPLL;
        wndId2Enum[ID_MODE] = MODE_RXPLL;
        wndId2Enum[ID_NINT] = NINT_RXPLL;
        wndId2Enum[ID_NFRAC] = NFRAC_RXPLL;
        wndId2Enum[ID_SELVCO] = SELVCO_RXPLL;
        wndId2Enum[ID_ACODE] = ACODE_RXPLL;
        wndId2Enum[ID_BCODE] = BCODE_RXPLL;
        wndId2Enum[ID_FRANGE] = FRANGE_RXPLL;
        wndId2Enum[ID_BSTATE] = BSTATE_RXPLL;
        wndId2Enum[ID_BSIG] = BSIG_RXPLL;
        wndId2Enum[ID_BCLKSEL] = BCLKSEL_RXPLL;
        wndId2Enum[ID_BINSEL] = BINSEL_RXPLL;
        txtDesFreq->SetValue(wxString::Format(_("%.9f"), 2.139));
    }
    else
    {
        wndId2Enum[ID_DECODE_PLL] = DECODE_TXPLL;
        wndId2Enum[ID_OEN_TSTD_SX] = OEN_TSTD_SX_TXPLL;
        wndId2Enum[ID_PASSEN_TSTOD_SD] = PASSEN_TSTOD_SD_TXPLL;
        wndId2Enum[ID_VCOCAP] = VCOCAP_TXPLL;
        wndId2Enum[ID_VOVCOREG] = VOVCOREG_TXPLL;
        wndId2Enum[ID_BYPVCOREG] = BYPVCOREG_TXPLL;
        wndId2Enum[ID_PDVCOREG] = PDVCOREG_TXPLL;
        wndId2Enum[ID_FSTVCOBG] = FSTVCOBG_TXPLL;
        wndId2Enum[ID_EN] = EN_TXPLL;
        wndId2Enum[ID_PFDPD] = PFDPD_TXPLL;
        wndId2Enum[ID_ENLOBUF] = ENLOBUF_TXPLL;
        wndId2Enum[ID_PD_VCOCOMP_SX] = PD_VCOCOMP_SX_TXPLL;
        wndId2Enum[ID_ENLAMP] = ENLAMP_TXPLL;
        wndId2Enum[ID_AUTOBYP] = AUTOBYP_TXPLL;
        wndId2Enum[ID_ENFEEDDIV] = ENFEEDDIV_TXPLL;
        wndId2Enum[ID_EN_PFD_UP] = EN_PFD_UP_TXPLL;
        wndId2Enum[ID_PFDCLKP] = PFDCLKP_TXPLL;
        wndId2Enum[ID_TRI] = TRI_TXPLL;
        wndId2Enum[ID_POL] = POL_TXPLL;
        wndId2Enum[ID_ICHP] = ICHP_TXPLL;
        wndId2Enum[ID_OFFUP] = OFFUP_TXPLL;
        wndId2Enum[ID_OFFDOWN] = OFFDOWN_TXPLL;
        wndId2Enum[ID_SELOUT] = SELOUT_TXPLL;
        wndId2Enum[ID_DITHEN] = DITHEN_TXPLL;
        wndId2Enum[ID_DITHN] = DITHN_TXPLL;
        wndId2Enum[ID_MODE] = MODE_TXPLL;
        wndId2Enum[ID_NINT] = NINT_TXPLL;
        wndId2Enum[ID_NFRAC] = NFRAC_TXPLL;
        wndId2Enum[ID_SELVCO] = SELVCO_TXPLL;
        wndId2Enum[ID_ACODE] = ACODE_TXPLL;
        wndId2Enum[ID_BCODE] = BCODE_TXPLL;
        wndId2Enum[ID_FRANGE] = FRANGE_TXPLL;
        wndId2Enum[ID_BSTATE] = BSTATE_TXPLL;
        wndId2Enum[ID_BSIG] = BSIG_TXPLL;
        wndId2Enum[ID_BCLKSEL] = BCLKSEL_TXPLL;
        wndId2Enum[ID_BINSEL] = BINSEL_TXPLL;
        cmbSELOUT->Enable(false);
    }
}

void pnlTxPLL::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
    long value = lmsControl->GetParam(BSIG_TXPLL);
    lblBSIG->SetLabel(wxString::Format("0x%0lX", value));
}

void pnlTxPLL::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrPllMods->Enable(!enabled);
    chkENLOBUF->Enable(enabled);
    chkENLAMP->Enable(enabled);
    chkENFEEDDIV->Enable(enabled);
    chkPFDCLKP->Enable(enabled);
    chkTRI->Enable(enabled);
    chkPOL->Enable(enabled);
    chkPFDPD->Enable(enabled);
    chkPD_VCOCOMP_SX->Enable(enabled);

}

void pnlTxPLL::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    if(event.GetId() == ID_ACODE || event.GetId() == ID_BCODE)
    {
        RefreshIntPLLData();
    }
    SetControlDisables();
}

void pnlTxPLL::OnCalculate(wxCommandEvent& event)
{
    double dDesFreq;
	txtDesFreq->GetValue().ToDouble(&dDesFreq);
	if ((dDesFreq < 0.235) || (dDesFreq > 4.199))
	{
		wxMessageBox(_("Incorrect Frequency Value.\nShould be between 0.235 and 4.199 GHz."), _("WARNING"));
		return;
	}
	else
	{
	    unsigned Nint, Nfrac, ivco;
	    double realfreq;
	    double fvco;
	    int divider;
		int status = lmsControl->SetFrequency(m_Rx, dDesFreq*1000, realfreq, Nint, Nfrac, ivco, fvco, divider);
        if(status == -1)
        {
            wxMessageBox( wxString::Format("%s %f GHz", "Unable to deliver frequency!", dDesFreq), _("WARNING"));
            return;
        }

        lblNint->SetLabel(wxString::Format("%i", Nint));
        lblNfrac->SetLabel(wxString::Format("%i", Nfrac));
        lblDiv->SetLabel(wxString::Format("%.0f", pow(2.0, divider)));
        lblROutF->SetLabel(wxString::Format("%f", realfreq/1000.0));
        lblVcoF->SetLabel(wxString::Format("%f", fvco/1000.0));
        RefreshIntPLLData();
	}
	UpdateGUI();
}

void pnlTxPLL::OnTune(wxCommandEvent& event)
{
    lmsControl->Tune(m_Rx);
    cmbVCOCAP->SetSelection(lmsControl->GetParam(m_Rx?VCOCAP_RXPLL:VCOCAP_TXPLL));
}

void pnlTxPLL::OnbtnReadVtuneClick(wxCommandEvent& event)
{
    int vtune_h, vtune_l;
    if(m_Rx)
    {
        vtune_h = lmsControl->GetParam(VTUNE_H_RXPLL, true, true);
        vtune_l = lmsControl->GetParam(VTUNE_L_RXPLL, true, true);
    }
    else
    {
        vtune_h = lmsControl->GetParam(VTUNE_H_TXPLL, true, true);
        vtune_l = lmsControl->GetParam(VTUNE_L_TXPLL, true, true);
    }
    lblVTUNE_H->SetLabel(wxString::Format("%i", vtune_h));
    lblVTUNE_L->SetLabel(wxString::Format("%i", vtune_l));
}

void pnlTxPLL::OnbtnClbrClick(wxCommandEvent& event)
{
    dlgFreqVsCap dlg(this);
    dlg.Initialize(lmsControl, m_Rx);
    dlg.ShowModal();
}

void pnlTxPLL::OnbtnReadSignatureClick(wxCommandEvent& event)
{
    long value = 0;
    if(m_Rx)
        value = lmsControl->GetParam(BSIG_RXPLL, true, true);
    else
        value = lmsControl->GetParam(BSIG_TXPLL, true, true);
    lblBSIG->SetLabel(wxString::Format("0x%0X", value));
}

void pnlTxPLL::OnbtnReadBISTStateClick(wxCommandEvent& event)
{
    long value = 0;
    if(m_Rx)
        value = lmsControl->GetParam(BSTATE_RXPLL, true, true);
    else
        value = lmsControl->GetParam(BSTATE_TXPLL, true, true);
    lblBSTATE->SetLabel(value==1 ? _("In progress") : _("Not running"));
}

void pnlTxPLL::OnbtnStartBISTClick(wxCommandEvent& event)
{
    if(m_Rx)
    {
        lmsControl->SetParam(BSTART_RXPLL, 0);
        lmsControl->SetParam(BSTART_RXPLL, 1);
    }
    else
    {
        lmsControl->SetParam(BSTART_TXPLL, 0);
        lmsControl->SetParam(BSTART_TXPLL, 1);
    }
}

void pnlTxPLL::RefreshIntPLLData()
{
    int N;
    double intFvco = 0;
    lmsControl->CalcIntPllData(m_Rx, intFvco, N);
    lblN->SetLabel(wxString::Format("%i", N));
    lblFvcoInt->SetLabel(wxString::Format("%f", intFvco/1000.0));
    lblFvco2Int->SetLabel(wxString::Format("%f", intFvco/1000.0/2));
    lblFvco4Int->SetLabel(wxString::Format("%f", intFvco/1000.0/4));
    lblFvco8Int->SetLabel(wxString::Format("%f", intFvco/1000.0/8));
    lblFvco16Int->SetLabel(wxString::Format("%f", intFvco/1000.0/16));
}

void pnlTxPLL::OnspinFreqbtnChangeUp(wxSpinEvent& event)
{
    double freq = 0;
    txtDesFreq->GetValue().ToDouble(&freq);
    freq = freq + 0.001;
    txtDesFreq->SetValue(wxString::Format("%f", freq));
}

void pnlTxPLL::OnspinFreqbtnChangeDown(wxSpinEvent& event)
{
    double freq = 0;
    txtDesFreq->GetValue().ToDouble(&freq);
    freq = freq - 0.001;
    txtDesFreq->SetValue(wxString::Format("%f", freq));
}
