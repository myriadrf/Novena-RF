#ifndef PNLWFMLOADER_H
#define PNLWFMLOADER_H

//(*Headers(pnlWFMLoader)
#include <wx/panel.h>
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)

#include "PluginPanel.h"

class ConnectionManager;

class pnlWFMLoader: public wxPanel, public PluginPanel
{
	public:

		pnlWFMLoader(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlWFMLoader();

		//(*Declarations(pnlWFMLoader)
		wxButton* btnUpload;
		wxButton* btnHex;
		wxStaticText* StaticText2;
		wxStaticText* txtFilename;
		wxButton* btnMif;
		wxButton* btnOpenFile;
		//*)

	protected:

		//(*Identifiers(pnlWFMLoader)
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(pnlWFMLoader)
		void OnbtnUploadClick(wxCommandEvent& event);
		void OnbtnOpenFileClick(wxCommandEvent& event);
		void OnbtnMifClick(wxCommandEvent& event);
		void OnbtnHexClick(wxCommandEvent& event);
		//*)

	protected:
        ConnectionManager* m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
