// -----------------------------------------------------------------------------
// FILE: 		dlgFloatInput.cpp
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "dlgFloatInput.h"
#include <iostream>
#include <wx/valtext.h>
using namespace std;

//(*InternalHeaders(dlgFloatInput)
#include <wx/string.h>
//*)

//(*IdInit(dlgFloatInput)
const long dlgFloatInput::ID_STATICTEXT1 = wxNewId();
const long dlgFloatInput::ID_TEXTCTRL1 = wxNewId();
const long dlgFloatInput::ID_BUTTON1 = wxNewId();
const long dlgFloatInput::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgFloatInput,wxDialog)
	//(*EventTable(dlgFloatInput)
	//*)
END_EVENT_TABLE()

dlgFloatInput::dlgFloatInput(wxWindow* parent, const wxString &message, const wxString &title, double defValue)
{
	BuildContent(parent, message, title);
	char ctemp[20];
	sprintf(ctemp, "%f", defValue);
	m_floatString = ctemp;
	txtFloatInput->SetLabel(wxString::Format("%f", defValue));
}

void dlgFloatInput::BuildContent(wxWindow* parent, const wxString &message, const wxString &title)
{
	//(*Initialize(dlgFloatInput)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	txtMessage = new wxStaticText(this, ID_STATICTEXT1, _T("DialogMessage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(txtMessage, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txtFloatInput = new wxTextCtrl(this, ID_TEXTCTRL1, _T("0.0"), wxDefaultPosition, wxDefaultSize, 0, wxTextValidator (wxFILTER_NUMERIC, &m_floatString), _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(txtFloatInput, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	btnOK = new wxButton(this, ID_BUTTON1, _T("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFloatInput::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFloatInput::OnbtnCancelClick);
	//*)
	SetTitle(title);
	txtMessage->SetLabel(message);
}

dlgFloatInput::~dlgFloatInput()
{
	//(*Destroy(dlgFloatInput)
	//*)
}


void dlgFloatInput::OnbtnOKClick(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
        EndModal(wxID_OK);
}

void dlgFloatInput::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

double dlgFloatInput::GetValue()
{
    double result = 0;
    m_floatString.ToDouble(&result);
    return result;
}
