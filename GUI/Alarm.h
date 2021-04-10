#ifndef ANKERALARM_ALARM_H
#define ANKERALARM_ALARM_H

#include "Utils.h"
#include "Settings.h"
#include "GPSInfo.h"

class Alarm : public Zustand {
public:
    void encoderPush() override;

    void encoderLeft() override;

    void encoderRight() override;

    void buttonReturn() override;

    void getLCDOutput() override;
};


#endif