
#include "Settings.h"
#include "Ringer.h"

#define toDEG (3.14159265/180)

void Settings::encoderPush() {
	this->display->setZustand(new DisplayBrightness);
}

void Settings::encoderLeft() {
	this->display->setZustand(new GPSInfo);
}

void Settings::encoderRight() {
	this->display->setZustand(new Ringer);
}

void Settings::getLCDOutput() {
	display->print2Lines("Settings");
}

// Brightness
void DisplayBrightness::encoderPush() {
	this->display->setZustand(new ChangeDisplayBrightness());
}

void DisplayBrightness::getLCDOutput() {
	display->print2Lines("Brightness");
}

void DisplayBrightness::encoderLeft() {
	if (display->props.alarmActive) {
		this->display->setZustand(new ChangeAlarmCenter);
	} else {
		this->display->setZustand(new UTCFactor);
	}
}

void DisplayBrightness::encoderRight() {
	this->display->setZustand(new Timeout);
}

void DisplayBrightness::buttonReturn() {
	this->display->setZustand(new Settings);
}

//Change Brightness
void ChangeDisplayBrightness::encoderPush() {
	// Save Brightness
	this->display->props.displayBrightness = brightness;
	this->display->props.eeprom.writeInEEPROM(display->props.eeprom.BRIGHTNESS, display->props.displayBrightness);
	this->display->setZustand(new DisplayBrightness);
}

void ChangeDisplayBrightness::getLCDOutput() {
	display->print2Lines("ChangeBrightness", brightness);
}

void ChangeDisplayBrightness::encoderLeft() {
	if (brightness < 5) {
		brightness = 5;
	}
	brightness -= 5;
	Properties::setDisplayBrightness(brightness);
	this->getLCDOutput();
}

void ChangeDisplayBrightness::encoderRight() {
	if (brightness > 250) {
		brightness = 250;
	}
	brightness += 5;
	Properties::setDisplayBrightness(brightness);
	this->getLCDOutput();
}

void ChangeDisplayBrightness::buttonReturn() {
	// Reset Brightness
	brightness = display->props.displayBrightness;
	Properties::setDisplayBrightness(brightness);
	this->display->setZustand(new DisplayBrightness);

}

void ChangeDisplayBrightness::init() {
	brightness = display->props.displayBrightness;
}

// Timeout
void Timeout::encoderPush() {
	this->display->setZustand(new ChangeTimeout());
}

void Timeout::getLCDOutput() {
	display->print2Lines("Timeout");
}

void Timeout::encoderLeft() {
	this->display->setZustand(new DisplayBrightness);
}

void Timeout::encoderRight() {
	this->display->setZustand(new UTCFactor);
}

void Timeout::buttonReturn() {
	this->display->setZustand(new Settings);
}

void ChangeTimeout::encoderPush() {
	// Save Timeout
	this->display->props.displayTimeout = timeout;
	this->display->props.eeprom.writeInEEPROM(display->props.eeprom.TIMEOUT, display->props.displayTimeout);
	this->display->setZustand(new Timeout);
}

void ChangeTimeout::getLCDOutput() {
	display->print2Lines("ChangeTimeout", timeout);
}

void ChangeTimeout::encoderLeft() {
	if (timeout < 5) {
		timeout = 5;
	}
	timeout -= 5;
	this->getLCDOutput();
}

void ChangeTimeout::encoderRight() {
	if (timeout > 250) {
		timeout = 250;
	}
	timeout += 5;
	this->getLCDOutput();
}

void ChangeTimeout::buttonReturn() {
	this->display->setZustand(new Timeout);
}

void ChangeTimeout::init() {
	timeout = display->props.displayTimeout;
}

// UTC/Local Time
void UTCFactor::encoderPush() {
	this->display->setZustand(new ChangeUTCFactor());
}

void UTCFactor::getLCDOutput() {
	display->print2Lines("UTC/Local");
}

void UTCFactor::encoderLeft() {
	this->display->setZustand(new Timeout);
}

void UTCFactor::encoderRight() {
	if (display->props.alarmActive) {
		this->display->setZustand(new AlarmRadius);
	} else {
		this->display->setZustand(new DisplayBrightness);
	}
}

void UTCFactor::buttonReturn() {
	this->display->setZustand(new Settings);
}

void ChangeUTCFactor::encoderPush() {
	display->props.myGPS.getLastTimeStamp().setUTCFactor(factor);
	display->props.eeprom.writeInEEPROM(display->props.eeprom.UTCFACTOR,
										(unsigned char) (display->props.myGPS.getLastTimeStamp().getUTCFactor()));
	this->display->setZustand(new UTCFactor);
}

void ChangeUTCFactor::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%i", factor);
	display->print2Lines("ChangeUTCFactor", buf);
}

void ChangeUTCFactor::encoderLeft() {
	factor--;
	if (factor < -12) {
		factor = 12;
	}
	this->getLCDOutput();
}

void ChangeUTCFactor::encoderRight() {
	factor++;
	if (factor > 12) {
		factor = -12;
	}
	this->getLCDOutput();
}

void ChangeUTCFactor::buttonReturn() {
	this->display->setZustand(new UTCFactor);
}

void ChangeUTCFactor::init() {
	factor = display->props.myGPS.getLastTimeStamp().getUTCFactor();
}

void AlarmRadius::encoderPush() {
	this->display->setZustand(new ChangeAlarmRadius());
}

void AlarmRadius::encoderLeft() {
	this->display->setZustand(new UTCFactor);
}

void AlarmRadius::encoderRight() {
	this->display->setZustand(new ChangeAlarmCenter);
}

void AlarmRadius::buttonReturn() {
	this->display->setZustand(new Settings);
}

void AlarmRadius::getLCDOutput() {
	display->print2Lines("Set Alarm Radius");
}

void ChangeAlarmRadius::encoderLeft() {
	if (radius < 5) {
		radius = 5;
	}
	radius -= 5;
	getLCDOutput();
}

void ChangeAlarmRadius::encoderPush() {
	this->display->props.alarmRadius = radius;
	this->display->setZustand(new AlarmRadius);
}

void ChangeAlarmRadius::encoderRight() {
	if (radius > 250) {
		radius = 250;
	}
	radius += 5;
	getLCDOutput();
}

void ChangeAlarmRadius::buttonReturn() {
	this->display->setZustand(new AlarmRadius);
}

void ChangeAlarmRadius::getLCDOutput() {
	display->print2Lines("Set Alarm Radius", radius);
}

void ChangeAlarmRadius::init() {
	this->radius = display->props.alarmRadius;
}

void ChangeAlarmCenter::encoderPush() {
	display->setZustand(new ChangeAlarmCenterDist);
}

void ChangeAlarmCenter::encoderLeft() {
	display->setZustand(new AlarmRadius);
}

void ChangeAlarmCenter::encoderRight() {
	display->setZustand(new DisplayBrightness);
}

void ChangeAlarmCenter::getLCDOutput() {
	display->print2Lines("Set Alarm Center");
}

void ChangeAlarmCenter::buttonReturn() {
	display->setZustand(new Settings);
}

void ChangeAlarmCenterDist::encoderPush() {
	display->setZustand(new ChangeAlarmCenterDeg(dist));
}

void ChangeAlarmCenterDist::encoderLeft() {
	if (dist < 10) {
		dist = 10;
	}
	dist -= 5;
	getLCDOutput();
}

void ChangeAlarmCenterDist::encoderRight() {
	if (dist > 250) {
		dist = 250;
	}
	dist += 5;
	getLCDOutput();
}

void ChangeAlarmCenterDist::buttonReturn() {
	display->setZustand(new ChangeAlarmCenter);
}

void ChangeAlarmCenterDist::getLCDOutput() {
	display->print2Lines("Set Distance", dist);
}

void ChangeAlarmCenterDeg::encoderPush() {
	long lat = (long) (54 * dist * cos(deg * toDEG));
	long lon = (long) (54 * dist * sin(deg * toDEG));

	display->props.centralPosition.getWorkLatitude() += lat;
	display->props.centralPosition.getWorkLongitude() += lon;
	display->setZustand(new ChangeAlarmCenter);
}

void ChangeAlarmCenterDeg::encoderLeft() {
	if (deg < 5) {
		deg = 5;
	}
	deg -= 5;
	getLCDOutput();
}

void ChangeAlarmCenterDeg::encoderRight() {
	if (deg > 355) {
		deg = 355;
	}
	deg += 5;
	getLCDOutput();
}

void ChangeAlarmCenterDeg::buttonReturn() {
	display->setZustand(new ChangeAlarmCenterDist);
}

void ChangeAlarmCenterDeg::getLCDOutput() {
	display->print2Lines("Set Degrees", deg);
}
