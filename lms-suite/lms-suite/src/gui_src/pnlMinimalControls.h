#ifndef PNLMINIMALCONTROLS_H
#define PNLMINIMALCONTROLS_H

//(*Headers(pnlMinimalControls)
#include <wx/panel.h>
class wxGridBagSizer;
class wxTextCtrl;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

#include "GUIPanel.h"
#include "PluginPanel.h"
class pnlMinimalControls: public GUIPanel, public PluginPanel
{
	public:

		pnlMinimalControls(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlMinimalControls();

		//(*Declarations(pnlMinimalControls)
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxTextCtrl* txtFreqGHz_Tx;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		ComboBoxMap* cmbG_LNA_RXFE;
		wxButton* btnSetFreqRx;
		wxTextCtrl* txtFreqGHz_Rx;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		ComboBoxMap* cmbRFB_TIA_RXFE;
		ComboBoxMap* cmbVGA2GAIN_TXVGA2;
		ComboBoxMap* cmbBWC_LPF_TXLPF;
		wxButton* btnUpdateGUI;
		ComboBoxMap* cmbBWC_LPF_RXLPF;
		wxStaticText* StaticText4;
		wxButton* btnSetFreqTx;
		ComboBoxMap* cmbVGA1GAIN;
		ComboBoxMap* cmbVGA2GAIN_RXVGA2;
		//*)

	protected:

		//(*Identifiers(pnlMinimalControls)
		static const long ID_STATICTEXT1;
		static const long ID_BWC_LPF_TXLPF;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_VGA1GAIN;
		static const long ID_STATICTEXT4;
		static const long ID_VGA2GAIN_TXVGA2;
		static const long ID_STATICTEXT5;
		static const long ID_BWC_LPF_RXLPF;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT7;
		static const long ID_RFB_TIA_RXFE;
		static const long ID_STATICTEXT8;
		static const long ID_VGA2GAIN_RXVGA2;
		static const long ID_G_LNA_RXFE;
		static const long ID_BUTTON3;
		//*)

	private:

		//(*Handlers(pnlMinimalControls)
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnSetFreqTxClick(wxCommandEvent& event);
		void OnbtnSetFreqRxClick(wxCommandEvent& event);
		void OnbtnUpdateGUIClick(wxCommandEvent& event);
		//*)

	protected:
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
