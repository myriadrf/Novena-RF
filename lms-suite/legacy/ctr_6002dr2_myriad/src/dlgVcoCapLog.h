// -----------------------------------------------------------------------------
// FILE: 		    dlgVcoCapLog.h
// DESCRIPTION:	Header for dlgVcoCapLog.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef dlgVcoCapLogH
#define dlgVcoCapLogH
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
//----------------------------------------------------------------------------
class TdVcoCapLog : public TForm
{
__published:
  TMemo *memLogText;
  void __fastcall FormCreate(TObject *Sender);
private:
public:
	virtual __fastcall TdVcoCapLog(TComponent* AOwner);
};
//----------------------------------------------------------------------------
//extern PACKAGE TdVcoCapLog *dVcoCapLog;
//----------------------------------------------------------------------------
#endif    
