#include "pnlSi5356A.h"
#include "ConnectionManager.h"
#include "Si5356A.h"

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
//(*InternalHeaders(pnlSi5356A)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSi5356A)
const long pnlSi5356A::ID_BUTTON4 = wxNewId();
const long pnlSi5356A::ID_BUTTON5 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX6 = wxNewId();
const long pnlSi5356A::ID_TEXTCTRL2 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX5 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX4 = wxNewId();
const long pnlSi5356A::ID_STATICLINE1 = wxNewId();
const long pnlSi5356A::ID_STATICTEXT4 = wxNewId();
const long pnlSi5356A::ID_TEXTCTRL4 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX2 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX3 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX1 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX5 = wxNewId();
const long pnlSi5356A::ID_STATICLINE2 = wxNewId();
const long pnlSi5356A::ID_STATICTEXT1 = wxNewId();
const long pnlSi5356A::ID_TEXTCTRL1 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX1 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX6 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX2 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX7 = wxNewId();
const long pnlSi5356A::ID_STATICLINE3 = wxNewId();
const long pnlSi5356A::ID_STATICTEXT3 = wxNewId();
const long pnlSi5356A::ID_TEXTCTRL3 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX9 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX10 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX3 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX8 = wxNewId();
const long pnlSi5356A::ID_STATICLINE4 = wxNewId();
const long pnlSi5356A::ID_STATICTEXT5 = wxNewId();
const long pnlSi5356A::ID_TEXTCTRL5 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX13 = wxNewId();
const long pnlSi5356A::ID_CHECKBOX14 = wxNewId();
const long pnlSi5356A::ID_RADIOBOX4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSi5356A,wxPanel)
	//(*EventTable(pnlSi5356A)
	//*)
END_EVENT_TABLE()

pnlSi5356A::pnlSi5356A(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    m_controlModule = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlSi5356A::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSi5356A)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Si5356A"));
	btnLoadFile = new wxButton(this, ID_BUTTON4, _("Upload register map from file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	StaticBoxSizer2->Add(btnLoadFile, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btnConfigureClock = new wxButton(this, ID_BUTTON5, _("Configure Clocks"), wxDefaultPosition, wxSize(160,32), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	StaticBoxSizer2->Add(btnConfigureClock, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("27 MHz"),
		_("25 MHz")
	};
	rgrCrystalFreq = new wxRadioBox(this, ID_RADIOBOX6, _("Crystal Frequency"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	rgrCrystalFreq->SetSelection(0);
	FlexGridSizer8->Add(rgrCrystalFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("CLKIN (MHz):"));
	txtRefClk = new wxTextCtrl(this, ID_TEXTCTRL2, _("30.72"), wxDefaultPosition, wxSize(72,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	StaticBoxSizer6->Add(txtRefClk, 1, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_("Crystal"),
		_("CLKIN")
	};
	rgrRefClkSelect = new wxRadioBox(this, ID_RADIOBOX5, _("Reference Clock"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	rgrRefClkSelect->SetSelection(1);
	FlexGridSizer8->Add(rgrRefClkSelect, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(2, 2, 5, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Clock 0/1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVAen = new wxCheckBox(this, ID_CHECKBOX4, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkDRVAen->SetValue(true);
	FlexGridSizer1->Add(chkDRVAen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVAfreq = new wxTextCtrl(this, ID_TEXTCTRL4, _("20"), wxDefaultPosition, wxSize(82,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer1->Add(txtDRVAfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVAInvertEven = new wxCheckBox(this, ID_CHECKBOX2, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDRVAInvertEven->SetValue(false);
	FlexGridSizer1->Add(chkDRVAInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVAInvertOdd = new wxCheckBox(this, ID_CHECKBOX3, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkDRVAInvertOdd->SetValue(false);
	FlexGridSizer1->Add(chkDRVAInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_3[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVAoutput = new wxRadioBox(this, ID_RADIOBOX1, _("Output Signal"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_3, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrDRVAoutput->SetSelection(2);
	StaticBoxSizer1->Add(rgrDRVAoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("DAC Clock"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVBen = new wxCheckBox(this, ID_CHECKBOX5, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkDRVBen->SetValue(true);
	FlexGridSizer3->Add(chkDRVBen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	FlexGridSizer3->Add(StaticLine2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVBfreq = new wxTextCtrl(this, ID_TEXTCTRL1, _("20"), wxDefaultPosition, wxSize(82,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(txtDRVBfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVBInvertEven = new wxCheckBox(this, ID_CHECKBOX1, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkDRVBInvertEven->SetValue(false);
	FlexGridSizer3->Add(chkDRVBInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVBInvertOdd = new wxCheckBox(this, ID_CHECKBOX6, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkDRVBInvertOdd->SetValue(false);
	FlexGridSizer3->Add(chkDRVBInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_4[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVBoutput = new wxRadioBox(this, ID_RADIOBOX2, _("Output Signal"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_4, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrDRVBoutput->SetSelection(2);
	StaticBoxSizer3->Add(rgrDRVBoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("ADC Clock"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVCen = new wxCheckBox(this, ID_CHECKBOX7, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkDRVCen->SetValue(true);
	FlexGridSizer4->Add(chkDRVCen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
	FlexGridSizer4->Add(StaticLine3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer4->Add(StaticText3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVCfreq = new wxTextCtrl(this, ID_TEXTCTRL3, _("20"), wxDefaultPosition, wxSize(82,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer4->Add(txtDRVCfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVCInvertEven = new wxCheckBox(this, ID_CHECKBOX9, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkDRVCInvertEven->SetValue(false);
	FlexGridSizer4->Add(chkDRVCInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVCInvertOdd = new wxCheckBox(this, ID_CHECKBOX10, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkDRVCInvertOdd->SetValue(false);
	FlexGridSizer4->Add(chkDRVCInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_5[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVCoutput = new wxRadioBox(this, ID_RADIOBOX3, _("Output Signal"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_5, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	rgrDRVCoutput->SetSelection(2);
	StaticBoxSizer4->Add(rgrDRVCoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, this, _("Clock 6/7"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	chkDRVDen = new wxCheckBox(this, ID_CHECKBOX8, _("Clock Enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkDRVDen->SetValue(true);
	FlexGridSizer5->Add(chkDRVDen, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
	FlexGridSizer5->Add(StaticLine4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Frequency(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDRVDfreq = new wxTextCtrl(this, ID_TEXTCTRL5, _("20"), wxDefaultPosition, wxSize(82,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer5->Add(txtDRVDfreq, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVDInvertEven = new wxCheckBox(this, ID_CHECKBOX13, _("Invert even"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkDRVDInvertEven->SetValue(false);
	FlexGridSizer5->Add(chkDRVDInvertEven, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDRVDInvertOdd = new wxCheckBox(this, ID_CHECKBOX14, _("Invert odd"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkDRVDInvertOdd->SetValue(false);
	FlexGridSizer5->Add(chkDRVDInvertOdd, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	wxString __wxRadioBoxChoices_6[3] =
	{
		_("Even on"),
		_("Odd on"),
		_("Both on")
	};
	rgrDRVDoutput = new wxRadioBox(this, ID_RADIOBOX4, _("Output Signal"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_6, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	rgrDRVDoutput->SetSelection(2);
	StaticBoxSizer5->Add(rgrDRVDoutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(this);
	FlexGridSizer6->SetSizeHints(this);

	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5356A::OnbtnLoadFileClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSi5356A::OnbtnConfigureClockClick);
	//*)
}

pnlSi5356A::~pnlSi5356A()
{
	//(*Destroy(pnlSi5356A)
	//*)
}

void pnlSi5356A::Initialize(Si5356A *pControl)
{
    m_controlModule = pControl;
}

void pnlSi5356A::OnbtnLoadFileClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open register map file"), "", "", "Register files (*.h)|*.h", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    if( m_controlModule->LoadRegValuesFromFile(dlg.GetPath().c_str()) == true)
    {
        if( m_controlModule->ConfigureSi5356A() == false)
            wxMessageBox( _("Failed to configure Si5356A"), _("ERROR"));
    }
    else
        wxMessageBox( _("Failed to load file"), _("ERROR"));
}

void pnlSi5356A::OnbtnConfigureClockClick(wxCommandEvent& event)
{
    double refFreq;
    double freq;

    txtRefClk->GetValue().ToDouble(&refFreq);

    m_controlModule->EnableClock(0, chkDRVAen->GetValue());
    m_controlModule->EnableClock(1, chkDRVBen->GetValue());
    m_controlModule->EnableClock(2, chkDRVCen->GetValue());
    m_controlModule->EnableClock(3, chkDRVDen->GetValue());

    txtDRVAfreq->GetValue().ToDouble(&freq);
    double mult = 1;
    m_controlModule->SetFrequency(0, refFreq*mult, freq*mult);
    txtDRVBfreq->GetValue().ToDouble(&freq);
    m_controlModule->SetFrequency(1, refFreq*mult, freq*mult);
    txtDRVCfreq->GetValue().ToDouble(&freq);
    m_controlModule->SetFrequency(2, refFreq*mult, freq*mult);
    txtDRVDfreq->GetValue().ToDouble(&freq);
    m_controlModule->SetFrequency(3, refFreq*mult, freq*mult);

    unsigned int inv = 0;
    inv = chkDRVAInvertEven->GetValue();
    inv |= chkDRVAInvertOdd->GetValue() << 2;
    m_controlModule->SetInvertClock(0, inv);

    inv = chkDRVBInvertEven->GetValue();
    inv |= chkDRVBInvertOdd->GetValue() << 2;
    m_controlModule->SetInvertClock(1, inv);

    inv = chkDRVCInvertEven->GetValue();
    inv |= chkDRVCInvertOdd->GetValue() << 2;
    m_controlModule->SetInvertClock(2, inv);

    inv = chkDRVDInvertEven->GetValue();
    inv |= chkDRVDInvertOdd->GetValue() << 2;
    m_controlModule->SetInvertClock(3, inv);

    m_controlModule->SetOutputFormat(0, rgrDRVAoutput->GetSelection() + 1);
    m_controlModule->SetOutputFormat(1, rgrDRVBoutput->GetSelection() + 1);
    m_controlModule->SetOutputFormat(2, rgrDRVCoutput->GetSelection() + 1);
    m_controlModule->SetOutputFormat(3, rgrDRVDoutput->GetSelection() + 1);
    if(m_controlModule->ConfigureSi5356A() == false)
        wxMessageBox( _("Failed to configure Si5356A"), _("ERROR"));
}
