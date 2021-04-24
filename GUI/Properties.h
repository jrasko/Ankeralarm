
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#include "../GPS/GPS.h"

class Properties {
public:
    GPS myGPS;
    bool alarmActive;
    // TODO init with EPROM, set Display in setup
    unsigned char displayBrighness = 0;
    unsigned char displayTimeout = 0;

    void setDisplayBrightness(unsigned char brightness){

    }

    void setDisplayTimeout(unsigned char brightness){

    }

    void writeEEPROM(unsigned char value){

    }

    unsigned char readEEPROM(){
        return 0;
    }

};

#endif //ANKERALARM_PROPERTIES_H
