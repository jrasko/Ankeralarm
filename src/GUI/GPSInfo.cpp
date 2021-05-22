#include "GPSInfo.h"


// GPSInfo
void GPSInfo::encoderPush() {
	this->display->setZustand(new Coordinates);
}

void GPSInfo::encoderRight() {
	this->display->setZustand(new Settings);
}

void GPSInfo::encoderLeft() {
	this->display->setZustand(new Alarm);
}

void GPSInfo::getLCDOutput() {
	display->print2Lines("GPSInfo");
}

// Coordinates
void Coordinates::encoderRight() {
	this->display->setZustand(new Satellites);
}

void Coordinates::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void Coordinates::encoderLeft() {
	if (display->props.alarmActive) {
		this->display->setZustand(new Radius);
	} else {
		this->display->setZustand(new Time);
	}
}

void Coordinates::getLCDOutput() {
	const char *lines = display->props.myGPS.getCurrentPosition().toString();
	display->print2Lines(lines, &lines[17]);
	delete lines;
}

//Sattelites
void Satellites::encoderRight() {
	this->display->setZustand(new FixAge);
}


void Satellites::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void Satellites::encoderLeft() {
	this->display->setZustand(new Coordinates);
}

void Satellites::getLCDOutput() {
	display->print2Lines("Satteliten", display->props.myGPS.getSatellitesAvailable());
}

//FixAge
void FixAge::encoderRight() {
	this->display->setZustand(new HDOP);
}

void FixAge::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void FixAge::encoderLeft() {
	this->display->setZustand(new Satellites);
}

void FixAge::getLCDOutput() {
	display->print2Lines("Fix Age:", display->props.myGPS.getFixAge());
}

//HDOP
void HDOP::encoderRight() {
	this->display->setZustand(new Time);
}


void HDOP::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void HDOP::encoderLeft() {
	this->display->setZustand(new FixAge);
}

void HDOP::getLCDOutput() {
	display->print2Lines("HDOP", display->props.myGPS.getHDOP());
}

// Time
void Time::encoderRight() {
	if (display->props.alarmActive) {
		this->display->setZustand(new Radius);
	} else {
		this->display->setZustand(new Coordinates);
	}
}

void Time::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void Time::encoderLeft() {
	this->display->setZustand(new HDOP);
}

void Time::getLCDOutput() {
	const char *lines = display->props.myGPS.getLastTimeStamp().toString();
	display->print2Lines(lines, &lines[17]);
	delete lines;
}

void Radius::encoderRight() {
	this->display->setZustand(new Coordinates);
}

void Radius::buttonReturn() {
	this->display->setZustand(new GPSInfo);
}

void Radius::encoderLeft() {
	this->display->setZustand(new Time);
}

void Radius::getLCDOutput() {
	char buff[16];
	char buff1[17];
	char buff2[17];
	dtostrf(display->props.centralPosition.distanceTo(display->props.myGPS.getCurrentPosition()), 6, 1, buff);
	sprintf(buff1, "Distance: %s", buff);
	sprintf(buff2, "max Radius:  %3u", display->props.alarmRadius);
	display->print2Lines(buff1, buff2);
}