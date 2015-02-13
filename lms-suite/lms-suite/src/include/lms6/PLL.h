/**
@file   PLL.h
@author Lime Microsystems (www.limemicro.com)
*/

#ifndef LMS6_PLL_SX_H
#define LMS6_PLL_SX_H

#include <vector>
namespace lms6
{
/// Frequency and capacitance corelation
struct sVcoVsCap
{
    ///Number of reference points
	int iRef;
	/// frequency in MHz
	double *dFreq;
	/// capacitance
	double *iCap;
};

class PLL
{
private:
    double m_dRefF;   //Reference frequency, MHz
    sVcoVsCap sVco[4];

protected:

public:
    PLL();
    ~PLL();

    const sVcoVsCap* getVcoCap(int id);
    void setVcoCap(int id, sVcoVsCap* src);

    int AutoSelectVcoCap(double Freq, int iVcoInd);

    int CalcIntPllData(int Bcode, int Acode, double &FVCO_MHz, unsigned &DividerN);
    int FreqParams(double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco_MHz, int &Divider);
    void SetReferenceFrequency(double freq_MHz);
    double GetReferenceFrequency() const;

    bool SaveToFile(const char* filename);
    bool LoadFromFile(const char* filename);

    int QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco);
};
}
#endif // PLL_SX_H
