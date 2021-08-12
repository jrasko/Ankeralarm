#include "Ringer.h"

void Ringer::encoderPush() {
	// Ringer aktiviert?
	this->display->setZustand(new SetHour);
}

void Ringer::encoderLeft() {
	this->display->setZustand(new Settings);
}

void Ringer::encoderRight() {
	this->display->setZustand(new Alarm);
}

void Ringer::getLCDOutput() {
	display->print2Lines("Ringer");
}

void SetHour::encoderPush() {
	display->print2Lines("Minuten");
}

void SetHour::encoderLeft() {
	if (hour < 1) {
		hour = 1;
	}
	hour--;
	getLCDOutput();
}

void SetHour::encoderRight() {
	if (hour > 22) {
		hour = 22;
	}
	hour ++;
	getLCDOutput();
}

void SetHour::buttonReturn() {
	display->setZustand(new Ringer);
}

void SetHour::getLCDOutput() {
	display->print2Lines("Hours:" , hour);
}

void SetMinute::encoderPush() {
	display->setZustand(new AreUSureRinger);
}

void SetMinute::encoderLeft() {
	if (minute < 5) {
		minute = 5;
	}
	minute -= 5;
	getLCDOutput();
}

void SetMinute::encoderRight() {
	if (minute > 50) {
		minute = 50;
	}
	minute += 5;
	getLCDOutput();
}

void SetMinute::buttonReturn() {
	display->setZustand(new SetHour);
}

void SetMinute::getLCDOutput() {
	display->print2Lines("Minutes", minute);
}

void AreUSureRinger::encoderPush() {
	display->props.ringerActive = true;
	display->setZustand(new GPSInfo);
}

void AreUSureRinger::buttonReturn() {
	display->setZustand(new SetMinute);
}

void AreUSureRinger::getLCDOutput() {
	display->print2Lines("Are you sure?");
}
