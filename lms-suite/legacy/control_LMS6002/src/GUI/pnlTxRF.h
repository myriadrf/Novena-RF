#ifndef PNLTXRF_H
#define PNLTXRF_H

//(*Headers(pnlTxRF)
#include <wx/panel.h>
class wxStaticBoxSizer;
class wxComboBox;
class wxFlexGridSizer;
class wxStaticText;
class wxRadioBox;
class wxCheckBox;
//*)

class pnlTxRF: public wxPanel
{
	public:

		pnlTxRF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles = 0, wxString idname="");
		virtual ~pnlTxRF();

        void FillComboBoxes();
		void SetGuiDefaults();
        void SetGuiDecode();
        void Initialize();
        bool UpdateGUI();

		//(*Declarations(pnlTxRF)
		wxCheckBox* chbPwrVga1_Q;
		wxComboBox* cmbVga2G_t;
		wxStaticText* StaticText13;
		wxCheckBox* chbPD_DRVAUX;
		wxComboBox* cmbVga1DcI;
		wxRadioBox* rgrLOOPBBEN;
		wxCheckBox* chbPwrTxRfMods;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxCheckBox* chbPwrVga1_I;
		wxRadioBox* rgrPA;
		wxComboBox* cmbVga2G_u;
		wxStaticText* StaticText3;
		wxCheckBox* chbPD_PKDET;
		wxComboBox* cmbICT_TXLOBUF;
		wxStaticText* StaticText8;
		wxStaticText* StaticText12;
		wxComboBox* cmbICT_TXDRV;
		wxComboBox* cmbICT_TXMIX;
		wxStaticText* StaticText7;
		wxComboBox* cmbPKDBW;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxComboBox* cmbENVD2;
		wxStaticText* StaticText2;
		wxComboBox* cmbVga1G_t;
		wxStaticText* StaticText6;
		wxCheckBox* chbFST_TXHFBIAS;
		wxCheckBox* chbPwrVga2;
		wxRadioBox* rgrDecode;
		wxComboBox* cmbVga1G_u;
		wxComboBox* cmbVBCAS_TXDRV;
		wxStaticText* StaticText9;
		wxStaticText* StaticText11;
		wxComboBox* cmbENVD;
		wxCheckBox* chbPD_TXDRV;
		wxCheckBox* chbPD_TXLOBUF;
		wxComboBox* cmbVga1DcQ;
		wxCheckBox* chbFST_PKDET;
		//*)

	protected:

		//(*Identifiers(pnlTxRF)
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT6;
		static const long ID_COMBOBOX6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX7;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX9;
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_COMBOBOX4;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX2;
		static const long ID_STATICTEXT4;
		static const long ID_COMBOBOX3;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX8;
		static const long ID_COMBOBOX9;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT11;
		static const long ID_COMBOBOX10;
		static const long ID_COMBOBOX11;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_COMBOBOX12;
		static const long ID_COMBOBOX13;
		//*)

	private:

		//(*Handlers(pnlTxRF)
        void chbPwrTxRfModsClick(wxCommandEvent& event);
        void rgrDecodeClick(wxCommandEvent& event);
        void cmbVga1G_uChange(wxCommandEvent& event);
        void cmbVga1DcIChange(wxCommandEvent& event);
        void cmbVga1DcQChange(wxCommandEvent& event);
        void rgrPAClick(wxCommandEvent& event);
        void cmbVga2G_uChange(wxCommandEvent& event);
        void chbPwrVga1_IClick(wxCommandEvent& event);
        void chbPwrVga2Click(wxCommandEvent& event);
        void cmbVga1G_tChange(wxCommandEvent& event);
        void cmbVga2G_tChange(wxCommandEvent& event);
        void chbPwrVga1_QClick(wxCommandEvent& event);
        void rgrLOOPBBENClick(wxCommandEvent& event);
        void chbPD_DRVAUXClick(wxCommandEvent& event);
        void chbPD_PKDETClick(wxCommandEvent& event);
        void cmbENVDChange(wxCommandEvent& event);
        void cmbENVD2Change(wxCommandEvent& event);
        void cmbPKDBWChange(wxCommandEvent& event);
        void chbFST_PKDETClick(wxCommandEvent& event);
        void chbFST_TXHFBIASClick(wxCommandEvent& event);
        void cmbICT_TXLOBUFChange(wxCommandEvent& event);
        void cmbVBCAS_TXDRVChange(wxCommandEvent& event);
        void cmbICT_TXMIXChange(wxCommandEvent& event);
        void cmbICT_TXDRVChange(wxCommandEvent& event);
        void chbPD_TXLOBUFClick(wxCommandEvent& event);
        void chbPD_TXDRVClick(wxCommandEvent& event);
		//*)

	protected:
        int m_cMAddr;
        int m_cVer;
        int m_cRev;
        int m_cMask;

        bool sendChanges;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
