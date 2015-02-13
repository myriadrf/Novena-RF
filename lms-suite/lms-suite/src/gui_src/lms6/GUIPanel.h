#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "LMS6002_MainControl.h"
#include "ParameterDescription.h"
#include "RegistersMap.h"
#include <wx/panel.h>
#include <wx/tooltip.h>
#include <wx/checkbox.h>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <stdexcept>
#include "ComboBoxMap.h"

class GUIPanel : public wxPanel
{
public:
    GUIPanel(){ lmsControl = NULL; };
    ~GUIPanel(){};

    virtual void UpdateGUI()
    {
        UpdateGUI(this);
    }

    void Initialize(lms6::LMS6002_MainControl *pControl)
    {
        lmsControl = pControl;
        UpdateTooltips(this);
        UpdateGUI(this);
    }

protected:
    virtual void UpdateGUI(wxWindow *pwnd)
    {
        if(lmsControl == NULL)
            return;

        wxWindowList childs;
        childs = pwnd->GetChildren();
        wxWindow *wnd;
        wxWindowList::iterator iter;

        std::map<long, lms6::LMS_Parameter>::iterator id_param_pair;
        unsigned long value = 0;
        wxClassInfo *wndClass;
        wxClassInfo *cmbInfo =  wxClassInfo::FindClass(_("wxComboBox"));
        wxClassInfo *cmbMapInfo =  wxClassInfo::FindClass(_("ComboBoxMap"));
        wxClassInfo *chkInfo =  wxClassInfo::FindClass(_("wxCheckBox"));
        wxClassInfo *rgrInfo =  wxClassInfo::FindClass(_("wxRadioBox"));
        wxClassInfo *notebookInfo =  wxClassInfo::FindClass(_("wxNotebook"));
        wxClassInfo *panelInfo =  wxClassInfo::FindClass(_("wxPanel"));
        wxClassInfo *labelInfo =  wxClassInfo::FindClass(_("wxStaticText"));

        for(iter = childs.begin(); iter != childs.end(); ++iter)
        {
            wnd = *iter;
            wndClass = wnd->GetClassInfo();
            if(wndClass->IsKindOf(notebookInfo) || wndClass->IsKindOf(panelInfo))
            {
                UpdateGUI(wnd); //recursive call needed because getChildren returns child notebooks and panels, without their inner childs
            }
            id_param_pair = wndId2Enum.find(wnd->GetId());

            if(id_param_pair == wndId2Enum.end())
                continue; //skip controls that don't have assigned LMS parameter
            value = lmsControl->GetParam(id_param_pair->second);
            //cast window to specific control, to set value, or set selection
            if(wndClass->IsKindOf(cmbInfo))
            {
                wxComboBox *box = wxStaticCast(wnd, wxComboBox);
                if(box->GetCount() < value)
                {
                    lms6::Parameter cp = lmsControl->getRegistersMap()->getParameterInfo( id_param_pair->second );
                    wxString str;
                    str = wxString::Format("%s value(%i) is out of range [0-%i]", cp.name, value, box->GetCount()-1);
                    wxMessageBox(str, "WARNING!");
                    value = 0;
                }
                box->SetSelection(value);
            }
            else if(wndClass->IsKindOf(cmbMapInfo))
            {
                wxStaticCast(wnd, ComboBoxMap)->SetSelection(value);
            }
            else if(wndClass->IsKindOf(chkInfo))
            {
                if(m_checkboxIDToInvert.find(wnd->GetId()) != m_checkboxIDToInvert.end())
                {
                    if(value != 0)
                        value = 0;
                    else
                        value = 1;
                }
                wxStaticCast(wnd, wxCheckBox)->SetValue(value);
            }
            else if(wndClass->IsKindOf(rgrInfo))
            {
                wxRadioBox *box = wxStaticCast(wnd, wxRadioBox);
                bool radiomap = id_param_pair->second != lms6::FRANGE_RXPLL || id_param_pair->second != lms6::FRANGE_TXPLL ||
                                id_param_pair->second != lms6::SELVCO_RXPLL || id_param_pair->second != lms6::SELVCO_TXPLL;
                if(box->GetCount() < value && !radiomap)
                {
                    lms6::Parameter cp = lmsControl->getRegistersMap()->getParameterInfo( id_param_pair->second );
                    wxString str;
                    str = wxString::Format("%s value(%i) is out of range [0-%i]", cp.name, value, box->GetCount()-1);
                    wxMessageBox(str, "WARNING!");
                    value = 0;
                }
                box->SetSelection(value);
            }
            else if(wndClass->IsKindOf(labelInfo))
            {
                wxStaticCast(wnd, wxStaticText)->SetLabel( wxString::Format(_("%li"), value) );
            }
        }
    }

    virtual void UpdateTooltips(wxWindow* panel)
    {
        if(lmsControl == NULL)
            return;
        wxWindow *field = NULL;
        std::map<long, lms6::LMS_Parameter>::iterator fieldIds;
        wxString sttip = "";
        for(fieldIds = wndId2Enum.begin(); fieldIds != wndId2Enum.end(); ++fieldIds)
        {
            field = panel->FindWindow(fieldIds->first);
            wxToolTip *ttip = NULL;
            ttip = field->GetToolTip();
            if(ttip)
                sttip = ttip->GetTip();
            else
                sttip = "";

            lms6::Parameter cp = lmsControl->getRegistersMap()->getParameterInfo( fieldIds->second );
            if(cp.bitsCount == 0)
                cout << "Warning: bit count = 0" << endl;
            char cname[64];
            sprintf(cname, "%s", cp.name.c_str());
            char caddr[64];
            memset(caddr, 0, sizeof(caddr));
            if(cp.bitsCount == 1)
                sprintf(caddr, "0x%.2X[%i]", cp.registers[0].addr, cp.registers[0].lsb);
            else
            {
                char ctemp[64];
                memset(ctemp, 0, sizeof(ctemp));
                for(int i=cp.piecesCount-1; i>=0; --i)
                {
                    sprintf(ctemp, "%s 0x%.2X[%i:%i]", caddr, cp.registers[i].addr, cp.registers[i].msb, cp.registers[i].lsb);
                    strcpy(caddr, ctemp);
                }
            }
            if(sttip.length() > 0)
                field->SetToolTip( wxString::Format("%s.\n %s %s", sttip.c_str(), caddr, cname) );
            else
                field->SetToolTip( wxString::Format("%s %s", caddr, cname) );
            ttip = field->GetToolTip();
        }
    }

    virtual void ParameterChangeHandler(wxCommandEvent& event)
    {
        unsigned long value = event.GetInt();
        char ctemp[80];
        sprintf(ctemp, "%s", event.GetString().ToStdString().c_str());
        if(m_checkboxIDToInvert.find( ((wxWindow*)event.GetEventObject())->GetId()) != m_checkboxIDToInvert.end())
        {
            if(value != 0)
                value = 0;
            else
                value = 1;
        }
        if(lmsControl == NULL)
        {
            std::cout << "panel don't have control module assigned" << std::endl;
            return;
        }

        lms6::LMS_Parameter parameter;
        try
        {
            parameter = wndId2Enum.at(event.GetId());
        }
        catch( std::out_of_range &e )
        {
            std::cout << "Control element(ID = " << event.GetId() << ") don't have assigned LMS parameter enumeration." << std::endl;
            return;
        }
        lmsControl->SetParam( parameter, value);
        UpdateGUI(this);
    }

    std::set<long> m_checkboxIDToInvert;
    std::map<long, lms6::LMS_Parameter> wndId2Enum;
    lms6::LMS6002_MainControl *lmsControl;
};

#endif // GUI_PANEL_H

