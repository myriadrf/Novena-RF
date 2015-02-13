#ifndef PNLTXRF_H
#define PNLTXRF_H

//(*Headers(pnlTxRF)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/combobox.h>
//*)
#include "GUIPanel.h"
class pnlTxRF: public GUIPanel
{
	public:

		pnlTxRF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlTxRF();
        virtual void UpdateGUI();
        void SetControlDisables();
		//(*Declarations(pnlTxRF)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		ComboBoxMap* cmbVga1G_t;
		wxCheckBox* chbPD_DRVAUX;
		wxRadioBox* rgrDecode;
		wxCheckBox* chbPwrVga1_I;
		ComboBoxMap* cmbVga1DcQ;
		wxCheckBox* chbPD_TXDRV;
		ComboBoxMap* cmbPKDBW;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		ComboBoxMap* cmbVga1DcI;
		wxStaticText* StaticText6;
		wxCheckBox* chbPD_TXLOBUF;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxCheckBox* chbFST_PKDET;
		wxRadioBox* rgrPA;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxCheckBox* chbFST_TXHFBIAS;
		wxCheckBox* chbPwrVga2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		ComboBoxMap* cmbVBCAS_TXDRV;
		wxCheckBox* chbPD_PKDET;
		wxCheckBox* chbPwrTxRfMods;
		ComboBoxMap* cmbVga2G_t;
		ComboBoxMap* cmbVga2G_u;
		wxStaticText* StaticText12;
		ComboBoxMap* cmbENVD2;
		wxRadioBox* rgrLOOPBBEN;
		wxCheckBox* chbPwrVga1_Q;
		ComboBoxMap* cmbICT_TXDRV;
		ComboBoxMap* cmbICT_TXLOBUF;
		ComboBoxMap* cmbENVD;
		wxStaticText* StaticText4;
		ComboBoxMap* cmbICT_TXMIX;
		ComboBoxMap* cmbVga1G_u;
		//*)

	protected:

		//(*Identifiers(pnlTxRF)
		static const long ID_EN_TXRF;
		static const long ID_PD_DRVAUX;
		static const long ID_PD_PKDET;
		static const long ID_PW_VGA1_I;
		static const long ID_PW_VGA1_Q;
		static const long ID_PD_TXDRV;
		static const long ID_PD_TXLOBUF;
		static const long ID_PD_TXMIX;
		static const long ID_STATICTEXT5;
		static const long ID_ENVD;
		static const long ID_STATICTEXT6;
		static const long ID_ENVD2;
		static const long ID_STATICTEXT7;
		static const long ID_PKDBW;
		static const long ID_FST_PKDET;
		static const long ID_FST_TXHFBIAS;
		static const long ID_STATICTEXT1;
		static const long ID_ICT_TXLOBUF;
		static const long ID_STATICTEXT2;
		static const long ID_VBCAS_TXDRV;
		static const long ID_STATICTEXT3;
		static const long ID_ICT_TXMIX;
		static const long ID_STATICTEXT4;
		static const long ID_ICT_TXDRV;
		static const long ID_LOOPBBEN;
		static const long ID_PA;
		static const long ID_DECODE_TXRF;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_VGA1G_U;
		static const long ID_VGA1_DC_I;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_VGA1G_T;
		static const long ID_VGA1_DC_Q;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_VGA2G_U;
		static const long ID_VGA2G_T;
		//*)

	private:

		//(*Handlers(pnlTxRF)
		void ParameterChangeHandler(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
