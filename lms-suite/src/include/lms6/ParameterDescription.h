/**
@file   ParameterDescription.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for defining control parameters
*/

#ifndef LMS6_Parameter_description_H
#define LMS6_Parameter_description_H

#include <string>
#include <string.h>

using namespace std;
namespace lms6
{

struct RegPiece
{
	unsigned int addr;
	unsigned int msb;
	unsigned int lsb;
};

class Parameter
{
	public:
	Parameter()
	{
	    registers = NULL;
	    name = "Unnamed";
	    bitsCount = 0;
	    piecesCount = 0;
	    defaultValue = 0;
	    registers = NULL;
	}
	Parameter(unsigned msb, unsigned lsb, unsigned long addr, unsigned long defVal, const char* nameID)
	{
	    name = nameID;
	    bitsCount = msb-lsb+1;
	    piecesCount = 1;
	    registers = new RegPiece[1];
        registers[0].addr = addr;
        registers[0].msb = msb;
        registers[0].lsb = lsb;
        defaultValue = defVal;
	}
	Parameter(const RegPiece *MSBtoLSB, unsigned pCount, unsigned long defVal, const char* nameID)
	{
	    defaultValue = defVal;
	    registers = NULL;
	    name = nameID;
	    bitsCount = 0;
	    piecesCount = pCount;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            for(int i=0; i<piecesCount; ++i)
            {
                registers[i] = MSBtoLSB[piecesCount-1-i];
                bitsCount += MSBtoLSB[piecesCount-1-i].msb-MSBtoLSB[piecesCount-1-i].lsb+1;
            }
            //memcpy(registers, pieces, piecesCount*sizeof(RegPiece));
        }
	}
	Parameter(const Parameter &p2)
	{
	    defaultValue = p2.defaultValue;
	    registers = NULL;
	    name = p2.name;
	    bitsCount = p2.bitsCount;
	    piecesCount = p2.piecesCount;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            //memcpy(registers, p2.registers, p2.piecesCount*sizeof(RegPiece));
            for(int i=0; i<piecesCount; ++i)
                registers[i] = p2.registers[i];
        }
	}

	Parameter &operator=(const Parameter &p2)
	{
	    defaultValue = p2.defaultValue;
	    registers = NULL;
	    name = p2.name;
	    bitsCount = p2.bitsCount;
	    piecesCount = p2.piecesCount;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            //memcpy(registers, p2.registers, p2.piecesCount*sizeof(RegPiece));
            for(int i=0; i<piecesCount; ++i)
                registers[i] = p2.registers[i];
        }
        return *this;
	}

	~Parameter()
	{
	    if(registers)
            delete []registers;
	}

    string name;
	unsigned char bitsCount;
	unsigned char piecesCount;
	unsigned long defaultValue;
	RegPiece *registers; //first index lsb, further msb
};

}
#endif // LMS_Parameter_description_H

