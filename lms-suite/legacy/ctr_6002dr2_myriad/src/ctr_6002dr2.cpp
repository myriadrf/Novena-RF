// -----------------------------------------------------------------------------
// FILE: 		    ctr_6002dr2.cpp
// DESCRIPTION:	Main control
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("frMain.cpp", frmMain);
USEFORM("About.cpp", AboutBox);
USERES("ctr_6002dr2.res");
USEFORM("frRxFe.cpp", frmRxFe); /* TFrame: File Type */
USEFORM("frRxVGA2.cpp", frmRxVGA2); /* TFrame: File Type */
USEFORM("frTop.cpp", frmTop); /* TFrame: File Type */
USEFORM("frTxLpf.cpp", frmTxLpf); /* TFrame: File Type */
USEFORM("frTxPLL.cpp", frmTxPLL); /* TFrame: File Type */
USEFORM("frTxRf.cpp", frmTxRf); /* TFrame: File Type */
USEUNIT("common.cpp");
USEFORM("frFreqVsCap.cpp", dlgFreqVsCap);
USEFORM("dlgVcoGrph.cpp", dlgGraph);
USEFORM("dgRefClk.cpp", dlgRefClk);
USELIB("IntercomP.lib");
USEFORM("frCustomer.cpp", frmCustomer); /* TFrame: File Type */
USEUNIT("clUARFCN.cpp");
USEFORM("frADDC.cpp", frmADDC); /* TFrame: File Type */
USEFORM("dlgVcoCapLog.cpp", dVcoCapLog);
USEFORM("dlgRegTest.cpp", dRegTest);
USEFORM("frBoard.cpp", frmBoard); /* TFrame: File Type */
USEFORM("dlgSerPort.cpp", dSerPort);
USEFORM("dgRFIFParam.cpp", dlgRFIFParam);
USELIB("C:\Cypress\Cypress Suite USB 3.4.7\CyAPI\lib\BC6\CyAPI.lib");
USEUNIT("register_map.cpp");
USEFORM("frBoard2.cpp", frmBoard2); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
  Application->CreateForm(__classid(TfrmMain), &frmMain);
                 Application->Run();

	return 0;
}
//---------------------------------------------------------------------
