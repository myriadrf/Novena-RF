#ifndef UARFCN_H
#define UARFCN_H

#define BandN 14
class iniParser;
#include <string>

struct sUARFCNDef
{
	double dFul_low[BandN];
	double dFul_high[BandN];
	double dFul_offset[BandN];
};

class CUARFCN
{
public:
	CUARFCN();
	~CUARFCN(){};

	void SaveConf(iniParser *pini);
	void ReadConf(iniParser *pini);

	sUARFCNDef m_sRxUARFCNDef; // Uplink
	sUARFCNDef m_sTxUARFCNDef; // Downlink
	bool m_bBandEnable[BandN];
	std::string m_sBands[BandN];

	double CalculateFrequency(bool ULRX, int band, int channel);
};

#endif // UARFCN_H

