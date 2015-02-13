// -----------------------------------------------------------------------------
// FILE: 		    frCustomer.cpp
// DESCRIPTION:	System control user interface
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "frCustomer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
__fastcall TfrmCustomer::TfrmCustomer(TComponent* Owner)
  : TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void TfrmCustomer::Initialize(char MAddr)
{
  SetGuiDefaults();
};

//---------------------------------------------------------------------------
void TfrmCustomer::SetGuiDefaults()
{
	int itmp;
	m_bAllowSend = false;

  //LNASEL_RXFE[1:0]
  cmbLNASEL_Cust->Clear();
  cmbLNASEL_Cust->Items->Add("Disabled");
  cmbLNASEL_Cust->Items->Add("LNA 1");
  cmbLNASEL_Cust->Items->Add("LNA 2");
  cmbLNASEL_Cust->Items->Add("LNA 3");
  cmbLNASEL_Cust->ItemIndex = 1;

  cmbBypass->ItemIndex = 0;
  cmbTxBypass->ItemIndex = 0;
  cmbLoopback->ItemIndex = 0;

  SetGuiDecode();

  m_bAllowSend = true;
};

//---------------------------------------------------------------------------
void TfrmCustomer::SetGuiDecode()
{
};

//---------------------------------------------------------------------------






