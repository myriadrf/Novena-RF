#include "pnlProgramming.h"

//(*InternalHeaders(pnlProgramming)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

#include "Programmer.h"

//(*IdInit(pnlProgramming)
const long pnlProgramming::ID_BUTTON1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT2 = wxNewId();
const long pnlProgramming::ID_STATICTEXT3 = wxNewId();
const long pnlProgramming::ID_STATICTEXT6 = wxNewId();
const long pnlProgramming::ID_CHOICE2 = wxNewId();
const long pnlProgramming::ID_CHOICE1 = wxNewId();
const long pnlProgramming::ID_BUTTON2 = wxNewId();
const long pnlProgramming::ID_GAUGE1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlProgramming,wxPanel)
	//(*EventTable(pnlProgramming)
	//*)
END_EVENT_TABLE()

pnlProgramming::pnlProgramming(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    m_programmer = new Programmer(pSerPort);
	BuildContent(parent,id,pos,size);
}

void pnlProgramming::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlProgramming)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 5, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	btnOpen = new wxButton(this, ID_BUTTON1, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnOpen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblFilename = new wxStaticText(this, ID_STATICTEXT2, _("\?\?\?"), wxDefaultPosition, wxSize(275,-1), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(lblFilename, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Device:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer7->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT6, _("Programming mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbDevice = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	cmbDevice->SetSelection( cmbDevice->Append(_("HPM1000")) );
	cmbDevice->Append(_("Altera FPGA"));
	FlexGridSizer7->Add(cmbDevice, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbProgMode = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(90,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	cmbProgMode->SetSelection( cmbProgMode->Append(_("0")) );
	cmbProgMode->Append(_("1"));
	cmbProgMode->Append(_("2"));
	cmbProgMode->Append(_("3"));
	cmbProgMode->Append(_("4"));
	cmbProgMode->Append(_("5"));
	cmbProgMode->Append(_("6"));
	cmbProgMode->Append(_("7"));
	cmbProgMode->Append(_("8"));
	FlexGridSizer7->Add(cmbProgMode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	btnProgram = new wxButton(this, ID_BUTTON2, _("Program"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer4->Add(btnProgram, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	progressBar = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE1"));
	FlexGridSizer5->Add(progressBar, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblProgressPercent = new wxStaticText(this, ID_STATICTEXT5, _("0 %"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(lblProgressPercent, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlProgramming::OnbtnOpenClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlProgramming::OnbtnProgMyriadClick);
	//*)
}

pnlProgramming::~pnlProgramming()
{
	//(*Destroy(pnlProgramming)
	//*)
}


void pnlProgramming::OnbtnOpenClick(wxCommandEvent& event)
{
    if(!m_programmer)
        return;
    wxFileDialog dlg(this, _("Select file"), "", "", "bin (*.bin)|*.bin", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lblFilename->SetLabel(dlg.GetPath());
}

void pnlProgramming::OnbtnProgMyriadClick(wxCommandEvent& event)
{
    progressBar->SetValue(0);
    lblProgressPercent->SetLabel(wxString::Format("%3.1f%%", 0.0));
    if(!m_programmer)
        return;
    if(m_programmer->LoadFile(lblFilename->GetLabel().ToStdString().c_str(), 0))
    {
        wxMessageBox("Error loading program file");
        return;
    }
    m_programmer->RegisterForNotifications(this);
    int status = m_programmer->UploadProgram(cmbDevice->GetSelection(), cmbProgMode->GetSelection());
    if(status != 0)
    {
        if(status == -3)
            wxMessageBox("Board not connected");
        if(status == -2)
            wxMessageBox("Program file not selected");
    }
    m_programmer->UnregisterFromNotifications(this);
    Notify(LMS_Message(MSG_PROGRAMMING_COMPLETED, "", 0, 0));
}

void pnlProgramming::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
    case MSG_INFO:
    case MSG_ERROR:
        wxMessageBox( wxString::Format("%s", msg.text), _(""));
        break;
    case MSG_PROGRAMMING_PACKET_SENT:
        if(progressBar->GetRange() != msg.param2)
            progressBar->SetRange(msg.param2);
        progressBar->SetValue(msg.param1);
        lblProgressPercent->SetLabel(wxString::Format("%3.1f%%", 100.0*msg.param1/msg.param2));
        break;
    default:
        break;
    }
}
