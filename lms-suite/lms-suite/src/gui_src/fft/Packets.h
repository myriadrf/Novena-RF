#ifndef PACKETS_h
#define PACKETS_h

#include <string.h>

/**
    Packet used for transferring data from stream to fft calculation
*/
struct SamplesPacket
{
public:
    SamplesPacket() : samplesCount(32768), channel(0)
	{
	    iqdata = new float[samplesCount];
	}
	SamplesPacket(unsigned int packetSize) : samplesCount(packetSize), channel(0)
	{
	    iqdata = new float[packetSize];
	}
	~SamplesPacket()
	{
	    delete []iqdata;
	}

	SamplesPacket& operator=(SamplesPacket& obj)
	{
	    unsigned int cpSize = 0;
	    if(samplesCount < obj.samplesCount)
            cpSize = samplesCount;
        else
            cpSize = obj.samplesCount;
		memcpy(this->iqdata, obj.iqdata, cpSize*sizeof(float));
		this->channel = obj.channel;
		return *this;
	}

	const int samplesCount;
	float *iqdata;
	int channel;
};

/**
    Packet used for transferring FFT calculation results to graphs
*/
struct FFTPacket
{
public:
    FFTPacket() : samplesCount(32768), channel(0)
	{
	    iqsamples = new float[samplesCount];
	    amplitudesCount = samplesCount/2;
	    amplitudes = new float[amplitudesCount];
	}
	FFTPacket(unsigned int packetSize) : samplesCount(packetSize), channel(0)
	{
	    iqsamples = new float[samplesCount];
	    amplitudesCount = samplesCount/2;
	    amplitudes = new float[amplitudesCount];
	}

	~FFTPacket()
	{
        delete iqsamples;
        delete amplitudes;
	}

	FFTPacket& operator=(FFTPacket& obj)
	{
	    unsigned int cpSize = 0;
	    if(samplesCount < obj.samplesCount)
            cpSize = samplesCount;
        else
            cpSize = obj.samplesCount;
		memcpy(this->iqsamples, obj.iqsamples, sizeof(float)*cpSize);
		memcpy(this->amplitudes, obj.amplitudes, sizeof(float)*amplitudesCount);
		this->channel = obj.channel;
		return *this;
	}
	const int samplesCount;
	unsigned int amplitudesCount;
	float *iqsamples;
	float *amplitudes;
	int channel;
};

#endif // PACKETS_h
