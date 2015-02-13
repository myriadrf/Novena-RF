// -----------------------------------------------------------------------------
// FILE: 		GraphUpdateThread.h
// DESCRIPTION: Header for GraphUpdateThread.h
// DATE:		2013-05-06
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef GraphUpdateThreadH
#define GraphUpdateThreadH
//---------------------------------------------------------------------------

#include <pthread.h>

class pnlSpectrum;

class GraphUpdateThread
{
private:
	pnlSpectrum *m_spectrum;
	bool work;
	bool terminated;

	float **m_FFTamplitudesBuffer;
	int m_buffersCount;
	int m_buffersCountMask;
	int bufferPos;
    pthread_t threadID;
protected:
    static void *ThreadEntry(void *ptrThread);
	void Execute();
public:
    bool Start();
	bool Stop();
	GraphUpdateThread(pnlSpectrum *frm);
	~GraphUpdateThread();
};
//---------------------------------------------------------------------------
#endif
