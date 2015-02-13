// -----------------------------------------------------------------------------
// FILE: 		dlgRegisterTest.cpp
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "dlgRegisterTest.h"
#include "LMS6002_MainControl.h"
#include "RegistersMap.h"
//(*InternalHeaders(dlgRegisterTest)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace lms6;

//(*IdInit(dlgRegisterTest)
const long dlgRegisterTest::ID_BUTTON2 = wxNewId();
const long dlgRegisterTest::ID_RICHTEXTCTRL1 = wxNewId();
const long dlgRegisterTest::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgRegisterTest,wxDialog)
	//(*EventTable(dlgRegisterTest)
	//*)
END_EVENT_TABLE()

dlgRegisterTest::dlgRegisterTest(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, LMS6002_MainControl *mainControl)
{
    m_testStarted = false;
    lmsControl = mainControl;
	BuildContent(parent,id,pos,size);
}

void dlgRegisterTest::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgRegisterTest)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Registers test"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(1);
	btnStart = new wxButton(this, ID_BUTTON2, _("Start registers test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnStart, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	richTextField = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(300,400), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	FlexGridSizer2->Add(richTextField, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClose = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnClose, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegisterTest::OnbtnStartClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegisterTest::OnbtnCloseClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgRegisterTest::OnInit);
	//*)
}

dlgRegisterTest::~dlgRegisterTest()
{
	//(*Destroy(dlgRegisterTest)
	//*)
	lmsControl->UnregisterFromNotifications(this);
}


void dlgRegisterTest::OnbtnCloseClick(wxCommandEvent& event)
{
    lmsControl->getRegistersMap()->CancelRegisterTest();
    lmsControl->UnregisterFromNotifications(this);
    EndModal(wxID_CLOSE);
}

void dlgRegisterTest::OnInit(wxInitDialogEvent& event)
{
    if(lmsControl == NULL)
        return;
    lmsControl->RegisterForNotifications(this);
}

void dlgRegisterTest::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
    case MSG_REGISTER_TEST:
        richTextField->WriteText(msg.text);
        richTextField->ShowPosition(richTextField->GetLastPosition());
        richTextField->Update();
        break;
    default:
        break;
    }
}

void dlgRegisterTest::OnClose(wxCloseEvent& event)
{
    lmsControl->UnregisterFromNotifications(this);
}

void dlgRegisterTest::OnbtnStartClick(wxCommandEvent& event)
{
    m_testStarted = true;
    lmsControl->getRegistersMap()->RegistersTest();
}
