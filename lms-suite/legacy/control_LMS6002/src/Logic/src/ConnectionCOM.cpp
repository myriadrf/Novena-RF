#include "ConnectionCOM.h"
#include "LMS_Commands.h"
#include <fstream>
#include <sstream>
#include "MessageLog.h"
#include <iomanip>


#ifdef LINUX
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#endif // LINUX
using namespace std;

/** @brief Converts given integer to hex string
    @param i integer to convert
    @param sizeBytes number of bytes to print
*/
string int2hex(int i, int sizeBytes)
{
    std::stringstream stream;
    for(int k=sizeBytes; k>0; --k)
        stream << std::setfill ('0') << std::setw(2) << std::hex << ((i >> (k-1)*8)&0xFF);
    return stream.str();
}

const int COM_RETRY_INTERVAL = 20; //ms
const int COM_TOTAL_TIMEOUT = 300; //ms

/** @brief Initializes com port connection
*/
ConnectionCOM::ConnectionCOM()
{
	connected = false;
	comPortList.clear();
	m_deviceNames.clear();
	m_connectionType = COM_PORT;
#ifndef LINUX
	hComm = INVALID_HANDLE_VALUE;
#else
    hComm = -1;
#endif
	comBaudrate = 9600;
}

/** @brief When object is destroyed it closed it's opened COM port
*/
ConnectionCOM::~ConnectionCOM()
{
	Close();
}

/** @brief Opens connection to first found chip
    @return true if device found
*/
bool ConnectionCOM::Open()
{
	bool opened = false;
	comPortList.clear();
	if(comPortList.size() == 0)
		FindAllComPorts();

	m_deviceNames.clear();
	if(m_deviceNames.size() == 0)
		FindDevices();

	for(unsigned int i=0; i<m_deviceNames.size(); i++)
	{
		if( Open(i) )
		{
			currentDeviceIndex = i;
			break;
		}
	}
	return opened;
}

/** @brief Opens connection to selected chip
    @param index chip index in device list
*/
bool ConnectionCOM::Open(int index)
{
	Close();
	if(index >= 0 && m_deviceNames.size() > 0 )
	{
		comPortName = m_deviceNames[index];
		connected = Open(comPortName.c_str(), comBaudrate);
		if( connected )
		{
			currentDeviceIndex = index;
			return connected;
		}
	}
	return false;
}

/** @brief Closes connection to chip
*/
void ConnectionCOM::Close()
{
    connected = false;
#ifndef LINUX
	if (hComm != INVALID_HANDLE_VALUE)
	{
		SetCommTimeouts(hComm, &m_ctmoOld);
		CloseHandle(hComm);
	}
	hComm = INVALID_HANDLE_VALUE;
#else
    if( hComm >= 0)
    {
        close(hComm);
    }
    hComm = -1;
#endif
}

/** @brief Returns whether chip is connected
    @return chip is connected
*/
bool ConnectionCOM::IsOpen()
{
#ifndef LINUX
	if (hComm != INVALID_HANDLE_VALUE && TestConnectivity() )
		return true;
#else
    if( hComm != -1 && TestConnectivity() )
        return true;
#endif
    return false;
}

/** @brief Sends data through COM port
    @param buffer data buffer to send
    @param length size of data buffer
    @return Number of bytes sent
*/
int ConnectionCOM::SendData(const unsigned char *buffer, unsigned long length)
{
    int retryCount = 0;
    const int maxRetries = (COM_TOTAL_TIMEOUT/COM_RETRY_INTERVAL) > 1 ? (COM_TOTAL_TIMEOUT/COM_RETRY_INTERVAL) : 1;
    bool status = false;

#ifndef LINUX
	unsigned long bytesWriten = 0;
	PurgeComm(hComm, PURGE_TXCLEAR|PURGE_RXCLEAR);

	for(int i = 0; i<maxRetries && bytesWriten == 0; ++i)
    {
        if (!WriteFile(hComm, buffer, length , &bytesWriten, &m_osWOverlap))
        {
            if (GetLastError() == ERROR_IO_PENDING)
            {
                if (WaitForSingleObjectEx(m_osWOverlap.hEvent, (int) COM_RETRY_INTERVAL, true) == WAIT_TIMEOUT)
                    status = false;
                else
                    bytesWriten = m_osWOverlap.InternalHigh;
            }
            else
                status = false;
        }
        else
            status = true;
        bytesWriten = m_osWOverlap.InternalHigh;
        ++retryCount;
    }
#else
    long bytesWriten = 0;
    for(int i = 0; i<maxRetries && bytesWriten == 0; ++i)
    {
        bytesWriten = write(hComm, buffer, length);
        if(bytesWriten <= 0)
        {
            if(bytesWriten < 0)
                MessageLog::getInstance()->write("COM PORT: error writting data\n", LOG_ERROR);
            if(bytesWriten == 0)
                MessageLog::getInstance()->write("COM PORT: data bytes sent 0\n", LOG_WARNING);
            status = false;
        }
        else
            status = true;
        ++retryCount;
    }
#endif
    if(retryCount == maxRetries)
        MessageLog::getInstance()->write("COM PORT: send data failed.\n", LOG_WARNING);
    if(bytesWriten == length)
        status = true;
    if(status == true)
    {
        stringstream ss;
        ss << "write(" << bytesWriten << "): ";
        for(unsigned i=0; i<length; ++i)
            ss << int2hex(buffer[i], 1) << " ";
        ss << " - retries: " << retryCount-1 << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_DATA);
    }
	return bytesWriten;
}

/** @brief Reads data from COM port
    @param buffer pointer to data buffer for receiving
    @param length number of bytes to read
    @return Number of bytes received
*/
int ConnectionCOM::ReadData(unsigned char *buffer, unsigned long length)
{
    int retryCount = 0;
    const int maxRetries = (COM_TOTAL_TIMEOUT/COM_RETRY_INTERVAL) > 1 ? (COM_TOTAL_TIMEOUT/COM_RETRY_INTERVAL) : 1;
    bool status = false;

    memset(buffer, 0, length);
	long bytesReaded = 0;
	char cRawData[COM_BUFFER_LENGTH];
	unsigned long bytesToRead = length;

	memset(cRawData, '\0', sizeof(cRawData[0])*COM_BUFFER_LENGTH);

	for(int i=0; i<maxRetries && status == false && bytesReaded == 0; ++i)
    {
#ifndef LINUX
        if ( !ReadFile(hComm, cRawData, bytesToRead, NULL, &m_osROverlap) )
        {
            if (GetLastError() == ERROR_IO_PENDING)
            {
                if (WaitForSingleObject(m_osROverlap.hEvent, (int) 100) == WAIT_TIMEOUT)
                    status = false;
                else
                    bytesReaded = m_osROverlap.InternalHigh;
            }
            else
                status = false;
        }
        else
            status = true;
        bytesReaded = m_osROverlap.InternalHigh;
#else
        bytesReaded = read(hComm, cRawData, bytesToRead);
        if(bytesReaded <= 0)
        {
            if(bytesReaded < 0)
                MessageLog::getInstance()->write("COM PORT: error reading data\n", LOG_ERROR);
            if(bytesReaded == 0)
                MessageLog::getInstance()->write("COM PORT: reading 0 bytes\n", LOG_WARNING);
            status = false;
        }
#endif
        retryCount++;
        memcpy(buffer, cRawData, bytesToRead);
    }
	//cout << "Bytes received " << bytesReaded << "  in " << retryCount << " atempts" << endl;
	if(bytesReaded == bytesToRead)
        status = true;
    if(status == true)
    {
        stringstream ss;
        ss << "read(" << bytesReaded << "): ";
        for(unsigned int i=0; i<bytesToRead; ++i)
            ss << int2hex(cRawData[i], 1) << " ";
        ss <<  " - retries: " << retryCount-1 << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_DATA);
    }
	if(retryCount == maxRetries)
        MessageLog::getInstance()->write("COM PORT: read data timeout\n", LOG_WARNING);
	return bytesReaded;
}

/** @brief Searches for available COM ports and adds them to list
*/
void ConnectionCOM::FindAllComPorts()
{
    Close();
	comPortList.clear();
#ifndef LINUX
	HKEY hSERIALCOMM;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, ("HARDWARE\\DEVICEMAP\\SERIALCOMM"),	0, KEY_QUERY_VALUE, &hSERIALCOMM) == ERROR_SUCCESS)
	{
		// Get the max value name and max value lengths
		DWORD dwMaxValueNameLen;
		DWORD dwMaxValueLen;
		DWORD dwQueryInfo = RegQueryInfoKey(hSERIALCOMM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		if (dwQueryInfo == ERROR_SUCCESS)
		{
			DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars*sizeof(char);
			DWORD dwMaxValueDataSizeInChars = dwMaxValueLen / sizeof(char) + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars*sizeof(char);

			// Allocate some space for the value name and value data
			char *szValueName = new char[dwMaxValueNameSizeInChars];
			char *byValue = new char[dwMaxValueDataSizeInBytes];
			if (szValueName && byValue)
			{
				// Enumerate all the values underneath HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
				DWORD dwIndex = 0;
				DWORD dwType;
				DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
				DWORD dwDataSize = dwMaxValueDataSizeInBytes;
				memset(szValueName, 0, dwMaxValueNameSizeInBytes);
				memset(byValue, 0, dwMaxValueDataSizeInBytes);
				LONG nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				while (nEnum == ERROR_SUCCESS)
				{
					// If the value is of the correct type, then add it to the array
					if (dwType == REG_SZ)
					{
						char* szPort = reinterpret_cast<char*>(byValue);
						comPortList.push_back(szPort);
					}
					// Prepare for the next time around
					dwValueNameSize = dwMaxValueNameSizeInChars;
					dwDataSize = dwMaxValueDataSizeInBytes;
					memset(szValueName, 0, dwMaxValueNameSizeInBytes);
					memset(byValue, 0, dwMaxValueDataSizeInBytes);
					++dwIndex;
					nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName,	&dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				}
			}
		}
		// Close the registry key now that we are finished with it
		RegCloseKey(hSERIALCOMM);

		if (dwQueryInfo != ERROR_SUCCESS)
			SetLastError(dwQueryInfo);
	}
#else
    fstream fin;
    char tempBuffer[256];
    string result = "";
#warning Currently searching only for ACM connections
    fin.open("/tmp/foundSerialPorts1.txt", ios::out);
    fin.close();
    system( "ls /dev | grep ttyACM > /tmp/foundSerialPorts1.txt");
    fin.open("/tmp/foundSerialPorts1.txt", ios::in);
    while(!fin.eof())
    {
        fin.getline(tempBuffer, 256);
        result = "/dev/";
        result.append(tempBuffer);
        if( strlen(tempBuffer) > 3 ) //longer than tty
            comPortList.push_back(result);
    }
    fin.close();
#endif
}

/** @brief Opens COM port
    @param comName COM port name
    @param baudrate COM port baudrate
*/
int ConnectionCOM::Open(const char *comName, int baudrate)
{
	Close();
	if (strlen(comName) == 0)
		return 0;

	int errorCode = 0;

#ifndef LINUX
	// Initialize Overlap structures
	m_osROverlap.Internal = 0;
	m_osROverlap.InternalHigh = 0;
	m_osROverlap.Offset = 0;
	m_osROverlap.OffsetHigh = 0;
	m_osROverlap.hEvent = CreateEvent(NULL, false, false, NULL);

	m_osWOverlap.Internal = 0;
	m_osWOverlap.InternalHigh = 0;
	m_osWOverlap.Offset = 0;
	m_osWOverlap.OffsetHigh = 0;
	m_osWOverlap.hEvent = CreateEvent(NULL, false, false, NULL);

	// Initialize DSB structure
	memset(&m_dcbCommPort, 0, sizeof(m_dcbCommPort));

	m_dcbCommPort.BaudRate = comBaudrate;
	m_dcbCommPort.fBinary = 1;
	m_dcbCommPort.fParity = 0;
	m_dcbCommPort.fOutxCtsFlow = 0;
	m_dcbCommPort.fOutxDsrFlow = 0;
	m_dcbCommPort.fDtrControl = 0;
	m_dcbCommPort.fDsrSensitivity = 0;
	m_dcbCommPort.fTXContinueOnXoff = 0;
	m_dcbCommPort.fOutX = 0;
	m_dcbCommPort.fInX = 0;
	m_dcbCommPort.fErrorChar = 0;
	m_dcbCommPort.fNull = 0;
	m_dcbCommPort.fRtsControl = 0;
	m_dcbCommPort.fAbortOnError = 0;
	m_dcbCommPort.fDummy2 = 0;
	// m_dcbCommPort.wReserved = 0;
	m_dcbCommPort.XonLim = 512;
	m_dcbCommPort.XoffLim = 512;
	m_dcbCommPort.ByteSize = 8;
	m_dcbCommPort.Parity = 0;
	m_dcbCommPort.StopBits = 0;
	//m_dcbCommPort.StopBits = 1;
	m_dcbCommPort.XonChar = 17;
	m_dcbCommPort.XoffChar = 19;
	m_dcbCommPort.ErrorChar = 0;
	m_dcbCommPort.EofChar = 26;
	m_dcbCommPort.EvtChar = 0;
	m_dcbCommPort.wReserved1 = 0;
	m_dcbCommPort.DCBlength = sizeof(DCB);

	// Initialize Timeout's
	m_ctmoNew.ReadIntervalTimeout = 20;
	m_ctmoNew.ReadTotalTimeoutMultiplier = 0;
	m_ctmoNew.ReadTotalTimeoutConstant = 0; // 1;
	m_ctmoNew.WriteTotalTimeoutMultiplier = 0;
	m_ctmoNew.WriteTotalTimeoutConstant = 0;

	// Open COM port
	string stmp;
	stmp = "\\\\.\\";
	stmp.append(comName);
	hComm = CreateFile(stmp.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

	if (hComm != INVALID_HANDLE_VALUE)
	{
		// Set Events
		if (!SetCommMask(hComm, 0))
			errorCode = -1;

		// Set Timeouts
		GetCommTimeouts(hComm, &m_ctmoOld);
		if (!SetCommTimeouts(hComm, &m_ctmoNew))
			errorCode = -2;

		// Set DCB
		if (!SetCommState(hComm, &m_dcbCommPort))
			errorCode = -4;
	}
	else
	{
		errorCode = -8;
	};

	// Check the results
	if (errorCode != 0)
	{
		//unsigned long err = GetLastError();
		CloseHandle(hComm);
		hComm = INVALID_HANDLE_VALUE;
		return errorCode;
	}
	else
	{
		PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
		return 1;
	}
#else
    hComm = open(comName, O_RDWR | O_NOCTTY | O_SYNC);
    if(hComm < 0)
    {
        MessageLog::getInstance()->write("Connection manager: failed opening COM port\n", LOG_ERROR);
        return -8;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if( tcgetattr(hComm, &tty) != 0)
    {
        MessageLog::getInstance()->write("Connection Manager: error from tcgetattr\n", LOG_ERROR);
        return -8;
    }
    int speed = B9600;
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0; // read non blocking
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);

    if(tcsetattr(hComm, TCSANOW, &tty) != 0)
    {
        MessageLog::getInstance()->write("Connection manager: error from tcsetattr\n", LOG_ERROR);
        return -8;
    }
#endif
    return 1;
}

/** @brief Checks if chip is connected to currently open port
    @return chip is connected
*/
bool ConnectionCOM::TestConnectivity()
{
//temporarily set to always return true to show all com ports
    return true;
#ifndef LINUX
	if (hComm != INVALID_HANDLE_VALUE)
#else
    if( hComm >= 0)
#endif
	{
	    unsigned char out[64];
	    unsigned char in[64];
	    memset(in, 0, 64);
	    out[0] = CMD_GET_INFO;
        SendData(out, 64);
        ReadData(in, 64);
        if(in[0] == CMD_GET_INFO && in[1] == 0x01)
            return true;
        else
            return false;
	}
	return false;
}

/** @brief Finds all chips connected to com ports
*/
void ConnectionCOM::FindDevices()
{
    Close();
    comPortList.clear();
	if(comPortList.size() == 0)
		FindAllComPorts();

	m_deviceNames.clear();
	string comName;
	for(unsigned int i=0; i<comPortList.size(); i++)
	{
	    comName = comPortList[i];
#ifndef LINUX
		if( Open(comName.c_str(), comBaudrate) > 0)
		{
			if( TestConnectivity() ) //if respond add it to device list
				m_deviceNames.push_back(comName);
		}
		Close();
#else
        m_deviceNames.push_back(comName);
#endif
	}
}

/** @brief Returns found devices names
    @return vector of device names
*/
vector<string> ConnectionCOM::GetDeviceNames()
{
    return m_deviceNames;
}
