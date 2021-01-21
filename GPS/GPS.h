
#ifndef ANKERALARM_2_GPS_H
#define ANKERALARM_2_GPS_H

#include <vector>
#include <stdexcept>
#include "gpsData.h"
#include "../Positioning/Position.h"
#include "../Time.h"

using namespace std;

class GPS {

public:

    void update(gpsData data);

    unsigned short getGPSQuality();

    const Time &getLastTimeStamp() const;

    unsigned short getAccuracy() const;

    unsigned short getSatellitesAvailable() const;

    const Position &getCurrentPosition() const;

private:
    //    TinyGPS gps;
    Time lastTimeStamp = Time(0, 0, 0);
    Position currentPosition = Position(LatitudeDegree(0, 0), LongitudeDegree(0, 0));
    unsigned short accuracy;
    unsigned short satellitesAvailable;
};


#endif //ANKERALARM_2_GPS_H
