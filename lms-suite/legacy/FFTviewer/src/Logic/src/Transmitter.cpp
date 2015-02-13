// -----------------------------------------------------------------------------
// FILE: 		Transmitter.cpp
// DESCRIPTION:	implements samples transmitting
// DATE:		2013-07-17
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "Transmitter.h"
#include <math.h>
#include <iostream>
#include "ConnectionManager.h"
#include "Main_Module.h"
#include "TimeCounter.h"
#include "CyAPI.h"
using namespace std;

/** @brief Transmitter
  *
  * @todo: document this function
  */
Transmitter::Transmitter(Main_Module* pMainModule)
{
    working = false;
    p_main = pMainModule;
    device = p_main->getSerPort();
    GenerateSamples(5, 1024, 20);
}

/** @brief ~Transmitter
  *
  * @todo: document this function
  */
Transmitter::~Transmitter()
{

}

/** @brief StartSendingSamples
  *
  * @todo: document this function
  */
void Transmitter::StartSendingSamples()
{
    if(!working)
    {
        working = true;
        pthread_create(&m_transmitThreadID, NULL, transmitThreadEntry, this);
    }
}

/** @brief StopSendingSamples
  *
  * @todo: document this function
  */
void Transmitter::StopSendingSamples()
{
    working = false;
    //pthread_cancel(m_transmitThreadID);
}

/** @brief LoadSamplesFromFile
  *
  * @todo: document this function
  */
void Transmitter::LoadSamplesFromFile(string filename, bool binary)
{
    fstream fin;
    m_Isamples.clear();
    m_Qsamples.clear();
    double sample;
    if(binary)
    {
        fin.open(filename.c_str(), ios::in | ios::binary);
        while( !fin.eof() )
        {
            fin.read((char*)&sample, sizeof(double));
            m_Isamples.push_back(sample);
            fin.read((char*)&sample, sizeof(double));
            m_Qsamples.push_back(sample);
        }
    }
    else
    {
        fin.open(filename.c_str(), ios::in);
        while( !fin.eof() )
        {
            fin >> sample;
            m_Isamples.push_back(sample);
            fin >> sample;
            m_Qsamples.push_back(sample);
        }
    }
    fin.close();
}

/** @brief GenerateSamples
  *
  * @todo: document this function
  */
void Transmitter::GenerateSamples(double freq, double amplitude, double samplingRate)
{
    m_Isamples.clear();
    m_Qsamples.clear();
    double period = 1/freq;
    double angularFreq = (2*3.141596)/period;
    double timeStep = 1/samplingRate;

    int currSample = 0;
    //generate one period of samples
    double t=0;
    cout << endl;
    for(int i=0; i<period/timeStep; i++)
    {
        currSample = (sin(angularFreq*t) * amplitude);
        m_Isamples.push_back(currSample);
        t+=timeStep;
    }
    for(int i=m_Isamples.size()/4; i<m_Isamples.size()+m_Isamples.size()/4; i++)
    {
        m_Qsamples.push_back( m_Isamples[i%m_Isamples.size()] );
    }
}

void Transmitter::Transmit()
{
    m_bytesXferred = 0;
    m_transmitErrors = 0;
    m_packetsSent=0;

    int bufSize = 4096*64;
    int probePos = 0;
    int bufPos = 0;
    long sendLen = bufSize;

    int QueueSize = 16;
    int QueueSizeMask = QueueSize-1;
    /*int* contexts = new int[QueueSize];*/
	unsigned char** buffers = new unsigned char*[QueueSize];
    for (int i = 0; i < QueueSize; i++)
    {
		buffers[i] = new unsigned char[bufSize];
		for(int j=0; j<bufSize; j+=4)
        {
            buffers[i][j] = 7;
            buffers[i][j+1] = 255;
            buffers[i][j+2] = 24;
            buffers[i][j+3] = 0;
        }
    }

    CCyUSBDevice *usbdev;
    usbdev = new CCyUSBDevice(NULL);

    CCyUSBEndPoint *outEndPt;

    usbdev->Open(0);
    bool endptfound = false;
    if(usbdev->IsOpen())
    {
        for(int i=0; i<usbdev->EndPointCount(); ++i)
        {
            if( usbdev->EndPoints[i]->Address == 0x01)
            {
                outEndPt =  usbdev->EndPoints[i];
                endptfound = true;
                break;
            }
        }
    }
    if(!endptfound)
    {
        cout << "transmitter end point not found " << endl;
        return;
    }



    long t1_info, t2_info;
    t1_info = GetTickCount();

    //PUCHAR			*buffers		= new PUCHAR[QueueSize];
    CCyIsoPktInfo	**isoPktInfos	= new CCyIsoPktInfo*[QueueSize];
    PUCHAR			*contexts		= new PUCHAR[QueueSize];
    OVERLAPPED		inOvLap[QueueSize];
    long len = 4096 * 64; // Each xfer request will get PPX isoc packets
    outEndPt->SetXferSize(len);

    for (int i=0; i< QueueSize; i++)
    {
        isoPktInfos[i]    = new CCyIsoPktInfo[64];
        inOvLap[i].hEvent = CreateEvent(NULL, false, false, NULL);
        //memset(buffers[i], 0,len);
    }

    /*for(int b=0; b<QueueSize; b++)
        for(int i=0; i<bufSize; i+=4)
        {
            //currsample = m_Isamples[probePos % m_Isamples.size()];
            buffers[b][i] = 0x07;
            buffers[b][i+1] = 0xff;

            buffers[b][i+2] = 0x18;
            buffers[b][i+3] = 0x00;
        }*/
    sendLen = len;
    for(int i=0; i<QueueSize; ++i)
        //contexts[i] = device->BeginDataSending(buffers[i], sendLen);
        contexts[i] = outEndPt->BeginDataXfer(buffers[i], sendLen, &inOvLap[i]);

    bool iq_select = 0;

    /*for(int b=0; b<QueueSize; b++)
        for(int i=0; i<bufSize; i+=4)
        {
            //currsample = m_Isamples[probePos % m_Isamples.size()];
            buffers[b][i] = (m_Isamples[probePos % m_Isamples.size()] >> 4) & 0x0F;
            buffers[b][i] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+1] = (m_Isamples[probePos % m_Isamples.size()] << 4) & 0xFF;
            //currsample = m_Qsamples[probePos % m_Qsamples.size()];
            buffers[b][i+2] = (m_Qsamples[probePos % m_Qsamples.size()] >> 4) & 0x0F;
            buffers[b][i+2] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+3] = (m_Qsamples[probePos % m_Qsamples.size()] << 4) & 0xFF;
            probePos++;
        }
        */



    /*long length = 64;
	unsigned char out[length];
	memset(out, 0x00, length);
	out[0] = 0x40;
	out[1] = 0x12;
	out[2] = 1;
	device->SendDataDirectly(out, length);
	device->ReadDataDirectly(out, length);
	*/
	cout << "TRANSMIT START" << endl;
	iq_select = 0;
    int b = 0;
    working = true;
    while(working)
    {
        sendLen = bufSize;
        /*for(int i=0; i<bufSize; i+=4)
        {
            //currsample = m_Isamples[probePos % m_Isamples.size()];
            buffers[b][i] = (m_Isamples[probePos % m_Isamples.size()] >> 4) & 0x0F;
            buffers[b][i] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+1] = (m_Isamples[probePos % m_Isamples.size()] << 4) & 0xFF;
            //currsample = m_Qsamples[probePos % m_Qsamples.size()];
            buffers[b][i+2] = (m_Qsamples[probePos % m_Qsamples.size()] >> 4) & 0x0F;
            buffers[b][i+2] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+3] = (m_Qsamples[probePos % m_Qsamples.size()] << 4) & 0xFF;
            probePos++;
        }*/
        /*if(!device->WaitForSending(contexts[b], 1000))
        {
            ++m_transmitErrors;
        }*/
        if (!outEndPt->WaitForXfer(&inOvLap[b], 1000))
        {
            //outEndPt->Abort();
            ++m_transmitErrors;
        }

        /*if (device->FinishDataSending(buffers[b], sendLen, contexts[b]))
  		{
            ++m_packetsSent;
            m_bytesXferred += sendLen;
		}
		else
            ++m_transmitErrors;
        */

        if (outEndPt->FinishDataXfer(buffers[b], sendLen, &inOvLap[b], contexts[b], isoPktInfos[b]))
        {
            m_bytesXferred += sendLen;
            //cout <<" packet sent: bytes = " << sendLen << endl;
            ++m_packetsSent;
        }
        else
            ++m_transmitErrors;

        sendLen = bufSize;

        /*for(int i=0; i<bufSize; i+=4)
        {
            //currsample = m_Isamples[probePos % m_Isamples.size()];
            buffers[b][i] = (m_Isamples[probePos % m_Isamples.size()] >> 4) & 0x0F;
            buffers[b][i] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+1] = (m_Isamples[probePos % m_Isamples.size()] << 4) & 0xFF;
            //currsample = m_Qsamples[probePos % m_Qsamples.size()];
            buffers[b][i+2] = (m_Qsamples[probePos % m_Qsamples.size()] >> 4) & 0x0F;
            buffers[b][i+2] |= ((unsigned int)iq_select << 4);
            iq_select = !iq_select;
            buffers[b][i+3] = (m_Qsamples[probePos % m_Qsamples.size()] << 4) & 0xFF;
            probePos++;
        }*/

        contexts[b] = outEndPt->BeginDataXfer(buffers[b], sendLen, &inOvLap[b]);
        //contexts[b] = device->BeginDataSending(buffers[b], sendLen);

        b++;
        b = b % QueueSize;

        t2_info = GetTickCount();
		if (t2_info - t1_info > 1000) // each second display info and update data rate
		{

			long deltaT = (t2_info - t1_info);
			if (deltaT <= 0)
			{
				deltaT = 1;
				m_bytesXferred = 0;
			}
			long m_bytesPerSecond = m_bytesXferred / deltaT; // / 1000;


			cout << "\nSending Rate: " << m_bytesPerSecond << "  KB/s  " << endl;
			cout << "Failures: " << m_transmitErrors << endl;
			cout << " Packets Sent: " << m_packetsSent << endl;
            m_bytesXferred = 0;
			m_packetsSent = 0;
			m_transmitErrors = 0;
			t1_info = t2_info;
		}
    }
    //device->AbortSending();
    for(int i=0; i<QueueSize; i++)
    {
        sendLen = bufSize;
        outEndPt->WaitForXfer(&inOvLap[i], 1000);
        outEndPt->FinishDataXfer(buffers[i], sendLen, &inOvLap[i], contexts[i], isoPktInfos[i]);
        //device->WaitForSending(contexts[i], 100);
        //device->FinishDataSending(buffers[i], sendLen, contexts[i]);
        delete []buffers[i];
    }
	cout << "TRANSMIT STOP" << endl;
    delete []buffers;
    delete []contexts;
}

void* Transmitter::transmitThreadEntry(void *pTransmitter)
{
    if(pTransmitter != NULL)
        reinterpret_cast<Transmitter*>(pTransmitter)->Transmit();
    return NULL;
}

void Transmitter::GetSamples(float *Ichannel, float *Qchannel, int &samplesCount)
{
    if(Ichannel && Qchannel)
    {
        for(int i=0; i<m_Isamples.size(); i++)
        {
            Ichannel[i] = m_Isamples[i];
            Qchannel[i] = m_Qsamples[i];
        }
    }
    samplesCount = m_Isamples.size();
}
