#ifndef ANKERALARM_UTILS_H
#define ANKERALARM_UTILS_H

#include "LiquidCrystal.h"
#include "Properties.h"

class Display;

class State {
protected:
	Display *display;

public:
	virtual ~State() = default;

	void setAnzeige(Display *a) {
		this->display = a;
	}

	virtual void encoderPush() {};

	virtual void encoderLeft() {};

	virtual void encoderRight() {};

	virtual void buttonReturn() {};

	virtual void getLCDOutput() = 0;
};

class Display {
private:
	State *state;
public:
	Properties &props = Properties::getInstance();
	LiquidCrystal &lcd;

	explicit Display(LiquidCrystal &l) : state(nullptr), lcd(l) {}

	~Display() {
		delete state;
	}

	void activate(State *z) {
		this->setZustand(z);
	}

	void encoderLeft() {
		this->state->encoderLeft();
	}

	void encoderRight() {
		this->state->encoderRight();
	}

	void encoderPush() {
		this->state->encoderPush();
	}

	void buttonReturn() {
		this->state->buttonReturn();
	}

	void getLCDOutput() {
		this->state->getLCDOutput();
	}

	void print2Lines(const char *l1, const char *l2) {
		lcd.setCursor(0, 0);
		lcd.write(l1);
		lcd.setCursor(0, 1);
		lcd.write(l2);
	}

	void setZustand(State *z) {
		delete this->state;
		this->state = z;
		this->state->setAnzeige(this);
		lcd.clear();
		this->state->getLCDOutput();
	}
};

#endif