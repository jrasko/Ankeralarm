#ifndef ANKERALARM_GPSINFO_H
#define ANKERALARM_GPSINFO_H

#include "Utils.h"
#include "Alarm.h"
#include "Settings.h"

using namespace std;

class GPSInfo;

class Koordinaten;

class Satellites;

class FixAge;

class HDOP;

class Time;


class GPSInfo : public Zustand {
public:
    void encoderPush() override {
        this->anzeige->setZustand(new Koordinaten);
    }

    void encoderRight() override {
        this->anzeige->setZustand(new Settings);
    }

    void buttonReturn() override {
        // Do nothing
    }

    void encoderLeft() override override {
        this->anzeige->setZustand(new Alarm);
    }
};

class Koordinaten : public Zustand {
public:
    void encoderPush() override {

    }

    void encoderRight() override {

    }

    void buttonReturn() override {
        this->anzeige->setZustand(new GPSInfo);
    }

    void encoderLeft() override {
    }

    virtual vector<string> getLCDOutput() {

    }
};

class Satellites : public Zustand {
public:
    void encoderPush() override {

    }

    void encoderRight() override {

    }


    void buttonReturn() override {
        this->anzeige->setZustand(new GPSInfo);
    }

    void encoderLeft() override {

    }

    virtual vector<string> getLCDOutput() {

    }
};

class FixAge : public Zustand {
public:
    void encoderPush() override {

    }

    void encoderRight() override {

    }


    void buttonReturn() override {
        this->anzeige->setZustand(new GPSInfo);
    }

    void encoderLeft() override {

    }

    virtual vector<string> getLCDOutput() {

    }
};

class HDOP : public Zustand {
public:
    void encoderPush() override {

    }

    void encoderRight() override {

    }


    void buttonReturn() override {
        this->anzeige->setZustand(new GPSInfo);
    }

    void encoderLeft() override {

    }

    virtual vector<string> getLCDOutput() {

    }
};

class Time : public Zustand {
public:
    void encoderPush() override {

    }

    void encoderRight() override {

    }

    void buttonReturn() override {
        this->anzeige->setZustand(new GPSInfo);
    }

    void encoderLeft() override {

    }

    virtual vector<string> getLCDOutput() {

    }
};


#endif