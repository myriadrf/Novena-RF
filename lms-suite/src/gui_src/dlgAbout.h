#ifndef DLGABOUT_H
#define DLGABOUT_H

//(*Headers(dlgAbout)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class dlgAbout: public wxDialog
{
	public:

		dlgAbout(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgAbout();

		//(*Declarations(dlgAbout)
		wxButton* btnClose;
		wxStaticBitmap* StaticBitmap1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* txtDescription;
		wxStaticText* txtVersion;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(dlgAbout)
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgAbout)
		void OnbtnCloseClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
