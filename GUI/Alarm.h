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

class FindPostition : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class SetRadius : public Zustand {
private:
	unsigned char radius = 25;
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AreUSure : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AbortAlarm : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};


#endif