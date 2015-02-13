#ifndef UNITS_BUTTON_H
#define UNITS_BUTTON_H

#include <wx/button.h>

class UnitsButton : public wxButton
{
public:
    UnitsButton();
    UnitsButton(wxWindow *parent, wxWindowID id, const wxString &label=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxButtonNameStr);
    ~UnitsButton();

    void SetUnits(wxString units);
    wxString GetUnits();
    double GetRatio();
    int GetPower();
    void SetPower(int power);

protected:
    void updateLabel();
    void ChangeUnits(wxCommandEvent& event);
    wxString m_units;
    int m_power;

    DECLARE_EVENT_TABLE()
};

#endif // UNITS_BUTTON_H

