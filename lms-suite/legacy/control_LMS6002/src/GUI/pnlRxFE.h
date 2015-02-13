#ifndef PNLRXFE_H
#define PNLRXFE_H

//(*Headers(pnlRxFE)
#include <wx/panel.h>
class wxStaticBoxSizer;
class wxComboBox;
class wxFlexGridSizer;
class wxStaticText;
class wxRadioBox;
class wxCheckBox;
//*)

class pnlRxFE: public wxPanel
{
	public:

		pnlRxFE(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlRxFE();

        void FillComboBoxes();
		void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        bool UpdateGUI();

		//(*Declarations(pnlRxFE)
		wxComboBox* cmbIP2TRIM_I_RXFE;
		wxCheckBox* chkPD_MIX_RXFE;
		wxComboBox* cmbIN1SEL_MIX_RXFE;
		wxComboBox* cmbICT_MIX_RXFE;
		wxStaticText* StaticText13;
		wxStaticText* StaticText14;
		wxStaticText* StaticText15;
		wxStaticText* StaticText17;
		wxComboBox* cmbLNASEL_RXFE;
		wxComboBox* cmbG_LNA_RXFE;
		wxCheckBox* chkPD_TIA_RXFE;
		wxCheckBox* chkPD_LNA_RXFE;
		wxComboBox* cmbRFB_TIA_RXFE;
		wxCheckBox* chbPwrRxFeMods;
		wxComboBox* cmbICT_TIA_RXFE;
		wxStaticText* StaticText18;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxStaticText* StaticText16;
		wxStaticText* StaticText3;
		wxComboBox* cmbRDLEXT_LNA_RXFE;
		wxComboBox* cmbCFB_TIA_RXFE;
		wxCheckBox* chkXLOAD_LNA_RXFE;
		wxComboBox* cmbCBE_LNA_RXFE;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxStaticText* StaticText7;
		wxCheckBox* chkINLOAD_LNA_RXFE;
		wxStaticText* StaticText4;
		wxComboBox* cmbDCOFF_Q_RXFE;
		wxCheckBox* chkPD_MXLOB_RXFE;
		wxComboBox* cmbLOBN_MIX_RXFE;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxComboBox* cmbICT_MXLOB_RXFE;
		wxComboBox* cmbDCOFF_I_RXFE;
		wxStaticText* StaticText6;
		wxRadioBox* rgrDecode;
		wxComboBox* cmbRDLINT_LNA_RXFE;
		wxComboBox* cmbG_FINE_LNA3_RXFE;
		wxStaticText* StaticText9;
		wxStaticText* StaticText11;
		wxCheckBox* chkRINEN_MIX_RXFE;
		wxComboBox* cmbIP2TRIM_Q_RXFE;
		wxComboBox* cmbICT_LNA_RXFE;
		//*)

	protected:

		//(*Identifiers(pnlRxFE)
		static const long ID_RADIOBOX2;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_STATICTEXT1;
		static const long ID_CHECKBOX8;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX2;
		static const long ID_COMBOBOX3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX12;
		static const long ID_COMBOBOX13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_COMBOBOX14;
		static const long ID_COMBOBOX15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX16;
		static const long ID_COMBOBOX17;
		static const long ID_COMBOBOX18;
		//*)

	private:

		//(*Handlers(pnlRxFE)
        void rgrDecodeClick(wxCommandEvent& event);
        void chbPwrRxFeModsClick(wxCommandEvent& event);
        void cmbIN1SEL_MIX_RXFEChange(wxCommandEvent& event);
        void cmbDCOFF_I_RXFEChange(wxCommandEvent& event);
        void chkINLOAD_LNA_RXFEClick(wxCommandEvent& event);
        void cmbDCOFF_Q_RXFEChange(wxCommandEvent& event);
        void chkXLOAD_LNA_RXFEClick(wxCommandEvent& event);
        void cmbIP2TRIM_I_RXFEChange(wxCommandEvent& event);
        void cmbIP2TRIM_Q_RXFEChange(wxCommandEvent& event);
        void cmbG_LNA_RXFEChange(wxCommandEvent& event);
        void cmbLNASEL_RXFEChange(wxCommandEvent& event);
        void cmbCBE_LNA_RXFEChange(wxCommandEvent& event);
        void cmbRFB_TIA_RXFEChange(wxCommandEvent& event);
        void cmbCFB_TIA_RXFEChange(wxCommandEvent& event);
        void cmbRDLEXT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbRDLINT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbICT_MIX_RXFEChange(wxCommandEvent& event);
        void cmbICT_LNA_RXFEChange(wxCommandEvent& event);
        void cmbICT_TIA_RXFEChange(wxCommandEvent& event);
        void cmbICT_MXLOB_RXFEChange(wxCommandEvent& event);
        void cmbLOBN_MIX_RXFEChange(wxCommandEvent& event);
        void chkPD_TIA_RXFEClick(wxCommandEvent& event);
        void chkPD_MXLOB_RXFEClick(wxCommandEvent& event);
        void chkPD_MIX_RXFEClick(wxCommandEvent& event);
        void chkPD_LNA_RXFEClick(wxCommandEvent& event);
        void chkRINEN_MIX_RXFEClick(wxCommandEvent& event);
        void cmbG_FINE_LNA3_RXFEChange(wxCommandEvent& event);
		//*)

	protected:
        char m_cMAddr;
        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
