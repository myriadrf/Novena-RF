// -----------------------------------------------------------------------------
// FILE: 		    dlgSerPort.h
// DESCRIPTION:	Header for dlgSerPort.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef dlgSerPortH
#define dlgSerPortH
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

#include "CyAPI.h"
#include <vector>
//----------------------------------------------------------------------------

const unsigned int cuiBuffL = 1024;
struct sPrData;

class TdSerPort : public TForm
{
__published:
  TButton *btnOK;
  TButton *btnCancel;
  TComboBox *cmbComPorts;
  TRadioGroup *rgrBaud;
        TComboBox *cmbUSBDevices;
        TRadioGroup *rgrPortSelection;
        TComboBox *cmbInEndPt;
        TComboBox *cmbOutEndPt;
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
        void __fastcall cmbUSBDevicesChange(TObject *Sender);
        void __fastcall cmbInEndPtChange(TObject *Sender);
        void __fastcall cmbOutEndPtChange(TObject *Sender);
        void __fastcall rgrPortSelectionClick(TObject *Sender);

private:

  //======USB===============;
        int iPortSelected;  // 0-COM  1-USB

        CCyUSBDevice *USBDevice;
        CCyUSBEndPoint *OutEndPt;
	CCyUSBEndPoint *InEndPt;
        CCyUSBEndPoint *OutCtrEndPt;
	CCyUSBEndPoint *InCtrEndPt;

        int iSelectedUSBDeviceIndex;
        int iSelectedInEndPt;
        int iSelectedOutEndPt;
        std::vector<int> inEndPointIndexes;
        std::vector<int> outEndPointIndexes;

        void findUSBDevices();
        bool OpenUSBDevice(int iDeviceIndex);
        void CloseUSBDevice();

  //========================


  HANDLE hComm;
  String m_sComName;
  int m_iBaud;

  COMMTIMEOUTS m_ctmoNew;
  COMMTIMEOUTS m_ctmoOld;
  OVERLAPPED m_osROverlap;
  OVERLAPPED m_osWOverlap;
  DCB m_dcbCommPort;

  int Code2Baud(int Code);
  void LoadFromIni();
  void SaveToIni();
  bool __fastcall WritePort(BYTE *Buffer, int iSize);
  bool __fastcall ReadPort(LPVOID Buffer, int *iSize, int iToRead);

  bool WriteUSBPort(BYTE *Buffer, int iSize, char I2Ccmd);
  bool ReadUSBPort(LPVOID Buffer);



public:
	virtual __fastcall TdSerPort(TComponent* AOwner);

  void __fastcall CloseComPort();
  bool __fastcall OpenComPort(String sPortName, int iBaudRate);

  CCyUSBEndPoint *getOutBulkPt();
  CCyUSBEndPoint *getInBulkPt();
  CCyUSBEndPoint *getInCtrBulkPt();
  CCyUSBEndPoint *getOutCtrBulkPt();

  bool PortOpened();

  void SPI_Rst();
	void SPI_RstAct();
	void SPI_RstInact();

  void SetBrdPA(char Code);
  void SetBrdLNA(char Code);

	void SPI_Rd(sPrData *pPD);
  char SPI_Rd_OneByte(char Command);
  void SPI_Rd_Xil(sPrData *pPD);
  void SPI_Rd_AD7691(sPrData *pPD);

	void SPI_Wr(sPrData *pPD);
  void SPI_Wr_ADF(sPrData *pPD);
  void SPI_Wr_Xil(sPrData *pPD);
  void SPI_Wr_AD9552(sPrData *pPD);

};
//----------------------------------------------------------------------------
extern PACKAGE TdSerPort *dSerPort;
//----------------------------------------------------------------------------
#endif    
