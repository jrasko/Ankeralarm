#ifndef ANKERALARM_SETTINGS_H
#define ANKERALARM_SETTINGS_H

#include "Utils.h"
#include "Alarm.h"
#include "GPSInfo.h"

class Settings : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

class DisplayBrightness : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

class ChangeDisplayBrightness : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

class Timeout : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

class ChangeTimeout : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

class UTCLocal : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};

#endif //ANKERALARM_SETTINGS_H
