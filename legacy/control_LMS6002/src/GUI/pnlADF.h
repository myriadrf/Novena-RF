#ifndef PNLADF_H
#define PNLADF_H

//(*Headers(pnlADF)
#include <wx/panel.h>
class wxTextCtrl;
class wxStaticBoxSizer;
class wxComboBox;
class wxFlexGridSizer;
class wxSpinEvent;
class wxButton;
class wxSpinCtrl;
class wxStaticText;
class wxRadioBox;
//*)

class pnlADF: public wxPanel
{
	public:

		pnlADF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlADF();

		void SetGuiDefaults();

		//(*Declarations(pnlADF)
		wxRadioBox* rgrCPS_f;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxComboBox* cmbMOC_f;
		wxStaticText* StaticText15;
		wxComboBox* cmbMOC_i;
		wxStaticText* StaticText17;
		wxComboBox* cmbFL_f;
		wxComboBox* cmbLDP;
		wxRadioBox* rgrPDP_i;
		wxComboBox* cmbTC_i;
		wxRadioBox* rgrCR_i;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxComboBox* cmbCS2_f;
		wxRadioBox* rgrPD2_f;
		wxButton* btnCalcSend;
		wxStaticText* StaticText3;
		wxRadioBox* rgrCR_f;
		wxRadioBox* rgrPD2_i;
		wxComboBox* cmbABW;
		wxTextCtrl* txtFref;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxRadioBox* rgrPD1_f;
		wxRadioBox* rgrPDP_f;
		wxRadioBox* rgrPD1_i;
		wxComboBox* cmbCS1_f;
		wxStaticText* StaticText7;
		wxStaticText* lblFcomp;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxComboBox* cmbTC_f;
		wxSpinCtrl* spinNCnt;
		wxComboBox* cmbCS2_i;
		wxRadioBox* rgrCPS_i;
		wxComboBox* cmbFL_i;
		wxStaticText* StaticText6;
		wxComboBox* cmbCS1_i;
		wxSpinCtrl* spinRCnt;
		wxComboBox* cmbCPG;
		wxStaticText* StaticText19;
		wxTextCtrl* txtFvco;
		wxStaticText* StaticText9;
		wxStaticText* lblFvco;
		wxStaticText* StaticText11;
		//*)

	protected:

		//(*Identifiers(pnlADF)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX3;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX8;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX5;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX11;
		static const long ID_COMBOBOX12;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX13;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_RADIOBOX8;
		static const long ID_RADIOBOX9;
		static const long ID_RADIOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(pnlADF)
		void OnbtnCalcSendClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
