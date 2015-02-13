// -----------------------------------------------------------------------------
// FILE: 		dlgConnectionSettings.cpp
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "dlgConnectionSettings.h"
#include "ConnectionManager.h"

//(*InternalHeaders(dlgConnectionSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgConnectionSettings)
const long dlgConnectionSettings::ID_CONTROLDEVICE_RGR = wxNewId();
const long dlgConnectionSettings::ID_STATICTEXT1 = wxNewId();
const long dlgConnectionSettings::ID_STATICLINE1 = wxNewId();
const long dlgConnectionSettings::ID_STATICTEXT2 = wxNewId();
const long dlgConnectionSettings::ID_LISTBOX1 = wxNewId();
const long dlgConnectionSettings::ID_STATICLINE2 = wxNewId();
const long dlgConnectionSettings::ID_LISTBOX2 = wxNewId();
const long dlgConnectionSettings::ID_BUTTON1 = wxNewId();
const long dlgConnectionSettings::ID_BUTTON2 = wxNewId();
const long dlgConnectionSettings::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgConnectionSettings,wxDialog)
    //(*EventTable(dlgConnectionSettings)
    //*)
END_EVENT_TABLE()

dlgConnectionSettings::dlgConnectionSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_pManager = NULL;
    BuildContent(parent,id,pos,size);
}

void dlgConnectionSettings::SetConnectionManager(ConnectionManager *pManager)
{
    m_pManager = pManager;
}

void dlgConnectionSettings::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(dlgConnectionSettings)
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, _("Connection Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,300));
    Move(wxDefaultPosition);
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    wxString __wxRadioBoxChoices_1[2] =
    {
    	_("Receiver"),
    	_("Transmitter")
    };
    rgrControlDevice = new wxRadioBox(this, ID_CONTROLDEVICE_RGR, _("Control device"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_ROWS, wxDefaultValidator, _T("ID_CONTROLDEVICE_RGR"));
    rgrControlDevice->SetSelection(0);
    rgrControlDevice->Hide();
    FlexGridSizer1->Add(rgrControlDevice, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(2);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Devices:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(2,10), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    FlexGridSizer2->Add(StaticLine1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Transmitters"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Hide();
    FlexGridSizer2->Add(StaticText2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listReceivers = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    listReceivers->SetMinSize(wxSize(150,100));
    FlexGridSizer2->Add(listReceivers, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(-1,10), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    FlexGridSizer2->Add(StaticLine2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listTransmitters = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
    listTransmitters->SetMinSize(wxSize(150,100));
    listTransmitters->Disable();
    listTransmitters->Hide();
    FlexGridSizer2->Add(listTransmitters, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    btnOK = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer3->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDisconnect = new wxButton(this, ID_BUTTON3, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer3->Add(btnDisconnect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    SetSizer(FlexGridSizer1);
    Layout();
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionSettings::OnbtnOKClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionSettings::OnbtnCancelClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionSettings::OnbtnDisconnectClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgConnectionSettings::OnInit);
    //*)
}

dlgConnectionSettings::~dlgConnectionSettings()
{
    //(*Destroy(dlgConnectionSettings)
    //*)
}


void dlgConnectionSettings::OnbtnOKClick(wxCommandEvent& event)
{
    if(!m_pManager)
        return;


    int selReceiver = listReceivers->GetSelection();
    if( selReceiver >= 0 )
        m_pManager->OpenReceiver( selReceiver );

    switch(rgrControlDevice->GetSelection())
    {
    case 0:
        m_pManager->SetControlDevice( LMS_RECEIVER );
        break;
    case 1:
        m_pManager->SetControlDevice( LMS_TRANSMITTER );
        break;
    default:
        cout << "incorrect value " << rgrControlDevice->GetSelection() << endl;
        break;
    }

    EndModal(wxID_OK);
}

void dlgConnectionSettings::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void dlgConnectionSettings::OnInit(wxInitDialogEvent& event)
{
    if(!m_pManager)
        return;
    m_pManager->FindDevices();
    vector<string> deviceNames;
    deviceNames = m_pManager->GetReceiverList();
    for(unsigned int i=0; i<deviceNames.size(); ++i)
        listReceivers->AppendAndEnsureVisible( deviceNames[i] );
    unsigned dev_index = m_pManager->GetOpenedReceiver();
    if(dev_index < deviceNames.size())
        listReceivers->SetSelection(dev_index);

    deviceNames = m_pManager->GetTransmitterList();
    for(unsigned int i=0; i<deviceNames.size(); ++i)
        listTransmitters->AppendAndEnsureVisible( deviceNames[i] );
    dev_index = m_pManager->GetOpenedTransmitter();
    if(dev_index < deviceNames.size())
        listTransmitters->SetSelection( m_pManager->GetOpenedTransmitter() );

    rgrControlDevice->SetSelection( m_pManager->GetControlDevice() );
}

void dlgConnectionSettings::OnbtnDisconnectClick(wxCommandEvent& event)
{
    m_pManager->Close();
    EndModal(wxID_ABORT);
}
