
#include "LatitudeDegree.h"

using namespace std;

LatitudeDegree::LatitudeDegree(const std::string &koordString) {
    int deg = 0;
    long double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;

    char direction = koordString[11];

    if ((direction != 'N' && direction != 'S') || deg < 0 || deg > 90 || min < 0 || min >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        return ;
    }
    long double jdeg = deg + (min / 60);
    if (direction == 'S') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}

LatitudeDegree::LatitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    long double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;
    if ((direction != 'N' && direction != 'S') || deg < 0 || deg > 90 || min < 0 || min >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        return ;
    }
    long double jdeg = deg + (min / 60);
    if (direction == 'S') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}

LatitudeDegree::LatitudeDegree(char direction, int degrees, long double minutes) {
    if (direction != 'N' && direction != 'S' || degrees < 0 ||
        degrees > 90 || minutes < 0 || minutes >= 60) {
        //throw std::invalid_argument("Invalid Argument!");
        return ;
    }
    long double deg = degrees + (minutes / 60);
    if (direction == 'S') {
        deg = -deg;
    }
    this->degrees = deg;
}


LatitudeDegree::LatitudeDegree(int degrees, long double minutes) {
    if (minutes <= -60 || minutes >= 60 || degrees < -90 || degrees > 90) {
        //throw std::invalid_argument("Invalid Argument!");
        return ;
    }
    this->degrees = degrees + (minutes / 60);
}

LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
    return LatitudeDegree(dg1.degrees - dg2.degrees);
}

//Returns Distance to Point Zero
long double LatitudeDegree::toMeters() const {
    return abs(degrees) * 60 * 1852.216;
}


LatitudeDegree::LatitudeDegree(long double degrees) {
    if (degrees < -90 || degrees > 90) {
        //throw std::invalid_argument("Invalid Argument!");
        return ;
    }
    this->degrees = degrees;

}


