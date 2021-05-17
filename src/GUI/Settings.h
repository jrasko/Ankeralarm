#ifndef ANKERALARM_SETTINGS_H
#define ANKERALARM_SETTINGS_H

#include "Utils.h"
#include "Alarm.h"
#include "GPSInfo.h"

class Settings : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void getLCDOutput() override;
};

class DisplayBrightness : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeDisplayBrightness : public State {
private:
	unsigned char brightness = 255;
public:
	ChangeDisplayBrightness();

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class Timeout : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeTimeout : public State {
private:
	unsigned char timeout = 60;
public:
	ChangeTimeout();

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class UTCFactor : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeUTCFactor : public State {
private:
	char factor = 0;
public:
	ChangeUTCFactor();

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};


class AlarmRadius : public State {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeAlarmRadius : public State {
private:
	unsigned char radius = 0;
public:
	ChangeAlarmRadius();

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

#endif //ANKERALARM_SETTINGS_H
