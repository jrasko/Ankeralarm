
#ifndef ANKERALARM_POSITION_H
#define ANKERALARM_POSITION_H


#include "LatitudeDegree.h"
#include "LongitudeDegree.h"

class Position {
public:

    Position(const LatitudeDegree &latitude, const LongitudeDegree &longitude) : latitude(latitude),
                                                                                 longitude(longitude) {}

    long double distanceTo(Position &p);

    void setPosition(LatitudeDegree &x, LongitudeDegree &y);

private:
    LatitudeDegree latitude;
    LongitudeDegree longitude;
};


#endif //ANKERALARM_POSITION_H
