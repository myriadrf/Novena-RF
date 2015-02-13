/**
@file   ConnectionCOM.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for data communications through COM port
*/

#ifndef CONNECTION_COM_PORT_H
#define CONNECTION_COM_PORT_H

#ifndef __unix__
	#include "windows.h"
#endif

#include "IConnection.h"
#include <string>
#include <vector>

class ConnectionCOM : public IConnection
{
public:
    static const int COM_BUFFER_LENGTH = 1024; //max buffer size for data

	ConnectionCOM();
	~ConnectionCOM();

	bool Open();
	bool Open(int i);
	void Close();
	bool IsOpen();

	int SendData(const unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0);
	int ReadData(unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0);

	std::vector<std::string> GetDeviceNames();
	void FindDevices();
	void ClearComm();
private:
	void FindAllComPorts();
	int Open(const char *comName, int baudrate);

	bool TestConnectivity();

	std::string comPortName;
	int comBaudrate;
	bool connected;

	int currentDeviceIndex;
	std::vector<std::string> comPortList;
	std::vector<std::string> m_deviceNames;

#ifndef __unix__
	HANDLE hComm;
	COMMTIMEOUTS m_ctmoNew;
	COMMTIMEOUTS m_ctmoOld;
	OVERLAPPED m_osROverlap;
	OVERLAPPED m_osWOverlap;
	DCB m_dcbCommPort;
#else
    int hComm; //com port file descriptor
#endif

};
#endif
