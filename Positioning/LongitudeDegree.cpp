
#include "LongitudeDegree.h"

#define toDEG 3.14159265/180
using namespace std;

LongitudeDegree::LongitudeDegree(const std::string &koordString, char direction) {
    int deg = 0;
    float min = 0;

    stringstream(koordString.substr(0, 3)) >> deg;
    stringstream(koordString.substr(3, 10)) >> min;


    float jdeg = deg + (min / 60);
    if (direction == 'W') {
        jdeg = -jdeg;
    }
    this->degrees = jdeg;
}

LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2) {
    return LongitudeDegree(dg1.degrees - dg2.degrees);
}

float LongitudeDegree::toMeters(float latdeg = 0) const {
    return std::abs(degrees) * 60 * 1852.216 * cos(latdeg * toDEG);
}

LongitudeDegree::LongitudeDegree(float degrees) {
    this->degrees = degrees;
}
