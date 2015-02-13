#ifndef NOVENA_FPGA_H
#define NOVENA_FPGA_H

int fpga_init();
int fpga_send(unsigned const int addr, const char* buf, const int len);
int fpga_read(unsigned const int addr, unsigned short *buf, const int len);
int prep_eim_burst();

//int spi_init();
//int spi_transfer(const char *tx, const int len, char *rx = 0);

int readKernelMemory(long offset, int virtualized, int size);
int writeKernelMemory(long offset, long value, int virtualized, int size);

#endif // NOVENA_FPGA_H

