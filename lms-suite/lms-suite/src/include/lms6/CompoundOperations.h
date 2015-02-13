#ifndef COMPOUND_OPERATIONS_H
#define COMPOUND_OPERATIONS_H
namespace lms6
{

class LMS6002_MainControl;

/** @brief Compound operations used by GUI for enabling modules
*/
class CompoundOperations
{
public:
    CompoundOperations(LMS6002_MainControl *pControl);
    ~CompoundOperations();

    void CustSet_BypassTxLpfOFF();
    void CustSet_BypassTxLpfON();

    void CustSet_BypassRxLpfOFF();
    void CustSet_BypassRxLpfON();

    void CustSet_RxVGA2PowerON();
    void CustSet_RxVGA2PowerOFF();

    void SetLnaChain(int iChain);

    void CustSet_SetBBLB(int i);

    void CustSet_LNAPowerON();
    void CustSet_LNAPowerOFF();

    void CustSet_RxLpfPowerON();
    void CustSet_RxLpfPowerOFF();

    void CustSet_RxFePowerOFF();
    void CustSet_RxFePowerON();

    void CustSet_ActiveLNA(int i);
    void CustSet_ActiveLOBuff(int i);
private:
    LMS6002_MainControl *lmsControl;
};

}
#endif // COMPOUND_OPERATIONS_H
