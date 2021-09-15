#ifndef RESULTS_H
#define RESULTS_H

#include <inttypes.h>
#include <stdio.h>
#include <string>
#include <vector> 

struct validblock {
    std::vector<uint16_t> keyvalues;  
    uint16_t crc_ccitt_1d0f_val;
    uint8_t shine;
    int count;
};

bool nopriorhit(validblock& candidate);

class Results {
public:
    Results();
    void addblock(uint8_t shine, uint16_t crc_ccitt_1d0f_val);
    void showtable();
    uint16_t fetchkey();
    uint8_t fetchshime();
    char* getscreenstring();

private:
    validblock* resultable;
    uint16_t bestkey;
    uint8_t bestshine;
};


#endif