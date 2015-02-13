#ifndef FRCONTROLPANEL_H
#define FRCONTROLPANEL_H

#include "pnlTop.h"
#include "pnlTxPLL.h"
#include "pnlTxRF.h"
#include "pnlTxLPF.h"
#include "pnlRxLPF.h"
#include "pnlRxVGA2.h"
#include "pnlADDC.h"
#include "pnlRxFE.h"
#include "pnlRxPLL.h"
#include "pnlCustomer.h"
#include "pnlADF.h"
#include "pnlBoard.h"
#include <wx/toolbar.h>
#include "dlgSerPort.h"

//(*Headers(frControlPanel)
#include <wx/frame.h>
class wxToolBar;
class wxMenu;
class wxNotebook;
class wxFlexGridSizer;
class wxStatusBar;
class wxMenuBar;
class wxFileDialog;
class wxNotebookEvent;
class wxRichTextCtrl;
class wxPanel;
//*)

class frControlPanel: public wxFrame
{
	public:

		frControlPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~frControlPanel();

		void FileNew1Execute(wxCommandEvent& event);
        void FileOpen1Execute(wxCommandEvent& event);
        void Save(wxCommandEvent& event);
        void FileExit1Execute(wxCommandEvent& event);
        void HelpAbout1Execute(wxCommandEvent& event);
        void FormCreate(wxCommandEvent& event);
        void mnuAutoDwnldClick(wxCommandEvent& event);
        void mnuReadConfigurationClick(wxCommandEvent& event);
        void tbtnDownloadClick(wxCommandEvent& event);
        void FileSaveAsItemClick(wxCommandEvent& event);
        void mnuRefClkClick(wxCommandEvent& event);

        void ChipGUI1Click(wxCommandEvent& event);
        void mnuSaveRegistersClick(wxCommandEvent& event);
        void ChipGUI2Click(wxCommandEvent& event);
        void CommunicationSettings1Click(wxCommandEvent& event);
        void RegisterTest1Click(wxCommandEvent& event);
        void mnuRegTestLongClick(wxCommandEvent& event);
        void mnuReadRVFClick(wxCommandEvent& event);
        void mnuReadRVF_hexClick(wxCommandEvent& event);
        void mnuReadRVF_rfifClick(wxCommandEvent& event);

        void slLogMesg(char *msg);
        void slLogMesg(int num);
        static void UpdateInterface(int code, char *opt_Msg);
        static int UpdateMessageLog();
        static void ReceivePopUpMessage(char *msg);
        static void ReceiveLogMessage(char *msg);

		//(*Declarations(frControlPanel)
		wxMenuItem* mnuAbout;
		wxToolBarToolBase* tbtnDownload;
		wxMenuItem* CommunicationSettings1;
		pnlTxRF* m_TxRF;
		wxMenuItem* RegisterTest1;
		wxMenu* Menu1;
		pnlRxVGA2* m_RxVGA2;
		wxFileDialog* dlgOpen;
		pnlRxFE* m_RxFE;
		wxMenuItem* mnuReadRVF_rfif;
		wxMenu* Menu3;
		pnlTxLPF* m_TxLPF;
		pnlADF* m_ADF;
		pnlRxLPF* m_RxLPF;
		wxMenuItem* mnuNew;
		wxStatusBar* sbMain;
		wxMenuItem* mnuOpen;
		wxToolBarToolBase* ToolBarItem2;
		pnlADDC* m_ADDC;
		wxMenu* Menu4;
		wxMenuItem* mnuChipToGUI;
		wxMenuItem* mnuSave;
		wxToolBar* ToolBar1;
		pnlTop* m_top;
		wxToolBarToolBase* ToolBarItem1;
		wxMenuBar* MenuBar1;
		wxNotebook* pcSPIS;
		wxToolBarToolBase* ToolBarItem3;
		wxMenu* Menu2;
		wxMenuItem* mnuRefClk;
		pnlRxPLL* m_RxPLL;
		pnlCustomer* m_Customer;
		wxMenuItem* mnuAutoDwnld;
		wxRichTextCtrl* lbMsgs;
		pnlBoard* m_Board;
		pnlTxPLL* m_TxPLL;
		wxMenuItem* mnuSaveAs;
		//*)

	protected:

		//(*Identifiers(frControlPanel)
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_PANEL4;
		static const long ID_PANEL5;
		static const long ID_PANEL6;
		static const long ID_PANEL7;
		static const long ID_PANEL8;
		static const long ID_PANEL9;
		static const long ID_PANEL10;
		static const long ID_PANEL11;
		static const long ID_PANEL13;
		static const long ID_PANEL1;
		static const long ID_NOTEBOOK1;
		static const long ID_RICHTEXTCTRL1;
		static const long ID_MENUITEM1;
		static const long ID_MENUITEM2;
		static const long ID_MENUITEM3;
		static const long ID_MENUITEM4;
		static const long ID_MENUITEM9;
		static const long ID_MENUITEM10;
		static const long ID_MENUITEM5;
		static const long ID_MENUITEM6;
		static const long ID_MENUITEM7;
		static const long ID_MENUITEM8;
		static const long ID_MENUITEM11;
		static const long ID_TOOLBARITEM1;
		static const long ID_TOOLBARITEM2;
		static const long ID_TOOLBARITEM3;
		static const long ID_TOOLBARITEM4;
		static const long ID_TOOLBAR1;
		static const long ID_STATUSBAR1;
		//*)

	private:

		//(*Handlers(frControlPanel)
		void OnmnuNewSelected(wxCommandEvent& event);
		void OnmnuOpenSelected(wxCommandEvent& event);
		void OnmnuSaveSelected(wxCommandEvent& event);
		void OnmnuSaveAsSelected(wxCommandEvent& event);
		void OnmnuAutoDwnldSelected(wxCommandEvent& event);
		void OnCommunicationSettings1Selected(wxCommandEvent& event);
		void OnRegisterTest1Selected(wxCommandEvent& event);
		void OnmnuAboutSelected(wxCommandEvent& event);
		void OntbtnDownloadClicked(wxCommandEvent& event);
		void OnmnuAutoDwnldSelected1(wxCommandEvent& event);
		void OnCommunicationSettings1Selected1(wxCommandEvent& event);
		void OnmnuRefClkSelected1(wxCommandEvent& event);
		void OnmnuChipToGUISelected(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnpcSPISPageChanging(wxNotebookEvent& event);
		void OnmnuReadRVFSelected(wxCommandEvent& event);
		void OnmnuReadRVF_hexSelected(wxCommandEvent& event);
		void OnmnuReadRVF_rfifSelected(wxCommandEvent& event);
		void OnmnuSaveRegistersSelected(wxCommandEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		//*)

		dlgSerPort *dSerPort;

        bool sendChanges;
        wxString m_sFileName;

        void setCurrentFileName(wxString fileName);
        void EnableAllSPIClocks();
        void EnableSPIClockByMask(int Mask);
        void RestoreAllSPIClocks();
        void SetLnaChain(int iChain);
        void SetBypassLoopback();
        bool TestRegisters();
        bool TestRegistersTrial();
        void CalLPFCore();

        bool FileIsNotEmpty(wxString filename);
        void LoadConfiguration(wxString sIniName);

        void ShowReferenceClk(double Val);
        void SaveRefClkToReg(double Freq);
        double ReadRefClkFromReg(void);

        void LoadAdditionalSettings();
        void UpdateVerRevMask();
        void DevicesChanged();

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
