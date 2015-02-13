#include "pnlBoard.h"
#include "ctr_6002dr2_LogicDLL.h"
#include <wx/filedlg.h>
#include "ConnectionManager.h"
//(*InternalHeaders(pnlBoard)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlBoard)
const long pnlBoard::ID_BUTTON2 = wxNewId();
const long pnlBoard::ID_BUTTON4 = wxNewId();
const long pnlBoard::ID_STATICTEXT1 = wxNewId();
const long pnlBoard::ID_TEXTCTRL1 = wxNewId();
const long pnlBoard::ID_STATICTEXT2 = wxNewId();
const long pnlBoard::ID_STATICTEXT11 = wxNewId();
const long pnlBoard::ID_STATICTEXT12 = wxNewId();
const long pnlBoard::ID_STATICTEXT13 = wxNewId();
const long pnlBoard::ID_STATICTEXT3 = wxNewId();
const long pnlBoard::ID_CHECKBOX1 = wxNewId();
const long pnlBoard::ID_TEXTCTRL2 = wxNewId();
const long pnlBoard::ID_CHECKBOX9 = wxNewId();
const long pnlBoard::ID_STATICTEXT4 = wxNewId();
const long pnlBoard::ID_CHECKBOX2 = wxNewId();
const long pnlBoard::ID_TEXTCTRL3 = wxNewId();
const long pnlBoard::ID_CHECKBOX10 = wxNewId();
const long pnlBoard::ID_STATICTEXT5 = wxNewId();
const long pnlBoard::ID_CHECKBOX3 = wxNewId();
const long pnlBoard::ID_TEXTCTRL4 = wxNewId();
const long pnlBoard::ID_CHECKBOX11 = wxNewId();
const long pnlBoard::ID_STATICTEXT6 = wxNewId();
const long pnlBoard::ID_CHECKBOX4 = wxNewId();
const long pnlBoard::ID_TEXTCTRL5 = wxNewId();
const long pnlBoard::ID_CHECKBOX12 = wxNewId();
const long pnlBoard::ID_STATICTEXT7 = wxNewId();
const long pnlBoard::ID_CHECKBOX5 = wxNewId();
const long pnlBoard::ID_TEXTCTRL6 = wxNewId();
const long pnlBoard::ID_CHECKBOX13 = wxNewId();
const long pnlBoard::ID_STATICTEXT8 = wxNewId();
const long pnlBoard::ID_CHECKBOX6 = wxNewId();
const long pnlBoard::ID_TEXTCTRL7 = wxNewId();
const long pnlBoard::ID_CHECKBOX14 = wxNewId();
const long pnlBoard::ID_STATICTEXT9 = wxNewId();
const long pnlBoard::ID_CHECKBOX7 = wxNewId();
const long pnlBoard::ID_TEXTCTRL8 = wxNewId();
const long pnlBoard::ID_CHECKBOX15 = wxNewId();
const long pnlBoard::ID_STATICTEXT10 = wxNewId();
const long pnlBoard::ID_CHECKBOX8 = wxNewId();
const long pnlBoard::ID_TEXTCTRL9 = wxNewId();
const long pnlBoard::ID_CHECKBOX16 = wxNewId();
const long pnlBoard::ID_BUTTON3 = wxNewId();
const long pnlBoard::ID_STATICTEXT15 = wxNewId();
const long pnlBoard::ID_COMBOBOX2 = wxNewId();
const long pnlBoard::ID_STATICTEXT16 = wxNewId();
const long pnlBoard::ID_COMBOBOX3 = wxNewId();
const long pnlBoard::ID_CHECKBOX17 = wxNewId();
const long pnlBoard::ID_CHECKBOX18 = wxNewId();
const long pnlBoard::ID_CHECKBOX19 = wxNewId();
const long pnlBoard::ID_STATICTEXT17 = wxNewId();
const long pnlBoard::ID_COMBOBOX4 = wxNewId();
const long pnlBoard::ID_STATICTEXT18 = wxNewId();
const long pnlBoard::ID_COMBOBOX5 = wxNewId();
const long pnlBoard::ID_CHECKBOX20 = wxNewId();
const long pnlBoard::ID_CHECKBOX21 = wxNewId();
const long pnlBoard::ID_CHECKBOX22 = wxNewId();
const long pnlBoard::ID_STATICTEXT14 = wxNewId();
const long pnlBoard::ID_COMBOBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlBoard,wxPanel)
	//(*EventTable(pnlBoard)
	//*)
END_EVENT_TABLE()

pnlBoard::pnlBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlBoard::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlBoard)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Clock Gen"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Si5351C"));
	btnLoadFile = new wxButton(this, ID_BUTTON2, _T("Load register map from file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer2->Add(btnLoadFile, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnResetToDefaults = new wxButton(this, ID_BUTTON4, _T("Reset register map to default"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticBoxSizer2->Add(btnResetToDefaults, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("CLKIN Frequency (MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtCLKIN_MHz = new wxTextCtrl(this, ID_TEXTCTRL1, _T("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer5->Add(txtCLKIN_MHz, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer9 = new wxFlexGridSizer(0, 4, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Pin Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer9->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _T("Enable channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer9->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _T("Output frequency (MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer9->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _T("Invert output"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer9->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("PLL CLK (CLK0)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer9->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK0 = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkEN_CLK0->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK0 = new wxTextCtrl(this, ID_TEXTCTRL2, _T("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer9->Add(txtFreq_CLK0, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK0 = new wxCheckBox(this, ID_CHECKBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkInvert_CLK0->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("N/A (CLK1)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText4->Disable();
	FlexGridSizer9->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK1 = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkEN_CLK1->SetValue(false);
	chkEN_CLK1->Disable();
	FlexGridSizer9->Add(chkEN_CLK1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK1 = new wxTextCtrl(this, ID_TEXTCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	txtFreq_CLK1->Disable();
	FlexGridSizer9->Add(txtFreq_CLK1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK1 = new wxCheckBox(this, ID_CHECKBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkInvert_CLK1->SetValue(false);
	chkInvert_CLK1->Disable();
	FlexGridSizer9->Add(chkInvert_CLK1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("RxCLK (CLK2)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer9->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK2 = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkEN_CLK2->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK2 = new wxTextCtrl(this, ID_TEXTCTRL4, _T("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer9->Add(txtFreq_CLK2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK2 = new wxCheckBox(this, ID_CHECKBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkInvert_CLK2->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _T("RxCLK_C (CLK3)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer9->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK3 = new wxCheckBox(this, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkEN_CLK3->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK3 = new wxTextCtrl(this, ID_TEXTCTRL5, _T("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer9->Add(txtFreq_CLK3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK3 = new wxCheckBox(this, ID_CHECKBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkInvert_CLK3->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _T("TxCLK (CLK4)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK4 = new wxCheckBox(this, ID_CHECKBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkEN_CLK4->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK4 = new wxTextCtrl(this, ID_TEXTCTRL6, _T("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer9->Add(txtFreq_CLK4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK4 = new wxCheckBox(this, ID_CHECKBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkInvert_CLK4->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _T("TxCLK_C (CLK5)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer9->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK5 = new wxCheckBox(this, ID_CHECKBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkEN_CLK5->SetValue(true);
	FlexGridSizer9->Add(chkEN_CLK5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK5 = new wxTextCtrl(this, ID_TEXTCTRL7, _T("20.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	FlexGridSizer9->Add(txtFreq_CLK5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK5 = new wxCheckBox(this, ID_CHECKBOX14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkInvert_CLK5->SetValue(false);
	FlexGridSizer9->Add(chkInvert_CLK5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _T("N/A (CLK6)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	StaticText9->Disable();
	FlexGridSizer9->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK6 = new wxCheckBox(this, ID_CHECKBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkEN_CLK6->SetValue(false);
	chkEN_CLK6->Disable();
	FlexGridSizer9->Add(chkEN_CLK6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK6 = new wxTextCtrl(this, ID_TEXTCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	txtFreq_CLK6->Disable();
	FlexGridSizer9->Add(txtFreq_CLK6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK6 = new wxCheckBox(this, ID_CHECKBOX15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkInvert_CLK6->SetValue(false);
	chkInvert_CLK6->Disable();
	FlexGridSizer9->Add(chkInvert_CLK6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _T("N/A (CLK7)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText10->Disable();
	FlexGridSizer9->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK7 = new wxCheckBox(this, ID_CHECKBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkEN_CLK7->SetValue(false);
	chkEN_CLK7->Disable();
	FlexGridSizer9->Add(chkEN_CLK7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK7 = new wxTextCtrl(this, ID_TEXTCTRL9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	txtFreq_CLK7->Disable();
	FlexGridSizer9->Add(txtFreq_CLK7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK7 = new wxCheckBox(this, ID_CHECKBOX16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	chkInvert_CLK7->SetValue(false);
	chkInvert_CLK7->Disable();
	FlexGridSizer9->Add(chkInvert_CLK7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer9, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnConfigure = new wxButton(this, ID_BUTTON3, _T("Configure Clocks"), wxDefaultPosition, wxSize(-1,64), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer6->Add(btnConfigure, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("MyriadRF2"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("PA IN"));
	FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer10->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1in = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer10->Add(cmbDTC1in, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer10->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2in = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer10->Add(cmbDTC2in, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC1 = new wxCheckBox(this, ID_CHECKBOX17, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	chkSWC1->SetValue(false);
	FlexGridSizer10->Add(chkSWC1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC2 = new wxCheckBox(this, ID_CHECKBOX18, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
	chkSWC2->SetValue(false);
	FlexGridSizer10->Add(chkSWC2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC3 = new wxCheckBox(this, ID_CHECKBOX19, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
	chkSWC3->SetValue(false);
	FlexGridSizer10->Add(chkSWC3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("PA OUT"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer11->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1out = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer11->Add(cmbDTC1out, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer11->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2out = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer11->Add(cmbDTC2out, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC1out = new wxCheckBox(this, ID_CHECKBOX20, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
	chkSWC1out->SetValue(false);
	FlexGridSizer11->Add(chkSWC1out, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC2out = new wxCheckBox(this, ID_CHECKBOX21, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX21"));
	chkSWC2out->SetValue(false);
	FlexGridSizer11->Add(chkSWC2out, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC3out = new wxCheckBox(this, ID_CHECKBOX22, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX22"));
	chkSWC3out->SetValue(false);
	FlexGridSizer11->Add(chkSWC3out, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _T("LNA Bypass:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer12->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNAbypass = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbLNAbypass->SetSelection( cmbLNAbypass->Append(_T("LNA bypassed")) );
	cmbLNAbypass->Append(_T("LNA engaged"));
	FlexGridSizer12->Add(cmbLNAbypass, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer12, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer3, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnLoadFileClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnResetToDefaultsClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnConfigureClockClick);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAIN);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX19,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAIN);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAOUT);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAOUT);
	Connect(ID_CHECKBOX22,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBoard::configMyriadRF_PAOUT);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBoard::OncmbLNAbypassSelected);
	//*)

    wxArrayString sarr;
    sarr.clear();
	for(int i=0; i<16; ++i)
    {
        sarr.push_back( wxString::Format("%.3f pF", 0.64 + 0.160*i));
    }
    cmbDTC1in->Append(sarr);
    cmbDTC1in->SetSelection(0);
    cmbDTC1out->Append(sarr);
    cmbDTC1out->SetSelection(0);

    sarr.clear();
	for(int i=0; i<32; ++i)
    {
        sarr.push_back( wxString::Format("%.3f pF", 0.50 + 0.374*i));
    }
    cmbDTC2in->Append(sarr);
    cmbDTC2in->SetSelection(0);
    cmbDTC2out->Append(sarr);
    cmbDTC2out->SetSelection(0);
}

pnlBoard::~pnlBoard()
{
	//(*Destroy(pnlBoard)
	//*)
}

void pnlBoard::OnbtnLoadFileClick(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open project file"), "", "", "Register Files (*.h)|*.h|Text files (*.txt)|*.TXT", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LMLL_BoardLoadRegValuesFromFile( (char*)openFileDialog.GetPath().ToStdString().c_str());
    LMLL_BoardUploadValuesSi5351C();
}

void pnlBoard::OnbtnConfigureClockClick(wxCommandEvent& event)
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

void pnlBoard::OnbtnResetToDefaultsClick(wxCommandEvent& event)
{
    LMLL_BoardResetToDefaults();
    LMLL_BoardUploadValuesSi5351C();
}

void pnlBoard::OnbtnUploadClick(wxCommandEvent& event)
{
    LMLL_BoardUploadValuesSi5351C();
}

void pnlBoard::OncmbLNAbypassSelected(wxCommandEvent& event)
{
    Main_Module *lmsControl = LMLL_GetControlModule();
    lmsControl->SetGPIO(3, 3, cmbLNAbypass->GetSelection());
}

void pnlBoard::ConfigMyriadRF2(int id)
{
    unsigned char buf[64];
    wxComboBox *dtc1;
    wxComboBox *dtc2;
    wxCheckBox *swc1;
    wxCheckBox *swc2;
    wxCheckBox *swc3;

    if(id == 0)
    {
        dtc1 = cmbDTC1in;
        dtc2 = cmbDTC2in;
        swc1 = chkSWC1;
        swc2 = chkSWC2;
        swc3 = chkSWC3;
    }
    else
    {
        dtc1 = cmbDTC1out;
        dtc2 = cmbDTC2out;
        swc1 = chkSWC1out;
        swc2 = chkSWC2out;
        swc3 = chkSWC3out;
    }

    buf[0] = id;
    buf[1] = 0x01;
    buf[2] = dtc1->GetSelection();

    buf[3] = id;
    buf[4] = 0x02;
    buf[5] = 0;
    buf[5] = (buf[5] << 1) | swc1->GetValue();
    buf[5] = (buf[5] << 1) | swc2->GetValue();
    buf[5] = (buf[5] << 1) | swc3->GetValue();
    buf[5] = (buf[5] << 5) | dtc2->GetSelection();

    LMLL_GetControlModule()->getSerPort()->SendData(CMD_PE636040_WR, buf, 6);
}

void pnlBoard::configMyriadRF_PAIN(wxCommandEvent& event)
{
    ConfigMyriadRF2(0);
}

void pnlBoard::configMyriadRF_PAOUT(wxCommandEvent& event)
{
    ConfigMyriadRF2(1);
}
