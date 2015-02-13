#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "LMS_Commands.h"
#include "IConnection.h"
#include <string>
#include <map>
#include "common.h"

enum eDeviceType
{
    LMS_RECEIVER,
    LMS_TRANSMITTER,
    LMS_TRANCEIVER
};

struct DeviceInfo
{
    string name;
    eDeviceType type;
    eConnectionType port;
    int portIndex;
};

class ConnectionManager
{
public:
    static const int cMAX_CONTROL_PACKET_SIZE = 64;
    static const int cPACKET_HEADER_SIZE = 8;

	ConnectionManager();
	~ConnectionManager();

	void SetControlDevice( eDeviceType dev );
    eDeviceType GetControlDevice();

    bool IsOpen();
	bool Open();
	void Close();
	void FindDevices();

    int GetOpenedReceiver();
    int GetOpenedTransmitter();
    bool OpenReceiver(int i);
    bool OpenTransmitter(int i);
    vector<string> GetReceiverList();
    vector<string> GetTransmitterList();

    int SendData( eCMD_LMS cmd, const unsigned char *data, long length);
	int SendReadData( eCMD_LMS cmd, const unsigned char *outData, unsigned long oLength, unsigned char *inData, unsigned long &iLength);

    void SPI_Rst();
	void SPI_RstAct();
    void SPI_RstInact();

	bool SPI_Read(sPrData *pPD);
	char SPI_Read_OneByte(const unsigned char Command);
	bool SPI_Write(sPrData *pPD);
	void SPI_Wr_ADF(sPrData *pPD);
	void SetBrdLNA(int i);
	void SetBrdPA(int i);

protected:
    int MakeAndSendPacket( eCMD_LMS cmd, const unsigned char *data, long length);
    int ReadData(unsigned char *data, long &length);

    vector<DeviceInfo> m_receivers;
    vector<DeviceInfo> m_transmitters;
	/// Port used for communication.
	IConnection *activeControlPort;
	IConnection *activeTransmitter;
	IConnection *activeReceiver;
	std::map<eConnectionType, IConnection*> m_connections;

	eDeviceType m_controllingDevice;
	int currentReceiver;
	int currentTransmitter;
	bool m_system_big_endian;
};

#endif
