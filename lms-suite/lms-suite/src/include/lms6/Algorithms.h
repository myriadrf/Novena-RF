/**
@file   Algorithms.h
@author Lime Microsystems (www.limemicro.com)
@brief  Function prototypes for calibrating and tuning operations
*/

#ifndef LMS_ALGORITHMS_H
#define LMS_ALGORITHMS_H

#include "LMS_Parameter.h"

namespace lms6
{

class LMS6002_MainControl;

/** @brief Stucture for saving PLL module settings while calibrating LPF CAL Core
*/
struct F320M_Data
{
    int F320M_rgrDecode;
    bool F320M_chbPwrPllMods;
    int F320M_rgrMODE;
    int F320M_cmbVCOCAP;
    int F320M_rgrSELVCO;
    int F320M_rgrFRANGE;
    double F320M_DesFreq_MHz;
};

/** @brief Procedures used for calibrating and tuning LMS6002 chip
*/
class Algorithms
{
public:
    Algorithms(LMS6002_MainControl *pControl);
    ~Algorithms();

    int CapAutoTune_S(const bool Rx);
    bool CapIncrement(const bool Rx, int untilState);
    bool CapDecrement(const bool Rx, int untilState);
    int GetVTuneState(const bool Rx);

    void DCResetCalibration(LMS_MODULE moduleAddress);
    void DCLoadValues(LMS_MODULE moduleAddress);
    void DCStartCalibration(LMS_MODULE moduleAddress);

    void CalibrateTx();
    void CalibrateRx();
    void CalibrateLPFCore();

private:
    F320M_Data m_F320M_Data;
    void SetPLLTo320MHz();
    void RestoreAfterSetPLLTo320MHz();
    LMS6002_MainControl *lmsControl;
};

}
#endif // LMS_ALGORITHMS_H

