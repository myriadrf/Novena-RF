#ifndef USB_PORT_CONNECTION_H
#define USB_PORT_CONNECTION_H

#include "IConnection.h"
#include <string>
#include <vector>

using namespace std;

#define USB_BUFFER_LENGTH = 64;

#ifndef LINUX
#include "windows.h"
#include "CyAPI.h"
#else
#include <libusb-1.0/libusb.h>
#endif

#define USB_MAX_CONTEXTS 64 //maximum number of contexts for asynchronous transfers

class USBTransferContext
{
public:
	USBTransferContext() : used(false)
	{
		#ifndef LINUX
		inOvLap = new OVERLAPPED;
		inOvLap->hEvent = CreateEvent(NULL, false, false, NULL);
		context = NULL;
		#else
		transfer = libusb_alloc_transfer(64);
		bytesXfered = 0;
		bytesExpected = 0;
		done = 0;
		#endif
	}
	~USBTransferContext()
	{
		#ifndef LINUX
		CloseHandle(inOvLap->hEvent);
		delete inOvLap;
		#else
		libusb_free_transfer(transfer);
		#endif
	}
	bool used;
	#ifndef LINUX
	PUCHAR context;
	OVERLAPPED *inOvLap;
	#else
	libusb_transfer* transfer;
	long bytesXfered;
	long bytesExpected;
	bool done;
	#endif
};

class ConnectionUSB : public IConnection
{
public:
	ConnectionUSB();
	~ConnectionUSB();

    void FindDevices();
	bool Open();
	bool Open(unsigned index);
	void Close();
	bool IsOpen();

	int SendData(const unsigned char *buffer, unsigned long length);
	int ReadData(unsigned char *buffer, unsigned long length);

	vector<string> GetDeviceNames();
private:
    vector<string> m_deviceNames;
    int m_maxPacketSize;
    string m_hardwareName;
    int m_hardwareVer;

	USBTransferContext contexts[USB_MAX_CONTEXTS];
	USBTransferContext contextsToSend[USB_MAX_CONTEXTS];
	void Initialize();

	void FindAllUSBDevices();

	bool isConnected;
	int currentPortIndex;

	#ifndef LINUX
	CCyUSBDevice *USBDevicePrimary;
	//usb device for DigiRed transmitting
	CCyUSBDevice *USBDeviceSecondary;
	//control endpoints for DigiRed
	CCyControlEndPoint *InCtrlEndPt3;
	CCyControlEndPoint *OutCtrlEndPt3;

    //control endpoints for DigiGreen
	CCyUSBEndPoint *OutCtrEndPt;
	CCyUSBEndPoint *InCtrEndPt;

    //end points for samples reading and writing
	CCyUSBEndPoint *InEndPt;
	CCyUSBEndPoint *OutEndPt;

	#else
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = NULL; //a libusb session
	#endif
};

#endif
