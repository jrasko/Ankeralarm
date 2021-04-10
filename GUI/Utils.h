#ifndef ANKERALARM_UTILS_H
#define ANKERALARM_UTILS_H

class Anzeige;

class Zustand {
protected:
    Anzeige *anzeige;
    // LiquidCrystal lcd;
public:
    virtual ~Zustand() {}

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

    explicit Anzeige(Zustand *z) : zustand(nullptr) {
        this->setZustand(z);
    }

    ~Anzeige() {
        delete zustand;
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
    }
};

#endif