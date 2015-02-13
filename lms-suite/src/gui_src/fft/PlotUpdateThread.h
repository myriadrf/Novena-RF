#ifndef PLOT_UPDATE_THREAD_H
#define PLOT_UPDATE_THREAD_H

#include "wx/thread.h"
#include "fftw3.h"
class pnlFFTviewer;

class PlotUpdateThread : public wxThread
{
public:
    PlotUpdateThread(pnlFFTviewer *mainFrame);
    ~PlotUpdateThread();
    virtual void* Entry();
    void Stop();
    bool SetFFTsize(int size);
    bool SetSamplingFrequency(double freq);
private:
    int m_FFTsize;
    double m_samplingFreq;
    pnlFFTviewer *m_mainframe;
    bool m_running;
};

#endif // PLOT_UPDATE_THREAD_H

