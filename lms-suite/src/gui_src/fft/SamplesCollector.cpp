#include "SamplesCollector.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "CommonUtilities.h"
#include "NovenaFPGA.h"

#if defined(__GNUC__) || defined(__GNUG__)
    #include <unistd.h>
#endif

SamplesCollector::SamplesCollector(ConnectionManager *serPort, BlockingFIFO<SamplesPacket> *channels) : m_running(false)
{
    frameStart = 0;
    m_packetsDiscarded = 0;
    m_channels = channels;
    m_selectedDevice = BOARD_UNKNOWN;
    m_samplesToPacket = 16384;
    m_dataRate = 0;
    m_serPort = serPort;

    m_writeToFile = false;
    m_filename = "DataInStream_bin.txt";
    m_fileSizeLimit = 100000000; //100 MB
    m_dataSource = 0;
}

SamplesCollector::~SamplesCollector()
{

}

/** @brief Gets connected board type and starts it's sampling process
*/
bool SamplesCollector::StartSampling()
{
    if(m_channels == NULL)
    {
        fprintf(stderr, "Samples collector has no assigned data buffers!\n");
        return false;
    }

    m_running = true;
    switch(m_selectedDevice)
    {
    case BOARD_DIGIGREEN:
        lmThread_create(m_samplingThread, &DigiGreenSamplingThread, this);
        break;
    case BOARD_DIGIRED:
        lmThread_create(m_samplingThread, &DigiRedSamplingThread, this);
        break;
    case BOARD_STREAM:
        lmThread_create(m_samplingThread, &StreamSamplingThread, this);
        break;
    case BOARD_NOVENA:
        #ifdef __unix__
        lmThread_create(m_samplingThread, &NovenaSamplingThread, this);
        #else
        m_running = false; return false;
        #endif
        break;
    case BOARD_UNKNOWN:
    default:
        m_running = false;
        return false;
    }
    return true;
}

/** @brief Signals to stop sampling process and blocks until sampling is finished
*/
void SamplesCollector::StopSampling()
{
    printf("Stopping\n");
    m_running = false;
    lmThread_join(m_samplingThread);
}

/** @brief Sampling procedure for DigiGreen board
    @param pCollector pointer to Samples Collector
*/
void* SamplesCollector::DigiGreenSamplingThread(void* pCollector)
{
    int samplesCollected = 0;
    const int buffer_size = 32768;
    const int buffers_count = 32; // must be power of 2
    int buffers_count_mask = buffers_count-1;
    int handles[buffers_count];
    memset(handles, 0, sizeof(int)*buffers_count);
    char *buffers = NULL;
    buffers = new char[buffers_count*buffer_size];
    if(buffers == 0)
    {
        printf("error allocating buffers\n");
        return 0;
    }
    memset(buffers, 0, buffers_count*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_running = true;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);
    samples->channel = 0;

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

	const long bufLen = 64;
	long length = bufLen;
	unsigned char out[bufLen];
	memset(out, 0x00, length);
	out[0] = 0x14; //CMD_CFG_I2C_WR 0x14
	out[1] = 0xAA; //CFG_ADDR 0xAA
	out[2] = 1;
	out[4] = 0x02;
	out[5] = pthis->m_dataSource; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | 1; // TXDEN
	out[5] = (out[5] << 1) | 0; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

	//reset FPGA ON
	memset(out, 0x00, length);
	out[0] = 0x14;
	out[1] = 0xAA;
	out[2] = 1;
	out[4] = 0x03;
	out[5] = 0x00;
	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

	//USB FIFO reset
	memset(out, 0x00, length);
	out[0] = 0x40;
	out[1] = 0x10;
	out[2] = 1;
	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

    //reset FPGA OFF
    memset(out, 0x00, length);
	out[0] = 0x14;
	out[1] = 0xAA;
	out[2] = 1;
	out[4] = 0x03;
	out[5] = 0x01;
    pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

    memset(out, 0x00, length);
	out[0] = 0x14; //CMD_CFG_I2C_WR 0x14
	out[1] = 0xAA; //CFG_ADDR 0xAA
	out[2] = 1;
	out[4] = 0x02;
	out[5] = pthis->m_dataSource; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | 1; // TXDEN
	out[5] = (out[5] << 1) | 1; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

    int tempInt = 0;
    int bi = 0; //buffer index

    fstream fout;
    bool wToFile = pthis->m_writeToFile;
    unsigned long fileSizeLimit = pthis->m_fileSizeLimit;
    unsigned long fileSize = 0;
    if(wToFile)
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);

    for (int i=0; i<buffers_count; ++i)
		handles[i] = pthis->m_serPort->BeginDataReading(&buffers[i*buffer_size], buffer_size);

    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;
    while(pthis->m_running)
    {
        if(pthis->m_serPort->WaitForReading(handles[bi], 3000) == false)
		{
			++m_bufferFailures;
			skip = true;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]

		bytesToRead = buffer_size;
		if (pthis->m_serPort->FinishDataReading(&buffers[bi*buffer_size], bytesToRead, handles[bi]))
  		{
			++packetsReceived;
			totalBytesReceived += bytesToRead;
			if(wToFile && fileSize < fileSizeLimit)
            {
                fout.write(&buffers[bi*buffer_size], bytesToRead);
                fileSize += bytesToRead;
            }
			skip = false;
		}
		else
		{
			++m_bufferFailures;
			skip = true;
		}

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels->status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        char* buf;
        buf = &buffers[bi*buffer_size];
        for(int b=0; b<bytesToRead/512 && !skip; ++b)
        {
            for(int c=0; c<510; c+=3)
            {
                int pos = b*512+c;
                tempInt = (buf[pos + 1] & 0x0F) << 8;
                tempInt |= (buf[pos] & 0xFF);
                tempInt = tempInt << 20;
                samples->iqdata[samplesCollected] = tempInt >> 20;
                ++samplesCollected;
                // Q channel
                tempInt = buf[pos + 2] << 4;
                tempInt |= (buf[pos + 1] >> 4) & 0xF;
                tempInt = tempInt << 20;
                samples->iqdata[samplesCollected] = tempInt >> 20;
                ++samplesCollected;

                if(samplesCollected == samples->samplesCount)
                {
                    if(pthis->m_channels->push_back(samples, 0) == false)
                        ++pthis->m_packetsDiscarded;
                    samplesCollected = 0;
                }
            }
        }

        // Re-submit this request to keep the queue full
        memset(&buffers[bi*buffer_size], 0, buffer_size);
        handles[bi] = pthis->m_serPort->BeginDataReading(&buffers[bi*buffer_size], buffer_size);
        bi = (bi+1) & buffers_count_mask;
    }

    // Wait for all the queued requests to be cancelled
    pthis->m_serPort->AbortReading();
	for(int j=0; j<buffers_count; j++)
	{
		bytesToRead = buffer_size;
		pthis->m_serPort->WaitForReading(handles[j], 1000);
		pthis->m_serPort->FinishDataReading(&buffers[j*buffer_size], bytesToRead, handles[j]);
	}

	length = 64;
	memset(out, 0x00, length);
	out[0] = 0x14;
	out[1] = 0xaa;
	out[2] = 1;
	out[4] = 0x02;
	out[5] = 1; // RXSRC
	out[5] = (out[5] << 1) | 0x01; // TXEN
	out[5] = (out[5] << 1) | 0x01; // RXEN
	out[5] = (out[5] << 1) | 0; // TXDEN
	out[5] = (out[5] << 1) | 0; // RXDEN
	out[5] = out[5] << 1; // EN:reserved

	//pthis->m_serPort->Port_write_direct(out, length);
	//pthis->m_serPort->Port_read_direct(out, length);

	fout.close();
	delete []buffers;
	delete samples;
    printf("FULLY STOPPED\n");
    return 0;
}

/** @brief Sampling procedure for DigiRed board
    @param pCollector pointer to Samples Collector
*/
void* SamplesCollector::DigiRedSamplingThread(void* pCollector)
{
    int samplesCollected = 0;
    const int buffer_size = 4096*64;
    const int buffers_count = 32; // must be power of 2
    const int buffers_count_mask = buffers_count-1;
    int handles[buffers_count];
    memset(handles, 0, sizeof(int)*buffers_count);
    char *buffers = NULL;
    buffers = new char[buffers_count*buffer_size];
    if(buffers == 0)
    {
        printf("error allocating buffers\n");
        return 0;
    }
    memset(buffers, 0, buffers_count*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

    short tempInt = 0;
    int bi = 0; //buffer index

    fstream fout;
    bool wToFile = pthis->m_writeToFile;
    unsigned long fileSizeLimit = pthis->m_fileSizeLimit;
    unsigned long fileSize = 0;
    if(wToFile)
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);
    for (int i=0; i<buffers_count; ++i)
		handles[i] = pthis->m_serPort->BeginDataReading(&buffers[i*buffer_size], buffer_size);
    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;
    while(pthis->m_running)
    {
        if(pthis->m_serPort->WaitForReading(handles[bi], 1000) == false)
		{
			++m_bufferFailures;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]
		bytesToRead = buffer_size;
		if (pthis->m_serPort->FinishDataReading(&buffers[bi*buffer_size], bytesToRead, handles[bi]))
  		{
			++packetsReceived;
			totalBytesReceived += bytesToRead;
			if(wToFile && fileSize < fileSizeLimit)
            {
                fout.write((const char*)&buffers[bi*buffer_size], bytesToRead);
                fileSize += bytesToRead;
            }
			skip = false;
		}
		else
		{
			++m_bufferFailures;
			skip = true;
		}

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels[0].status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        short* buf;
        buf = (short*)&buffers[bi*buffer_size];
        int framestart = pthis->frameStart;
        for(int b=0; b<buffer_size/2 && !skip; ++b)
        {
            if(samplesCollected == 0)
            {
                //find frame start
                for(int fs=b; fs<buffer_size/2; ++fs)
                {
                    if( ((buf[b]&0x1000)>0) == framestart)
                        break;
                    ++b;
                }
            }
            tempInt = buf[b] & 0x0FFF;
            tempInt = tempInt << 4;
            samples->iqdata[samplesCollected] = tempInt >> 4;
            ++samplesCollected;
            if(samplesCollected >= samples->samplesCount)
            {
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
            }
        }

        // Re-submit this request to keep the queue full
        memset(&buffers[bi*buffer_size], 0, buffer_size);
        handles[bi] = pthis->m_serPort->BeginDataReading(&buffers[bi*buffer_size], buffer_size);
        bi = (bi+1) & buffers_count_mask;
    }

    // Wait for all the queued requests to be cancelled
    pthis->m_serPort->AbortReading();
	for(int j=0; j<buffers_count; j++)
	{
		bytesToRead = buffer_size;
		pthis->m_serPort->WaitForReading(handles[j], 1000);
		pthis->m_serPort->FinishDataReading(&buffers[j*buffer_size], bytesToRead, handles[j]);
	}
	fout.close();
	delete []buffers;
	delete samples;
    printf("FULLY STOPPED\n");
    return 0;
}

/** @brief Sampling procedure for DigiRed board
    @param pCollector pointer to Samples Collector
*/
void* SamplesCollector::StreamSamplingThread(void* pCollector)
{
    int samplesCollected = 0;
    const int buffer_size = 4096*64;
    const int buffers_count = 32; // must be power of 2
    const int buffers_count_mask = buffers_count-1;
    int handles[buffers_count];
    memset(handles, 0, sizeof(int)*buffers_count);
    char *buffers = NULL;
    buffers = new char[buffers_count*buffer_size];
    if(buffers == 0)
    {
        printf("error allocating buffers\n");
        return 0;
    }
    memset(buffers, 0, buffers_count*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

    short tempInt = 0;
    int bi = 0; //buffer index

    fstream fout;
    bool wToFile = pthis->m_writeToFile;
    unsigned long fileSizeLimit = pthis->m_fileSizeLimit;
    unsigned long fileSize = 0;
    if(wToFile)
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);

    //USB FIFO reset
    unsigned char out[64];
    long length = 64;
	memset(out, 0x00, length);
	out[0] = 0x40;
	out[1] = 0x10;
	out[2] = 1;
	out[8] = 0x01;
	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

	length = 64;
	out[8] = 0x00;
	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

    for (int i=0; i<buffers_count; ++i)
		handles[i] = pthis->m_serPort->BeginDataReading(&buffers[i*buffer_size], buffer_size);

    length = 64;
	out[8] = 0x02;
	pthis->m_serPort->Port_write_direct(out, length);
	pthis->m_serPort->Port_read_direct(out, length);

    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;
    while(pthis->m_running)
    {
        if(pthis->m_serPort->WaitForReading(handles[bi], 1000) == false)
		{
			++m_bufferFailures;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]
		bytesToRead = buffer_size;
		if (pthis->m_serPort->FinishDataReading(&buffers[bi*buffer_size], bytesToRead, handles[bi]))
  		{
			++packetsReceived;
			totalBytesReceived += bytesToRead;
			if(wToFile && fileSize < fileSizeLimit)
            {
                fout.write((const char*)&buffers[bi*buffer_size], bytesToRead);
                fileSize += bytesToRead;
            }
			skip = false;
		}
		else
		{
			++m_bufferFailures;
			skip = true;
		}

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels[0].status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        short* buf;
        buf = (short*)&buffers[bi*buffer_size];
        int framestart = pthis->frameStart;
        for(int b=0; b<buffer_size/2 && !skip; ++b)
        {
            if(samplesCollected == 0)
            {
                //find frame start
                for(int fs=b; fs<buffer_size/2; ++fs)
                {
                    if( ((buf[b]&0x1000)>0) == framestart)
                        break;
                    ++b;
                }
            }
            tempInt = buf[b] & 0x0FFF;
            tempInt = tempInt << 4;
            samples->iqdata[samplesCollected] = tempInt >> 4;
            ++samplesCollected;
            if(samplesCollected >= samples->samplesCount)
            {
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
            }
        }

        // Re-submit this request to keep the queue full
        memset(&buffers[bi*buffer_size], 0, buffer_size);
        handles[bi] = pthis->m_serPort->BeginDataReading(&buffers[bi*buffer_size], buffer_size);
        bi = (bi+1) & buffers_count_mask;
    }

    // Wait for all the queued requests to be cancelled
    pthis->m_serPort->AbortReading();
	for(int j=0; j<buffers_count; j++)
	{
		bytesToRead = buffer_size;
		pthis->m_serPort->WaitForReading(handles[j], 1000);
		pthis->m_serPort->FinishDataReading(&buffers[j*buffer_size], bytesToRead, handles[j]);
	}
	fout.close();
	delete []buffers;
	delete samples;
    printf("FULLY STOPPED\n");
    return 0;
}

bool SamplesCollector::SetPacketSize(int samplesCount)
{
    if(!m_running)
    {
        m_samplesToPacket = samplesCount;
        return true;
    }
    else
        return false;
}

void SamplesCollector::SwitchSource(eBOARD_FFT_SOURCE device)
{
    m_selectedDevice = device;
}

/** @brief Enables writing of received data to file
    @param writeToFile enable writing to file
    @param filename Destination filename
    @param sizeLimit_B file size limit in bytes
*/
void SamplesCollector::SetWriteToFile(bool writeToFile, const char* filename, unsigned long sizeLimit_B)
{
    m_writeToFile = writeToFile;
    m_filename = filename;
    m_fileSizeLimit = sizeLimit_B; //100 MB
}

#ifdef __unix__
void* SamplesCollector::NovenaSamplingThread(void *pCollector)
{
    printf("Novena sampling\n");
    fpga_init();

    int samplesCollected = 0;
    int buffer_size = 16384*2;

    unsigned short* buffer = new unsigned short[buffer_size];
    if(buffer == 0)
    {
        printf("error allocating buffer\n");
        return 0;
    }
    memset(buffer, 0, sizeof(unsigned short)*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);

    fstream fout;
    bool wToFile = pthis->m_writeToFile;
    unsigned long fileSizeLimit = pthis->m_fileSizeLimit;
    unsigned long fileSize = 0;
    if(wToFile)
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

    short tempInt = 0;
    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;

    GenericPacket pkt;
    pkt.cmd = CMD_LMS6002_WR;
	pkt.outBuffer[0] = 0xBC; //address
	pkt.outBuffer[1] = 0x40 | (pthis->m_dataSource & 0x03) << 4;
	pkt.outBuffer[2] = 0xBC; //address
	pkt.outBuffer[3] = 0x00 | (pthis->m_dataSource & 0x03) << 4;
	pkt.outLen = 4;
    pthis->m_serPort->TransferPacket(pkt);

    while(pthis->m_running)
    {
		bytesToRead = 4096;
		milSleep(10);
		for(int bb=0; bb<32768; bb+=2048)
		{
            fpga_read(0xC000000, (unsigned short*)&buffer[bb], bytesToRead);
            totalBytesReceived += bytesToRead;
            //printf("fpga read %i words\n", bytesToRead/2);
		}

        pkt.outBuffer[0] = 0xBC; //address
        pkt.outBuffer[1] = 0x40 | (pthis->m_dataSource & 0x03) << 4;
        pkt.outBuffer[2] = 0xBC; //address
        pkt.outBuffer[3] = 0x00 | (pthis->m_dataSource & 0x03) << 4;
        pthis->m_serPort->TransferPacket(pkt);

        ++packetsReceived;

        skip = false;
        if(wToFile && fileSize < fileSizeLimit)
        {
            fout.write((const char*)buffer, bytesToRead);
            fileSize += bytesToRead;
        }

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels[0].status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        short* buf;
        buf = (short*)buffer;
        int framestart = pthis->frameStart;
        for(int b=0; b<buffer_size && !skip; ++b)
        {
            if(samplesCollected == 0)
            {
                //find frame start
                for(int fs=b+8; fs<buffer_size; ++fs)
                {
                    if( ((buf[fs]&0x1000)>0) == framestart)
                        break;
                    ++b;
                }
            }
            tempInt = buf[b] & 0x0FFF;
            tempInt = tempInt << 4;
            samples->iqdata[samplesCollected] = tempInt >> 4;
            ++samplesCollected;
            if(samplesCollected >= samples->samplesCount)
            {
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
                break;
            }
        }
        if(samplesCollected < samples->samplesCount && samplesCollected != 0)
        {
            for(; samplesCollected<samples->samplesCount; ++samplesCollected)
                samples->iqdata[samplesCollected] = 0;
            if(samplesCollected >= samples->samplesCount)
            {
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
            }
        }
        samplesCollected = 0;
        memset(buffer, 0, buffer_size*sizeof(unsigned short));
    }

    bytesToRead = 4096;
    for(int bb=0; bb<32768; bb+=2048)
    {
        fpga_read(0xC000000, (unsigned short*)&buffer[bb], bytesToRead);
        totalBytesReceived += bytesToRead;
        //printf("fpga read %i words\n", bytesToRead/2);
    }

	delete buffer;
	delete samples;

	fout.close();
    printf("FULLY STOPPED\n");
    return 0;
}
#endif
