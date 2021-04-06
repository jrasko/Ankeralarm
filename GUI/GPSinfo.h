#ifndef ANKERALRM_GPSINFO_H
#define ANKERALRM_GPSINFO_H

#include "Anzeige.h"

class GPSinfo : public Zustand {
private:
    Anzeige anzeige;
public:
    void encoderPush() override {

    }

    void enocderRight() override {

    }

    GPSinfo(const Anzeige &anzeige) : anzeige(anzeige) {}

    void buttonReturn() override {

    }

    void encoderLeft() {
        anzeige.setZusatand(Alarm());
    }
};


#endif