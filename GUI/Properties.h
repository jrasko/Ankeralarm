
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#include "../GPS/GPS.h"

class Properties {
public:
    GPS myGPS;
    bool alarmActive;
    unsigned char displayBrighness = 0;
    unsigned char displayTimeout = 0;

};

#endif //ANKERALARM_PROPERTIES_H
