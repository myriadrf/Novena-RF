#ifndef DLGLOGGER_H
#define DLGLOGGER_H

//(*Headers(dlgLogger)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class dlgLogger: public wxDialog
{
	public:

		dlgLogger(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgLogger();

		void write(const wxString &str);

		//(*Declarations(dlgLogger)
		wxButton* btnSave;
		wxCheckBox* chkWARNINGS;
		wxCheckBox* chkDATA;
		wxButton* btnClear;
		wxCheckBox* chkERRORS;
		wxCheckBox* chkINFO;
		wxRichTextCtrl* txtTextField;
		//*)

	protected:

		//(*Identifiers(dlgLogger)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(dlgLogger)
		void OnbtnSaveClick(wxCommandEvent& event);
		void OnbtnClearClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnChangeFilter(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
