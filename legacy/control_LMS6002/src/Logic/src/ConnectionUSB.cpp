// -----------------------------------------------------------------------------
// FILE: 		ConnectionUSB.cpp
// DESCRIPTION:	implements data transfer through USB port
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "ConnectionUSB.h"
#include <iostream>

#ifndef LINUX


	#include "windows.h"
	#include "CyAPI.h"
#else
	#include <libusb-1.0/libusb.h>
	#include "TimeCounter.h"
#define USB_TIMEOUT 1000

#endif

#define HW_DIGIRED "DigiRed"
#define HW_DIGIGREEN "DigiGreen"

#define HW_LDIGIRED L"DigiRed"
#define HW_LDIGIGREEN L"DigiGreen"

#define CTR_W_REQCODE 0xC1
#define CTR_W_VALUE 0x0000
#define CTR_W_INDEX 0x0000

#define CTR_R_REQCODE 0xC0
#define CTR_R_VALUE 0x0000
#define CTR_R_INDEX 0x0000

#define CMD_GET_INFO 0x50

using namespace std;
/**
	@brief Initializes port type and object necessary to communicate to usb device.
*/
ConnectionUSB::ConnectionUSB()
{
    m_maxPacketSize = 256;
    m_hardwareName = "";
    isConnected = false;
    m_connectionType = USB_PORT;
#ifndef LINUX
    USBDevicePrimary = new CCyUSBDevice(NULL);
    OutCtrEndPt = NULL;
    InCtrEndPt = NULL;
#else
    int r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0)
    {
        cout<<"Init Error "<<r<<endl; //there was an error
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
#endif
    currentPortIndex = -1;
}

/**
	@brief Closes connection to chip and deallocates used memory.
*/
ConnectionUSB::~ConnectionUSB()
{
    Close();
#ifndef LINUX
    delete USBDevicePrimary;
#else
    libusb_exit(ctx);
#endif
}

/**
	@brief Automatically open first available chip connected to usb port.
	@return 1-Success, 0-chip not found.
*/
bool ConnectionUSB::Open()
{
    currentPortIndex = -1;
    if(m_deviceNames.size() == 0)
        FindAllUSBDevices();

#ifndef LINUX
    for(int i=0; i<USBDevicePrimary->DeviceCount(); i++)
        if( Open(i) == 1)
        {
            currentPortIndex = i;
            return true;
        }
#else
    if(Open(0))
        return true;
#endif

    return false;
}

/**
	@brief Tries to open connected USB device and find communication endpoints.
	@return Returns 1-Success, 0-EndPoints not found or device didn't connect.
*/
bool ConnectionUSB::Open(unsigned index)
{
#ifndef LINUX
	unsigned short vID;
	unsigned short pID;
	wstring m_hardwareDesc = L"";
	int devicesFound = 0;
	if( index < USBDevicePrimary->DeviceCount())
	{
		if(USBDevicePrimary->Open(index))
		{

			vID = USBDevicePrimary->VendorID;
			pID = USBDevicePrimary->ProductID;

			//check if vendor and product ID matches
			if( vID != 1204 )
            {
                return 0;
            }
            else
            {
                if( pID != 241 && pID != 34323 )
                {
                    return 0;
                }
            }


            m_hardwareDesc = USBDevicePrimary->Product;

            int pos;
            pos = m_hardwareDesc.find(HW_LDIGIRED, 0);
            if( pos != wstring::npos )
            {
                m_hardwareName = "DigiRed";
            }
            else
            {
                m_hardwareName = "DigiGreen";
            }

            if(m_hardwareName != "DigiRed")
            {
                // DigiGreen, control through bulk endpoints
                int endPointsFound = 0;
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                {
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x01)
                    {
                        OutCtrEndPt = USBDevicePrimary->EndPoints[i];
                        endPointsFound++;
                        break;
                    }
                }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                {
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x81)
                    {
                        InCtrEndPt = USBDevicePrimary->EndPoints[i];
                        endPointsFound++;
                        break;
                    }
                }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x86)
                    {
                        InEndPt = USBDevicePrimary->EndPoints[i];
                        m_maxPacketSize = InEndPt->MaxPktSize;
                        //m_maxPacketSize = 1024;
                        long len = InEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        InEndPt->SetXferSize(len);
                    }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x02)
                    {
                        OutEndPt = USBDevicePrimary->EndPoints[i];
                    }

                if(endPointsFound == 2)
                {
                    currentPortIndex = index;
                    isConnected = true;
                    return true;
                }
                else
                    return false;
            }
            else //digired, controls through control end point
            {
                InCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);
                OutCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);

                InCtrlEndPt3->ReqCode = CTR_R_REQCODE;
                InCtrlEndPt3->Value = CTR_R_VALUE;
                InCtrlEndPt3->Index = CTR_R_INDEX;

                OutCtrlEndPt3->ReqCode = CTR_W_REQCODE;
                OutCtrlEndPt3->Value = CTR_W_VALUE;
                OutCtrlEndPt3->Index = CTR_W_INDEX;

                bool devIsTx;
                devIsTx = false;

                char unsigned tbuf[64];
                long len = 64;
                memset(tbuf, 0, len);
                tbuf[0] = CMD_GET_INFO;
                SendData(tbuf, len);
                ReadData(tbuf, len);

                if(tbuf[0] == 1)
                    devIsTx = true;

                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x01)
                    {
                        //cout << "out end point found " << endl;
                        OutEndPt = USBDevicePrimary->EndPoints[i];
                        //OutEndPt->MaxPktSize = OutEndPt->MaxPktSize;
                        long len = OutEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        OutEndPt->SetXferSize(len);
                        break;
                    }
                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x81)
                    {
                        //cout << "in end point found " << endl;
                        InEndPt = USBDevicePrimary->EndPoints[i];
                        m_maxPacketSize = InEndPt->MaxPktSize;
                        long len = InEndPt->MaxPktSize * 64;
                        // Each xfer request will get PPX isoc packets
                        InEndPt->SetXferSize(len);
                        break;
                    }
                isConnected = true;
                return true;
            }
            return false;
		} //successfully opened device
	} //if has devices
    return 0;
#else
    int usbDeviceCount = libusb_get_device_list(ctx, &devs);;
    if(usbDeviceCount > 0)
    {
        //open by pid and vid
		dev_handle = libusb_open_device_with_vid_pid(ctx, 1204, 34323);
//		dev_handle = libusb_open_device_with_vid_pid(ctx, 1204, 241);
		if(dev_handle == 0)
            return false;
        if(libusb_kernel_driver_active(dev_handle, 0) == 1)   //find out if kernel driver is attached
        {
            cout<<"Kernel Driver Active"<<endl;
            if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
                cout<<"Kernel Driver Detached!"<<endl;
        }
        int r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device
        if(r < 0)
        {
            cout<<"Cannot Claim Interface"<<endl;
            return 1;
        }
        cout<<"Claimed Interface"<<endl;
        libusb_free_device_list(devs, 1);
        isConnected = true;
        return true;
    }
    else
    {
        libusb_free_device_list(devs, 1);
        return false;
    }
#endif

}

/**
	@brief Closes communication to device.
*/
void ConnectionUSB::Close()
{
    #ifndef LINUX
	USBDevicePrimary->Close();
	InEndPt = NULL;
	OutEndPt = NULL;
    #else
    int r = libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    #endif
    isConnected = false;
}

/**
	@brief Returns connection status
	@return 1-connection open, 0-connection closed.
*/
bool ConnectionUSB::IsOpen()
{
    #ifndef LINUX
    return USBDevicePrimary->IsOpen() && isConnected;
    #else
    return isConnected;
    #endif
}

/**
	@brief Sends given data buffer to chip through USB port.
	@param buffer data buffer, must not be longer than 64 bytes.
	@param length given buffer size.
	@return number of bytes sent.
*/
int ConnectionUSB::SendData(const unsigned char *buffer, unsigned long length)
{
    unsigned char temp[64];
    if(length > 64)
        length = 64;
    memcpy(temp, buffer, length);
    if(IsOpen())
    {
        long len = length;
        if(m_hardwareName == HW_DIGIRED)
        {
            #ifndef LINUX
            if(OutCtrlEndPt3)
                return OutCtrlEndPt3->Write(temp, len);
            #endif
        }
        else
        {
            #ifndef LINUX
            if(OutCtrEndPt)
                return OutCtrEndPt->XferData(temp, len);
            else
                return 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x01, temp, len, &actual, USB_TIMEOUT);
                return actual;
            #endif
        }
    }
    return 0;
}

/**
	@brief Reads data coming from the chip through USB port.
	@param buffer pointer to array where received data will be copied, array must be
	big enough to fit received data.
	@param bytesRead number of bytes to read from chip.
	@return number of bytes received.
*/
int ConnectionUSB::ReadData(unsigned char *buffer, unsigned long bytesRead)
{
    if(IsOpen())
    {
        long len = bytesRead;
        if(m_hardwareName == HW_DIGIRED)
        {
            #ifndef LINUX
            if(InCtrlEndPt3)
                return InCtrlEndPt3->Read((unsigned char*)buffer, len);
            #endif
        }
        else
        {
            #ifndef LINUX
            if(InCtrEndPt)
                return InCtrEndPt->XferData((unsigned char*)buffer, len);
            else
                return 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x81, (unsigned char*)buffer, len, &actual, USB_TIMEOUT);
                return actual;
            #endif
        }
    }
    return 0;
}

#ifdef LINUX
/**
	@brief Function for handling libusb callbacks
*/
void callback_libusbtransfer(libusb_transfer *trans)
{
	USBTransferContext *context = reinterpret_cast<USBTransferContext*>(trans->user_data);
	switch(trans->status)
	{
    case LIBUSB_TRANSFER_CANCELLED:
        //printf("Transfer canceled\n" );
        break;
    case LIBUSB_TRANSFER_COMPLETED:
        if(trans->actual_length == context->bytesExpected)
		{
			context->bytesXfered = trans->actual_length;
			context->done = true;
		}
        break;
    case LIBUSB_TRANSFER_ERROR:
        //printf("TRANSFER ERRRO\n");
        break;
    case LIBUSB_TRANSFER_TIMED_OUT:
        //printf("transfer timed out\n");

        break;
    case LIBUSB_TRANSFER_OVERFLOW:
        //printf("transfer overflow\n");

        break;
	}
}
#endif

/**
	@brief Checks all connected USB devices and found chips are added to list.
*/
void ConnectionUSB::FindAllUSBDevices()
{
    #ifndef LINUX
    USBDevicePrimary->Close();
    currentPortIndex = -1;
    m_deviceNames.clear();
    string name;
    if (USBDevicePrimary->DeviceCount())
    {
        for (int i = 0; i < USBDevicePrimary->DeviceCount(); i++)
        {
            Open(i);
            name = DeviceName();
            if( m_hardwareName == "DigiRed")
            {
                unsigned char tbuf[64];
                long len = 64;
                memset(tbuf, 0, len);
                tbuf[0] = CMD_GET_INFO;
                SendData(tbuf, len);
                ReadData(tbuf, len);

                if(tbuf[0] == 1)
                    name.append( " (Transmitter)" );
                else
                    name.append( " (Receiver)" );
            }
            m_deviceNames.push_back(name);
        }
        currentPortIndex = -1;
    }
    #endif
}
