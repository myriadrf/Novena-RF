#ifndef PNLMYRIADRF2_H
#define PNLMYRIADRF2_H

//(*Headers(pnlMyriadRF2)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)

#include "PluginPanel.h"

namespace lms6
{
    class LMS6002_MainControl;
}

class pnlMyriadRF2: public wxPanel, public PluginPanel
{
	public:

		pnlMyriadRF2(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlMyriadRF2();
        void Initialize(lms6::LMS6002_MainControl* pControl);
		//(*Declarations(pnlMyriadRF2)
		wxComboBox* cmbDTC1out;
		wxStaticText* StaticText14;
		wxCheckBox* chkSWC1out;
		wxStaticText* StaticText18;
		wxCheckBox* chkSWC1;
		wxCheckBox* chkSWC2out;
		wxCheckBox* chkSWC3out;
		wxComboBox* cmbLNAbypass;
		wxComboBox* cmbDTC2out;
		wxCheckBox* chkSWC2;
		wxComboBox* cmbDTC2in;
		wxStaticText* StaticText15;
		wxStaticText* StaticText17;
		wxStaticText* StaticText16;
		wxCheckBox* chkSWC3;
		wxComboBox* cmbDTC1in;
		//*)

	protected:

		//(*Identifiers(pnlMyriadRF2)
		static const long ID_STATICTEXT15;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT16;
		static const long ID_COMBOBOX3;
		static const long ID_CHECKBOX17;
		static const long ID_CHECKBOX18;
		static const long ID_CHECKBOX19;
		static const long ID_STATICTEXT17;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX5;
		static const long ID_CHECKBOX20;
		static const long ID_CHECKBOX21;
		static const long ID_CHECKBOX22;
		static const long ID_STATICTEXT14;
		static const long ID_COMBOBOX1;
		//*)

	private:

		//(*Handlers(pnlMyriadRF2)
        void configMyriadRF_PAIN(wxCommandEvent& event);
		void configMyriadRF_PAOUT(wxCommandEvent& event);
		void OncmbLNAbypassSelected(wxCommandEvent& event);
		//*)

	protected:
	    lms6::LMS6002_MainControl* lmsControl;
        void ConfigMyriadRF2(int id);
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
