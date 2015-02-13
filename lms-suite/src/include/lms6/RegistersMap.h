/**
@file   RegistersMap.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for LMS6002 registers configuring
*/

#ifndef LMS_REGISTERS_MAP_H
#define LMS_REGISTERS_MAP_H

#include "ConnectionManager.h"
#include "ParameterDescription.h"
#include "LMS_Parameter.h"
#include <map>
#include <vector>

namespace lms6
{
/// Value type to use for addesses and data
typedef unsigned char valType;

/** @brief Register information
*/
struct Register
{
    Register() : value(0), defaultValue(0), mask(0xff) {};
    valType value;
    valType defaultValue;
    valType mask;
};

class RegistersMap
{
public:
    bool CheckForOverlays();
    RegistersMap(ConnectionManager *pMng);
    ~RegistersMap();

    bool SaveToStream(std::ofstream &fout);
    bool LoadFromStream(std::ifstream &fin);

    bool SetParameterValue(const LMS_Parameter param, unsigned long value);
    unsigned long GetParameterValue(const LMS_Parameter param, bool fromChip = false, bool updateLocal = true);

    valType GetRegisterValue(const valType address, bool fromChip = false, bool updateLocal = true);
    bool SetRegisterValue(const valType address, const valType value);

	int DownloadAll();
	int UploadAll();

	void SetAutoDownload(bool download) {m_autoDownload = download; };
	bool GetAutoDownload() const {return m_autoDownload; };
	void SetAutoUpload(bool upload) { m_autoUpload = upload; };
	bool GetAutoUpload() const {return m_autoUpload; };

	void SetDefaultValues();
	void InitializeControlParameters();

	LMS_Parameter GetParamIDbyName(const char *name);
	int RegistersTest();
	void CancelRegisterTest();
	int RegisterTestBatch(const char *name, const unsigned short addr1, const unsigned short addr2, const unsigned short pattern, const bool onlyUsed);

    void printOut();
    const Parameter getParameterInfo(const LMS_Parameter param );

    std::map<valType, Register> m_registers;
    std::map<LMS_Parameter, Parameter> m_parameterList;

    /// when enabled each parameter change will be written immediately
	bool m_autoUpload;
	/// when enabled each parameter value will be read from chip
    bool m_autoDownload;
    /// stops registers testing
    bool m_cancelRegisterTest;
    ConnectionManager *m_serPort;

protected:
    bool Comparators(int Min, int Max);
private:
    RegistersMap(); //prevent creating without connection manager
};

/** @brief Address space definition for registers testing
*/
struct RegTestPlan
{
    RegTestPlan() : name("unnamed"), startAddr(0), endAddr(0), onlyUsedAddresses(true) {};
    RegTestPlan(const std::string sname, const unsigned short saddr, const unsigned short eaddr, const bool onlyUsed) :
        name(sname), startAddr(saddr), endAddr(eaddr), onlyUsedAddresses(onlyUsed) {};
    RegTestPlan(const RegTestPlan &reg)
    {
        name = reg.name;
        startAddr = reg.startAddr;
        endAddr = reg.endAddr;
        onlyUsedAddresses = reg.onlyUsedAddresses;
    };
    std::string name;
    unsigned short startAddr;
    unsigned short endAddr;
    bool onlyUsedAddresses;
};

}
#endif // LMS_REGISTERS_MAP_H

