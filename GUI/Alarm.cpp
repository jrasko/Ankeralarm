
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

void Alarm::buttonReturn() {

}

void Alarm::getLCDOutput() {
	anzeige->lcd.print("Alarm");
}

// FindPosition
void FindPostition::encoderLeft() {

}

void FindPostition::encoderPush() {

}

void FindPostition::encoderRight() {
}

void FindPostition::buttonReturn() {

}

void FindPostition::getLCDOutput() {
	// TODO 3 GPS Anfragen mit zeitlichem Timeout + mitteln
	anzeige->print2Lines("Please wait", "Find Position");
	/*
	vector <Position> posCollection;
	posCollection.reserve(4);
	for (int i = 0; i < 4; ++i) {
		// wait for updated GPS Data
		bool update;
		do {
			update = anzeige->props.updateGPSData();
		} while (!update);
		posCollection.push_back(anzeige->props.myGPS.getCurrentPosition());
	}
	anzeige->props.centralPosition = getMedian(posCollection);*/
	anzeige->props.centralPosition = anzeige->props.myGPS.getCurrentPosition();
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
void AreUSure::encoderLeft() {

}

void AreUSure::encoderPush() {
	this->anzeige->props.alarmActive = true;
	this->anzeige->setZustand(new GPSInfo);
}

void AreUSure::encoderRight() {
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

void AbortAlarm::encoderLeft() {}

void AbortAlarm::encoderRight() {}

void AbortAlarm::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void AbortAlarm::getLCDOutput() {
	this->anzeige->print2Lines("Alarm beenden", "Bist du sicher?");
}