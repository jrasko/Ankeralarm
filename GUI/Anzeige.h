#ifndef ANKERALRM_ANZEIGE_H
#define ANKERALRM_ANZEIGE_H

#include "Zustand.h"
#include "GPSinfo.h"

class Anzeige {
private:
    Zustand zustand;

public:
    Anzeige() = default;

    void encoderLeft() {
        zustand.encoderLeft();
    }

    void encoderRight() {
        zustand.encoderRight();
    }

    void encoderPush() {
        zustand.encoderPush();
    }

    void buttonReturn() {
        zustand.buttonReturn();
    }

    void setZusatand(const Zustand& z) {
        zusatand = z;
    }
};

Anzeige::Anzeige() {
    zustand = GPSinfo();
}

#endif