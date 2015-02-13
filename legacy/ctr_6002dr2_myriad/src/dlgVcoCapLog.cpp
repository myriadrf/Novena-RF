// -----------------------------------------------------------------------------
// FILE: 		    dlgVcoCapLog.cpp
// DESCRIPTION:	Log box for VCO CAP selection procedures
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dlgVcoCapLog.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
//TdVcoCapLog *dVcoCapLog;
//---------------------------------------------------------------------
__fastcall TdVcoCapLog::TdVcoCapLog(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TdVcoCapLog::FormCreate(TObject *Sender)
{
  memLogText->Align = alClient;
  memLogText->Lines->Clear();  
}
//---------------------------------------------------------------------------


