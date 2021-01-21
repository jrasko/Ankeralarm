
#include "LongitudeDegree.h"

#define toDEG 3.14159265/180

LongitudeDegree::LongitudeDegree(const std::string &koordString) {
    int deg = 0;
    long double min = 0;

    stringstream(koordString.substr(0, 3)) >> deg;
    stringstream(koordString.substr(3, 10)) >> min;

    char direction = koordString[12];


    if ((direction != 'W' && direction != 'E') || deg < 0 || deg > 180 || min < 0 || min >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    if (direction == 'W') {
        deg = -deg;
        min = -min;
    }
    this->degrees = deg;
    this->minutes = min;
}

LongitudeDegree::LongitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    long double min = 0;

    stringstream(koordString.substr(0, 3)) >> deg;
    stringstream(koordString.substr(3, 10)) >> min;


    if ((direction != 'W' && direction != 'E') || deg < 0 || deg > 180 || min < 0 || min >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    if (direction == 'W') {
        deg = -deg;
        min = -min;
    }
    this->degrees = deg;
    this->minutes = min;
}

LongitudeDegree::LongitudeDegree(char direction, int degrees, long double minutes) {
    if (direction != 'W' && direction != 'E' || degrees < 0 ||
        degrees > 180 || minutes < 0 || minutes >= 60) {
        throw std::invalid_argument("Invalid Argument!");
        return;
    }
    if (direction == 'W') {
        degrees = -degrees;
        minutes = -minutes;
    }
    this->degrees = degrees;
    this->minutes = minutes;
}

LongitudeDegree::LongitudeDegree(int degrees, long double minutes) {
    if (minutes <= -60 || minutes >= 60 || degrees < -180 || degrees > 180) {
        throw std::invalid_argument("Invalid Argument!");
    }
    this->degrees = degrees;
    this->minutes = minutes;
}

LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2) {
    int deg = 0;
    long double min = 0;

    min = dg1.minutes - dg2.minutes;
    if (min > 60) {
        min -= 60;
        deg++;
    }
    if (min < -60) {
        min += 60;
        deg--;
    }
    deg = deg + (dg2.degrees - dg1.degrees);

    if (deg > 180) {
        deg -= 360;
    }
    if (deg < -180) {
        deg += 360;
    }
    return LongitudeDegree(deg, min);
}

long double LongitudeDegree::toMeters(long double latdeg = 0) const {
    return abs(this->minutes + degrees * 60) * 1852.216 * cos(latdeg * toDEG);
}
