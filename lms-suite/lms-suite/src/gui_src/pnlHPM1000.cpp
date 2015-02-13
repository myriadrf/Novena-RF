#include "pnlHPM1000.h"

//(*InternalHeaders(pnlHPM1000)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

#include "ConnectionManager.h"
#include <sstream>

//(*IdInit(pnlHPM1000)
const long pnlHPM1000::ID_STATICTEXT1 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT9 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL3 = wxNewId();
const long pnlHPM1000::ID_BUTTON1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT5 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT6 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT2 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL2 = wxNewId();
const long pnlHPM1000::ID_BUTTON2 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT3 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT7 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT8 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT14 = wxNewId();
const long pnlHPM1000::ID_COMBOBOX1 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT10 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT11 = wxNewId();
const long pnlHPM1000::ID_TEXTCTRL5 = wxNewId();
const long pnlHPM1000::ID_BUTTON3 = wxNewId();
const long pnlHPM1000::ID_BUTTON4 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT15 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT16 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT17 = wxNewId();
const long pnlHPM1000::ID_STATICTEXT18 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX1 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX2 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX3 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX4 = wxNewId();
const long pnlHPM1000::ID_CHECKBOX5 = wxNewId();
const long pnlHPM1000::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlHPM1000,wxPanel)
	//(*EventTable(pnlHPM1000)
	//*)
END_EVENT_TABLE()

pnlHPM1000::pnlHPM1000(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
 : PluginPanel(this)
{
    m_serPort = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlHPM1000::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlHPM1000)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 5, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Write"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtWriteAddr = new wxTextCtrl(this, ID_TEXTCTRL1, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(txtWriteAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _T("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtWvalue = new wxTextCtrl(this, ID_TEXTCTRL3, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer3->Add(txtWvalue, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnWrite = new wxButton(this, ID_BUTTON1, _T("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnWrite, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblWstatus = new wxStaticText(this, ID_STATICTEXT6, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(lblWstatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Read"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 7, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtReadAddr = new wxTextCtrl(this, ID_TEXTCTRL2, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer4->Add(txtReadAddr, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnRead = new wxButton(this, ID_BUTTON2, _T("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer4->Add(btnRead, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblReadVal = new wxStaticText(this, ID_STATICTEXT4, _T("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer5->Add(lblReadVal, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer5->Add(StaticText6, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblRstatus = new wxStaticText(this, ID_STATICTEXT8, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT8"));
	FlexGridSizer5->Add(lblRstatus, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("MIPI"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 10, 0, 0);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT14, _T("Id:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer6->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbMIPIId = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbMIPIId->SetSelection( cmbMIPIId->Append(_T("0-TXRFOUT1 to RFin1 tuner")) );
	cmbMIPIId->Append(_T("1-RFout1 to RFin2 tuner"));
	cmbMIPIId->Append(_T("2-RFout2 to TXOUTPA tuner"));
	FlexGridSizer6->Add(cmbMIPIId, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _T("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer6->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtAddrMIPI = new wxTextCtrl(this, ID_TEXTCTRL4, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer6->Add(txtAddrMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT11, _T("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer6->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtValueMIPI = new wxTextCtrl(this, ID_TEXTCTRL5, _T("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer6->Add(txtValueMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnWriteMIPI = new wxButton(this, ID_BUTTON3, _T("Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer6->Add(btnWriteMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnReadMIPI = new wxButton(this, ID_BUTTON4, _T("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer6->Add(btnReadMIPI, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT15, _T("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer1->Add(StaticText11, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblReadValMipi = new wxStaticText(this, ID_STATICTEXT16, _T("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer1->Add(lblReadValMipi, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT17, _T("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer1->Add(StaticText13, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblStatusMIPI = new wxStaticText(this, ID_STATICTEXT18, _T("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT18"));
	FlexGridSizer1->Add(lblStatusMIPI, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("GPIO"));
	chkGPIO4 = new wxCheckBox(this, ID_CHECKBOX1, _T("GPIO4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkGPIO4->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO3 = new wxCheckBox(this, ID_CHECKBOX2, _T("GPIO3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkGPIO3->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO2 = new wxCheckBox(this, ID_CHECKBOX3, _T("GPIO2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkGPIO2->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO1 = new wxCheckBox(this, ID_CHECKBOX4, _T("GPIO1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkGPIO1->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkGPIO0 = new wxCheckBox(this, ID_CHECKBOX5, _T("GPIO0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkGPIO0->SetValue(false);
	StaticBoxSizer4->Add(chkGPIO0, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnReadGPIO = new wxButton(this, ID_BUTTON5, _T("ReadGPIO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	StaticBoxSizer4->Add(btnReadGPIO, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(this);
	FlexGridSizer2->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnWriteClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnWriteMIPIClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadMIPIClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnchkGPIOClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlHPM1000::OnbtnReadGPIOClick);
	//*)
}

pnlHPM1000::~pnlHPM1000()
{
	//(*Destroy(pnlHPM1000)
	//*)
}

void pnlHPM1000::Initialize( ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlHPM1000::UpdatePanel()
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outLen = 1;
    pkt.outBuffer[0] = 0x10;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
    if(status == STATUS_COMPLETED_CMD)
    {
        int value = pkt.inBuffer[1];
        chkGPIO0->SetValue(value & 0x1);
        chkGPIO1->SetValue((value >> 1)&0x1);
        chkGPIO2->SetValue((value >> 2)&0x1);
        chkGPIO3->SetValue((value >> 3)&0x1);
        chkGPIO4->SetValue((value >> 4)&0x1);
    }
}

void pnlHPM1000::OnchkGPIOClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outLen = 2;
    pkt.outBuffer[0] = 0x10;
    pkt.outBuffer[1] = chkGPIO0->GetValue();
    pkt.outBuffer[1] |= chkGPIO1->GetValue() << 1;
    pkt.outBuffer[1] |= chkGPIO2->GetValue() << 2;
    pkt.outBuffer[1] |= chkGPIO3->GetValue() << 3;
    pkt.outBuffer[1] |= chkGPIO4->GetValue() << 4;
    int status = m_serPort->TransferPacket(pkt);
    lblWstatus->SetLabel(status2string(status));
}

void pnlHPM1000::OnbtnWriteClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
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

void pnlHPM1000::OnbtnReadClick(wxCommandEvent& event)
{
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddr->GetValue().ToStdString() );
    string address = txtReadAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outBuffer[0] = sample & 0xFF;
    pkt.outLen = 1;
    int status = m_serPort->TransferPacket(pkt);
    lblRstatus->SetLabel(status2string(status));

    wxString txthex = "";
    txthex= wxString::Format("%02X", pkt.inBuffer[1]);
    lblReadVal->SetLabel(txthex);
}

void pnlHPM1000::OnbtnWriteMIPIClick(wxCommandEvent& event)
{
    unsigned int mipiId = cmbMIPIId->GetSelection();
    unsigned int mipiAddr = 0;
    unsigned int mipiValue = 0;
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    string address = txtAddrMIPI->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &mipiAddr);
    string value = txtValueMIPI->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &mipiValue);
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = mipiAddr;
    pkt.outBuffer[4] = 0x22;
    pkt.outBuffer[5] = mipiValue;
    pkt.outBuffer[6] = 0x23;
    pkt.outBuffer[7] = 0x02; //write bit
    pkt.outLen = 8;
    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        pkt.cmd = CMD_MYRIAD_RD;
        pkt.outBuffer[0] = 0x24;
        pkt.outLen = 1;
        int status = m_serPort->TransferPacket(pkt);
        if(status == STATUS_COMPLETED_CMD)
        {
            lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[1]));
        }
        else
            lblStatusMIPI->SetLabel(status2string(status));
    }
    else
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[status]));
}

void pnlHPM1000::OnbtnReadMIPIClick(wxCommandEvent& event)
{
    unsigned int mipiId = cmbMIPIId->GetSelection();
    unsigned int mipiAddr = 0;
    string address = txtAddrMIPI->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &mipiAddr);
    GenericPacket pkt;
    pkt.cmd = CMD_MYRIAD_WR;
    pkt.outBuffer[0] = 0x20;
    pkt.outBuffer[1] = mipiId;
    pkt.outBuffer[2] = 0x21;
    pkt.outBuffer[3] = mipiAddr;
    pkt.outBuffer[4] = 0x23;
    pkt.outBuffer[5] = 0x01; //read bits
    pkt.outLen = 6;
    if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD)
        lblStatusMIPI->SetLabel("Read ok");
    else
        lblStatusMIPI->SetLabel("Read failed");

    pkt.cmd = CMD_MYRIAD_RD;
    pkt.outBuffer[0] = 0x22;
    pkt.outBuffer[1] = 0x24;
    pkt.outLen = 2;
    int status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[3]));
        wxString txthex = "";
        txthex= wxString::Format("%02X", pkt.inBuffer[1]);
        lblReadValMipi->SetLabel(txthex);
    }
    else
        lblStatusMIPI->SetLabel(status2string(pkt.inBuffer[status]));
}


void pnlHPM1000::OnbtnReadGPIOClick(wxCommandEvent& event)
{
    UpdatePanel();
}
