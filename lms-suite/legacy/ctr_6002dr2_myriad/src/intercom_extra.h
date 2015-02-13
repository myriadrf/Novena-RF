#ifndef _SHELL_H_
#define _SHELL_H_

#ifndef EXPORT
#define EXPORT
#endif

#define WM_WriteData  (WM_USER + 1001)  //LMS6002
#define WM_ReadData   (WM_USER + 1002)  //LMS6002
#define WM_Reset      (WM_USER + 1003)  //LMS6002

#define WM_WR_Xil     (WM_USER + 1004)  //Xilinx
#define WM_RD_Xil     (WM_USER + 1005)  //Xilinx

#define WM_WR_AD9552  (WM_USER + 1006)  //AD9552
#define WM_RD_AD9552  (WM_USER + 1007)  //AD9552

#define WM_WR_AD7691  (WM_USER + 1008)  //AD7691
#define WM_RD_AD7691  (WM_USER + 1009)  //AD7691


//First parameter: Server Window Handle
EXPORT void  SetServer(int);

//First parameter: Value from server
EXPORT void  SetValueFromServer(int);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
//EXPORT void  WriteDataToServer(int SPI, int Reg, int Data);
EXPORT void  WriteDataToServer(int, int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
EXPORT int ReadDataFromServer(int, int);

//Reset the chip
EXPORT void ResetChip(void);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
EXPORT void  WriteDataToXil(int, int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
EXPORT int ReadDataFromXil(int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
EXPORT void  WriteDataToAD9552(int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
EXPORT int ReadDataFromAD9552(int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Second parameter: Data to write
EXPORT void  WriteDataToAD7691(int, int, int);

//First parameter: SPI module address
//Second parameter: Register address
//Return value: Data from SPI register
EXPORT int ReadDataFromAD7691(int, int);


#endif
 