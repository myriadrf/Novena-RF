#include "ConnectionManager.h"
#include <iostream>

#include "ConnectionCOM.h"
//#include "ConnectionUSB.h"
#include "MessageLog.h"
#include <sstream>

using namespace std;

/** @brief Creates connection interfaces, determines system endianness for forming 16 bit values
*/
ConnectionManager::ConnectionManager() : activeControlPort(NULL), activeTransmitter(NULL), activeReceiver(NULL)
{
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
    //m_connections[USB_PORT] = new ConnectionUSB();
    MessageLog::getInstance()->write("COM connection supported\n", LOG_INFO);
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
*/
bool ConnectionManager::Open()
{
    FindDevices();
    if(m_receivers.size() > 0)
        OpenReceiver(0);
//    if(m_transmitters.size() > 0)
//        OpenTransmitter(0);
//    SetControlDevice(m_controllingDevice);
    return false;
}

/** @brief Closes connection to chip
*/
void ConnectionManager::Close()
{
    bool wasConnected = false;
    if(activeControlPort)
    {
        wasConnected = activeControlPort->IsOpen();
        activeControlPort->Close();
    }
    if(activeReceiver)
        activeReceiver->Close();
    if(activeTransmitter)
        activeTransmitter->Close();
    if(wasConnected)
        MessageLog::getInstance()->write("Connection to Board closed\n");
}

/** @brief Finds all currently connected devices and forms transmitter,receiver device lists
*/
void ConnectionManager::FindDevices()
{
    Close();
// TODO (userk1#1#): differentiate between receivers and transmitters
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
            m_transmitters.push_back(dev);
            m_receivers.push_back(dev);
        }
    }
}

/** @brief Sends given data to chip
    @param cmd LMS chip command
    @param data data buffer to send
    @param length size of data in bytes
    @return Command status

    Forms packet header and sends given data buffer to chip.
    When using CMD_LMS7002_WR the data buffer should be pointer to array of unsigned shorts.
 */
int ConnectionManager::SendData(eCMD_LMS cmd, const unsigned char* data, long length)
{
    const int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    long sendLen;

    int status = STATUS_UNDEFINED;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);

    const unsigned char* pdata_start = data;

    while( length > 0)
    {
        sendLen = length < maxDataLen ? length : maxDataLen;

        if( MakeAndSendPacket(cmd, pdata_start, sendLen) )
        {
            long readLen = cMAX_CONTROL_PACKET_SIZE;

            status = ReadData(buffer, readLen);
            if(status == STATUS_ERROR_CMD || readLen == 0)
                return STATUS_ERROR_CMD;
        }
        else
        {
            return STATUS_ERROR_CMD;
        }
        pdata_start += sendLen;
        length -= sendLen;
    }
    return status;
}

/** @brief Creates packet buffer according to given command and data buffers
    @param cmd LMS chip command
    @param data data buffer to send
    @param length size of data in bytes
    @return true if success

    When using CMD_LMS7002_WR the data buffer should be pointer to array of unsigned shorts.
*/
int ConnectionManager::MakeAndSendPacket( eCMD_LMS cmd, const unsigned char *data, long length)
{
    unsigned char temp;
    const int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    if(length > maxDataLen)
    {
        MessageLog::getInstance()->write("MakeAndSendPacket : Packet larger than 64 bytes, truncating to 64 bytes." , LOG_WARNING);
        length = maxDataLen;
    }
    long sendLen;

    int status = false;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);

    sendLen = length < maxDataLen ? length : maxDataLen;
    memcpy(&buffer[8], data, sendLen);
    if(activeControlPort)
    {
        buffer[0] = cmd;
        //buffer[1] = 0; //Status
        // buffer[3-7] reserved
        switch( cmd )
        {
        case CMD_SI5351_WR:
        case CMD_SI5356_WR:
            buffer[2] = sendLen/2; //data block pairs(address,value)
            break;
        case CMD_SI5351_RD:
        case CMD_SI5356_RD:
            buffer[2] = sendLen; //data blocks(address)
            break;
        case CMD_ADF4002_WR:
            buffer[2] = sendLen/3; //data block(3xByte)
            break;
        case CMD_LMS7002_WR:
            buffer[2] = sendLen/4; //data block pairs(address,value)
            for(int i=8; i<cMAX_CONTROL_PACKET_SIZE; i+=2)
            {
                temp = buffer[i];
                buffer[i] = buffer[i+1];
                buffer[i+1] = temp;
            }
            break;
        case CMD_LMS7002_RD:
            buffer[2] = sendLen/2; //data blocks(address)
            break;
        case CMD_LMS7002_RST:
        case CMD_GET_INFO:
            buffer[2] = 1;
            break;
        case CMD_LMS6002_RD:
            buffer[2] = sendLen;
            break;
        case CMD_LMS6002_WR:
            buffer[2] = sendLen/2;
            break;
        case 0x2A:
        case 0x2B:
            buffer[2] = 1;
            break;

        case CMD_PE636040_WR:
        //case CMD_PE636040_RD:
            buffer[2] = sendLen/3;
            break;
        case CMD_MYRIAD_GPIO_WR:
        //case CMD_MYRIAD_GPIO_RD:
            buffer[2] = sendLen;
            break;
        default:
            MessageLog::getInstance()->write("Sending packet with unrecognized command", LOG_WARNING);
        }
        // retry data sending


        if( activeControlPort->SendData(buffer, cMAX_CONTROL_PACKET_SIZE) )
        {
            status = true;
        }
        else
            status = false;

    }
    return status;
}

/** @brief Receives data from chip
    @param data array for incoming data
    @param length number of bytes to receive, this variable will be changed to actual number of bytes received
    @return Command status
    Receives incoming data from chip and places it to given array.

*/
int ConnectionManager::ReadData(unsigned char* data, long& length)
{
    if(length > cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE)
    {
        length = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    }

    int status = STATUS_UNDEFINED;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);
    if(activeControlPort)
    {
        int bytesReceived = activeControlPort->ReadData(buffer, cMAX_CONTROL_PACKET_SIZE);
        if(bytesReceived > 0)
        {
            status = buffer[1];
            length = length > bytesReceived ? bytesReceived : length;
            memcpy(data, buffer, length);
        }
        else
            status = STATUS_UNDEFINED;
    }
    return status;
}

/** @brief Sends given data to chip and reads incoming data
    @param cmd LMS chip command
    @param outData data buffer to send
    @param oLength size of outData in bytes
    @param inData received data
    @param iLength data size to receive
    @return Command status

    When using CMD_LMS7002_WR or CMD_LMS7002_RD commands the data buffers should be pointers to array of unsigned shorts.
*/
int ConnectionManager::SendReadData( eCMD_LMS cmd, const unsigned char *outData, unsigned long oLength, unsigned char *inData, unsigned long &iLength)
{
    const int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    unsigned char outBuffer[maxDataLen];
    memset(outBuffer, 0, maxDataLen);
    unsigned char inBuffer[maxDataLen];

    long bytesToRead = iLength;

    int status = STATUS_UNDEFINED;

    int outBufPos = 0;
    int inDataPos = 0;


    for(unsigned int i=0; i<oLength; ++i)
    {
        outBuffer[outBufPos++] = outData[i];
        if(outBufPos >= maxDataLen || (cmd == CMD_LMS7002_RD && outBufPos>=28) || outBufPos == oLength)
        {
            if(MakeAndSendPacket(cmd, outBuffer, outBufPos))
            {
                long readLen = cMAX_CONTROL_PACKET_SIZE;
                memset(inBuffer, 0, maxDataLen);
                status = ReadData(inBuffer, readLen);

                if(cmd == CMD_LMS7002_RD)
                {
                    unsigned char temp;
                    if(m_system_big_endian)
                        for(int j=0; j<outBufPos; j+=2)
                        {
                            temp = inBuffer[i];
                            inBuffer[i] = inBuffer[i+1];
                            inBuffer[i+1] = temp;
                        }
                }

                for(int j=0; j<(readLen-cPACKET_HEADER_SIZE)/2; ++j)
                    inBuffer[j] = inBuffer[j*2+9];

                bytesToRead = ((iLength - inDataPos) > outBufPos) ? outBufPos : (iLength-inDataPos);
                memcpy(&inData[inDataPos], inBuffer, bytesToRead);
                //memcpy(&inData[inDataPos], inBuffer, outBufPos);
                inDataPos += outBufPos;
                if(inDataPos > iLength)
                {
                    return status;
                }
            }
            //cout << "SEND READ DATA: status " << status << endl;
            outBufPos = 0;
            memset(outBuffer, 0, maxDataLen);
        }
    }
    return status;
}

/** @brief Creates connection to selected receiver
    @param i receiver index from list
    @return true if success
*/
bool ConnectionManager::OpenReceiver(int i)
{
    if(activeReceiver)
    {
        delete activeReceiver;
        activeReceiver = NULL;
    }

    switch(m_receivers[i].port)
    {
    case COM_PORT:
        activeReceiver = new ConnectionCOM();
        activeReceiver->FindDevices();
        break;
    case USB_PORT:
        //activeReceiver = new ConnectionUSB();
        //activeReceiver->FindDevices();
        break;
    }

    if(activeReceiver)
    {
        currentReceiver = i;
        if( activeReceiver->Open(i) )
        {
            //string msg = "Connected to Receiver on ";
            string msg = "Connected to Board on ";
            msg.append(m_receivers[i].name);
            msg.append("\n");
            MessageLog::getInstance()->write(msg);
            SetControlDevice(m_controllingDevice);
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
bool ConnectionManager::OpenTransmitter(int i)
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
    }
    if(activeTransmitter)
    {
        if( activeTransmitter->Open(i) )
        {
            currentTransmitter = i;
            //string msg = "Connected to Transmitter on ";
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
    }
}

eDeviceType ConnectionManager::GetControlDevice()
{
    return m_controllingDevice;
}

int ConnectionManager::GetOpenedReceiver()
{
    return currentReceiver;
}

int ConnectionManager::GetOpenedTransmitter()
{
    return currentTransmitter;
}

void ConnectionManager::SPI_Rst()
{
    unsigned char buf[1];
    buf[0] = 2;
    SendData(CMD_LMS7002_RST, buf, 1);
}
void ConnectionManager::SPI_RstAct()
{
    unsigned char buf[1];
    buf[0] = 1;
    SendData(CMD_LMS7002_RST, buf, 1);
}
void ConnectionManager::SPI_RstInact()
{
    unsigned char buf[1];
    buf[0] = 0;
    SendData(CMD_LMS7002_RST, buf, 1);
}

bool ConnectionManager::SPI_Read(sPrData *pPD)
{
    unsigned char *buf = new unsigned char[pPD->iToR];
	unsigned char *inBuf = new unsigned char[pPD->iToR];
	unsigned long bytesRead = pPD->iToR;

	bool status;
	int itmp = 0;
	memset(buf, 0, pPD->iToR);
	memset(inBuf, 0, pPD->iToR);

	// Construct write (uC->Chip) commands
	for (int j = 0; j < pPD->iToR; j++)
	{
		buf[itmp] = pPD->cCmdR[pPD->iRInd[j]];
		itmp++;
	};

	// Write commands
	status = SendReadData(CMD_LMS6002_RD, (unsigned char*)buf, pPD->iToR, (unsigned char*)inBuf, bytesRead);

	// Read Data from Chip
	for (int j = 0; j < pPD->iToR && j < bytesRead; j++)
	{
		pPD->cDataR[pPD->iRInd[j]] = inBuf[j];
	};

	delete[]buf;
	delete[]inBuf;

	return status == STATUS_COMPLETED_CMD;
}
char ConnectionManager::SPI_Read_OneByte(const unsigned char Command)
{
    unsigned char outbuf[1];
    outbuf[0] = Command;
    unsigned char *inbuf = new unsigned char[64];
	memset(inbuf, 0x0, 64);
    unsigned long bytesRead = 1;
	int status = SendReadData(CMD_LMS6002_RD, (unsigned char*)outbuf, sizeof(outbuf), (unsigned char*)inbuf, bytesRead);
	char cRez = inbuf[0];
	delete[]inbuf;
	return cRez;
}
bool ConnectionManager::SPI_Write(sPrData *pPD)
{
    int bytesToSend = 2 * pPD->iToW;
	unsigned char *buf = new unsigned char[bytesToSend];
	int ind = 0;
	for (int j = 0; j < pPD->iToW; j++)
	{
		buf[ind] = pPD->cCmdW[pPD->iWInd[j]];
		ind++;
		buf[ind] = pPD->cDataW[pPD->iWInd[j]];
		ind++;
	};
	int status = SendData(CMD_LMS6002_WR, (unsigned char*)buf, bytesToSend);
	delete[]buf;
	return status == STATUS_COMPLETED_CMD;
}
void ConnectionManager::SPI_Wr_ADF(sPrData *pPD)
{
    unsigned char buf[64];
    memset(buf, 0, 64);
    int ind = 0;
    for(int j=0; j<pPD->iToW; j++)
    {
        buf[ind] = pPD->cDataW[pPD->iWInd[j]];
        ++ind;
    };
    SendData(CMD_ADF4002_WR, buf, ind);
}
void ConnectionManager::SetBrdLNA(int i)
{
    unsigned char buf[1];
    switch(i)
    {
        case 1:
            buf[0] = 0x03;
            break;
        case 2:
            buf[0] = 0x01;
            break;
        case 3:
            buf[0] = 0x00;
            break;
        default:
            buf[0] = 0x03;
            break;
    }
    SendData((eCMD_LMS)0x2A, buf, 1);
}
void ConnectionManager::SetBrdPA(int i)
{
    unsigned char buf[1];
    switch(i)
    {
        case 1:
            buf[0] = 0x00;
            break;
        case 2:
            buf[0] = 0x01;
            break;
        default:
            buf[0] = 0;
            break;
    }
    SendData((eCMD_LMS)0x2B, buf, 1);
}
