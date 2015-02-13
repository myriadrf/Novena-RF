#include "Protocols.h"
#include "ConnectionManager.h"
#include <stdio.h>
/** @brief Takes generic paket data and transforms into appopriate protocol
    @param pkt packet to be processed
    @param length returned buffer length
    @param protocol output protocol type
    @param pSerPort connection manager used to read unmanaged register values (eg. Novena board gpio controls)
    @return pointer to buffer, NULL on failure, buffer must be deleted manually after use
*/
unsigned char* PreparePacket(const GenericPacket &pkt, int &length, const eLMS_PROTOCOL protocol, ConnectionManager* pSerPort)
{
    unsigned char* buffer = NULL;
    bool m_system_big_endian = true;
    if(protocol == LMS_PROTOCOL_UNDEFINED)
        return 0;

    if(protocol == LMS_PROTOCOL_LMS64C)
    {
        ProtocolLMS64C packet;
        memset(packet.data, 0, packet.maxDataLength);
        memcpy(packet.data, pkt.outBuffer, packet.maxDataLength);
        packet.cmd = pkt.cmd;
        packet.status = pkt.status;
        int blockRatio = 1;
        switch( packet.cmd )
        {
        case CMD_SI5351_WR:
        case CMD_SI5356_WR:
            packet.blockCount = pkt.outLen/2; //data block pairs(address,value)
            blockRatio = 2;
            break;
        case CMD_ADF4002_WR:
            packet.blockCount = pkt.outLen/3; //data block(3xByte)
            blockRatio = 3;
            break;
        case CMD_LMS7002_WR:
            packet.blockCount = pkt.outLen/4; //data block pairs(address,value)
            blockRatio = 4;
            if(m_system_big_endian)
                for(int i=0; i<packet.maxDataLength; i+=2)
                {
                    int ctemp = packet.data[i];
                    packet.data[i] = packet.data[i+1];
                    packet.data[i+1] = ctemp;
                }
            break;
        case CMD_LMS7002_RD:
            blockRatio = 2;
            packet.blockCount = pkt.outLen/2; //data blocks(address)
            if(m_system_big_endian)
                for(int i=0; i<packet.maxDataLength; i+=2)
                {
                    int ctemp = packet.data[i];
                    packet.data[i] = packet.data[i+1];
                    packet.data[i+1] = ctemp;
                }
            break;
        case CMD_LMS6002_RST:
            packet.cmd = CMD_LMS7002_RST;
        case CMD_PROG_MCU:
        case CMD_LMS7002_RST:
        case CMD_GET_INFO:
        case CMD_LMS_LNA:
        case CMD_LMS_PA:
            packet.blockCount = 1;
            break;
        case CMD_LMS6002_WR:
        case CMD_MYRIAD_WR:
            blockRatio = 2;
            packet.blockCount = pkt.outLen/2;
            break;
        case CMD_LMS6002_RD:
        case CMD_MYRIAD_RD:
        case CMD_SI5351_RD:
        case CMD_SI5356_RD:
            packet.blockCount = pkt.outLen; //data blocks(address)
            blockRatio = 2;
            break;
        case CMD_PE636040_WR:
        case CMD_MYRIAD_GPIO_WR:
            packet.blockCount = pkt.outLen;
            blockRatio = 1;
            break;
        default:
            packet.blockCount = pkt.outLen;
        }
        int bufLen = ((pkt.outLen/(packet.maxDataLength/blockRatio))+(pkt.outLen%packet.maxDataLength!=0))*packet.pktLength;
        if(bufLen == 0)
            bufLen = packet.pktLength;
        buffer = new unsigned char[bufLen];
        memset(buffer, 0, bufLen);
        for(int j=0; j*packet.pktLength<bufLen; ++j)
        {
            int pktPos = j*packet.pktLength;
            buffer[pktPos] = packet.cmd;
            buffer[pktPos+1] = packet.status;
            if(packet.blockCount > (packet.maxDataLength/blockRatio))
            {
                buffer[pktPos+2] = packet.maxDataLength/blockRatio;
                packet.blockCount -= buffer[pktPos+2];
            }
            else
                buffer[pktPos+2] = packet.blockCount;
            memcpy(&buffer[pktPos+3], packet.reserved, sizeof(packet.reserved));
            memcpy(&buffer[pktPos+8], &pkt.outBuffer[j*packet.maxDataLength/blockRatio], packet.maxDataLength/blockRatio);
        }
        length = bufLen;
    }
    else if(protocol == LMS_PROTOCOL_DIGIC)
    {
        ProtocolDIGIC packet;
        bool writing = false;
        packet.cmd = pkt.cmd;
        int totalBlocks = 0;
        switch(pkt.cmd)
        {
        case CMD_SI5351_WR:
        case CMD_SI5356_WR:
            totalBlocks  = pkt.outLen/2; //data block pairs(address,value)
            break;
        case CMD_SI5351_RD:
        case CMD_SI5356_RD:
            totalBlocks  = pkt.outLen; //data blocks(address)
            break;
        case CMD_ADF4002_WR:
            packet.cmd = 0xAD;
            totalBlocks = pkt.outLen/3; //data block(3xByte)
            break;
        case CMD_LMS6002_RST:
        case CMD_LMS7002_RST:
            totalBlocks = 1;
            break;
        case CMD_GET_INFO:
            packet.cmd = 0x50;
            totalBlocks = 1;
            break;
        case CMD_LMS_PA:
            packet.cmd = 0x31;
            totalBlocks = 1;
            break;
        case CMD_LMS_LNA:
            packet.cmd = 0x30;
            totalBlocks = 1;
            break;
        case CMD_LMS6002_WR:
            packet.cmd = 0x16;
            totalBlocks = pkt.outLen/2;
            writing = true;
            break;
        case CMD_LMS6002_RD:
            packet.cmd = 0x17;
            totalBlocks = pkt.outLen;
            break;
        case CMD_PE636040_WR:
        case CMD_MYRIAD_GPIO_WR:
            totalBlocks = pkt.outLen;
            break;
        default:
            totalBlocks = pkt.outLen;
        }
        packet.i2cAddr = 0x28;
        packet.reserved = 0; //reserved

        int bufLen = ((pkt.outLen/packet.maxDataLength)+(pkt.outLen%packet.maxDataLength!=0))*packet.pktLength;
        if(bufLen == 0)
            bufLen = packet.pktLength;
        buffer = new unsigned char[bufLen];
        memset(buffer, 0, bufLen);

        for(int j=0; j*packet.pktLength<bufLen; ++j)
        {
            int pktPos = j*packet.pktLength;
            buffer[pktPos] = packet.cmd;
            buffer[pktPos+1] = packet.i2cAddr;
            if(totalBlocks > packet.maxDataLength/2 && writing)
            {
                buffer[pktPos+2] = packet.maxDataLength/2;
                totalBlocks -= packet.maxDataLength/2;
            }
            else if(totalBlocks > packet.maxDataLength)
            {
                buffer[pktPos+2] = packet.maxDataLength;
                totalBlocks -= packet.maxDataLength;
            }
            else
                buffer[pktPos+2] = totalBlocks;
            packet.blockCount = buffer[pktPos+2];
            buffer[pktPos+3] = packet.reserved;
            memcpy(&buffer[pktPos+4], &pkt.outBuffer[j*packet.maxDataLength], packet.maxDataLength);
            if(writing)
                for(int i=0; i<buffer[pktPos+2]; ++i)
                    buffer[pktPos+4+i*2] |= 0x80;
            if(packet.cmd == CMD_LMS6002_RST)
            {
                if(buffer[pktPos+4] == LMS_RST_ACTIVATE)
                    buffer[pktPos+4] = 0;
                else if(buffer[pktPos+4]== LMS_RST_DEACTIVATE)
                    buffer[pktPos+4] = 1;
                else if(buffer[pktPos+4] == LMS_RST_PULSE)
                {
                    buffer[pktPos+4] = 0;
                    buffer[pktPos+5] = 1;
                    buffer[pktPos+2] = 2;
                }
            }
        }
        length = bufLen;
    }
    else if(protocol == LMS_PROTOCOL_NOVENA)
    {
        ProtocolNovena packet;
        int bufLen = packet.pktLength;
        switch(pkt.cmd)
        {
        case CMD_LMS6002_WR:
            bufLen = pkt.outLen;
            break;
        case CMD_LMS6002_RD:
            bufLen = pkt.outLen*2;
            break;
        case CMD_LMS6002_RST:
            bufLen = pkt.outLen*2;
            break;
        default:
            bufLen = pkt.outLen;
        }

        if(bufLen == 0)
            bufLen = packet.pktLength;
        buffer = new unsigned char[bufLen];
        memset(buffer, 0, bufLen);
        if(pkt.cmd == CMD_LMS6002_WR)
        {
            memcpy(buffer, pkt.outBuffer, pkt.outLen);
            for(int i=0; i<pkt.outLen; i+=2)
                buffer[i] |= 0x80;
        }
        else if(pkt.cmd == CMD_LMS6002_RST)
        {
            buffer[0] = 0xb8;
            buffer[2] = 0xb8;
            bufLen = 2;
            if(pkt.outBuffer[0] == LMS_RST_ACTIVATE)
                buffer[1] = 0x18;
            else if(pkt.outBuffer[0] == LMS_RST_DEACTIVATE)
                buffer[1] = 0x38;
            else if(pkt.outBuffer[0] == LMS_RST_PULSE)
            {
                buffer[1] = 0x18;
                buffer[3] = 0x38;
                bufLen = 4;
            }
        }
        else if(pkt.cmd == CMD_LMS6002_RD)
        {
            for(int i=pkt.outLen-1; i>=0; --i)
            {
                buffer[i*2] = pkt.outBuffer[i];
                buffer[i*2+1] = 0;
            }
        }
        else if(pkt.cmd == CMD_LMS_PA)
        {
            unsigned char spibuf[2] = {0x38, 0};
            if(pSerPort != NULL)
            {
                long int btor = 2;
                pSerPort->Port_write_direct(spibuf, 2);
                pSerPort->Port_read_direct(spibuf, btor);
            }
            else
            {
                printf("Novena protocol needs to read 0x38 register, but connection manager is not given\n");
                spibuf[1] = 0xFF;
            }
            buffer[0] = 0xb8;
            buffer[1] = spibuf[1];
            buffer[1] &= 0xFB;
            buffer[1] |= 0x38;
            buffer[1] |= ((pkt.outBuffer[0] & 0x01) << 2);
            bufLen = 2;
        }
        else if(pkt.cmd == CMD_LMS_LNA)
        {
            unsigned char spibuf[2] = {0x38, 0};
            if(pSerPort != NULL)
            {
                long int btor = 2;
                pSerPort->Port_write_direct(spibuf, 2);
                pSerPort->Port_read_direct(spibuf, btor);
            }
            else
                printf("Novena protocol needs to read 0x38 register, but connection manager is not given\n");
            buffer[0] = 0xb8;
            buffer[1] = spibuf[1];
            buffer[1] &= 0xFC;
            buffer[1] |= 0x38;
            buffer[1] |= (pkt.outBuffer[0] & 0x03);
            bufLen = 2;
        }
        length = bufLen;
    }
    return buffer;
}

/** @brief Takes protocol data and transforms into generic packet
    @param pkt output packet
    @param buffer received protocol buffer
    @param length received buffer length
    @param protocol input protocol type
    @return 0:success, -1:unknown protocol
*/
int ParsePacket(GenericPacket &pkt, const unsigned char* buffer, const int length, const eLMS_PROTOCOL protocol)
{
    if(protocol == LMS_PROTOCOL_UNDEFINED)
        return -1;

    if(protocol == LMS_PROTOCOL_LMS64C)
    {
        ProtocolLMS64C packet;
        int inBufPos = 0;
        for(int i=0; i<length; i+=packet.pktLength)
        {
            pkt.cmd = (eCMD_LMS)buffer[i];
            pkt.status = (eCMD_STATUS)buffer[i+1];
            memcpy(&pkt.inBuffer[inBufPos], &buffer[i+8], packet.maxDataLength);
            inBufPos += packet.maxDataLength;
        }
        pkt.inLen = inBufPos;
        pkt.inLen = length;
    }
    if(protocol == LMS_PROTOCOL_DIGIC)
    {
        ProtocolDIGIC packet;
        int inBufPos = 0;
        for(int i=0; i<length; i+=packet.pktLength)
        {
            for(int j=0; j<packet.maxDataLength && j<length-i; ++j)
            {
                pkt.inBuffer[inBufPos++] = 0;
                pkt.inBuffer[inBufPos++] = buffer[i+j];
            }
        }
        pkt.inLen = inBufPos;
        pkt.status = STATUS_COMPLETED_CMD;
    }
    if(protocol == LMS_PROTOCOL_NOVENA)
    {
        ProtocolNovena packet;
        int inBufPos = 0;
        for(int i=0; i<length; i+=packet.pktLength)
        {
            for(int j=0; j<packet.maxDataLength && j<length-i; j+=2)
            {
                pkt.inBuffer[inBufPos++] = 0;
                pkt.inBuffer[inBufPos++] = buffer[i+j+1];
            }
        }
        pkt.inLen = inBufPos;
        pkt.status = STATUS_COMPLETED_CMD;
    }
    return 0;
}
