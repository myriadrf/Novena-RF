// -----------------------------------------------------------------------------
// FILE: 		    dgRefClk.cpp
// DESCRIPTION:	Reference clock management
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dgRefClk.h"
//--------------------------------------------------------------------- 
#pragma link "CSPIN"
#pragma link "RXSpin"
#pragma resource "*.dfm"
//TdlgRefClk *dlgRefClk;
//---------------------------------------------------------------------
__fastcall TdlgRefClk::TdlgRefClk(double dFreq, TComponent* AOwner)
	: TForm(AOwner)
{
  txtRefClk->Value = dFreq;
}
//---------------------------------------------------------------------
void __fastcall TdlgRefClk::btnS01Click(TObject *Sender)
{
  txtRefClk->Value = 40;
}
//---------------------------------------------------------------------------

void __fastcall TdlgRefClk::btnS02Click(TObject *Sender)
{
  txtRefClk->Value = 30.72;  
}
//---------------------------------------------------------------------------

