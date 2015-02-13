#ifndef PNLSI5356A_H
#define PNLSI5356A_H

//(*Headers(pnlSi5356A)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "PluginPanel.h"

class ConnectionManager;
class Si5356A;

class pnlSi5356A: public wxPanel, public PluginPanel
{
	public:

		pnlSi5356A(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlSi5356A();
		void Initialize(Si5356A *pControl);

		//(*Declarations(pnlSi5356A)
		wxTextCtrl* txtDRVAfreq;
		wxRadioBox* rgrDRVCoutput;
		wxTextCtrl* txtDRVDfreq;
		wxButton* btnLoadFile;
		wxRadioBox* rgrRefClkSelect;
		wxTextCtrl* txtRefClk;
		wxTextCtrl* txtDRVCfreq;
		wxStaticText* StaticText1;
		wxCheckBox* chkDRVAInvertEven;
		wxStaticText* StaticText3;
		wxCheckBox* chkDRVCInvertOdd;
		wxRadioBox* rgrDRVAoutput;
		wxCheckBox* chkDRVDen;
		wxTextCtrl* txtDRVBfreq;
		wxStaticLine* StaticLine4;
		wxStaticLine* StaticLine2;
		wxCheckBox* chkDRVBen;
		wxCheckBox* chkDRVAen;
		wxRadioBox* rgrCrystalFreq;
		wxCheckBox* chkDRVDInvertEven;
		wxStaticText* StaticText5;
		wxCheckBox* chkDRVBInvertEven;
		wxCheckBox* chkDRVCen;
		wxStaticLine* StaticLine3;
		wxStaticLine* StaticLine1;
		wxButton* btnConfigureClock;
		wxCheckBox* chkDRVDInvertOdd;
		wxStaticText* StaticText4;
		wxCheckBox* chkDRVBInvertOdd;
		wxRadioBox* rgrDRVDoutput;
		wxRadioBox* rgrDRVBoutput;
		wxCheckBox* chkDRVAInvertOdd;
		wxCheckBox* chkDRVCInvertEven;
		//*)

	protected:

		//(*Identifiers(pnlSi5356A)
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_RADIOBOX6;
		static const long ID_TEXTCTRL2;
		static const long ID_RADIOBOX5;
		static const long ID_CHECKBOX4;
		static const long ID_STATICLINE1;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_RADIOBOX1;
		static const long ID_CHECKBOX5;
		static const long ID_STATICLINE2;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX6;
		static const long ID_RADIOBOX2;
		static const long ID_CHECKBOX7;
		static const long ID_STATICLINE3;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_RADIOBOX3;
		static const long ID_CHECKBOX8;
		static const long ID_STATICLINE4;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL5;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_RADIOBOX4;
		//*)

	private:

		//(*Handlers(pnlSi5356A)
		void OnbtnLoadFileClick(wxCommandEvent& event);
		void OnbtnConfigureClockClick(wxCommandEvent& event);
		//*)

	protected:
        Si5356A *m_controlModule;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
