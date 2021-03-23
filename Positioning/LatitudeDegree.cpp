
#include "LatitudeDegree.h"

using namespace std;

LatitudeDegree::LatitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    double min = 0;
    stringstream(koordString.substr(0, 2)) >> deg;
    stringstream(koordString.substr(2, 10)) >> min;

    double jdeg = min / 60.0 + deg;
    if (direction == 'S') {
        jdeg = -jdeg;
    }
    degrees = jdeg;
}


LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
    return LatitudeDegree(dg1.degrees - dg2.degrees);
}

//Returns Distance to Point Zero
double LatitudeDegree::toMeters() const {
    const double mile = degrees < 0 ? -1852.216 : 1852.216;
    return degrees * 60 * mile;
}


LatitudeDegree::LatitudeDegree(double deg) {
    degrees = deg;
}


