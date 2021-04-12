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
    this->anzeige->setZustand(new Time);

}

void Koordinaten::getLCDOutput() {
    anzeige->lcd.print("Koordinaten");
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
     anzeige->lcd.print("Satelliten");
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
 anzeige->lcd.print("FixAge");
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
    this->anzeige->lcd.print("HDOP");
}

// Time
void Time::encoderPush() {

}

void Time::encoderRight() {
    this->anzeige->setZustand(new Koordinaten);
}

void Time::buttonReturn() {
    this->anzeige->setZustand(new GPSInfo);
}

void Time::encoderLeft() {
    this->anzeige->setZustand(new HDOP);
}

void Time::getLCDOutput() {
 anzeige->lcd.print("Time");
}