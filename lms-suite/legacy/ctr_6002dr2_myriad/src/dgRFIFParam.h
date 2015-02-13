// -----------------------------------------------------------------------------
// FILE: 		    dgRFIFParam.h
// DESCRIPTION:	Header for dgRFIFParam.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef dgRFIFParamH
#define dgRFIFParamH
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
class TdlgRFIFParam : public TForm
{
__published:
  TButton *btnOK;
  TButton *btnCancel;
  TEdit *txtValue;
  TLabel *Label1;
  void __fastcall txtValueKeyPress(TObject *Sender, char &Key);
private:
public:
	virtual __fastcall TdlgRFIFParam(TComponent* AOwner);
};
//----------------------------------------------------------------------------
//extern PACKAGE TdlgRFIFParam *dlgRFIFParam;
//----------------------------------------------------------------------------
#endif    
