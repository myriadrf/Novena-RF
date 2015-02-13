/**
@file   CommonUtilities.h
@author Lime Microsystems (www.limemicro.com)
@brief  Prototypes for common utility functions used by logic and GUI
*/

#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

#include <string>

void milSleep(unsigned int miliseconds);
long getMilis();
std::string int2hex(int i, int sizeBytes = 1);
std::string uint2hex(unsigned int i, int sizeBytes = 1);
unsigned long makeMask(unsigned msb, unsigned lsb);

#endif // COMMON_UTILITIES_H

