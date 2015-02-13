// -----------------------------------------------------------------------------
// FILE: 		pnlSPI.cpp
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "pnlSPI.h"
#include "CommonUtilities.h"
#include "LMS6002_MainControl.h"
#include "ConnectionManager.h"
#include "RegistersMap.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <wx/filedlg.h>

extern unsigned char bestOfThree(const unsigned char A, const unsigned char B, const unsigned char C);

//(*InternalHeaders(pnlSPI)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSPI)
const long pnlSPI::ID_STATICTEXT1 = wxNewId();
const long pnlSPI::ID_TEXTCTRL1 = wxNewId();
const long pnlSPI::ID_STATICTEXT9 = wxNewId();
const long pnlSPI::ID_TEXTCTRL3 = wxNewId();
const long pnlSPI::ID_BUTTON1 = wxNewId();
const long pnlSPI::ID_STATICTEXT5 = wxNewId();
const long pnlSPI::ID_STATICTEXT6 = wxNewId();
const long pnlSPI::ID_STATICTEXT2 = wxNewId();
const long pnlSPI::ID_TEXTCTRL2 = wxNewId();
const long pnlSPI::ID_BUTTON2 = wxNewId();
const long pnlSPI::ID_STATICTEXT3 = wxNewId();
const long pnlSPI::ID_STATICTEXT4 = wxNewId();
const long pnlSPI::ID_STATICTEXT7 = wxNewId();
const long pnlSPI::ID_STATICTEXT8 = wxNewId();
const long pnlSPI::ID_SCROLLEDWINDOW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSPI,wxPanel)
    //(*EventTable(pnlSPI)
    //*)
END_EVENT_TABLE()

pnlSPI::pnlSPI(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    m_serPort = NULL;
    BuildContent(parent, id);
}

void pnlSPI::Initialize(ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlSPI::BuildContent(wxWindow* parent, wxWindowID id)
{
    //(*Initialize(pnlSPI)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    ScrolledWindow1 = new wxScrolledWindow(this, ID_SCROLLEDWINDOW1, wxPoint(8,8), wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 5, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, ScrolledWindow1, _("Write"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText1 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT1, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddr = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL1, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer3->Add(txtWriteAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT9, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalue = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL3, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer3->Add(txtWvalue, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWrite = new wxButton(ScrolledWindow1, ID_BUTTON1, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(btnWrite, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT5, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatus = new wxStaticText(ScrolledWindow1, ID_STATICTEXT6, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT6"));
    FlexGridSizer3->Add(lblWstatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, ScrolledWindow1, _("Read"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText2 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT2, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddr = new wxTextCtrl(ScrolledWindow1, ID_TEXTCTRL2, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer4->Add(txtReadAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRead = new wxButton(ScrolledWindow1, ID_BUTTON2, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer4->Add(btnRead, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT3, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer5->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadVal = new wxStaticText(ScrolledWindow1, ID_STATICTEXT4, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer5->Add(lblReadVal, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(ScrolledWindow1, ID_STATICTEXT7, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer5->Add(StaticText6, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatus = new wxStaticText(ScrolledWindow1, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT8"));
    FlexGridSizer5->Add(lblRstatus, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    ScrolledWindow1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(ScrolledWindow1);
    FlexGridSizer2->SetSizeHints(ScrolledWindow1);
    FlexGridSizer1->Add(ScrolledWindow1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadClick);
    //*)
    ScrolledWindow1->FitInside();
}

pnlSPI::~pnlSPI()
{
    //(*Destroy(pnlSPI)
    //*)
}


void pnlSPI::OnbtnWriteClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outLen = 2;
    string address = txtWriteAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    pkt.outBuffer[0] = sample & 0xFF;
    string value = txtWvalue->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    pkt.outBuffer[1] = sample & 0xFF;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
}

void pnlSPI::OnbtnReadClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddr->GetValue().ToStdString() );
    string address = txtReadAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_RD;
    pkt.outBuffer[0] = sample & 0xFF;
    pkt.outLen = 1;

    int status = m_serPort->TransferPacket(pkt);
    lblRstatus->SetLabel(status2string(status));

    wxString txthex = "";
    txthex= wxString::Format("%02X", pkt.inBuffer[1]);
    lblReadVal->SetLabel(txthex);
}
