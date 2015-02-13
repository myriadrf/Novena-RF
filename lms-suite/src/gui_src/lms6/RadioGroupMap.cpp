#include "RadioGroupMap.h"
#include <iostream>
using namespace std;
RadioGroupMap::RadioGroupMap(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], int majorDimension, long style, const wxValidator& validator, const wxString& name)
    : wxRadioBox(parent, id, label, pos, size, n, choices, majorDimension, style, validator, name)
{
    for(int i=0; i<n; ++i)
    {
        m_indexValues.insert(pair<int,int>(i, i));
    }
}

RadioGroupMap::RadioGroupMap(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, int majorDimension, long style, const wxValidator& validator, const wxString& name)
    : wxRadioBox(parent, id, label, pos, size, choices, majorDimension, style, validator, name)
{
    for(unsigned i=0; i<choices.size(); ++i)
    {
        m_indexValues.insert(pair<int,int>(i, i));
    }
}

RadioGroupMap::~RadioGroupMap()
{

}

int RadioGroupMap::GetSelection()
{
    int value = m_indexValues[wxRadioBox::GetSelection()];
    return value;
}

void RadioGroupMap::SetSelection(int n)
{
    int index = -1;
    map<int,int>::iterator iter;
    for(iter = m_indexValues.begin(); iter != m_indexValues.end(); ++iter)
    {
        if(n == iter->second)
        {
            index = iter->first;
        }
    }
    wxRadioBox::SetSelection(index);
}

void RadioGroupMap::valueChanged(wxCommandEvent& event)
{
    int val = event.GetInt();
    wxCommandEvent evt(wxEVT_RADIOBOX);
    evt.SetId(GetId());
    int value = -1;
    value = m_indexValues[val];
    evt.SetInt(value);
    evt.SetEventObject(this);
    evt.SetString(event.GetString());
    wxPostEvent(GetParent()->GetEventHandler(), evt);
}

void RadioGroupMap::SetIndexValues(int* values, int len)
{
    m_indexValues.clear();
    for(int i=0; i<len; ++i)
    {
        m_indexValues.insert(pair<int,int>(i, values[i]));
    }
}

BEGIN_EVENT_TABLE(RadioGroupMap, wxRadioBox)
    EVT_RADIOBOX(wxID_ANY, RadioGroupMap::valueChanged)
END_EVENT_TABLE()
