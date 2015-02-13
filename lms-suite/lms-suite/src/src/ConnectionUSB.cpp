/**
@file   ConnectionUSB.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Data writing and reading through USB port
*/

#include "ConnectionUSB.h"
#include <iostream>

#ifndef __unix__
	#include "windows.h"
	#include "CyAPI.h"
#else
	#include <libusb-1.0/libusb.h>
#define USB_TIMEOUT 1000
#endif

#define HW_LDIGIRED L"DigiRed"
#define HW_LDIGIGREEN L"DigiGreen"
#define HW_LSTREAMER L"Stream"

#define HW_DIGIRED "DigiRed"
#define HW_DIGIGREEN "DigiGreen"
#define HW_STREAMER "Stream"

#define CTR_W_REQCODE 0xC1
#define CTR_W_VALUE 0x0000
#define CTR_W_INDEX 0x0000

#define CTR_R_REQCODE 0xC0
#define CTR_R_VALUE 0x0000
#define CTR_R_INDEX 0x0000

#include "LMS_Commands.h"
#include "CommonUtilities.h"
#include "MessageLog.h"
#include <sstream>
#include <stdio.h>

using namespace std;

/**	@brief Initializes port type and object necessary to communicate to usb device.
*/
ConnectionUSB::ConnectionUSB()
{
    m_maxPacketSize = 256;
    m_hardwareName = "";
    isConnected = false;
    m_connectionType = USB_PORT;
#ifndef __unix__
    USBDevicePrimary = new CCyUSBDevice(NULL);
    OutCtrEndPt = NULL;
    InCtrEndPt = NULL;
#else
    dev_handle = 0;
    devs = 0;
    int r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0)
    {
        cout<<"Init Error "<<r<<endl; //there was an error
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
#endif
    currentPortIndex = -1;
}

/**	@brief Closes connection to chip and deallocates used memory.
*/
ConnectionUSB::~ConnectionUSB()
{
    Close();
#ifndef __unix__
    delete USBDevicePrimary;
#else
    libusb_exit(ctx);
#endif
}

/**	@brief Automatically open first available chip connected to usb port.
	@return 1-Success, 0-chip not found.
*/
bool ConnectionUSB::Open()
{
    currentPortIndex = -1;
    if(m_deviceNames.size() == 0)
        FindDevices();

#ifndef __unix__
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

/**	@brief Tries to open connected USB device and find communication endpoints.
	@return Returns 1-Success, 0-EndPoints not found or device didn't connect.
*/
bool ConnectionUSB::Open(int index)
{
#ifndef __unix__
//	unsigned short vID;
//	unsigned short pID;
	wstring m_hardwareDesc = L"";
	if( index < USBDevicePrimary->DeviceCount())
	{
		if(USBDevicePrimary->Open(index))
		{
//			vID = USBDevicePrimary->VendorID;
//			pID = USBDevicePrimary->ProductID;
			//check if vendor and product ID matches
//			if( vID != 1204 )
//            {
//                return 0;
//            }
//            else
//            {
//                if( pID != 241 && pID != 34323 )
//                {
//                    return 0;
//                }
//            }
            m_hardwareDesc = USBDevicePrimary->Product;
            //m_hardwareDesc = L"Stream_01";
            unsigned int pos;
            pos = m_hardwareDesc.find(HW_LDIGIRED, 0);
            if( pos != wstring::npos )
                m_hardwareName = HW_DIGIRED;
            else if (m_hardwareDesc.find(HW_LSTREAMER, 0) != wstring::npos)
                m_hardwareName = HW_STREAMER;
            else
                m_hardwareName = HW_DIGIGREEN;
            if(m_hardwareName == HW_DIGIRED || m_hardwareName == HW_STREAMER) //digired, controls through control end point
            {
                InCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);
                OutCtrlEndPt3 = new CCyControlEndPoint(*USBDevicePrimary->ControlEndPt);

                InCtrlEndPt3->ReqCode = CTR_R_REQCODE;
                InCtrlEndPt3->Value = CTR_R_VALUE;
                InCtrlEndPt3->Index = CTR_R_INDEX;

                OutCtrlEndPt3->ReqCode = CTR_W_REQCODE;
                OutCtrlEndPt3->Value = CTR_W_VALUE;
                OutCtrlEndPt3->Index = CTR_W_INDEX;

                for (int i=0; i<USBDevicePrimary->EndPointCount(); i++)
                    if(USBDevicePrimary->EndPoints[i]->Address == 0x01)
                    {
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
            else
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
            return false;
		} //successfully opened device
	} //if has devices
    return 0;
#else
    if(index >= 0 && index < m_dev_pid_vid.size())
    {
		dev_handle = libusb_open_device_with_vid_pid(ctx, m_dev_pid_vid[index].second, m_dev_pid_vid[index].first);

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
            //return 1;
        }
        cout<<"Claimed Interface"<<endl;
        isConnected = true;
        return true;
    }
    else
    {
        return false;
    }
#endif
}

/**	@brief Closes communication to device.
*/
void ConnectionUSB::Close()
{
    #ifndef __unix__
	USBDevicePrimary->Close();
	InEndPt = NULL;
	OutEndPt = NULL;
    #else
    if(dev_handle != 0)
    {
        libusb_release_interface(dev_handle, 0);
        libusb_close(dev_handle);
        dev_handle = 0;
    }
    #endif
    isConnected = false;
}

/**	@brief Returns connection status
	@return 1-connection open, 0-connection closed.
*/
bool ConnectionUSB::IsOpen()
{
    #ifndef __unix__
    return USBDevicePrimary->IsOpen() && isConnected;
    #else
    return isConnected;
    #endif
}

/**	@brief Sends given data buffer to chip through USB port.
	@param buffer data buffer, must not be longer than 64 bytes.
	@param length given buffer size.
	@return number of bytes sent.
*/
int ConnectionUSB::SendData(const unsigned char *buffer, unsigned long length, unsigned long timeout_ms)
{
    unsigned char temp[64];
    if(length > 64)
        length = 64;

    memcpy(temp, buffer, length);
    long len = length;
    if(IsOpen())
    {
        if(m_hardwareName == HW_DIGIRED || m_hardwareName == HW_STREAMER)
        {
            #ifndef __unix__
            if(OutCtrlEndPt3)
            {
                OutCtrlEndPt3->Write(temp, len);
            }
            else
                len = 0;
            #else
                len = libusb_control_transfer(dev_handle, LIBUSB_REQUEST_TYPE_VENDOR,CTR_W_REQCODE ,CTR_W_VALUE, CTR_W_INDEX, temp, length, USB_TIMEOUT);
            #endif
        }
        else
        {
            #ifndef __unix__
            if(OutCtrEndPt)
            {
                OutCtrEndPt->XferData(temp, len);
            }
            else
                len = 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x01, temp, len, &actual, USB_TIMEOUT);
                len = actual;
            #endif
        }
    }
    else
        return 0;
    stringstream ss;
    ss << "write(" << len << "): ";
    for(int i=0; i<len; ++i)
        ss << int2hex(buffer[i], 1) << " ";
    ss << endl;
    MessageLog::getInstance()->write(ss.str(), LOG_DATA);
    return len;
}

/**	@brief Reads data coming from the chip through USB port.
	@param buffer pointer to array where received data will be copied, array must be
	big enough to fit received data.
	@param bytesRead number of bytes to read from chip.
	@return number of bytes received.
*/
int ConnectionUSB::ReadData(unsigned char *buffer, unsigned long bytesRead, unsigned long timeout_ms)
{
    unsigned char tempBuffer[64];
    memset(tempBuffer, 0, 64);

    long len = bytesRead;
    if(IsOpen())
    {
        if(m_hardwareName == HW_DIGIRED || m_hardwareName == HW_STREAMER)
        {
            #ifndef __unix__
            if(InCtrlEndPt3)
                InCtrlEndPt3->Read((unsigned char*)tempBuffer, len);
            else
                len = 0;
            #else
            len = libusb_control_transfer(dev_handle, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN ,CTR_R_REQCODE ,CTR_R_VALUE, CTR_R_INDEX, tempBuffer, len, USB_TIMEOUT);
            #endif
        }
        else
        {
            #ifndef __unix__
            if(InCtrEndPt)
                InCtrEndPt->XferData((unsigned char*)tempBuffer, len);
            else
                len = 0;
            #else
                int actual = 0;
                libusb_bulk_transfer(dev_handle, 0x81, (unsigned char*)tempBuffer, len, &actual, USB_TIMEOUT);
                len = actual;
            #endif
        }
    }

    memset(buffer, 0, bytesRead);
    memcpy(buffer, tempBuffer, 64);
    stringstream ss;
    ss << " read(" << len << "): ";
    for(int i=0; i<len; ++i)
        ss << int2hex(buffer[i], 1) << " ";
    ss << endl;
    MessageLog::getInstance()->write(ss.str(), LOG_DATA);

    return len;
}

#ifdef __unix__
/**	@brief Function for handling libusb callbacks
*/
void callback_libusbtransfer(libusb_transfer *trans)
{
	USBTransferContext *context = reinterpret_cast<USBTransferContext*>(trans->user_data);
	switch(trans->status)
	{
    case LIBUSB_TRANSFER_CANCELLED:
        printf("Transfer canceled\n" );
        context->bytesXfered = trans->actual_length;
        context->done = true;
        break;
    case LIBUSB_TRANSFER_COMPLETED:
        if(trans->actual_length == context->bytesExpected)
		{
			context->bytesXfered = trans->actual_length;
			context->done = true;
		}
		//printf("Transfer complete %i\n", trans->actual_length);
        break;
    case LIBUSB_TRANSFER_ERROR:
        printf("TRANSFER ERRRO\n");
        break;
    case LIBUSB_TRANSFER_TIMED_OUT:
        printf("transfer timed out\n");

        break;
    case LIBUSB_TRANSFER_OVERFLOW:
        printf("transfer overflow\n");

        break;
    case LIBUSB_TRANSFER_STALL:
        printf("transfer stalled\n");
        break;
	}
	lmSem_post(context->m_lock);
}
#endif

/**	@brief Checks all connected USB devices and found chips are added to list.
*/
void ConnectionUSB::FindDevices()
{
    #ifndef __unix__
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
            if( m_hardwareName == HW_DIGIRED)
            {
                unsigned char tbuf[64];
                long len = 64;
                memset(tbuf, 0, len);
                tbuf[0] = 0x50;
                SendData(tbuf, len);
                ReadData(tbuf, len);
                if(tbuf[0] == 1)
                    name.append( " (Transmitter)" );
                else
                    name.append( " (Receiver)" );
            }
            else if( m_hardwareName == HW_STREAMER)
            {
                name.append( " (Stream)" );
            }
            m_deviceNames.push_back(name);
        }
        currentPortIndex = -1;
    }
    #else
    m_dev_pid_vid.clear();
    m_deviceNames.clear();
    int usbDeviceCount = libusb_get_device_list(ctx, &devs);
    if(usbDeviceCount > 0)
    {
        libusb_device_descriptor desc;
        for(int i=0; i<usbDeviceCount; ++i)
        {
            int r = libusb_get_device_descriptor(devs[i], &desc);
            if(r<0)
                cout << "failed to get device description" << endl;
            int pid = desc.idProduct;
            int vid = desc.idVendor;
            if( vid == 1204)
            {
                if(pid == 34323)
                {
                    m_hardwareName = HW_DIGIGREEN;
                    m_deviceNames.push_back("DigiGreen");
                    m_dev_pid_vid.push_back( pair<int,int>(pid,vid));
                }
                else if(pid == 241)
                {
                    m_hardwareName = HW_DIGIRED;
                    m_deviceNames.push_back("DigiRed");
                    m_dev_pid_vid.push_back( pair<int,int>(pid,vid));
                }
            }
        }
    }
    else
    {
        libusb_free_device_list(devs, 1);
        return;
    }
    #endif
}

void ConnectionUSB::ClearComm()
{

}

/**	@return name of currently opened device as string.
*/
string ConnectionUSB::DeviceName()
{
	#ifndef __unix__
	string name;
	char tempName [256];
	//memcpy(&tempName, &USBDevicePrimary->DeviceName, 256);
	for(int i=0; i<256; ++i)
	{
		tempName[i] = USBDevicePrimary->FriendlyName[i];
	}
    name = tempName;
    return name;
    #else
    string name = "no name";
    return name;
    #endif
}

/**
	@brief Starts asynchronous data reading from board
	@param *buffer buffer where to store received data
	@param length number of bytes to read
	@return handle of transfer context
*/
int ConnectionUSB::BeginDataReading(char *buffer, long length)
{
    int i = 0;
	bool contextFound = false;
	//find not used context
    for(i = 0; i<USB_MAX_CONTEXTS; i++)
    {
        if(!contexts[i].used)
        {
            contextFound = true;
            break;
        }
    }
    if(!contextFound)
        return -1;
    contexts[i].used = true;
    #ifndef __unix__
    if(InEndPt)
        contexts[i].context = InEndPt->BeginDataXfer((unsigned char*)buffer, length, contexts[i].inOvLap);
	return i;
    #else
    unsigned int Timeout = 1000;
    libusb_transfer *tr = contexts[i].transfer;
    //libusb_set_iso_packet_lengths(contexts[i].transfer, 512*64);
	libusb_fill_bulk_transfer(tr, dev_handle, 0x86, (unsigned char*)buffer, length, callback_libusbtransfer, &contexts[i], Timeout);
	contexts[i].done = false;
	contexts[i].bytesXfered = 0;
	contexts[i].bytesExpected = length;
    int status = libusb_submit_transfer(tr);
//    int actual = 0;
//    int status = libusb_bulk_transfer(dev_handle, 0x86, (unsigned char*)buffer, length, &actual, USB_TIMEOUT);
    if(status != 0)
        printf("ERROR BEGIN DATA TRANSFER %s\n", libusb_error_name(status));
    #endif
    return i;
}

/**
	@brief Waits for asynchronous data reception
	@param contextHandle handle of which context data to wait
	@param timeout_ms number of miliseconds to wait
	@return 1-data received, 0-data not received
*/
int ConnectionUSB::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    if( contexts[contextHandle].used == true && contextHandle > 0)
    {
    int status = 0;
    #ifndef __unix__
	if(InEndPt)
        status = InEndPt->WaitForXfer(contexts[contextHandle].inOvLap, timeout_ms);
	return status;
    #else
	unsigned long t1, t2;
	t2 = t1 = getMilis();
    while(contexts[contextHandle].done == false && (t2 - t1) < timeout_ms)
	{
	    struct timeval tv;
	    tv.tv_sec = 1;
	    tv.tv_usec = 0;
		//if(libusb_handle_events(ctx) != 0)
		if(libusb_handle_events_timeout_completed(ctx, &tv, NULL) != 0)
            printf("error libusb_handle_events %i\n", status);
		t2 = getMilis();
		milSleep(1);
	}
	if(lmSem_wait(contexts[contextHandle].m_lock, 1000) == 0)
        return 1;
    else
        return 0;
	if((t2-t1) > timeout_ms)
		return 0;
    return 1;
    #endif
    }
    else
        return 0;
}

/**
	@brief Finishes asynchronous data reading from board
	@param buffer array where to store received data
	@param length number of bytes to read, function changes this value to number of bytes actually received
	@param contextHandle handle of which context to finish
	@return false failure, true success
*/
int ConnectionUSB::FinishDataReading(char *buffer, long &length, int contextHandle)
{
    if( contexts[contextHandle].used == true && contextHandle > 0)
    {
    #ifndef __unix__
    int status = 0;
    if(InEndPt)
        status = InEndPt->FinishDataXfer((unsigned char*)buffer, length, contexts[contextHandle].inOvLap, contexts[contextHandle].context);
    contexts[contextHandle].used = false;
    contexts[contextHandle].reset();
    return status;
    #else
	length = contexts[contextHandle].bytesXfered;
	contexts[contextHandle].used = false;
	contexts[contextHandle].reset();
	return length;
    #endif
    }
    else
        return 0;
}

/**
	@brief Aborts reading operations
*/
void ConnectionUSB::AbortReading()
{
#ifndef __unix__
	InEndPt->Abort();
#else
    for(int i=0; i<USB_MAX_CONTEXTS; ++i)
    {
        libusb_cancel_transfer( contexts[i].transfer );
    }
#endif
}

/**
	@brief Starts asynchronous data Sending to board
	@param *buffer buffer to send
	@param length number of bytes to send
	@return handle of transfer context
*/
int ConnectionUSB::BeginDataSending(const char *buffer, long length)
{
    int i = 0;
	//find not used context
	bool contextFound = false;
     for(i = 0; i<USB_MAX_CONTEXTS; i++)
    {
        if(!contextsToSend[i].used)
        {
            contextFound = true;
            break;
        }
    }
    if(!contextFound)
        return -1;
    contextsToSend[i].used = true;
    #ifndef __unix__
    if(OutEndPt)
        contextsToSend[i].context = OutEndPt->BeginDataXfer((unsigned char*)buffer, length, contextsToSend[i].inOvLap);
	return i;
    #else
    unsigned int Timeout = 1000;
    libusb_transfer *tr = contexts[i].transfer;
    libusb_set_iso_packet_lengths(contexts[i].transfer, 512*64);
	libusb_fill_bulk_transfer(tr, dev_handle, 0x86, (unsigned char*)buffer, length, callback_libusbtransfer, &contexts[i], Timeout);
	contexts[i].done = false;
	contexts[i].bytesXfered = 0;
	contexts[i].bytesExpected = length;
    libusb_submit_transfer(tr);
    #endif
    return i;
}

/**
	@brief Waits for asynchronous data sending
	@param contextHandle handle of which context data to wait
	@param timeout_ms number of miliseconds to wait
	@return 1-data received, 0-data not received
*/
int ConnectionUSB::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    if( contextsToSend[contextHandle].used == true )
    {
    #ifndef __unix__
	int status = 0;
	if(OutEndPt)
        status = OutEndPt->WaitForXfer(contextsToSend[contextHandle].inOvLap, timeout_ms);
	return status;
    #else
	unsigned long t1, t2;
	t2 = t1 = getMilis();
    while(contextsToSend[contextHandle].bytesXfered < contextsToSend[contextHandle].bytesExpected && (t2 - t1) < timeout_ms)
	{
		milSleep(1);
		libusb_handle_events(ctx);
		t2 = getMilis();
	}
	if((t2-t1) > timeout_ms)
		return 0;
    return 1;
    #endif
    }
    else
        return 0;
}

/**
	@brief Finishes asynchronous data sending to board
	@param buffer array where to store received data
	@param length number of bytes to read, function changes this value to number of bytes acctually received
	@param contextHandle handle of which context to finish
	@return false failure, true success
*/
int ConnectionUSB::FinishDataSending(const char *buffer, long &length, int contextHandle)
{
    if( contextsToSend[contextHandle].used == true)
    {
    #ifndef __unix__
	if(OutEndPt)
        OutEndPt->FinishDataXfer((unsigned char*)buffer, length, contextsToSend[contextHandle].inOvLap, contextsToSend[contextHandle].context);
    contextsToSend[contextHandle].used = false;
    return length;
    #else
	length = contextsToSend[contextHandle].bytesXfered;
	contextsToSend[contextHandle].used = false;
	return length;
    #endif
    }
    else
        return 0;
}

/**
	@brief Aborts sending operations
*/
void ConnectionUSB::AbortSending()
{
#ifndef __unix__
	OutEndPt->Abort();
#endif
}

eLMS_DEV ConnectionUSB::ConnectedDeviceType()
{
    if(m_hardwareName == HW_DIGIGREEN)
        return LMS_DEV_DIGIGREEN;
    else if(m_hardwareName == HW_DIGIRED)
        return LMS_DEV_DIGIRED;
    else if(m_hardwareName == HW_STREAMER)
        return LMS_DEV_STREAM;
    else
        return LMS_DEV_UNKNOWN;
}
