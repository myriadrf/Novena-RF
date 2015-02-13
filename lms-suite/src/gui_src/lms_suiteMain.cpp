/***************************************************************
 * Name:      lms_suiteMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-09-08
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#include "lms_suiteMain.h"
#include <wx/msgdlg.h>
#include <wx/wx.h>
//(*InternalHeaders(lms_suiteFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "LMS6002_MainControl.h"
#include "LMS_Parameter.h"
#include "Algorithms.h"
#include "LMS6002_GUI_Main.h"
#include "pnlSi5351C.h"
#include "Si5351C.h"
#include "pnlSi5356A.h"
#include "Si5356A.h"
#include "pnlSPI.h"
#include "pnlMyriadRF2.h"
#include "dlgConnectionSettings.h"
#include "ConnectionManager.h"
#include "pnlADF4002.h"
#include "ADF_module.h"
#include "pnlFFTviewer.h"
#include "pnlMinimalControls.h"
#include "pnlWFMLoader.h"
#include "dlgAbout.h"
#include "PluginPanel.h"
#include "pnlProgramming.h"
#include "Programmer.h"
#include "pnlNovena.h"
#include "pnlHPM1000.h"
#include "pnlInfo.h"
//(*IdInit(lms_suiteFrame)
const long lms_suiteFrame::ID_STATICTEXT1 = wxNewId();
const long lms_suiteFrame::ID_COMBOBOX1 = wxNewId();
const long lms_suiteFrame::ID_PANEL1 = wxNewId();
const long lms_suiteFrame::ID_MENUITEM1 = wxNewId();
const long lms_suiteFrame::ID_MENUITEM6 = wxNewId();
const long lms_suiteFrame::idMenuAbout = wxNewId();
const long lms_suiteFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long lms_suiteFrame::ID_MDIFRAME = wxNewId();
const wxString applicationName = "Lime Microsystems Suite";

BEGIN_EVENT_TABLE(lms_suiteFrame,wxFrame)
    //(*EventTable(lms_suiteFrame)
    //*)
END_EVENT_TABLE()

lms_suiteFrame::lms_suiteFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(lms_suiteFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Lime Microsystems Suite"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,750));
    SetMinSize(wxSize(800,600));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Modules collection:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    cmbPluginsConfig = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    cmbPluginsConfig->SetSelection( cmbPluginsConfig->Append(_("CUSTOM")) );
    cmbPluginsConfig->Append(_("EVB6"));
    cmbPluginsConfig->Append(_("DigiGreen"));
    cmbPluginsConfig->Append(_("DigiRed"));
    cmbPluginsConfig->Append(_("Zipper"));
    cmbPluginsConfig->Append(_("Novena"));
    cmbPluginsConfig->Append(_("Stream"));
    FlexGridSizer2->Add(cmbPluginsConfig, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    panelsManager = new wxAuiManager(Panel1, wxAUI_MGR_DEFAULT);
    FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu4 = new wxMenu();
    menuConnectionSettings = new wxMenuItem(Menu4, ID_MENUITEM6, _("Connection settings"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(menuConnectionSettings);
    MenuBar1->Append(Menu4, _("Options"));
    Menu3 = new wxMenu();
    MenuBar1->Append(Menu3, _("Modules"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&lms_suiteFrame::OncmbPluginsConfigSelected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&lms_suiteFrame::OnQuit);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&lms_suiteFrame::OnmenuConnectionSettingsSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&lms_suiteFrame::OnAbout);
    //*)
    m_pluginsConfiguration = PLUGINS_ALL;

    m_serPort = new ConnectionManager();
    m_serPort->RegisterForNotifications(this);

    lms6ctrl = new lms6::LMS6002_MainControl(m_serPort);
    pnl_lms6ctrl = new LMS6002_GUI_Main(Panel1, wxNewId(), lms6ctrl);
    pnl_lms6ctrl->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_DIGIRED|PLUGINS_EVB6|PLUGINS_ZIPPER|PLUGINS_NOVENA|PLUGINS_STREAM);
    plugins.push_back(pnl_lms6ctrl);
    panelsManager->AddPane(pnl_lms6ctrl, wxAuiPaneInfo().Name("LMS6002").Caption("LMS6002").Hide().Float().BestSize(pnl_lms6ctrl->GetSize()).MinSize(pnl_lms6ctrl->GetSize()));

    adf_control = new ADF_module();
    adf_control->Initialize(m_serPort);
    pnladf_control = new pnlADF4002(adf_control, Panel1, wxNewId());
    pnladf_control->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_DIGIRED|PLUGINS_EVB6|PLUGINS_ZIPPER);
    plugins.push_back(pnladf_control);
    panelsManager->AddPane(pnladf_control, wxAuiPaneInfo().Name("ADF4002").Caption("ADF4002").Float().Hide());

    pnlspictrl = new pnlSPI(Panel1, wxNewId());
    pnlspictrl->Initialize(m_serPort);
    pnlspictrl->AssignToConfigurations(PLUGINS_ALL);
    plugins.push_back(pnlspictrl);
    panelsManager->AddPane(pnlspictrl, wxAuiPaneInfo().Name("SPI").Caption("SPI").Float().Hide());

    pnlsi51 = new pnlSi5351C(Panel1, wxNewId());
    pnlsi51->AssignToConfigurations(PLUGINS_ZIPPER);
    si5351ctrl = new Si5351C();
    si5351ctrl->Initialize(m_serPort);
    pnlsi51->Initialize(si5351ctrl);
    plugins.push_back(pnlsi51);
    panelsManager->AddPane(pnlsi51, wxAuiPaneInfo().Name("Si5351C").Caption("Si5351C").Float().Hide());

    pnlsi56 = new pnlSi5356A(Panel1, wxNewId());
    pnlsi56->AssignToConfigurations(PLUGINS_EVB6|PLUGINS_DIGIGREEN|PLUGINS_DIGIRED);
    si5356ctrl = new Si5356A();
    si5356ctrl->Initialize(m_serPort);
    pnlsi56->Initialize( si5356ctrl );
    plugins.push_back(pnlsi56);
    panelsManager->AddPane(pnlsi56, wxAuiPaneInfo().Name("Si5356A").Caption("Si5356A").Float().Hide().BestSize(pnlsi56->GetSize()).MinSize(pnlsi56->GetSize()));

    pnlfft = new pnlFFTviewer(m_serPort, Panel1, wxNewId());
    pnlfft->AssignToConfigurations(PLUGINS_ALL);
    pnlfft->AssignControl(lms6ctrl);
    panelsManager->AddPane(pnlfft, wxAuiPaneInfo().Name("FFTviewer").Caption("FFTviewer").BestSize(pnlfft->GetSize()).MinSize(pnlfft->GetSize()).Center().Dock().Show());

    myriadrf2ctrl = new pnlMyriadRF2(Panel1, wxNewId());
    myriadrf2ctrl->AssignToConfigurations(PLUGINS_ZIPPER);
    myriadrf2ctrl->Initialize(lms6ctrl);
    plugins.push_back(myriadrf2ctrl);
    panelsManager->AddPane(myriadrf2ctrl, wxAuiPaneInfo().Name("MyriadRF2").Caption("MyriadRF2").Float().Hide());

    minCtrl = new pnlMinimalControls(Panel1, wxNewId());
    minCtrl->AssignToConfigurations(PLUGINS_EVB6|PLUGINS_DIGIGREEN|PLUGINS_DIGIRED|PLUGINS_ZIPPER|PLUGINS_NOVENA|PLUGINS_STREAM);
    minCtrl->Initialize(lms6ctrl);
    plugins.push_back(minCtrl);
    minCtrl->UpdateGUI();
    panelsManager->AddPane(minCtrl, wxAuiPaneInfo().Name("MinimalControls").Caption("Minimal Controls").Bottom().Dock().Show());

    pnlwfm = new pnlWFMLoader(m_serPort, Panel1, wxNewId());
    pnlwfm->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_STREAM);
    plugins.push_back(pnlwfm);
    panelsManager->AddPane(pnlwfm, wxAuiPaneInfo().Name("WFMLoader").Caption("WFM Loader").Bottom().Dock().Hide());

    pnlProg = new pnlProgramming(m_serPort, Panel1, wxNewId());
    pnlProg->AssignToConfigurations(PLUGINS_STREAM|PLUGINS_ZIPPER);
    pnlProg->RegisterForNotifications(this);
    plugins.push_back(pnlProg);
    panelsManager->AddPane(pnlProg, wxAuiPaneInfo().Name("Programming").Caption("Programming").Bottom().Dock().Hide());

    pnlNovenaBoard = new pnlNovena(Panel1, wxNewId());
    pnlNovenaBoard->AssignToConfigurations(PLUGINS_NOVENA);
    pnlNovenaBoard->Initialize(lms6ctrl);
    plugins.push_back(pnlNovenaBoard);
    panelsManager->AddPane(pnlNovenaBoard, wxAuiPaneInfo().Name("Novena").Caption("Novena").Bottom().Dock().Hide());

    pnlHPM = new pnlHPM1000(Panel1, wxNewId());
    pnlHPM->AssignToConfigurations(PLUGINS_ALL ^ PLUGINS_NOVENA);
    pnlHPM->Initialize(m_serPort);
    plugins.push_back(pnlHPM);
    panelsManager->AddPane(pnlHPM, wxAuiPaneInfo().Name("HPM1000").Caption("HPM1000").Bottom().Dock().Hide());

    pnlGetInfo = new pnlInfo(Panel1, wxNewId());
    pnlGetInfo ->AssignToConfigurations(PLUGINS_ALL ^ PLUGINS_NOVENA ^ PLUGINS_DIGIGREEN ^ PLUGINS_DIGIRED);
    pnlGetInfo ->Initialize(m_serPort);
    plugins.push_back(pnlGetInfo );
    panelsManager->AddPane(pnlGetInfo , wxAuiPaneInfo().Name("INFO").Caption("INFO").Bottom().Dock().Hide());

    panelsManager->Update();

    InitializeWorkingSettings();
    pnl_lms6ctrl->UpdateAllPages();
    minCtrl->UpdateGUI();
    Layout();
    SetAvailableModules(PLUGINS_ALL);
}

lms_suiteFrame::~lms_suiteFrame()
{
    //(*Destroy(lms_suiteFrame)
    //*)
    panelsManager->UnInit();
    //delete m_serPort;
}

void lms_suiteFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void lms_suiteFrame::OnAbout(wxCommandEvent& event)
{
    dlgAbout dlg(this);
    dlg.ShowModal();
}

void lms_suiteFrame::OnmenuConnectionSettingsSelected(wxCommandEvent& event)
{
    if(pnlfft)
        pnlfft->StopCapturing();
    dlgConnectionSettings dlg(this);
    dlg.SetConnectionManager(m_serPort);
    dlg.ShowModal();
}

void lms_suiteFrame::OnShowModule(wxCommandEvent& event)
{
    wxWindow *item = NULL;
    item = FindWindowById(event.GetId());
    if(item)
    {
        panelsManager->GetPane(item).Show();
        panelsManager->Update();
    }
}

int lms_suiteFrame::InitializeWorkingSettings()
{
    if(m_serPort->IsOpen() == false)
        return -1;
    lms6ctrl->ResetChip(LMS_RST_PULSE);
    lms6ctrl->LoadAdditionalSettings();
    if(m_serPort->GetConnectedDeviceType() == LMS_DEV_DIGIGREEN ||
       m_serPort->GetConnectedDeviceType() == LMS_DEV_DIGIRED)
    {
        si5356ctrl->ConfigureSi5356A();
    }
    if(m_serPort->GetConnectedDeviceType() == LMS_DEV_ZIPPER)
    {
        si5351ctrl->ConfigureClocks();
    }
	lms6ctrl->SetParam(lms6::BWC_LPF_TXLPF, 4); //set LPF bandwidth filters to 5 MHz
	lms6ctrl->SetParam(lms6::BWC_LPF_RXLPF, 4);
    lms6ctrl->SetParam(lms6::STXEN, 1); //enable transmitter
    lms6ctrl->SetParam(lms6::SRXEN, 1); //enable receiver

    lms6ctrl->SetParam(lms6::VGA1GAIN, 14);
    lms6ctrl->SetParam(lms6::MISC_CTRL_6, 1);
    lms6ctrl->SetParam(lms6::PD_7, 1);
    lms6ctrl->SetParam(lms6::PD_5, 1);

    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;

    lms6ctrl->algorithms->CalibrateLPFCore();
    lms6ctrl->algorithms->CalibrateRx();
    lms6ctrl->algorithms->CalibrateTx();

    lms6ctrl->SetFrequency(true, 2139 , realFreq, Nint, Nfrac, iVco, fVco, divider);
    lms6ctrl->Tune(true);

	lms6ctrl->SetFrequency(false, 2140 , realFreq, Nint, Nfrac, iVco, fVco, divider);
    lms6ctrl->Tune(false);

	if(m_serPort->GetConnectedDeviceType() == LMS_DEV_DIGIGREEN)
    {
        unsigned char out[64];
        long length = 64;
        //reset FPGA ON/OFF
        memset(out, 0x00, length);
        out[0] = 0x14;
        out[1] = 0xAA;
        out[2] = 2;
        out[4] = 0x03;
        out[5] = 0x00;
        out[6] = 0x03;
        out[7] = 0x01;
        m_serPort->Port_write_direct(out, length);
        m_serPort->Port_read_direct(out, length);
    }

    return 0;
}

void lms_suiteFrame::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
        case MSG_BOARD_DISCONNECTED:
            SetTitle(applicationName);
            break;
        case MSG_BOARD_CONNECTED:
            {
            //InitializeWorkingSettings();
            eLMS_DEV device = m_serPort->GetConnectedDeviceType();
            SetTitle(applicationName+" - "+m_serPort->GetConnectionStatus());
            if(device == LMS_DEV_UNKNOWN)
            {
                cmbPluginsConfig->SetSelection(5);
                pnlfft->SetBoardType(2);
            }
            else if(device == LMS_DEV_EVB6)
                cmbPluginsConfig->SetSelection(1);
            else if(device == LMS_DEV_DIGIGREEN)
            {
                cmbPluginsConfig->SetSelection(2);
                pnlfft->SetBoardType(0);
            }
            else if(device == LMS_DEV_DIGIRED)
            {
                cmbPluginsConfig->SetSelection(3);
                pnlfft->SetBoardType(1);
            }
            else if(device == LMS_DEV_ZIPPER)
                cmbPluginsConfig->SetSelection(4);
            else if(device == LMS_DEV_STREAM)
            {
                cmbPluginsConfig->SetSelection(6);
                pnlfft->SetBoardType(3);
            }
            wxCommandEvent evt;
            OncmbPluginsConfigSelected(evt);
            }
        break;
        case MSG_PROGRAMMING_COMPLETED:
            {
            wxCommandEvent evt;
            OncmbPluginsConfigSelected(evt); //need to update, after programming can appear expansion board
            break;
            }
        default:
            break;
    }
}

int lms_suiteFrame::SetAvailableModules(unsigned long ePluginsConfiguration_flags)
{
    wxMenuItemList itemList = Menu3->GetMenuItems();
    wxMenuItemList::iterator iter;
    for(iter = itemList.begin(); iter!=itemList.end(); ++iter)
    {
        wxMenuItem *item = *iter;
        Menu3->Destroy(item);
    }
    m_pluginsConfiguration = ePluginsConfiguration_flags;
    GenericPacket pkt;
    pkt.cmd = CMD_GET_INFO;
    pkt.outBuffer[0] = 0;
    pkt.outLen = 1;
    m_serPort->TransferPacket(pkt);
    eEXP_BOARD expansionBoard = (eEXP_BOARD)pkt.inBuffer[4];
    for(unsigned i=0; i<plugins.size(); ++i)
    {
        unsigned long flags = plugins[i]->GetAssignedConfigurations();
        if( (flags & m_pluginsConfiguration) == false)
        {
            wxAuiPaneInfo *pnl = &panelsManager->GetPane(plugins[i]->GetPluginWindow());
            pnl->Hide();
        }
        else
        {
            wxAuiPaneInfo *pnl = &panelsManager->GetPane(plugins[i]->GetPluginWindow());
            if(expansionBoard != EXP_BOARD_HPM1000 && pnl->name == "HPM1000")
            {
                pnl->Hide();
                continue;
            }
            int mnu_id = pnl->window->GetId();
            wxMenuItem *item = new wxMenuItem(Menu3, mnu_id, _(pnl->name), wxEmptyString, wxITEM_NORMAL);
            Menu3->Append(item);
            Connect(mnu_id,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&lms_suiteFrame::OnShowModule);
        }
    }
    panelsManager->Update();
    return 0;
}

void lms_suiteFrame::OncmbPluginsConfigSelected(wxCommandEvent& event)
{
    long selection = cmbPluginsConfig->GetSelection()-1;
    if(selection == -1)
        SetAvailableModules(PLUGINS_ALL);
    else
    {
        SetAvailableModules( pow(2.0, selection) );
    }
}
