#ifndef ANKERALARM_SETTINGS_H
#define ANKERALARM_SETTINGS_H

#include "Zustand.h"
#include "Anzeige.h"

class Settings : public Zustand {
private:
    Anzeige anzeige;
public:
    Settings(const Anzeige &anzeige) : anzeige(anzeige) {}

    void encoderPush() override {

    }

    void encoderLeft() override {

    }

    void enocderRight() override {

    }

    void buttonReturn() override {

    }

}

#endif //ANKERALARM_SETTINGS_H
