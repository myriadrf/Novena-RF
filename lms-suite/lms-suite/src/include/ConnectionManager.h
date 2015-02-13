/**
@file   ConnectionManager.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for managing connection ports and handling data writing and reading
*/

#ifndef LMS_CONNECTION_MANAGER_H
#define LMS_CONNECTION_MANAGER_H

#include "LMS_Commands.h"
#include "IConnection.h"
#include <string>
#include <map>
#include "SignalHandler.h"
#include "Protocols.h"
#include "lmSemaphore.h"
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

/** @brief Handles communication with device. Data writing and reading is not
    thread safe
*/
class ConnectionManager : public SignalHandler
{
public:
    static const int cMAX_CONTROL_PACKET_SIZE = 64;
    static const int cPACKET_HEADER_SIZE = 8;

    virtual void HandleMessage(const LMS_Message &msg);

	ConnectionManager();
	~ConnectionManager();

	void SetControlDevice( eDeviceType dev );
    eDeviceType GetControlDevice();

    eConnectionType GetConnectionType();

    bool IsOpen();
	bool Open();
	void Close();
	void FindDevices();

    int GetOpenedReceiver();
    int GetOpenedTransmitter();
    bool OpenReceiver(unsigned int i);
    bool OpenTransmitter(unsigned int i);
    vector<string> GetReceiverList();
    vector<string> GetTransmitterList();

    eLMS_PROTOCOL GetActiveProtocol();
	int TransferPacket(GenericPacket &pkt);

	unsigned char mSPI_read(unsigned char addr_reg);
	int mSPI_write(unsigned char addr_reg, unsigned char data_reg);

	bool Port_write_direct(const unsigned char *buf, const long len);
	bool Port_read_direct(unsigned char *buf, long &len);

	void EnableTrippleReadChecking(bool checkMultipleReads);
	bool GetTriplleReadCheckingState() { return m_tripleCheckRead; };
	void ClearComm();
	void EnableTestWrittenData(bool enabled);

	string GetConnectionStatus();
    eLMS_DEV GetConnectedDeviceType();
    eEXP_BOARD GetExpansionBoardType();

	int BeginDataReading(char *buffer, long length);
	int WaitForReading(int contextHandle, unsigned int timeout_ms);
	int FinishDataReading(char *buffer, long &length, int contextHandle);
	void AbortReading();

    int BeginDataSending(const char *buffer, long length);
	int WaitForSending(int contextHandle, unsigned int timeout_ms);
	int FinishDataSending(const char *buffer, long &length, int contextHandle);
	void AbortSending();

protected:
    lmSemaphore m_lock;
    eLMS_PROTOCOL m_activeProtocol;
    eLMS_DEV m_currentDeviceType;
    eEXP_BOARD m_expansionBoardType;

    vector<DeviceInfo> m_receivers;
    vector<DeviceInfo> m_transmitters;

	/// Port used for communication.
	IConnection *activeControlPort;

	IConnection *activeTransmitter;
	IConnection *activeReceiver;
	std::map<eConnectionType, IConnection*> m_connections;

	string m_connectionStatus;

	eDeviceType m_controllingDevice;
	int currentReceiver;
	int currentTransmitter;
	bool m_system_big_endian;

	bool m_tripleCheckRead;
	bool m_testWriting;
};

#endif
