#ifndef CONNECTION_COM_PORT_H
#define CONNECTION_COM_PORT_H

#ifndef LINUX
	#include "windows.h"
#endif

#include "IConnection.h"
#include <string>
#include <vector>
using namespace std;

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

	int SendData(const unsigned char *buffer, unsigned long length);
	int ReadData(unsigned char *buffer, unsigned long length);

	vector<string> GetDeviceNames();
	void FindDevices();
private:
	void FindAllComPorts();
	int Open(const char *comName, int baudrate);

	bool TestConnectivity();

	string comPortName;
	int comBaudrate;
	bool connected;

	int currentDeviceIndex;
	vector<string> comPortList;
	vector<string> m_deviceNames;

#ifndef LINUX
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
