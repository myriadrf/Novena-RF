/**
@file   LMS6002_MainControl.h
@author Lime Microsystems (www.limemicro.com)
@brief  Main class for controlling LMS6002 chip
*/
#ifndef LMS6002_MAIN_CONTROL_H
#define LMS6002_MAIN_CONTROL_H

#include <string>
#include <map>
#include "LMS_Parameter.h"
#include "SignalHandler.h"
#include "LMS_Commands.h"
#include "PLL.h"
#include "RegistersMap.h"

namespace lms6
{
class Algorithms;

std::string LMS_GetLibVersion();
int indexToSELVCO_FRANGE(int i);
int SELVCO_FRANGE_ToIndex(int value);

/** @class LMS6002_MainControl
    @brief Main class for controlling LMS6002 chip
*/
class LMS6002_MainControl : public SignalHandler
{
    public:
        LMS6002_MainControl(ConnectionManager *serPort);
        ~LMS6002_MainControl();

        void HandleMessage(const LMS_Message &msg);

        void NewProject();
        bool LoadFromFile(const char *filename);
        bool SaveToFile(const char *filename, bool binary);

        void FindDevices();
        int ResetChip(int action = LMS_RST_PULSE);

        bool UploadAll();
        bool DownloadAll();

        bool SetParam(LMS_Parameter param, long value);
        long GetParam(LMS_Parameter param, const bool fromChip = false, const bool updateLocal = false) const;

        bool SetReferenceFrequency(const double freq_MHz, const bool Rx);
        double GetReferenceFrequency(const bool Rx) const;

        void SetAutoDownload(const bool enabled);
        bool GetAutoDownload() const;
        void SetAutoUpload(const bool enabled);
        bool GetAutoUpload() const;

        int SetFrequency(bool Rx, const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco, int &Divider);
        double GetFrequency(const bool Rx) const;
        void CalcIntPllData(const bool Rx, double &fVCO_MHz, int &divider);

        int Tune(bool Rx);

        void EnableSPIClocksByMask(unsigned int mask);
        void RestoreAllSPIClocks();

        void LoadAdditionalSettings();
        int RegistersTest();

        void SetGPIO(unsigned int msb, unsigned int lsb, int value);

        RegistersMap *getRegistersMap() const;
        ConnectionManager *getSerPort() const;
        Algorithms *algorithms;

        std::map<std::string, std::string> m_textVariables;
        PLL m_RxPLL;
        PLL m_TxPLL;
    protected:
        void Initialize();

        ConnectionManager *m_device;
        RegistersMap *m_registersMap;

        double m_FreqTx_MHz;
        double m_FreqRx_MHz;

        unsigned int m_SPIclocksBackup;
        unsigned char m_GPIO;
    private:

};

}
#endif // LMS6002_MAIN_CONTROL_H

