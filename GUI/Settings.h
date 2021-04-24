#ifndef ANKERALARM_SETTINGS_H
#define ANKERALARM_SETTINGS_H

#include "Utils.h"
#include "Alarm.h"
#include "GPSInfo.h"

/*
 * TODO
 *  Handling der Buttons bei Einstellungen überlegen, evtl. Push zum speichern und Return zum abbrechen
 */
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
private:
    unsigned char brightness;
public:
    ChangeDisplayBrightness();

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
private:
    unsigned char timeout;
public:
    ChangeTimeout();

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
