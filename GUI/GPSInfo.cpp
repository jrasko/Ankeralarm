#include "GPSInfo.h"


// GPSInfo
void GPSInfo::encoderPush() {
	this->anzeige->setZustand(new Koordinaten);
}

void GPSInfo::encoderRight() {
	this->anzeige->setZustand(new Settings);
}

void GPSInfo::buttonReturn() {

}

void GPSInfo::encoderLeft() {
	this->anzeige->setZustand(new Alarm);
}

void GPSInfo::getLCDOutput() {
	anzeige->lcd.print("GPSInfo");
}

// Koordinaten
void Koordinaten::encoderPush() {
	this->anzeige->setZustand(new GPSInfo);
}

void Koordinaten::encoderRight() {
	this->anzeige->setZustand(new Satellites);
}

void Koordinaten::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void Koordinaten::encoderLeft() {
	if (anzeige->props.alarmActive) {
		this->anzeige->setZustand(new Radius);
	} else {
		this->anzeige->setZustand(new Time);
	}
}

void Koordinaten::getLCDOutput() {
	const vector<string> &lines = anzeige->props.myGPS.getCurrentPosition().toString();
	anzeige->print2Lines(lines[0].c_str(), lines[1].c_str());
}

//Sattelites
void Satellites::encoderPush() {

}

void Satellites::encoderRight() {
	this->anzeige->setZustand(new FixAge);
}


void Satellites::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void Satellites::encoderLeft() {
	this->anzeige->setZustand(new Koordinaten);
}

void Satellites::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%u", anzeige->props.myGPS.getSatellitesAvailable());
	anzeige->print2Lines("Satteliten", buf);
}

//FixAge
void FixAge::encoderPush() {

}

void FixAge::encoderRight() {
	this->anzeige->setZustand(new HDOP);
}


void FixAge::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void FixAge::encoderLeft() {
	this->anzeige->setZustand(new Satellites);
}

void FixAge::getLCDOutput() {
	char buf[16];
	sprintf(buf, "%lu", anzeige->props.myGPS.getFixAge());
	anzeige->print2Lines("Fix Age:", buf);
}
//HDOP


void HDOP::encoderPush() {

}

void HDOP::encoderRight() {
	this->anzeige->setZustand(new Time);
}


void HDOP::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void HDOP::encoderLeft() {
	this->anzeige->setZustand(new FixAge);
}

void HDOP::getLCDOutput() {
	char buf[16];
	dtostrf(anzeige->props.myGPS.getHDOP(), 4, 1, buf);
	anzeige->print2Lines("HDOP", buf);
}

// Time
void Time::encoderPush() {

}

void Time::encoderRight() {
	if (anzeige->props.alarmActive) {
		this->anzeige->setZustand(new Radius);
	} else {
		this->anzeige->setZustand(new Koordinaten);
	}
}

void Time::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void Time::encoderLeft() {
	this->anzeige->setZustand(new HDOP);
}

void Time::getLCDOutput() {
	const vector<string> &lines = anzeige->props.myGPS.getLastTimeStamp().toString();
	anzeige->print2Lines(lines[0].c_str(), lines[1].c_str());
}

void Radius::encoderPush() {

}

void Radius::encoderRight() {
	this->anzeige->setZustand(new Koordinaten);
}

void Radius::buttonReturn() {
	this->anzeige->setZustand(new GPSInfo);
}

void Radius::encoderLeft() {
	this->anzeige->setZustand(new Time);
}

void Radius::getLCDOutput() {
	char buff[16];
	char buff1[16];
	char buff2[16];
	dtostrf(anzeige->props.centralPosition.distanceTo(anzeige->props.myGPS.getCurrentPosition()), 6, 0, buff);
	sprintf(buff1, "Distance: %s", buff);
	sprintf(buff2, "max Radius: %u", anzeige->props.alarmRadius);
	anzeige->print2Lines(buff1, buff2);
}