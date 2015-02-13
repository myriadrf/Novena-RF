#include "pnlTop.h"
#include <fstream>
#include "Algorithms.h"
#include "LMS_Parameter.h"

//(*InternalHeaders(pnlTop)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace std;
using namespace lms6;

//(*IdInit(pnlTop)
const long pnlTop::ID_BUTTON1 = wxNewId();
const long pnlTop::ID_BUTTON2 = wxNewId();
const long pnlTop::ID_BUTTON4 = wxNewId();
const long pnlTop::ID_STATICTEXT1 = wxNewId();
const long pnlTop::ID_STATICTEXT2 = wxNewId();
const long pnlTop::ID_STATICLINE1 = wxNewId();
const long pnlTop::ID_DCCAL_ADDR = wxNewId();
const long pnlTop::ID_CALVAL = wxNewId();
const long pnlTop::ID_BUTTON5 = wxNewId();
const long pnlTop::ID_STATICTEXT3 = wxNewId();
const long pnlTop::ID_DC_REGVAL_TOP = wxNewId();
const long pnlTop::ID_STATICTEXT4 = wxNewId();
const long pnlTop::ID_DC_LOCK_TOP = wxNewId();
const long pnlTop::ID_STATICTEXT5 = wxNewId();
const long pnlTop::ID_DC_CLBR_DONE_TOP = wxNewId();
const long pnlTop::ID_STATICTEXT6 = wxNewId();
const long pnlTop::ID_DC_UD_TOP = wxNewId();
const long pnlTop::ID_RF_LOOPBACK_CONTROL = wxNewId();
const long pnlTop::ID_BB_LOOPBACK = wxNewId();
const long pnlTop::ID_EN_TOP = wxNewId();
const long pnlTop::ID_STXEN = wxNewId();
const long pnlTop::ID_SRXEN = wxNewId();
const long pnlTop::ID_PD_1_TOP = wxNewId();
const long pnlTop::ID_PD_0_TOP = wxNewId();
const long pnlTop::ID_RXOUTSW = wxNewId();
const long pnlTop::ID_TDD_MODE_SELECTION = wxNewId();
const long pnlTop::ID_FDDTDD_SELECTION = wxNewId();
const long pnlTop::ID_XCO_BUF_POWER_DOWN = wxNewId();
const long pnlTop::ID_XCO_BUF_SELF_BIASING = wxNewId();
const long pnlTop::ID_XCO_BUF_BYPASS = wxNewId();
const long pnlTop::ID_CLK_EN_0 = wxNewId();
const long pnlTop::ID_CLK_EN_4 = wxNewId();
const long pnlTop::ID_CLK_EN_1 = wxNewId();
const long pnlTop::ID_CLK_EN_5 = wxNewId();
const long pnlTop::ID_CLK_EN_2 = wxNewId();
const long pnlTop::ID_CLK_EN_6 = wxNewId();
const long pnlTop::ID_CLK_EN_3 = wxNewId();
const long pnlTop::ID_PD_CLKLPFCAL = wxNewId();
const long pnlTop::ID_LPFCALENENF = wxNewId();
const long pnlTop::ID_LPFCALRST = wxNewId();
const long pnlTop::ID_LPFCALEN = wxNewId();
const long pnlTop::ID_STATICTEXT11 = wxNewId();
const long pnlTop::ID_RCCAL_LPFCAL = wxNewId();
const long pnlTop::ID_BUTTON3 = wxNewId();
const long pnlTop::ID_STATICTEXT13 = wxNewId();
const long pnlTop::ID_LPFCALCODE = wxNewId();
const long pnlTop::ID_STATICTEXT14 = wxNewId();
const long pnlTop::ID_LPFCALBW = wxNewId();
const long pnlTop::ID_CLKSEL_LPFCAL = wxNewId();
const long pnlTop::ID_DECODE_TOP = wxNewId();
const long pnlTop::ID_SPIMODE = wxNewId();
const long pnlTop::ID_RX_TEST_MODE_EN = wxNewId();
const long pnlTop::ID_DSMRST = wxNewId();
const long pnlTop::ID_GLOBALRESET = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTop,wxPanel)
	//(*EventTable(pnlTop)
	//*)
END_EVENT_TABLE()

pnlTop::pnlTop(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlTop::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTop)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer7;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer14;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Calibration"));
	FlexGridSizer4 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(3, 3, 0, 5);
	btnDCRstClbr = new wxButton(this, ID_BUTTON1, _("Reset Calibration"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer5->Add(btnDCRstClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCLoadVal = new wxButton(this, ID_BUTTON2, _("Load Cnt Value"), wxPoint(136,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer5->Add(btnDCLoadVal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCStartClbr = new wxButton(this, ID_BUTTON4, _("Start Calibration"), wxPoint(256,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer5->Add(btnDCStartClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("CAL ModuleAddress:"), wxPoint(8,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Calibration Value:"), wxPoint(136,40), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer5->Add(StaticText2, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine1->Hide();
	FlexGridSizer5->Add(StaticLine1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCalAddr = new ComboBoxMap(this, ID_DCCAL_ADDR, wxEmptyString, wxPoint(8,56), wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DCCAL_ADDR"));
	FlexGridSizer5->Add(cmbDCCalAddr, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCalVal = new ComboBoxMap(this, ID_CALVAL, wxEmptyString, wxPoint(136,56), wxSize(100,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CALVAL"));
	FlexGridSizer5->Add(cmbCalVal, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCReadVal = new wxButton(this, ID_BUTTON5, _("Read Values"), wxDefaultPosition, wxSize(96,-1), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer5->Add(btnDCReadVal, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Calibration Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_REGVAL = new wxStaticText(this, ID_DC_REGVAL_TOP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_REGVAL_TOP"));
	FlexGridSizer6->Add(lblDC_REGVAL, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_DC_LOCK_TOP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_LOCK_TOP"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_DC_CLBR_DONE_TOP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_CLBR_DONE_TOP"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_DC_UD_TOP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_UD_TOP"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 5, 5);
	FlexGridSizer11 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 5, 5);
	wxString __wxRadioBoxChoices_1[4] =
	{
		_("Disabled"),
		_("TxMIX to LNA1 Path"),
		_("TxMIX to LNA2 Path"),
		_("TxMIX to LNA3 (GSM) Path")
	};
	rgrRFLB = new wxRadioBox(this, ID_RF_LOOPBACK_CONTROL, _("RF Loopback Control"), wxPoint(8,120), wxDefaultSize, 4, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RF_LOOPBACK_CONTROL"));
	FlexGridSizer8->Add(rgrRFLB, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[4] =
	{
		_("Disabled"),
		_("loopb to LPF input"),
		_("loopb to VGA2 input"),
		_("loopb to Rx Out Pins")
	};
	rgrBBLB = new wxRadioBox(this, ID_BB_LOOPBACK, _("BB Loopback"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_BB_LOOPBACK"));
	FlexGridSizer8->Add(rgrBBLB, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power Control"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	chbPwrTopMods = new wxCheckBox(this, ID_EN_TOP, _("Top Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_TOP"));
	chbPwrTopMods->SetValue(true);
	BoxSizer1->Add(chbPwrTopMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrSoftTx = new wxCheckBox(this, ID_STXEN, _("Soft Tx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_STXEN"));
	chbPwrSoftTx->SetValue(false);
	BoxSizer1->Add(chbPwrSoftTx, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrSoftRx = new wxCheckBox(this, ID_SRXEN, _("Soft Rx Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SRXEN"));
	chbPwrSoftRx->SetValue(false);
	BoxSizer1->Add(chbPwrSoftRx, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrLpfCal = new wxCheckBox(this, ID_PD_1_TOP, _("DCOREG LPFCAL Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_1_TOP"));
	chbPwrLpfCal->SetValue(false);
	BoxSizer1->Add(chbPwrLpfCal, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrRfLbsw = new wxCheckBox(this, ID_PD_0_TOP, _("RF LBSW Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_0_TOP"));
	chbPwrRfLbsw->SetValue(false);
	BoxSizer1->Add(chbPwrRfLbsw, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_("Open (off)"),
		_("Closed (on)")
	};
	rgrRXOUTSW = new wxRadioBox(this, ID_RXOUTSW, _("RX Out/ADC In Switch"), wxPoint(208,248), wxDefaultSize, 2, __wxRadioBoxChoices_3, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RXOUTSW"));
	rgrRXOUTSW->SetSelection(1);
	BoxSizer3->Add(rgrRXOUTSW, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_("Transmit"),
		_("Receive")
	};
	rgrTDDMOD = new wxRadioBox(this, ID_TDD_MODE_SELECTION, _("TDD Mode Selection"), wxPoint(208,296), wxDefaultSize, 2, __wxRadioBoxChoices_4, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TDD_MODE_SELECTION"));
	rgrTDDMOD->SetSelection(1);
	BoxSizer3->Add(rgrTDDMOD, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_("FDD"),
		_("TDD")
	};
	rgrFDDTDD = new wxRadioBox(this, ID_FDDTDD_SELECTION, _("FDD/TDD Selection"), wxPoint(208,344), wxDefaultSize, 2, __wxRadioBoxChoices_5, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_FDDTDD_SELECTION"));
	rgrFDDTDD->SetSelection(1);
	BoxSizer3->Add(rgrFDDTDD, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(BoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("XCO Buffer"));
	chbPDXCOBUF = new wxCheckBox(this, ID_XCO_BUF_POWER_DOWN, _("Power Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_XCO_BUF_POWER_DOWN"));
	chbPDXCOBUF->SetValue(false);
	StaticBoxSizer3->Add(chbPDXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chbSLFBXCOBUF = new wxCheckBox(this, ID_XCO_BUF_SELF_BIASING, _("Self Biasing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_XCO_BUF_SELF_BIASING"));
	chbSLFBXCOBUF->SetValue(true);
	StaticBoxSizer3->Add(chbSLFBXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chbBYPXCOBUF = new wxCheckBox(this, ID_XCO_BUF_BYPASS, _("Bypass"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_XCO_BUF_BYPASS"));
	chbBYPXCOBUF->SetValue(false);
	StaticBoxSizer3->Add(chbBYPXCOBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(FlexGridSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10 = new wxFlexGridSizer(0, 1, 5, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Clock Buffers"));
	FlexGridSizer16 = new wxFlexGridSizer(0, 2, 0, 5);
	chkCLK_EN_0 = new wxCheckBox(this, ID_CLK_EN_0, _("Tx DSM SPI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_0"));
	chkCLK_EN_0->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_0, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkCLK_EN_4 = new wxCheckBox(this, ID_CLK_EN_4, _("Rx VGA2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_4"));
	chkCLK_EN_4->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkCLK_EN_1 = new wxCheckBox(this, ID_CLK_EN_1, _("Tx LPF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_1"));
	chkCLK_EN_1->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkCLK_EN_5 = new wxCheckBox(this, ID_CLK_EN_5, _("LPF CALCORE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_5"));
	chkCLK_EN_5->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkCLK_EN_2 = new wxCheckBox(this, ID_CLK_EN_2, _("Rx DSM SPI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_2"));
	chkCLK_EN_2->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkCLK_EN_6 = new wxCheckBox(this, ID_CLK_EN_6, _("PLLCLKOUT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_6"));
	chkCLK_EN_6->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkCLK_EN_3 = new wxCheckBox(this, ID_CLK_EN_3, _("Rx LPF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CLK_EN_3"));
	chkCLK_EN_3->SetValue(false);
	FlexGridSizer16->Add(chkCLK_EN_3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer6->Add(FlexGridSizer16, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TRX LPF Calibration"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer9->AddGrowableCol(0);
	chbPD_CLKLPFCAL = new wxCheckBox(this, ID_PD_CLKLPFCAL, _("DIV8 for LPD Tuning CLock PD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_CLKLPFCAL"));
	chbPD_CLKLPFCAL->SetValue(false);
	FlexGridSizer9->Add(chbPD_CLKLPFCAL, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer12->AddGrowableCol(0);
	chkLpfCalEnEnf = new wxCheckBox(this, ID_LPFCALENENF, _("Enable Enforce Mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LPFCALENENF"));
	chkLpfCalEnEnf->SetValue(false);
	FlexGridSizer12->Add(chkLpfCalEnEnf, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	chkLpfCalRst = new wxCheckBox(this, ID_LPFCALRST, _("Reset LPFCAL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LPFCALRST"));
	chkLpfCalRst->SetValue(false);
	FlexGridSizer12->Add(chkLpfCalRst, 0, wxALIGN_RIGHT|wxALIGN_TOP, 0);
	FlexGridSizer9->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkLpfCalEn = new wxCheckBox(this, ID_LPFCALEN, _("Enable LPFCAL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LPFCALEN"));
	chkLpfCalEn->SetValue(false);
	FlexGridSizer9->Add(chkLpfCalEn, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer13 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer13->AddGrowableCol(0);
	FlexGridSizer13->AddGrowableCol(1);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, this, _("RCCAL LPFCAL Value"));
	FlexGridSizer14 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer14->AddGrowableCol(0);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT11, _("RCCAL_LPFCAL:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer14->Add(StaticText7, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblRCCAL_LPFCAL = new wxStaticText(this, ID_RCCAL_LPFCAL, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_RCCAL_LPFCAL"));
	FlexGridSizer14->Add(lblRCCAL_LPFCAL, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnReadRCCALVal = new wxButton(this, ID_BUTTON3, _("Read Value"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StaticBoxSizer8->Add(btnReadRCCALVal, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer13->Add(StaticBoxSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer15 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT13, _("LPFCAL Code:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer15->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	cmbLpfCalCode = new ComboBoxMap(this, ID_LPFCALCODE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LPFCALCODE"));
	FlexGridSizer15->Add(cmbLpfCalCode, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT14, _("LPF Bandwidth:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer15->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
	cmbLpfCalBw = new ComboBoxMap(this, ID_LPFCALBW, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LPFCALBW"));
	FlexGridSizer15->Add(cmbLpfCalBw, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer13->Add(FlexGridSizer15, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(FlexGridSizer13, 1, wxTOP|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_("From TxPLL"),
		_("PLL Reference")
	};
	rgrCLKSEL_LPFCAL = new wxRadioBox(this, ID_CLKSEL_LPFCAL, _("LPF Tuning Clock"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CLKSEL_LPFCAL"));
	rgrCLKSEL_LPFCAL->SetSelection(1);
	FlexGridSizer9->Add(rgrCLKSEL_LPFCAL, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	StaticBoxSizer4->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(5, 1, 0, 0);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_TOP, _("Decoding"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_TOP"));
	FlexGridSizer3->Add(rgrDecode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_8[2] =
	{
		_("3 Wire"),
		_("4 Wire")
	};
	rgrSpiMode = new wxRadioBox(this, ID_SPIMODE, _("SPI Port Mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SPIMODE"));
	rgrSpiMode->SetSelection(1);
	FlexGridSizer3->Add(rgrSpiMode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Rx Bypass Mode"));
	chbRxTestModeEn = new wxCheckBox(this, ID_RX_TEST_MODE_EN, _("TIA Shorted\nTo Output Pins"), wxDefaultPosition, wxSize(100,-1), 0, wxDefaultValidator, _T("ID_RX_TEST_MODE_EN"));
	chbRxTestModeEn->SetValue(false);
	StaticBoxSizer5->Add(chbRxTestModeEn, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_9[2] =
	{
		_("Reset State"),
		_("Inactive")
	};
	rgrDsmRst = new wxRadioBox(this, ID_DSMRST, _("DSM Soft Reset"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DSMRST"));
	rgrDsmRst->SetSelection(1);
	FlexGridSizer3->Add(rgrDsmRst, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Global Reset"));
	swReset = new wxToggleButton(this, ID_GLOBALRESET, _("RESET is OFF"), wxPoint(16,16), wxSize(100,100), 0, wxDefaultValidator, _T("ID_GLOBALRESET"));
	StaticBoxSizer7->Add(swReset, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnbtnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnbtnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnbtnDCStartClbrClick);
	Connect(ID_DCCAL_ADDR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CALVAL,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnbtnDCReadValClick);
	Connect(ID_RF_LOOPBACK_CONTROL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_BB_LOOPBACK,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::OnrgrBBLBSelect);
	Connect(ID_EN_TOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_STXEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_SRXEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_PD_1_TOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_PD_0_TOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_RXOUTSW,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_TDD_MODE_SELECTION,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_FDDTDD_SELECTION,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_XCO_BUF_POWER_DOWN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_XCO_BUF_SELF_BIASING,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_XCO_BUF_BYPASS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_0,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLK_EN_3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_PD_CLKLPFCAL,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_LPFCALENENF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_LPFCALRST,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_LPFCALEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnbtnReadRCCALValClick);
	Connect(ID_LPFCALCODE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_LPFCALBW,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_CLKSEL_LPFCAL,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_DECODE_TOP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_SPIMODE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_RX_TEST_MODE_EN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_DSMRST,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTop::ParameterChangeHandler);
	Connect(ID_GLOBALRESET,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&pnlTop::OnswResetToggle);
	//*)

	wndId2Enum[ID_DCCAL_ADDR] = DC_ADDR_TOP;
    wndId2Enum[ID_CALVAL] = DC_CNTVAL_TOP;
    wndId2Enum[ID_RF_LOOPBACK_CONTROL] = LBRFEN;
    //wndId2Enum[ID_BB_LOOPBACK] = ;
    wndId2Enum[ID_EN_TOP] = EN_TOP;
    wndId2Enum[ID_STXEN] = STXEN;
    wndId2Enum[ID_SRXEN] = SRXEN;
    wndId2Enum[ID_PD_1_TOP] = PD_1_TOP;
    wndId2Enum[ID_PD_0_TOP] = PD_0_TOP;
    wndId2Enum[ID_RXOUTSW] = RXOUTSW;
    wndId2Enum[ID_TDD_MODE_SELECTION] = TDDMOD;
    wndId2Enum[ID_FDDTDD_SELECTION] = FDDTDD;
    wndId2Enum[ID_XCO_BUF_POWER_DOWN] = PDXCOBUF;
    wndId2Enum[ID_XCO_BUF_SELF_BIASING] = SLFBXCOBUF;
    wndId2Enum[ID_XCO_BUF_BYPASS] = BYPXCOBUF;
    wndId2Enum[ID_PD_CLKLPFCAL] = PD_CLKLPFCAL;
    wndId2Enum[ID_LPFCALENENF] = ENF_EN_CAL_LPFCAL;
    wndId2Enum[ID_LPFCALRST] = RST_CAL_LPFCAL;
    wndId2Enum[ID_LPFCALEN] = EN_CAL_LPFCAL;
    wndId2Enum[ID_RCCAL_LPFCAL] = RCCAL_LPFCAL;
    wndId2Enum[ID_LPFCALCODE] = FORCE_CODE_CAL_LPFCAL;
    wndId2Enum[ID_LPFCALBW] = BWC_LPFCAL;
    wndId2Enum[ID_CLKSEL_LPFCAL] = CLKSEL_LPFCAL;
    wndId2Enum[ID_DECODE_TOP] = DECODE_TOP;
    wndId2Enum[ID_SPIMODE] = TFWMODE;
    wndId2Enum[ID_RX_TEST_MODE_EN] = BBBYP;
    wndId2Enum[ID_DSMRST] = SRESET;
    wndId2Enum[ID_CLK_EN_0] = CLK_EN_0;
    wndId2Enum[ID_CLK_EN_1] = CLK_EN_1;
    wndId2Enum[ID_CLK_EN_2] = CLK_EN_2;
    wndId2Enum[ID_CLK_EN_3] = CLK_EN_3;
    wndId2Enum[ID_CLK_EN_4] = CLK_EN_4;
    wndId2Enum[ID_CLK_EN_5] = CLK_EN_5;
    wndId2Enum[ID_CLK_EN_6] = CLK_EN_6;
    wndId2Enum[ID_DC_REGVAL_TOP] = DC_REGVAL_TOP;
    wndId2Enum[ID_DC_LOCK_TOP] = DC_LOCK_TOP;
    wndId2Enum[ID_DC_CLBR_DONE_TOP] = DC_CLBR_DONE_TOP;
    wndId2Enum[ID_DC_UD_TOP] = DC_UD_TOP;

    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<1; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbDCCalAddr->Set(temp);

    temp.clear();
    temp.push_back( _("14 MHz"));
    temp.push_back( _("10 MHz"));
    temp.push_back( _("7 MHz"));
    temp.push_back( _("6 MHz"));
    temp.push_back( _("5 MHz"));
    temp.push_back( _("4.375 MHz"));
    temp.push_back( _("3.5 MHz"));
    temp.push_back( _("3 MHz"));
    temp.push_back( _("2.75 MHz"));
    temp.push_back( _("2.5 MHz"));
    temp.push_back( _("1.92 MHz"));
    temp.push_back( _("1.5 MHz"));
    temp.push_back( _("1.375 MHz"));
    temp.push_back( _("1.25 MHz"));
    temp.push_back( _("0.875 MHz"));
    temp.push_back( _("0.75 MHz"));
    cmbLpfCalBw->Set(temp);

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbCalVal->Set(temp);

    temp.clear();
    temp.push_back(_("000"));
    temp.push_back(_("001"));
    temp.push_back(_("010"));
    temp.push_back(_("011"));
    temp.push_back(_("100"));
    temp.push_back(_("101"));
    temp.push_back(_("110"));
    temp.push_back(_("111"));
    cmbLpfCalCode->Set(temp);

    m_checkboxIDToInvert.insert(ID_PD_1_TOP);

    SetControlDisables();
}

pnlTop::~pnlTop()
{
	//(*Destroy(pnlTop)
	//*)
}

void pnlTop::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}

void pnlTop::OnswResetToggle(wxCommandEvent& event)
{
    if(swReset->GetValue() == 1)
    {
        if(lmsControl->ResetChip(LMS_RST_ACTIVATE) == 1)
        {
            swReset->SetLabel("RESET is ON");
        }
        else
            swReset->SetValue(0);
    }
    else
    {
        if(lmsControl->ResetChip(LMS_RST_DEACTIVATE) == 1)
        {
            swReset->SetLabel("RESET is OFF");
        }
        else
            swReset->SetValue(1);
    }
}

void pnlTop::OnrgrBBLBSelect(wxCommandEvent& event)
{
    int valLBEN_LPFIN = 0;
    int valLBEN_VGA2IN = 0;
    int valLBEN_OPIN = 0;

    if(event.GetInt() == 0)
    {
        valLBEN_LPFIN = 0;
        valLBEN_VGA2IN = 0;
        valLBEN_OPIN = 0;
    }
    else if(event.GetInt() == 1)
    {
        valLBEN_LPFIN = 1;
        valLBEN_VGA2IN = 0;
        valLBEN_OPIN = 0;
    }
    else if(event.GetInt() == 2)
    {
        valLBEN_LPFIN = 0;
        valLBEN_VGA2IN = 1;
        valLBEN_OPIN = 0;
    }
    else if(event.GetInt() == 3)
    {
        valLBEN_LPFIN = 0;
        valLBEN_VGA2IN = 0;
        valLBEN_OPIN = 1;
    }
    lmsControl->SetParam(LBEN_LPFIN, valLBEN_LPFIN);
    lmsControl->SetParam(LBEN_VGA2IN, valLBEN_VGA2IN);
    lmsControl->SetParam(LBEN_OPIN, valLBEN_OPIN);
}

void pnlTop::OnbtnReadRCCALValClick(wxCommandEvent& event)
{
    int value = lmsControl->GetParam(RCCAL_LPFCAL, true, true);
    lblRCCAL_LPFCAL->SetLabel( wxString::Format("%li", value));
}

void pnlTop::OnbtnDCRstClbrClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCResetCalibration(TOP);
}

void pnlTop::OnbtnDCLoadValClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCLoadValues(TOP);
}

void pnlTop::OnbtnDCStartClbrClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCStartCalibration(TOP);
}

void pnlTop::OnbtnDCReadValClick(wxCommandEvent& event)
{
    lblDC_REGVAL->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_REGVAL_TOP, true, true)));
    lblDC_LOCK->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_LOCK_TOP, true, true)));
    lblDC_CLBR_DONE->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_CLBR_DONE_TOP, true, true)));
    lblDC_UD->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_UD_TOP, true, true)));
}

void pnlTop::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    int valLBEN_LPFIN = lmsControl->GetParam(LBEN_LPFIN);
    int valLBEN_VGA2IN = lmsControl->GetParam(LBEN_VGA2IN);
    int valLBEN_OPIN = lmsControl->GetParam(LBEN_OPIN);
    if((valLBEN_LPFIN == 0) && (valLBEN_VGA2IN == 0) && (valLBEN_OPIN == 0))
        rgrBBLB->SetSelection(0);
    else if(valLBEN_LPFIN == 1)
        rgrBBLB->SetSelection(1);
    else if(valLBEN_VGA2IN == 1)
        rgrBBLB->SetSelection(2);
    else if(valLBEN_OPIN == 1)
        rgrBBLB->SetSelection(3);
    SetControlDisables();
}

void pnlTop::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrLpfCal->Enable(enabled);
    chbPwrRfLbsw->Enable(enabled);
    chbPwrTopMods->Enable(!enabled);
}

void pnlTop::UpdateTooltips(wxWindow *panel)
{
    GUIPanel::UpdateTooltips(this);
    LMS_Parameter params[] = {LBEN_LPFIN, LBEN_VGA2IN, LBEN_OPIN};
    for(int i=1; i<4; ++i)
    {
        Parameter cp = lmsControl->getRegistersMap()->getParameterInfo( params[i-1] );
        char cname[64];
        sprintf(cname, "%s", cp.name.c_str());
        char caddr[64];
        memset(caddr, 0, sizeof(caddr));
        sprintf(caddr, "0x%.2X[%i]", cp.registers[0].addr, cp.registers[0].lsb);
        rgrBBLB->SetItemToolTip(i, wxString::Format("%s %s", caddr, cname) );
    }
}
