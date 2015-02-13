#ifndef PNLHPM1000_H
#define PNLHPM1000_H

//(*Headers(pnlHPM1000)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
class ConnectionManager;
#include "PluginPanel.h"

class pnlHPM1000: public wxPanel, public PluginPanel
{
	public:

		pnlHPM1000(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		void Initialize( ConnectionManager *pControl);
		virtual ~pnlHPM1000();
		virtual void UpdatePanel();

		//(*Declarations(pnlHPM1000)
		wxStaticText* StaticText10;
		wxCheckBox* chkGPIO2;
		wxStaticText* lblReadVal;
		wxComboBox* cmbMIPIId;
		wxCheckBox* chkGPIO1;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxCheckBox* chkGPIO0;
		wxButton* btnWriteMIPI;
		wxButton* btnWrite;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* lblRstatus;
		wxTextCtrl* txtAddrMIPI;
		wxTextCtrl* txtValueMIPI;
		wxStaticText* lblStatusMIPI;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* chkGPIO3;
		wxTextCtrl* txtWvalue;
		wxCheckBox* chkGPIO4;
		wxButton* btnReadMIPI;
		wxButton* btnReadGPIO;
		wxButton* btnRead;
		wxTextCtrl* txtWriteAddr;
		wxStaticText* lblReadValMipi;
		wxStaticText* StaticText4;
		wxTextCtrl* txtReadAddr;
		wxStaticText* lblWstatus;
		//*)

		//(*Identifiers(pnlHPM1000)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT14;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL4;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL5;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_BUTTON5;
		//*)

		//(*Handlers(pnlHPM1000)
		void OnchkGPIOClick(wxCommandEvent& event);
		void OnbtnWriteClick(wxCommandEvent& event);
		void OnbtnReadClick(wxCommandEvent& event);
		void OnbtnWriteNCOClick(wxCommandEvent& event);
		void OnbtnReadNCOClick(wxCommandEvent& event);
		void OnrgrNCOFCWUPDSelect(wxCommandEvent& event);
		void OnbtnWriteMIPIClick(wxCommandEvent& event);
		void OnbtnReadMIPIClick(wxCommandEvent& event);
		void OnbtnReadGPIOClick(wxCommandEvent& event);
		//*)

	protected:
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
