#include "dlgSerPort.h"
#include "ConnectionManager.h"
#include "ctr_6002dr2_LogicDLL.h"

//(*InternalHeaders(dlgSerPort)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
//*)

//(*IdInit(dlgSerPort)
const long dlgSerPort::ID_STATICTEXT1 = wxNewId();
const long dlgSerPort::ID_LISTBOX1 = wxNewId();
const long dlgSerPort::ID_BUTTON1 = wxNewId();
const long dlgSerPort::ID_BUTTON2 = wxNewId();
const long dlgSerPort::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgSerPort, wxDialog)
    //(*EventTable(dlgSerPort)
    //*)
END_EVENT_TABLE()

dlgSerPort::dlgSerPort(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    BuildContent(parent,id,pos,size);
}

void dlgSerPort::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(dlgSerPort)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;

    Create(parent, id, _("Connection Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,300));
    Move(wxDefaultPosition);
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Devices"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listReceivers = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    FlexGridSizer2->Add(listReceivers, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgSerPort::OnbtnOKClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgSerPort::OnbtnCancelClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgSerPort::OnbtnDisconnectClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgSerPort::OnInit);
    //*)
}

dlgSerPort::~dlgSerPort()
{
    //(*Destroy(dlgSerPort)
    //*)
}


void dlgSerPort::OnbtnOKClick(wxCommandEvent& event)
{
    int selReceiver = listReceivers->GetSelection();

    if( selReceiver >= 0 )
        LMAL_OpenI( selReceiver );
    //LMAL_SetConnectionType( LMS_RECEIVER );
    EndModal(wxID_OK);
}

void dlgSerPort::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void dlgSerPort::OnInit(wxInitDialogEvent& event)
{
    char cstring[256];
    for(unsigned int i=0; i<LMAL_DeviceCount(); ++i)
    {
        LMAL_DeviceName(cstring, i);
        listReceivers->AppendAndEnsureVisible( cstring );
    }
    listReceivers->SetSelection( LMAL_CurrentDevice());
}

void dlgSerPort::OnbtnDisconnectClick(wxCommandEvent& event)
{
    LMAL_Close();
    EndModal(wxID_ABORT);
}
