#ifndef __intercomUnit_H
#define __intercomUnit_H

#define WM_WriteData  (WM_USER + 1001)  //LMS6002
#define WM_ReadData   (WM_USER + 1002)  //LMS6002
#define WM_Reset      (WM_USER + 1003)  //LMS6002

#define WM_WR_Xil     (WM_USER + 1004)  //Xilinx
#define WM_RD_Xil     (WM_USER + 1005)  //Xilinx

#define WM_WR_AD9552  (WM_USER + 1006)  //AD9552
#define WM_RD_AD9552  (WM_USER + 1007)  //AD9552

#define WM_WR_AD7691  (WM_USER + 1008)  //AD7691
#define WM_RD_AD7691  (WM_USER + 1009)  //AD7691

// DLL Interface
extern "C"
{
//First parameter: Server Window Handle
__declspec( dllexport ) void  SetServer(DWORD);

//First parameter: Value from server
__declspec( dllexport ) void  SetValueFromServer(DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
__declspec( dllexport ) void  WriteDataToServer(DWORD, DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
__declspec( dllexport ) DWORD ReadDataFromServer(DWORD, DWORD);

//Reset the chip
__declspec( dllexport ) void ResetChip(void);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
__declspec( dllexport ) void  WriteDataToXil(DWORD, DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
__declspec( dllexport ) DWORD ReadDataFromXil(DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
__declspec( dllexport ) void  WriteDataToAD9552(DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
__declspec( dllexport ) DWORD ReadDataFromAD9552(DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
__declspec( dllexport ) void  WriteDataToAD7691(DWORD, DWORD, DWORD);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
__declspec( dllexport ) DWORD ReadDataFromAD7691(DWORD, DWORD);
}

#endif
 