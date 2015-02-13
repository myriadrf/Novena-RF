// -----------------------------------------------------------------------------
// FILE: 		    frCustomer.h
// DESCRIPTION:	Header for frCustomer.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef frCustomerH
#define frCustomerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmCustomer : public TFrame
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox4;
  TLabel *Label6;
  TComboBox *cmbLNASEL_Cust;
  TGroupBox *GroupBox1;
  TButton *btnClbrTx;
  TButton *btnClbrRx;
  TGroupBox *GroupBox2;
  TComboBox *cmbBypass;
  TLabel *Label1;
  TComboBox *cmbLoopback;
  TLabel *Label2;
  TLabel *Label3;
  TComboBox *cmbTxBypass;
  TGroupBox *GroupBox3;
  TComboBox *cmbULRXBands;
  TLabel *Label4;
  TLabel *Label5;
  TComboBox *cmbULRXChan;
  TLabel *Label7;
  TLabel *Label8;
  TEdit *txtULRXFreq;
  TButton *btnCalRxTIA;
  TSpeedButton *btnULRXFChan_B;
  TSpeedButton *btnULRXFChan_M;
  TSpeedButton *btnULRXFChan_T;
  TGroupBox *GroupBox5;
  TLabel *Label9;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TSpeedButton *btnDLTXFChan_B;
  TSpeedButton *btnDLTXFChan_M;
  TSpeedButton *btnDLTXFChan_T;
  TComboBox *cmbDLTXBands;
  TComboBox *cmbDLTXChan;
  TEdit *txtDLTXFreq;
  TButton *Button1;
private:	// User declarations
  void SetGuiDefaults();
  void SetGuiDecode();

  bool m_bAllowSend;


public:		// User declarations
  __fastcall TfrmCustomer(TComponent* Owner);

  void Initialize(char MAddr);
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
#endif
