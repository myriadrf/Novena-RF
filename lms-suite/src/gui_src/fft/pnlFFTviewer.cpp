/***************************************************************
 * Name:      pnlFFTviewer.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-02-27
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#include "pnlFFTviewer.h"
#include <wx/msgdlg.h>

#include "ConnectionManager.h"
#include "SamplesCollector.h"
#include "FFTcalculator.h"
#include "PlotUpdateThread.h"
#include "dlgAbout.h"
#include "dlgConnectionSettings.h"
#include "CommonUtilities.h"
#include "Packets.h"
#include "NovenaFPGA.h"
#include "LMS6002_MainControl.h"
#include "LMS_Parameter.h"
const char *config_filename = "config.ini";

const int CHANNEL_COUNT = 2;

//(*InternalHeaders(pnlFFTviewer)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlFFTviewer)
const long pnlFFTviewer::ID_GLCANVAS4 = wxNewId();
const long pnlFFTviewer::ID_GLCANVAS5 = wxNewId();
const long pnlFFTviewer::ID_PANEL1 = wxNewId();
const long pnlFFTviewer::ID_GLCANVAS1 = wxNewId();
const long pnlFFTviewer::ID_PANEL2 = wxNewId();
const long pnlFFTviewer::ID_SPLITTERWINDOW1 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT1 = wxNewId();
const long pnlFFTviewer::ID_CHOICE2 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT4 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL1 = wxNewId();
const long pnlFFTviewer::ID_BUTTON1 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT5 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL2 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX1 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL7 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX4 = wxNewId();
const long pnlFFTviewer::ID_COMBOBOX1 = wxNewId();
const long pnlFFTviewer::ID_BUTTON2 = wxNewId();
const long pnlFFTviewer::ID_RADIOBOX1 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT2 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT3 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT6 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT7 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT8 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT9 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX6 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT12 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL8 = wxNewId();
const long pnlFFTviewer::ID_CHOICE1 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX2 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX3 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX5 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT10 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL3 = wxNewId();
const long pnlFFTviewer::ID_BUTTON3 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT11 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL4 = wxNewId();
const long pnlFFTviewer::ID_BUTTON4 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT18 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT20 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL5 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT19 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL6 = wxNewId();
const long pnlFFTviewer::ID_BUTTON6 = wxNewId();
const long pnlFFTviewer::ID_TAB_SPECTRUM = wxNewId();
const long pnlFFTviewer::ID_NOTEBOOK1 = wxNewId();
//*)

wxDEFINE_EVENT(wxEVT_COMMAND_THREAD_UPDATE, wxThreadEvent);
BEGIN_EVENT_TABLE(pnlFFTviewer,wxPanel)
    //(*EventTable(pnlFFTviewer)
    //*)
    EVT_THREAD(wxID_ANY, pnlFFTviewer::OnThreadUpdatePlots)
END_EVENT_TABLE()

pnlFFTviewer::pnlFFTviewer(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id):
    PluginPanel(this)
{
    lmsControl = NULL;
    t2 = t1 = getMilis();
    m_samplesChannels = NULL;
    m_fftOutputs = NULL;
    m_collector = NULL;
    m_calculator = NULL;

    m_redrawsDone = 0;
    m_serPort = pSerPort;

    m_dataReading = false;
    m_plotThread = NULL;

    m_extraControls = new dlgExtraControls(this, m_serPort);

    //(*Initialize(pnlFFTviewer)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* m_plotSizer;
    wxFlexGridSizer* m_TimeConstSizer;
    wxFlexGridSizer* m_spectrumSizer;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* m_controlsSizer;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxFlexGridSizer* m_FFTsizer;

    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    SetMinSize(wxSize(600,400));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    m_MainTabs = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    m_tabSpectrum = new wxPanel(m_MainTabs, ID_TAB_SPECTRUM, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TAB_SPECTRUM"));
    m_spectrumSizer = new wxFlexGridSizer(0, 2, 0, 0);
    m_spectrumSizer->AddGrowableCol(0);
    m_spectrumSizer->AddGrowableRow(0);
    m_plotSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_plotSizer->AddGrowableCol(0);
    m_plotSizer->AddGrowableRow(0);
    m_plotSplitter = new wxSplitterWindow(m_tabSpectrum, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxFULL_REPAINT_ON_RESIZE, _T("ID_SPLITTERWINDOW1"));
    m_plotSplitter->SetMinSize(wxSize(100,100));
    m_plotSplitter->SetMinimumPaneSize(100);
    m_plotSplitter->SetSashGravity(0.5);
    Panel1 = new wxPanel(m_plotSplitter, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    m_TimeConstSizer = new wxFlexGridSizer(0, 2, 0, 5);
    m_TimeConstSizer->AddGrowableCol(0);
    m_TimeConstSizer->AddGrowableCol(1);
    m_TimeConstSizer->AddGrowableRow(0);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_gltimePlot = new OpenGLGraph(Panel1, ID_GLCANVAS4, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS4"), GLCanvasAttributes_1);
    m_gltimePlot->SetMinSize(wxSize(225,150));
    m_gltimePlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_TimeConstSizer->Add(m_gltimePlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    int GLCanvasAttributes_2[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_glconstellationPlot = new OpenGLGraph(Panel1, ID_GLCANVAS5, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS5"), GLCanvasAttributes_2);
    m_glconstellationPlot->SetMinSize(wxSize(225,150));
    m_glconstellationPlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_TimeConstSizer->Add(m_glconstellationPlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel1->SetSizer(m_TimeConstSizer);
    m_TimeConstSizer->Fit(Panel1);
    m_TimeConstSizer->SetSizeHints(Panel1);
    Panel2 = new wxPanel(m_plotSplitter, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    m_FFTsizer = new wxFlexGridSizer(0, 3, 0, 0);
    m_FFTsizer->AddGrowableCol(0);
    m_FFTsizer->AddGrowableCol(1);
    m_FFTsizer->AddGrowableRow(0);
    int GLCanvasAttributes_3[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_glFFTplot = new OpenGLGraph(Panel2, ID_GLCANVAS1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_3);
    m_glFFTplot->SetMinSize(wxSize(300,200));
    m_glFFTplot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_FFTsizer->Add(m_glFFTplot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel2->SetSizer(m_FFTsizer);
    m_FFTsizer->Fit(Panel2);
    m_FFTsizer->SetSizeHints(Panel2);
    m_plotSplitter->SplitHorizontally(Panel1, Panel2);
    m_plotSizer->Add(m_plotSplitter, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_spectrumSizer->Add(m_plotSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_controlsSizer->AddGrowableCol(0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(1);
    StaticText1 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT1, _("Data format:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    cmbBoardType = new wxChoice(m_tabSpectrum, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    cmbBoardType->SetSelection( cmbBoardType->Append(_("DigiGreen")) );
    cmbBoardType->Append(_("DigiRed"));
    cmbBoardType->Append(_("Novena"));
    cmbBoardType->Append(_("Stream"));
    FlexGridSizer2->Add(cmbBoardType, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _("FFT parameters"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 2, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    StaticText4 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT4, _("Sampling frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer4->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtSamplingFreq = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL1, _("15.36"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer4->Add(txtSamplingFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnSamplingFreqRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON1, _("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer4->Add(btnSamplingFreqRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer6->AddGrowableCol(1);
    StaticText5 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT5, _("FFT samples count:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer6->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtFFTsize = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL2, _("16384"), wxDefaultPosition, wxSize(54,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer6->Add(txtFFTsize, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
    chkCalcAverage = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX1, _("Calculate average"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    chkCalcAverage->SetValue(false);
    FlexGridSizer5->Add(chkCalcAverage, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    spinAvg = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL7, _("20"), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    spinAvg->SetMaxLength(4);
    FlexGridSizer5->Add(spinAvg, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer3->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    chkDCcorrection = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX4, _("DC correction"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    chkDCcorrection->SetValue(false);
    FlexGridSizer3->Add(chkDCcorrection, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    cmbWindowFunction = new wxComboBox(m_tabSpectrum, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    cmbWindowFunction->SetSelection( cmbWindowFunction->Append(_("No window")) );
    cmbWindowFunction->Append(_("Blackman-Harris"));
    cmbWindowFunction->Append(_("Hamming"));
    cmbWindowFunction->Append(_("Hanning"));
    cmbWindowFunction->Append(_("Flat top"));
    cmbWindowFunction->Hide();
    FlexGridSizer3->Add(cmbWindowFunction, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, m_tabSpectrum, _("Data Reading"));
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    FlexGridSizer13 = new wxFlexGridSizer(0, 1, 0, 0);
    btnStartStop = new wxButton(m_tabSpectrum, ID_BUTTON2, _("START"), wxDefaultPosition, wxSize(76,76), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer13->Add(btnStartStop, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    wxString __wxRadioBoxChoices_1[2] =
    {
    	_("0"),
    	_("1")
    };
    rgrFrameStart = new wxRadioBox(m_tabSpectrum, ID_RADIOBOX1, _("Frame start"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
    rgrFrameStart->SetSelection(0);
    rgrFrameStart->Disable();
    FlexGridSizer13->Add(rgrFrameStart, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(FlexGridSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer8 = new wxFlexGridSizer(0, 2, 5, 5);
    StaticText2 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT2, _("Data rate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer8->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblDatarate = new wxStaticText(m_tabSpectrum, ID_STATICTEXT3, _("0 MB/s"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer8->Add(m_lblDatarate, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT6, _("FFT/s:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer8->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblFFTperSecond = new wxStaticText(m_tabSpectrum, ID_STATICTEXT7, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer8->Add(m_lblFFTperSecond, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT8, _("Updates/s:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer8->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblUpdatePerSecond = new wxStaticText(m_tabSpectrum, ID_STATICTEXT9, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer8->Add(m_lblUpdatePerSecond, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    chkSaveStreamToFile = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX6, _("Save stream to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    chkSaveStreamToFile->SetValue(false);
    FlexGridSizer14->Add(chkSaveStreamToFile, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText9 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT12, _("filesize (MB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer15->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    spinFilelimit = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL8, _("10"), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    FlexGridSizer15->Add(spinFilelimit, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer14->Add(FlexGridSizer15, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer12->AddGrowableCol(1);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _("Channels"));
    cmbChannelSelection = new wxChoice(m_tabSpectrum, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    cmbChannelSelection->Append(_("A"));
    cmbChannelSelection->Append(_("B"));
    cmbChannelSelection->SetSelection( cmbChannelSelection->Append(_("A&B")) );
    StaticBoxSizer6->Add(cmbChannelSelection, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer12->Add(StaticBoxSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _("Graphs"));
    chkShowConstellation = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX2, _("Show constellation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    chkShowConstellation->SetValue(true);
    StaticBoxSizer4->Add(chkShowConstellation, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkShowFFT = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX3, _("Show FFT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    chkShowFFT->SetValue(true);
    StaticBoxSizer4->Add(chkShowFFT, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkFreezeDrawing = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX5, _("Freeze"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    chkFreezeDrawing->SetValue(false);
    StaticBoxSizer4->Add(chkFreezeDrawing, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer12->Add(StaticBoxSizer4, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _("Analyzer controls"));
    FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer9->AddGrowableCol(0);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer10->AddGrowableCol(1);
    StaticText7 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT10, _("Center:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer10->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_txtCenterFreq = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL3, _("0"), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer10->Add(m_txtCenterFreq, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnCenterFreqRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON3, _("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer10->Add(btnCenterFreqRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer11->AddGrowableCol(0);
    FlexGridSizer11->AddGrowableCol(1);
    StaticText8 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT11, _("Span:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer11->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_txtFreqSpan = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL4, _("10"), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer11->Add(m_txtFreqSpan, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnFreqSpanRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON4, _("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer11->Add(btnFreqSpanRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer11, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer16 = new wxFlexGridSizer(0, 5, 0, 0);
    FlexGridSizer16->AddGrowableCol(0);
    StaticText15 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT18, _("Y axis"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer16->Add(StaticText15, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText17 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT20, _("from:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer16->Add(StaticText17, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtYaxisBottom = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL5, _("-20"), wxDefaultPosition, wxSize(48,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    FlexGridSizer16->Add(txtYaxisBottom, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText16 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT19, _("to:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer16->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtYaxisTop = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL6, _("80"), wxDefaultPosition, wxSize(48,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    FlexGridSizer16->Add(txtYaxisTop, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9->Add(FlexGridSizer16, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_controlsSizer->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnExtraControls = new wxButton(m_tabSpectrum, ID_BUTTON6, _("Extra Controls"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    m_controlsSizer->Add(btnExtraControls, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    m_spectrumSizer->Add(m_controlsSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_tabSpectrum->SetSizer(m_spectrumSizer);
    m_spectrumSizer->Fit(m_tabSpectrum);
    m_spectrumSizer->SetSizeHints(m_tabSpectrum);
    m_MainTabs->AddPage(m_tabSpectrum, _("Spectrum"), false);
    FlexGridSizer1->Add(m_MainTabs, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlFFTviewer::OncmbBoardTypeSelect);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnspinAvgChange);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnspinAvgChange);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnchkDCcorrectionClick);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlFFTviewer::OncmbWindowFunctionSelected);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnbtnStartStopClick);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlFFTviewer::OnChannelSelectionSelect);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnChangePlotVisibility);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnChangePlotVisibility);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnYaxisChange);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnYaxisChange);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnbtnExtraControlsClick);
    //*)
    btnSamplingFreqRatio->SetUnits("Hz");
    btnCenterFreqRatio->SetUnits("Hz");
    btnFreqSpanRatio->SetUnits("Hz");

    int w,h;
    GetSize(&w, &h);
    SetMinSize(wxSize(w, h));


    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxCommandEvent evt;

    //load gui configuration from file
    m_options.Open(config_filename);
    m_options.SelectSection("fft_parameters");
    txtFFTsize->SetValue( m_options.Get("fft_size", "16384"));
    txtSamplingFreq->SetValue( m_options.Get("sampling_freq", "15.36"));
    btnSamplingFreqRatio->SetPower(m_options.Get("sampling_freq_10power", 6));
    chkCalcAverage->SetValue( m_options.Get("calculate_average", false));
    spinAvg->SetValue( m_options.Get("average_count", "20"));
    chkDCcorrection->SetValue( m_options.Get("dc_correction", 0));

    m_options.SelectSection("GUI options");
    cmbChannelSelection->SetSelection(m_options.Get("channel_selection", 0));

    chkShowFFT->SetValue(m_options.Get("show_fft", 1));
    chkShowConstellation->SetValue(m_options.Get("show_constellation", 1));
    m_options.SelectSection("oscilloscope");
    m_txtCenterFreq->SetValue( m_options.Get("center_frequency", "0"));
    btnCenterFreqRatio->SetPower(m_options.Get("center_frequency_10power", 6));
    m_txtFreqSpan->SetValue( m_options.Get("span", "10"));
    btnFreqSpanRatio->SetPower(m_options.Get("span_10power", 6));

     //fill some default values to plots
    long samplesCount = 0;
    double fs = 0;
    vector<double> vecTime;
    vector<double> vecZeros;
    vector<double> freqVector;

    txtFFTsize->GetValue().ToLong(&samplesCount);
    txtSamplingFreq->GetValue().ToDouble(&fs);
    fs = fs*btnSamplingFreqRatio->GetRatio();
    for(int i=0; i<samplesCount-1; ++i)
    {
        vecTime.push_back(i);
        vecZeros.push_back(0);
    }

    freqVector.resize(samplesCount-1);
    for (int f = 0; f < samplesCount / 2-1; f++)
    {
        freqVector[f] = (-1) * (samplesCount / 2 - 1 - f) * (fs / samplesCount);
    }
    // possitive frequencies
    for (int f = 0; f < samplesCount / 2; f++)
    {
        freqVector[f + samplesCount / 2 - 1] = (f) * (fs / samplesCount);
    }

    OnChangePlotVisibility(evt);

    m_gltimePlot->settings.useVBO = true;
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->SetInitialDisplayArea(0, 1024, -2048, 2048);
        m_gltimePlot->settings.title = "IQ samples";
        m_gltimePlot->series[0]->color = 0xFF0000FF;
        m_gltimePlot->series[1]->color = 0x0000FFFF;
        m_gltimePlot->series[2]->color = 0xFF00FFFF;
        m_gltimePlot->series[3]->color = 0x00FFFFFF;
        m_gltimePlot->settings.marginLeft = 35;

    m_glconstellationPlot->settings.useVBO = true;
        m_glconstellationPlot->AddSerie(new cDataSerie());
        m_glconstellationPlot->AddSerie(new cDataSerie());
        m_glconstellationPlot->series[0]->color = 0xFF0000FF;
        m_glconstellationPlot->series[1]->color = 0xFF00FFFF;
        m_glconstellationPlot->SetInitialDisplayArea(-2048, 2048, -2048, 2048);
        m_glconstellationPlot->SetDrawingMode(GLG_POINTS);
        m_glconstellationPlot->settings.title = "I versus Q";
        m_glconstellationPlot->settings.titleXaxis = "I";
        m_glconstellationPlot->settings.titleYaxis = "Q";
        m_glconstellationPlot->settings.gridXlines = 8;
        m_glconstellationPlot->settings.gridYlines = 8;
        m_glconstellationPlot->settings.marginLeft = 35;

    m_glFFTplot->settings.useVBO = true;
        m_glFFTplot->AddSerie(new cDataSerie());
        m_glFFTplot->AddSerie(new cDataSerie());
        m_glFFTplot->series[0]->color = 0xFF0000FF;
        m_glFFTplot->series[1]->color = 0xFF00FFFF;
        m_glFFTplot->SetDrawingMode(GLG_LINE);
        m_glFFTplot->settings.gridXlines = 15;
        m_glFFTplot->SetInitialDisplayArea(-5000000, 5000000, -70, 70);

        m_glFFTplot->settings.title = "FFT";
        m_glFFTplot->settings.titleXaxis = "Frequency";
        m_glFFTplot->settings.titleYaxis = "Amplitude (dB)";
        m_glFFTplot->settings.xUnits = "Hz";
        //m_glFFTplot->settings.yUnits = "dB";
        m_glFFTplot->settings.markersEnabled = true;

        m_glFFTplot->settings.marginLeft = 35;
        m_glFFTplot->settings.staticGrid = true;

        m_glFFTplot->Refresh();
    OnChannelSelectionSelect(evt);
#ifdef NOVENA
    fpga_init();
#endif
}

pnlFFTviewer::~pnlFFTviewer()
{
    StopCapturing();
    SaveConfig();
    if(m_collector)
        delete m_collector;
    if(m_calculator)
        delete m_calculator;
    if(m_plotThread)
        delete m_plotThread;
    //(*Destroy(pnlFFTviewer)
    //*)
}

void pnlFFTviewer::OnQuit(wxCommandEvent& event)
{
    wxCloseEvent evt;
    OnClose(evt);
    printf("Quitting\n");
}

void pnlFFTviewer::switchGUIEnables(bool dataReading)
{
    txtSamplingFreq->Enable(!dataReading);
    txtFFTsize->Enable(!dataReading);
    btnSamplingFreqRatio->Enable(!dataReading);
    chkSaveStreamToFile->Enable(!dataReading);
}

void pnlFFTviewer::OnbtnStartStopClick(wxCommandEvent& event)
{
    if(m_dataReading == false) //start process
    {
        bool saveTofile = chkSaveStreamToFile->IsChecked();
        wxString filename;
        if(saveTofile)
        {
            wxFileDialog dlg(this, _("Save file for stream data"), "", "", "binary (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            if (dlg.ShowModal() == wxID_CANCEL)
                return;
            filename = dlg.GetPath();
        }
        long fftsize = 0;
        txtFFTsize->GetValue().ToLong(&fftsize);
        if(m_samplesChannels)
            delete m_samplesChannels;
        m_samplesChannels = new BlockingFIFO<SamplesPacket>();
        if(m_fftOutputs)
            delete m_fftOutputs;
        m_fftOutputs = new BlockingFIFO<FFTPacket>();
        if(m_collector)
            delete m_collector;
        m_collector = new SamplesCollector(m_serPort, m_samplesChannels);
        if(lmsControl && cmbBoardType->GetSelection() != 3)
            m_collector->frameStart = !lmsControl->GetParam(lms6::MISC_CTRL_9);
        else
            m_collector->frameStart = rgrFrameStart->GetSelection();
        m_collector->SwitchSource((eBOARD_FFT_SOURCE)cmbBoardType->GetSelection());
        m_extraControls->SetSamplesCollector(m_collector);
        m_collector->m_dataSource = m_extraControls->rxDataSource->GetSelection() ? 3 : 0;
        if(m_calculator)
            delete m_calculator;
        m_calculator = new FFTcalculator(m_samplesChannels, m_fftOutputs, CHANNEL_COUNT);

        m_samplesChannels->setLength(128, 2*fftsize);
        m_fftOutputs->setLength(8, 2*fftsize);

        m_redrawsDone = 0;
        if(m_plotThread)
            delete m_plotThread;
        m_plotThread = new PlotUpdateThread(this);

        m_collector->SetPacketSize(2*fftsize);
        double filelimit = 0;
        spinFilelimit->GetValue().ToDouble(&filelimit);
        m_collector->SetWriteToFile(saveTofile, filename.c_str(), filelimit*1000000);
        m_calculator->SetFFTsize(fftsize);
        m_plotThread->SetFFTsize(fftsize);
        double Fs = 0;
        txtSamplingFreq->GetValue().ToDouble(&Fs);
        m_calculator->SetSamplingFrequency(Fs*btnSamplingFreqRatio->GetRatio());
        m_plotThread->SetSamplingFrequency(Fs*btnSamplingFreqRatio->GetRatio());
        m_calculator->SetDCcorrection(chkDCcorrection->IsChecked());
        wxCommandEvent temp_evt;
        OnspinAvgChange(temp_evt);
        //m_calculator->SetAveragingCount(spinAverageCount->GetValue(), chkCalcAverage->IsChecked());
        if( m_serPort->IsOpen() == false)
        {
            wxMessageDialog dlg(this, "Device not connected!", "Error", wxOK);
            dlg.ShowModal();
            return;
        }

        m_samplesChannels->reset();
        m_fftOutputs->reset();

        //start samples collector
        wxCheckBox *usbRst = (wxCheckBox*)m_extraControls->FindWindow("chkUSBFIFOReset");
        if(usbRst)
        {
            if(usbRst->IsChecked() && m_serPort->GetConnectedDeviceType() == LMS_DEV_DIGIGREEN)
            {
                unsigned char out[64];
                long length = 64;
                memset(out, 0x00, length);
                out[0] = 0x40;
                out[1] = 0x10;
                out[2] = 1;
                //m_serPort->Port_write_direct(out, length);
                //m_serPort->Port_read_direct(out, length);
            }
        }
        if(m_collector->StartSampling() != true)
        {
            return;
        }
        //start fft calculations
        if(m_calculator->Start() != true)
        {
            delete m_plotThread;
            m_plotThread = NULL;
            m_collector->StopSampling();
            return;
        }
        //start graphs drawing
        if(m_plotThread->Run() != wxTHREAD_NO_ERROR)
        {
            delete m_plotThread;
            m_plotThread = NULL;
            m_collector->StopSampling();
            m_calculator->Stop();
            return;
        }
        m_dataReading = true;
        btnStartStop->SetLabel("STOP");
        rgrFrameStart->Enable(false);
    }
    else //stop process
    {
        m_plotThread->Stop();
        m_calculator->Stop();
        m_collector->StopSampling();
        m_dataReading = false;
        btnStartStop->SetLabel("START");
        if(cmbBoardType->GetSelection() == 3)
            rgrFrameStart->Enable(true);
    }
    switchGUIEnables(m_dataReading);
}

void pnlFFTviewer::OnThreadUpdatePlots(wxThreadEvent &evt)
{
    //printf("THREAD UPDATE EVENT\n");
    if(m_collector == NULL || m_calculator == NULL)
        return;

    t2 = getMilis();
    if(t2 - t1 >= 1000)
    {
        float fps = 0;
        fps = (1000.0*m_redrawsDone)/(t2-t1);
        m_redrawsDone = 0;
        t1 = t2;

        float dataRate = m_collector->m_dataRate;
        if(dataRate > 1000000)
            m_lblDatarate->SetLabel(wxString::Format("%.1f MiB/s", dataRate/1048576.0));
        else if(dataRate > 1000)
            m_lblDatarate->SetLabel(wxString::Format("%.1f KiB/s", dataRate/1024.0));
        else
            m_lblDatarate->SetLabel(wxString::Format("%.1f B/s", dataRate));
        m_lblFFTperSecond->SetLabel(wxString::Format("%.1f", m_calculator->GetFFTrate()));
        m_lblUpdatePerSecond->SetLabel(wxString::Format("%.1f", fps));
    }
}

void pnlFFTviewer::SaveConfig()
{
    //save all gui settings to file
    m_options.SelectSection("fft_parameters");
    m_options.Set("fft_size", txtFFTsize->GetValue().ToAscii());
    m_options.Set("sampling_freq", txtSamplingFreq->GetValue().ToAscii());
    m_options.Set("sampling_freq_10power", btnSamplingFreqRatio->GetPower());
    m_options.Set("calculate_average", chkCalcAverage->GetValue());
    m_options.Set("average_count", spinAvg->GetValue());
    m_options.Set("dc_correction", chkDCcorrection->GetValue());
    m_options.SelectSection("GUI options");
    m_options.Set("channel_selection", cmbChannelSelection->GetSelection());
    m_options.Set("show_fft", chkShowFFT->GetValue());
    m_options.Set("show_constellation", chkShowConstellation->GetValue());
    m_options.SelectSection("oscilloscope");
    m_options.Set("center_frequency", m_txtCenterFreq->GetValue());
    m_options.Set("center_frequency_10power", btnCenterFreqRatio->GetPower());
    m_options.Set("span", m_txtFreqSpan->GetValue());
    m_options.Set("span_10power", btnFreqSpanRatio->GetPower());
    m_options.Save(config_filename);
}

void pnlFFTviewer::OnClose(wxCloseEvent& event)
{
    StopCapturing();
    SaveConfig();
    Destroy();
}

void pnlFFTviewer::OnChannelSelectionSelect(wxCommandEvent& event)
{
    int chsel = cmbChannelSelection->GetSelection();
    if( chsel == 0)
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = true;
            m_glconstellationPlot->series[1]->visible = false;
            m_gltimePlot->series[0]->visible = true;
            m_gltimePlot->series[1]->visible = true;
            m_gltimePlot->series[2]->visible = false;
            m_gltimePlot->series[3]->visible = false;
            m_glFFTplot->series[0]->visible = true;
            m_glFFTplot->series[1]->visible = false;
            if(m_calculator)
                m_calculator->EnableChannels(0x1);
        }
    }
    else if( chsel == 1)
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = false;
            m_glconstellationPlot->series[1]->visible = true;
            m_gltimePlot->series[0]->visible = false;
            m_gltimePlot->series[1]->visible = false;
            m_gltimePlot->series[2]->visible = true;
            m_gltimePlot->series[3]->visible = true;
            m_glFFTplot->series[0]->visible = false;
            m_glFFTplot->series[1]->visible = true;
            if(m_calculator)
                m_calculator->EnableChannels(0x2);
        }
    }
    else
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = true;
            m_glconstellationPlot->series[1]->visible = true;
            m_gltimePlot->series[0]->visible = true;
            m_gltimePlot->series[1]->visible = true;
            m_gltimePlot->series[2]->visible = true;
            m_gltimePlot->series[3]->visible = true;
            m_glFFTplot->series[0]->visible = true;
            m_glFFTplot->series[1]->visible = true;
            if(m_calculator)
                m_calculator->EnableChannels(0x3);
        }
    }
    m_glconstellationPlot->Draw();
    m_glFFTplot->Draw();
    m_gltimePlot->Draw();
}

void pnlFFTviewer::OnChangePlotVisibility(wxCommandEvent& event)
{
    if(!chkShowConstellation->IsChecked() && !chkShowFFT->IsChecked())
    {
        if(event.GetEventObject() == chkShowFFT)
            chkShowConstellation->SetValue(true);
        else
            chkShowFFT->SetValue(true);
    }
    bool iqplot = chkShowConstellation->IsChecked();
    bool fftplot = chkShowFFT->IsChecked();

    m_plotSplitter->Unsplit();
    if(iqplot && fftplot)
    {
        m_plotSplitter->SplitHorizontally(Panel1, Panel2);
        Panel1->Show(true);
        Panel2->Show(true);
        Panel1->Enable(true);
        Panel2->Enable(true);
    }
    else if(iqplot && !fftplot)
    {
        Panel1->Show(true);
        Panel1->Enable(true);
        Panel2->Show(false);
        Panel2->Enable(false);
    }
    else if(!iqplot && fftplot)
    {
        m_plotSplitter->ReplaceWindow( m_plotSplitter->GetWindow1(), Panel2);
        Panel2->Show(true);
        Panel2->Enable(true);
        Panel1->Show(false);
        Panel1->Enable(false);
    }
    else
    {
        m_plotSplitter->SplitHorizontally(Panel1, Panel2);
        Panel1->Show(true);
        Panel2->Show(true);
        Panel1->Enable(true);
        Panel2->Enable(true);
    }
    Panel1->Update();
    Panel2->Update();
}

void pnlFFTviewer::OnCenterSpanChange(wxCommandEvent& event)
{
    double dFreq = 0;
    double dSpan = 0;
    m_txtCenterFreq->GetValue().ToDouble(&dFreq);
    dFreq *= btnCenterFreqRatio->GetRatio();
    m_txtFreqSpan->GetValue().ToDouble(&dSpan);
    dSpan *= btnFreqSpanRatio->GetRatio();
    m_glFFTplot->ZoomX(dFreq, dSpan);
}

void pnlFFTviewer::OnYaxisChange(wxCommandEvent& event)
{
    double dFreq = 0;
    double dSpan = 0;
    m_txtCenterFreq->GetValue().ToDouble(&dFreq);
    dFreq *= btnCenterFreqRatio->GetRatio();
    m_txtFreqSpan->GetValue().ToDouble(&dSpan);
    dSpan *= btnFreqSpanRatio->GetRatio();
    double ymin = 0;
    double ymax = 0;
    txtYaxisBottom->GetValue().ToDouble(&ymin);
    txtYaxisTop->GetValue().ToDouble(&ymax);
    m_glFFTplot->ZoomY((ymax+ymin)/2, abs(ymax-ymin));
}

void pnlFFTviewer::OnchkDCcorrectionClick(wxCommandEvent& event)
{
    if(m_calculator)
        m_calculator->SetDCcorrection(chkDCcorrection->IsChecked());
}

void pnlFFTviewer::OnbtnRefreshClick(wxCommandEvent& event)
{
    m_glFFTplot->Refresh();
}

void pnlFFTviewer::OnbtnExtraControlsClick(wxCommandEvent& event)
{
    if(m_extraControls == NULL)
        m_extraControls = new dlgExtraControls(this, m_serPort);
    m_extraControls->Show();
}

void pnlFFTviewer::OncmbWindowFunctionSelected(wxCommandEvent& event)
{
    if(m_calculator)
        m_calculator->SetWindowFunction(cmbWindowFunction->GetSelection());
}

void pnlFFTviewer::StopCapturing()
{
    if(m_dataReading) //stop data reading before closing window
    {
        wxCommandEvent evt;
        OnbtnStartStopClick(evt);
    }
}

void pnlFFTviewer::OnspinAvgChange(wxCommandEvent& event)
{
    long avgCount = 0;
    spinAvg->GetValue().ToLong(&avgCount);
    if(avgCount <= 0)
    {
        avgCount = 1;
        spinAvg->SetValue("1");
    }
    if(m_calculator)
        m_calculator->SetAveragingCount(avgCount, chkCalcAverage->IsChecked());
}

void pnlFFTviewer::AssignControl(lms6::LMS6002_MainControl *pControl)
{
    lmsControl = pControl;
}

void pnlFFTviewer::SetBoardType(unsigned i)
{
    if(i < cmbBoardType->GetCount())
        cmbBoardType->SetSelection(i);
    if(i==3)
        rgrFrameStart->Enable(true);
    else
        rgrFrameStart->Enable(false);
}

void pnlFFTviewer::OncmbBoardTypeSelect(wxCommandEvent& event)
{
    SetBoardType(event.GetInt());
}
