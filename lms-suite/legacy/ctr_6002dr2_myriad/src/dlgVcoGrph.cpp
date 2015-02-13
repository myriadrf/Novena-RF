// -----------------------------------------------------------------------------
// FILE: 		    dlgVcoGrph.cpp
// DESCRIPTION:	CAP selection graph using quadratic interpolation
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dlgVcoGrph.h"
#include "common.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
//TdlgGraph *dlgGraph;

//---------------------------------------------------------------------
__fastcall TdlgGraph::TdlgGraph(TComponent* AOwner)
	: TForm(AOwner)
{
}

//---------------------------------------------------------------------
void __fastcall TdlgGraph::FormCreate(TObject *Sender)
{
  chrtVcos->Align = alClient;
  serVco1R->FillSampleValues(20);
  serVco1M->FillSampleValues(20);
}
//---------------------------------------------------------------------------

void TdlgGraph::SetValues(int iRefVCnt, double *dFVco, double *dCVco)
{
  serVco1R->Clear();
  for(int i=0; i<iRefVCnt; i++)
  {
    serVco1R->AddXY(dFVco[i], dCVco[i], "", clGreen);
  };

  serVco1M->Clear();
  for(double d=dFVco[0]; d<=dFVco[iRefVCnt-1]; d += 0.05)
  {
    serVco1M->AddXY(d, QuadraticInterpol(iRefVCnt, dFVco, dCVco, d), "", clRed);
  };

};
