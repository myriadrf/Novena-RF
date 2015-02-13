#ifndef DLGEXTRACONTROLS_H
#define DLGEXTRACONTROLS_H

//(*Headers(dlgExtraControls)
#include <wx/sizer.h>
#include <wx/dialog.h>
//*)

#include "LMS_Commands.h"
#include <wx/radiobox.h>
#include <wx/checkbox.h>

class ConnectionManager;
class SamplesCollector;

class dlgExtraControls: public wxDialog
{
	public:

		dlgExtraControls(wxWindow* parent, ConnectionManager *serPort, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgExtraControls();

		//(*Declarations(dlgExtraControls)
		wxFlexGridSizer* m_checkboxes;
		wxFlexGridSizer* m_controlsSizer;
		//*)

		void SetSamplesCollector(SamplesCollector *pCollector);

		wxRadioBox *rxDataSource;
	protected:
        ConnectionManager *m_serPort;
        SamplesCollector *m_collector;
	    void createControls(int dev_type);

        void onRxDataSourceChangeNovena(wxCommandEvent &evt);
	    void onRxDataSourceChange(wxCommandEvent &evt);
	    void onUSBFIFOReset(wxCommandEvent &evt);
        void onFPGAReset(wxCommandEvent &evt);
        void onResetSeq(wxCommandEvent &evt);
		//(*Identifiers(dlgExtraControls)
		//*)

	private:
        wxCheckBox *chkFPGATransmitter;
        wxCheckBox *chkFPGAReceiver;
        wxCheckBox *chkUSBFIFOReset;
        wxCheckBox *chkTxEN;
        wxCheckBox *chkRxEN;
        wxCheckBox *chkFPGAReset;
        wxCheckBox *chkWFMload;
        wxButton *btnResetSeq;
		//(*Handlers(dlgExtraControls)
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
