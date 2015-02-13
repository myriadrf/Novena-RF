// -----------------------------------------------------------------------------
// FILE: 		IConnection.h
// DESCRIPTION:	Common interface for port connection
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "LMS_Commands.h"
using namespace std;

/// Supported connection types.
enum eConnectionType
{
	CONNECTION_UNDEFINED = -1,
	COM_PORT = 0,
	USB_PORT = 1,
	SPI_PORT = 2,
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

	virtual int SendData(const unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0) = 0;
	virtual int ReadData(unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0) = 0;

	virtual vector<string> GetDeviceNames() = 0;

	virtual eConnectionType GetType() { return m_connectionType; };
	virtual void ClearComm() = 0;
	virtual bool SetParam(const char *name, const char* value) {return false;};

	virtual int BeginDataReading(char *buffer, long length){ return -1; };
	virtual int WaitForReading(int contextHandle, unsigned int timeout_ms){ return 0;};
	virtual int FinishDataReading(char *buffer, long &length, int contextHandle){ return 0;}
	virtual void AbortReading(){};

	virtual int BeginDataSending(const char *buffer, long length){ return -1; };
	virtual int WaitForSending(int contextHandle, unsigned int timeout_ms){ return 0;};
	virtual int FinishDataSending(const char *buffer, long &length, int contextHandle){ return 0;}
	virtual void AbortSending(){};
	virtual eLMS_DEV ConnectedDeviceType() { return LMS_DEV_UNKNOWN; };
protected:
	eConnectionType m_connectionType;
};

#endif

