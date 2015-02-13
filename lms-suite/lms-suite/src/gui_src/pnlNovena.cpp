#include "pnlNovena.h"

//(*InternalHeaders(pnlNovena)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "ConnectionManager.h"
#include "LMS6002_MainControl.h"
#include "NovenaFPGA.h"
#include "fft/Packets.h"
//(*IdInit(pnlNovena)
const long pnlNovena::ID_STATICTEXT1 = wxNewId();
const long pnlNovena::ID_TEXTCTRL1 = wxNewId();
const long pnlNovena::ID_BUTTON1 = wxNewId();
const long pnlNovena::ID_BUTTON2 = wxNewId();
const long pnlNovena::ID_BUTTON3 = wxNewId();
const long pnlNovena::ID_BUTTON4 = wxNewId();
const long pnlNovena::ID_RADIOBOX1 = wxNewId();
const long pnlNovena::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlNovena,wxPanel)
	//(*EventTable(pnlNovena)
	//*)
END_EVENT_TABLE()

pnlNovena::pnlNovena(wxWindow* parent,wxWindowID id) : PluginPanel(this)
{
	//(*Initialize(pnlNovena)
	wxFlexGridSizer* m_TimeConstSizer;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(2);
	FlexGridSizer2 = new wxFlexGridSizer(0, 5, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("FPGA NCO (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	txtFPGA_NCO_MHz = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(txtFPGA_NCO_MHz, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnWriteNCO = new wxButton(this, ID_BUTTON1, _("Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnWriteNCO, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnReadNCO = new wxButton(this, ID_BUTTON2, _("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnReadNCO, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(444,20,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 4, 0, 0);
	btnFillFIFO = new wxButton(this, ID_BUTTON3, _("Fill FIFO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer3->Add(btnFillFIFO, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnReadFIFO = new wxButton(this, ID_BUTTON4, _("ReadFIFO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer3->Add(btnReadFIFO, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_("NCO"),
		_("ADC")
	};
	rgrDataSource = new wxRadioBox(this, ID_RADIOBOX1, _("DataSource"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrDataSource->SetSelection(1);
	FlexGridSizer3->Add(rgrDataSource, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnEIMsetup = new wxButton(this, ID_BUTTON5, _("EIM setup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer3->Add(btnEIMsetup, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	m_TimeConstSizer = new wxFlexGridSizer(0, 2, 0, 5);
	m_TimeConstSizer->AddGrowableCol(0);
	m_TimeConstSizer->AddGrowableCol(1);
	m_TimeConstSizer->AddGrowableRow(0);
	FlexGridSizer1->Add(m_TimeConstSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNovena::OnbtnWriteNCOClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNovena::OnbtnReadNCOClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNovena::OnbtnFillFIFOClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNovena::OnbtnReadFIFOClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlNovena::OnbtnEIMsetupClick);
	//*)
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
	m_gltimePlot = new OpenGLGraph(this, wxNewId(), wxDefaultPosition, wxSize(800,800), 0, _T("ID_GLCANVAS4"), GLCanvasAttributes_1);
    m_gltimePlot->SetMinSize(wxSize(225,150));
    m_gltimePlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_TimeConstSizer->Add(m_gltimePlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_glconstellationPlot = new OpenGLGraph(this, wxNewId(), wxDefaultPosition, wxSize(800,800), 0, _T("ID_GLCANVAS5"), GLCanvasAttributes_1);
    m_glconstellationPlot->SetMinSize(wxSize(225,150));
    m_glconstellationPlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_TimeConstSizer->Add(m_glconstellationPlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);

    m_gltimePlot->settings.useVBO = true;
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->SetInitialDisplayArea(0, 1024, -2048, 2048);
        m_gltimePlot->settings.title = "IQ samples";
        m_gltimePlot->series[0]->color = 0xFF0000FF;
        m_gltimePlot->series[1]->color = 0x0000FFFF;
        m_gltimePlot->settings.marginLeft = 35;

    m_glconstellationPlot->settings.useVBO = true;
        m_glconstellationPlot->AddSerie(new cDataSerie());
        m_glconstellationPlot->series[0]->color = 0xFF0000FF;
        m_glconstellationPlot->SetInitialDisplayArea(-2048, 2048, -2048, 2048);
        m_glconstellationPlot->SetDrawingMode(GLG_POINTS);
        m_glconstellationPlot->settings.title = "I versus Q";
        m_glconstellationPlot->settings.titleXaxis = "I";
        m_glconstellationPlot->settings.titleYaxis = "Q";
        m_glconstellationPlot->settings.gridXlines = 8;
        m_glconstellationPlot->settings.gridYlines = 8;
        m_glconstellationPlot->settings.marginLeft = 35;
    FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
}

pnlNovena::~pnlNovena()
{
	//(*Destroy(pnlNovena)
	//*)
}

void pnlNovena::OnbtnWriteNCOClick(wxCommandEvent& event)
{
    double Fclk = 0;
    Fclk = lmsControl->GetReferenceFrequency(false);
    Fclk = Fclk * 1000000/2;
    double Fout = 0;
    txtFPGA_NCO_MHz->GetValue().ToDouble(&Fout);
    Fout = Fout * 1000000;
    int fcw = ((Fout)*pow(2.0, 27))/Fclk;
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outBuffer[0] = 0x39 | 0x80;
    pkt.outBuffer[1] = fcw & 0xFF;
    pkt.outBuffer[2] = 0x3A | 0x80;
    pkt.outBuffer[3] = (fcw >> 8) & 0xFF;
    pkt.outBuffer[4] = 0x3B | 0x80;
    pkt.outBuffer[5] = (fcw >> 16) & 0xFF;
    pkt.outBuffer[6] = 0x3C | 0x80;
    pkt.outBuffer[7] = (fcw >> 24) & 0x7;
    pkt.outBuffer[7] = pkt.outBuffer[7] | 0x8; //update
    pkt.outLen = 8;
    lmsControl->getSerPort()->TransferPacket(pkt);
}

void pnlNovena::OnbtnReadNCOClick(wxCommandEvent& event)
{
    double Fclk = 0;
    Fclk = lmsControl->GetReferenceFrequency(false);
    Fclk = Fclk*1000000/2;
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_RD;
    pkt.outBuffer[0] = 0x39;
    pkt.outBuffer[1] = 0x3A;
    pkt.outBuffer[2] = 0x3B;
    pkt.outBuffer[3] = 0x3C;
    pkt.outLen = 4;

    lmsControl->getSerPort()->TransferPacket(pkt);
    int fcw = 0;
    fcw |= pkt.inBuffer[1];
    fcw |= (pkt.inBuffer[3] << 8);
    fcw |= (pkt.inBuffer[5] << 16);
    fcw |= ((pkt.inBuffer[7] & 0x7) << 24);
    double Fout = Fclk*(fcw/pow(2.0, 27));
    txtFPGA_NCO_MHz->SetValue( wxString::Format("%f", Fout/1000000));
}

void pnlNovena::Initialize(lms6::LMS6002_MainControl *pControl)
{
    lmsControl = pControl;
}

void pnlNovena::OnbtnFillFIFOClick(wxCommandEvent& event)
{
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
	pkt.outBuffer[0] = 0xBC; //address
	pkt.outBuffer[1] = 0x40 | (rgrDataSource->GetSelection()*2 & 0x03) << 4;
	pkt.outBuffer[2] = 0xBC; //address
	pkt.outBuffer[3] = 0x00 | (rgrDataSource->GetSelection()*2 & 0x03) << 4;
	pkt.outLen = 4;
    lmsControl->getSerPort()->TransferPacket(pkt);
}

void pnlNovena::OnbtnReadFIFOClick(wxCommandEvent& event)
{
    int buffer_size = 16384*2;
    unsigned short* buffer = new unsigned short[buffer_size];
    int bytesToRead = 4096;
    for(int bb=0; bb<32768; bb+=2048)
    {
        fpga_read(0xC000000, (unsigned short*)&buffer[bb], bytesToRead);
        printf("fpga read %i words\n", bytesToRead/2);
    }

    SamplesPacket *samples = new SamplesPacket(16384*2);
    short tempInt = 0;
    short* buf;
    buf = (short*)buffer;
    int samplesCollected = 0;
    for(int b=0; b<buffer_size; ++b)
    {
        tempInt = buf[b] & 0x0FFF;
        tempInt = tempInt << 4;
        samples->iqdata[samplesCollected] = tempInt >> 4;
        ++samplesCollected;
    }
    int m_FFTsize = 16384;
    float *ftempI = new float[m_FFTsize];
    float *ftempQ = new float[m_FFTsize];
    memset(ftempI, 0, sizeof(float)*m_FFTsize);
    memset(ftempQ, 0, sizeof(float)*m_FFTsize);
    vector<float> timeVector;
    timeVector.reserve(m_FFTsize);
    int pos = 0;
    for(int i=0; i<m_FFTsize; ++i)
    {
        timeVector.push_back(i);
        ftempI[i] = samples->iqdata[pos++];
        ftempQ[i] = samples->iqdata[pos++];
    }

    m_gltimePlot->series[0]->AssignValues(&timeVector[0], ftempI, m_FFTsize);
    m_gltimePlot->series[1]->AssignValues(&timeVector[0], ftempQ, m_FFTsize);
    m_glconstellationPlot->series[0]->AssignValues(samples->iqdata, samples->samplesCount);
    m_gltimePlot->Refresh();
    m_glconstellationPlot->Refresh();
    delete []ftempI;
    delete []ftempQ;
    delete []buffer;
}

void pnlNovena::OnbtnEIMsetupClick(wxCommandEvent& event)
{
    fpga_init();
}
