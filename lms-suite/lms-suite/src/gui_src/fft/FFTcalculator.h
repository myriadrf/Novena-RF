#ifndef FFT_CALCULATOR_H
#define FFT_CALCULATOR_H

#include "Packets.h"
#include "BlockingFIFO.h"
#include "fftw3.h"
#include "lmThread.h"

class FFTcalculator
{
public:
    FFTcalculator(BlockingFIFO<SamplesPacket> *InChannels, BlockingFIFO<FFTPacket> *OutChannels, int outputChannels);
    ~FFTcalculator();

    bool Start();
    void Stop();

    bool SetFFTsize(int size);
    bool SetSamplingFrequency(double freq);
    bool SetAveragingCount(unsigned count, bool enabled);
    bool SetDCcorrection(bool enabled);
    float GetFFTrate() {return m_fftRate;};
    void SetFFTrate(int ffts) { m_fftLimit = ffts;};

    int m_windowFunction;
    int m_newWindowFunction;
    void SetWindowFunction(int index);
    void EnableChannels(int hexFlags);
protected:
    void GenerateWindowCoefficients(int func, int fftsize);
    float *windowFcoefs;
    BlockingFIFO<SamplesPacket> *m_inChannels;
    BlockingFIFO<FFTPacket> *m_outChannels;
    int m_inputCount;
    int m_outputCount;

    static void* CalculationsThread(void* pFFTcalculator);

    int m_FFTsize;
    double m_samplingFreq;
    int m_avgCount;
    int m_new_avgCount;
    bool m_dccorr;

    bool m_running;
    unsigned long m_fftsCalculated;
    float m_fftRate;

    int m_fftLimit;

    lmThread m_thread;

    int m_channelsEnable;
};

#endif // FFT_CALCULATOR_H

