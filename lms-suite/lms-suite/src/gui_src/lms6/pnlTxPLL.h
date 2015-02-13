#ifndef PNLTXPLL_H
#define PNLTXPLL_H

//(*Headers(pnlTxPLL)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/spinbutt.h>
#include <wx/combobox.h>
//*)

#include "GUIPanel.h"
#include "RadioGroupMap.h"

class pnlTxPLL: public GUIPanel
{
	public:

		pnlTxPLL(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		virtual ~pnlTxPLL();

        void SetType(bool Rx);
        virtual void UpdateGUI();
        void SetControlDisables();
        void RefreshIntPLLData();

		//(*Declarations(pnlTxPLL)
		wxStaticText* StaticText10;
		wxRadioBox* rgrBCLKSEL;
		wxStaticText* StaticText9;
		wxCheckBox* chbPwrPllMods;
		wxCheckBox* chbFSTVCOBG;
		wxStaticText* StaticText20;
		wxCheckBox* chbAUTOBYP;
		wxRadioBox* rgrDecode;
		wxRadioBox* rgrBINSEL;
		wxStaticText* lblDiv;
		wxNotebook* Notebook1;
		ComboBoxMap* cmbBCODE;
		wxCheckBox* chkENFEEDDIV;
		wxStaticText* StaticText13;
		ComboBoxMap* cmbVOVCOREG;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxCheckBox* chkOEN_TSTD_SX;
		wxStaticText* StaticText14;
		wxSpinButton* spinFreqbtn;
		wxStaticText* StaticText6;
		wxCheckBox* chbEN_PFD_UP;
		wxStaticText* lblVTUNE_H;
		wxButton* btnClbr;
		wxStaticText* StaticText19;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnTune;
		wxStaticText* StaticText18;
		wxButton* btnStartBIST;
		wxButton* btnReadBISTState;
		wxButton* btnCalc;
		wxStaticText* StaticText3;
		wxStaticText* lblVTUNE_L;
		RadioGroupMap* rgrSELVCO;
		ComboBoxMap* cmbICHP;
		wxStaticText* StaticText21;
		wxStaticText* lblFvco8Int;
		wxStaticText* StaticText23;
		wxCheckBox* chkPOL;
		wxStaticText* lblVcoF;
		wxCheckBox* chkDITHEN;
		ComboBoxMap* cmbOFFDOWN;
		wxCheckBox* chkENLAMP;
		wxCheckBox* chkENLOBUF;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxButton* btnReadVtune;
		wxButton* btnReadSignature;
		wxPanel* Panel7;
		wxStaticText* lblN;
		wxStaticText* lblFvco4Int;
		wxStaticText* lblFvco16Int;
		wxStaticText* lblFvcoInt;
		wxStaticText* lblNfrac;
		ComboBoxMap* cmbDITHN;
		wxCheckBox* chkTRI;
		wxCheckBox* chkPD_VCOCOMP_SX;
		ComboBoxMap* cmbACODE;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		ComboBoxMap* cmbOFFUP;
		wxCheckBox* chbPDVCOREG;
		RadioGroupMap* rgrFRANGE;
		wxCheckBox* chbBYPVCOREG;
		wxCheckBox* chkPFDCLKP;
		wxCheckBox* chkPFDPD;
		wxRadioBox* rgrMODE;
		wxStaticText* lblBSIG;
		wxStaticText* lblFvco2Int;
		ComboBoxMap* cmbSELOUT;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxStaticText* lblBSTATE;
		wxStaticText* lblNint;
		wxStaticText* lblROutF;
		wxCheckBox* chkPASSEN_TSTOD_SD;
		wxStaticText* StaticText16;
		wxTextCtrl* txtDesFreq;
		ComboBoxMap* cmbVCOCAP;
		//*)

	protected:

		//(*Identifiers(pnlTxPLL)
		static const long ID_DECODE_PLL;
		static const long ID_OEN_TSTD_SX;
		static const long ID_PASSEN_TSTOD_SD;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT3;
		static const long ID_VCOCAP;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT4;
		static const long ID_VOVCOREG;
		static const long ID_BYPVCOREG;
		static const long ID_PDVCOREG;
		static const long ID_FSTVCOBG;
		static const long ID_STATICTEXT5;
		static const long ID_VTUNE_H;
		static const long ID_STATICTEXT7;
		static const long ID_VTUNE_L;
		static const long ID_BUTTON4;
		static const long ID_EN;
		static const long ID_PFDPD;
		static const long ID_ENLOBUF;
		static const long ID_PD_VCOCOMP_SX;
		static const long ID_ENLAMP;
		static const long ID_AUTOBYP;
		static const long ID_ENFEEDDIV;
		static const long ID_EN_PFD_UP;
		static const long ID_PFDCLKP;
		static const long ID_TRI;
		static const long ID_POL;
		static const long ID_STATICTEXT33;
		static const long ID_STATICTEXT35;
		static const long ID_STATICTEXT34;
		static const long ID_ICHP;
		static const long ID_OFFUP;
		static const long ID_OFFDOWN;
		static const long ID_SELOUT;
		static const long ID_DITHEN;
		static const long ID_STATICTEXT36;
		static const long ID_DITHN;
		static const long ID_MODE;
		static const long ID_TEXTCTRL1;
		static const long ID_SPINBUTTON1;
		static const long ID_BUTTON5;
		static const long ID_STATICTEXT11;
		static const long ID_NINT;
		static const long ID_STATICTEXT13;
		static const long ID_NFRAC;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT20;
		static const long ID_SELVCO;
		static const long ID_STATICTEXT9;
		static const long ID_ACODE;
		static const long ID_STATICTEXT10;
		static const long ID_BCODE;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT28;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT30;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT32;
		static const long ID_FRANGE;
		static const long ID_PANEL4;
		static const long ID_BSTATE;
		static const long ID_BUTTON6;
		static const long ID_BSIG;
		static const long ID_BUTTON7;
		static const long ID_BCLKSEL;
		static const long ID_BINSEL;
		static const long ID_BUTTON8;
		static const long ID_PANEL7;
		static const long ID_NOTEBOOK1;
		//*)

	private:

		//(*Handlers(pnlTxPLL)
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnCalculate(wxCommandEvent& event);
		void OnTune(wxCommandEvent& event);
		void OnbtnReadVtuneClick(wxCommandEvent& event);
		void OnbtnClbrClick(wxCommandEvent& event);
		void OnbtnReadSignatureClick(wxCommandEvent& event);
		void OnbtnReadBISTStateClick(wxCommandEvent& event);
		void OnbtnStartBISTClick(wxCommandEvent& event);
		void OnspinFreqbtnChangeUp(wxSpinEvent& event);
		void OnspinFreqbtnChangeDown(wxSpinEvent& event);
		//*)

	protected:
        bool m_Rx;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
