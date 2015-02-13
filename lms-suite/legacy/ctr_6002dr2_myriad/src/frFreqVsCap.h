// -----------------------------------------------------------------------------
// FILE: 		    frFreqVsCap.h
// DESCRIPTION:	Header for frFreqVsCap.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef frFreqVsCapH
#define frFreqVsCapH
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
#include <Grids.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>

#include "common.h"
//----------------------------------------------------------------------------
class TdlgFreqVsCap : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
  TStringGrid *grdVco1;
  TStringGrid *grdVco2;
  TStringGrid *grdVco3;
  TStringGrid *grdVco4;
  TBitBtn *btnLoad;
  TBitBtn *btnSave;
  TMaskEdit *txtVCO2Pts;
  TBitBtn *btnSetVCO2_RFCnt;
  TMaskEdit *txtVCO1Pts;
  TBitBtn *btnSetVCO1_RFCnt;
  TMaskEdit *txtVCO3Pts;
  TBitBtn *btnSetVCO3_RFCnt;
  TMaskEdit *txtVCO4Pts;
  TBitBtn *btnSetVCO4_RFCnt;
  TOpenDialog *dlgOpen;
  TSaveDialog *dlgSave;
  TButton *btnViewGrphVCO1;
  TButton *btnViewGrphVCO2;
  TButton *btnViewGrphVCO3;
  TButton *btnViewGrphVCO4;
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall grdVco1KeyPress(TObject *Sender, char &Key);
  void __fastcall btnSetVCO1_RFCntClick(TObject *Sender);
  void __fastcall btnSetVCO2_RFCntClick(TObject *Sender);
  void __fastcall btnSetVCO3_RFCntClick(TObject *Sender);
  void __fastcall btnSetVCO4_RFCntClick(TObject *Sender);
  void __fastcall btnLoadClick(TObject *Sender);
  void __fastcall btnViewGrphVCO1Click(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall btnViewGrphVCO2Click(TObject *Sender);
  void __fastcall btnViewGrphVCO3Click(TObject *Sender);
  void __fastcall btnViewGrphVCO4Click(TObject *Sender);
  void __fastcall OKBtnClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:
  void SetTblRws(int Cnt, TStringGrid *grd);
  bool CheckValues(TStringGrid *grd);
  void ConstructValues(sVcoVsCap &Vco, TStringGrid *grdVco, TMaskEdit *VCOPts);
  void DestroyValues(sVcoVsCap &Vco);
  void SavePathToReg(String Path);
  String ReadPathFromReg();
  void LoadValuesFromFile(String FName);
  void ShowVCOValues(sVcoVsCap Vco, TStringGrid *grdVco, TMaskEdit *VCOPts);

  String m_sName;
  String m_sLastUsedVCOFile;

public:
	virtual __fastcall TdlgFreqVsCap(TComponent* AOwner);
  sVcoVsCap sVco1;
  sVcoVsCap sVco2;
  sVcoVsCap sVco3;
  sVcoVsCap sVco4;
  void Initialize(String Name);
};
//----------------------------------------------------------------------------
//extern PACKAGE TdlgFreqVsCap *dlgFreqVsCap;
//----------------------------------------------------------------------------
#endif    
