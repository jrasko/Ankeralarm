#ifndef ANKERALARM_ALARM_H
#define ANKERALARM_ALARM_H

#include "Utils.h"
#include "Settings.h"
#include "GPSInfo.h"

class Alarm : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void getLCDOutput() override;
};

class FindPosition : public State {
public:
	void getLCDOutput() override;
};

class SetRadius : public State {
private:
	unsigned char radius = 25;
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AreUSure : public State {
public:
	void encoderPush() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AbortAlarm : public State {
public:
	void encoderPush() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};


#endif