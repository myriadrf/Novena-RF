#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "SignalHandler.h"

class ConnectionManager;

class Programmer : public SignalHandler
{
public:
    virtual void HandleMessage(const LMS_Message &msg);

    Programmer(ConnectionManager* pSerPort);
    ~Programmer();

    int LoadFile(const char* filename, const int type);
    int UploadProgram(const int device, const int prog_mode);
protected:
    ConnectionManager* m_serPort;
    unsigned char* m_data;
    long m_data_size;
};

#endif // PROGRAMMER_H

