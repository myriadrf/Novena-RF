/***************************************************************
 * Name:      FFTviewerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-02-27
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#ifndef PNL_FFT_VIEWER_H
#define PNL_FFT_VIEWER_H

#include "iniParser.h"
#include "UnitsButton.h"
#include "Packets.h"
#include "BlockingFIFO.h"
#include "oglGraph/OpenGLGraph.h"
#include "dlgExtraControls.h"
#include "PluginPanel.h"
//(*Headers(pnlFFTviewer)
#include <wx/panel.h>
class wxSplitterWindow;
class wxCheckBox;
class wxTextCtrl;
class wxNotebookEvent;
class wxSplitterEvent;
class wxComboBox;
class wxRadioBox;
class wxNotebook;
class wxStaticText;
class wxGLCanvas;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
class wxChoice;
//*)

class SamplesCollector;
class FFTcalculator;
class ConnectionManager;
class PlotUpdateThread;
class dlgMarkers;
class ConnectionManager;
namespace lms6
{
class LMS6002_MainControl;
}

wxDECLARE_EVENT(wxEVT_COMMAND_THREAD_UPDATE, wxThreadEvent);

class pnlFFTviewer: public wxPanel, public PluginPanel
{
    friend class PlotUpdateThread;
    public:

        pnlFFTviewer(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id = -1);
        void AssignControl(lms6::LMS6002_MainControl *pControl);
        virtual ~pnlFFTviewer();
        wxCriticalSection m_dataCS;
        SamplesCollector *getSamplesCollector() { return m_collector; };
        void SaveConfig();
        void StopCapturing();
        void SetBoardType(unsigned i);
    private:
        long t1,t2;

        BlockingFIFO<SamplesPacket> *m_samplesChannels;
        BlockingFIFO<FFTPacket> *m_fftOutputs;
        dlgMarkers *m_dlgMarkers;
        PlotUpdateThread *m_plotThread;
        iniParser m_options;
        void RefreshDeviceList(wxCommandEvent &evt);
        void OnThreadUpdatePlots(wxThreadEvent& evt);
        bool m_dataReading;
        void switchGUIEnables(bool dataReading);

        lms6::LMS6002_MainControl *lmsControl;
        ConnectionManager *m_serPort;
        SamplesCollector *m_collector;
        FFTcalculator *m_calculator;
        unsigned long m_redrawsDone;

        dlgExtraControls *m_extraControls;

        //(*Handlers(pnlFFTviewer)
        void OnQuit(wxCommandEvent& event);
        void OnbtnStartStopClick(wxCommandEvent& event);
        void OncmbDeviceListSelected(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnChannelSelectionSelect(wxCommandEvent& event);
        void OnChangePlotVisibility(wxCommandEvent& event);
        void OnbtnConnectionSettingsClick(wxCommandEvent& event);
        void OnCenterSpanChange(wxCommandEvent& event);
        void OnYaxisChange(wxCommandEvent& event);
        void OnchkDCcorrectionClick(wxCommandEvent& event);
        void OnchkCalcAverageClick(wxCommandEvent& event);
        void OnspinAverageCountChange(wxSpinEvent& event);
        void OntxtMark0FreqText(wxCommandEvent& event);
        void OntxtMark1FreqTextEnter(wxCommandEvent& event);
        void OnchkMarkerEnableClick(wxCommandEvent& event);
        void OnbtnOpenMarkersClick(wxCommandEvent& event);
        void OnbtnRefreshClick(wxCommandEvent& event);
        void OnbtnExtraControlsClick(wxCommandEvent& event);
        void OncmbWindowFunctionSelected(wxCommandEvent& event);
        void OnspinAvgChange(wxCommandEvent& event);
        void OncmbBoardTypeSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(pnlFFTviewer)
        static const long ID_GLCANVAS4;
        static const long ID_GLCANVAS5;
        static const long ID_PANEL1;
        static const long ID_GLCANVAS1;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL2;
        static const long ID_CHECKBOX1;
        static const long ID_TEXTCTRL7;
        static const long ID_CHECKBOX4;
        static const long ID_COMBOBOX1;
        static const long ID_BUTTON2;
        static const long ID_RADIOBOX1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_CHECKBOX6;
        static const long ID_STATICTEXT12;
        static const long ID_TEXTCTRL8;
        static const long ID_CHOICE1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX5;
        static const long ID_STATICTEXT10;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON3;
        static const long ID_STATICTEXT11;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT20;
        static const long ID_TEXTCTRL5;
        static const long ID_STATICTEXT19;
        static const long ID_TEXTCTRL6;
        static const long ID_BUTTON6;
        static const long ID_TAB_SPECTRUM;
        static const long ID_NOTEBOOK1;
        //*)

        //(*Declarations(pnlFFTviewer)
        wxStaticText* StaticText9;
        wxComboBox* cmbWindowFunction;
        wxChoice* cmbBoardType;
        wxTextCtrl* spinAvg;
        wxStaticText* m_lblFFTperSecond;
        wxCheckBox* chkShowFFT;
        UnitsButton* btnCenterFreqRatio;
        wxTextCtrl* m_txtCenterFreq;
        wxCheckBox* chkFreezeDrawing;
        wxStaticText* StaticText2;
        wxStaticText* m_lblUpdatePerSecond;
        OpenGLGraph* m_glconstellationPlot;
        wxStaticText* StaticText6;
        wxTextCtrl* m_txtFreqSpan;
        wxStaticText* StaticText8;
        UnitsButton* btnSamplingFreqRatio;
        wxNotebook* m_MainTabs;
        wxButton* btnExtraControls;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxCheckBox* chkSaveStreamToFile;
        OpenGLGraph* m_gltimePlot;
        wxStaticText* m_lblDatarate;
        wxTextCtrl* txtYaxisBottom;
        wxCheckBox* chkDCcorrection;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxRadioBox* rgrFrameStart;
        wxTextCtrl* txtFFTsize;
        wxPanel* m_tabSpectrum;
        wxButton* btnStartStop;
        wxTextCtrl* txtYaxisTop;
        wxStaticText* StaticText15;
        wxTextCtrl* spinFilelimit;
        wxCheckBox* chkShowConstellation;
        wxPanel* Panel2;
        UnitsButton* btnFreqSpanRatio;
        wxChoice* cmbChannelSelection;
        wxCheckBox* chkCalcAverage;
        wxTextCtrl* txtSamplingFreq;
        wxSplitterWindow* m_plotSplitter;
        OpenGLGraph* m_glFFTplot;
        wxStaticText* StaticText17;
        wxStaticText* StaticText4;
        wxStaticText* StaticText16;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SAMPLESTESTERMAIN_H
