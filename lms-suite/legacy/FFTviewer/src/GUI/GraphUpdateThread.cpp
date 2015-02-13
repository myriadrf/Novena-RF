// -----------------------------------------------------------------------------
// FILE: 		GraphUpdateThread.cpp
// DESCRIPTION: thread used for reading  and displaying data results from library
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------
#include "GraphUpdateThread.h"
#include "ctr_6002dr2_LogicDLL.h"
#include "pnlSpectrum.h"

#ifdef WIN32
#else
#include "TimeCounter.h"
#endif // WIN32
#include "GUIUtils.h"

/**
    Sets up buffers for FFT results calculating and drawing
    @param frm pointer to Spectrum panel
*/
GraphUpdateThread::GraphUpdateThread(pnlSpectrum *frm)
{
	m_spectrum = frm;
	work = false;
	terminated = true;

    //buffer count for averaging FFT results
	m_buffersCount = 4;  // must be power of 2
	m_buffersCountMask = m_buffersCount - 1;

	//allocates memory for FFT results averaging
	m_FFTamplitudesBuffer = new float*[m_buffersCount+1];
	for(int i=0; i<m_buffersCount+1; i++)
		m_FFTamplitudesBuffer[i] = new float[m_spectrum->m_FFTsamplesCount];
	bufferPos = 0;
}

GraphUpdateThread::~GraphUpdateThread()
{
    if(m_FFTamplitudesBuffer)
    {
        for(int i=0; i<m_buffersCount+1; i++)
            delete []m_FFTamplitudesBuffer[i];
        delete []m_FFTamplitudesBuffer;
        m_FFTamplitudesBuffer = NULL;
    }
}

/**
    Performs FFT calculation and updates graphs
*/
void GraphUpdateThread::Execute()
{
    terminated = false;
	int fps = 60; //max number of graph updates per second
	int currentFps = 60;  // currently achieved fps
	long waitTime = 1000/fps; // time to wait between updates

	unsigned int frames=0;
	long t1, t2;
	long t1fps, t2fps;

	int fftsLeft = 0; // FFT results left in queue

	t1 = t1fps = GetTickCount();

	bool averageFFT = m_spectrum->chkAverage->GetValue();
	bool calculated = false;

	if(averageFFT != true)
	{
		while( work )
		{
			if(m_spectrum->chkUpdateGraphs->GetValue() == true)
			{
                //calculate FFT
                calculated = LMLL_Testing_CalculateFFT();

                //if FFT has been calculated
                if(calculated)
                {
                    //not averaging, take only one result
                    LMLL_Testing_GetFFTData(m_spectrum->m_IchannelData,
                                              m_spectrum->m_QchannelData,
                                              m_spectrum->m_IQdataSize,
                                              m_spectrum->m_FFTamplitudes,
                                              m_spectrum->m_FFTdataSize,
                                              fftsLeft);

                    //convert FFT results to dB
                    for(int i=0; i<m_spectrum->m_FFTdataSize; i++)
                    {
                        if( m_spectrum->m_FFTamplitudes[i] <= 0)
                        {
                            m_spectrum->m_FFTamplitudes[i] = -370;
                        }
                        else
                            m_spectrum->m_FFTamplitudes[i] = 10 * log10( m_spectrum->m_FFTamplitudes[i] );
                    }
                }
			}
			t2 = GetTickCount();
			if(t2 - t1 < waitTime) //framerate limiter
            {
                milSleep(waitTime-(t2-t1));
            }
            t1 = t2;
			m_spectrum->UpdateGraphs(); //update IQ line, IQ scatter and FFT graphs
			++frames;
			t2fps = GetTickCount();
			//show update rate, frames per second
			//wait until next update
			if( t2fps - t1fps > 1000)
			{
			    currentFps = 1000.0*frames/(t2fps-t1fps);
                m_spectrum->lblFPS->SetLabel( wxString::Format("%i", currentFps));
                frames = 0;
				t1fps = GetTickCount();
			}
		}
	}
	else
	{
		while( work )
		{
			if(m_spectrum->chkUpdateGraphs->GetValue() == true)
			{
				calculated = LMLL_Testing_CalculateFFT();
				if(calculated)
                {
                    //takes one FFT results and add it to averaging buffer
					LMLL_Testing_GetFFTData(m_spectrum->m_IchannelData, m_spectrum->m_QchannelData, m_spectrum->m_IQdataSize, m_FFTamplitudesBuffer[bufferPos], m_spectrum->m_FFTdataSize, fftsLeft);
					bufferPos = (bufferPos + 1) & m_buffersCountMask;

                    memset(m_FFTamplitudesBuffer[m_buffersCount], 0, sizeof(float)*m_spectrum->m_FFTsamplesCount);
                    //calculate average
                    for(int i=0; i<m_buffersCount; ++i)
                    {
                        for(int j=0; j<m_spectrum->m_FFTsamplesCount; ++j)
                            m_FFTamplitudesBuffer[m_buffersCount][j] += m_FFTamplitudesBuffer[bufferPos][j];
                        bufferPos = (bufferPos + 1) & m_buffersCountMask;
                    }
                    for(int j=0; j<m_spectrum->m_FFTsamplesCount; ++j)
                        m_FFTamplitudesBuffer[m_buffersCount][j] = m_FFTamplitudesBuffer[m_buffersCount][j]/m_buffersCount;

                    //convert to dB
                    for(int i=0; i<m_spectrum->m_FFTdataSize; i++)
                    {
                        if( m_FFTamplitudesBuffer[m_buffersCount][i] <= 0)
                        {
                            m_spectrum->m_FFTamplitudes[i] = -370;
                        }
                        else
                            m_spectrum->m_FFTamplitudes[i] = 10 * log10( m_FFTamplitudesBuffer[m_buffersCount][i] );
                    }
                }
			}
			//update graphs
			t2 = GetTickCount();
			if(t2 - t1 < waitTime) //framerate limiter
            {
                milSleep(waitTime-(t2-t1));
            }
            t1 = t2;
			m_spectrum->UpdateGraphs();
			++frames;
			t2fps = GetTickCount();
			if( t2fps - t1fps > 1000)
			{
			    currentFps = 1000.0*frames/(t2fps-t1fps);
                m_spectrum->lblFPS->SetLabel( wxString::Format("%i", currentFps));
                frames = 0;
				t1fps = GetTickCount();
			}
		}
	}
	LMLL_Testing_StopSdramRead();
	terminated = true;
}
/**
	@brief Signals to stop thread
*/
bool GraphUpdateThread::Stop()
{
    if(!terminated)
    {
        void *status;
        work = false;

        milSleep(100);
        return terminated; //!pthread_join(threadID, &status);
    }
    return terminated;
}

void* GraphUpdateThread::ThreadEntry(void *ptrThread)
{
    GraphUpdateThread *thread = reinterpret_cast<GraphUpdateThread*>(ptrThread);
    if( thread )
        thread->Execute();
    return NULL;
}

/**
    Starts thread for FFT calculation and graphs update
*/
bool GraphUpdateThread::Start()
{
    if(!work && terminated)
    {
        LMLL_Testing_StartSdramRead();
        milSleep(100); //wait for some samples to accumulate than start calculations thread
        if( pthread_create(&threadID, NULL, ThreadEntry, this) == 0)
        {
            work = true;
            cout << "STARTED SDRAM READ" << endl;
            return true;
        }
        else
        {
            LMLL_Testing_StopSdramRead();
            work = false;
            cout << "ERROR STARTING SDRAM READ" << endl;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
