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
	display->lcd.print("GPSInfo");
}

// Coordinates
void Coordinates::encoderPush() {
	this->display->setZustand(new GPSInfo);
}

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
	char buf[16];
	sprintf(buf, "%u", display->props.myGPS.getSatellitesAvailable());
	display->print2Lines("Satteliten", buf);
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
	char buf[16];
	sprintf(buf, "%lu", display->props.myGPS.getFixAge());
	display->print2Lines("Fix Age:", buf);
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
	char buf[16];
	dtostrf(display->props.myGPS.getHDOP(), 4, 1, buf);
	display->print2Lines("HDOP", buf);
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
	char buff1[16];
	char buff2[16];
	dtostrf(display->props.centralPosition.distanceTo(display->props.myGPS.getCurrentPosition()), 6, 0, buff);
	sprintf(buff1, "Distance: %s", buff);
	sprintf(buff2, "max Radius:  %03u", display->props.alarmRadius);
	display->print2Lines(buff1, buff2);
}