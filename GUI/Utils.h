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

	//TODO leere Methode geben damit im Code nix implementiert werden muss
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

	void getLCDOutput(){
		this->zustand->getLCDOutput();
	}

	void print2Lines(const char *l1, const char *l2) {
		lcd.setCursor(0, 0);
		lcd.write(l1);
		lcd.setCursor(0, 1);
		lcd.write(l2);
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