
#include "LongitudeDegree.h"

#define toDEG 3.14159265/180
using namespace std;
LongitudeDegree::LongitudeDegree(const std::string &koordString) {
    int deg = 0;
    long double min = 0;

    stringstream(koordString.substr(0, 3)) >> deg;
    stringstream(koordString.substr(3, 10)) >> min;

    char direction = koordString[12];


    if ((direction != 'W' && direction != 'E') || deg < 0 || deg > 180 || min < 0 || min >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        dirty = true;
        return ;
    }
    long double jdeg = deg + (min / 60);
    if (direction == 'W') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}

LongitudeDegree::LongitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    long double min = 0;

    stringstream(koordString.substr(0, 3)) >> deg;
    stringstream(koordString.substr(3, 10)) >> min;


    if ((direction != 'W' && direction != 'E') || deg < 0 || deg > 180 || min < 0 || min >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        dirty = true;
        return ;
    }
    long double jdeg = deg + (min / 60);
    if (direction == 'W') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}

LongitudeDegree::LongitudeDegree(char direction, int degrees, long double minutes) {
    if (direction != 'W' && direction != 'E' || degrees < 0 ||
        degrees > 180 || minutes < 0 || minutes >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        dirty = true;
        return ;
    }
    long double deg = degrees + (minutes / 60);
    if (direction == 'W') {
        deg = -deg;
    }
    this->degrees = deg;
}

LongitudeDegree::LongitudeDegree(int degrees, long double minutes) {
    if (minutes <= -60 || minutes >= 60 || degrees < -180 || degrees > 180) {
        //throw std::invalid_argument("Invalid Argument!");
        dirty = true;
        return ;
    }
    this->degrees = degrees + (minutes / 60);
}

LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2) {
    return LongitudeDegree(dg1.degrees - dg2.degrees);
}

long double LongitudeDegree::toMeters(long double latdeg = 0) const {
    return abs(degrees) * 60 * 1852.216 * cos(latdeg * toDEG);
}

LongitudeDegree::LongitudeDegree(long double degrees) {
    if (degrees < -180 || degrees > 180) {
        //throw std::invalid_argument("Invalid Argument!");
        dirty = true;
        return ;
    }
    this->degrees = degrees;
}
