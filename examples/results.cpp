#include "results.h"

validblock resultarray[256];
char screenstring[100];

Results::Results() {
    for(int i=0;i<256;i++) {
        resultarray[i].shine = (uint16_t)i;
        resultarray[i].crc_ccitt_1d0f_val = 0;
        resultarray[i].count = 0;
    }
    bestkey = 65535;
    bestshine = 255;
}
void Results::addblock(uint8_t shine, uint16_t crc_ccitt_1d0f_val) { 
    validblock candidate;
    candidate.shine = shine;
    candidate.crc_ccitt_1d0f_val = crc_ccitt_1d0f_val;
    candidate.count = resultarray[(int)(shine)].count + 1;
    candidate.keyvalues = resultarray[(int)(shine)].keyvalues;
    if(nopriorhit(candidate)) {
        if (candidate.shine < bestshine) {
            bestshine = candidate.shine;
            bestkey = candidate.crc_ccitt_1d0f_val;
        }
        if ((candidate.shine == bestshine)&&(candidate.crc_ccitt_1d0f_val < bestkey)) {
            bestkey = candidate.crc_ccitt_1d0f_val;
        }
    }
    resultarray[(int)(shine)] = candidate;
}
bool nopriorhit(validblock& candidate) {
    bool newmatch = true;
    int size = candidate.keyvalues.size();
    uint16_t tmpkey = candidate.crc_ccitt_1d0f_val;
    for(int i=0;i<size;i++) {
        if(candidate.keyvalues[i] == candidate.crc_ccitt_1d0f_val) newmatch = false;
        if(tmpkey > candidate.keyvalues[i]) tmpkey = candidate.keyvalues[i];
    }
    candidate.crc_ccitt_1d0f_val = tmpkey;
    if(newmatch) {
        candidate.keyvalues.push_back(candidate.crc_ccitt_1d0f_val);
        printf( "shine = 0x%02" PRIX8"  ", candidate.shine );
        printf( "CRC-CCITT (0x1d0f) = 0x%04" PRIX16"  ", candidate.crc_ccitt_1d0f_val); 
        printf( "count = %d  \n", candidate.count);         
     }
     return newmatch;
}
void Results::showtable() {
    printf("\n\n");
    for(int i=0;i<256;i++) { 
        if(resultarray[i].crc_ccitt_1d0f_val > 0){
            printf( "shine = 0x%02" PRIX8"  ", resultarray[i].shine );
            printf( "CRC-CCITT (0x1d0f) = 0x%04" PRIX16"  ", resultarray[i].crc_ccitt_1d0f_val); 
            printf( "count = %d    ", resultarray[i].count);
            if ( resultarray[i].count<10 ) printf(" ");
            printf( "keycount = %d  \n", (int)resultarray[i].keyvalues.size());
        }
    }
}
uint16_t Results::fetchkey() {
    return bestkey;
}
uint8_t Results::fetchshime() {
    return bestshine;
}
char* Results::getscreenstring() {
    sprintf(screenstring,"Hello World");
    sprintf(screenstring, "BLOCK SHINE = 0x%02" PRIX8  "  BLOCK KEY = 0x%04" PRIX8, bestshine,bestkey);
    return screenstring;
}