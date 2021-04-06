#ifndef ANKERALRM_ZUSTAND_H
#define ANKERALRM_ZUSTAND_H

class Zustand {
public:
    virtual void encoderPush() = 0;

    virtual void encoderLeft() = 0;

    virtual void enocderRight() = 0;

    virtual void buttonReturn() = 0;
};


#endif