// -----------------------------------------------------------------------------
// FILE: 		    common.cpp
// DESCRIPTION:	Common structures and definitions file.
// DATE:        2007.10.01
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

HWND G_hwWindow;  //Global pointer to the main window.

//---------------------------------------------------------------------------
// Quadratic interpolation for CAP selection
//---------------------------------------------------------------------------
int QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco)
{
  double dGV = 0;
  double dNum;
  double dDenom;

  for(int i=0; i<iRefVCnt; i++) //Loop through each reference point
  {
    dNum = 1;
    dDenom = 1;
    for(int j=0; j<iRefVCnt; j++)
    {
      if(i != j)
      {
        dNum    *= dRealFvco - dFVco[j];
        dDenom  *= dFVco[i]  - dFVco[j];
      };
    };
    dGV += (double)dCVco[i] * dNum / dDenom;
  };

  return (int)(dGV + 0.5);
};

