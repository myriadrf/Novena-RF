#ifndef pnlSi5351_H
#define pnlSi5351_H

#include "Si5351C.h"

//(*Headers(pnlBoard)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlBoard: public wxPanel
{
public:

    pnlBoard(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style = 0, wxString name="");
    virtual ~pnlBoard();

    //(*Declarations(pnlBoard)
    wxStaticText* StaticText10;
    wxStaticText* StaticText9;
    wxCheckBox* chkEN_CLK5;
    wxCheckBox* chkInvert_CLK6;
    wxComboBox* cmbDTC1out;
    wxTextCtrl* txtFreq_CLK7;
    wxTextCtrl* txtFreq_CLK1;
    wxCheckBox* chkEN_CLK3;
    wxCheckBox* chkEN_CLK4;
    wxCheckBox* chkInvert_CLK3;
    wxTextCtrl* txtFreq_CLK5;
    wxStaticText* StaticText13;
    wxStaticText* StaticText2;
    wxButton* btnLoadFile;
    wxTextCtrl* txtFreq_CLK0;
    wxStaticText* StaticText14;
    wxCheckBox* chkSWC1out;
    wxStaticText* StaticText6;
    wxButton* btnResetToDefaults;
    wxStaticText* StaticText8;
    wxStaticText* StaticText11;
    wxStaticText* StaticText18;
    wxCheckBox* chkSWC1;
    wxStaticText* StaticText1;
    wxStaticText* StaticText3;
    wxCheckBox* chkSWC2out;
    wxCheckBox* chkSWC3out;
    wxButton* btnConfigure;
    wxCheckBox* chkEN_CLK6;
    wxTextCtrl* txtFreq_CLK3;
    wxTextCtrl* txtFreq_CLK6;
    wxComboBox* cmbLNAbypass;
    wxTextCtrl* txtFreq_CLK2;
    wxStaticText* StaticText5;
    wxStaticText* StaticText7;
    wxComboBox* cmbDTC2out;
    wxCheckBox* chkInvert_CLK2;
    wxCheckBox* chkInvert_CLK0;
    wxCheckBox* chkSWC2;
    wxCheckBox* chkEN_CLK1;
    wxComboBox* cmbDTC2in;
    wxStaticText* StaticText15;
    wxStaticText* StaticText12;
    wxCheckBox* chkEN_CLK7;
    wxCheckBox* chkInvert_CLK1;
    wxTextCtrl* txtFreq_CLK4;
    wxStaticText* StaticText17;
    wxStaticText* StaticText4;
    wxTextCtrl* txtCLKIN_MHz;
    wxCheckBox* chkInvert_CLK7;
    wxCheckBox* chkInvert_CLK5;
    wxCheckBox* chkEN_CLK2;
    wxCheckBox* chkEN_CLK0;
    wxStaticText* StaticText16;
    wxCheckBox* chkSWC3;
    wxCheckBox* chkInvert_CLK4;
    wxComboBox* cmbDTC1in;
    //*)

protected:

    //(*Identifiers(pnlBoard)
    static const long ID_BUTTON2;
    static const long ID_BUTTON4;
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT11;
    static const long ID_STATICTEXT12;
    static const long ID_STATICTEXT13;
    static const long ID_STATICTEXT3;
    static const long ID_CHECKBOX1;
    static const long ID_TEXTCTRL2;
    static const long ID_CHECKBOX9;
    static const long ID_STATICTEXT4;
    static const long ID_CHECKBOX2;
    static const long ID_TEXTCTRL3;
    static const long ID_CHECKBOX10;
    static const long ID_STATICTEXT5;
    static const long ID_CHECKBOX3;
    static const long ID_TEXTCTRL4;
    static const long ID_CHECKBOX11;
    static const long ID_STATICTEXT6;
    static const long ID_CHECKBOX4;
    static const long ID_TEXTCTRL5;
    static const long ID_CHECKBOX12;
    static const long ID_STATICTEXT7;
    static const long ID_CHECKBOX5;
    static const long ID_TEXTCTRL6;
    static const long ID_CHECKBOX13;
    static const long ID_STATICTEXT8;
    static const long ID_CHECKBOX6;
    static const long ID_TEXTCTRL7;
    static const long ID_CHECKBOX14;
    static const long ID_STATICTEXT9;
    static const long ID_CHECKBOX7;
    static const long ID_TEXTCTRL8;
    static const long ID_CHECKBOX15;
    static const long ID_STATICTEXT10;
    static const long ID_CHECKBOX8;
    static const long ID_TEXTCTRL9;
    static const long ID_CHECKBOX16;
    static const long ID_BUTTON3;
    static const long ID_STATICTEXT15;
    static const long ID_COMBOBOX2;
    static const long ID_STATICTEXT16;
    static const long ID_COMBOBOX3;
    static const long ID_CHECKBOX17;
    static const long ID_CHECKBOX18;
    static const long ID_CHECKBOX19;
    static const long ID_STATICTEXT17;
    static const long ID_COMBOBOX4;
    static const long ID_STATICTEXT18;
    static const long ID_COMBOBOX5;
    static const long ID_CHECKBOX20;
    static const long ID_CHECKBOX21;
    static const long ID_CHECKBOX22;
    static const long ID_STATICTEXT14;
    static const long ID_COMBOBOX1;
    //*)

private:
    //(*Handlers(pnlBoard)
    void OnbtnLoadFileClick(wxCommandEvent& event);
    void OnbtnConfigureClockClick(wxCommandEvent& event);
    void OnbtnResetToDefaultsClick(wxCommandEvent& event);
    void OnbtnUploadClick(wxCommandEvent& event);
    void OncmbLNAbypassSelected(wxCommandEvent& event);
    void OncmbLNAbypassSelected1(wxCommandEvent& event);
    void OncmbDTC1Selected(wxCommandEvent& event);
    void OncmbDTC2Selected(wxCommandEvent& event);
    void OncmbDTC1outSelected(wxCommandEvent& event);
    void OncmbDTC2outSelected(wxCommandEvent& event);
    void configMyriadRF_PAIN(wxCommandEvent& event);
    void configMyriadRF_PAOUT(wxCommandEvent& event);
    //*)

protected:

    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void ConfigMyriadRF2(int id);
    DECLARE_EVENT_TABLE()
};

#endif
