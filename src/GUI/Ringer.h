
#ifndef ANKERALARM_5_0_RINGER_H
#define ANKERALARM_5_0_RINGER_H

#include "Utils.h"
#include "Alarm.h"
#include "GPSInfo.h"

class Ringer : public State {
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void getLCDOutput() override;
};

class SetHour : public State{
private:
	unsigned char hour = 0;
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class SetMinute: public State{
private:
	unsigned char minute = 0;
public:
	void encoderPush() override;

	void encoderLeft() override;

	void encoderRight() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AreUSureRinger: public State{
public:
	void encoderPush() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};

class AbortRinger : public State{
public:
	void encoderPush() override;

	void buttonReturn() override;

	void getLCDOutput() override;
};


#endif //ANKERALARM_5_0_RINGER_H
