#ifndef CRC0X1D0F_H
#define CRC0X1D0F_H

#include <inttypes.h>
#include <sys/time.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "../../include/checksum.h"

/* "ABCDEFGHIJKLMNOPQRSTUVWXYZ" : CRC-CCITT (0x1d0f) = 0x4430  --  17456 */

class Crc0x1d0f
{
public:
    Crc0x1d0f(const char* message);
    void compute();
    bool extendedcompute(uint16_t link, uint8_t extra);
    void print();
    uint16_t getblockkey();
    int getshine();
private:
    char *ptr;
	uint16_t crc_ccitt_1d0f_val;
	uint16_t blockkey;
    uint8_t shine;
    const char *message;
	int charcount;
};


#endif 