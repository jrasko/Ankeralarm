
#include "LatitudeDegree.h"

using namespace std;

LatitudeDegree::LatitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    long double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;

    long double jdeg = deg + (min / 60);
    if (direction == 'S') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}


LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
    return LatitudeDegree(dg1.degrees - dg2.degrees);
}

//Returns Distance to Point Zero
long double LatitudeDegree::toMeters() const {
    return std::abs(degrees) * 60 * 1852.216;
}


LatitudeDegree::LatitudeDegree(long double degrees) {
    if (degrees < -90 || degrees > 90) {
        //throw std::invalid_argument("Invalid Argument!");
        return;
    }
    this->degrees = degrees;

}


