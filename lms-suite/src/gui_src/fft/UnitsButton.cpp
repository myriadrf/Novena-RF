#include "UnitsButton.h"

BEGIN_EVENT_TABLE(UnitsButton,wxButton)
    EVT_BUTTON(wxID_ANY, UnitsButton::ChangeUnits)
END_EVENT_TABLE()

UnitsButton::UnitsButton() : wxButton()
{
    m_power = 0;
}

UnitsButton::UnitsButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    : wxButton(parent, id, label, pos, size, style, validator, name)
{
    m_power = 0;
}

UnitsButton::~UnitsButton()
{

}

void UnitsButton::SetUnits(wxString units)
{
    m_units = units;
}

wxString UnitsButton::GetUnits()
{
    return m_units;
}

double UnitsButton::GetRatio()
{
    return pow(10, m_power);
}

int UnitsButton::GetPower()
{
    return m_power;
}

void UnitsButton::SetPower(int power)
{
    m_power = power;
    wxCommandEvent evt;
    updateLabel();
}

void UnitsButton::ChangeUnits(wxCommandEvent& event)
{
    m_power += 3;
    if(m_power > 9)
        m_power = 0;
    updateLabel();
    event.Skip();
}

void UnitsButton::updateLabel()
{
    wxString units;
    switch(m_power)
    {
    case 0:
        units = m_units; break;
    case 3:
        units = "K"+m_units; break;
    case 6:
        units = "M"+m_units; break;
    case 9:
        units = "G"+m_units; break;
    default:
        units = m_units; break;
    }
    wxButton::SetLabel(units);
}
