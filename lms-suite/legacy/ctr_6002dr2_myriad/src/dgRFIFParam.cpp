// -----------------------------------------------------------------------------
// FILE: 		    dgRFIFParam.cpp
// DESCRIPTION:	Dialog window. Used to select Chip Select Code parameter
//              when making RFIF report.
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dgRFIFParam.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
//TdlgRFIFParam *dlgRFIFParam;
//---------------------------------------------------------------------
__fastcall TdlgRFIFParam::TdlgRFIFParam(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TdlgRFIFParam::txtValueKeyPress(TObject *Sender, char &Key)
{
  if (((Key <'0') || (Key >'9' && Key < 'A') || (Key > 'F' && Key <'a') || (Key > 'f')) && (Key != VK_BACK) && (Key != 'x') && (Key != 'X'))
  {
    //ShowMessage("Non hexadecimal is not allowed");
    Key = 0;
  }

}
//---------------------------------------------------------------------------

