// -----------------------------------------------------------------------------
// FILE: 		    clUARFCN.h
// DESCRIPTION:	Header for clUARFCN.cpp
// DATE:
// AUTHOR(s):	  Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef clUARFCNH
#define clUARFCNH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#include <Buttons.hpp>

#define BandN 14
struct sUARFCNDef
{
  double dFul_low[BandN];
  double dFul_high[BandN];
  double dFul_offset[BandN];
};

struct sUARFCNf
{
  int a;
};

class CUARFCN
{
  private:
    sUARFCNDef m_sRxUARFCNDef;  //Uplink
    sUARFCNDef m_sTxUARFCNDef;  //Downlink
    bool m_bBandEnable[BandN];
    String m_sBands[BandN];

    int ChName2ChInd(String ChName);

    TComboBox *cmbULRXBands;
    TComboBox *cmbULRXChan;
    TEdit *txtULRXFreq;
    TSpeedButton *btnULRXFChan_B;
    TSpeedButton *btnULRXFChan_M;
    TSpeedButton *btnULRXFChan_T;


    TComboBox *cmbDLTXBands;
    TComboBox *cmbDLTXChan;
    TEdit *txtDLTXFreq;
    TSpeedButton *btnDLTXFChan_B;
    TSpeedButton *btnDLTXFChan_M;
    TSpeedButton *btnDLTXFChan_T;

  protected:

  public:
    CUARFCN();
    ~CUARFCN();

    void SaveConf(TIniFile *pini);
    void ReadConf(TIniFile *pini);

    void Initialize( TComboBox *ULRXBands, TComboBox *ULRXChan, TEdit *ULRXFreq,
                     TSpeedButton *ULRXFChan_B, TSpeedButton *ULRXFChan_M, TSpeedButton *ULRXFChan_T,
                     TComboBox *DLTXBands, TComboBox *DLTXChan, TEdit *DLTXFreq,
                     TSpeedButton *DLTXFChan_B, TSpeedButton *DLTXFChan_M, TSpeedButton *DLTXFChan_T
                     );
    void SetBands(bool ULRX);
    void SetChannels(bool ULRX);
    void SetFastChannels(bool ULRX);
    void SetFastChannelsAllUp(bool ULRX);
    double SetFrequency(bool ULRX);

};


#endif
