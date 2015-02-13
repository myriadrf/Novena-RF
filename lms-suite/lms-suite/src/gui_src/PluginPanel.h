#ifndef MODULE_PANEL_H
#define MODULE_PANEL_H

#include <wx/wx.h>

enum ePLUGINS_CONFIGURATION
{
    PLUGINS_NONE = 0,
    PLUGINS_EVB6 = 1,
    PLUGINS_DIGIGREEN = 2,
    PLUGINS_DIGIRED = 4,
    PLUGINS_ZIPPER = 8,
    PLUGINS_NOVENA = 16,
    PLUGINS_STREAM = 32,

    PLUGINS_ALL = 0xFFFFFFFF,
};

class PluginPanel
{
public:
    PluginPanel(wxWindow* window) : m_window(window), m_assignedPluginsConfigurations(PLUGINS_NONE)
    {
    }
    virtual ~PluginPanel(){};
    virtual void UpdatePanel(){};
    void AssignToConfigurations(unsigned long plugins_config_flags) {m_assignedPluginsConfigurations = plugins_config_flags;};
    unsigned long GetAssignedConfigurations() {return m_assignedPluginsConfigurations;};
    wxWindow* GetPluginWindow() {return m_window;};
protected:
    wxWindow* m_window;
    unsigned long m_assignedPluginsConfigurations;
};

#endif // MODULE_PANEL_H

