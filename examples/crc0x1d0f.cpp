#include "crc0x1d0f.h"

Crc0x1d0f::Crc0x1d0f(const char* message) {
    this->message = (char*)message;
    int count = 0;
    while (*(message+count++)!=0);
    this->charcount = count-1;
}
void Crc0x1d0f::compute() {  // used for test
    crc_ccitt_1d0f_val = 0x1d0f;
	ptr = (char *) message;
	while ( *ptr ) {crc_ccitt_1d0f_val = update_crc_ccitt(crc_ccitt_1d0f_val, *ptr++); }
}
void Crc0x1d0f::print() {
    printf( "\nshine = 0x%02" PRIX8"  ", shine );
    printf( "CRC-CCITT (0x1d0f) = 0x%04" PRIX16"\n", crc_ccitt_1d0f_val);
}
uint16_t Crc0x1d0f::getblockkey() { return blockkey; }
int Crc0x1d0f::getshine() { return (int)shine; }


bool Crc0x1d0f::extendedcompute(uint16_t link, uint8_t extra) {
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    crc_ccitt_1d0f_val = 0x1d0f;
    unsigned char blocklinks[6];
    blocklinks[0] = (unsigned char)(0x00ff & (link >> 8));
    blocklinks[1] = (unsigned char)(0x00ff & link);
    blocklinks[2] = (unsigned char)(unsigned char)extra;
    blocklinks[3] = (unsigned char)(rand() % 256);
    blocklinks[4] = (unsigned char)(rand() % 256);
    blocklinks[5] = (unsigned char)(rand() % 256);
    uint16_t compval = uint16_t(blocklinks[3] << 8) + uint16_t(blocklinks[4]);
    //printfs to verify compval is constructed right
    //printf( "\nCRC-CCITT (0x1d0f) = 0x%04" PRIX8 "\n", blocklinks[2]);
    //printf( "\nCRC-CCITT (0x1d0f) = 0x%04" PRIX8 "\n", blocklinks[3]);
    //printf( "\nCRC-CCITT (0x1d0f) = 0x%04" PRIX16 "\n", compval);

	ptr = (char *) blocklinks;
	while ( *ptr ) { crc_ccitt_1d0f_val = update_crc_ccitt(crc_ccitt_1d0f_val, *ptr++); }
	ptr = (char *) message;
	while ( *ptr ) { crc_ccitt_1d0f_val = update_crc_ccitt(crc_ccitt_1d0f_val, *ptr++); }

    if(compval == crc_ccitt_1d0f_val) {
        blockkey = compval;
        shine = blocklinks[4];
        return true;
    }
    else return false;

}