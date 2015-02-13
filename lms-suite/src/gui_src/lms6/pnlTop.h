#ifndef PNLTOP_H
#define PNLTOP_H

//(*Headers(pnlTop)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/tglbtn.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "GUIPanel.h"

class pnlTop: public GUIPanel
{
	public:

		pnlTop(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlTop();
		virtual void UpdateGUI();
        void SetControlDisables();
		//(*Declarations(pnlTop)
		wxRadioBox* rgrCLKSEL_LPFCAL;
		wxCheckBox* chkLpfCalEn;
		wxStaticText* StaticText9;
		wxCheckBox* chbPwrSoftTx;
		wxRadioBox* rgrDecode;
		wxStaticText* lblRCCAL_LPFCAL;
		wxButton* btnReadRCCALVal;
		wxCheckBox* chkCLK_EN_0;
		ComboBoxMap* cmbLpfCalCode;
		wxRadioBox* rgrRFLB;
		wxCheckBox* chkLpfCalEnEnf;
		wxButton* btnDCStartClbr;
		wxStaticText* StaticText2;
		wxCheckBox* chkCLK_EN_4;
		wxCheckBox* chkCLK_EN_6;
		wxStaticText* StaticText6;
		wxCheckBox* chbPDXCOBUF;
		wxCheckBox* chkCLK_EN_5;
		wxStaticText* StaticText8;
		wxCheckBox* chkCLK_EN_1;
		wxCheckBox* chbPwrRfLbsw;
		wxStaticText* StaticText1;
		wxCheckBox* chbSLFBXCOBUF;
		wxStaticText* StaticText3;
		wxRadioBox* rgrBBLB;
		wxRadioBox* rgrRXOUTSW;
		wxCheckBox* chbPwrLpfCal;
		wxRadioBox* rgrDsmRst;
		wxCheckBox* chkLpfCalRst;
		wxCheckBox* chbPwrTopMods;
		ComboBoxMap* cmbDCCalAddr;
		ComboBoxMap* cmbLpfCalBw;
		ComboBoxMap* cmbCalVal;
		wxCheckBox* chkCLK_EN_2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* chkCLK_EN_3;
		wxButton* btnDCRstClbr;
		wxStaticLine* StaticLine1;
		wxCheckBox* chbBYPXCOBUF;
		wxStaticText* lblDC_LOCK;
		wxCheckBox* chbPD_CLKLPFCAL;
		wxRadioBox* rgrSpiMode;
		wxButton* btnDCLoadVal;
		wxToggleButton* swReset;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxStaticText* StaticText4;
		wxRadioBox* rgrTDDMOD;
		wxStaticText* lblDC_REGVAL;
		wxCheckBox* chbRxTestModeEn;
		wxStaticText* lblDC_UD;
		wxRadioBox* rgrFDDTDD;
		wxCheckBox* chbPwrSoftRx;
		//*)

	protected:
        virtual void UpdateTooltips(wxWindow *panel);
		//(*Identifiers(pnlTop)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICLINE1;
		static const long ID_DCCAL_ADDR;
		static const long ID_CALVAL;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT3;
		static const long ID_DC_REGVAL_TOP;
		static const long ID_STATICTEXT4;
		static const long ID_DC_LOCK_TOP;
		static const long ID_STATICTEXT5;
		static const long ID_DC_CLBR_DONE_TOP;
		static const long ID_STATICTEXT6;
		static const long ID_DC_UD_TOP;
		static const long ID_RF_LOOPBACK_CONTROL;
		static const long ID_BB_LOOPBACK;
		static const long ID_EN_TOP;
		static const long ID_STXEN;
		static const long ID_SRXEN;
		static const long ID_PD_1_TOP;
		static const long ID_PD_0_TOP;
		static const long ID_RXOUTSW;
		static const long ID_TDD_MODE_SELECTION;
		static const long ID_FDDTDD_SELECTION;
		static const long ID_XCO_BUF_POWER_DOWN;
		static const long ID_XCO_BUF_SELF_BIASING;
		static const long ID_XCO_BUF_BYPASS;
		static const long ID_CLK_EN_0;
		static const long ID_CLK_EN_4;
		static const long ID_CLK_EN_1;
		static const long ID_CLK_EN_5;
		static const long ID_CLK_EN_2;
		static const long ID_CLK_EN_6;
		static const long ID_CLK_EN_3;
		static const long ID_PD_CLKLPFCAL;
		static const long ID_LPFCALENENF;
		static const long ID_LPFCALRST;
		static const long ID_LPFCALEN;
		static const long ID_STATICTEXT11;
		static const long ID_RCCAL_LPFCAL;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT13;
		static const long ID_LPFCALCODE;
		static const long ID_STATICTEXT14;
		static const long ID_LPFCALBW;
		static const long ID_CLKSEL_LPFCAL;
		static const long ID_DECODE_TOP;
		static const long ID_SPIMODE;
		static const long ID_RX_TEST_MODE_EN;
		static const long ID_DSMRST;
		static const long ID_GLOBALRESET;
		//*)

	private:

		//(*Handlers(pnlTop)
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnswResetToggle(wxCommandEvent& event);
		void OnrgrBBLBSelect(wxCommandEvent& event);
		void OnbtnReadRCCALValClick(wxCommandEvent& event);
		void OnbtnDCRstClbrClick(wxCommandEvent& event);
		void OnbtnDCLoadValClick(wxCommandEvent& event);
		void OnbtnDCStartClbrClick(wxCommandEvent& event);
		void OnbtnDCReadValClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
