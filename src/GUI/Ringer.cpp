#include "Ringer.h"

void Ringer::encoderPush() {
	// Ringer aktiviert?
	if (display->props.ringerActive){
		display->setZustand(new AbortRinger);
		return;
	}
	display->props.ringerHours = 10;
	display->props.ringerMinutes = 0;
	display->setZustand(new SetHour);
}

void Ringer::encoderLeft() {
	display->setZustand(new Settings);
}

void Ringer::encoderRight() {
	display->setZustand(new Alarm);
}

void Ringer::getLCDOutput() {
	display->print2Lines("Ringer");
}

void SetHour::encoderPush() {
	display->props.ringerHours = hour;
	display->setZustand(new SetMinute);
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
	display->props.ringerMinutes = minute;
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

void AbortRinger::encoderPush() {
	display->props.ringerActive = false;
	display->setZustand(new GPSInfo);
}

void AbortRinger::buttonReturn() {
	display->setZustand(new GPSInfo);
}

void AbortRinger::getLCDOutput() {
	display->print2Lines("Stop Ringer", "Are you sure?");
}
