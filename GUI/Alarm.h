#ifndef ANKERALRM_ALARM_H
#define ANKERALRM_ALARM_H

#include "Zustand.h"
#include "Anzeige.h"

class Alarm : public Zustand {
private:
    Anzeige anzeige;
public:
    void encoderPush() override {

    }

    void encoderLeft() override {

    }

    void enocderRight() override {

    }

    void buttonReturn() override {

    }

    Alarm(const Anzeige &anzeige) : anzeige(anzeige) {}

};


#endif