#ifndef ANKERALARM_UTILS_H
#define ANKERALARM_UTILS_H

#include "LiquidCrystal.h"
#include "Properties.h"

class Anzeige;

class Zustand {
protected:
    Anzeige *anzeige;

public:
    virtual ~Zustand() = default;

    void setAnzeige(Anzeige *a) {
        this->anzeige = a;
    }

    virtual void encoderPush() = 0;

    virtual void encoderLeft() = 0;

    virtual void encoderRight() = 0;

    virtual void buttonReturn() = 0;

    virtual void getLCDOutput() = 0;
};

class Anzeige {
private:
    Zustand *zustand;
public:
    Properties props;
public:
    LiquidCrystal &lcd;

    explicit Anzeige(LiquidCrystal &l) : zustand(nullptr), lcd(l) {}

    ~Anzeige() {
        delete zustand;
    }

    void activate(Zustand *z) {
        this->setZustand(z);
    }

    void encoderLeft() {
        this->zustand->encoderLeft();
    }

    void encoderRight() {
        this->zustand->encoderRight();
    }

    void encoderPush() {
        this->zustand->encoderPush();
    }

    void buttonReturn() {
        this->zustand->buttonReturn();
    }

    void setZustand(Zustand *z) {
        delete this->zustand;
        this->zustand = z;
        this->zustand->setAnzeige(this);
        lcd.clear();
        this->zustand->getLCDOutput();

    }
};

#endif