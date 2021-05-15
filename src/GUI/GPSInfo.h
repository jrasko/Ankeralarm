#ifndef ANKERALARM_GPSINFO_H
#define ANKERALARM_GPSINFO_H

#include "Utils.h"
#include "Settings.h"
#include "Alarm.h"
#include <Arduino.h>


class GPSInfo : public State {
public:
	void encoderPush() override;

	void encoderRight() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class Coordinates : public State {
public:
	void encoderPush() override;

	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class Satellites : public State {
public:
	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class FixAge : public State {
public:
	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class HDOP : public State {
public:
	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class Time : public State {
public:
	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};

class Radius : public State {
public:
	void encoderRight() override;

	void buttonReturn() override;

	void encoderLeft() override;

	void getLCDOutput() override;
};


#endif