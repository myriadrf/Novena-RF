// -----------------------------------------------------------------------------
// FILE: 		    frFreqVsCap.cpp
// DESCRIPTION:	VCO calibration form
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include<string>
#include <Registry.hpp>
#include <dir.h>

#pragma hdrstop

#include "frFreqVsCap.h"
#include "dlgVcoGrph.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
//TdlgFreqVsCap *dlgFreqVsCap;
//---------------------------------------------------------------------
__fastcall TdlgFreqVsCap::TdlgFreqVsCap(TComponent* AOwner)
	: TForm(AOwner)
{
  grdVco1->Cells[0][0] = "Nr.";
  grdVco1->Cells[1][0] = "Vco4 Freq., GHz";
  grdVco1->Cells[2][0] = "Vco4 Cap";
  grdVco2->Cells[0][0] = "Nr.";
  grdVco2->Cells[1][0] = "Vco3 Freq., GHz";
  grdVco2->Cells[2][0] = "Vco3 Cap";
  grdVco3->Cells[0][0] = "Nr.";
  grdVco3->Cells[1][0] = "Vco2 Freq., GHz";
  grdVco3->Cells[2][0] = "Vco2 Cap";
  grdVco4->Cells[0][0] = "Nr.";
  grdVco4->Cells[1][0] = "Vco1 Freq., GHz";
  grdVco4->Cells[2][0] = "Vco1 Cap";

  grdVco1->Cells[1][1] = "3.76";
  grdVco1->Cells[2][1] = "0";
  grdVco1->Cells[1][2] = "4.20";
  grdVco1->Cells[2][2] = "31";
  grdVco1->Cells[1][3] = "4.84";
  grdVco1->Cells[2][3] = "63";

  grdVco2->Cells[1][1] = "4.6800";
  grdVco2->Cells[2][1] = "0";
  grdVco2->Cells[1][2] = "5.32";
  grdVco2->Cells[2][2] = "31";
  grdVco2->Cells[1][3] = "6.04";
  grdVco2->Cells[2][3] = "63";

  grdVco3->Cells[1][1] = "5.72";
  grdVco3->Cells[2][1] = "0";
  grdVco3->Cells[1][2] = "6.44";
  grdVco3->Cells[2][2] = "31";
  grdVco3->Cells[1][3] = "7.36";
  grdVco3->Cells[2][3] = "63";

  grdVco4->Cells[1][1] = "6.92";
  grdVco4->Cells[2][1] = "0";
  grdVco4->Cells[1][2] = "7.36";
  grdVco4->Cells[2][2] = "31";
  grdVco4->Cells[1][3] = "8.398";
  grdVco4->Cells[2][3] = "63";

  grdVco1->ColWidths[0] = 35;
  grdVco1->ColWidths[1] = 90;
  grdVco1->ColWidths[2] = 90;
  grdVco2->ColWidths[0] = 35;
  grdVco2->ColWidths[1] = 90;
  grdVco2->ColWidths[2] = 90;
  grdVco3->ColWidths[0] = 35;
  grdVco3->ColWidths[1] = 90;
  grdVco3->ColWidths[2] = 90;
  grdVco4->ColWidths[0] = 35;
  grdVco4->ColWidths[1] = 90;
  grdVco4->ColWidths[2] = 90;

  sVco1.iRef = 0;
  sVco1.dFreq = NULL;
  sVco1.iCap = NULL;
  sVco2.iRef = 0;
  sVco2.dFreq = NULL;
  sVco2.iCap = NULL;
  sVco3.iRef = 0;
  sVco3.dFreq = NULL;
  sVco3.iCap = NULL;
  sVco4.iRef = 0;
  sVco4.dFreq = NULL;
  sVco4.iCap = NULL;

  ConstructValues(sVco1, grdVco1, txtVCO1Pts);
  ConstructValues(sVco2, grdVco2, txtVCO2Pts);
  ConstructValues(sVco3, grdVco3, txtVCO3Pts);
  ConstructValues(sVco4, grdVco4, txtVCO4Pts);

  m_sLastUsedVCOFile = "";
}
//---------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::grdVco1KeyPress(TObject *Sender, char &Key)
{
  std::string str = "+-1234567890.";
  if( str.find(Key) == std::string::npos && Key != VK_BACK && Key != VK_RETURN )
  {
    //ShowMessage("Allowed Input: +-1234567890.");
    Key = 0;
  }  
}
//---------------------------------------------------------------------------
void TdlgFreqVsCap::SetTblRws(int Cnt, TStringGrid *grd)
{
  grd->RowCount = Cnt;
  for(int i=1; i<=grdVco1->RowCount; i++)
  {
    grd->Cells[0][i] = i;
  };
};
//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::btnSetVCO1_RFCntClick(TObject *Sender)
{
  SetTblRws(atoi(txtVCO1Pts->Text.c_str()) + 1, grdVco1);
}
//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnSetVCO2_RFCntClick(TObject *Sender)
{
  SetTblRws(atoi(txtVCO2Pts->Text.c_str()) + 1, grdVco2);  
}
//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnSetVCO3_RFCntClick(TObject *Sender)
{
  SetTblRws(atoi(txtVCO3Pts->Text.c_str()) + 1, grdVco3);  
}
//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnSetVCO4_RFCntClick(TObject *Sender)
{
  SetTblRws(atoi(txtVCO4Pts->Text.c_str()) + 1, grdVco4);  
}
//---------------------------------------------------------------------------

bool TdlgFreqVsCap::CheckValues(TStringGrid *grd)
{
  double dtry;
  char *ends;
  for(int i=1; i<=grdVco1->RowCount; i++)
  {
      dtry = strtod(grd->Cells[1][i].c_str(), &ends);
      if(*ends != NULL)
      {
        //ShowMessage("Allowed Input: +-1234567890.");
        return false;
      };

      dtry = strtod(grd->Cells[2][i].c_str(), &ends);
      if(*ends != NULL)
      {
        //ShowMessage("Allowed Input: +-1234567890.");
        return false;
      };
  };
  return true;
};

//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::btnSaveClick(TObject *Sender)
{
  HANDLE pfItems;
	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";
  DWORD writen;
  int iCnt;
  double dTmp;

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
  dlgSave->DefaultExt = "vco";
  dlgSave->FileName = "*.vco";
  dlgSave->Filter = "VCO values (*.vco)|*.vco";
  dlgSave->InitialDir = drive;
  dlgSave->InitialDir = dlgSave->InitialDir + dir;

  if(dlgSave->Execute())
  {
    //Check values
    if(!CheckValues(grdVco1))
    {
      ShowMessage("Allowed Input in Table for VCO1: +-1234567890.\nValues are not Saved To the File!");
      return;
    };
    if(!CheckValues(grdVco2))
    {
      ShowMessage("Allowed Input in Table for VCO2: +-1234567890.\nValues are not Saved To the File!");
      return;
    };
    if(!CheckValues(grdVco3))
    {
      ShowMessage("Allowed Input in Table for VCO3: +-1234567890.\nValues are not Saved To the File!");
      return;
    };
    if(!CheckValues(grdVco4))
    {
      ShowMessage("Allowed Input in Table for VCO4: +-1234567890.\nValues are not Saved To the File!");
      return;
    };


    pfItems = CreateFile(
      dlgSave->FileName.c_str(),//name of the file
      GENERIC_WRITE,//desired access
      FILE_SHARE_READ,//share mode
      NULL,//security attributes
      CREATE_ALWAYS,//creation disposition
      FILE_ATTRIBUTE_NORMAL,// | FILE_FLAG_WRITE_THROUGH , //flags and attr
      NULL);//template file
    if(pfItems == INVALID_HANDLE_VALUE)
    {
      ShowMessage("Can not Create File.\nValues are not Saved To the File!");
      return;
    };

    //VCO1 Values
    iCnt = atoi(txtVCO1Pts->Text.c_str());
    WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt), (LPDWORD)&writen, NULL);
    for(int i=1; i<=iCnt; i++)
    {
      dTmp = atof(grdVco1->Cells[1][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
      dTmp = atof(grdVco1->Cells[2][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
    };

    //VCO2 Values
    iCnt = atoi(txtVCO2Pts->Text.c_str());
    WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt), (LPDWORD)&writen, NULL);
    for(int i=1; i<=iCnt; i++)
    {
      dTmp = atof(grdVco2->Cells[1][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
      dTmp = atof(grdVco2->Cells[2][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
    };

    //VCO3 Values
    iCnt = atoi(txtVCO3Pts->Text.c_str());
    WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt), (LPDWORD)&writen, NULL);
    for(int i=1; i<=iCnt; i++)
    {
      dTmp = atof(grdVco3->Cells[1][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
      dTmp = atof(grdVco3->Cells[2][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
    };

    //VCO4 Values
    iCnt = atoi(txtVCO4Pts->Text.c_str());
    WriteFile(pfItems, (LPCVOID)&iCnt, sizeof(iCnt), (LPDWORD)&writen, NULL);
    for(int i=1; i<=iCnt; i++)
    {
      dTmp = atof(grdVco4->Cells[1][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
      dTmp = atof(grdVco4->Cells[2][i].c_str());
      WriteFile(pfItems, (LPCVOID)&dTmp, sizeof(dTmp), (LPDWORD)&writen, NULL);
    };

    CloseHandle(pfItems);
  };
}
//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::btnLoadClick(TObject *Sender)
{

	char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
  dlgOpen->DefaultExt = "vco";
  //dlgOpen->FileName = "*.vco";
  dlgOpen->Filter = "VCO Values (*.vco)|*.vco";
  dlgOpen->InitialDir = drive;
  dlgOpen->InitialDir = dlgSave->InitialDir + dir;
  if(dlgOpen->Execute())
  {
    LoadValuesFromFile(dlgOpen->FileName);
  };
}
//---------------------------------------------------------------------------

void TdlgFreqVsCap::ConstructValues(sVcoVsCap &Vco, TStringGrid *grdVco, TMaskEdit *VCOPts)
{
  DestroyValues(Vco);
  Vco.iRef = atoi(VCOPts->Text.c_str());
  Vco.dFreq = new double[Vco.iRef];
  Vco.iCap = new double[Vco.iRef];
  for(int i=1; i<=Vco.iRef; i++)
  {
    Vco.dFreq[i-1] = atof(grdVco->Cells[1][i].c_str());
    Vco.iCap[i-1] = atof(grdVco->Cells[2][i].c_str());
  };
};
//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::FormDestroy(TObject *Sender)
{
  DestroyValues(sVco1);
  DestroyValues(sVco2);
  DestroyValues(sVco3);
  DestroyValues(sVco4);
}
//---------------------------------------------------------------------------
void TdlgFreqVsCap::DestroyValues(sVcoVsCap &Vco)
{
  if(Vco.iRef)
  {
    Vco.iRef = 0;
    delete[] Vco.dFreq;
    Vco.dFreq = NULL;
    delete[] Vco.iCap;
    Vco.iCap = NULL;
  };
};

//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnViewGrphVCO1Click(TObject *Sender)
{
  TdlgGraph *dlgGraph = new TdlgGraph(Application);
  //Check values
  if(!CheckValues(grdVco1))
  {
    ShowMessage("Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco1, grdVco1, txtVCO1Pts);
  dlgGraph->SetValues(sVco1.iRef, sVco1.dFreq, sVco1.iCap);
  dlgGraph->ShowModal();
  delete dlgGraph;
}

//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::btnViewGrphVCO2Click(TObject *Sender)
{
  TdlgGraph *dlgGraph = new TdlgGraph(Application);
  //Check values
  if(!CheckValues(grdVco2))
  {
    ShowMessage("Allowed Input in Table for VCO3: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco2, grdVco2, txtVCO2Pts);
  dlgGraph->SetValues(sVco2.iRef, sVco2.dFreq, sVco2.iCap);
  dlgGraph->ShowModal();
  delete dlgGraph;
}
//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnViewGrphVCO3Click(TObject *Sender)
{
  TdlgGraph *dlgGraph = new TdlgGraph(Application);
  //Check values
  if(!CheckValues(grdVco3))
  {
    ShowMessage("Allowed Input in Table for VCO2: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco3, grdVco3, txtVCO3Pts);
  dlgGraph->SetValues(sVco3.iRef, sVco3.dFreq, sVco3.iCap);
  dlgGraph->ShowModal();
  delete dlgGraph;
}
//---------------------------------------------------------------------------

void __fastcall TdlgFreqVsCap::btnViewGrphVCO4Click(TObject *Sender)
{
  TdlgGraph *dlgGraph = new TdlgGraph(Application);
  //Check values
  if(!CheckValues(grdVco4))
  {
    ShowMessage("Allowed Input in Table for VCO1: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco4, grdVco4, txtVCO4Pts);
  dlgGraph->SetValues(sVco4.iRef, sVco4.dFreq, sVco4.iCap);
  dlgGraph->ShowModal();
  delete dlgGraph;
}
//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::OKBtnClick(TObject *Sender)
{
  //Check values
  if(!CheckValues(grdVco1))
  {
    ShowMessage("Allowed Input in Table for VCO1: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco1, grdVco1, txtVCO1Pts);

  //Check values
  if(!CheckValues(grdVco2))
  {
    ShowMessage("Allowed Input in Table for VCO2: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco2, grdVco2, txtVCO2Pts);

  //Check values
  if(!CheckValues(grdVco3))
  {
    ShowMessage("Allowed Input in Table for VCO3: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco3, grdVco3, txtVCO3Pts);

  //Check values
  if(!CheckValues(grdVco4))
  {
    ShowMessage("Allowed Input in Table for VCO4: +-1234567890.\nCan not Draw Values!");
    return;
  };
  ConstructValues(sVco4, grdVco4, txtVCO4Pts);
  if(m_sLastUsedVCOFile != "") SavePathToReg(m_sLastUsedVCOFile);
}
//---------------------------------------------------------------------------
void TdlgFreqVsCap::Initialize(String Name)
{
  String FName;
  String Str;
  m_sName = Name;

  //Load VCO calibration values from last used file
  FName = ReadPathFromReg();

  if(!FileExists(FName))
  {
    if(m_sName == "TxVCOFile")
    {
      FName = ChangeFileExt(Application->ExeName,".tco");
    }
    else
    {
      FName = ChangeFileExt(Application->ExeName,".rco");
    };
  };

  if(FileExists(FName))
  {
    LoadValuesFromFile(FName);
    ConstructValues(sVco1, grdVco1, txtVCO1Pts);
    ConstructValues(sVco2, grdVco2, txtVCO2Pts);
    ConstructValues(sVco3, grdVco3, txtVCO3Pts);
    ConstructValues(sVco4, grdVco4, txtVCO4Pts);
  }
  else
  {
    Str = "Can't find VCO calibration values file for" + Name;
    Str = Str + "\nDefault values are used.";
    // Uncoment this line for displaying the message.
    //ShowMessage(Str);
  };
};
//---------------------------------------------------------------------------
void TdlgFreqVsCap::SavePathToReg(String Path)
{
  TRegistry* reg = new TRegistry;
  //reg->OpenKey("Software\\ctr_6002d\\Settings", true);
  reg->OpenKey(RegistryString, true);
  reg->WriteString(m_sName, Path);
  //reg->WriteString("LastDirectory", "C:\\");
  //reg->WriteInteger("Data", 1);
  delete reg;
};
//---------------------------------------------------------------------------
String TdlgFreqVsCap::ReadPathFromReg()
{
  String FileName;
  TRegistry* reg = new TRegistry;
  //reg->OpenKey("Software\\ctr_6002d\\Settings", true);
  reg->OpenKey(RegistryString, true);
  FileName = reg->ReadString(m_sName);
  delete reg;
  return FileName;
};
//---------------------------------------------------------------------------
void __fastcall TdlgFreqVsCap::FormShow(TObject *Sender)
{
  ShowVCOValues(sVco1, grdVco1, txtVCO1Pts);
  ShowVCOValues(sVco2, grdVco2, txtVCO2Pts);
  ShowVCOValues(sVco3, grdVco3, txtVCO3Pts);
  ShowVCOValues(sVco4, grdVco4, txtVCO4Pts);
}
//---------------------------------------------------------------------------

void TdlgFreqVsCap::ShowVCOValues(sVcoVsCap Vco, TStringGrid *grdVco, TMaskEdit *VCOPts)
{
	char buffer[50];
	int precision = 5;

  VCOPts->Text = Vco.iRef;
  SetTblRws(Vco.iRef + 1, grdVco);
  for(int i=1; i<=Vco.iRef; i++)
  {
    gcvt(Vco.dFreq[i-1], precision, buffer);
    grdVco->Cells[1][i] = buffer;
    gcvt(Vco.iCap[i-1], precision, buffer);
    grdVco->Cells[2][i] = buffer;
  };
};

//---------------------------------------------------------------------------
void TdlgFreqVsCap::LoadValuesFromFile(String FName)
{
  HANDLE pfItems;
  DWORD dwBytesRead;
  int iCnt;
  double dTmp;
  sVcoVsCap VcoVsCap;

    pfItems = CreateFile(
      FName.c_str(),//name of the file
      GENERIC_READ,//desired access
      FILE_SHARE_READ,//share mode
      NULL,//security attributes
      OPEN_EXISTING,//creation disposition
      FILE_ATTRIBUTE_NORMAL,// | FILE_FLAG_WRITE_THROUGH , //flags and attr
      NULL);//template file
    if(pfItems == INVALID_HANDLE_VALUE)
    {
      ShowMessage("Can not Open the File!");
      return;
    };

    //--===== Save path to registry. BEGIN =====--
    //SavePathToReg(FName);
    m_sLastUsedVCOFile = FName;
    //--=====  Save path to registry. END  =====--

    //VCO1 Values
    ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
    VcoVsCap.iRef = iCnt;
    VcoVsCap.dFreq = new double[iCnt];
    VcoVsCap.iCap = new double[iCnt];
    for(int i=1; i<=iCnt; i++)
    {
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.dFreq[i-1] = dTmp;
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.iCap[i-1] = dTmp;
    };
    ShowVCOValues(VcoVsCap, grdVco1, txtVCO1Pts);
    delete[] VcoVsCap.dFreq;
    delete[] VcoVsCap.iCap;

    //VCO2 Values
    ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
    VcoVsCap.iRef = iCnt;
    VcoVsCap.dFreq = new double[iCnt];
    VcoVsCap.iCap = new double[iCnt];
    for(int i=1; i<=iCnt; i++)
    {
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.dFreq[i-1] = dTmp;
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.iCap[i-1] = dTmp;
    };
    ShowVCOValues(VcoVsCap, grdVco2, txtVCO2Pts);
    delete[] VcoVsCap.dFreq;
    delete[] VcoVsCap.iCap;

    //VCO3 Values
    ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
    VcoVsCap.iRef = iCnt;
    VcoVsCap.dFreq = new double[iCnt];
    VcoVsCap.iCap = new double[iCnt];
    for(int i=1; i<=iCnt; i++)
    {
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.dFreq[i-1] = dTmp;
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.iCap[i-1] = dTmp;
    };
    ShowVCOValues(VcoVsCap, grdVco3, txtVCO3Pts);
    delete[] VcoVsCap.dFreq;
    delete[] VcoVsCap.iCap;

    //VCO4 Values
    ReadFile(pfItems, (LPVOID)&iCnt, sizeof(iCnt), &dwBytesRead, NULL);
    VcoVsCap.iRef = iCnt;
    VcoVsCap.dFreq = new double[iCnt];
    VcoVsCap.iCap = new double[iCnt];
    for(int i=1; i<=iCnt; i++)
    {
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.dFreq[i-1] = dTmp;
      ReadFile(pfItems, (LPVOID)&dTmp, sizeof(dTmp), &dwBytesRead, NULL);
      VcoVsCap.iCap[i-1] = dTmp;
    };
    ShowVCOValues(VcoVsCap, grdVco4, txtVCO4Pts);
    delete[] VcoVsCap.dFreq;
    delete[] VcoVsCap.iCap;

    CloseHandle(pfItems);
};

