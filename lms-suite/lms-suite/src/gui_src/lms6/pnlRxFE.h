#ifndef PNLRXFE_H
#define PNLRXFE_H

//(*Headers(pnlRxFE)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/combobox.h>
//*)
#include "GUIPanel.h"
class pnlRxFE: public GUIPanel
{
	public:

		pnlRxFE(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlRxFE();
        virtual void UpdateGUI();
        void SetControlDisables();

		//(*Declarations(pnlRxFE)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		ComboBoxMap* cmbCFB_TIA_RXFE;
		wxRadioBox* rgrDecode;
		ComboBoxMap* cmbICT_MXLOB_RXFE;
		ComboBoxMap* cmbICT_LNA_RXFE;
		ComboBoxMap* cmbIP2TRIM_Q_RXFE;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxStaticText* StaticText6;
		ComboBoxMap* cmbRDLEXT_LNA_RXFE;
		wxStaticText* StaticText8;
		ComboBoxMap* cmbLNASEL_RXFE;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		ComboBoxMap* cmbDCOFF_Q_RXFE;
		wxStaticText* StaticText1;
		wxCheckBox* chkINLOAD_LNA_RXFE;
		ComboBoxMap* cmbICT_MIX_RXFE;
		wxStaticText* StaticText3;
		ComboBoxMap* cmbG_LNA_RXFE;
		ComboBoxMap* cmbLOBN_MIX_RXFE;
		wxCheckBox* chkPD_MXLOB_RXFE;
		ComboBoxMap* cmbCBE_LNA_RXFE;
		wxStaticText* StaticText5;
		ComboBoxMap* cmbICT_TIA_RXFE;
		wxStaticText* StaticText7;
		wxCheckBox* chkRINEN_MIX_RXFE;
		ComboBoxMap* cmbRFB_TIA_RXFE;
		wxCheckBox* chkXLOAD_LNA_RXFE;
		wxCheckBox* chkPD_LNA_RXFE;
		ComboBoxMap* cmbRDLINT_LNA_RXFE;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		ComboBoxMap* cmbG_FINE_LNA3_RXFE;
		wxCheckBox* chbPwrRxFeMods;
		wxCheckBox* chkPD_MIX_RXFE;
		ComboBoxMap* cmbIN1SEL_MIX_RXFE;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxCheckBox* chkPD_TIA_RXFE;
		wxStaticText* StaticText16;
		ComboBoxMap* cmbDCOFF_I_RXFE;
		ComboBoxMap* cmbIP2TRIM_I_RXFE;
		//*)

	protected:

		//(*Identifiers(pnlRxFE)
		static const long ID_DECODE_RXFE;
		static const long ID_EN_RXFE;
		static const long ID_PD_TIA_RXFE;
		static const long ID_PD_MXLOB_RXFE;
		static const long ID_PD_MIX_RXFE;
		static const long ID_PD_LNA_RXFE;
		static const long ID_RINEN_MIX_RXFE;
		static const long ID_INLOAD_LNA_RXFE;
		static const long ID_STATICTEXT1;
		static const long ID_XLOAD_LNA_RXFE;
		static const long ID_CBE_LNA_RXFE;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_G_LNA_RXFE;
		static const long ID_G_FINE_LNA3_RXFE;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_LNASEL_RXFE;
		static const long ID_ICT_LNA_RXFE;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_RDLEXT_LNA_RXFE;
		static const long ID_RDLINT_LNA_RXFE;
		static const long ID_STATICTEXT8;
		static const long ID_ICT_MIX_RXFE;
		static const long ID_STATICTEXT9;
		static const long ID_IN1SEL_MIX_RXFE;
		static const long ID_STATICTEXT10;
		static const long ID_ICT_MXLOB_RXFE;
		static const long ID_STATICTEXT11;
		static const long ID_LOBN_MIX_RXFE;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_IP2TRIM_I_RXFE;
		static const long ID_IP2TRIM_Q_RXFE;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_DCOFF_I_RXFE;
		static const long ID_DCOFF_Q_RXFE;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_RFB_TIA_RXFE;
		static const long ID_CFB_TIA_RXFE;
		static const long ID_ICT_TIA_RXFE;
		//*)

	private:

		//(*Handlers(pnlRxFE)
		void ParameterChangeHandler(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
