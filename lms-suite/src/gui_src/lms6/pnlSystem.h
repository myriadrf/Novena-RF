#ifndef PNLSYSTEM_H
#define PNLSYSTEM_H

//(*Headers(pnlSystem)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "GUIPanel.h"
#include "UARFCN.h"

class pnlSystem: public GUIPanel
{
	public:

		pnlSystem(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name = wxEmptyString);
		void SetBypassLoopback();
		virtual ~pnlSystem();

		void fillChannels(bool Rx);
		void fillBands(bool Rx);

		CUARFCN bandsConf;

		//(*Declarations(pnlSystem)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxButton* btnULRXFChan_M;
		wxButton* btnDLTXFChan_T;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxComboBox* cmbLoopback;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxButton* btnDLTXFChan_B;
		wxStaticText* StaticText1;
		wxButton* btnULRXFChan_B;
		wxStaticText* StaticText3;
		wxButton* btnULRXFChan_T;
		ComboBoxMap* cmbLNASEL_Cust;
		ComboBoxMap* cmbULRXBands;
		ComboBoxMap* cmbDLTXChan;
		ComboBoxMap* cmbDLTXBands;
		wxButton* btnDLTXFChan_M;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxComboBox* cmbTxBypass;
		wxButton* btnClbrRx;
		wxStaticText* StaticText12;
		wxTextCtrl* txtULRXFreq;
		wxButton* btnCalLPFCore;
		wxComboBox* cmbBypass;
		wxStaticText* StaticText4;
		wxTextCtrl* txtDLTXFreq;
		ComboBoxMap* cmbULRXChan;
		wxButton* btnClbrTx;
		//*)

	protected:

		//(*Identifiers(pnlSystem)
		static const long ID_STATICTEXT1;
		static const long ID_LNASEL_RXFE;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_COMBOBOX7;
		static const long ID_COMBOBOX8;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_TEXTCTRL1;
		//*)

	private:

		//(*Handlers(pnlSystem)
		void OnbtnClbrTxClick(wxCommandEvent& event);
		void OnbtnClbrRxClick(wxCommandEvent& event);
		void OnbtnCalLPFCoreClick(wxCommandEvent& event);
		void OnbtnDLTXFChan_BClick(wxCommandEvent& event);
		void OnbtnDLTXFChan_MClick(wxCommandEvent& event);
		void OnbtnDLTXFChan_TClick(wxCommandEvent& event);
		void OnbtnULRXFChan_BClick(wxCommandEvent& event);
		void OnbtnULRXFChan_MClick(wxCommandEvent& event);
		void OnbtnULRXFChan_TClick(wxCommandEvent& event);
		void ParameterChangeHandler(wxCommandEvent& event);
		void OncmbRxBypassSelected(wxCommandEvent& event);
		void OncmbLoopbackSelected(wxCommandEvent& event);
		void OncmbTxBypassSelected(wxCommandEvent& event);
		void OncmbDLTXBandsSelected(wxCommandEvent& event);
		void OncmbDLTXChanSelected(wxCommandEvent& event);
		void OncmbULRXBandsSelected(wxCommandEvent& event);
		void OncmbULRXChanSelected(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
