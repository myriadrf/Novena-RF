#include "pnlMinimalControls.h"

//(*InternalHeaders(pnlMinimalControls)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/gbsizer.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

#include "LMS_Parameter.h"
using namespace lms6;
//(*IdInit(pnlMinimalControls)
const long pnlMinimalControls::ID_STATICTEXT1 = wxNewId();
const long pnlMinimalControls::ID_BWC_LPF_TXLPF = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT3 = wxNewId();
const long pnlMinimalControls::ID_TEXTCTRL1 = wxNewId();
const long pnlMinimalControls::ID_BUTTON1 = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT2 = wxNewId();
const long pnlMinimalControls::ID_VGA1GAIN = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT4 = wxNewId();
const long pnlMinimalControls::ID_VGA2GAIN_TXVGA2 = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT5 = wxNewId();
const long pnlMinimalControls::ID_BWC_LPF_RXLPF = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT6 = wxNewId();
const long pnlMinimalControls::ID_TEXTCTRL2 = wxNewId();
const long pnlMinimalControls::ID_BUTTON2 = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT7 = wxNewId();
const long pnlMinimalControls::ID_RFB_TIA_RXFE = wxNewId();
const long pnlMinimalControls::ID_STATICTEXT8 = wxNewId();
const long pnlMinimalControls::ID_VGA2GAIN_RXVGA2 = wxNewId();
const long pnlMinimalControls::ID_G_LNA_RXFE = wxNewId();
const long pnlMinimalControls::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlMinimalControls,wxPanel)
	//(*EventTable(pnlMinimalControls)
	//*)
END_EVENT_TABLE()

pnlMinimalControls::pnlMinimalControls(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    PluginPanel(this)
{
	BuildContent(parent,id,pos,size);
}

void pnlMinimalControls::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlMinimalControls)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxGridBagSizer* GridBagSizer1;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Tx"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Filter(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbBWC_LPF_TXLPF = new ComboBoxMap(this, ID_BWC_LPF_TXLPF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_BWC_LPF_TXLPF"));
	FlexGridSizer2->Add(cmbBWC_LPF_TXLPF, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Frequency(GHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	txtFreqGHz_Tx = new wxTextCtrl(this, ID_TEXTCTRL1, _T("2.14"), wxDefaultPosition, wxSize(60,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(txtFreqGHz_Tx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnSetFreqTx = new wxButton(this, ID_BUTTON1, _T("Set"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnSetFreqTx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("VGA1 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbVGA1GAIN = new ComboBoxMap(this, ID_VGA1GAIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA1GAIN"));
	FlexGridSizer2->Add(cmbVGA1GAIN, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("VGA2 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbVGA2GAIN_TXVGA2 = new ComboBoxMap(this, ID_VGA2GAIN_TXVGA2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2GAIN_TXVGA2"));
	FlexGridSizer2->Add(cmbVGA2GAIN_TXVGA2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Rx"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("Filter(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer4->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbBWC_LPF_RXLPF = new ComboBoxMap(this, ID_BWC_LPF_RXLPF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_BWC_LPF_RXLPF"));
	FlexGridSizer4->Add(cmbBWC_LPF_RXLPF, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _T("Frequency(GHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer4->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	txtFreqGHz_Rx = new wxTextCtrl(this, ID_TEXTCTRL2, _T("2.139"), wxDefaultPosition, wxSize(60,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer5->Add(txtFreqGHz_Rx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnSetFreqRx = new wxButton(this, ID_BUTTON2, _T("Set"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer5->Add(btnSetFreqRx, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _T("VGA1 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer4->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbRFB_TIA_RXFE = new ComboBoxMap(this, ID_RFB_TIA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RFB_TIA_RXFE"));
	FlexGridSizer4->Add(cmbRFB_TIA_RXFE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _T("VGA2 Gain(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer4->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbVGA2GAIN_RXVGA2 = new ComboBoxMap(this, ID_VGA2GAIN_RXVGA2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VGA2GAIN_RXVGA2"));
	FlexGridSizer4->Add(cmbVGA2GAIN_RXVGA2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("LNA Gain Mode"));
	cmbG_LNA_RXFE = new ComboBoxMap(this, ID_G_LNA_RXFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_LNA_RXFE"));
	StaticBoxSizer3->Add(cmbG_LNA_RXFE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	GridBagSizer1->Add(StaticBoxSizer3, wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnUpdateGUI = new wxButton(this, ID_BUTTON3, _T("Chip->GUI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	GridBagSizer1->Add(btnUpdateGUI, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(GridBagSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BWC_LPF_TXLPF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMinimalControls::OnbtnSetFreqTxClick);
	Connect(ID_VGA1GAIN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_VGA2GAIN_TXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_BWC_LPF_RXLPF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMinimalControls::OnbtnSetFreqRxClick);
	Connect(ID_RFB_TIA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_VGA2GAIN_RXVGA2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_G_LNA_RXFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMinimalControls::ParameterChangeHandler);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMinimalControls::OnbtnUpdateGUIClick);
	//*)

    char ctemp[80];
    wxArrayString temp;
	wndId2Enum[ID_VGA1GAIN] = VGA1GAIN;
	temp.clear();
    for(int i=-35; i<=-4; i++)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVGA1GAIN->Set(temp);

    wndId2Enum[ID_BWC_LPF_TXLPF] = BWC_LPF_TXLPF;
    wndId2Enum[ID_BWC_LPF_RXLPF] = BWC_LPF_RXLPF;
    temp.clear();
    temp.push_back( "14 MHz");
    temp.push_back( "10 MHz");
    temp.push_back( "7 MHz");
    temp.push_back( "6 MHz");
    temp.push_back( "5 MHz");
    temp.push_back( "4.375 MHz");
    temp.push_back( "3.5 MHz");
    temp.push_back( "3 MHz");
    temp.push_back( "2.75 MHz");
    temp.push_back( "2.5 MHz");
    temp.push_back( "1.92 MHz");
    temp.push_back( "1.5 MHz");
    temp.push_back( "1.375 MHz");
    temp.push_back( "1.25 MHz");
    temp.push_back( "0.875 MHz");
    temp.push_back( "0.75 MHz");
    cmbBWC_LPF_TXLPF->Set(temp);
    cmbBWC_LPF_RXLPF->Set(temp);

    wndId2Enum[ID_VGA2GAIN_TXVGA2] = VGA2GAIN_TXVGA2;
    temp.clear();
    for(int i=0; i<=25; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVGA2GAIN_TXVGA2->Set(temp);

    wndId2Enum[ID_RFB_TIA_RXFE] = RFB_TIA_RXFE;
    temp.clear();
    for(int i=0; i<=120; ++i)
        {sprintf(ctemp, "%.2f", 20*log10(127.0/(127-i))); temp.push_back( ctemp );}
    cmbRFB_TIA_RXFE->Set(temp);

    wndId2Enum[ID_VGA2GAIN_RXVGA2] = VGA2GAIN_RXVGA2;
    temp.clear();
    for(int i=0; i<=30; i+=3)
        {sprintf(ctemp, "%i", i); temp.push_back( ctemp );}
    cmbVGA2GAIN_RXVGA2->Set(temp);

    wndId2Enum[ID_G_LNA_RXFE] = G_LNA_RXFE;
    vector<cmbKeyValuePair> keyVals;
    keyVals.push_back(cmbKeyValuePair(1, wxString(_("Bypass"))));
    keyVals.push_back(cmbKeyValuePair(2, wxString(_("Mid gain"))));
    keyVals.push_back(cmbKeyValuePair(3, wxString(_("Max gain"))));
    cmbG_LNA_RXFE->Set(keyVals);

}

pnlMinimalControls::~pnlMinimalControls()
{
	//(*Destroy(pnlMinimalControls)
	//*)
}

void pnlMinimalControls::ParameterChangeHandler(wxCommandEvent& event)
{
    GUIPanel::ParameterChangeHandler(event);
}

void pnlMinimalControls::OnbtnSetFreqTxClick(wxCommandEvent& event)
{
    double freqMHz = 0;
    txtFreqGHz_Tx->GetValue().ToDouble(&freqMHz);
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;
    lmsControl->SetFrequency(false, 1000*freqMHz, realFreq, Nint, Nfrac, iVco, fVco, divider);
    lmsControl->Tune(false);
}

void pnlMinimalControls::OnbtnSetFreqRxClick(wxCommandEvent& event)
{
    double freqMHz = 0;
    txtFreqGHz_Rx->GetValue().ToDouble(&freqMHz);
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;
    lmsControl->SetFrequency(true, 1000*freqMHz, realFreq, Nint, Nfrac, iVco, fVco, divider);
    lmsControl->Tune(true);
}

void pnlMinimalControls::OnbtnUpdateGUIClick(wxCommandEvent& event)
{
    lmsControl->DownloadAll();
    UpdateGUI();
}
