
#include "Alarm.h"
#include "Ringer.h"

// Alarm
void Alarm::encoderLeft() {
	display->setZustand(new Ringer);
}

void Alarm::encoderPush() {
	if (display->props.alarmActive) {
		display->setZustand(new AbortAlarm);
		return;
	}
	display->setZustand(new FindPosition);
}

void Alarm::encoderRight() {
	display->setZustand(new GPSInfo);
}

void Alarm::getLCDOutput() {
	display->print2Lines("Alarm");
}

// FindPosition

void FindPosition::getLCDOutput() {
	display->print2Lines("Please wait  0/3", "Find Position");
	const unsigned char size = 2 * 3;
	long long latDeg = 0;
	long long lonDeg = 0;

	for (unsigned char i = 0; i < size; ++i) {
		// wait for updated GPS Data
		bool update;
		do {
			update = display->props.updateGPSData();
		} while (!update);
		if (i % 2 == 0) {
			latDeg += display->props.myGPS.getCurrentPosition().getLatitude().getDegrees();
			lonDeg += display->props.myGPS.getCurrentPosition().getLongitude().getDegrees();
		}
		char buff[17];
		sprintf(buff, "Please wait  %u/%u", (i + 1) / 2, size / 2);
		display->print2Lines(buff, "Find Position");
	}
	latDeg /= size / 2;
	lonDeg /= size / 2;

	display->props.centralPosition = Position(LatitudeDegree(latDeg), LongitudeDegree(lonDeg));
	display->setZustand(new SetRadius);
}

// SetRadius
void SetRadius::encoderLeft() {
	if (radius < 5) {
		radius = 5;
	}
	radius -= 5;
	getLCDOutput();
}

void SetRadius::encoderPush() {
	display->props.alarmRadius = radius;
	display->setZustand(new AreUSure);
}

void SetRadius::encoderRight() {
	if (radius > 250) {
		radius = 250;
	}
	radius += 5;
	getLCDOutput();
}

void SetRadius::buttonReturn() {
	display->setZustand(new GPSInfo);
}

void SetRadius::getLCDOutput() {
	display->print2Lines("Setze den Radius", radius);
}


// AreUSure
void AreUSure::encoderPush() {
	display->props.alarmActive = true;
	display->setZustand(new GPSInfo);
}

void AreUSure::buttonReturn() {
	display->setZustand(new GPSInfo);
}

void AreUSure::getLCDOutput() {
	display->print2Lines("Bist du sicher?");
}


void AbortAlarm::encoderPush() {
	display->props.alarmActive = false;
	display->setZustand(new GPSInfo);
}

void AbortAlarm::buttonReturn() {
	display->setZustand(new GPSInfo);
}

void AbortAlarm::getLCDOutput() {
	display->print2Lines("Alarm beenden", "Bist du sicher?");
}