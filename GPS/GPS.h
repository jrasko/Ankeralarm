
#ifndef ANKERALARM_2_GPS_H
#define ANKERALARM_2_GPS_H

#include <vector>
#include <stdexcept>
#include "gpsData.h"
#include "../Positioning/Position.h"
#include "DateTime.h"

using namespace std;

class GPS {

public:


    void update(gpsData data);

    unsigned short getGPSQuality();

    const DateTime &getLastTimeStamp() const;

    unsigned short getAccuracy() const;

    unsigned short getSatellitesAvailable() const;

    const Position &getCurrentPosition() const;

private:
    //    Maybe deprecated
    //    TinyGPS gps;
    DateTime lastTimeStamp;
    Position currentPosition = Position(LatitudeDegree(0, 0), LongitudeDegree(0, 0));
    unsigned short accuracy;
    unsigned short satellitesAvailable;
};


#endif //ANKERALARM_2_GPS_H
