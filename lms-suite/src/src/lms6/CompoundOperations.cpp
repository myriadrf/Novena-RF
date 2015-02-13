#include "CompoundOperations.h"
#include "LMS6002_MainControl.h"

namespace lms6
{

CompoundOperations::CompoundOperations(LMS6002_MainControl *pControl)
{
    lmsControl = pControl;
}
CompoundOperations::~CompoundOperations()
{

}

void CompoundOperations::CustSet_BypassTxLpfOFF()
{
    lmsControl->SetParam(DECODE_TXLPF, 0);
    lmsControl->SetParam(EN_TXLPF, 1);
    lmsControl->SetParam(BYP_EN_LPF_TXLPF, 0);
}
void CompoundOperations::CustSet_BypassTxLpfON()
{
    lmsControl->SetParam(DECODE_TXLPF, 0);
    lmsControl->SetParam(EN_TXLPF, 0);
    lmsControl->SetParam(BYP_EN_LPF_TXLPF, 1);
}

void CompoundOperations::CustSet_BypassRxLpfOFF()
{
    lmsControl->SetParam(DECODE_RXLPF, 0);
    lmsControl->SetParam(EN_RXLPF, 1);
    lmsControl->SetParam(BYP_EN_LPF_RXLPF, 0);
}
void CompoundOperations::CustSet_BypassRxLpfON()
{
    lmsControl->SetParam(DECODE_RXLPF, 0);
    lmsControl->SetParam(EN_RXLPF, 0);
    lmsControl->SetParam(BYP_EN_LPF_RXLPF, 1);
}

void CompoundOperations::CustSet_RxVGA2PowerON()
{
    lmsControl->SetParam(EN_RXVGA2, 1);
    lmsControl->SetParam(DECODE_RXVGA2, 0);
}
void CompoundOperations::CustSet_RxVGA2PowerOFF()
{
    lmsControl->SetParam(EN_RXVGA2, 0);
    lmsControl->SetParam(DECODE_RXVGA2, 0);
}

void CompoundOperations::SetLnaChain(int iChain)
{
    switch(iChain)
    {
    case 0:
        lmsControl->SetParam(LNASEL_RXFE, 0);
        lmsControl->SetParam(SELOUT_RXPLL, 0);
    break;

    case 1:
        lmsControl->SetParam(LNASEL_RXFE, 1);
        lmsControl->SetParam(SELOUT_RXPLL, 1);
    break;

    case 2:
        lmsControl->SetParam(LNASEL_RXFE, 2);
        lmsControl->SetParam(SELOUT_RXPLL, 2);
    break;

    case 3:
        lmsControl->SetParam(LNASEL_RXFE, 3);
        lmsControl->SetParam(SELOUT_RXPLL, 3);
    break;
    default:
        break;
    };
}

void CompoundOperations::CustSet_SetBBLB(int i)
{
    lmsControl->SetParam(LBEN_LPFIN, i == 1);
    lmsControl->SetParam(LBEN_VGA2IN, i == 2);
    lmsControl->SetParam(LBEN_OPIN, i == 3);
}

void CompoundOperations::CustSet_LNAPowerON()
{
    lmsControl->SetParam(DECODE_RXFE, 0);
    lmsControl->SetParam(PD_LNA_RXFE, 0);
}

void CompoundOperations::CustSet_LNAPowerOFF()
{
    lmsControl->SetParam(DECODE_RXFE, 1);
    lmsControl->SetParam(PD_LNA_RXFE, 1);
}

void CompoundOperations::CustSet_RxFePowerON()
{
    lmsControl->SetParam(DECODE_RXFE, 0);
    lmsControl->SetParam(EN_RXFE, 1);
}

void CompoundOperations::CustSet_RxFePowerOFF()
{
    lmsControl->SetParam(DECODE_RXFE, 0);
    lmsControl->SetParam(EN_RXFE, 0);
}

void CompoundOperations::CustSet_RxLpfPowerON()
{
    lmsControl->SetParam(DECODE_RXLPF, 0);
    lmsControl->SetParam(EN_RXLPF, 1);
}
void CompoundOperations::CustSet_RxLpfPowerOFF()
{
    lmsControl->SetParam(DECODE_RXLPF, 0);
    lmsControl->SetParam(EN_RXLPF, 0);
}

}
