#ifndef ANKERALRM_GPSINFO_H
#define ANKERALRM_GPSINFO_H

#include "Anzeige.h"

class GPSinfo : public Zustand
{
private:
    Anzeige a;
public:
void encoderLeft(){
    a.setZusatand(Alarm());
}
};


#endif