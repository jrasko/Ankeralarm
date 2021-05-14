
#include "Alarm.h"

// Alarm
void Alarm::encoderLeft() {
	this->anzeige->setZustand(new Settings);
}

void Alarm::encoderPush() {
	if (!this->anzeige->props.alarmActive) {
		this->anzeige->setZustand(new FindPostition);
	} else {
		this->anzeige->setZustand(new AbortAlarm);
	}
}

void Alarm::encoderRight() {
	this->anzeige->setZustand(new GPSInfo);
}

void Alarm::getLCDOutput() {
	anzeige->lcd.print("Alarm");
}

// FindPosition

void FindPostition::getLCDOutput() {
	anzeige->print2Lines("Please wait  0/4", "Find Position");
	const unsigned char size = 8;
	Position ary[size];
	Vector<Position> posCollection(ary);
	for (unsigned char i = 0; i < 8; ++i) {
		// wait for updated GPS Data
		bool update;
		do {
			update = anzeige->props.updateGPSData();
		} while (!update);
		posCollection[i] = anzeige->props.myGPS.getCurrentPosition();
		char buff[17];
		sprintf(buff, "Please wait  %u/4", (i + 1) / 2);
		anzeige->print2Lines(buff, "Find Position");
	}
	anzeige->props.centralPosition = getMedian(posCollection, size);
	anzeige->setZustand(new SetRadius);
}

// SetRadius
void SetRadius::encoderLeft() {
	if (radius < 5) {
		radius = 5;
	}
	radius -= 5;
	anzeige->lcd.clear();
	getLCDOutput();
}

void SetRadius::encoderPush() {
	this->anzeige->props.alarmRadius = radius;
	this->anzeige->setZustand(new AreUSure);
}

void SetRadius::encoderRight() {
	if (radius > 250) {
		radius = 250;
	}
	radius += 5;
	anzeige->lcd.clear();
	getLCDOutput();
}

void SetRadius::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void SetRadius::getLCDOutput() {
	char buff[16];
	sprintf(buff, "%u", radius);
	anzeige->print2Lines("Setze den Radius", buff);
}


// AreUSure
void AreUSure::encoderPush() {
	this->anzeige->props.alarmActive = true;
	this->anzeige->setZustand(new GPSInfo);
}

void AreUSure::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void AreUSure::getLCDOutput() {
	anzeige->print2Lines("Bist du sicher?", "");
}


void AbortAlarm::encoderPush() {
	this->anzeige->props.alarmActive = false;
	this->anzeige->setZustand(new GPSInfo);
}

void AbortAlarm::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void AbortAlarm::getLCDOutput() {
	this->anzeige->print2Lines("Alarm beenden", "Bist du sicher?");
}