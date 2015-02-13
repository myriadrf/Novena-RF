#include "pnlSystem.h"
#include "CompoundOperations.h"
#include "MessageLog.h"
#include "ComboBoxMap.h"
#include "Algorithms.h"
//(*InternalHeaders(pnlSystem)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(pnlSystem)
const long pnlSystem::ID_STATICTEXT1 = wxNewId();
const long pnlSystem::ID_LNASEL_RXFE = wxNewId();
const long pnlSystem::ID_BUTTON4 = wxNewId();
const long pnlSystem::ID_BUTTON5 = wxNewId();
const long pnlSystem::ID_BUTTON6 = wxNewId();
const long pnlSystem::ID_STATICTEXT6 = wxNewId();
const long pnlSystem::ID_STATICTEXT7 = wxNewId();
const long pnlSystem::ID_STATICTEXT8 = wxNewId();
const long pnlSystem::ID_COMBOBOX4 = wxNewId();
const long pnlSystem::ID_COMBOBOX9 = wxNewId();
const long pnlSystem::ID_COMBOBOX6 = wxNewId();
const long pnlSystem::ID_STATICTEXT9 = wxNewId();
const long pnlSystem::ID_STATICTEXT10 = wxNewId();
const long pnlSystem::ID_STATICTEXT11 = wxNewId();
const long pnlSystem::ID_STATICTEXT12 = wxNewId();
const long pnlSystem::ID_COMBOBOX7 = wxNewId();
const long pnlSystem::ID_COMBOBOX8 = wxNewId();
const long pnlSystem::ID_BUTTON7 = wxNewId();
const long pnlSystem::ID_BUTTON8 = wxNewId();
const long pnlSystem::ID_BUTTON9 = wxNewId();
const long pnlSystem::ID_TEXTCTRL2 = wxNewId();
const long pnlSystem::ID_STATICTEXT2 = wxNewId();
const long pnlSystem::ID_STATICTEXT3 = wxNewId();
const long pnlSystem::ID_STATICTEXT4 = wxNewId();
const long pnlSystem::ID_STATICTEXT5 = wxNewId();
const long pnlSystem::ID_COMBOBOX1 = wxNewId();
const long pnlSystem::ID_COMBOBOX2 = wxNewId();
const long pnlSystem::ID_BUTTON1 = wxNewId();
const long pnlSystem::ID_BUTTON2 = wxNewId();
const long pnlSystem::ID_BUTTON3 = wxNewId();
const long pnlSystem::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSystem,wxPanel)
    //(*EventTable(pnlSystem)
    //*)
END_EVENT_TABLE()

pnlSystem::pnlSystem(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    BuildContent(parent,id,pos,size);
}

void pnlSystem::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(pnlSystem)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxFlexGridSizer* FlexGridSizer8;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("LNA Control"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT1, _("Active LNA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer8->Add(StaticText5, 1, wxTOP|wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbLNASEL_Cust = new ComboBoxMap(this, ID_LNASEL_RXFE, wxEmptyString, wxDefaultPosition, wxSize(76,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LNASEL_RXFE"));
    FlexGridSizer8->Add(cmbLNASEL_Cust, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Automatic Calibration"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 5);
    btnClbrTx = new wxButton(this, ID_BUTTON4, _("Transmitter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer2->Add(btnClbrTx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnClbrRx = new wxButton(this, ID_BUTTON5, _("Receiver"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer2->Add(btnClbrRx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnCalLPFCore = new wxButton(this, ID_BUTTON6, _("LPF Core"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    FlexGridSizer2->Add(btnCalLPFCore, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bypass Congiurations"));
    FlexGridSizer3 = new wxFlexGridSizer(2, 3, 0, 5);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Rx Bypass Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer3->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Tx Bypass Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer3->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("RF / BB Loopback Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer3->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbBypass = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
    cmbBypass->SetSelection( cmbBypass->Append(_("Normal Operation")) );
    cmbBypass->Append(_("Bypass RxLPF"));
    cmbBypass->Append(_("Bypass RxLPF, RxVGA2"));
    FlexGridSizer3->Add(cmbBypass, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbTxBypass = new wxComboBox(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
    cmbTxBypass->SetSelection( cmbTxBypass->Append(_("Normal Operation")) );
    cmbTxBypass->Append(_("Bypass LPF"));
    FlexGridSizer3->Add(cmbTxBypass, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbLoopback = new wxComboBox(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
    cmbLoopback->SetSelection( cmbLoopback->Append(_("Normal Operation")) );
    cmbLoopback->Append(_("BB loopback to RxLPF Input"));
    cmbLoopback->Append(_("BB loopback to RxVGA2 Input"));
    cmbLoopback->Append(_("BB loopback to Output Pins"));
    cmbLoopback->Append(_("RF loopback LNA1"));
    cmbLoopback->Append(_("RF loopback LNA2"));
    cmbLoopback->Append(_("RF loopback LNA3"));
    FlexGridSizer3->Add(cmbLoopback, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Downlink (Tx) Frequency Band and Channel"));
    FlexGridSizer4 = new wxFlexGridSizer(2, 4, 0, 5);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Band:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer4->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer4->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Fast Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer4->Add(StaticText11, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Frequency, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer4->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbDLTXBands = new ComboBoxMap(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
    FlexGridSizer4->Add(cmbDLTXBands, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbDLTXChan = new ComboBoxMap(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(76,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
    FlexGridSizer4->Add(cmbDLTXChan, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    btnDLTXFChan_B = new wxButton(this, ID_BUTTON7, _("B"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer2->Add(btnDLTXFChan_B, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDLTXFChan_M = new wxButton(this, ID_BUTTON8, _("M"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer2->Add(btnDLTXFChan_M, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDLTXFChan_T = new wxButton(this, ID_BUTTON9, _("T"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer2->Add(btnDLTXFChan_T, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtDLTXFreq = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(96,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer4->Add(txtDLTXFreq, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Uplink (Rx) Frequency Band and Channel"));
    FlexGridSizer1 = new wxFlexGridSizer(2, 4, 0, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Band:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Fast Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Frequency, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbULRXBands = new ComboBoxMap(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    FlexGridSizer1->Add(cmbULRXBands, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbULRXChan = new ComboBoxMap(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(76,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    FlexGridSizer1->Add(cmbULRXChan, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    btnULRXFChan_B = new wxButton(this, ID_BUTTON1, _("B"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(btnULRXFChan_B, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnULRXFChan_M = new wxButton(this, ID_BUTTON2, _("M"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer1->Add(btnULRXFChan_M, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnULRXFChan_T = new wxButton(this, ID_BUTTON3, _("T"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer1->Add(btnULRXFChan_T, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtULRXFreq = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(96,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(txtULRXFreq, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(this);
    FlexGridSizer5->SetSizeHints(this);

    Connect(ID_LNASEL_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::ParameterChangeHandler);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnClbrTxClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnClbrRxClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnCalLPFCoreClick);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbRxBypassSelected);
    Connect(ID_COMBOBOX9,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbTxBypassSelected);
    Connect(ID_COMBOBOX6,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbLoopbackSelected);
    Connect(ID_COMBOBOX7,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbDLTXBandsSelected);
    Connect(ID_COMBOBOX8,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbDLTXChanSelected);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnDLTXFChan_BClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnDLTXFChan_MClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnDLTXFChan_TClick);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbULRXBandsSelected);
    Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSystem::OncmbULRXChanSelected);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnULRXFChan_BClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnULRXFChan_MClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSystem::OnbtnULRXFChan_TClick);
    //*)
    wndId2Enum[ID_LNASEL_RXFE] = LNASEL_RXFE;

    wxArrayString temp;
    temp.push_back(_("Disabled"));
    temp.push_back(_("LNA 1"));
    temp.push_back(_("LNA 2"));
    temp.push_back(_("LNA 3"));
    cmbLNASEL_Cust->Set(temp);

    fillBands(false);
    fillBands(true);
    fillChannels(false);
    fillChannels(true);
}

pnlSystem::~pnlSystem()
{
    //(*Destroy(pnlSystem)
    //*)
}


void pnlSystem::OnbtnClbrTxClick(wxCommandEvent& event)
{
    lmsControl->algorithms->CalibrateTx();
}

void pnlSystem::OnbtnClbrRxClick(wxCommandEvent& event)
{
    lmsControl->algorithms->CalibrateRx();
}

void pnlSystem::OnbtnCalLPFCoreClick(wxCommandEvent& event)
{
    lmsControl->algorithms->CalibrateLPFCore();
}

void pnlSystem::OnbtnDLTXFChan_BClick(wxCommandEvent& event)
{
    cmbDLTXChan->SetSelectionByIndex(0);
    OncmbDLTXChanSelected(event);
}

void pnlSystem::OnbtnDLTXFChan_MClick(wxCommandEvent& event)
{
    int index = (cmbDLTXChan->GetCount()-1)/2;
    cmbDLTXChan->SetSelectionByIndex(index);
    OncmbDLTXChanSelected(event);
}

void pnlSystem::OnbtnDLTXFChan_TClick(wxCommandEvent& event)
{
    int index = cmbDLTXChan->GetCount()-1;
    cmbDLTXChan->SetSelectionByIndex(index);
    OncmbDLTXChanSelected(event);
}

void pnlSystem::OnbtnULRXFChan_BClick(wxCommandEvent& event)
{
    cmbULRXChan->SetSelectionByIndex(0);
    OncmbULRXChanSelected(event);
}

void pnlSystem::OnbtnULRXFChan_MClick(wxCommandEvent& event)
{
    int index = (cmbULRXChan->GetCount()-1)/2;
    cmbULRXChan->SetSelectionByIndex(index);
    OncmbULRXChanSelected(event);
}

void pnlSystem::OnbtnULRXFChan_TClick(wxCommandEvent& event)
{
    int index = cmbULRXChan->GetCount()-1;
    cmbULRXChan->SetSelectionByIndex(index);
    OncmbULRXChanSelected(event);
}

void pnlSystem::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
    if(wndId2Enum[event.GetId()] == LNASEL_RXFE)
    {//when changing LNA, for convenience change output buffer
        lmsControl->SetParam(SELOUT_RXPLL, event.GetInt());
    }
}

void pnlSystem::OncmbRxBypassSelected(wxCommandEvent& event)
{
    SetBypassLoopback();
}

void pnlSystem::OncmbLoopbackSelected(wxCommandEvent& event)
{
    SetBypassLoopback();
}

void pnlSystem::OncmbTxBypassSelected(wxCommandEvent& event)
{
    switch(cmbTxBypass->GetSelection())
    {
    //Turn off all Bypass Modes
    case 0:
        //m_frmTxLpf->CustSet_BypassLpfOFF();
        lmsControl->SetParam(DECODE_TXLPF, 0);
        lmsControl->SetParam(EN_TXLPF, 1);
        lmsControl->SetParam(BYP_EN_LPF_TXLPF, 0);
        break;
    case 1:
        //Turn on required bypass mode
        //m_frmTxLpf->CustSet_BypassLpfON();
        lmsControl->SetParam(DECODE_TXLPF, 0);
        lmsControl->SetParam(EN_TXLPF, 0);
        lmsControl->SetParam(BYP_EN_LPF_TXLPF, 1);
        break;
    };
}

void pnlSystem::SetBypassLoopback()
{
    CompoundOperations ops(lmsControl);
    int iBB = cmbBypass->GetSelection();
    int iLB = cmbLoopback->GetSelection();

    //Turn Off all bypass modes
    //EnableAllSPIClocks();
        //m_frmTop->CustSet_Tia2OutOFF();
    lmsControl->SetParam(BBBYP, false);
        //m_frmRxLpf->CustSet_BypassLpfOFF();
    lmsControl->SetParam(DECODE_RXLPF, 0);
    lmsControl->SetParam(EN_RXLPF, 0);
    ops.CustSet_RxVGA2PowerON();
    //RestoreAllSPIClocks();

    //Turn Off all loopback modes
    //EnableAllSPIClocks();
        //m_frmCustomer->cmbLNASEL_Cust->ItemIndex = 1;
    lmsControl->SetParam(LNASEL_RXFE, 1);
    cmbLNASEL_Cust->SetSelection(1);
    ops.SetLnaChain(cmbLNASEL_Cust->GetSelection());

    //m_frmTop->CustSet_SetRFLB(0);
    lmsControl->SetParam(LBRFEN, 0);
    ops.CustSet_SetBBLB(0);
    ops.CustSet_LNAPowerON();
    ops.CustSet_RxFePowerON();
    ops.CustSet_RxLpfPowerON();
    ops.CustSet_RxVGA2PowerON();
    //RestoreAllSPIClocks();

    //RxLPF Bypass, LBEN_LPFIN ON
    if((iLB == 0x01) && (iBB == 0x01))
    {
        //EnableAllSPIClocks();
        ops.CustSet_BypassRxLpfON();  //Turns Bypas RxLPF switch ON, powers down LPF
        ops.CustSet_RxFePowerOFF();      //Powers down TIA, RxMIX, RxLNA
        ops.CustSet_SetBBLB(1);
        ops.CustSet_SetBBLB(1);
        //RestoreAllSPIClocks();
        return;
    };

    //RxVGA2 and RxLPF Bypass, LBEN_LPFIN ON
    if((iLB == 0x01) && (iBB == 0x02))
    {
        //EnableAllSPIClocks();
        ops.CustSet_RxFePowerOFF();          //Powers down TIA, RxMIX, RxLNA
        ops.CustSet_RxVGA2PowerOFF();  //Powers down RxVGA2
        ops.CustSet_RxLpfPowerOFF();      //Powers down RxLPF
        //m_frmTop->CustSet_Tia2OutON();
        lmsControl->SetParam(BBBYP, true);
        ops.CustSet_SetBBLB(1);
        //RestoreAllSPIClocks();
        return;
    };

    //Illegal combination
    if(  ((iLB == 0x02) || (iLB == 0x03)) && ((iBB == 0x01) || (iBB == 0x02))  )
    {
        MessageLog::getInstance()->write("Illegal Baseband Bypass and Baseband Loopback mode.\n", LOG_ERROR);
        return;
    };


    //
    switch(iBB)
    {
    //Bypass RxLPF:
    //1. Power Down RxLPF;
    //2. Select Bypass Mode.
    case 1:
        //Turn on required bypass mode
        //EnableAllSPIClocks();
        ops.CustSet_BypassRxLpfON();
        //RestoreAllSPIClocks();
        break;

    //Bypass RxLPF, RxVGA2:
    //1. Power Down RxLPF;
    //2. Power Down RxVGA2;
    //3. Select RxTIA Connected to Output Pins
    case 2:
        //Turn on required bypass mode
        //EnableAllSPIClocks();
        ops.CustSet_RxVGA2PowerOFF();
        ops.CustSet_RxLpfPowerOFF();
        //m_frmTop->CustSet_Tia2OutON();
        lmsControl->SetParam(BBBYP, true);
        //RestoreAllSPIClocks();
        break;
    };


    //
    switch(iLB)
    {
    //To RxLPF input
    case 1:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        ops.CustSet_RxFePowerOFF();
        ops.CustSet_RxLpfPowerON();
        ops.CustSet_RxVGA2PowerON();
        ops.CustSet_SetBBLB(1);
        //RestoreAllSPIClocks();
        break;

    //To RxVGA2 input
    case 2:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        ops.CustSet_RxFePowerOFF();
        ops.CustSet_RxLpfPowerOFF();
        ops.CustSet_RxVGA2PowerON();
        ops.CustSet_SetBBLB(2);
        //RestoreAllSPIClocks();
        break;

    //To output pins
    case 3:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        ops.CustSet_RxFePowerOFF();
        ops.CustSet_RxLpfPowerOFF();
        ops.CustSet_RxVGA2PowerOFF();
        ops.CustSet_SetBBLB(3);
        //RestoreAllSPIClocks();
        break;

    //
    case 4:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        cmbLNASEL_Cust->SetSelection(1);
        ops.SetLnaChain(cmbLNASEL_Cust->GetSelection());
        ops.CustSet_LNAPowerOFF();
        //m_frmTop->CustSet_SetRFLB(1);
        lmsControl->SetParam(LBRFEN, 1);
        //RestoreAllSPIClocks();
        break;

    case 5:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        cmbLNASEL_Cust->SetSelection(2);
        ops.SetLnaChain(cmbLNASEL_Cust->GetSelection());
        ops.CustSet_LNAPowerOFF();
        //m_frmTop->CustSet_SetRFLB(2);
        lmsControl->SetParam(LBRFEN, 2);
        //RestoreAllSPIClocks();
        break;

    case 6:
        //Turn off other bypass

        //Turn on required bypass mode
        //EnableAllSPIClocks();
        cmbLNASEL_Cust->SetSelection(3);
        ops.SetLnaChain(cmbLNASEL_Cust->GetSelection());
        ops.CustSet_LNAPowerOFF();
        //m_frmTop->CustSet_SetRFLB(3);
        lmsControl->SetParam(LBRFEN, 3);
        //RestoreAllSPIClocks();
        break;
    };


};

void pnlSystem::fillChannels(bool ULRX)
{
    int BandInd;
	int iChFreq;
	int iTmp;
	double *dFul_low;
	double *dFul_high;
	double *dFul_offset;

	ComboBoxMap *Bands;
	ComboBoxMap *Chans;
	if (ULRX)
	{
		Bands = cmbULRXBands;
		Chans = cmbULRXChan;
		dFul_low = bandsConf.m_sRxUARFCNDef.dFul_low;
		dFul_high = bandsConf.m_sRxUARFCNDef.dFul_high;
		dFul_offset = bandsConf.m_sRxUARFCNDef.dFul_offset;
	}
	else
	{
		Bands = cmbDLTXBands;
		Chans = cmbDLTXChan;
		dFul_low = bandsConf.m_sTxUARFCNDef.dFul_low;
		dFul_high = bandsConf.m_sTxUARFCNDef.dFul_high;
		dFul_offset = bandsConf.m_sTxUARFCNDef.dFul_offset;
	};

	if ((Bands == NULL) || (Chans == NULL))
		return;

	BandInd = Bands->GetSelection();
	if (BandInd < 0)
		return;
	Chans->Clear();

	iChFreq = dFul_low[BandInd];
	vector< cmbKeyValuePair > keymap;
	while (iChFreq <= dFul_high[BandInd])
	{
		iTmp = 5 * (iChFreq - dFul_offset[BandInd]);
		iTmp = iTmp / 10;
		keymap.push_back( cmbKeyValuePair(iTmp, wxString::Format("%i",iTmp)));
		iChFreq += 2;
	};
    Chans->Set(keymap);
    if(keymap.size() > 0)
        Chans->SetSelection(keymap[0].first);
}

void pnlSystem::fillBands(bool ULRX)
{
    ComboBoxMap *Bands;
    if(ULRX)
        Bands = cmbULRXBands;
    else
        Bands = cmbDLTXBands;
    vector< cmbKeyValuePair > keymap;
    for(int i=0; i<BandN; ++i)
    {
        if(bandsConf.m_bBandEnable[i])
        {
            keymap.push_back( cmbKeyValuePair(i, wxString::Format("%s",bandsConf.m_sBands[i])));
        }
    }
    Bands->Set(keymap);
    if(keymap.size() > 0)
        Bands->SetSelection(keymap[0].first);
}

void pnlSystem::OncmbDLTXBandsSelected(wxCommandEvent& event)
{
    fillChannels(false);
    OncmbDLTXChanSelected(event);
}

void pnlSystem::OncmbDLTXChanSelected(wxCommandEvent& event)
{
    float freqMHz = (2*cmbDLTXChan->GetSelection() + bandsConf.m_sTxUARFCNDef.dFul_offset[cmbDLTXBands->GetSelection()])/10;
    txtDLTXFreq->SetValue(wxString::Format("%f", freqMHz/1000));
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;
    lmsControl->SetFrequency(false, freqMHz, realFreq, Nint, Nfrac, iVco, fVco, divider);
    lmsControl->Tune(false);
}

void pnlSystem::OncmbULRXBandsSelected(wxCommandEvent& event)
{
    fillChannels(true);
    OncmbULRXChanSelected(event);
}

void pnlSystem::OncmbULRXChanSelected(wxCommandEvent& event)
{
    float freqMHz = (2*cmbULRXChan->GetSelection() + bandsConf.m_sRxUARFCNDef.dFul_offset[cmbULRXBands->GetSelection()])/10;
    txtULRXFreq->SetValue(wxString::Format("%f", freqMHz/1000));
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;
    lmsControl->SetFrequency(true, freqMHz, realFreq, Nint, Nfrac, iVco, fVco, divider);
    lmsControl->Tune(true);
}
