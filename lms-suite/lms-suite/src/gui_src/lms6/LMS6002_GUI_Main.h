/***************************************************************
 * Name:      LMS6002_GUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-04-14
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#ifndef LMS6002_GUIMAIN_H
#define LMS6002_GUIMAIN_H

//(*Headers(LMS6002_GUI_Main)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "PluginPanel.h"
#include "SignalHandler.h"
#include "dlgLogger.h"

#include <list>
namespace lms6
{
    class LMS6002_MainControl;
}

class pnlSystem;
class pnlTop;
class pnlTxPLL;
class pnlTxLPF;
class pnlRxFE;
class pnlADDC;
class pnlRxVGA2;
class pnlTxRF;
class pnlADF4002;
class pnlSi5356A;
class pnlSi5351C;
class pnlSPI;

class LMS6002_GUI_Main: public wxPanel, public PluginPanel, SignalHandler
{
    public:

        LMS6002_GUI_Main(wxWindow* parent,wxWindowID id = -1, lms6::LMS6002_MainControl* plmsControl=NULL);
        virtual ~LMS6002_GUI_Main();

        virtual void HandleMessage(const LMS_Message &msg);
        void UpdateAllPages();

        void PrintToLogWindow(const wxString txt);
    private:
        void AddTab(wxNotebookPage* tab, wxString title);
        bool RemoveTab(const long windowID);
        void DisplayReferenceClock(double clk_MHz);
        lms6::LMS6002_MainControl *lmsControl;
        dlgLogger *m_logger;
        std::list<wxString> m_logMessages;

        //(*Handlers(LMS6002_GUI_Main)
        void OnQuit(wxCommandEvent& event);
        void OnmnuNewSelected(wxCommandEvent& event);
        void OnmnuOpenSelected(wxCommandEvent& event);
        void OnmnuSaveSelected(wxCommandEvent& event);
        void OnmnuSaveAsSelected(wxCommandEvent& event);
        void OnmnuReadRVF_rfifSelected(wxCommandEvent& event);
        void OnmnuChipToGUISelected(wxCommandEvent& event);
        void OnmnuAboutSelected(wxCommandEvent& event);
        void OnmnuRefClkSelected(wxCommandEvent& event);
        void OnRegisterTestSelected(wxCommandEvent& event);
        void OnbtnShowLogClick(wxCommandEvent& event);
        void OnmnuGUIToChipSelected(wxCommandEvent& event);
        void OnbtnOpenClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(LMS6002_GUI_Main)
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_SYSTEM_TAB;
        static const long ID_TOP_TAB;
        static const long ID_TXPLL_TAB;
        static const long ID_RXPLL_TAB;
        static const long ID_TXLPF_TAB;
        static const long ID_TXRF_TAB;
        static const long ID_RXLPF_TAB;
        static const long ID_RXVGA2_TAB;
        static const long ID_RXFE_TAB;
        static const long ID_ADDC_TAB;
        static const long ID_LMS6_TABS;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT2;
        //*)

        //(*Declarations(LMS6002_GUI_Main)
        wxStaticText* lblVerRevMask;
        wxButton* btnRefClk;
        pnlADDC* m_ADDC;
        wxButton* btnSave;
        wxButton* GUI2Chip;
        pnlRxFE* m_RxFE;
        pnlTxLPF* m_TxLPF;
        pnlTxLPF* m_RxLPF;
        pnlTxRF* m_TxRF;
        pnlRxVGA2* m_RxVGA2;
        pnlTxPLL* m_RxPLL;
        pnlSystem* m_system;
        wxStaticText* lblRefClk;
        wxNotebook* pcSPIS;
        pnlTop* m_top;
        pnlTxPLL* m_TxPLL;
        wxTextCtrl* m_messageLogt;
        wxButton* btnRegisters;
        wxButton* btnShowLog;
        wxButton* Chip2GUI;
        wxStaticText* lblDevFwPr;
        wxButton* btnOpen;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // LMS6002_GUIMAIN_H
