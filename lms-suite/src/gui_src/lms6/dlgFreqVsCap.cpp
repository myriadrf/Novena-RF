#include "dlgFreqVsCap.h"

//(*InternalHeaders(dlgFreqVsCap)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "LMS6002_MainControl.h"
#include <wx/filedlg.h>
#include "PLL.h"

//(*IdInit(dlgFreqVsCap)
const long dlgFreqVsCap::ID_SPINCTRL1 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON1 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON2 = wxNewId();
const long dlgFreqVsCap::ID_GRID1 = wxNewId();
const long dlgFreqVsCap::ID_PANEL1 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL2 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON3 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON4 = wxNewId();
const long dlgFreqVsCap::ID_GRID2 = wxNewId();
const long dlgFreqVsCap::ID_PANEL2 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL3 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON5 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON6 = wxNewId();
const long dlgFreqVsCap::ID_GRID3 = wxNewId();
const long dlgFreqVsCap::ID_PANEL3 = wxNewId();
const long dlgFreqVsCap::ID_SPINCTRL4 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON7 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON8 = wxNewId();
const long dlgFreqVsCap::ID_GRID4 = wxNewId();
const long dlgFreqVsCap::ID_PANEL4 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON9 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON10 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON11 = wxNewId();
const long dlgFreqVsCap::ID_BUTTON12 = wxNewId();
//*)

using namespace lms6;

BEGIN_EVENT_TABLE(dlgFreqVsCap,wxDialog)
	//(*EventTable(dlgFreqVsCap)
	//*)
END_EVENT_TABLE()

dlgFreqVsCap::dlgFreqVsCap(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    lmsControl = NULL;
    m_Rx = false;
	BuildContent(parent,id,pos,size);
}

void dlgFreqVsCap::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgFreqVsCap)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Frequency vs Capacitance"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO1Pts = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL1"));
	txtVCO1Pts->SetValue(_T("3"));
	FlexGridSizer3->Add(txtVCO1Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO1_RFCnt = new wxButton(Panel1, ID_BUTTON1, _("Set VCO1 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnSetVCO1_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO1 = new wxButton(Panel1, ID_BUTTON2, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnViewGrphVCO1->Disable();
	FlexGridSizer3->Add(btnViewGrphVCO1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	grdVco1->CreateGrid(3,2);
	grdVco1->EnableEditing(true);
	grdVco1->EnableGridLines(true);
	grdVco1->SetRowLabelSize(48);
	grdVco1->SetDefaultColSize(100, true);
	grdVco1->SetColLabelValue(0, _("Vco1 Freq. GHz"));
	grdVco1->SetColLabelValue(1, _("Vco1 Cap "));
	grdVco1->SetDefaultCellFont( grdVco1->GetFont() );
	grdVco1->SetDefaultCellTextColour( grdVco1->GetForegroundColour() );
	FlexGridSizer2->Add(grdVco1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO2Pts = new wxSpinCtrl(Panel2, ID_SPINCTRL2, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL2"));
	txtVCO2Pts->SetValue(_T("3"));
	FlexGridSizer5->Add(txtVCO2Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO2_RFCnt = new wxButton(Panel2, ID_BUTTON3, _("Set VCO2 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer5->Add(btnSetVCO2_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO2 = new wxButton(Panel2, ID_BUTTON4, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	btnViewGrphVCO2->Disable();
	FlexGridSizer5->Add(btnViewGrphVCO2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco2 = new wxGrid(Panel2, ID_GRID2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID2"));
	grdVco2->CreateGrid(3,2);
	grdVco2->EnableEditing(true);
	grdVco2->EnableGridLines(true);
	grdVco2->SetRowLabelSize(48);
	grdVco2->SetDefaultColSize(100, true);
	grdVco2->SetColLabelValue(0, _("Vco2 Freq. GHz"));
	grdVco2->SetColLabelValue(1, _("Vco2 Cap "));
	grdVco2->SetDefaultCellFont( grdVco2->GetFont() );
	grdVco2->SetDefaultCellTextColour( grdVco2->GetForegroundColour() );
	FlexGridSizer4->Add(grdVco2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(FlexGridSizer4);
	FlexGridSizer4->Fit(Panel2);
	FlexGridSizer4->SetSizeHints(Panel2);
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3 = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO3Pts = new wxSpinCtrl(Panel3, ID_SPINCTRL3, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL3"));
	txtVCO3Pts->SetValue(_T("3"));
	FlexGridSizer7->Add(txtVCO3Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO3_RFCnt = new wxButton(Panel3, ID_BUTTON5, _("Set VCO3 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer7->Add(btnSetVCO3_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO3 = new wxButton(Panel3, ID_BUTTON6, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	btnViewGrphVCO3->Disable();
	FlexGridSizer7->Add(btnViewGrphVCO3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco3 = new wxGrid(Panel3, ID_GRID3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID3"));
	grdVco3->CreateGrid(3,2);
	grdVco3->EnableEditing(true);
	grdVco3->EnableGridLines(true);
	grdVco3->SetRowLabelSize(48);
	grdVco3->SetDefaultColSize(100, true);
	grdVco3->SetColLabelValue(0, _("Vco3 Freq. GHz"));
	grdVco3->SetColLabelValue(1, _("Vco3 Cap "));
	grdVco3->SetDefaultCellFont( grdVco3->GetFont() );
	grdVco3->SetDefaultCellTextColour( grdVco3->GetForegroundColour() );
	FlexGridSizer6->Add(grdVco3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Panel3);
	FlexGridSizer6->SetSizeHints(Panel3);
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	txtVCO4Pts = new wxSpinCtrl(Panel4, ID_SPINCTRL4, _T("3"), wxDefaultPosition, wxSize(49,21), 0, 0, 100, 3, _T("ID_SPINCTRL4"));
	txtVCO4Pts->SetValue(_T("3"));
	FlexGridSizer9->Add(txtVCO4Pts, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSetVCO4_RFCnt = new wxButton(Panel4, ID_BUTTON7, _("Set VCO4 Value Count"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer9->Add(btnSetVCO4_RFCnt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnViewGrphVCO4 = new wxButton(Panel4, ID_BUTTON8, _("Graph"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	btnViewGrphVCO4->Disable();
	FlexGridSizer9->Add(btnViewGrphVCO4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	grdVco4 = new wxGrid(Panel4, ID_GRID4, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID4"));
	grdVco4->CreateGrid(3,2);
	grdVco4->EnableEditing(true);
	grdVco4->EnableGridLines(true);
	grdVco4->SetRowLabelSize(48);
	grdVco4->SetDefaultColSize(100, true);
	grdVco4->SetColLabelValue(0, _("Vco4 Freq. GHz"));
	grdVco4->SetColLabelValue(1, _("Vco4 Cap "));
	grdVco4->SetDefaultCellFont( grdVco4->GetFont() );
	grdVco4->SetDefaultCellTextColour( grdVco4->GetForegroundColour() );
	FlexGridSizer8->Add(grdVco4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(FlexGridSizer8);
	FlexGridSizer8->Fit(Panel4);
	FlexGridSizer8->SetSizeHints(Panel4);
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	OKBtn = new wxButton(this, ID_BUTTON9, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	BoxSizer1->Add(OKBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CancelBtn = new wxButton(this, ID_BUTTON10, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	BoxSizer1->Add(CancelBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	btnLoad = new wxButton(this, ID_BUTTON11, _("Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
	BoxSizer2->Add(btnLoad, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON12, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
	BoxSizer2->Add(btnSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO1_RFCntClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnViewGrphVCO1Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO2_RFCntClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO3_RFCntClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnbtnSetVCO4_RFCntClick);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OKBtnClick);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::OnCancelBtnClick);
	Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::btnLoadClick);
	Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgFreqVsCap::btnSaveClick);
	//*)
}

dlgFreqVsCap::~dlgFreqVsCap()
{
	//(*Destroy(dlgFreqVsCap)
	//*)
}

void dlgFreqVsCap::SetTblRws(int Cnt, wxGrid *grd)
{
	if (Cnt > grd->GetRows())
	{
		for (int i = grd->GetRows(); i < Cnt; i++)
		{
		    grd->AppendRows(1);
			grd->SetCellValue(i, 0, "");
            grd->SetCellValue(i, 1, "");
		}
	}
	else
	{
        for (int i = grd->GetRows()-1; i >= Cnt; i--)
		{
		    grd->DeleteRows(i);
		}
	}
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::btnSaveClick(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "VCO Values (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_OK)
	{
        PLL *ppll;
        if(m_Rx)
            ppll = &lmsControl->m_RxPLL;
        else
            ppll = &lmsControl->m_TxPLL;
        sVcoVsCap *sVco = new sVcoVsCap();
        ConstructValues(sVco, grdVco1, txtVCO1Pts);
        ppll->setVcoCap(0, sVco);
        DestroyValues(sVco);

        sVco = new sVcoVsCap();
        ConstructValues(sVco, grdVco2, txtVCO2Pts);
        ppll->setVcoCap(1, sVco);
        DestroyValues(sVco);

        sVco = new sVcoVsCap();
        ConstructValues(sVco, grdVco3, txtVCO3Pts);
        ppll->setVcoCap(2, sVco);
        DestroyValues(sVco);

        sVco = new sVcoVsCap();
        ConstructValues(sVco, grdVco4, txtVCO4Pts);
        ppll->setVcoCap(3, sVco);
        DestroyValues(sVco);
        ppll->SaveToFile(saveFileDialog.GetPath().ToStdString().c_str());
	};
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::btnLoadClick(wxCommandEvent& event)
{
	wxFileDialog *openFileDialog = new wxFileDialog(this, _("Open file"), "", "", "VCO Values (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;
    PLL *ppll;
    if(m_Rx)
        ppll = &lmsControl->m_RxPLL;
    else
        ppll = &lmsControl->m_TxPLL;
    ppll->LoadFromFile(openFileDialog->GetPath().ToStdString().c_str());
    Initialize(lmsControl, m_Rx);
}
// ---------------------------------------------------------------------------

void dlgFreqVsCap::ConstructValues(sVcoVsCap *Vco, wxGrid *grdVco, wxSpinCtrl *VCOPts)
{
	Vco->iRef = VCOPts->GetValue();
	Vco->dFreq = new double[Vco->iRef];
	Vco->iCap = new double[Vco->iRef];
	for (int i = 0; i < Vco->iRef; i++)
	{
		Vco->dFreq[i] = 1000.0*atof((grdVco->GetCellValue(i, 0).ToStdString().c_str()));
		Vco->iCap[i] = atof((grdVco->GetCellValue(i, 1).ToStdString().c_str()));
	};
};

// ---------------------------------------------------------------------------
void dlgFreqVsCap::FormDestroy(wxCommandEvent& event)
{

}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::OKBtnClick(wxCommandEvent& event)
{
    PLL *ppll;
    if(m_Rx)
        ppll = &lmsControl->m_RxPLL;
    else
        ppll = &lmsControl->m_TxPLL;

	sVcoVsCap *sVco = new sVcoVsCap();
	ConstructValues(sVco, grdVco1, txtVCO1Pts);
	ppll->setVcoCap(0, sVco);
	DestroyValues(sVco);

	sVco = new sVcoVsCap();
	ConstructValues(sVco, grdVco2, txtVCO2Pts);
	ppll->setVcoCap(1, sVco);
	DestroyValues(sVco);

	sVco = new sVcoVsCap();
	ConstructValues(sVco, grdVco3, txtVCO3Pts);
	ppll->setVcoCap(2, sVco);
	DestroyValues(sVco);

	sVco = new sVcoVsCap();
	ConstructValues(sVco, grdVco4, txtVCO4Pts);
	ppll->setVcoCap(3, sVco);
	DestroyValues(sVco);

    EndModal(wxID_OK);
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::Initialize(LMS6002_MainControl *pControl, bool Rx)
{
    lmsControl = pControl;
    m_Rx = Rx;

    PLL *ppll;
    if(Rx)
        ppll = &lmsControl->m_RxPLL;
    else
        ppll = &lmsControl->m_TxPLL;

	ShowVCOValues(ppll->getVcoCap(0), grdVco1, txtVCO1Pts);
	ShowVCOValues(ppll->getVcoCap(1), grdVco2, txtVCO2Pts);
	ShowVCOValues(ppll->getVcoCap(2), grdVco3, txtVCO3Pts);
	ShowVCOValues(ppll->getVcoCap(3), grdVco4, txtVCO4Pts);
};

// ---------------------------------------------------------------------------

void dlgFreqVsCap::ShowVCOValues(const sVcoVsCap *Vco, wxGrid *grdVco, wxSpinCtrl *VCOPts)
{
	VCOPts->SetValue(Vco->iRef);
	SetTblRws(Vco->iRef, grdVco);
	for (int i = 0; i < Vco->iRef; i++)
	{
		grdVco->SetCellValue(i, 0, wxString::Format("%f", Vco->dFreq[i]/1000.0));
		grdVco->SetCellValue(i, 1, wxString::Format("%.0f", Vco->iCap[i]));
	};
};

void dlgFreqVsCap::OnbtnSetVCO1_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO1Pts->GetValue(), grdVco1);
}

void dlgFreqVsCap::OnbtnSetVCO2_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO2Pts->GetValue(), grdVco2);
}

void dlgFreqVsCap::OnbtnSetVCO3_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO3Pts->GetValue(), grdVco3);
}

void dlgFreqVsCap::OnbtnSetVCO4_RFCntClick(wxCommandEvent& event)
{
    SetTblRws( txtVCO4Pts->GetValue(), grdVco4);
}

void dlgFreqVsCap::OnbtnViewGrphVCO1Click(wxCommandEvent& event)
{

}

void dlgFreqVsCap::OnbtnViewGrphVCO2Click(wxCommandEvent& event)
{

}

void dlgFreqVsCap::OnbtnViewGrphVCO3Click(wxCommandEvent& event)
{

}

void dlgFreqVsCap::OnbtnViewGrphVCO4Click(wxCommandEvent& event)
{

}

void dlgFreqVsCap::OnCancelBtnClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

// ---------------------------------------------------------------------------
void dlgFreqVsCap::DestroyValues(sVcoVsCap *Vco)
{
	if (Vco->iRef)
	{
		Vco->iRef = 0;
		delete[]Vco->dFreq;
		Vco->dFreq = NULL;
		delete[]Vco->iCap;
		Vco->iCap = NULL;
	};
};
