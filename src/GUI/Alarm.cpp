
#include "Alarm.h"

// Alarm
void Alarm::encoderLeft() {
	this->display->setZustand(new Settings);
}

void Alarm::encoderPush() {
	if (!this->display->props.alarmActive) {
		this->display->setZustand(new FindPosition);
	} else {
		this->display->setZustand(new AbortAlarm);
	}
}

void Alarm::encoderRight() {
	this->display->setZustand(new GPSInfo);
}

void Alarm::getLCDOutput() {
	display->lcd.print("Alarm");
}

// FindPosition

void FindPosition::getLCDOutput() {
	display->print2Lines("Please wait  0/4", "Find Position");
	const unsigned char size = 8;
	Position ary[size];
	Vector<Position> posCollection(ary);
	for (unsigned char i = 0; i < 8; ++i) {
		// wait for updated GPS Data
		bool update;
		do {
			update = display->props.updateGPSData();
		} while (!update);
		posCollection[i] = display->props.myGPS.getCurrentPosition();
		char buff[17];
		sprintf(buff, "Please wait  %u/4", (i + 1) / 2);
		display->print2Lines(buff, "Find Position");
	}
	display->props.centralPosition = getMedian(posCollection, size);
	display->setZustand(new SetRadius);
}

// SetRadius
void SetRadius::encoderLeft() {
	if (radius < 5) {
		radius = 5;
	}
	radius -= 5;
	display->lcd.clear();
	getLCDOutput();
}

void SetRadius::encoderPush() {
	this->display->props.alarmRadius = radius;
	this->display->setZustand(new AreUSure);
}

void SetRadius::encoderRight() {
	if (radius > 250) {
		radius = 250;
	}
	radius += 5;
	display->lcd.clear();
	getLCDOutput();
}

void SetRadius::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void SetRadius::getLCDOutput() {
	char buff[16];
	sprintf(buff, "%u", radius);
	display->print2Lines("Setze den Radius", buff);
}


// AreUSure
void AreUSure::encoderPush() {
	this->display->props.alarmActive = true;
	this->display->setZustand(new GPSInfo);
}

void AreUSure::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void AreUSure::getLCDOutput() {
	display->print2Lines("Bist du sicher?", "");
}


void AbortAlarm::encoderPush() {
	this->display->props.alarmActive = false;
	this->display->setZustand(new GPSInfo);
}

void AbortAlarm::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void AbortAlarm::getLCDOutput() {
	this->display->print2Lines("Alarm beenden", "Bist du sicher?");
}