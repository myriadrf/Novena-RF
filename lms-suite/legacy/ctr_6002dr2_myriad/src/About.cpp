// -----------------------------------------------------------------------------
// FILE: 		    About.cpp
// DESCRIPTION:	About dialog box
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <ShellApi.h>

#include "About.h"
#include "common.h"
//--------------------------------------------------------------------- 
#pragma link "RxGIF"
#pragma resource "*.dfm"
//TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent *Owner)
	: TForm(Owner)
{


  sttVer->Caption = "v.6002Dr2.02.08052012_1800";

#ifndef ALTERA_EDITION
  sttAE->Visible = false;
#endif


}
//---------------------------------------------------------------------
void __fastcall TAboutBox::StaticText12Click(TObject *Sender)
{
	int result =(int)ShellExecute(0, "open", "http://myriadrf.org/", "", "", SW_SHOWNORMAL);
	if (result <= 32) ShowMessage("Unable to start web browser.");
}
//---------------------------------------------------------------------------

