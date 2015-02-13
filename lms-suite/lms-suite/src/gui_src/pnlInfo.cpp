#include "pnlInfo.h"
#include "ConnectionManager.h"
//(*InternalHeaders(pnlInfo)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlInfo)
const long pnlInfo::ID_BUTTON1 = wxNewId();
const long pnlInfo::ID_STATICTEXT1 = wxNewId();
const long pnlInfo::ID_STATICTEXT2 = wxNewId();
const long pnlInfo::ID_STATICTEXT3 = wxNewId();
const long pnlInfo::ID_STATICTEXT4 = wxNewId();
const long pnlInfo::ID_STATICTEXT5 = wxNewId();
const long pnlInfo::ID_STATICTEXT6 = wxNewId();
const long pnlInfo::ID_STATICTEXT7 = wxNewId();
const long pnlInfo::ID_STATICTEXT8 = wxNewId();
const long pnlInfo::ID_STATICTEXT9 = wxNewId();
const long pnlInfo::ID_STATICTEXT10 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlInfo,wxPanel)
	//(*EventTable(pnlInfo)
	//*)
END_EVENT_TABLE()

pnlInfo::pnlInfo(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
    : PluginPanel(this)
{
    m_serPort = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlInfo::Initialize( ConnectionManager *pControl)
{
    m_serPort = pControl;
}

void pnlInfo::UpdatePanel()
{
    GenericPacket pkt;
    pkt.cmd = CMD_GET_INFO;
    pkt.outLen = 1;
    pkt.outBuffer[0] = 0x00;
    int status = STATUS_UNDEFINED;
    if(m_serPort)
        status = m_serPort->TransferPacket(pkt);
    if(status == STATUS_COMPLETED_CMD)
    {
        int devId = pkt.inBuffer[1]<LMS_DEV_COUNT ? pkt.inBuffer[1] : 0;
        lblLMS_DEV->SetLabel(wxString::Format("%s", LMS_DEV_NAMES[devId]));
        int expId = pkt.inBuffer[4]<EXP_BOARD_COUNT ? pkt.inBuffer[4] : 0;
        lblEXP_BOARD->SetLabel(wxString::Format("%s", EXP_BOARD_NAMES[expId]));
        lblFW->SetLabel(wxString::Format("%i", pkt.inBuffer[0]));
        lblHW->SetLabel(wxString::Format("%i", pkt.inBuffer[3]));
        lblProtocol->SetLabel(wxString::Format("%i", pkt.inBuffer[2]));
    }
    else
    {
        lblLMS_DEV->SetLabel("???");
        lblEXP_BOARD->SetLabel("???");
        lblFW->SetLabel("???");
        lblHW->SetLabel("???");
        lblProtocol->SetLabel("???");
    }
}

void pnlInfo::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlInfo)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	btnGetInfo = new wxButton(this, ID_BUTTON1, _T("GET INFO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnGetInfo, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("LMS Device:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblLMS_DEV = new wxStaticText(this, ID_STATICTEXT2, _T("\?\?\?"), wxDefaultPosition, wxSize(128,-1), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(lblLMS_DEV, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Expansion Board:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblEXP_BOARD = new wxStaticText(this, ID_STATICTEXT4, _T("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(lblEXP_BOARD, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT5, _T("Firmware ver.:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFW = new wxStaticText(this, ID_STATICTEXT6, _T("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer2->Add(lblFW, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT7, _T("Hardware ver.:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblHW = new wxStaticText(this, ID_STATICTEXT8, _T("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer2->Add(lblHW, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT9, _T("Protocol:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblProtocol = new wxStaticText(this, ID_STATICTEXT10, _T("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer2->Add(lblProtocol, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlInfo::OnbtnGetInfoClick);
	//*)
}

pnlInfo::~pnlInfo()
{
	//(*Destroy(pnlInfo)
	//*)
}


void pnlInfo::OnbtnGetInfoClick(wxCommandEvent& event)
{
    UpdatePanel();
}
