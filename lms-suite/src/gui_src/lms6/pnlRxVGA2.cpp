#include "pnlRxVGA2.h"
#include "Algorithms.h"
//(*InternalHeaders(pnlRxVGA2)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlRxVGA2)
const long pnlRxVGA2::ID_BUTTON1 = wxNewId();
const long pnlRxVGA2::ID_BUTTON2 = wxNewId();
const long pnlRxVGA2::ID_BUTTON4 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT1 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT2 = wxNewId();
const long pnlRxVGA2::ID_STATICLINE1 = wxNewId();
const long pnlRxVGA2::ID_DC_ADDR_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_DC_CNTVAL_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_BUTTON5 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT3 = wxNewId();
const long pnlRxVGA2::ID_DC_REGVAL_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT4 = wxNewId();
const long pnlRxVGA2::ID_DC_LOCK_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT5 = wxNewId();
const long pnlRxVGA2::ID_DC_CLBR_DONE_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT6 = wxNewId();
const long pnlRxVGA2::ID_DC_UD_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_EN_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_PD_9 = wxNewId();
const long pnlRxVGA2::ID_PD_8 = wxNewId();
const long pnlRxVGA2::ID_PD_7 = wxNewId();
const long pnlRxVGA2::ID_PD_6 = wxNewId();
const long pnlRxVGA2::ID_PD_5 = wxNewId();
const long pnlRxVGA2::ID_PD_4 = wxNewId();
const long pnlRxVGA2::ID_PD_3 = wxNewId();
const long pnlRxVGA2::ID_PD_2 = wxNewId();
const long pnlRxVGA2::ID_PD_1 = wxNewId();
const long pnlRxVGA2::ID_PD_0 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT11 = wxNewId();
const long pnlRxVGA2::ID_VGA2GAIN_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT12 = wxNewId();
const long pnlRxVGA2::ID_VGA2GAINB = wxNewId();
const long pnlRxVGA2::ID_STATICTEXT13 = wxNewId();
const long pnlRxVGA2::ID_VGA2GAINA = wxNewId();
const long pnlRxVGA2::ID_VCM_RXVGA2 = wxNewId();
const long pnlRxVGA2::ID_DECODE_RXVGA2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlRxVGA2,wxPanel)
	//(*EventTable(pnlRxVGA2)
	//*)
END_EVENT_TABLE()

pnlRxVGA2::pnlRxVGA2(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlRxVGA2::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlRxVGA2)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 5);
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
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
	cmbDCCalAddr = new ComboBoxMap(this, ID_DC_ADDR_RXVGA2, wxEmptyString, wxPoint(8,56), wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DC_ADDR_RXVGA2"));
	FlexGridSizer5->Add(cmbDCCalAddr, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCalVal = new ComboBoxMap(this, ID_DC_CNTVAL_RXVGA2, wxEmptyString, wxPoint(136,56), wxSize(100,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DC_CNTVAL_RXVGA2"));
	FlexGridSizer5->Add(cmbCalVal, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCReadVal = new wxButton(this, ID_BUTTON5, _("Read Values"), wxDefaultPosition, wxSize(96,-1), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer5->Add(btnDCReadVal, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Calibration Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_REGVAL = new wxStaticText(this, ID_DC_REGVAL_RXVGA2, _("\?\?\?"), wxDefaultPosition, wxSize(78,13), 0, _T("ID_DC_REGVAL_RXVGA2"));
	FlexGridSizer6->Add(lblDC_REGVAL, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_DC_LOCK_RXVGA2, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_LOCK_RXVGA2"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_DC_CLBR_DONE_RXVGA2, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_CLBR_DONE_RXVGA2"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_DC_UD_RXVGA2, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_UD_RXVGA2"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrVGA2Mods = new wxCheckBox(this, ID_EN_RXVGA2, _("RxVGA2 Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_RXVGA2"));
	chbPwrVGA2Mods->SetValue(false);
	StaticBoxSizer2->Add(chbPwrVGA2Mods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCurrR = new wxCheckBox(this, ID_PD_9, _("DC Current Regulator Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_9"));
	chbPwrDCCurrR->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCurrR, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDACB = new wxCheckBox(this, ID_PD_8, _("VGA2B DC Cal. DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_8"));
	chbPwrDCDACB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDACB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpB = new wxCheckBox(this, ID_PD_7, _("VGA2B DC Cal. Comp. Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_7"));
	chbPwrDCCmpB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDACA = new wxCheckBox(this, ID_PD_6, _("VGA2A DC Cal. DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_6"));
	chbPwrDCDACA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDACA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpA = new wxCheckBox(this, ID_PD_5, _("VGA2A DC Cal. Comp. Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_5"));
	chbPwrDCCmpA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBG = new wxCheckBox(this, ID_PD_4, _("Band Gap Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_4"));
	chbPwrBG->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypAB = new wxCheckBox(this, ID_PD_3, _("Out Buff. in Both VGAs Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_3"));
	chbPwrBypAB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypAB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypB = new wxCheckBox(this, ID_PD_2, _("VGA2B Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_2"));
	chbPwrBypB->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypB, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrBypA = new wxCheckBox(this, ID_PD_1, _("VGA2A Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_1"));
	chbPwrBypA->SetValue(false);
	StaticBoxSizer2->Add(chbPwrBypA, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrCurrRef = new wxCheckBox(this, ID_PD_0, _("Current Reference Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_0"));
	chbPwrCurrRef->SetValue(false);
	StaticBoxSizer2->Add(chbPwrCurrRef, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("VGA2 Control"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT11, _("VGA2 Gain, dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer7->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2G_u = new ComboBoxMap(this, ID_VGA2GAIN_RXVGA2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2GAIN_RXVGA2"));
	FlexGridSizer7->Add(cmbVga2G_u, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT12, _("VGA2B Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer7->Add(StaticText8, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2GB_t = new ComboBoxMap(this, ID_VGA2GAINB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2GAINB"));
	FlexGridSizer7->Add(cmbVga2GB_t, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT13, _("VGA2A Gain (Test), dB:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer7->Add(StaticText9, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbVga2GA_t = new ComboBoxMap(this, ID_VGA2GAINA, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2GAINA"));
	FlexGridSizer7->Add(cmbVga2GA_t, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(StaticBoxSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("VGA2 CM Voltage"));
	cmbVCM = new ComboBoxMap(this, ID_VCM_RXVGA2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VCM_RXVGA2"));
	StaticBoxSizer4->Add(cmbVCM, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE_RXVGA2, _("Decoding"), wxPoint(720,8), wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE_RXVGA2"));
	FlexGridSizer1->Add(rgrDecode, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::OnbtnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::OnbtnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::OnbtnDCStartClbrClick);
	Connect(ID_DC_ADDR_RXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_DC_CNTVAL_RXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::OnbtnDCReadValClick);
	Connect(ID_EN_RXVGA2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_8,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_PD_0,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_VGA2GAIN_RXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_VGA2GAINB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_VGA2GAINA,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_VCM_RXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	Connect(ID_DECODE_RXVGA2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxVGA2::ParameterChangeHandler);
	//*)

	wndId2Enum[ID_DC_ADDR_RXVGA2] = DC_ADDR_RXVGA2;
    wndId2Enum[ID_DC_CNTVAL_RXVGA2] = DC_CNTVAL_RXVGA2;
    wndId2Enum[ID_DC_REGVAL_RXVGA2] = DC_REGVAL_RXVGA2;
    wndId2Enum[ID_DC_LOCK_RXVGA2] = DC_LOCK_RXVGA2;
    wndId2Enum[ID_DC_CLBR_DONE_RXVGA2] = DC_CLBR_DONE_RXVGA2;
    wndId2Enum[ID_DC_UD_RXVGA2] = DC_UD_RXVGA2;
    wndId2Enum[ID_EN_RXVGA2] = EN_RXVGA2;
    wndId2Enum[ID_PD_9] = PD_9;
    wndId2Enum[ID_PD_8] = PD_8;
    wndId2Enum[ID_PD_7] = PD_7;
    wndId2Enum[ID_PD_6] = PD_6;
    wndId2Enum[ID_PD_5] = PD_5;
    wndId2Enum[ID_PD_4] = PD_4;
    wndId2Enum[ID_PD_3] = PD_3;
    wndId2Enum[ID_PD_2] = PD_2;
    wndId2Enum[ID_PD_1] = PD_1;
    wndId2Enum[ID_PD_0] = PD_0;
    wndId2Enum[ID_VGA2GAIN_RXVGA2] = VGA2GAIN_RXVGA2;
    wndId2Enum[ID_VGA2GAINB] = VGA2GAINB;
    wndId2Enum[ID_VGA2GAINA] = VGA2GAINA;
    wndId2Enum[ID_VCM_RXVGA2] = VCM_RXVGA2;
    wndId2Enum[ID_DECODE_RXVGA2] = DECODE_RXVGA2;

    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<=30; i+=3)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVga2G_u->Set(temp);
    cmbVga2GB_t->Set(temp);
    cmbVga2GA_t->Set(temp);

    temp.clear();
    vector<cmbKeyValuePair> keyVals;
    for(int i=0; i<=7; ++i)
        keyVals.push_back( cmbKeyValuePair(i, wxString::Format("%.2f", 1.18-i*0.04)));
    for(int i=14; i>=8; --i)
        keyVals.push_back( cmbKeyValuePair(i, wxString::Format("%.2f", 0.62+(i-8)*0.04)));
    cmbVCM->Set(keyVals);

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbCalVal->Set(temp);

    temp.clear();
    temp.push_back(_("DC reference module"));
    temp.push_back(_("First gain stage, Q channel"));
    temp.push_back(_("First gain stage, I channel"));
    temp.push_back(_("Second gain stage, Q channel"));
    temp.push_back(_("Second gain stage, I channel"));
    cmbDCCalAddr->Set(temp);

    m_checkboxIDToInvert.insert(ID_PD_0);
    m_checkboxIDToInvert.insert(ID_PD_1);
    m_checkboxIDToInvert.insert(ID_PD_2);
    m_checkboxIDToInvert.insert(ID_PD_3);
    m_checkboxIDToInvert.insert(ID_PD_4);
    m_checkboxIDToInvert.insert(ID_PD_5);
    m_checkboxIDToInvert.insert(ID_PD_6);
    m_checkboxIDToInvert.insert(ID_PD_7);
    m_checkboxIDToInvert.insert(ID_PD_8);
    m_checkboxIDToInvert.insert(ID_PD_9);

    SetControlDisables();
}

pnlRxVGA2::~pnlRxVGA2()
{
	//(*Destroy(pnlRxVGA2)
	//*)
}


void pnlRxVGA2::OnbtnDCRstClbrClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCResetCalibration(RXVGA2);
}

void pnlRxVGA2::OnbtnDCLoadValClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCLoadValues(RXVGA2);
}

void pnlRxVGA2::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}

void pnlRxVGA2::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
}

void pnlRxVGA2::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrVGA2Mods->Enable(!enabled);
    chbPwrDCCurrR->Enable(enabled);
    chbPwrDCDACB->Enable(enabled);
    //chbPwrDCCmpB->Enable(enabled);
    chbPwrDCDACA->Enable(enabled);
    chbPwrDCDACA->Enable(enabled);
    //chbPwrDCCmpA->Enable(enabled);
    chbPwrBG->Enable(enabled);
    chbPwrBypAB->Enable(enabled);
    chbPwrBypB->Enable(enabled);
    chbPwrBypA->Enable(enabled);
    chbPwrCurrRef->Enable(enabled);
    cmbVga2GB_t->Enable(enabled);
    cmbVga2GA_t->Enable(enabled);
}

void pnlRxVGA2::OnbtnDCStartClbrClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DCStartCalibration(RXVGA2);
}

void pnlRxVGA2::OnbtnDCReadValClick(wxCommandEvent& event)
{
    lblDC_REGVAL->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_REGVAL_RXVGA2, true, true)));
    lblDC_LOCK->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_LOCK_RXVGA2, true, true)));
    lblDC_CLBR_DONE->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_CLBR_DONE_RXVGA2, true, true)));
    lblDC_UD->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_UD_RXVGA2, true, true)));
}
