#ifndef dlgSerPort_H
#define dlgSerPort_H

//(*Headers(dlgSerPort)
#include <wx/dialog.h>
class wxListBox;
class wxFlexGridSizer;
class wxButton;
class wxStaticText;
//*)

class ConnectionManager;

class dlgSerPort: public wxDialog
{
public:
    dlgSerPort(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~dlgSerPort();

    //(*Declarations(dlgSerPort)
    wxListBox* listReceivers;
    wxButton* btnDisconnect;
    wxStaticText* StaticText1;
    wxButton* btnOK;
    wxButton* btnCancel;
    //*)

protected:

    //(*Identifiers(dlgSerPort)
    static const long ID_STATICTEXT1;
    static const long ID_LISTBOX1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_BUTTON3;
    //*)

private:
    //(*Handlers(dlgSerPort)
    void OnbtnOKClick(wxCommandEvent& event);
    void OnbtnCancelClick(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnbtnDisconnectClick(wxCommandEvent& event);
    //*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    DECLARE_EVENT_TABLE()
};

#endif
