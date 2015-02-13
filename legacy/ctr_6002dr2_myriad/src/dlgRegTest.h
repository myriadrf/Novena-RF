// -----------------------------------------------------------------------------
// FILE: 		    dlgRegTest.h
// DESCRIPTION:	Header for dlgRegTest.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef dlgRegTestH
#define dlgRegTestH
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
#include <ComCtrls.hpp>

#include "common.h"
//----------------------------------------------------------------------------
class TdRegTest : public TForm
{
__published:
  TPanel *Panel1;
  TButton *OKBtn;
  TButton *CancelBtn;
  TRichEdit *reInfo;
  void __fastcall OKBtnClick(TObject *Sender);
  void __fastcall CancelBtnClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormCreate(TObject *Sender);
private:
public:
	virtual __fastcall TdRegTest(TComponent* AOwner);

  void AddLine(String Line);
  void Compare(sPrData *pPrData);
  void Comparators(int Min, int Max);
};
//----------------------------------------------------------------------------
//extern PACKAGE TOKBottomDlg *OKBottomDlg;
//----------------------------------------------------------------------------
#endif    
