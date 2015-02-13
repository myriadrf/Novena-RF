#include "pnlMyriadRF2.h"

//(*InternalHeaders(pnlMyriadRF2)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

#include "LMS6002_MainControl.h"

using namespace lms6;

//(*IdInit(pnlMyriadRF2)
const long pnlMyriadRF2::ID_STATICTEXT15 = wxNewId();
const long pnlMyriadRF2::ID_COMBOBOX2 = wxNewId();
const long pnlMyriadRF2::ID_STATICTEXT16 = wxNewId();
const long pnlMyriadRF2::ID_COMBOBOX3 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX17 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX18 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX19 = wxNewId();
const long pnlMyriadRF2::ID_STATICTEXT17 = wxNewId();
const long pnlMyriadRF2::ID_COMBOBOX4 = wxNewId();
const long pnlMyriadRF2::ID_STATICTEXT18 = wxNewId();
const long pnlMyriadRF2::ID_COMBOBOX5 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX20 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX21 = wxNewId();
const long pnlMyriadRF2::ID_CHECKBOX22 = wxNewId();
const long pnlMyriadRF2::ID_STATICTEXT14 = wxNewId();
const long pnlMyriadRF2::ID_COMBOBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlMyriadRF2,wxPanel)
	//(*EventTable(pnlMyriadRF2)
	//*)
END_EVENT_TABLE()

pnlMyriadRF2::pnlMyriadRF2(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    PluginPanel(this)
{
	BuildContent(parent,id,pos,size);
}

void pnlMyriadRF2::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlMyriadRF2)
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer11;
	wxStaticBoxSizer* StaticBoxSizer5;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("MyriadRF2"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("PA IN"));
	FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 2);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer10->Add(StaticText15, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1in = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	FlexGridSizer10->Add(cmbDTC1in, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT16, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer10->Add(StaticText16, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2in = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	FlexGridSizer10->Add(cmbDTC2in, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC1 = new wxCheckBox(this, ID_CHECKBOX17, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
	chkSWC1->SetValue(false);
	FlexGridSizer10->Add(chkSWC1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC2 = new wxCheckBox(this, ID_CHECKBOX18, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
	chkSWC2->SetValue(false);
	FlexGridSizer10->Add(chkSWC2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC3 = new wxCheckBox(this, ID_CHECKBOX19, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
	chkSWC3->SetValue(false);
	FlexGridSizer10->Add(chkSWC3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("PA OUT"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 2);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _T("DTC1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer11->Add(StaticText17, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC1out = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	FlexGridSizer11->Add(cmbDTC1out, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT18, _T("DTC2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer11->Add(StaticText18, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbDTC2out = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	FlexGridSizer11->Add(cmbDTC2out, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC1out = new wxCheckBox(this, ID_CHECKBOX20, _T("SW1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
	chkSWC1out->SetValue(false);
	FlexGridSizer11->Add(chkSWC1out, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC2out = new wxCheckBox(this, ID_CHECKBOX21, _T("SW2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX21"));
	chkSWC2out->SetValue(false);
	FlexGridSizer11->Add(chkSWC2out, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkSWC3out = new wxCheckBox(this, ID_CHECKBOX22, _T("SW3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX22"));
	chkSWC3out->SetValue(false);
	FlexGridSizer11->Add(chkSWC3out, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8->Add(StaticBoxSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT14, _T("LNA:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer12->Add(StaticText14, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbLNAbypass = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbLNAbypass->SetSelection( cmbLNAbypass->Append(_T("LNA bypassed")) );
	cmbLNAbypass->Append(_T("LNA engaged"));
	FlexGridSizer12->Add(cmbLNAbypass, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer12, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(StaticBoxSizer3);
	StaticBoxSizer3->Fit(this);
	StaticBoxSizer3->SetSizeHints(this);

	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAIN);
	Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX17,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX18,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAIN);
	Connect(ID_CHECKBOX19,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAIN);
	Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAOUT);
	Connect(ID_COMBOBOX5,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAOUT);
	Connect(ID_CHECKBOX20,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAOUT);
	Connect(ID_CHECKBOX21,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAOUT);
	Connect(ID_CHECKBOX22,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMyriadRF2::configMyriadRF_PAOUT);
	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriadRF2::OncmbLNAbypassSelected);
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

pnlMyriadRF2::~pnlMyriadRF2()
{
	//(*Destroy(pnlMyriadRF2)
	//*)
}

void pnlMyriadRF2::Initialize(LMS6002_MainControl* pControl)
{
    lmsControl = pControl;
}

void pnlMyriadRF2::ConfigMyriadRF2(int id)
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

    GenericPacket pkt;
    pkt.cmd = CMD_PE636040_WR;
    pkt.outLen = 6;
    memcpy(pkt.outBuffer, buf, 6);

    lmsControl->getSerPort()->TransferPacket(pkt);
}

void pnlMyriadRF2::configMyriadRF_PAIN(wxCommandEvent& event)
{
    ConfigMyriadRF2(0);
}

void pnlMyriadRF2::configMyriadRF_PAOUT(wxCommandEvent& event)
{
    ConfigMyriadRF2(1);
}

void pnlMyriadRF2::OncmbLNAbypassSelected(wxCommandEvent& event)
{
    lmsControl->SetGPIO(3, 3, cmbLNAbypass->GetSelection());
}
