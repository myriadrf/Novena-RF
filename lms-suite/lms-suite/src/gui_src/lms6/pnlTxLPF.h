#ifndef PNLTXLPF_H
#define PNLTXLPF_H

//(*Headers(pnlTxLPF)
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
class pnlTxLPF: public GUIPanel
{
	public:

		pnlTxLPF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlTxLPF();
        virtual void UpdateGUI();
        void SetControlDisables();
		void SetType(bool Rx);

		//(*Declarations(pnlTxLPF)
		wxCheckBox* chbPwrDCDac;
		wxRadioBox* rgrDecode;
		wxButton* btnDCStartClbr;
		wxStaticText* StaticText2;
		wxCheckBox* chbPwrDCRef;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		ComboBoxMap* cmbDCOffset;
		ComboBoxMap* cmbDCCalAddr;
		wxRadioBox* rgrLpfByp;
		ComboBoxMap* cmbCalVal;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnDCRstClbr;
		wxStaticLine* StaticLine1;
		wxStaticText* lblDC_LOCK;
		ComboBoxMap* cmbRcCal;
		ComboBoxMap* cmbLpfBw;
		wxButton* btnDCLoadVal;
		wxCheckBox* chbPwrLpfMods;
		wxButton* btnDCReadVal;
		wxStaticText* lblDC_CLBR_DONE;
		wxCheckBox* chbPwrDCCmpr;
		wxStaticText* StaticText4;
		wxStaticText* lblDC_REGVAL;
		wxStaticText* lblDC_UD;
		wxCheckBox* chbTX_DACBUF_EN;
		wxCheckBox* chbPwrLpf;
		//*)

	protected:

		//(*Identifiers(pnlTxLPF)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICLINE1;
		static const long ID_DC_ADDR;
		static const long ID_DC_CNTVAL;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT3;
		static const long ID_DC_REGVAL;
		static const long ID_STATICTEXT4;
		static const long ID_DC_LOCK;
		static const long ID_STATICTEXT5;
		static const long ID_DC_CLBR_DONE;
		static const long ID_STATICTEXT6;
		static const long ID_DC_UD;
		static const long ID_EN;
		static const long ID_PD_FIL_LPF;
		static const long ID_PD_DCODAC_LPF;
		static const long ID_PD_DCOREF_LPF;
		static const long ID_PD_DCOCMP_LPF;
		static const long ID_TX_DACBUF_PD;
		static const long ID_LPFBW;
		static const long ID_BYP_EN_LPF;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_DCO_DACCAL;
		static const long ID_RCCAL_LPF;
		static const long ID_DECODE;
		//*)

	private:

		//(*Handlers(pnlTxLPF)
		void OnbtnDCLoadValClick(wxCommandEvent& event);
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnDCRstClbrClick(wxCommandEvent& event);
		void OnbtnDCStartClbrClick(wxCommandEvent& event);
		void OnbtnDCReadValClick(wxCommandEvent& event);
		//*)

	protected:
        bool m_Rx;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
