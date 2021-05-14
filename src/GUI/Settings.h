#ifndef ANKERALARM_SETTINGS_H
#define ANKERALARM_SETTINGS_H

#include "Utils.h"
#include "Alarm.h"
#include "GPSInfo.h"

class Settings : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class DisplayBrightness : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeDisplayBrightness : public Zustand {
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

class Timeout : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeTimeout : public Zustand {
private:
	unsigned char timeout = 0;
public:
	ChangeTimeout();

	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class UTCFactor : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeUTCFactor : public Zustand {
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


class AlarmRadius : public Zustand {
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class ChangeAlarmRadius : public Zustand {
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
