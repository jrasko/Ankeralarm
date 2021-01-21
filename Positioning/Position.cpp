
#include "Position.h"
#include <cmath>

using namespace std;

long double Position::distanceTo(Position &p) {

    LatitudeDegree dlat = this->latitude - p.latitude;
    LongitudeDegree dlong = this->longitude - p.longitude;

    long double avgDeg = (latitude.getDegrees() + p.latitude.getDegrees() + latitude.getMinutes() / 60 + p.latitude.getMinutes() / 60) / 2;
    return sqrt(dlat.toMeters() * dlat.toMeters() + dlong.toMeters(avgDeg) * dlong.toMeters(avgDeg));
}

void Position::setPosition(LatitudeDegree &x, LongitudeDegree &y) {
    latitude = x;
    longitude = y;
}
