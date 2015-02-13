#ifndef RADIO_GROUP_MAP_H
#define RADIO_GROUP_MAP_H

#include <wx/radiobox.h>
#include <map>

class RadioGroupMap : public wxRadioBox
{
public:
    RadioGroupMap(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, int n=0, const wxString choices[]=NULL, int majorDimension=0, long style=wxRA_SPECIFY_COLS, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxRadioBoxNameStr);
    RadioGroupMap(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, const wxArrayString &choices, int majorDimension=0, long style=wxRA_SPECIFY_COLS, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxRadioBoxNameStr);
    ~RadioGroupMap();
    virtual int GetSelection();
    virtual void SetSelection(int n);
    void SetIndexValues(int* values, int len);
private:
    void valueChanged(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()

    std::map<int, int> m_indexValues;
};

#endif // RADIO_GROUP_MAP_H
