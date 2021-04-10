
#include "Alarm.h"

void Alarm::encoderLeft() {
    this->anzeige->setZustand(new Settings);
}

void Alarm::encoderPush() {

}

void Alarm::encoderRight() {
    this->anzeige->setZustand(new GPSInfo);
}

void Alarm::buttonReturn() {

}

void Alarm::getLCDOutput() {

}

