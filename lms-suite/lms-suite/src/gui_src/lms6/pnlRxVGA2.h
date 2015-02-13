#ifndef PNLRXVGA2_H
#define PNLRXVGA2_H

//(*Headers(pnlRxVGA2)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)
#include "GUIPanel.h"
#include "ComboBoxMap.h"
class pnlRxVGA2: public GUIPanel
{
	public:

		pnlRxVGA2(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlRxVGA2();
		virtual void UpdateGUI();
        void SetControlDisables();

		//(*Declarations(pnlRxVGA2)
		wxStaticText* StaticText9;
		wxRadioBox* rgrDecode;
		wxCheckBox* chbPwrBypAB;
		wxCheckBox* chbPwrBypA;
		wxButton* btnDCStartClbr;
		ComboBoxMap* cmbVga2GB_t;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxCheckBox* chbPwrDCCurrR;
		wxCheckBox* chbPwrBypB;
		wxStaticText* StaticText8;
		wxCheckBox* chbPwrVGA2Mods;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxCheckBox* chbPwrCurrRef;
		ComboBoxMap* cmbVCM;
		wxCheckBox* chbPwrDCDACB;
		ComboBoxMap* cmbVga2GA_t;
		wxCheckBox* chbPwrBG;
		wxCheckBox* chbPwrDCDACA;
		wxCheckBox* chbPwrDCCmpA;
		ComboBoxMap* cmbDCCalAddr;
		ComboBoxMap* cmbCalVal;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnDCRstClbr;
		wxCheckBox* chbPwrDCCmpB;
		wxStaticLine* StaticLine1;
		ComboBoxMap* cmbVga2G_u;
		wxStaticText* lblDC_LOCK;
		wxButton* btnDCLoadVal;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxStaticText* StaticText4;
		wxStaticText* lblDC_REGVAL;
		wxStaticText* lblDC_UD;
		//*)

	protected:

		//(*Identifiers(pnlRxVGA2)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICLINE1;
		static const long ID_DC_ADDR_RXVGA2;
		static const long ID_DC_CNTVAL_RXVGA2;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT3;
		static const long ID_DC_REGVAL_RXVGA2;
		static const long ID_STATICTEXT4;
		static const long ID_DC_LOCK_RXVGA2;
		static const long ID_STATICTEXT5;
		static const long ID_DC_CLBR_DONE_RXVGA2;
		static const long ID_STATICTEXT6;
		static const long ID_DC_UD_RXVGA2;
		static const long ID_EN_RXVGA2;
		static const long ID_PD_9;
		static const long ID_PD_8;
		static const long ID_PD_7;
		static const long ID_PD_6;
		static const long ID_PD_5;
		static const long ID_PD_4;
		static const long ID_PD_3;
		static const long ID_PD_2;
		static const long ID_PD_1;
		static const long ID_PD_0;
		static const long ID_STATICTEXT11;
		static const long ID_VGA2GAIN_RXVGA2;
		static const long ID_STATICTEXT12;
		static const long ID_VGA2GAINB;
		static const long ID_STATICTEXT13;
		static const long ID_VGA2GAINA;
		static const long ID_VCM_RXVGA2;
		static const long ID_DECODE_RXVGA2;
		//*)

	private:

		//(*Handlers(pnlRxVGA2)
		void OnbtnDCRstClbrClick(wxCommandEvent& event);
		void OnbtnDCLoadValClick(wxCommandEvent& event);
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnDCStartClbrClick(wxCommandEvent& event);
		void OnbtnDCReadValClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
