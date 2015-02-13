/**
@file   ConnectionManager.h
@author Lime Microsystems (www.limemicro.com)
@brief  Communication ports managing, handles data writing and reading from chip
*/

#include "ConnectionManager.h"
#include <iostream>
#include <stdio.h>

#include "CommonUtilities.h"
#include "ConnectionCOM.h"
#include "ConnectionUSB.h"
#include "ConnectionSPI.h"
#include "MessageLog.h"
#include <sstream>

using namespace std;

/** @brief Returns most repeated value, if all different returns first one
*/
unsigned char bestOfThree(const unsigned char A, const unsigned char B, const unsigned char C)
{
    if(A == B || A == C)
        return A;
    else if(B == C)
        return B;
    return A;
}

/** @brief Handles incoming messages
    @param msg message about event
*/
void ConnectionManager::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
    case MSG_REGISTER_TEST:
        cout << msg.text << endl;
        break;
    default:
        break;
    }
}

/** @brief Creates connection interfaces, determines system endianness for forming 16 bit values
*/
ConnectionManager::ConnectionManager() : activeControlPort(NULL), activeTransmitter(NULL), activeReceiver(NULL)
{
    lmCreateSemaphore(m_lock, 1, 1);
    m_activeProtocol = LMS_PROTOCOL_UNDEFINED;
    m_currentDeviceType = LMS_DEV_UNKNOWN;
    m_expansionBoardType = EXP_BOARD_UNKNOWN;
    m_connectionStatus = "Board disconnected";
	m_testWriting = false;
    m_tripleCheckRead = false;
    m_system_big_endian = true;
    unsigned int endian_test = 0x11000044;
    unsigned char *p_byte;
    p_byte = (unsigned char*)&endian_test;
    if(p_byte[0] == 0x11 && p_byte[3] == 0x44) // little endian
        m_system_big_endian = false;
    else if(p_byte[0] == 0x44 && p_byte[3] == 0x11) // big endian
        m_system_big_endian = true;
    else
        MessageLog::getInstance()->write("Cannot determine system endiannes. Using big endian", LOG_ERROR);
    currentReceiver = -1;
	currentTransmitter = -1;
    m_controllingDevice = LMS_RECEIVER;
    m_connections[COM_PORT] = new ConnectionCOM();
    MessageLog::getInstance()->write("COM connection supported\n", LOG_INFO);
    m_connections[USB_PORT] = new ConnectionUSB();
    MessageLog::getInstance()->write("USB connection supported\n", LOG_INFO);
    m_connections[SPI_PORT] = new ConnectionSPI();
    MessageLog::getInstance()->write("SPI connection supported\n", LOG_INFO);
}

/** @brief Destroys connection interfaces
*/
ConnectionManager::~ConnectionManager()
{
    std::map<eConnectionType, IConnection*>::iterator iter;
    for (iter = m_connections.begin(); iter != m_connections.end(); ++iter)
    {
        delete iter->second;
    }

    if(activeReceiver)
        delete activeReceiver;
    if(activeTransmitter)
        delete activeTransmitter;
    lmDestroySemaphore(m_lock);
}

/** @brief Returns whether control device is opened
    @return true if opened
*/
bool ConnectionManager::IsOpen()
{
    if(activeControlPort)
        return activeControlPort->IsOpen();
    return false;
}

/** @brief Connects to first found chip
    @return true is connection was made
*/
bool ConnectionManager::Open()
{
    bool status = false;
    FindDevices();
    if(m_receivers.size() > 0)
    {
        status = OpenReceiver(0);
    }
//    if(m_transmitters.size() > 0)
//        OpenTransmitter(0);
//    SetControlDevice(m_controllingDevice);
    return status;
}

/** @brief Closes connection to chip
*/
void ConnectionManager::Close()
{
    if(activeControlPort)
    {
        activeControlPort->Close();
    }
    if(activeReceiver)
    {
        activeReceiver->Close();
        Notify(LMS_Message(MSG_BOARD_DISCONNECTED, "Disconnected from board\n", activeReceiver->GetType(), 0));
    }
    if(activeTransmitter)
    {
        activeTransmitter->Close();
        //Notify(LMS_Message(MSG_BOARD_DISCONNECTED, "Disconnected from board", activeReceiver->GetType(), 0));
    }
    m_connectionStatus = "Board disconnected";
}

/** @brief Finds all currently connected devices and forms transmitter,receiver device lists
*/
void ConnectionManager::FindDevices()
{
    m_transmitters.clear();
    m_receivers.clear();
    DeviceInfo dev;
    std::map<eConnectionType, IConnection*>::iterator iter;
    for (iter = m_connections.begin(); iter != m_connections.end(); ++iter)
    {
        vector<string> names;
        IConnection *port = iter->second;
        port->FindDevices();
        names = port->GetDeviceNames();
        for(unsigned int i=0; i<names.size(); ++i)
        {
            dev.name = names[i];
            dev.port = iter->first;
            dev.portIndex = i;
            dev.type = LMS_TRANCEIVER;
            //cout << dev.name << endl;
            m_transmitters.push_back(dev);
            m_receivers.push_back(dev);
        }
        port->Close();
    }
}

/** @brief Creates connection to selected receiver
    @param i receiver index from list
    @return true if success
*/
bool ConnectionManager::OpenReceiver(unsigned int i)
{
    if(i >= m_receivers.size())
        return false;

    if(activeReceiver)
    {
        delete activeReceiver;
        activeReceiver = NULL;
    }

    switch(m_receivers[i].port)
    {
    case COM_PORT:
        m_activeProtocol = LMS_PROTOCOL_LMS64C;
        activeReceiver = new ConnectionCOM();
        activeReceiver->FindDevices();
        break;
    case USB_PORT:
        m_activeProtocol = LMS_PROTOCOL_DIGIC;
        activeReceiver = new ConnectionUSB();
        activeReceiver->FindDevices();
        break;
    case SPI_PORT:
        m_activeProtocol = LMS_PROTOCOL_NOVENA;
        activeReceiver = new ConnectionSPI();
        activeReceiver->FindDevices();
        break;
    default:
        return false;
    }

    if(activeReceiver && i < m_receivers.size() )
    {
        currentReceiver = i;
        if( activeReceiver->Open( m_receivers[i].portIndex) )
        {
            stringstream ss;
            ss << "Connected to Board on ";
            ss << m_receivers[i].name << " | ";

            SetControlDevice(m_controllingDevice);
            GenericPacket pkt;
            pkt.cmd = CMD_GET_INFO;

            if(m_receivers[i].port == COM_PORT)
            {
                TransferPacket(pkt);
                ss << "Firmware: " << (int)pkt.inBuffer[0] << "  Device: ";
                if(pkt.inBuffer[1] < LMS_DEV_COUNT)
                {
                    ss << LMS_DEV_NAMES[pkt.inBuffer[1]];
                    m_currentDeviceType = (eLMS_DEV)pkt.inBuffer[1];
                }
                else
                {
                    m_currentDeviceType = LMS_DEV_UNKNOWN;
                    ss << "UNSPECIFIED ID";
                }
                m_expansionBoardType = (eEXP_BOARD)pkt.inBuffer[4];
                ss << "  Protocol: " << (int)pkt.inBuffer[2] << endl;
            }
            else if(m_receivers[i].port == SPI_PORT)
            {
                //TransferPacket(pkt);
                if(IsNovenaBoard())
                {
                    ss << "Firmware: ?" << "  Device: ";
                    m_currentDeviceType = LMS_DEV_NOVENA;
                    ss << "Novena";
                    ss << "  Protocol: ?" << endl;
                    m_expansionBoardType = EXP_BOARD_MYRIAD_NOVENA;
                }
                else
                {
                    ss << "Firmware: ?" << "  Device: ";
                    m_currentDeviceType = LMS_DEV_UNKNOWN;
                    ss << "UNSPECIFIED ID";
                    ss << "  Protocol: ?" << endl;
                    m_expansionBoardType = EXP_BOARD_UNKNOWN;
                }
            }
            else
            {
                m_currentDeviceType = activeReceiver->ConnectedDeviceType();
                if(m_currentDeviceType == LMS_DEV_STREAM)
                {
                    m_activeProtocol = LMS_PROTOCOL_LMS64C;
                    TransferPacket(pkt);
                    ss << "Firmware: " << (int)pkt.inBuffer[0] << "  Device: ";
                    if(pkt.inBuffer[1] < LMS_DEV_COUNT)
                    {
                        ss << LMS_DEV_NAMES[pkt.inBuffer[1]];
                        m_currentDeviceType = (eLMS_DEV)pkt.inBuffer[1];
                    }
                    else
                    {
                        m_currentDeviceType = LMS_DEV_UNKNOWN;
                        ss << "UNSPECIFIED ID";
                    }
                    m_expansionBoardType = (eEXP_BOARD)pkt.inBuffer[4];
                    ss << "  Protocol: " << (int)pkt.inBuffer[2] << endl;
                }
                else
                {
                    m_activeProtocol = LMS_PROTOCOL_DIGIC;
                    TransferPacket(pkt);
                    ss << "Firmware: ?" << "  Device: ";
                    ss << LMS_DEV_NAMES[m_currentDeviceType];
                    m_expansionBoardType = EXP_BOARD_UNKNOWN;
                    ss << "  Protocol: ?" << endl;
                }
            }
            m_connectionStatus = ss.str();
            Notify(LMS_Message(MSG_BOARD_CONNECTED, ss.str(), activeReceiver->GetType(), i));
            ss << endl;
            return true;
        }
    }
    else
        currentReceiver = -1;
    return false;
}

/** @brief Creates connection to selected transmitter
    @param i transmitter index from list
    @return true if success
*/
bool ConnectionManager::OpenTransmitter(unsigned int i)
{
    if(activeTransmitter)
    {
        delete activeTransmitter;
        activeTransmitter = NULL;
    }
    switch(m_transmitters[i].port)
    {
    case COM_PORT:
        activeTransmitter = new ConnectionCOM();
        activeTransmitter->FindDevices();
        break;
    default:
        return false;
    }
    if(activeTransmitter)
    {
        if( activeTransmitter->Open(i) )
        {
            currentTransmitter = i;
            string msg = "Connected to Board on ";
            msg.append(m_transmitters[i].name);
            MessageLog::getInstance()->write(msg);
            SetControlDevice(m_controllingDevice);
            return true;
        }
    }
    else
        currentTransmitter = -1;
    return false;
}

/** @brief Returns a list of connected receivers
    @return vector of receiver device names
*/
vector<string> ConnectionManager::GetReceiverList()
{
    vector<string> receivers;
    for(unsigned int i=0; i<m_receivers.size(); ++i)
    {
        receivers.push_back(m_receivers[i].name);
    }
    return receivers;
}

/** @brief Returns a list of connected transmitters
    @return vector of transmitter device names
*/
vector<string> ConnectionManager::GetTransmitterList()
{
    vector<string> transmitters;
    for(unsigned int i=0; i<m_transmitters.size(); ++i)
    {
        transmitters.push_back(m_transmitters[i].name);
    }
    return transmitters;
}

/** @brief Sets which device receives configuration commands
    @param dev device type: receiver, transmitter, transceiver
*/
void ConnectionManager::SetControlDevice( eDeviceType dev )
{
    m_controllingDevice = dev;
    switch(m_controllingDevice)
    {
    case LMS_RECEIVER:
        if(activeReceiver)
            activeControlPort = activeReceiver;
        break;
    case LMS_TRANSMITTER:
        if(activeTransmitter)
            activeControlPort = activeTransmitter;
        break;
    default:
        break;
    }
}

/** @brief Returns connection port selected for controlling
*/
eDeviceType ConnectionManager::GetControlDevice()
{
    return m_controllingDevice;
}

/** @brief Returns connection port to opened receiver
*/
int ConnectionManager::GetOpenedReceiver()
{
    return currentReceiver;
}

/** @brief Returns connection port to opened transmitter
*/
int ConnectionManager::GetOpenedTransmitter()
{
    return currentTransmitter;
}

/** @brief Writes given data to one chip register
    @param addr_reg register address 8 bits
    @param data_reg register value 8 bits
    @return command status
*/
int ConnectionManager:: mSPI_write(unsigned char addr_reg, unsigned char data_reg)
{
    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
    pkt.outBuffer[0] = addr_reg;
    pkt.outBuffer[1] = data_reg;
    pkt.outLen = 2;
    if ( IsOpen() )
        return TransferPacket(pkt);
    return STATUS_UNDEFINED;
}

/** @brief Reads one register value from chip
    @param addr_reg register address 8 bits
    @return register value 8 bits
*/
unsigned char ConnectionManager:: mSPI_read(unsigned char addr_reg)
{
    if (IsOpen())
    {
        GenericPacket pkt;
        pkt.cmd = CMD_LMS6002_RD;
        pkt.outBuffer[0] = addr_reg;
        pkt.outLen = 1;
        if (TransferPacket(pkt) == STATUS_COMPLETED_CMD)
            return pkt.inBuffer[1];
    }
    return 0;
}

/** @brief Writes given data to chip without any modifications
    @param buf data buffer to write
    @param len length of data buffer
    @return true if success
*/
bool ConnectionManager::Port_write_direct(const unsigned char *buf, const long len)
{
    if(activeControlPort)
    {
        unsigned long bytesSent = activeControlPort->SendData(buf, len);
        if(bytesSent > 0)
            return true;
    }
    else
        MessageLog::getInstance()->write("Connection port not opened\n", LOG_WARNING);
    return false;
}

/** @brief Tries to read any incoming data and puts it to given buffer
    @param buf buffer for received data, must be big enough to store len bytes
    @param len number of bytes to read, after procedure it will be changed to actual number of bytes received
    @param true if success
*/
bool ConnectionManager::Port_read_direct(unsigned char *buf, long &len)
{
    const long blen = len;
    unsigned char *inBuffers = new unsigned char[blen];
    int bytesReceived;

    if(activeControlPort)
    {
        bytesReceived = activeControlPort->ReadData(inBuffers, len);
        memcpy(buf, inBuffers, bytesReceived);
        delete []inBuffers;
        return true;
    }
    else
        MessageLog::getInstance()->write("Connection port not opened\n", LOG_WARNING);
    delete []inBuffers;
    return false;
}

/** @brief Enables or Disables triple checking of received data
*/
void ConnectionManager::EnableTrippleReadChecking(bool checkMultipleReads)
{
    m_tripleCheckRead = checkMultipleReads;
}

/** @brief Clears currently used connection buffers
*/
void ConnectionManager::ClearComm()
{
    if(activeControlPort)
        activeControlPort->ClearComm();
}

void ConnectionManager::EnableTestWrittenData(bool enabled)
{
    m_testWriting = enabled;
}

string ConnectionManager::GetConnectionStatus()
{
    return m_connectionStatus;
}

eConnectionType ConnectionManager::GetConnectionType()
{
    if(activeControlPort)
        return activeControlPort->GetType();
    return CONNECTION_UNDEFINED;
}

eLMS_DEV ConnectionManager::GetConnectedDeviceType()
{
    return m_currentDeviceType;
}

eEXP_BOARD ConnectionManager::GetExpansionBoardType()
{
    return m_expansionBoardType;
}

/**
    @brief Start asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read.
    @return context handle
*/
int ConnectionManager::BeginDataReading(char *buffer, long length)
{
    return activeControlPort->BeginDataReading(buffer, length);
}
/**
    @brief Blocks until data is received or set number of milliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of milliseconds to wait
    @return 1-data received, 0-data not received
*/
int ConnectionManager::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForReading(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read, will be changed to actual number of bytes received
    @param contextHandle context handle returned by BeginDataReading()
    @return received data length
*/
int ConnectionManager::FinishDataReading(char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataReading(buffer, length, contextHandle);
}

/**
	@brief Aborts reading operations
*/
void ConnectionManager::AbortReading()
{
	activeControlPort->AbortReading();
}

/**
    @brief Start asynchronous data sending.
    @param buffer data buffer to be sent
    @param length number of bytes to send.
    @return context handle
*/
int ConnectionManager::BeginDataSending(const char *buffer, long length)
{
    return activeControlPort->BeginDataSending(buffer, length);
}
/**
    @brief Blocks until data is sent or set number of miliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of miliseconds to wait
    @return 1-data sent, 0-data not sent
*/
int ConnectionManager::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForSending(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data sending.
    @param buffer where to put received data
    @param length number of bytes to send, will be changed to actual number of bytes sent
    @param contextHandle context handle returned by BeginDataReading()
    @return sent data length
*/
int ConnectionManager::FinishDataSending(const char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataSending(buffer, length, contextHandle);
}

/**
	@brief Aborts sending operations
*/
void ConnectionManager::AbortSending()
{
	activeControlPort->AbortSending();
}

/** @brief Transfers data between packet and connected device
    @param pkt packet containing output data and to receive incomming data
    @return command status
*/
int ConnectionManager::TransferPacket(GenericPacket &pkt)
{
    if(!IsOpen())
        return STATUS_UNDEFINED;

    if( lmSem_wait(m_lock, 500))
        return STATUS_BUSY_CMD;

    int packetLen;
    eLMS_PROTOCOL protocol = GetActiveProtocol();
    switch(protocol)
    {
    case LMS_PROTOCOL_UNDEFINED:
        return STATUS_UNDEFINED;
    case LMS_PROTOCOL_LMS64C:
        packetLen = ProtocolLMS64C::pktLength;
        break;
    case LMS_PROTOCOL_DIGIC:
        packetLen = ProtocolDIGIC::pktLength;
        break;
    case LMS_PROTOCOL_NOVENA:
        packetLen = ProtocolDIGIC::pktLength;
        break;
    }
    int outLen = 0;
    unsigned char* outBuffer = NULL;
    outBuffer = PreparePacket(pkt, outLen, protocol, this);
    unsigned char* inBuffer = new unsigned char[outLen];
    memset(inBuffer, 0, outLen);

    int outBufPos = 0;
    int inDataPos = 0;
    if(outLen == 0)
    {
        printf("packet outlen = 0\n");
        outLen = 1;
    }

    if(protocol == LMS_PROTOCOL_NOVENA)
    {
        for(int i=0; i<outLen; i+=packetLen)
        {
            int bytesToSend = 0;
            bytesToSend = (outLen-i) > packetLen ? packetLen : outLen-i;
            if( Port_write_direct(&outBuffer[outBufPos], bytesToSend) )
            {
                outBufPos += packetLen;
                if(pkt.cmd == CMD_LMS6002_RD)
                {
                    long readLen = bytesToSend;
                    Port_read_direct(&inBuffer[inDataPos], readLen);
                    inDataPos += readLen;
                }
            }
        }
    }
    else
        for(int i=0; i<outLen; i+=packetLen)
        {
            int bytesToSend = packetLen;
            if( m_activeProtocol == LMS_PROTOCOL_NOVENA)
                bytesToSend = (outLen-i) > packetLen ? packetLen : outLen-i;
            if( Port_write_direct(&outBuffer[outBufPos], bytesToSend) )
            {
                outBufPos += packetLen;
                long readLen = packetLen;
                Port_read_direct(&inBuffer[inDataPos], readLen);
                inDataPos += readLen;
            }
        }
    pkt.inLen = inDataPos;
    ParsePacket(pkt, inBuffer, inDataPos, protocol);
    delete outBuffer;
    delete inBuffer;
    lmSem_post(m_lock);
    return pkt.status;
}

/** @return protocol used by connected device
*/
eLMS_PROTOCOL ConnectionManager::GetActiveProtocol()
{
    return m_activeProtocol;
}
