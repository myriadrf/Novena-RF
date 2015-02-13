#ifndef DLGABOUT_H
#define DLGABOUT_H

//(*Headers(dlgAbout)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/imaglist.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
//*)

class dlgAbout: public wxDialog
{
	public:

		dlgAbout(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~dlgAbout();

		//(*Declarations(dlgAbout)
		wxStaticBitmap* bmpLimeImg;
		wxButton* Button1;
		wxStaticText* StaticText1;
		wxHyperlinkCtrl* HyperlinkCtrl1;
		wxStaticText* lblVersion;
		wxImageList* ImageList1;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(dlgAbout)
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT14;
		static const long ID_HYPERLINKCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgAbout)
		void OnbtnOKClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
