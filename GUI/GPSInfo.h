#ifndef ANKERALARM_GPSINFO_H
#define ANKERALARM_GPSINFO_H

#include "Utils.h"
#include "Settings.h"
#include "Alarm.h"
#include <bitset>



class GPSInfo : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class Koordinaten : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class Satellites : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class FixAge : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class HDOP : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class Time : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};

class Radius : public Zustand {
public:
    void encoderPush() override;

    void encoderRight() override;

    void buttonReturn() override;

    void encoderLeft() override;

    void getLCDOutput() override;
};


#endif