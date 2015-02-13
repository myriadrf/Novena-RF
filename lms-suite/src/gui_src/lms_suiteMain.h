/***************************************************************
 * Name:      lms_suiteMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lime Microsystems ()
 * Created:   2014-09-08
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#ifndef LMS_SUITEMAIN_H
#define LMS_SUITEMAIN_H

//(*Headers(lms_suiteFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

#include <vector>
#include "PluginPanel.h"
#include "SignalHandler.h"
namespace lms6
{
    class LMS6002_MainControl;
}

class ConnectionManager;
class ADF_module;
class Si5351C;
class pnlSi5351C;
class Si5356A;
class pnlSi5356A;
class ADF_module;
class pnlADF4002;
class pnlMinimalControls;
class pnlSPI;
class LMS6002_GUI_Main;
class pnlMyriadRF2;
class pnlFFTviewer;
class pnlWFMLoader;
class pnlProgramming;
class pnlNovena;
class pnlHPM1000;
class pnlInfo;

class lms_suiteFrame: public wxFrame, public SignalHandler
{
    public:
        virtual void HandleMessage(const LMS_Message &msg);
        lms_suiteFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~lms_suiteFrame();

        int InitializeWorkingSettings();
        int SetAvailableModules(unsigned long ePluginsConfiguration_flags);

    private:
        unsigned long m_pluginsConfiguration;
        lms6::LMS6002_MainControl* lms6ctrl;
        LMS6002_GUI_Main* pnl_lms6ctrl;
        ADF_module* adf_control;
        pnlADF4002* pnladf_control;
        pnlSPI* pnlspictrl;
        Si5351C* si5351ctrl;
        pnlSi5351C* pnlsi51;
        pnlSi5356A* pnlsi56;
        Si5356A* si5356ctrl;
        pnlFFTviewer* pnlfft;
        pnlMyriadRF2* myriadrf2ctrl;
        pnlMinimalControls* minCtrl;
        pnlWFMLoader* pnlwfm;
        pnlProgramming* pnlProg;
        pnlNovena* pnlNovenaBoard;
        pnlHPM1000* pnlHPM;
        pnlInfo* pnlGetInfo;
        ConnectionManager* m_serPort;
        std::vector<PluginPanel*> plugins;
        void OnPaneClose(wxAuiManagerEvent& event);
        //(*Handlers(lms_suiteFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnmenuConnectionSettingsSelected(wxCommandEvent& event);
        void OnShowModule(wxCommandEvent& event);
        void OncmbPluginsConfigSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(lms_suiteFrame)
        static const long ID_STATICTEXT1;
        static const long ID_COMBOBOX1;
        static const long ID_PANEL1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM6;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_MDIFRAME;

        //(*Declarations(lms_suiteFrame)
        wxMenu* Menu3;
        wxMenuItem* menuConnectionSettings;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxAuiManager* panelsManager;
        wxStatusBar* StatusBar1;
        wxComboBox* cmbPluginsConfig;
        wxMenu* Menu4;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // LMS_SUITEMAIN_H
