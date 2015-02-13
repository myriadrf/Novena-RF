#include "NovenaFPGA.h"

#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#if defined(__GNUC__) || defined(__GNUG__)
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef __unix__
#include <sys/mman.h>
#include <stdint.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#endif

#define IMX6_EIM_BASE_ADDR 0x021b8000
#define IMX6_EIM_CS0_BASE (0x00)
#define IMX6_EIM_CS1_BASE (0x18)
#define IMX6_EIM_CS2_BASE (0x30)
#define IMX6_EIM_CS3_BASE (0x48)
#define IMX6_EIM_WCR (0x90)
#define IMX6_EIM_WIAR (0x94)

#define IMX6_EIM_CS0_BASE_ADDR 0x08040000
#define IMX6_EIM_CS1_BASE_ADDR 0x0c040000

#define DATA_FIFO_ADDR (IMX6_EIM_CS1_BASE_ADDR + 0xf000)
#include "CommonUtilities.h"

using namespace std;

static const int cSPI_SPEED = 5000000;

int old_counter = 0;
#ifdef __unix__
static int   *mem_32 = 0;
static short *mem_16 = 0;
static char  *mem_8  = 0;
static int   *prev_mem_range = 0;
static int mem_fd = 0;
static int fd =0 ;
#endif

bool eim_configured = false;

int prep_eim_burst()
{
    if(eim_configured == true)
        return 1;
    eim_configured = true;
    // set up pads to be mapped to EIM
    for (int i = 0; i < 16; i++)
    {
        writeKernelMemory(0x20e0114 + i*4, 0x0, 0, 4); // mux mapping
        writeKernelMemory(0x20e0428 + i*4, 0xb0b1, 0, 4); // pad strength config'd for a 100MHz rate
    }

    // mux mapping
    writeKernelMemory(0x20e046c - 0x314, 0x0, 0, 4); // BCLK
    writeKernelMemory(0x20e040c - 0x314, 0x0, 0, 4); // CS0
    writeKernelMemory(0x20e0410 - 0x314, 0x0, 0, 4); // CS1
    writeKernelMemory(0x20e0414 - 0x314, 0x0, 0, 4); // OE
    writeKernelMemory(0x20e0418 - 0x314, 0x0, 0, 4); // RW
    writeKernelMemory(0x20e041c - 0x314, 0x0, 0, 4); // LBA
    writeKernelMemory(0x20e0468 - 0x314, 0x0, 0, 4); // WAIT
    writeKernelMemory(0x20e0408 - 0x314, 0x0, 0, 4); // A16
    writeKernelMemory(0x20e0404 - 0x314, 0x0, 0, 4); // A17
    writeKernelMemory(0x20e0400 - 0x314, 0x0, 0, 4); // A18
    writeKernelMemory(0x20e0400 - 0x314, 0x0, 0, 4); // A18

    // pad strength
    writeKernelMemory(0x20e046c, 0xb0b1, 0, 4); // BCLK
    writeKernelMemory(0x20e040c, 0xb0b1, 0, 4); // CS0
    writeKernelMemory(0x20e0410, 0xb0b1, 0, 4); // CS1
    writeKernelMemory(0x20e0414, 0xb0b1, 0, 4); // OE
    writeKernelMemory(0x20e0418, 0xb0b1, 0, 4); // RW
    writeKernelMemory(0x20e041c, 0xb0b1, 0, 4); // LBA
    writeKernelMemory(0x20e0468, 0xb0b1, 0, 4); // WAIT
    writeKernelMemory(0x20e0408, 0xb0b1, 0, 4); // A16
    writeKernelMemory(0x20e0404, 0xb0b1, 0, 4); // A17
    writeKernelMemory(0x20e0400, 0xb0b1, 0, 4); // A18

    writeKernelMemory(0x020c4080, 0xcf3, 0, 4); // ungate eim slow clocks

    // EIM_CSnGCR1
    // rework timing for sync use
    // PSZ WP GBC AUS CSREC SP DSZ BCS BCD WC BL CREP CRE RFL WFL MUM SRD SWR CSEN

    int PSZ = 3 << 28; // 2048 words page size
    int WP = 0 << 27; //(not protected)
    int GBC = 1 << 24; //min 1 cycles between chip select changes
    int AUS = 1 << 23; //0 address shifted according to port size / 1: unshifted
    int CSREC = 1 << 20; //min 1 cycles between CS, OE, WE signals
    int SP = 0 << 19; //no supervisor protect (user mode access allowed)
    int DSZ = 1 << 16; //16-bit port resides on DATA[15:0]
    int BCS = 0 << 14; //0 clock delay for burst generation
    int BCD = 0 << 12; //divide EIM clock by 1 for burst clock
    int WC = 1 << 11; //write accesses are continuous burst length
    int BL = 3 << 8; //32 word memory wrap length
    //int BL = 4 << 8; //32 word memory wrap length
    int CREP = 1 << 7; //non-PSRAM, set to 1
    int CRE = 0 << 6; //CRE is disabled
    int RFL = 0 << 5; //fixed latency reads
    int WFL = 0 << 4; //fixed latency writes
    int MUM = 1 << 3; //multiplexed mode enabled
    int SRD = 1 << 2; //synch reads
    int SWR = 1 << 1; //synch writes
    int CSEN = 1; //chip select is enabled
    int EIM_CSnGCR1 = PSZ|WP|GBC|AUS|CSREC|SP|DSZ|BCS|BCD|WC|BL|CREP|CRE|RFL|WFL|MUM|SRD|SWR|CSEN;
    printf("EIM_CSnGCR1 0x%08X\n", EIM_CSnGCR1);

    writeKernelMemory(0x21b8000, EIM_CSnGCR1, 0, 4);
    writeKernelMemory(0x21b8000+24, EIM_CSnGCR1, 0, 4);
    writeKernelMemory(0x21b8000+48, EIM_CSnGCR1, 0, 4);

    // EIM_CS0GCR2
    int MUX16_BYP_GRANT = 1 << 12;
    int DAP = 0 << 9;
    int DAE = 0 << 8;
    int DAPS = 0 << 4;
    int ADH = 0; // address hold time after ADC negation(0 cycles)
    int EIM_CSnGCR2 = MUX16_BYP_GRANT|DAP|DAE|DAPS|ADH;
    printf("EIM_CSnGCR2 0x%08X\n", EIM_CSnGCR2);
    writeKernelMemory(0x21b8004, EIM_CSnGCR2, 0, 4);
    writeKernelMemory(0x21b8004+24, EIM_CSnGCR2, 0, 4);
    writeKernelMemory(0x21b8004+48, EIM_CSnGCR2, 0, 4);

    // EIM_CS0RCR1
    // RWSC RADVA RAL RADVN OEA OEN RCSA RCSN
    int RWSC = 3 << 24;
    int RADVA = 0 << 20;
    int RAL = 0 << 19;
    int RADVN = 0 << 16;
    int OEA = 0 << 12;
    int OEN = 0 << 8;
    int RCSA = 0 << 4;
    int RCSN = 0;
    int EIM_CSnRCR1 = RWSC|RADVA|RAL|RADVN|OEA|OEN|RCSA|RCSN;
    writeKernelMemory(0x21b8008, EIM_CSnRCR1, 0, 4);
    writeKernelMemory(0x21b8008+24, EIM_CSnRCR1, 0, 4);
    writeKernelMemory(0x21b8008+48, EIM_CSnRCR1, 0, 4);
    printf("EIM_CSnRCR1 0x%08X\n", EIM_CSnRCR1);

    // EIM_CS0RCR2
    // APR PAT RL RBEA RBEN
    int APR = 0 << 15; // 0 mandatory because MUM = 1
    int PAT = 0 << 12; // XXX because APR = 0
    int RL = 0 << 8; //
    int RBEA = 0 << 4; //these match RCSA/RCSN from previous field
    int RBE = 0 << 3;
    int RBEN = 0;
    int EIM_CSnRCR2 = APR|PAT|RL|RBEA|RBE|RBEN;
    writeKernelMemory(0x21b800c, EIM_CSnRCR2, 0, 4);
    writeKernelMemory(0x21b800c+24, EIM_CSnRCR2, 0, 4);
    writeKernelMemory(0x21b800c+48, EIM_CSnRCR2, 0, 4);
    printf("EIM_CSnRCR2 0x%08X\n", EIM_CSnRCR2);

    // EIM_CS0WCR1
    // WAL WBED WWSC WADVA WADVN WBEA WBEN WEA WEN WCSA WCSN
    int WAL = 0 << 31; //use WADVN
    int WBED = 0 << 30; //allow BE during write
    int WWSC = 1 << 24; // write wait states
    int WADVA = 0 << 21; //same as RADVA
    int WADVN = 2 << 18; //this sets WE length to 1 (this value +1)
    int WBEA = 0 << 15; //same as RBEA
    int WBEN = 0 << 12; //same as RBEN
    //int WEA = 2 << 9; //2 cycles between beginning of access and WE assertion
    int WEA = 0 << 9; //0 cycles between beginning of access and WE assertion
    int WEN = 0 << 6; //1 cycles to end of WE assertion
    int WCSA = 0 << 3; //cycles to CS assertion
    int WCSN = 0 ; //cycles to CS negation
    int EIM_CSnWCR1 = WAL|WBED|WWSC|WADVA|WADVN|WBEA|WBEN|WEA|WEN|WCSA|WCSN;
    printf("EIM_CSnWCR1 0x%08X\n", EIM_CSnWCR1);
    writeKernelMemory(0x21b8010, EIM_CSnWCR1, 0, 4);
    writeKernelMemory(0x21b8010+24, EIM_CSnWCR1, 0, 4); //cs1
    writeKernelMemory(0x21b8010+48, EIM_CSnWCR1, 0, 4); //cs2

    // EIM_WCR
    // BCM = 1 free-run BCLK
    // GBCD = 0 don't divide the burst clock
    // EIM_WCR
    int WDOG_LIMIT = 3 << 9;
    int WDOG_EN = 1 << 8;
    int INTPOL = 0 << 5;
    int INTEN = 0 << 4;
    int GBCD = 0 << 1; //0 //don't divide the burst clock
    int BCM = 1; //free-run BCLK
    int EIM_WCR = WDOG_LIMIT|WDOG_EN|INTPOL|INTEN|GBCD|BCM;
    writeKernelMemory(0x21b8090, EIM_WCR, 0, 4);
    printf("EIM_WCR 0x%08X\n", EIM_WCR);

    // EIM_WIAR
    // ACLK_EN = 1
    // EIM_WIAR
    int ACLK_EN = 1 << 4;
    int ERRST = 0 << 3;
    int INT = 0 << 2;
    int IPS_ACK = 0 << 1;
    int IPS_REQ = 0;
    int EIM_WIAR = ACLK_EN|ERRST|INT|IPS_ACK|IPS_REQ;
    writeKernelMemory(0x21b8094, EIM_WIAR, 0, 4);
    printf("EIM_WIAR 0x%08X\n", EIM_WIAR);

    printf( "resetting CS0 space to 64M and enabling 32M CS1 and 32M CS2 space.\n" );
    writeKernelMemory( 0x20e0004, (readKernelMemory(0x20e0004, 0, 4) & 0xFFFFF000) | 0x04B, 0, 4);
    printf("EIM configured\n");
    return 0;
}

int fpga_init()
{
    prep_eim_burst();
    return 0;
}

int fpga_send(unsigned const int addr, const char* buf, const int len)
{
#ifdef __unix__
    void* mem_base = 0;
    if(mem_32)
        munmap(mem_32, 0xFFFF);
    if(fd)
        close(fd);

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if( fd < 0 )
    {
        perror("Unable to open /dev/mem");
        fd = 0;
        return -1;
    }

    const unsigned int map_size = 4096;
    const unsigned int map_mask = map_size-1;

    mem_base = mmap(0, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr & ~map_mask);
    if(mem_base < 0)
    {
        printf("error mapping memory\n");
        return -1;
    }

    void* virt_addr;
    virt_addr = mem_base + (addr & map_mask);
    for(unsigned i=0; i<len/sizeof(unsigned short); ++i)
    {
        *(unsigned short*)(virt_addr+i*2) = ((unsigned short*)buf)[i];
    }
    if(munmap(mem_base, map_size) == -1)
        return -2;
    close(fd);
#endif
    return 0;
}

int fpga_read(unsigned const int addr, unsigned short *buf, const int len)
{
#ifdef __unix__
    void* mem_base = 0;

    if(mem_32)
        munmap(mem_32, 0xFFFF);
    if(fd)
        close(fd);

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if( fd < 0 )
    {
        perror("Unable to open /dev/mem");
        fd = 0;
        return -1;
    }

    const unsigned int map_size = 4096;
    const unsigned int map_mask = map_size-1;

    mem_base = mmap(0, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr & ~map_mask);
    //mem_base = ioremap_wc(addr & ~map_mask, map_size);
    if(mem_base < 0)
    {
        printf("error mapping memory\n");
        return -1;
    }
    void* virt_addr;
    virt_addr = mem_base + (addr & map_mask);
    memcpy(buf, virt_addr, len);
    if(munmap(mem_base, map_size) == -1)
    {
        printf("munmap failed\n");
        return -2;
    }
    close(fd);
#endif
    return 0;
}

int readKernelMemory(long offset, int virtualized, int size)
{
#ifdef __unix__
    int result;

    int *mem_range = (int *)(offset & ~0xFFFF);
    if( mem_range != prev_mem_range )
    {
        prev_mem_range = mem_range;

        if(mem_32)
            munmap(mem_32, 0xFFFF);
        if(mem_fd)
            close(mem_fd);

        if(virtualized)
        {
            mem_fd = open("/dev/kmem", O_RDWR);
            if( mem_fd < 0 )
            {
                printf("%s %s\n", "Couldn't open /dev/mem", strerror(errno));
                mem_fd = 0;
                return -1;
            }
        }
        else
        {
            mem_fd = open("/dev/mem", O_RDWR);
            if (mem_fd < 0)
            {
                printf("%s %s\n", "Couldn't open /dev/mem" ,strerror(errno));
                mem_fd = 0;
                return -1;
            }
        }

        mem_32 = (int *)mmap(0, 0xffff, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, offset&~0xFFFF);
        if ((void *)-1 == mem_32)
        {
            printf("%s %s\n", "Couldn't mmap /dev/kmem: ", strerror(errno));

            if (-1 == close(mem_fd))
                printf("%s %s\n", "Also couldn't close /dev/kmem: ", strerror(errno));

            mem_fd=0;
            return -1;
        }
        mem_16 = (short *)mem_32;
        mem_8 = (char *)mem_32;
    }

    int scaled_offset = (offset-(offset&~0xFFFF));
    if (size == 1)
    {
        if(mem_8)
        result = mem_8[scaled_offset/sizeof(char)];
    }
    else if (size == 2)
    {
        if(mem_16)
            result = mem_16[scaled_offset/sizeof(short)];
    }
    else
    {
        if(mem_32)
            result = mem_32[scaled_offset/sizeof(long)];
    }

    return result;
#else
    return 0;
#endif
}

int writeKernelMemory(long offset, long value, int virtualized, int size)
{
#ifdef __unix__
    int old_value = readKernelMemory(offset, virtualized, size);
    int scaled_offset = (offset-(offset&~0xFFFF));
    if (size == 1)
    {
        if(mem_8)
            mem_8[scaled_offset/sizeof(char)] = value;
    }
    else if (size == 2)
    {
        if(mem_16)
            mem_16[scaled_offset/sizeof(short)] = value;
    }
    else
    {
        if(mem_32)
            mem_32[scaled_offset/sizeof(long)] = value;
    }
    return old_value;
#endif // __unix__
    return 0;
}
