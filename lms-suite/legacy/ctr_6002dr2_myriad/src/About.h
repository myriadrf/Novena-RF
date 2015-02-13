// -----------------------------------------------------------------------------
// FILE: 		    About.h
// DESCRIPTION:	Header for About.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include "RxGIF.hpp"
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TButton *OKButton;
	TStaticText *StaticText1;
	TStaticText *StaticText12;
  TStaticText *sttVer;
  TStaticText *sttAE;
        TImage *Image;
	void __fastcall StaticText12Click(TObject *Sender);
private:
public:
	virtual __fastcall TAboutBox(TComponent *Owner);
};
//----------------------------------------------------------------------------
//extern TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif	
