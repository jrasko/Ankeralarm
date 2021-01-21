
#include "LatitudeDegree.h"

using namespace std;

LatitudeDegree::LatitudeDegree(const std::string& koordString) {
    int deg = 0;
    long double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;

    char direction = koordString[11];

    if ((direction != 'N' && direction != 'S') || deg < 0 || deg > 90 || min < 0 || min >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    if (direction == 'S') {
        deg = -deg;
        min = -min;
    }
    this->degrees = deg;
    this->minutes = min;
}

LatitudeDegree::LatitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    long double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;
    if ((direction != 'N' && direction != 'S') || deg < 0 || deg > 90 || min < 0 || min >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    if (direction == 'S') {
        deg = -deg;
        min = -min;
    }
    this->degrees = deg;
    this->minutes = min;
}

LatitudeDegree::LatitudeDegree(char direction, int degrees, long double minutes) {
    if (direction != 'N' && direction != 'S' || degrees < 0 ||
        degrees > 90 || minutes < 0 || minutes >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    if (direction == 'S') {
        degrees = -degrees;
        minutes = -minutes;
    }
    this->degrees = degrees;
    this->minutes = minutes;
}


LatitudeDegree::LatitudeDegree(int degrees, long double minutes) {
    if (minutes <= -60 || minutes >= 60 || degrees < -90 || degrees > 90) {
        throw std::invalid_argument("Invalid Argument!");
    }
    this->degrees = degrees;
    this->minutes = minutes;
}

LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
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

    if (deg > 90) {
        deg = 180 - deg;
    }
    if (deg < -90) {
        deg = -180 - deg;
    }
    return LatitudeDegree(deg, min);
}

//Returns Distance to Point Zero
long double LatitudeDegree::toMeters() const {
    return abs((this->minutes + degrees * 60) * 1852.216);
}


