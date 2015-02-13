#ifndef PNLNOVENA_H
#define PNLNOVENA_H

#include "oglGraph/OpenGLGraph.h"

//(*Headers(pnlNovena)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "PluginPanel.h"
namespace lms6
{
    class LMS6002_MainControl;
}
class OpenGLGraph;

class pnlNovena: public wxPanel, public PluginPanel
{
	public:

		pnlNovena(wxWindow* parent,wxWindowID id=wxID_ANY);
		void Initialize(lms6::LMS6002_MainControl* pControl);
		virtual ~pnlNovena();

		//(*Declarations(pnlNovena)
		wxButton* btnFillFIFO;
		wxButton* btnEIMsetup;
		wxStaticText* StaticText1;
		wxButton* btnReadNCO;
		wxRadioBox* rgrDataSource;
		wxButton* btnWriteNCO;
		wxTextCtrl* txtFPGA_NCO_MHz;
		wxButton* btnReadFIFO;
		//*)

	protected:
        OpenGLGraph *m_gltimePlot;
        OpenGLGraph *m_glconstellationPlot;
        lms6::LMS6002_MainControl* lmsControl;
		//(*Identifiers(pnlNovena)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_RADIOBOX1;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(pnlNovena)
		void OnbtnWriteNCOClick(wxCommandEvent& event);
		void OnbtnReadNCOClick(wxCommandEvent& event);
		void OnbtnFillFIFOClick(wxCommandEvent& event);
		void OnbtnReadFIFOClick(wxCommandEvent& event);
		void OnbtnEIMsetupClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
