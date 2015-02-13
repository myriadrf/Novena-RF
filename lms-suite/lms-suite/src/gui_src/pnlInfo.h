#ifndef PNLINFO_H
#define PNLINFO_H

//(*Headers(pnlInfo)
#include <wx/panel.h>
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)
#include "PluginPanel.h"
class ConnectionManager;

class pnlInfo: public wxPanel, public PluginPanel
{
	public:

		pnlInfo(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		void Initialize( ConnectionManager *pControl);
		virtual ~pnlInfo();
        virtual void UpdatePanel();

		//(*Declarations(pnlInfo)
		wxStaticText* StaticText2;
		wxStaticText* lblEXP_BOARD;
		wxStaticText* lblLMS_DEV;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* btnGetInfo;
		wxStaticText* lblFW;
		wxStaticText* StaticText5;
		wxStaticText* lblHW;
		wxStaticText* StaticText4;
		wxStaticText* lblProtocol;
		//*)

		//(*Identifiers(pnlInfo)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		//*)

		//(*Handlers(pnlInfo)
		void OnbtnGetInfoClick(wxCommandEvent& event);
		//*)

	protected:
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
