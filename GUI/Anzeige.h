#ifndef ANKERALRM_ANZEIGE_H
#define ANKERALRM_ANZEIGE_H

#include "Zustand.h"

class Anzeige{
private:
    Zustand zustand;

public:
    Anzeige(){
        zustand = GPSinfo();
    }
    void encoderLeft(){
        zustand.encoderLeft();
    }
    void encoderRight(){
        zustand.encoderRight();
    }
    void encoderPush(){
        zustand.encoderPush();
    }
    void buttonReturn(){
        zustand.buttonReturn();
    }
    void setZusatand(Zustand z){
        zusatand = z;
    }
};

#endif