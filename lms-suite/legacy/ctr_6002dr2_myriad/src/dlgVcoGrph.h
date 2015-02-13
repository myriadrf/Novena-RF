// -----------------------------------------------------------------------------
// FILE: 		    dlgVcoGrph.h
// DESCRIPTION:	Header for dlgVcoGrph.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef dlgVcoGrphH
#define dlgVcoGrphH
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
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//----------------------------------------------------------------------------
class TdlgGraph : public TForm
{
__published:
  TChart *chrtVcos;
  TFastLineSeries *serVco1R;
  TFastLineSeries *serVco1M;
  void __fastcall FormCreate(TObject *Sender);
private:
public:
	virtual __fastcall TdlgGraph(TComponent* AOwner);
  void SetValues(int iRefVCnt, double *dFVco, double *dCVco);
};
//----------------------------------------------------------------------------
//extern PACKAGE TdlgGraph *dlgGraph;
//----------------------------------------------------------------------------
#endif    
