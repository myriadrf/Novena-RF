/***************************************************************
 * Name:      LMS6002_GUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-04-14
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#include "LMS6002_GUI_Main.h"
#include <wx/msgdlg.h>
#include <wx/time.h>

#include "pnlADDC.h"
#include "pnlRxFE.h"
#include "pnlRxVGA2.h"
#include "pnlSystem.h"
#include "pnlTop.h"
#include "pnlTxLPF.h"
#include "pnlTxPLL.h"
#include "pnlTxRF.h"

#include "pnlSPI.h"
#include "dlgFloatInput.h"
#include "dlgRegisterTest.h"
#include "dlgConnectionSettings.h"
#include "dlgAbout.h"

#include "LMS6002_MainControl.h"
#include "MessageLog.h"
//(*InternalHeaders(LMS6002_GUI_Main)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/panel.h>

using namespace lms6;

//(*IdInit(LMS6002_GUI_Main)
const long LMS6002_GUI_Main::ID_BUTTON2 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON3 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON4 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON5 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON6 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON7 = wxNewId();
const long LMS6002_GUI_Main::ID_SYSTEM_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_TOP_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_TXPLL_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_RXPLL_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_TXLPF_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_TXRF_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_RXLPF_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_RXVGA2_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_RXFE_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_ADDC_TAB = wxNewId();
const long LMS6002_GUI_Main::ID_LMS6_TABS = wxNewId();
const long LMS6002_GUI_Main::ID_TEXTCTRL1 = wxNewId();
const long LMS6002_GUI_Main::ID_BUTTON1 = wxNewId();
const long LMS6002_GUI_Main::ID_STATICTEXT1 = wxNewId();
const long LMS6002_GUI_Main::ID_STATICTEXT3 = wxNewId();
const long LMS6002_GUI_Main::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LMS6002_GUI_Main,wxPanel)
    //(*EventTable(LMS6002_GUI_Main)
    //*)
END_EVENT_TABLE()

const wxString cDisconnectedStatusVerRevMask = _("Ver:   Rev:   Mask:  ");

LMS6002_GUI_Main::LMS6002_GUI_Main(wxWindow* parent,wxWindowID id, LMS6002_MainControl* plmsControl):
    PluginPanel(this)
{
    m_logger = new dlgLogger(this);
    wxLongLong t1 = wxGetUTCTimeMillis();
    wxLongLong t2 = wxGetUTCTimeMillis();
    //(*Initialize(LMS6002_GUI_Main)
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    btnOpen = new wxButton(this, ID_BUTTON2, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer1->Add(btnOpen, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnSave = new wxButton(this, ID_BUTTON3, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer1->Add(btnSave, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Chip2GUI = new wxButton(this, ID_BUTTON4, _("Chip->GUI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer1->Add(Chip2GUI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GUI2Chip = new wxButton(this, ID_BUTTON5, _("GUI->Chip"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer1->Add(GUI2Chip, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRegisters = new wxButton(this, ID_BUTTON6, _("Registers Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer1->Add(btnRegisters, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRefClk = new wxButton(this, ID_BUTTON7, _("Reference Clk..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer1->Add(btnRefClk, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxBOTTOM|wxALIGN_LEFT|wxALIGN_TOP, 5);
    pcSPIS = new wxNotebook(this, ID_LMS6_TABS, wxDefaultPosition, wxDefaultSize, wxNO_FULL_REPAINT_ON_RESIZE, _T("ID_LMS6_TABS"));
    m_system = new pnlSystem(pcSPIS, ID_SYSTEM_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SYSTEM_TAB"));
    m_top = new pnlTop(pcSPIS, ID_TOP_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_TOP_TAB"));
    m_TxPLL = new pnlTxPLL(pcSPIS, ID_TXPLL_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TXPLL_TAB"));
    m_RxPLL = new pnlTxPLL(pcSPIS, ID_RXPLL_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RXPLL_TAB"));
    m_TxLPF = new pnlTxLPF(pcSPIS, ID_TXLPF_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TXLPF_TAB"));
    m_TxRF = new pnlTxRF(pcSPIS, ID_TXRF_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TXRF_TAB"));
    m_RxLPF = new pnlTxLPF(pcSPIS, ID_RXLPF_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RXLPF_TAB"));
    m_RxVGA2 = new pnlRxVGA2(pcSPIS, ID_RXVGA2_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RXVGA2_TAB"));
    m_RxFE = new pnlRxFE(pcSPIS, ID_RXFE_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RXFE_TAB"));
    m_ADDC = new pnlADDC(pcSPIS, ID_ADDC_TAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_ADDC_TAB"));
    pcSPIS->AddPage(m_system, _("System"), false);
    pcSPIS->AddPage(m_top, _("Top"), false);
    pcSPIS->AddPage(m_TxPLL, _("TxPLL+DSM"), false);
    pcSPIS->AddPage(m_RxPLL, _("RxPLL+DSM"), false);
    pcSPIS->AddPage(m_TxLPF, _("TxLPF"), false);
    pcSPIS->AddPage(m_TxRF, _("TxRF"), false);
    pcSPIS->AddPage(m_RxLPF, _("RxLPF"), false);
    pcSPIS->AddPage(m_RxVGA2, _("RxVGA2"), false);
    pcSPIS->AddPage(m_RxFE, _("RxFE"), false);
    pcSPIS->AddPage(m_ADDC, _("ADDC"), false);
    FlexGridSizer1->Add(pcSPIS, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(0);
    m_messageLogt = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_SCROLL|wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_messageLogt->SetMinSize(wxSize(400,60));
    FlexGridSizer2->Add(m_messageLogt, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnShowLog = new wxButton(this, ID_BUTTON1, _("Log"), wxDefaultPosition, wxSize(45,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer2->Add(btnShowLog, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    lblVerRevMask = new wxStaticText(this, ID_STATICTEXT1, _("Ver:  Rev:  Mask:  "), wxDefaultPosition, wxSize(200,-1), 0, _T("ID_STATICTEXT1"));
    FlexGridSizer3->Add(lblVerRevMask, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    lblRefClk = new wxStaticText(this, ID_STATICTEXT3, _("Reference Clock: 30.72 MHz"), wxDefaultPosition, wxSize(175,-1), 0, _T("ID_STATICTEXT3"));
    FlexGridSizer3->Add(lblRefClk, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    lblDevFwPr = new wxStaticText(this, ID_STATICTEXT2, _("Device: Firmware: Protocol:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    lblDevFwPr->Hide();
    FlexGridSizer3->Add(lblDevFwPr, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnmnuOpenSelected);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnmnuSaveAsSelected);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnmnuChipToGUISelected);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnmnuGUIToChipSelected);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnRegisterTestSelected);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnmnuRefClkSelected);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LMS6002_GUI_Main::OnbtnShowLogClick);
    //*)
    int w, h;
    GetSize(&w, &h);
    SetMinSize( wxSize(w, h) );

    t2 = wxGetUTCTimeMillis();
    cout << "Application Initialization time: " << t2-t1 << endl;

    lmsControl = plmsControl;
    lmsControl->RegisterForNotifications(this);
    MessageLog::getInstance()->RegisterForNotifications(this);
    m_top->Initialize(lmsControl);
    m_TxPLL->SetType(false);
    m_TxPLL->Initialize(lmsControl);
    m_RxPLL->SetType(true);
    m_RxPLL->Initialize(lmsControl);
    m_TxLPF->SetType(false);
    m_TxLPF->Initialize(lmsControl);
    m_RxLPF->SetType(true);
    m_RxLPF->Initialize(lmsControl);
    m_TxRF->Initialize(lmsControl);
    m_RxFE->Initialize(lmsControl);
    m_RxVGA2->Initialize(lmsControl);
    m_ADDC->Initialize(lmsControl);
    m_system->Initialize(lmsControl);
    lblVerRevMask->SetLabel( cDisconnectedStatusVerRevMask );
    DisplayReferenceClock( lmsControl->GetReferenceFrequency(false));

    //mnuAutoUpload->Check( lmsControl->GetAutoUpload() );
//    RemoveTab(ID_SI5356A_TAB);
//    RemoveTab(ID_SI5351C_TAB);
//    RemoveTab(ID_ADF4002_TAB);
}

LMS6002_GUI_Main::~LMS6002_GUI_Main()
{
    //(*Destroy(LMS6002_GUI_Main)
    //*)
}

void LMS6002_GUI_Main::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
    case MSG_INFO:
        PrintToLogWindow(msg.text);
        break;
    case MSG_WARNING:
        PrintToLogWindow(msg.text);
        wxMessageBox( wxString::Format("%s", msg.text), _("WARNING"));
        break;
    case MSG_ERROR:
        PrintToLogWindow(msg.text);
        wxMessageBox( wxString::Format("%s", msg.text), _("ERROR"));
        break;
    case MSG_BOARD_CONNECTED:
        {
            lblVerRevMask->SetLabel( wxString::Format("Ver: %li Rev: %li Mask: %li", lmsControl->GetParam(VER, true, true),lmsControl->GetParam(REV, true, true),lmsControl->GetParam(MASK, true, true)));
            PrintToLogWindow(msg.text);
        }
        break;
    case MSG_BOARD_DISCONNECTED:
        PrintToLogWindow(msg.text);
        lblVerRevMask->SetLabel( cDisconnectedStatusVerRevMask);
        break;
    case MSG_REGISTER_TEST:
        break;
    default:
        PrintToLogWindow(msg.text);
        break;
    }
    if(m_logger)
        m_logger->write(msg.text);
}

void LMS6002_GUI_Main::OnQuit(wxCommandEvent& event)
{
    Destroy();
}

void LMS6002_GUI_Main::OnmnuNewSelected(wxCommandEvent& event)
{
    lmsControl->NewProject();
    UpdateAllPages();
}

void LMS6002_GUI_Main::OnmnuOpenSelected(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open configuration file"), "", "", "ini (*.ini)|*.ini", wxFD_OPEN);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->LoadFromFile(dlg.GetPath().c_str());
    UpdateAllPages();
}

void LMS6002_GUI_Main::OnmnuSaveSelected(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save configuration file"), "", "", "ini (*.ini)|*.ini", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->SaveToFile(dlg.GetPath().c_str(), false);
}

void LMS6002_GUI_Main::OnmnuSaveAsSelected(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save configuration file"), "", "", "ini (*.ini)|*.ini", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->SaveToFile(dlg.GetPath().c_str(), false);
}

void LMS6002_GUI_Main::OnmnuReadRVF_rfifSelected(wxCommandEvent& event)
{
}

void LMS6002_GUI_Main::OnmnuChipToGUISelected(wxCommandEvent& event)
{
    lmsControl->DownloadAll();
    UpdateAllPages();
}

void LMS6002_GUI_Main::OnmnuAboutSelected(wxCommandEvent& event)
{
    dlgAbout dlg(this);
    dlg.ShowModal();
}

void LMS6002_GUI_Main::UpdateAllPages()
{
    m_top->UpdateGUI();
    m_TxPLL->UpdateGUI();
    m_RxPLL->UpdateGUI();
    m_TxLPF->UpdateGUI();
    m_RxLPF->UpdateGUI();
    m_TxRF->UpdateGUI();
    m_RxFE->UpdateGUI();
    m_ADDC->UpdateGUI();
    //m_ADF->UpdateGUI();
    m_RxVGA2->UpdateGUI();
    m_system->UpdateGUI();
}

void LMS6002_GUI_Main::OnmnuRefClkSelected(wxCommandEvent& event)
{
    dlgFloatInput dlg(this, "Reference clock (MHz):", "Enter reference clock", lmsControl->GetReferenceFrequency(false) );
    if( dlg.ShowModal() == wxID_OK)
    {
        lmsControl->SetReferenceFrequency(dlg.GetValue(), true);
        lmsControl->SetReferenceFrequency(dlg.GetValue(), false);
        DisplayReferenceClock(lmsControl->GetReferenceFrequency(false));
    }
}

void LMS6002_GUI_Main::OnRegisterTestSelected(wxCommandEvent& event)
{
    dlgRegisterTest dlg(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, lmsControl);
    dlg.ShowModal();
}

void LMS6002_GUI_Main::OnbtnShowLogClick(wxCommandEvent& event)
{
    if(m_logger)
        m_logger->Show(true);
}

void LMS6002_GUI_Main::OnmnuGUIToChipSelected(wxCommandEvent& event)
{
    lmsControl->UploadAll();
}

void LMS6002_GUI_Main::DisplayReferenceClock(double clk_MHz)
{
    lblRefClk->SetLabel( wxString::Format("Ref. clock: %f MHz", clk_MHz) );
}

void LMS6002_GUI_Main::AddTab(wxNotebookPage* tab, wxString title)
{
    if(pcSPIS->FindPage(tab) == wxNOT_FOUND)
        pcSPIS->InsertPage(pcSPIS->GetPageCount(), tab, title);
}

bool LMS6002_GUI_Main::RemoveTab(const long windowID)
{
    wxWindow *page;
    for(unsigned int i=0; i<pcSPIS->GetPageCount(); ++i)
    {
        page = pcSPIS->GetPage(i);
        if(page->GetId() == windowID )
        {
            pcSPIS->RemovePage(i);
            return true;
        }
    }
    return false;
}

void LMS6002_GUI_Main::PrintToLogWindow(const wxString txt)
{
    m_logMessages.push_back(txt);
    int lines = m_logMessages.size();
    wxString buffer;
    if(lines > 5)
        m_logMessages.pop_front();
    list<wxString>::iterator iter;
    for(iter = m_logMessages.begin(); iter != m_logMessages.end(); ++iter)
    {
        buffer.append(*iter);
    }
    m_messageLogt->SetValue(wxEmptyString);
    m_messageLogt->AppendText(buffer);
}
