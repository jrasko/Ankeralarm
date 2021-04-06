#ifndef ANKERALRM_ZUSTAND_H
#define ANKERALRM_ZUSTAND_H

class Zustand{
public:
    void encoderPush() = 0;
    void encoderLeft() = 0;
    void enocderRight() = 0;
    void buttonReturn() = 0;
};



#endif