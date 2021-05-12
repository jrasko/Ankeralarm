
#include "Settings.h"

void Settings::encoderPush() {
	this->anzeige->setZustand(new DisplayBrightness);
}

void Settings::encoderLeft() {
	this->anzeige->setZustand(new GPSInfo);
}

void Settings::encoderRight() {
	this->anzeige->setZustand(new Alarm);
}

void Settings::buttonReturn() {}

void Settings::getLCDOutput() {
	anzeige->lcd.print("Settings");
}

// Brightness
void DisplayBrightness::encoderPush() {
	this->anzeige->setZustand(new ChangeDisplayBrightness);
}

void DisplayBrightness::getLCDOutput() {
	anzeige->lcd.print("Brightness");
}

void DisplayBrightness::encoderLeft() {
	if (anzeige->props.alarmActive) {
		this->anzeige->setZustand(new AlarmRadius);
	} else {
		this->anzeige->setZustand(new UTCFactor);
	}
}

void DisplayBrightness::encoderRight() {
	this->anzeige->setZustand(new Timeout);
}

void DisplayBrightness::buttonReturn() {
	this->anzeige->setZustand(new Settings);
}

//Change Brightness
void ChangeDisplayBrightness::encoderPush() {
	// Save Brightness
	this->anzeige->props.displayBrighness = brightness;
	this->anzeige->props.writeEEPROM();
	this->anzeige->setZustand(new DisplayBrightness);
}

void ChangeDisplayBrightness::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%u", brightness);
	anzeige->print2Lines("ChangeBrightness", buf);
}

void ChangeDisplayBrightness::encoderLeft() {
	if (brightness < 5) {
		brightness = 5;
	}
	brightness -= 5;
	Properties::setDisplayBrightness(brightness);
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeDisplayBrightness::encoderRight() {
	if (brightness > 250) {
		brightness = 250;
	}
	brightness += 5;
	Properties::setDisplayBrightness(brightness);
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeDisplayBrightness::buttonReturn() {
	// Reset Brightness
	brightness = anzeige->props.displayBrighness;
	Properties::setDisplayBrightness(brightness);
	this->anzeige->setZustand(new DisplayBrightness);

}

ChangeDisplayBrightness::ChangeDisplayBrightness() {
	brightness = anzeige->props.displayBrighness;
}

// Timeout
void Timeout::encoderPush() {
	this->anzeige->setZustand(new ChangeTimeout);
}

void Timeout::getLCDOutput() {
	anzeige->lcd.print("Timeout");
}

void Timeout::encoderLeft() {
	this->anzeige->setZustand(new DisplayBrightness);
}

void Timeout::encoderRight() {
	this->anzeige->setZustand(new UTCFactor);
}

void Timeout::buttonReturn() {
	this->anzeige->setZustand(new Settings);
}

void ChangeTimeout::encoderPush() {
	// Save Timeout
	this->anzeige->props.displayTimeout = timeout;
}

void ChangeTimeout::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%u", timeout);
	anzeige->print2Lines("ChangeTimeout", buf);
}

void ChangeTimeout::encoderLeft() {
	timeout--;
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeTimeout::encoderRight() {
	timeout++;
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeTimeout::buttonReturn() {
	// Reset Timeout
	this->anzeige->props.setDisplayTimeout(this->anzeige->props.displayTimeout);
	this->anzeige->setZustand(new Timeout);
}

ChangeTimeout::ChangeTimeout() {
	timeout = anzeige->props.displayTimeout;
}


// UTC/Local Time
void UTCFactor::encoderPush() {
	this->anzeige->setZustand(new ChangeUTCFactor);
}

void UTCFactor::getLCDOutput() {
	anzeige->lcd.print("UTC/Local");
}

void UTCFactor::encoderLeft() {
	this->anzeige->setZustand(new Timeout);
}

void UTCFactor::encoderRight() {
	if (anzeige->props.alarmActive) {
		this->anzeige->setZustand(new AlarmRadius);
	} else {
		this->anzeige->setZustand(new DisplayBrightness);
	}
}

void UTCFactor::buttonReturn() {
	this->anzeige->setZustand(new Settings);
}

void ChangeUTCFactor::encoderPush() {
	anzeige->props.myGPS.getLastTimeStamp().setUTCFactor(factor);
	this->anzeige->setZustand(new UTCFactor);
}

void ChangeUTCFactor::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%i", factor);
	anzeige->print2Lines("ChangeUTCFactor", buf);
}

void ChangeUTCFactor::encoderLeft() {
	factor--;
	if (factor < -12) {
		factor = 12;
	}
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeUTCFactor::encoderRight() {
	factor++;
	if (factor > 12) {
		factor = -12;
	}
	anzeige->lcd.clear();
	this->getLCDOutput();
}

void ChangeUTCFactor::buttonReturn() {
	this->anzeige->setZustand(new UTCFactor);
}

ChangeUTCFactor::ChangeUTCFactor() {
	factor = anzeige->props.myGPS.getLastTimeStamp().getUTCFactor();
}

void AlarmRadius::encoderPush() {
	this->anzeige->setZustand(new ChangeAlarmRadius)
}

void AlarmRadius::encoderLeft() {
	this->anzeige->setZustand(new UTCFactor);
}

void AlarmRadius::encoderRight() {
	this->anzeige->setZustand(new DisplayBrightness);
}

void AlarmRadius::buttonReturn() {
	this->anzeige->setZustand(new Settings);
}

void AlarmRadius::getLCDOutput() {
	anzeige->print2Lines("Set Alarm Radius", "");
}

void ChangeAlarmRadius::encoderLeft() {
	if (radius < 5) {
		radius = 5;
	}
	radius -= 5;
	anzeige->lcd.clear();
	getLCDOutput();
}

void ChangeAlarmRadius::encoderPush() {
	this->anzeige->props.alarmRadius = radius;
	this->anzeige->setZustand(new AlarmRadius);
}

void ChangeAlarmRadius::encoderRight() {
	if (radius > 250) {
		radius = 250;
	}
	radius += 5;
	anzeige->lcd.clear();
	getLCDOutput();
}

void ChangeAlarmRadius::buttonReturn() {
	this->anzeige->setZustand(new AlarmRadius);
}

void ChangeAlarmRadius::getLCDOutput() {
	char buff[16];
	anzeige->print2Lines("ChangeAlarmRadius", sprintf(buff, "%u", radius));
}

ChangeAlarmRadius::ChangeAlarmRadius() {
	this->radius = anzeige->props.alarmRadius;
}