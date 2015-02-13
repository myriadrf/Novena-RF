#include "pnlSi5351C.h"
#include "ctr_6002dr2_LogicDLL.h"
#include <wx/filedlg.h>
//(*InternalHeaders(pnlSi5351C)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSi5351C)
const long pnlSi5351C::ID_BUTTON1 = wxNewId();
const long pnlSi5351C::ID_BUTTON2 = wxNewId();
const long pnlSi5351C::ID_BUTTON4 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT1 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL1 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT2 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT11 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT12 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT13 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT3 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX1 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL2 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX9 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT4 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX2 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL3 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX10 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT5 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX3 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL4 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX11 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT6 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX4 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL5 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX12 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT7 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX5 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL6 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX13 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT8 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX6 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL7 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX14 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT9 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX7 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL8 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX15 = wxNewId();
const long pnlSi5351C::ID_STATICTEXT10 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX8 = wxNewId();
const long pnlSi5351C::ID_TEXTCTRL9 = wxNewId();
const long pnlSi5351C::ID_CHECKBOX16 = wxNewId();
const long pnlSi5351C::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSi5351C,wxPanel)
	//(*EventTable(pnlSi5351C)
	//*)
END_EVENT_TABLE()

pnlSi5351C::pnlSi5351C(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlSi5351C::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSi5351C)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Si5351C"));
	btnUpload = new wxButton(this, ID_BUTTON1, _("Upload register map to Si5351C"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBoxSizer1->Add(btnUpload, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnLoadFile = new wxButton(this, ID_BUTTON2, _("Load register map from file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer1->Add(btnLoadFile, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnResetToDefaults = new wxButton(this, ID_BUTTON4, _("Reset register map to default"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticBoxSizer1->Add(btnResetToDefaults, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(StaticBoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("CLKIN Frequency (MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtCLKIN_MHz = new wxTextCtrl(this, ID_TEXTCTRL1, _("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(txtCLKIN_MHz, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer2, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer9 = new wxFlexGridSizer(0, 4, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Pin Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer9->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Enable channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer9->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Output frequency (MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer9->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _("Invert output"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer9->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("PLL CLK (CLK0)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer9->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK0 = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkEN_CLK0->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK0 = new wxTextCtrl(this, ID_TEXTCTRL2, _("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer9->Add(txtFreq_CLK0, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK0 = new wxCheckBox(this, ID_CHECKBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkInvert_CLK0->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("N/A (CLK1)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText4->Disable();
	FlexGridSizer9->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK1 = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkEN_CLK1->SetValue(false);
	chkEN_CLK1->Disable();
	FlexGridSizer9->Add(chkEN_CLK1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK1 = new wxTextCtrl(this, ID_TEXTCTRL3, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtFreq_CLK1->Disable();
	FlexGridSizer9->Add(txtFreq_CLK1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK1 = new wxCheckBox(this, ID_CHECKBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkInvert_CLK1->SetValue(false);
	chkInvert_CLK1->Disable();
	FlexGridSizer9->Add(chkInvert_CLK1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("RxCLK (CLK2)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer9->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK2 = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkEN_CLK2->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK2 = new wxTextCtrl(this, ID_TEXTCTRL4, _("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer9->Add(txtFreq_CLK2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK2 = new wxCheckBox(this, ID_CHECKBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkInvert_CLK2->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("RxCLK_C (CLK3)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer9->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK3 = new wxCheckBox(this, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkEN_CLK3->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK3 = new wxTextCtrl(this, ID_TEXTCTRL5, _("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer9->Add(txtFreq_CLK3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK3 = new wxCheckBox(this, ID_CHECKBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkInvert_CLK3->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("TxCLK (CLK4)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK4 = new wxCheckBox(this, ID_CHECKBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkEN_CLK4->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK4 = new wxTextCtrl(this, ID_TEXTCTRL6, _("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer9->Add(txtFreq_CLK4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK4 = new wxCheckBox(this, ID_CHECKBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkInvert_CLK4->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("TxCLK_C (CLK5)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer9->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK5 = new wxCheckBox(this, ID_CHECKBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkEN_CLK5->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK5 = new wxTextCtrl(this, ID_TEXTCTRL7, _("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	FlexGridSizer9->Add(txtFreq_CLK5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK5 = new wxCheckBox(this, ID_CHECKBOX14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkInvert_CLK5->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("N/A (CLK6)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticText9->Disable();
	FlexGridSizer9->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK6 = new wxCheckBox(this, ID_CHECKBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkEN_CLK6->SetValue(false);
	chkEN_CLK6->Disable();
	FlexGridSizer9->Add(chkEN_CLK6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK6 = new wxTextCtrl(this, ID_TEXTCTRL8, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	txtFreq_CLK6->Disable();
	FlexGridSizer9->Add(txtFreq_CLK6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK6 = new wxCheckBox(this, ID_CHECKBOX15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkInvert_CLK6->SetValue(false);
	chkInvert_CLK6->Disable();
	FlexGridSizer9->Add(chkInvert_CLK6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("N/A (CLK7)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText10->Disable();
	FlexGridSizer9->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK7 = new wxCheckBox(this, ID_CHECKBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkEN_CLK7->SetValue(false);
	chkEN_CLK7->Disable();
	FlexGridSizer9->Add(chkEN_CLK7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK7 = new wxTextCtrl(this, ID_TEXTCTRL9, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	txtFreq_CLK7->Disable();
	FlexGridSizer9->Add(txtFreq_CLK7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK7 = new wxCheckBox(this, ID_CHECKBOX16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	chkInvert_CLK7->SetValue(false);
	chkInvert_CLK7->Disable();
	FlexGridSizer9->Add(chkInvert_CLK7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnConfigure = new wxButton(this, ID_BUTTON3, _("Configure Clocks"), wxDefaultPosition, wxSize(-1,64), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer4->Add(btnConfigure, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5351C::OnbtnUploadClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5351C::OnbtnLoadFileClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5351C::OnbtnResetToDefaultsClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5351C::OnbtnConfigureClockClick);
	//*)
}

pnlSi5351C::~pnlSi5351C()
{
	//(*Destroy(pnlSi5351C)
	//*)
}

void pnlSi5351C::OnbtnLoadFileClick(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open project file"), "", "", "Register Files (*.h)|*.h|Text files (*.txt)|*.TXT", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMLL_BoardLoadRegValuesFromFile( (char*)openFileDialog.GetPath().ToStdString().c_str());
    LMLL_BoardUploadValuesSi5351C();
}

void pnlSi5351C::OnbtnConfigureClockClick(wxCommandEvent& event)
{
    double refFreq;
    double freq;
    txtCLKIN_MHz->GetValue().ToDouble(&refFreq);
    LMLL_BoardSetCLKIN(refFreq);

    txtFreq_CLK0->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(0, freq, chkEN_CLK0->GetValue(), chkInvert_CLK0->GetValue());
    txtFreq_CLK1->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(1, freq, chkEN_CLK1->GetValue(), chkInvert_CLK1->GetValue());
    txtFreq_CLK2->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(2, freq, chkEN_CLK2->GetValue(), chkInvert_CLK2->GetValue());
    txtFreq_CLK3->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(3, freq, chkEN_CLK3->GetValue(), chkInvert_CLK3->GetValue());
    txtFreq_CLK4->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(4, freq, chkEN_CLK4->GetValue(), chkInvert_CLK4->GetValue());
    txtFreq_CLK5->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(5, freq, chkEN_CLK5->GetValue(), chkInvert_CLK5->GetValue());
    txtFreq_CLK6->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(6, freq, chkEN_CLK6->GetValue(), chkInvert_CLK6->GetValue());
    txtFreq_CLK7->GetValue().ToDouble(&freq);
    LMLL_BoardSetFrequency(7, freq, chkEN_CLK7->GetValue(), chkInvert_CLK7->GetValue());

    LMLL_BoardConfigureSi5351C();
}

void pnlSi5351C::OnbtnResetToDefaultsClick(wxCommandEvent& event)
{
    LMLL_BoardResetToDefaults();
    LMLL_BoardUploadValuesSi5351C();
}

void pnlSi5351C::OnbtnUploadClick(wxCommandEvent& event)
{
    LMLL_BoardUploadValuesSi5351C();
}
