// -----------------------------------------------------------------------------
// FILE: 		dlgFloatInput.h
// DESCRIPTION:
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef DLGFLOATINPUT_H
#define DLGFLOATINPUT_H

//(*Headers(dlgFloatInput)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class dlgFloatInput: public wxDialog
{
	public:

		dlgFloatInput(wxWindow* parent, const wxString &message, const wxString &title, double defValue = 0);
		virtual ~dlgFloatInput();
		double GetValue();

		//(*Declarations(dlgFloatInput)
		wxStaticText* txtMessage;
		wxTextCtrl* txtFloatInput;
		wxButton* btnCancel;
		wxButton* btnOK;
		//*)

	protected:

		//(*Identifiers(dlgFloatInput)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(dlgFloatInput)
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		//*)

	protected:
		void BuildContent(wxWindow* parent, const wxString &message, const wxString &title);
		wxString m_floatString;

		DECLARE_EVENT_TABLE()
};

#endif
