// -----------------------------------------------------------------------------
// FILE: 		    dlgRegTest.cpp
// DESCRIPTION:	Register test analysis
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "dlgRegTest.h"
#include "math.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
//TdRegTest *dRegTest;
//---------------------------------------------------------------------
__fastcall TdRegTest::TdRegTest(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TdRegTest::OKBtnClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

void __fastcall TdRegTest::CancelBtnClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

void __fastcall TdRegTest::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TdRegTest::FormCreate(TObject *Sender)
{
  reInfo->Align = alClient;
  reInfo->Lines->Clear();  
}

//---------------------------------------------------------------------------
void TdRegTest::AddLine(String Line)
{
  reInfo->Lines->Add(Line);
};

//---------------------------------------------------------------------------
void TdRegTest::Compare(sPrData *pPrData)
{
  String Str;
  BYTE itmp;
  bool bTestRez = true;
  int mask;

	for(int i=0; i<pPrData->iToW; i++)
	{
        if((pPrData->cDataW[pPrData->iWInd[i]] & pPrData->cTestMap[pPrData->iWInd[i]]) != (pPrData->cDataR[pPrData->iWInd[i]] & pPrData->cTestMap[pPrData->iWInd[i]]))
        {
          bTestRez = false;
          Str = "Reg Addr = ";
          Str = Str + pPrData->iWInd[i];
          Str = Str + " Failed (Write/Read Values): ";
          itmp = pPrData->cDataW[pPrData->iWInd[i]] & 0x00FF;
          Str = Str + IntToHex(itmp, 2);
          Str = Str + " / ";
          //itmp = pPrData->cDataR[pPrData->iWInd[i]] & (BYTE)pPrData->cTestMap[pPrData->iWInd[i]];
          itmp = pPrData->cDataR[pPrData->iWInd[i]];
          Str = Str + IntToHex(itmp, 2);
          reInfo->Lines->Add(Str);
        };
  };

  if(pPrData->iToW == 0) reInfo->Lines->Add("Length Wrong!");

  if(bTestRez)
  {
    reInfo->Lines->Add("Module test with this pattern is OK.");
  }
  else
  {
    reInfo->Lines->Add("Module test with this pattern FAILED!");
  };
};


void TdRegTest::Comparators(int Min, int Max)
{
  String Str;
  
  if((Min == 0x2) && (Max == 0x1))
  {
    AddLine("VTUNE registers are OK.");
  }
  else
  {
    AddLine("Some problems with VTUNE registers:");
    Str = "VTUNE_H (should be/acctual): 1/";
    if((Min == 0x2) && (Min == 0x0))
    {
      Str = Str + "0;";
    }
    else
    {
      Str = Str + "1;";
    };
    AddLine(Str);

    Str = "VTUNE_H (should be/acctual): 0/";
    if((Min == 0x2) && (Min == 0x0))
    {
      Str = Str + "0;";
    }
    else
    {
      Str = Str + "1;";
    };
    AddLine(Str);

    Str = "VTUNE_L (should be/acctual): 1/";
    if((Min == 0x1) && (Min == 0x0))
    {
      Str = Str + "0;";
    }
    else
    {
      Str = Str + "1;";
    };
    AddLine(Str);

    Str = "VTUNE_L (should be/acctual): 0/";
    if((Min == 0x1) && (Min == 0x0))
    {
      Str = Str + "0;";
    }
    else
    {
      Str = Str + "1;";
    };
    AddLine(Str);
  };

};
