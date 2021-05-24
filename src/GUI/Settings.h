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
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;

	void init() override;
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
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;

	void init() override;
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
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;

	void init() override;
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

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;

	void init() override;
};

#endif //ANKERALARM_SETTINGS_H
