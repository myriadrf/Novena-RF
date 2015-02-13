#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

/// Supported connection types.
enum eConnectionType
{
	CONNECTION_UNDEFINED = -1,
	COM_PORT = 0,
	USB_PORT = 1,
	//insert new types here
	CONNECTION_TYPES_COUNT //used only for memory allocation
};

class IConnection
{
public:
	IConnection() : m_connectionType(CONNECTION_UNDEFINED){};
	virtual ~IConnection(){};
	virtual void FindDevices() = 0;
	virtual bool Open() = 0;
	virtual bool Open(int i) = 0;
	virtual void Close() = 0;
	virtual bool IsOpen() = 0;

	virtual int SendData(const unsigned char *buffer, unsigned long length) = 0;
	virtual int ReadData(unsigned char *buffer, unsigned long length) = 0;

	virtual vector<string> GetDeviceNames() = 0;

	virtual eConnectionType GetType() { return m_connectionType; };
protected:
	eConnectionType m_connectionType;
};

#endif

