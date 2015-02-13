#include "dlgLogger.h"
#include <wx/filedlg.h>
#include "MessageLog.h"
#include <sstream>
//(*InternalHeaders(dlgLogger)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgLogger)
const long dlgLogger::ID_RICHTEXTCTRL1 = wxNewId();
const long dlgLogger::ID_CHECKBOX1 = wxNewId();
const long dlgLogger::ID_CHECKBOX2 = wxNewId();
const long dlgLogger::ID_CHECKBOX3 = wxNewId();
const long dlgLogger::ID_CHECKBOX4 = wxNewId();
const long dlgLogger::ID_BUTTON1 = wxNewId();
const long dlgLogger::ID_BUTTON2 = wxNewId();
//*)

using namespace std;

BEGIN_EVENT_TABLE(dlgLogger,wxDialog)
	//(*EventTable(dlgLogger)
	//*)
END_EVENT_TABLE()

dlgLogger::dlgLogger(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgLogger::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgLogger)
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Message Log"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	txtTextField = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	wxFont Font_1(8,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	rchtxtAttr_1.SetFontFaceName(Font_1.GetFaceName());
	rchtxtAttr_1.SetFontSize(Font_1.GetPointSize());
	rchtxtAttr_1.SetFontStyle(Font_1.GetStyle());
	rchtxtAttr_1.SetFontUnderlined(Font_1.GetUnderlined());
	rchtxtAttr_1.SetFontWeight(Font_1.GetWeight());
	txtTextField->SetBasicStyle(rchtxtAttr_1);
	txtTextField->SetMinSize(wxSize(400,500));
	FlexGridSizer1->Add(txtTextField, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Log messages"));
	chkINFO = new wxCheckBox(this, ID_CHECKBOX1, _("INFO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkINFO->SetValue(false);
	StaticBoxSizer1->Add(chkINFO, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkWARNINGS = new wxCheckBox(this, ID_CHECKBOX2, _("WARNINGS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkWARNINGS->SetValue(false);
	StaticBoxSizer1->Add(chkWARNINGS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkERRORS = new wxCheckBox(this, ID_CHECKBOX3, _("ERRORS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkERRORS->SetValue(false);
	StaticBoxSizer1->Add(chkERRORS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDATA = new wxCheckBox(this, ID_CHECKBOX4, _("DATA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkDATA->SetValue(false);
	StaticBoxSizer1->Add(chkDATA, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON1, _("Save to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnSave, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(94,304,1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	btnClear = new wxButton(this, ID_BUTTON2, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnClear, 1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgLogger::OnChangeFilter);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgLogger::OnChangeFilter);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgLogger::OnChangeFilter);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgLogger::OnChangeFilter);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgLogger::OnbtnSaveClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgLogger::OnbtnClearClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgLogger::OnInit);
	//*)
	list<string> logMessages;
    logMessages = MessageLog::getInstance()->getLogMessages();
    stringstream ss;
    for(list<string>::iterator iter=logMessages.begin(); iter!=logMessages.end(); ++iter)
    {
        ss << *iter;
    }
    txtTextField->WriteText( ss.str() );
}

dlgLogger::~dlgLogger()
{
	//(*Destroy(dlgLogger)
	//*)
}

void dlgLogger::OnbtnSaveClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save log file"), "", "", "Text file (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    MessageLog::getInstance()->saveToFile(dlg.GetPath().ToStdString());
}

void dlgLogger::OnbtnClearClick(wxCommandEvent& event)
{
    MessageLog::getInstance()->clear();
    txtTextField->Clear();
}

void dlgLogger::OnInit(wxInitDialogEvent& event)
{
    unsigned int filter = MessageLog::getInstance()->GetLogFilter();
    if(( filter & LOG_INFO) == LOG_INFO)
        chkINFO->SetValue(true);
    if(( filter & LOG_WARNING) == LOG_WARNING)
        chkWARNINGS->SetValue(true);
    if(( filter & LOG_ERROR) == LOG_ERROR)
        chkERRORS->SetValue(true);
    if(( filter & LOG_DATA) == LOG_DATA)
        chkDATA->SetValue(true);
}

void dlgLogger::OnChangeFilter(wxCommandEvent& event)
{
    unsigned int filter = 0;
    if(chkINFO->GetValue())
        filter |= LOG_INFO;
    if(chkWARNINGS->GetValue())
        filter |= LOG_WARNING;
    if(chkERRORS->GetValue())
        filter |= LOG_ERROR;
    if(chkDATA->GetValue())
        filter |= LOG_DATA;

    MessageLog::getInstance()->SetLogFilter(filter);
    MessageLog::getInstance()->SetConsoleFilter(filter, false);
}

void dlgLogger::write(const wxString &str)
{
    txtTextField->AppendText(str);
}

void dlgLogger::OnClose(wxCloseEvent& event)
{
    Hide();
}
