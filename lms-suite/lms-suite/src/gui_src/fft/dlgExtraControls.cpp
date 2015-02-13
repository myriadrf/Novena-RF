#include "dlgExtraControls.h"

//(*InternalHeaders(dlgExtraControls)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgExtraControls)
//*)

#include <wx/button.h>

#include "ConnectionManager.h"
#include "SamplesCollector.h"

BEGIN_EVENT_TABLE(dlgExtraControls,wxDialog)
	//(*EventTable(dlgExtraControls)
	//*)
END_EVENT_TABLE()

dlgExtraControls::dlgExtraControls(wxWindow* parent, ConnectionManager *serPort, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_serPort = serPort;
    m_collector = NULL;
	BuildContent(parent,id,pos,size);
}

void dlgExtraControls::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgExtraControls)
	Create(parent, id, _("Extra controls"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	SetMinSize(wxSize(256,256));
	m_controlsSizer = new wxFlexGridSizer(0, 2, 0, 0);
	m_controlsSizer->AddGrowableCol(0);
	m_controlsSizer->AddGrowableCol(1);
	m_controlsSizer->AddGrowableRow(0);
	m_checkboxes = new wxFlexGridSizer(0, 1, 0, 0);
	m_controlsSizer->Add(m_checkboxes, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(m_controlsSizer);
	m_controlsSizer->Fit(this);
	m_controlsSizer->SetSizeHints(this);
	//*)
    //eLMS_DEV devtype = m_serPort->GetConnectedDeviceType();
	createControls(LMS_DEV_DIGIGREEN);
	m_controlsSizer->Fit(this);
}

dlgExtraControls::~dlgExtraControls()
{
	//(*Destroy(dlgExtraControls)
	//*)
}

void dlgExtraControls::createControls(int dev_type)
{
    if(dev_type == LMS_DEV_DIGIGREEN)
    {
        wxArrayString choices;
        choices.Add("NCO");
        choices.Add("ADC");
        long id = wxNewId();
        rxDataSource = new wxRadioBox(this, id, "Rx Data Source", wxDefaultPosition, wxDefaultSize, choices, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, "Rx Data Source");
        rxDataSource->SetSelection(1);
        m_controlsSizer->Add(rxDataSource, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);

        id = wxNewId();
        chkFPGATransmitter = new wxCheckBox(this, id, "FPGA Transmitter", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "FPGA Transmitter");
        chkFPGATransmitter->SetValue(true);
        m_checkboxes->Add(chkFPGATransmitter, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);

        id = wxNewId();
        chkFPGAReceiver = new wxCheckBox(this, id, "FPGA Receiver", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "FPGA Receiver");
        chkFPGAReceiver->SetValue(true);
        m_checkboxes->Add(chkFPGAReceiver, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);

        id = wxNewId();
        chkTxEN = new wxCheckBox(this, id, "TxEN", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "TxEN");
        chkTxEN->SetValue(true);
        m_checkboxes->Add(chkTxEN, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);

        id = wxNewId();
        chkRxEN = new wxCheckBox(this, id, "RxEN", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "RxEN");
        chkRxEN->SetValue(true);
        m_checkboxes->Add(chkRxEN, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);

        id = wxNewId();
        chkUSBFIFOReset = new wxCheckBox(this, id, "USB FIFO Reset before START", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "chkUSBFIFOReset");
        chkUSBFIFOReset->SetValue(true);
        m_checkboxes->Add(chkUSBFIFOReset, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onUSBFIFOReset);

        id = wxNewId();
        chkFPGAReset = new wxCheckBox(this, id, "FPGA Reset bit", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "FPGAReset");
        chkFPGAReset->SetValue(true);
        m_checkboxes->Add(chkFPGAReset, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onFPGAReset);

        /*id = wxNewId();
        chkWFMload = new wxCheckBox(this, id, "WFM load bit", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "WFM");
        chkWFMload->SetValue(false);
        m_checkboxes->Add(chkWFMload, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChange);*/

        id = wxNewId();
        btnResetSeq = new wxButton(this, id, "Reset sequence", wxDefaultPosition, wxDefaultSize);
        m_checkboxes->Add(btnResetSeq, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onResetSeq);
    }
    else
    {
        wxArrayString choices;
        choices.Add("NCO");
        choices.Add("ADC");
        long id = wxNewId();
        rxDataSource = new wxRadioBox(this, id, "Rx Data Source", wxDefaultPosition, wxDefaultSize, choices, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, "Rx Data Source");
        rxDataSource->SetSelection(0);
        m_controlsSizer->Add(rxDataSource, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
        Connect(id, wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&dlgExtraControls::onRxDataSourceChangeNovena);
    }
}

void dlgExtraControls::onRxDataSourceChangeNovena(wxCommandEvent &evt)
{
    if(m_collector == NULL)
        return;
    if(evt.GetInt() == 0)
        m_collector->m_dataSource = 0;
    else
        m_collector->m_dataSource = 2;
}

void dlgExtraControls::onRxDataSourceChange(wxCommandEvent &evt)
{
    long length = 64;
	unsigned char out[64];
	memset(out, 0x00, length);
	out[0] = 0x14; //CMD_CFG_I2C_WR 0x14
	out[1] = 0xAA; //CFG_ADDR 0xAA
	out[2] = 1;    //data block count
	out[4] = 0x02; //address
	out[5] = rxDataSource->GetSelection() & 0x01; // RXSRC
	out[5] = (out[5] << 1) | chkTxEN->IsChecked(); // TXEN
	out[5] = (out[5] << 1) | chkRxEN->IsChecked(); // RXEN
	out[5] = (out[5] << 1) | chkFPGATransmitter->GetValue(); // TXDEN
	out[5] = (out[5] << 1) | chkFPGAReceiver->GetValue(); // RXDEN
	out[5] = out[5] << 1; // EN:reserved
	//out[5] = out[5] << 1 | chkWFMload->GetValue(); // EN:reserved

	m_serPort->Port_write_direct(out, length);
	m_serPort->Port_read_direct(out, length);
}

void dlgExtraControls::onUSBFIFOReset(wxCommandEvent &evt)
{
    if(chkUSBFIFOReset->IsChecked() == false)
        return;
    unsigned char out[64];
    long length = 64;
    memset(out, 0x00, length);
    out[0] = 0x40;
    out[1] = 0x10;
    out[2] = 1;
    m_serPort->Port_write_direct(out, length);
    m_serPort->Port_read_direct(out, length);
}

void dlgExtraControls::onFPGAReset(wxCommandEvent &evt)
{
    if(chkUSBFIFOReset->IsChecked() == false)
        return;
    unsigned char out[64];
    long length = 64;
    //reset FPGA ON
	memset(out, 0x00, length);
	out[0] = 0x14;
	out[1] = 0xAA;
	out[2] = 1;
	out[4] = 0x03;
	out[5] = chkFPGAReset->GetValue();
	m_serPort->Port_write_direct(out, length);
	m_serPort->Port_read_direct(out, length);
}

void dlgExtraControls::SetSamplesCollector(SamplesCollector *pCollector)
{
    m_collector = pCollector;
}

void dlgExtraControls::onResetSeq(wxCommandEvent &evt)
{
    long length = 64;
	unsigned char out[64];
	memset(out, 0x00, length);
	out[0] = 0x14; //CMD_CFG_I2C_WR 0x14
	out[1] = 0xAA; //CFG_ADDR 0xAA
	out[2] = 1;
	out[4] = 0x02;
	out[5] = rxDataSource->GetSelection() & 0x01; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | 1; // TXDEN
	out[5] = (out[5] << 1) | 0; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	m_serPort->Port_write_direct(out, length);
	m_serPort->Port_read_direct(out, length);

	//USB FIFO reset
	memset(out, 0x00, length);
	out[0] = 0x40;
	out[1] = 0x10;
	out[2] = 1;
	m_serPort->Port_write_direct(out, length);
	m_serPort->Port_read_direct(out, length);

    memset(out, 0x00, length);
	out[0] = 0x14; //CMD_CFG_I2C_WR 0x14
	out[1] = 0xAA; //CFG_ADDR 0xAA
	out[2] = 1;
	out[4] = 0x02;
	out[5] = rxDataSource->GetSelection() & 0x01; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | 1; // TXDEN
	out[5] = (out[5] << 1) | 1; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

    m_serPort->Port_write_direct(out, length);
    m_serPort->Port_read_direct(out, length);

}
