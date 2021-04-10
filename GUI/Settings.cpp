
#include "Settings.h"

void Settings::encoderPush() {

}

void Settings::encoderLeft() {
    this->anzeige->setZustand(new GPSInfo);
}

void Settings::encoderRight() {
    this->anzeige->setZustand(new Alarm);
}

void Settings::buttonReturn() {}

void Settings::getLCDOutput() {

}
