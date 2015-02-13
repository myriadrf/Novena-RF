//---------------------------------------------------------------------------


#ifndef frSi5356H
#define frSi5356H
//---------------------------------------------------------------------------
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Messages.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <dir.h>

#include <stdio.h>
#include "cyapi.h"
#include "RxGIF.hpp"
#include "register_map.h"
//---------------------------------------------------------------------------
class TfrmBoard2 : public TFrame
{
__published:	// IDE-managed Components
        TGroupBox *LMS6002D;
        TGroupBox *Si5356A;
        TButton *btnConfigureSi5356A;
        TButton *btnLmsRd;
        TButton *btnLoadFile;
        TButton *btnRdMem;
        TOpenDialog *dlgOpen;
        void __fastcall btnConfigureSi5356AClick(TObject *Sender);
        void __fastcall btnLmsRdClick(TObject *Sender);
        void __fastcall btnLoadFileClick(TObject *Sender);
        void __fastcall btnRdMemClick(TObject *Sender);
private:	// User declarations
        CCyUSBEndPoint *InCtrEndPt;
        CCyUSBEndPoint *OutCtrEndPt;
        CCyUSBEndPoint *InEndPt;
        CCyUSBEndPoint *OutEndPt;
        CCyUSBDevice *USBDevice;
        bool m_bAllowSend;
        bool initialized;
        void LoadRegValuesFromFile(String FName);

public:		// User declarations
        __fastcall TfrmBoard2(TComponent* Owner);
        void Initialize();
        void Initialize(CCyUSBEndPoint *pInEndPt, CCyUSBEndPoint *pOutEndPt,
                                CCyUSBEndPoint *pInCtrEndPt, CCyUSBEndPoint *pOutCtrEndPt);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBoard2 *frmBoard2;
//---------------------------------------------------------------------------
#endif
