#include "pnlTxLPF.h"
#include "Algorithms.h"
//(*InternalHeaders(pnlTxLPF)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlTxLPF)
const long pnlTxLPF::ID_BUTTON1 = wxNewId();
const long pnlTxLPF::ID_BUTTON2 = wxNewId();
const long pnlTxLPF::ID_BUTTON4 = wxNewId();
const long pnlTxLPF::ID_STATICTEXT1 = wxNewId();
const long pnlTxLPF::ID_STATICTEXT2 = wxNewId();
const long pnlTxLPF::ID_STATICLINE1 = wxNewId();
const long pnlTxLPF::ID_DC_ADDR = wxNewId();
const long pnlTxLPF::ID_DC_CNTVAL = wxNewId();
const long pnlTxLPF::ID_BUTTON5 = wxNewId();
const long pnlTxLPF::ID_STATICTEXT3 = wxNewId();
const long pnlTxLPF::ID_DC_REGVAL = wxNewId();
const long pnlTxLPF::ID_STATICTEXT4 = wxNewId();
const long pnlTxLPF::ID_DC_LOCK = wxNewId();
const long pnlTxLPF::ID_STATICTEXT5 = wxNewId();
const long pnlTxLPF::ID_DC_CLBR_DONE = wxNewId();
const long pnlTxLPF::ID_STATICTEXT6 = wxNewId();
const long pnlTxLPF::ID_DC_UD = wxNewId();
const long pnlTxLPF::ID_EN = wxNewId();
const long pnlTxLPF::ID_PD_FIL_LPF = wxNewId();
const long pnlTxLPF::ID_PD_DCODAC_LPF = wxNewId();
const long pnlTxLPF::ID_PD_DCOREF_LPF = wxNewId();
const long pnlTxLPF::ID_PD_DCOCMP_LPF = wxNewId();
const long pnlTxLPF::ID_TX_DACBUF_PD = wxNewId();
const long pnlTxLPF::ID_LPFBW = wxNewId();
const long pnlTxLPF::ID_BYP_EN_LPF = wxNewId();
const long pnlTxLPF::ID_STATICTEXT11 = wxNewId();
const long pnlTxLPF::ID_STATICTEXT12 = wxNewId();
const long pnlTxLPF::ID_DCO_DACCAL = wxNewId();
const long pnlTxLPF::ID_RCCAL_LPF = wxNewId();
const long pnlTxLPF::ID_DECODE = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTxLPF,wxPanel)
	//(*EventTable(pnlTxLPF)
	//*)
END_EVENT_TABLE()

pnlTxLPF::pnlTxLPF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    m_Rx = false;
	BuildContent(parent,id,pos,size);
}

void pnlTxLPF::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTxLPF)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Calibration"));
	FlexGridSizer4 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 5);
	btnDCRstClbr = new wxButton(this, ID_BUTTON1, _("Reset Calibration"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer5->Add(btnDCRstClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCLoadVal = new wxButton(this, ID_BUTTON2, _("Load Cnt Value"), wxPoint(136,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer5->Add(btnDCLoadVal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCStartClbr = new wxButton(this, ID_BUTTON4, _("Start Calibration"), wxPoint(256,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer5->Add(btnDCStartClbr, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("CAL ModuleAddress:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Calibration Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer5->Add(StaticText2, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine1->Hide();
	FlexGridSizer5->Add(StaticLine1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCCalAddr = new ComboBoxMap(this, ID_DC_ADDR, wxEmptyString, wxPoint(8,56), wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DC_ADDR"));
	FlexGridSizer5->Add(cmbDCCalAddr, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbCalVal = new ComboBoxMap(this, ID_DC_CNTVAL, wxEmptyString, wxPoint(136,56), wxSize(100,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DC_CNTVAL"));
	FlexGridSizer5->Add(cmbCalVal, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDCReadVal = new wxButton(this, ID_BUTTON5, _("Read Values"), wxDefaultPosition, wxSize(96,-1), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer5->Add(btnDCReadVal, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Calibration Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_REGVAL = new wxStaticText(this, ID_DC_REGVAL, _("\?\?\?"), wxDefaultPosition, wxSize(78,13), 0, _T("ID_DC_REGVAL"));
	FlexGridSizer6->Add(lblDC_REGVAL, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Lock Pattern:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_LOCK = new wxStaticText(this, ID_DC_LOCK, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_LOCK"));
	FlexGridSizer6->Add(lblDC_LOCK, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Calibration Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_CLBR_DONE = new wxStaticText(this, ID_DC_CLBR_DONE, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_CLBR_DONE"));
	FlexGridSizer6->Add(lblDC_CLBR_DONE, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Comparator Value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer6->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
	lblDC_UD = new wxStaticText(this, ID_DC_UD, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DC_UD"));
	FlexGridSizer6->Add(lblDC_UD, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 5, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Power Control"));
	chbPwrLpfMods = new wxCheckBox(this, ID_EN, _("LPF Modules Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN"));
	chbPwrLpfMods->SetValue(false);
	StaticBoxSizer2->Add(chbPwrLpfMods, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrLpf = new wxCheckBox(this, ID_PD_FIL_LPF, _("LPF Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FIL_LPF"));
	chbPwrLpf->SetValue(false);
	StaticBoxSizer2->Add(chbPwrLpf, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCDac = new wxCheckBox(this, ID_PD_DCODAC_LPF, _("DC Offset DAC Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_DCODAC_LPF"));
	chbPwrDCDac->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCDac, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCRef = new wxCheckBox(this, ID_PD_DCOREF_LPF, _("dc_ref_con3 Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_DCOREF_LPF"));
	chbPwrDCRef->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCRef, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbPwrDCCmpr = new wxCheckBox(this, ID_PD_DCOCMP_LPF, _("DC Offset Comparator Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_DCOCMP_LPF"));
	chbPwrDCCmpr->SetValue(false);
	StaticBoxSizer2->Add(chbPwrDCCmpr, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chbTX_DACBUF_EN = new wxCheckBox(this, ID_TX_DACBUF_PD, _("DAC Buffer Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TX_DACBUF_PD"));
	chbTX_DACBUF_EN->SetValue(false);
	StaticBoxSizer2->Add(chbTX_DACBUF_EN, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 5, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LPF Bandwidth"));
	cmbLpfBw = new ComboBoxMap(this, ID_LPFBW, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LPFBW"));
	StaticBoxSizer3->Add(cmbLpfBw, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer1->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("Normal Operation"),
		_("Bypass LPF")
	};
	rgrLpfByp = new wxRadioBox(this, ID_BYP_EN_LPF, _("Test"), wxPoint(344,120), wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_BYP_EN_LPF"));
	BoxSizer1->Add(rgrLpfByp, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(BoxSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Process Calibration Values"));
	FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT11, _("DC Offset Resistor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer1->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT12, _("From TRX_LPF_CAL:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer1->Add(StaticText8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDCOffset = new ComboBoxMap(this, ID_DCO_DACCAL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCO_DACCAL"));
	FlexGridSizer1->Add(cmbDCOffset, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbRcCal = new ComboBoxMap(this, ID_RCCAL_LPF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RCCAL_LPF"));
	FlexGridSizer1->Add(cmbRcCal, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Decode Signals"),
		_("Direct Signals")
	};
	rgrDecode = new wxRadioBox(this, ID_DECODE, _("Decoding"), wxPoint(720,8), wxSize(136,69), 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DECODE"));
	FlexGridSizer2->Add(rgrDecode, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(this);
	FlexGridSizer2->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxLPF::OnbtnDCRstClbrClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxLPF::OnbtnDCLoadValClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxLPF::OnbtnDCStartClbrClick);
	Connect(ID_DC_ADDR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_DC_CNTVAL,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxLPF::OnbtnDCReadValClick);
	Connect(ID_EN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_PD_FIL_LPF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_PD_DCODAC_LPF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_PD_DCOREF_LPF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_PD_DCOCMP_LPF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_TX_DACBUF_PD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_LPFBW,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_BYP_EN_LPF,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_DCO_DACCAL,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_RCCAL_LPF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	Connect(ID_DECODE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxLPF::ParameterChangeHandler);
	//*)

	m_checkboxIDToInvert.insert(ID_TX_DACBUF_PD);
	m_checkboxIDToInvert.insert(ID_PD_DCOCMP_LPF);
	m_checkboxIDToInvert.insert(ID_PD_DCODAC_LPF);
	m_checkboxIDToInvert.insert(ID_PD_DCOREF_LPF);
	m_checkboxIDToInvert.insert(ID_PD_FIL_LPF);


    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbCalVal->Set(temp);
    cmbDCOffset->Set(temp);

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbRcCal->Set(temp);

    temp.clear();
    temp.push_back(_("I filter"));
    temp.push_back(_("Q filter"));
    cmbDCCalAddr->Set(temp);

    temp.clear();
    temp.push_back( "14 MHz");
    temp.push_back( "10 MHz");
    temp.push_back( "7 MHz");
    temp.push_back( "6 MHz");
    temp.push_back( "5 MHz");
    temp.push_back( "4.375 MHz");
    temp.push_back( "3.5 MHz");
    temp.push_back( "3 MHz");
    temp.push_back( "2.75 MHz");
    temp.push_back( "2.5 MHz");
    temp.push_back( "1.92 MHz");
    temp.push_back( "1.5 MHz");
    temp.push_back( "1.375 MHz");
    temp.push_back( "1.25 MHz");
    temp.push_back( "0.875 MHz");
    temp.push_back( "0.75 MHz");
    cmbLpfBw->Set(temp);

    SetControlDisables();
}

pnlTxLPF::~pnlTxLPF()
{
	//(*Destroy(pnlTxLPF)
	//*)
}

void pnlTxLPF::SetType(const bool Rx)
{
    m_Rx = Rx;
    if(m_Rx)
    {
        chbTX_DACBUF_EN->Show(false);
        wndId2Enum[ID_DC_ADDR] = DC_ADDR_RXLPF;
        wndId2Enum[ID_DC_CNTVAL] = DC_CNTVAL_RXLPF;
        wndId2Enum[ID_DC_REGVAL] = DC_REGVAL_RXLPF;
        wndId2Enum[ID_DC_LOCK] = DC_LOCK_RXLPF;
        wndId2Enum[ID_DC_CLBR_DONE] = DC_CLBR_DONE_RXLPF;
        wndId2Enum[ID_DC_UD] = DC_UD_RXLPF;
        wndId2Enum[ID_EN] = EN_RXLPF;
        wndId2Enum[ID_PD_FIL_LPF] = PD_FIL_LPF_RXLPF;
        wndId2Enum[ID_PD_DCODAC_LPF] = PD_DCODAC_LPF_RXLPF;
        wndId2Enum[ID_PD_DCOREF_LPF] = PD_DCOREF_LPF_RXLPF;
        wndId2Enum[ID_PD_DCOCMP_LPF] = PD_DCOCMP_LPF_RXLPF;
        wndId2Enum[ID_LPFBW] = BWC_LPF_RXLPF;
        wndId2Enum[ID_BYP_EN_LPF] = BYP_EN_LPF_RXLPF;
        wndId2Enum[ID_DCO_DACCAL] = DCO_DACCAL_RXLPF;
        wndId2Enum[ID_RCCAL_LPF] = RCCAL_LPF_RXLPF;
        wndId2Enum[ID_DECODE] = DECODE_RXLPF;
    }
    else
    {
        wndId2Enum[ID_DC_ADDR] = DC_ADDR_TXLPF;
        wndId2Enum[ID_DC_CNTVAL] = DC_CNTVAL_TXLPF;
        wndId2Enum[ID_DC_REGVAL] = DC_REGVAL_TXLPF;
        wndId2Enum[ID_DC_LOCK] = DC_LOCK_TXLPF;
        wndId2Enum[ID_DC_CLBR_DONE] = DC_CLBR_DONE_TXLPF;
        wndId2Enum[ID_DC_UD] = DC_UD_TXLPF;
        wndId2Enum[ID_EN] = EN_TXLPF;
        wndId2Enum[ID_PD_FIL_LPF] = PD_FIL_LPF_TXLPF;
        wndId2Enum[ID_PD_DCODAC_LPF] = PD_DCODAC_LPF_TXLPF;
        wndId2Enum[ID_PD_DCOREF_LPF] = PD_DCOREF_LPF_TXLPF;
        wndId2Enum[ID_PD_DCOCMP_LPF] = PD_DCOCMP_LPF_TXLPF;
        wndId2Enum[ID_TX_DACBUF_PD] = TX_DACBUF_PD_TXLPF;
        wndId2Enum[ID_LPFBW] = BWC_LPF_TXLPF;
        wndId2Enum[ID_BYP_EN_LPF] = BYP_EN_LPF_TXLPF;
        wndId2Enum[ID_DCO_DACCAL] = DCO_DACCAL_TXLPF;
        wndId2Enum[ID_RCCAL_LPF] = RCCAL_LPF_TXLPF;
        wndId2Enum[ID_DECODE] = DECODE_TXLPF;
    }
}

void pnlTxLPF::OnbtnDCLoadValClick(wxCommandEvent& event)
{
    if(m_Rx)
        lmsControl->algorithms->DCLoadValues(RXLPF);
    else
        lmsControl->algorithms->DCLoadValues(TXLPF);
}

void pnlTxLPF::UpdateGUI()
{
    GUIPanel::UpdateGUI();
    SetControlDisables();
}

void pnlTxLPF::SetControlDisables()
{
    //disable controls
    bool enabled = rgrDecode->GetSelection() == 1;
    chbPwrLpfMods->Enable(!enabled);
    chbPwrLpf->Enable(enabled);
    chbPwrDCDac->Enable(enabled);
    chbPwrDCRef->Enable(enabled);
    //chbPwrDCCmpr->Enable(enabled);
    chbTX_DACBUF_EN->Enable(enabled);
}

void pnlTxLPF::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    SetControlDisables();
}

void pnlTxLPF::OnbtnDCRstClbrClick(wxCommandEvent& event)
{
    if(m_Rx)
        lmsControl->algorithms->DCResetCalibration(RXLPF);
    else
        lmsControl->algorithms->DCResetCalibration(TXLPF);
}

void pnlTxLPF::OnbtnDCStartClbrClick(wxCommandEvent& event)
{
    if(m_Rx)
        lmsControl->algorithms->DCStartCalibration(RXLPF);
    else
        lmsControl->algorithms->DCStartCalibration(TXLPF);
}

void pnlTxLPF::OnbtnDCReadValClick(wxCommandEvent& event)
{
    if(m_Rx)
    {
        lblDC_REGVAL->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_REGVAL_RXLPF, true, true)));
        lblDC_LOCK->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_LOCK_RXLPF, true, true)));
        lblDC_CLBR_DONE->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_CLBR_DONE_RXLPF, true, true)));
        lblDC_UD->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_UD_RXLPF, true, true)));
    }
    else
    {
        lblDC_REGVAL->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_REGVAL_TXLPF, true, true)));
        lblDC_LOCK->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_LOCK_TXLPF, true, true)));
        lblDC_CLBR_DONE->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_CLBR_DONE_TXLPF, true, true)));
        lblDC_UD->SetLabel( wxString::Format("%li", lmsControl->GetParam(DC_UD_TXLPF, true, true)));
    }
}
