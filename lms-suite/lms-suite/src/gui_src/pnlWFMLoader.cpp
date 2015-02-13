#include "pnlWFMLoader.h"
#include "CommonUtilities.h"
//(*InternalHeaders(pnlWFMLoader)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include <vector>
#include "ConnectionManager.h"
#include <fstream>
//(*IdInit(pnlWFMLoader)
const long pnlWFMLoader::ID_BUTTON1 = wxNewId();
const long pnlWFMLoader::ID_STATICTEXT3 = wxNewId();
const long pnlWFMLoader::ID_STATICTEXT2 = wxNewId();
const long pnlWFMLoader::ID_BUTTON2 = wxNewId();
const long pnlWFMLoader::ID_BUTTON3 = wxNewId();
const long pnlWFMLoader::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlWFMLoader,wxPanel)
	//(*EventTable(pnlWFMLoader)
	//*)
END_EVENT_TABLE()

pnlWFMLoader::pnlWFMLoader(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    PluginPanel(this)
{
    m_serPort = pSerPort;
	BuildContent(parent,id,pos,size);
}

void pnlWFMLoader::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlWFMLoader)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	btnOpenFile = new wxButton(this, ID_BUTTON1, _("Select WFM file:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnOpenFile, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	txtFilename = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxSize(381,13), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(txtFilename, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnUpload = new wxButton(this, ID_BUTTON2, _("Upload file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(btnUpload, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnMif = new wxButton(this, ID_BUTTON3, _("Convert to .mif"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer1->Add(btnMif, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnHex = new wxButton(this, ID_BUTTON4, _("Convert to Hex"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer1->Add(btnHex, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnOpenFileClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnUploadClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnMifClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnHexClick);
	//*)
}

pnlWFMLoader::~pnlWFMLoader()
{
	//(*Destroy(pnlWFMLoader)
	//*)
}

int ReadWFM(const char *filename, const char *file_output, std::vector< std::pair<int, int> > &iq_pairs)
{
    FILE *fpin, *fpout;				// File pointers
    unsigned char c1, c2, c3, c4;			// To read Agilent Signal Studio file
    double iin, qin;			// IQ inputs
    int iint, qint;					// IQ integer versions
    int cnt = 0;

    fpin = fopen(filename, "rb");
    if( fpin == NULL)
    {
        printf("WFM Converter: Input file can not be opened.");
        return -1;
    }

    if ((fpout = fopen(file_output, "w")) == NULL)
    {
        printf("WFM Converter: Cannot open output file.");
        return -2;
    }

    while( fscanf(fpin, "%c%c%c%c", &c1, &c2, &c3, &c4) == 4 )
    {
        cnt++;

        c1 &= 0xFF;
        c2 &= 0xFF;
        c3 &= 0xFF;
        c4 &= 0xFF;

        if( c1&0x80 ) iin = (double)(-1*(1<<15) + ((c1&0x7F)<<8) + c2);
        else iin = (double)(((c1&0x7F)<<8) + c2);

        if( c3&0x80 ) qin = (double)(-1*(1<<15) + ((c3&0x7F)<<8) + c4);
        else qin = (double)(((c3&0x7F)<<8) + c4);

        iint = (int)(iin);
        qint = (int)(qin);

        iint = iint >> 4;
        qint = qint >> 4;

        iq_pairs.push_back( std::pair<int, int>(iint, qint) );
        fprintf(fpout, "%10d%10d\n", iint, qint);

    };
    fclose(fpin);
    fclose(fpout);
    return 0;
}

void pnlWFMLoader::OnbtnUploadClick(wxCommandEvent& event)
{
    if(m_serPort->IsOpen())
    {
        unsigned char ctrbuf[64];
        unsigned char inbuf[64];
        memset(ctrbuf, 0, 64);
        ctrbuf[0] = 0x14;
        ctrbuf[1] = 0xAA;
        ctrbuf[2] = 0x01;
        ctrbuf[3] = 0x00;
        ctrbuf[4] = 0x02;
        ctrbuf[5] = 0x7F;
        m_serPort->Port_write_direct(ctrbuf, 64);
        long len = 64;
        m_serPort->Port_read_direct(inbuf, len);

        vector< pair<int,int> > iq_pairs;
        if(txtFilename->GetLabel().size() == 0)
        {
            wxMessageBox("File not selected", "Error");
            return;
        }
        ReadWFM(txtFilename->GetLabel().ToAscii(), "output.txt", iq_pairs);
        int bufferSize = iq_pairs.size()*2;
        unsigned short *buffer = new unsigned short[bufferSize];
        memset(buffer, 0, bufferSize);
        int bufPos = 0;
        short ii = 0;
        short qq = 0;
        for(unsigned i=0; i<iq_pairs.size(); ++i)
        {
            ii = iq_pairs[i].first;
            qq = iq_pairs[i].second;
            buffer[bufPos] = (ii & 0xFFF) | 0x1000;
            buffer[bufPos+1] = (qq & 0xFFF);
            bufPos += 2;
        }
        long outLen = bufPos*2;

        int context = m_serPort->BeginDataSending((const char*)buffer, outLen);
        if(m_serPort->WaitForSending(context, 10000) == false)
            wxMessageBox("Failed to send data!", "Error");
        int bytesSent = m_serPort->FinishDataSending((const char*)buffer, outLen, context);
        printf("WFM bytes sent: %i\n", bytesSent);
        milSleep(1000);
        ctrbuf[5] = 0x3F;
        m_serPort->Port_write_direct(ctrbuf, 64);
        len = 64;
        m_serPort->Port_read_direct(inbuf, len);
    }
    else
        wxMessageBox("Device not connected", "Error");
}

void pnlWFMLoader::OnbtnOpenFileClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open file"), "", "", "wfm (*.wfm)|*.wfm", wxFD_OPEN);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    txtFilename->SetLabel( dlg.GetPath().c_str() );
}

void pnlWFMLoader::OnbtnMifClick(wxCommandEvent& event)
{
    vector< pair<int,int> > iq_pairs;
    if(txtFilename->GetLabel().size() == 0)
    {
        wxMessageBox("File not selected", "Error");
        return;
    }
    ReadWFM(txtFilename->GetLabel().ToAscii(), "output.txt", iq_pairs);
    int bufferSize = iq_pairs.size()*2;
    unsigned short *buffer = new unsigned short[bufferSize];
    memset(buffer, 0, bufferSize);
    short ii = 0;
    short qq = 0;

    wxFileDialog dlg(this, _("Save .mif file"), "", "", "mif (*.mif)|*.mif", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    ofstream fout;
    fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
    fout << "WIDTH=13;" << endl;
    fout << "DEPTH=" << iq_pairs.size()*2 << ";" << endl << endl;
    fout << "ADDRESS_RADIX=UNS;" << endl;
    fout << "DATA_RADIX=HEX;" << endl << endl;
    fout << "CONTENT BEGIN" << endl;
    int addr = 0;
    for(unsigned i=0; i<iq_pairs.size(); ++i)
    {
        ii = iq_pairs[i].first;
        qq = iq_pairs[i].second;
        ii = (ii & 0xFFF) | 0x1000;
        fout << "\t" << addr << " : " << uint2hex(ii, 2) << ";" << endl;
        ++addr;
        qq = (qq & 0xFFF);
        fout << "\t" << addr << " : " << uint2hex(qq, 2) << ";" << endl;
        ++addr;
    }
    fout << "END;" << endl;
    fout.close();
}

void pnlWFMLoader::OnbtnHexClick(wxCommandEvent& event)
{
    vector< pair<int,int> > iq_pairs;
    if(txtFilename->GetLabel().size() == 0)
    {
        wxMessageBox("File not selected", "Error");
        return;
    }
    ReadWFM(txtFilename->GetLabel().ToAscii(), "output.txt", iq_pairs);
    int bufferSize = iq_pairs.size()*2;
    unsigned short *buffer = new unsigned short[bufferSize];
    memset(buffer, 0, bufferSize);
    short ii = 0;
    short qq = 0;

    wxFileDialog dlg(this, _("Save .txt file"), "", "", "txt (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    ofstream fout;
    fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
    int addr = 0;
    for(unsigned i=0; i<iq_pairs.size(); ++i)
    {
        ii = iq_pairs[i].first;
        qq = iq_pairs[i].second;
        ii = (ii & 0xFFF);
        fout << "x" << addr << "\"" << uint2hex(ii, 2) << "\"," << endl;
        ++addr;
        qq = (qq & 0xFFF);
        fout << "x" << addr << "\"" << uint2hex(qq, 2) << "\"," << endl;
        ++addr;
    }
    fout.close();
}
