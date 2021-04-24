
#include "Settings.h"

void Settings::encoderPush() {
    this->anzeige->setZustand(new DisplayBrightness);
}

void Settings::encoderLeft() {
    this->anzeige->setZustand(new GPSInfo);
}

void Settings::encoderRight() {
    this->anzeige->setZustand(new Alarm);
}

void Settings::buttonReturn() {}

void Settings::getLCDOutput() {
    anzeige->lcd.print("Settings");
}

// Brightness
void DisplayBrightness::encoderPush() {
    this->anzeige->setZustand(new ChangeDisplayBrightness);
}

void DisplayBrightness::getLCDOutput() {
    anzeige->lcd.print("Brightness");
}

void DisplayBrightness::encoderLeft() {
    // TODO change Radius if alarm is active
    this->anzeige->setZustand(new UTCLocal);
}

void DisplayBrightness::encoderRight() {
    this->anzeige->setZustand(new Timeout);
}

void DisplayBrightness::buttonReturn() {
    this->anzeige->setZustand(new Settings);
}

//Change Brightness
void ChangeDisplayBrightness::encoderPush() {

}

void ChangeDisplayBrightness::getLCDOutput() {
    anzeige->lcd.print("ChangeBrightness");
}

void ChangeDisplayBrightness::encoderLeft() {
    brightness--;
}

void ChangeDisplayBrightness::encoderRight() {
    brightness++;
}

void ChangeDisplayBrightness::buttonReturn() {

}

ChangeDisplayBrightness::ChangeDisplayBrightness() {
    brightness = anzeige->props.displayBrighness;
}

// Timeout
void Timeout::encoderPush() {
    this->anzeige->setZustand(new ChangeTimeout);
}

void Timeout::getLCDOutput() {
    anzeige->lcd.print("Timeout");
}

void Timeout::encoderLeft() {
    this->anzeige->setZustand(new DisplayBrightness);
}

void Timeout::encoderRight() {
    this->anzeige->setZustand(new UTCLocal);
}

void Timeout::buttonReturn() {
    this->anzeige->setZustand(new Settings);
}

// ChangeTimeout
void ChangeTimeout::encoderPush() {

}

void ChangeTimeout::getLCDOutput() {
    anzeige->lcd.print("ChangeTimeout");
}

void ChangeTimeout::encoderLeft() {

}

void ChangeTimeout::encoderRight() {

}

void ChangeTimeout::buttonReturn() {

}

ChangeTimeout::ChangeTimeout() {
    timeout = anzeige->props.displayTimeout;
}


// UTC/Local Time
void UTCLocal::encoderPush() {
    // TODO Switch between UTC/Local Time
}

void UTCLocal::getLCDOutput() {
    anzeige->lcd.print("UTC/Local");
}

void UTCLocal::encoderLeft() {
    this->anzeige->setZustand(new Timeout);
}

void UTCLocal::encoderRight() {
    // TODO change Radius if alarm is active
    this->anzeige->setZustand(new DisplayBrightness);
}

void UTCLocal::buttonReturn() {
    this->anzeige->setZustand(new Settings);
}
