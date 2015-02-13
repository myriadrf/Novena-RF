// -----------------------------------------------------------------------------
// FILE: 		    dgRefClk.h
// DESCRIPTION:	Header for dgRefClk.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef dgRefClkH
#define dgRefClkH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include "CSPIN.h"
#include "RXSpin.hpp"
//----------------------------------------------------------------------------
class TdlgRefClk : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
  TLabel *Label1;
  TRxSpinEdit *txtRefClk;
  TButton *btnS01;
  TButton *btnS02;
  void __fastcall btnS01Click(TObject *Sender);
  void __fastcall btnS02Click(TObject *Sender);
private:
public:
	virtual __fastcall TdlgRefClk(double dFreq, TComponent* AOwner);
};
//----------------------------------------------------------------------------
//extern PACKAGE TdlgRefClk *dlgRefClk;
//----------------------------------------------------------------------------
#endif    
