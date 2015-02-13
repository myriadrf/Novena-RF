/**
@file   ConnectionSPI.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for data communications through SPI for NOVENA board
*/

#ifndef CONNECTION_SPI_H
#define CONNECTION_SPI_H

#include "IConnection.h"
#include <fstream>

bool IsNovenaBoard();

class ConnectionSPI : public IConnection
{
public:
    static const int cSPI_BUF_SIZE = 128;
    const int cSPI_SPEED_HZ;
    ConnectionSPI();
    ~ConnectionSPI();

    bool Open();
	bool Open(int i);
	void Close();
	bool IsOpen();

	int SendData(const unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0);
	int ReadData(unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 0);

	std::vector<std::string> GetDeviceNames();
	void FindDevices();
	void ClearComm();
protected:
    char rxbuf[1024];
    int fd;
    std::fstream m_SEN;
};

#endif // CONNECTION_SPI_H
