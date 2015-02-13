// -----------------------------------------------------------------------------
// FILE: 		ComboBoxMap.cpp
// DESCRIPTION: Replacement for wxComboBox due to it's slow item appending
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include "ComboBoxMap.h"
#include <wx/event.h>
/** Custom combobox control for wxWidgets, because standard one works too slow
when adding many items to drop lists.
*/

ComboBoxMap::ComboBoxMap()
{

}

/** @brief ComboBoxMap
*/
ComboBoxMap::ComboBoxMap(wxWindow* parent, wxWindowID winid, const wxString str, const wxPoint& pos, const wxSize& size, long style, int a, int b, const wxValidator& val, const wxString& name)
{
    Create(parent, winid, pos, size, style, a, b, val, name);
}

/** @brief ComboBoxMap
*/
ComboBoxMap::ComboBoxMap(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, int a, int b, const wxValidator& val, const wxString& name)
{
    Create(parent, winid, pos, size, style, a, b, val, name);
}

bool ComboBoxMap::Create(wxWindow *parent,
                         wxWindowID winid,
                         const wxPoint& pos,
                         const wxSize& size,
                         long style, int a, int b,
                         const wxValidator& val,
                         const wxString& name)
{
    bool status = wxComboCtrl::Create(parent, winid, wxEmptyString, pos, size, wxTE_PROCESS_ENTER, wxDefaultValidator, wxString(""));
    m_popup = new ComboBoxMapPopup(parent, winid);
    textOk = false;
    SetPopupControl(m_popup);
    return status;
}


/** @brief Appends vector of strings to drop list
*/
int ComboBoxMap::Append(const wxArrayString &sarray)
{
    std::vector<cmbKeyValuePair> keyVals;
    for(unsigned i=0; i<sarray.size(); ++i)
        keyVals.push_back( cmbKeyValuePair(i, sarray[i]));
    m_popup->Set(keyVals);
    return 0;
}

int ComboBoxMap::Set(const wxArrayString &sarray)
{
    return Append(sarray);
}

/** @brief Clears items from drop list
*/
void ComboBoxMap::Clear()
{
    m_popup->Clear();
}

/** @brief Sets current selection from drop list
*/
bool ComboBoxMap::SetSelection(int n)
{
    if( m_popup->SetSelection(n) )
    {
        SetValue(m_popup->GetStringValue());
        return true;
    }
    return false;
    //Refresh();
}

/** @brief Returns current selection from drop list
*/
int ComboBoxMap::GetSelection()
{
    return m_popup->GetSelection();
}

/** @brief Changes selection when mouse wheel is turned
*/
void ComboBoxMap::OnMouseWheelMoved(wxMouseEvent &event)
{
    if(IsPopupShown())
    {
        m_popup->OnMouseWheelMoved(event);
        return;
    }
    int selection = m_popup->GetSelectionIndex();
    if(event.GetWheelRotation() < 0)
    {
        if( m_popup->SetSelectionByIndex( selection+1 ) )
        {
            m_popup->SendComboboxEvent();
            SetValue(m_popup->GetStringValue());
        }
    }
    else if(event.GetWheelRotation() > 0)
    {
        if( m_popup->SetSelectionByIndex( selection-1 ) )
        {
            m_popup->SendComboboxEvent();
            SetValue(m_popup->GetStringValue());
        }
    }
}

void ComboBoxMap::OnTextChanged(wxCommandEvent &event)
{
    int i = m_popup->FindStringIndex(event.GetString().ToStdString());
    if(i >= 0)
    {
        pendingIndex = i;
        textOk = true;
    }
    else
    {
        pendingIndex = -1;
        textOk = false;
    }
    return;
}

void ComboBoxMap::OnKeyDown(wxKeyEvent &event)
{
    int keyCode = event.GetKeyCode();
    if(keyCode == WXK_RETURN || keyCode == WXK_NUMPAD_ENTER || keyCode == WXK_RETURN)
    {
        if(textOk)
        {
            m_popup->SetSelection(pendingIndex);
            m_popup->SendComboboxEvent();
            textOk = false;
        }
        else
        {
            SetText( m_popup->GetStringValue() );
        }
        return;
    }
    event.ResumePropagation(1);
    event.Skip();
}

void ComboBoxMap::OnKillFocus(wxFocusEvent &event)
{
    if(textOk)
    {
        m_popup->SetSelection(pendingIndex);
        m_popup->SendComboboxEvent();
        textOk = false;
    }
    else
    {
        SetText( m_popup->GetStringValue() );
    }
    //event.Skip();
}

int ComboBoxMap::Set(std::vector<cmbKeyValuePair> keyValuePairs)
{
    m_popup->Set(keyValuePairs);
    return 0;
}

unsigned int ComboBoxMap::GetCount() const
{
    return m_popup->GetCount();
}

bool ComboBoxMap::SetSelectionByIndex(int ind)
{
    if(m_popup->SetSelectionByIndex(ind))
    {
        SetValue(m_popup->GetStringValue());
        return true;
    }
    return false;
}

int ComboBoxMap::GetSelectionIndex()
{
    return m_popup->GetSelectionIndex();
}

wxIMPLEMENT_DYNAMIC_CLASS(ComboBoxMap, wxComboCtrl)

BEGIN_EVENT_TABLE(ComboBoxMap, wxComboCtrl)
    EVT_MOUSEWHEEL(ComboBoxMap::OnMouseWheelMoved)
    EVT_TEXT(wxID_ANY, ComboBoxMap::OnTextChanged)
    EVT_KEY_DOWN(ComboBoxMap::OnKeyDown)
END_EVENT_TABLE()

ComboBoxMapPopup::ComboBoxMapPopup()
{
    m_cmbbox = NULL;
}

ComboBoxMapPopup::ComboBoxMapPopup(wxWindow *parent, wxWindowID winid)
{
    m_myID = winid;
    m_cmbbox = NULL;
    SetId(winid);
}

ComboBoxMapPopup::~ComboBoxMapPopup()
{

}

void ComboBoxMapPopup::Init()
{
    m_selection = -1;
    m_textHeight = -1;
    showLines = 10;
    initialized = false;
}

void ComboBoxMapPopup::OnScroll(wxScrollEvent& event)
{
    Refresh();
}

bool ComboBoxMapPopup::Create(wxWindow* parent)
{
    return Create(parent, wxID_ANY);
}

bool ComboBoxMapPopup::Create(wxWindow* parent, wxWindowID winid)
{
    m_highlightedItem = -1;
    m_cmbbox = parent;
    bool status = wxControl::Create(parent, winid);

    long scrollBarId = wxNewId();
    ScrollBar1 = new wxScrollBar(this, scrollBarId, wxDefaultPosition , wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR1"));
    ScrollBar1->SetScrollbar(0, showLines, m_strings_items.size(), showLines-1);
    ScrollBar1->SetThumbPosition(m_selection);
    Connect(scrollBarId, wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&ComboBoxMapPopup::OnScroll);
    Connect(scrollBarId, wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&ComboBoxMapPopup::OnScroll);
    Connect(scrollBarId, wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&ComboBoxMapPopup::OnScroll);
    Connect(scrollBarId, wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&ComboBoxMapPopup::OnScroll);
    return status;
}

void ComboBoxMapPopup::SetStringValue(const wxString& s)
{
    for(unsigned int i=0; i<m_strings_items.size(); ++i)
    {
        if(m_strings_items[i].second == s)
        {
            SetSelection(m_strings_items[i].first);
            break;
        }
    }
}

wxString ComboBoxMapPopup::GetStringValue() const
{
    unsigned int selection = m_selection;
    if ( selection < m_strings_items.size())
    {
        return m_strings_items[selection].second;
    }
    return wxEmptyString;
}

void ComboBoxMapPopup::OnMouseClick(wxMouseEvent &event)
{
    if( SetSelectionByIndex(ScrollBar1->GetThumbPosition()+event.GetY()/m_textHeight) )
    {
        Dismiss();
        SendComboboxEvent();
    }
}

void ComboBoxMapPopup::OnMouseMove(wxMouseEvent &event)
{
    unsigned int ind = ScrollBar1->GetThumbPosition()+event.GetY()/m_textHeight;
    if(ind < m_strings_items.size())
    {
        if(m_highlightedItem != ind)
        {
            m_highlightedItem = ind;
            Refresh();
        }
    }
}

bool ComboBoxMapPopup::SetSelectionByIndex(int ind)
{
    unsigned int index = ind;
    if(index < m_strings_items.size())
    {
        m_selection = index;
        return true;
    }
    return false;
}

void ComboBoxMapPopup::OnPopup()
{
    int x, y;
    GetSize(&x, &y);
    if(ScrollBar1)
    {
        int sx, sy;
        SetSize( wxSize(x, showLines*15+4));
        ScrollBar1->GetSize(&sx, &sy);
        GetSize(&x, &y);
        ScrollBar1->SetPosition( wxPoint(x-sx-3, 0));
        ScrollBar1->SetSize(sx, y-3);
        ScrollBar1->SetScrollbar(0, showLines, m_strings_items.size(), showLines-1);
        ScrollBar1->SetThumbPosition(m_selection);
    }
}

void ComboBoxMapPopup::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    // draw a rectangle
    int width, height;
    GetSize(&width, &height);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.SetPen( *wxTRANSPARENT_PEN);
    dc.DrawRectangle( 0, 0, width-4, height );
    int scrollPos = ScrollBar1->GetThumbPosition();
    m_textHeight = GetCharHeight();
    for(int i=0; i<showLines && (scrollPos+i) < m_strings_items.size(); ++i)
    {
        if((scrollPos+i) == m_highlightedItem)
        {
            dc.SetBrush( wxBrush( wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT)) );
            dc.SetPen( *wxTRANSPARENT_PEN);
            dc.DrawRectangle( 0, (m_highlightedItem-scrollPos)*m_textHeight, width, m_textHeight);
            dc.SetPen( *wxWHITE_PEN );
            dc.DrawText(m_strings_items[scrollPos+i].second, 3, i*m_textHeight);
        }
        else
        {
            dc.SetPen( *wxBLACK_PEN );
            dc.DrawText(m_strings_items[scrollPos+i].second, 3, i*m_textHeight);
        }
    }
}

void ComboBoxMapPopup::Clear()
{
    m_strings_items.clear();
}

bool ComboBoxMapPopup::SetSelection(int n)
{
    int index = 0;
    for(unsigned i=0; i<m_strings_items.size(); ++i)
    {
        if(m_strings_items[i].first == n)
        {
            m_selection = index;
            m_highlightedItem = m_selection;
            return true;
        }
        ++index;
    }
    return false;
}
int ComboBoxMapPopup::GetSelection()
{
    if(m_selection == -1)
        return -1;
    return m_strings_items[m_selection].first;
}

int ComboBoxMapPopup::GetSelectionIndex()
{
    return m_selection;
}

void ComboBoxMapPopup::OnMyEvent(wxCommandEvent& event)
{
    event.Skip();
}

void ComboBoxMapPopup::SendComboboxEvent()
{
    wxCommandEvent event(wxEVT_COMBOBOX);
    event.SetId(m_myID);
    event.SetInt(m_strings_items[m_selection].first);
    event.SetEventObject((wxObject *)this);

    char ctemp[80];
    sprintf(ctemp, "%s", m_strings_items[m_selection].second.ToStdString().c_str());
    event.SetString(m_strings_items[m_selection].second);
    GetParent()->GetEventHandler()->ProcessEvent(event);
}

bool ComboBoxMapPopup::FindItem(const wxString &item, wxString *trueItem)
{
    for(unsigned int i=0; i<m_strings_items.size(); ++i)
    {
        if(m_strings_items[i].second == item)
        {
            SetSelection(i);
            return true;
            break;
        }
    }
    return false;
}

int ComboBoxMapPopup::FindStringIndex(const std::string &str)
{
    for(unsigned int i=0; i<m_strings_items.size(); ++i)
    {
        if(m_strings_items[i].second == str)
        {
            return i;
        }
    }
    return -1;
}

int ComboBoxMapPopup::Set(const std::vector<cmbKeyValuePair> keyVals)
{
    m_strings_items = keyVals;
    if(m_strings_items.size() < 10)
    {
        showLines = m_strings_items.size();
        ScrollBar1->Hide();
    }
    else
    {
        showLines = 10;
        ScrollBar1->Show(true);
    }
    return 0;
}

void ComboBoxMapPopup::OnEraseBackGround(wxEraseEvent& event)
{

}

void ComboBoxMapPopup::OnMouseWheelMoved(wxMouseEvent &event)
{
    if(event.GetWheelRotation() < 0)
    {
        ScrollBar1->LineDown();
    }
    else if(event.GetWheelRotation() > 0)
    {
        ScrollBar1->LineUp();
    }
}

BEGIN_EVENT_TABLE(ComboBoxMapPopup, wxControl)
    EVT_LEFT_UP(ComboBoxMapPopup::OnMouseClick)
    EVT_PAINT(ComboBoxMapPopup::OnPaint)
    EVT_COMBOBOX(wxID_ANY, ComboBoxMapPopup::OnMyEvent)
    EVT_MOTION(ComboBoxMapPopup::OnMouseMove)
    EVT_ERASE_BACKGROUND(ComboBoxMapPopup::OnEraseBackGround)
    EVT_MOUSEWHEEL(ComboBoxMapPopup::OnMouseWheelMoved)
END_EVENT_TABLE()

