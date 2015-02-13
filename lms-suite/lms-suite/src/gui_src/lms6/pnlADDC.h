#ifndef PNLADDC_H
#define PNLADDC_H

//(*Headers(pnlADDC)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/combobox.h>
//*)
#include "GUIPanel.h"
class pnlADDC: public GUIPanel
{
	public:

		pnlADDC(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlADDC();
		virtual void UpdateGUI();
        void SetControlDisables();

		//(*Declarations(pnlADDC)
		wxStaticText* StaticText10;
		wxRadioBox* rgrADCAmp24Stage1BasUp;
		wxStaticText* StaticText9;
		ComboBoxMap* cmbRefBiasUp;
		wxRadioBox* rgrRX_FSYNC_P;
		wxRadioBox* rgrDACReferenceCurrentResistor;
		wxRadioBox* rgrDecode;
		ComboBoxMap* cmbBandgapGain;
		wxStaticText* StaticText13;
		ComboBoxMap* cmbDACFullScaleOutputCurrent;
		wxStaticText* StaticText2;
		wxRadioBox* rgrTX_FSYNC_P;
		wxCheckBox* chkEN_DAC;
		wxStaticText* StaticText14;
		ComboBoxMap* cmbCoomonModeAdj;
		wxCheckBox* chkEN_ADC_REF;
		wxStaticText* StaticText6;
		ComboBoxMap* cmbRefGainAdj;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		ComboBoxMap* cmbRefAmpsBiasAdj;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxCheckBox* chbEN_ADC_DAC;
		wxCheckBox* chkEN_ADC_Q;
		wxRadioBox* rgrADCAmp1Stage1BasUp;
		wxRadioBox* rgrDAC_CLK_P;
		ComboBoxMap* cmbADCSamplingPhase;
		ComboBoxMap* cmbBandgapTemp;
		wxCheckBox* chkEN_M_REF;
		ComboBoxMap* cmbRefBufferBoost;
		ComboBoxMap* cmbDACInternalOutputLoadResistor;
		wxStaticText* StaticText5;
		ComboBoxMap* cmbRefBiasDn;
		wxStaticText* StaticText7;
		ComboBoxMap* cmbRefAmpsBiasUp;
		wxCheckBox* chkInputBufferDisable;
		wxRadioBox* rgrADCBiasResistorAdjust;
		ComboBoxMap* cmbMainBiasDN;
		wxRadioBox* rgrADCAmp24Stage2BasUp;
		ComboBoxMap* cmbClockNonOverlapAdjust;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxCheckBox* chkEN_ADC_I;
		wxRadioBox* rgrADCAmp1Stage2BasUp;
		ComboBoxMap* cmbRefAmpsBiasDn;
		wxRadioBox* rgrTX_INTER;
		ComboBoxMap* cmbRefResistorBiasAdj;
		wxRadioBox* rgrRX_INTER;
		wxRadioBox* rgrQuantizerBiasUp;
		wxStaticText* StaticText4;
		wxStaticText* StaticText16;
		wxRadioBox* rgrInputBufferBiasUp;
		//*)

	protected:

		//(*Identifiers(pnlADDC)
		static const long ID_DECODE_ADDC;
		static const long ID_EN_ADC_DAC;
		static const long ID_EN_ADC_REF;
		static const long ID_EN_ADC_I;
		static const long ID_EN_DAC;
		static const long ID_EN_ADC_Q;
		static const long ID_EN_M_REF;
		static const long ID_RX_FSYNC_P;
		static const long ID_TX_FSYNC_P;
		static const long ID_RX_INTER;
		static const long ID_TX_INTER;
		static const long ID_DAC_CLK_P;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_REF_CTRL0_74;
		static const long ID_REF_CTRL0_30;
		static const long ID_REF_CTRL1_76;
		static const long ID_REF_CTRL1_54;
		static const long ID_REF_CTRL1_30;
		static const long ID_STATICTEXT15;
		static const long ID_TX_CTRL1_64;
		static const long ID_TX_CTRL1_3;
		static const long ID_STATICTEXT16;
		static const long ID_TX_CTRL1_10;
		static const long ID_RX_CTRL2_0;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_RX_CTRL1_76;
		static const long ID_RX_CTRL1_54;
		static const long ID_RX_CTRL1_30;
		static const long ID_RX_CTRL2_32;
		static const long ID_RX_CTRL2_54;
		static const long ID_RX_CTRL2_76;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_RX_CTRL4_54;
		static const long ID_RX_CTRL3_10;
		static const long ID_RX_CTRL3_7;
		static const long ID_RX_CTRL4_76;
		static const long ID_RX_CTRL4_32;
		static const long ID_RX_CTRL4_10;
		static const long ID_RX_CTRL5_32;
		static const long ID_RX_CTRL5_76;
		static const long ID_RX_CTRL5_54;
		static const long ID_RX_CTRL5_10;
		//*)

	private:

		//(*Handlers(pnlADDC)
		void ParameterChangeHandler(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
