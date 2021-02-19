
#ifndef ANKERALARM_POSITION_H
#define ANKERALARM_POSITION_H


#include "LatitudeDegree.h"
#include "LongitudeDegree.h"
#include <cmath>
#include <vector>

using namespace std;
class Position {
public:

    Position(const LatitudeDegree &latitude, const LongitudeDegree &longitude) : latitude(latitude),
                                                                                 longitude(longitude) {}
    friend Position getMedian(const vector<Position> &p);

    long double distanceTo(const Position &p) const;

    void setPosition(LatitudeDegree &x, LongitudeDegree &y);

private:
    LatitudeDegree latitude;
    LongitudeDegree longitude;
};


#endif //ANKERALARM_POSITION_H
