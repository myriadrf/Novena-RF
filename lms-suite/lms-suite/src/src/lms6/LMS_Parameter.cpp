#include "LMS_Parameter.h"

namespace lms6
{

/** @brief Converts module name to enumeration
    @param str LMS6002 module name in capital letters
    @return module enumeration
*/
LMS_MODULE string2LMSModule(const char *str)
{
    if( strcmp(str, "TOP") == 0)
        return TOP;
    else if( strcmp(str, "TXPLL") == 0)
        return TXPLL;
    else if( strcmp(str, "RXPLL") == 0)
        return RXPLL;
    else if( strcmp(str, "TXLPF") == 0)
        return TXLPF;
    else if( strcmp(str, "TXRF") == 0)
        return TXRF;
    else if( strcmp(str, "RXLPF") == 0)
        return RXLPF;
    else if( strcmp(str, "RXVGA2") == 0)
        return RXVGA2;
    else if( strcmp(str, "RXFE") == 0)
        return RXFE;
    else if( strcmp(str, "ADDC") == 0)
        return ADDC;
    else
        return UNDEFINED_MODULE;
}

/** @brief Converts LMS6002 module enumeration to module address
    @param module LMS6002 module enumeration
    @return module address
*/
int getModuleAddress(LMS_MODULE module)
{
    switch(module)
    {
        case TOP: return 0;
        case TXPLL: return 0x10;
        case RXPLL: return 0x20;
        case TXLPF: return 0x30;
        case RXLPF: return 0x50;
        case TXRF: return 0x40;
        case RXVGA2: return 0x60;
        case RXFE: return 0x70;
        case ADDC: return 0x50;
        default: return -1;
    }
}

}
