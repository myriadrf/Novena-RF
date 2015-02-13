#ifndef PNLPROGRAMMING_H
#define PNLPROGRAMMING_H

//(*Headers(pnlProgramming)
#include <wx/panel.h>
class wxGauge;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxChoice;
//*)

#include "SignalHandler.h"
#include "PluginPanel.h"
class Programmer;
class ConnectionManager;

class pnlProgramming: public wxPanel, public PluginPanel, public SignalHandler
{
	public:
        virtual void HandleMessage(const LMS_Message &msg);
		pnlProgramming(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlProgramming();

		//(*Declarations(pnlProgramming)
		wxStaticText* lblProgressPercent;
		wxChoice* cmbDevice;
		wxStaticText* StaticText2;
		wxGauge* progressBar;
		wxStaticText* lblFilename;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxChoice* cmbProgMode;
		wxButton* btnProgram;
		wxButton* btnOpen;
		//*)

	protected:
	    Programmer* m_programmer;
		//(*Identifiers(pnlProgramming)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT6;
		static const long ID_CHOICE2;
		static const long ID_CHOICE1;
		static const long ID_BUTTON2;
		static const long ID_GAUGE1;
		static const long ID_STATICTEXT5;
		//*)

	private:

		//(*Handlers(pnlProgramming)
		void OnbtnOpenClick(wxCommandEvent& event);
		void OnbtnProgMyriadClick(wxCommandEvent& event);
		void OnbtnProgFPGAClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
