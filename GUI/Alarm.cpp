
#include "Alarm.h"

// Alarm
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

}

// SetRadius
void SetRadius::encoderLeft() {

}

void SetRadius::encoderPush() {

}

void SetRadius::encoderRight() {

}

void SetRadius::buttonReturn() {

}

void SetRadius::getLCDOutput() {

}

// AreUSure
void AreUSure::encoderLeft() {

}

void AreUSure::encoderPush() {
    // TODO beginne mit Alarm
}

void AreUSure::encoderRight() {
}

void AreUSure::buttonReturn() {

}

void AreUSure::getLCDOutput() {

}


