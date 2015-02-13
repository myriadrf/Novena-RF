/**
@file   PLL.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  PLL configuration
*/

#include "PLL.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
using namespace std;
namespace lms6
{

/** @brief Class constructor.
    Initialization of VCO frequencies, Min, Max
    PLL frequencies, threshold frequency is done here.
*/
PLL::PLL()
{
    sVco[0].iRef = 0;
	sVco[0].dFreq = NULL;
	sVco[0].iCap = NULL;
	sVco[1].iRef = 0;
	sVco[1].dFreq = NULL;
	sVco[1].iCap = NULL;
	sVco[2].iRef = 0;
	sVco[2].dFreq = NULL;
	sVco[2].iCap = NULL;
	sVco[3].iRef = 0;
	sVco[3].dFreq = NULL;
	sVco[3].iCap = NULL;

	sVco[0].iRef = 3;
	sVco[0].dFreq = new double[sVco[0].iRef];
	sVco[0].iCap = new double[sVco[0].iRef];
	sVco[0].dFreq[0] = 3760;
	sVco[0].dFreq[1] = 4200;
	sVco[0].dFreq[2] = 4840;
	sVco[0].iCap[0] = 0;
	sVco[0].iCap[1] = 31;
	sVco[0].iCap[2] = 63;

	sVco[1].iRef = 3;
	sVco[1].dFreq = new double[sVco[1].iRef];
	sVco[1].iCap = new double[sVco[1].iRef];
	sVco[1].dFreq[0] = 4680;
	sVco[1].dFreq[1] = 5320;
	sVco[1].dFreq[2] = 6040;
	sVco[1].iCap[0] = 0;
	sVco[1].iCap[1] = 31;
	sVco[1].iCap[2] = 63;

	sVco[2].iRef = 3;
	sVco[2].dFreq = new double[sVco[2].iRef];
	sVco[2].iCap = new double[sVco[2].iRef];
	sVco[2].dFreq[0] = 5720;
	sVco[2].dFreq[1] = 6440;
	sVco[2].dFreq[2] = 7360;
	sVco[2].iCap[0] = 0;
	sVco[2].iCap[1] = 31;
	sVco[2].iCap[2] = 63;

	sVco[3].iRef = 3;
	sVco[3].dFreq = new double[sVco[3].iRef];
	sVco[3].iCap = new double[sVco[3].iRef];
	sVco[3].dFreq[0] = 6920;
	sVco[3].dFreq[1] = 7360;
	sVco[3].dFreq[2] = 8398;
	sVco[3].iCap[0] = 0;
	sVco[3].iCap[1] = 31;
	sVco[3].iCap[2] = 63;

    m_dRefF = 30.720;    //Reference frequency MHz
}

PLL::~PLL()
{

}

/** @brief Calculates parameters for desired frequency
    @param desFreq_MHz desired frequency in MHz
    @param realFreq_MHz calculated frequency in MHz
    @param iVCO VCO index
    @param Fvco_MHz VCO frequency in MHz
    @param Divider VCO frequency divider
  @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range. Set to closest available frequency
*/
int PLL::FreqParams(double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco_MHz, int &Divider)
{
    bool canDeliverFrequency = false;
    bool frequencyWithinRange = true;
    Divider = 0;

    double dMul = 1;
	double dFvco;
	double dN;
	double dTmp;
	int iNint;
	int iNfrac;

	// VCO 4-5GHz
	if ((desFreq_MHz >= (sVco[0].dFreq[0] / 2.0)) && (desFreq_MHz <
		(sVco[0].dFreq[sVco[0].iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		Divider = 1;
		iVCO = 1;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[0].dFreq[0] / 4.0)) && (desFreq_MHz <
		(sVco[0].dFreq[sVco[0].iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		Divider = 2;
		iVCO = 1;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[0].dFreq[0] / 8.0)) && (desFreq_MHz <
		(sVco[0].dFreq[sVco[0].iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		Divider = 3;
		iVCO = 1;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[0].dFreq[0] / 16.0)) && (desFreq_MHz <
		(sVco[0].dFreq[sVco[0].iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		Divider = 4;
		iVCO = 1;
		canDeliverFrequency = true;
	}

	// VCO 5-6GHz
	else if ((desFreq_MHz >= (sVco[1].dFreq[0] / 2.0)) && (desFreq_MHz <
		(sVco[1].dFreq[sVco[1].iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		Divider = 1;
		iVCO = 2;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[1].dFreq[0] / 4.0)) && (desFreq_MHz <
		(sVco[1].dFreq[sVco[1].iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		Divider = 2;
		iVCO = 2;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[1].dFreq[0] / 8.0)) && (desFreq_MHz <
		(sVco[1].dFreq[sVco[1].iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		Divider = 3;
		iVCO = 2;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[1].dFreq[0] / 16.0)) && (desFreq_MHz <
		(sVco[1].dFreq[sVco[1].iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		Divider = 4;
		iVCO = 2;
		canDeliverFrequency = true;
	}

	// VCO 6-7-GHz
	else if ((desFreq_MHz >= (sVco[2].dFreq[0] / 2.0)) && (desFreq_MHz <
		(sVco[2].dFreq[sVco[2].iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		Divider = 1;
		iVCO = 3;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[2].dFreq[0] / 4.0)) && (desFreq_MHz <
		(sVco[2].dFreq[sVco[2].iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		Divider = 2;
		iVCO = 3;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[2].dFreq[0] / 8.0)) && (desFreq_MHz <
		(sVco[2].dFreq[sVco[2].iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		Divider = 3;
		iVCO = 3;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[2].dFreq[0] / 16.0)) && (desFreq_MHz <
		(sVco[2].dFreq[sVco[2].iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		Divider = 4;
		iVCO = 3;
		canDeliverFrequency = true;
	}

	// VCO 7-8-GHz
	// else if((desFreq_MHz >= (sVco[3].dFreq[0]/2.0)) && (desFreq_MHz < (sVco[3].dFreq[sVco[3].iRef-1]/2))) { dMul = (double) 2.0 / 1.0; Divider = 1; iVCO = 4; }
	else if ((desFreq_MHz >= (sVco[3].dFreq[0] / 2.0)) && (desFreq_MHz <=
		(sVco[3].dFreq[sVco[3].iRef - 1] / 2)))
	{
		dMul = (double)2.0 / 1.0;
		Divider = 1;
		iVCO = 4;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[3].dFreq[0] / 4.0)) && (desFreq_MHz <
		(sVco[3].dFreq[sVco[3].iRef - 1] / 4)))
	{
		dMul = (double)4.0 / 1.0;
		Divider = 2;
		iVCO = 4;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[3].dFreq[0] / 8.0)) && (desFreq_MHz <
		(sVco[3].dFreq[sVco[3].iRef - 1] / 8)))
	{
		dMul = (double)8.0 / 1.0;
		Divider = 3;
		iVCO = 4;
		canDeliverFrequency = true;
	}
	else if ((desFreq_MHz >= (sVco[3].dFreq[0] / 16.0)) && (desFreq_MHz <
		(sVco[3].dFreq[sVco[3].iRef - 1] / 16)))
	{
		dMul = (double)16.0 / 1.0;
		Divider = 4;
		iVCO = 4;
		canDeliverFrequency = true;
	}

	if(!canDeliverFrequency)
	{
	    //MessageLog::getInstance()->write("Cannot deliver requested frequency\n", LOG_ERROR);
        return -1;
	}

	dFvco = dMul * desFreq_MHz;
	Fvco_MHz = dFvco;
	dN =  1 / m_dRefF;
	dN *= dFvco;

	// Because 203 = double 202.9999999999... and double casting to int gives 202, not 203!!!
	if ((int)dN < (int)(dN + 1 / pow(2.0, 23)))
		dN += 1 / pow(2.0, 23);

	iNint = (int)dN;
	iNfrac = (double)(dN - iNint) * pow(2.0, 23);
	Nint = iNint;
	Nfrac = iNfrac;

	dTmp = (double)iNfrac / (double)pow(2.0, 23);
	double dTempMul = (double)(dTmp + (double)iNint);
	realFreq_MHz = (m_dRefF ) * (1.0 / dMul) * dTempMul;

    if(frequencyWithinRange)
        return 0;
    else
        return 1;
}

/** @brief Sets reference frequency
    @param freq_MHz reference frequency in MHz
*/
void PLL::SetReferenceFrequency(const double freq_MHz)
{
    m_dRefF = freq_MHz;
}

/** @brief Returns reference frequency in MHz
*/
double PLL::GetReferenceFrequency() const
{
    return m_dRefF;
}

int PLL::AutoSelectVcoCap(double Freq, int iVcoInd)
{
	int iCInd = 0;
	switch (iVcoInd)
	{
	case 1:
		iCInd = QuadraticInterpol(sVco[0].iRef, sVco[0].dFreq, sVco[0].iCap, Freq);
		break;
	case 2:
		iCInd = QuadraticInterpol(sVco[1].iRef, sVco[1].dFreq, sVco[1].iCap, Freq);
		break;
	case 3:
		iCInd = QuadraticInterpol(sVco[2].iRef, sVco[2].dFreq, sVco[2].iCap, Freq);
		break;
	case 4:
		iCInd = QuadraticInterpol(sVco[3].iRef, sVco[3].dFreq, sVco[3].iCap, Freq);
		break;
	default:
		iCInd = 0;
	};

	if (iCInd < 0)
		iCInd = 0;
	if (iCInd > 63)
		iCInd = 63;

	return iCInd;
}

int PLL::QuadraticInterpol(int iRefVCnt, double *dFVco, double *dCVco, double dRealFvco)
{

  double dGV = 0;
  double dNum;
  double dDenom;

  for(int i=0; i<iRefVCnt; i++) //Loop through each reference point
  {
    dNum = 1;
    dDenom = 1;
    for(int j=0; j<iRefVCnt; j++)
    {
      if(i != j)
      {
        dNum    *= (dRealFvco - dFVco[j])/1000;
        dDenom  *= (dFVco[i]  - dFVco[j])/1000;
      };
    };
    dGV += (double)dCVco[i] * dNum / dDenom;

  };

  return (int)(dGV + 0.5);
}

/** @brief Calculates values for Integer mode, returns VCO frequncy and divider
    @param Bcode B Code value
    @param Acode A Code value
    @param FVCO_MHz VCO frequency in MHz
    @param DividerN VCO frequency divider

*/
int PLL::CalcIntPllData(int Bcode, int Acode, double &FVCO_MHz, unsigned int &DividerN)
{
    DividerN = 8 * (Bcode + 7) + Acode + 34;
	FVCO_MHz = m_dRefF * DividerN;
    return 0;
}

/** @brief Returns selected VCO frequencies and capacitances
    @param id VCO index: 0,1,2,3
    @return pointer to VCO frequency capacitances structure, or NULL if bad id was selected
*/
const sVcoVsCap* PLL::getVcoCap(int id)
{
    if(id >= 0 && id < 4)
    {
        return &sVco[id];
    }
    else
    {
        return NULL;
    }
}

/** @brief Sets selected VCO frequencies and capacitances from given structure
    @param id VCO index: 0,1,2,3
    @param src pointer to VCO frequencies and capacitances structure
*/
void PLL::setVcoCap(int id, sVcoVsCap* src)
{
    if(id >= 0 && id < 4)
    {
        delete sVco[id].dFreq;
        delete sVco[id].iCap;
        sVco[id].iRef = src->iRef;
        sVco[id].dFreq = new double[sVco[id].iRef];
        sVco[id].iCap = new double[sVco[id].iRef];
        for(int i=0; i<sVco[id].iRef; ++i)
        {
            sVco[id].dFreq[i] = src->dFreq[i];
            sVco[id].iCap[i] = src->iCap[i];
        }
    }
}

/** @brief Loads VCOH VCOM VCOL values from file
    @param filename source file
    @return true on success
*/
bool PLL::LoadFromFile(const char* filename)
{
    std::fstream fin;
    fin.open(filename, ios::in);
    if(!fin.good())
    {
        fin.close();
        return false;
    }

    char cline[128];
    int lineLen = 128;

    char vconame[80];
    char ctemp[80];
    double freq = 0;
    double cap = 0;
    int freqCount = 0;

    sVcoVsCap vcocap;
    vcocap.dFreq = new double[100];
    vcocap.iCap = new double[100];
    vcocap.iRef = 0;

    const char* names[] = {"[VCO1]", "[VCO2]", "[VCO3]", "[VCO4]"};

    while(!fin.eof())
    {
        freqCount = 0;
        fin.getline(cline, lineLen);
        //find name and frequency count
        sscanf(cline, "%s %s %i", vconame, ctemp, &freqCount);
        for(int i=0; i<4; ++i)
        {
            if(strcmp(vconame, names[i]) == 0)
            {
                vcocap.iRef = freqCount;
                for(int j=0; j<freqCount; ++j)
                {
                    fin.getline(cline, lineLen);
                    sscanf(cline, "%lf %s %lf", &freq, ctemp, &cap);
                    vcocap.dFreq[j] = freq*1000; //GHz in file, MHz in variables
                    vcocap.iCap[j] = cap;
                }
                setVcoCap(i, &vcocap);
            }
        }
        vconame[0] = 0;
    }
    delete []vcocap.dFreq;
    delete []vcocap.iCap;
    fin.close();
    return true;
}

bool PLL::SaveToFile(const char* filename)
{
    fstream fout;
    fout.open(filename, ios::out);
    if(!fout.good())
    {
        fout.close();
        return false;
    }

    const sVcoVsCap* vcocap;
    for(int j=0; j<4; ++j)
    {
        vcocap = getVcoCap(j);
        fout << "[VCO" << j+1 << "] count: " << vcocap->iRef << "," << endl;
        for(int i=0; i<vcocap->iRef ; ++i)
            fout << vcocap->dFreq[i]/1000 << ' ' << "GHz, " << vcocap->iCap[i] << "," << endl;
    }
    fout.close();
    return true;
}

}
