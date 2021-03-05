
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

    void update(const gpsData &data);

    unsigned short getGPSQuality() const;

    const DateTime &getLastTimeStamp() const;

    unsigned short getAccuracy() const;

    unsigned short getSatellitesAvailable() const;

    const Position &getCurrentPosition() const;



private:
    //    Maybe deprecated
    //    TinyGPS gps;
    DateTime lastTimeStamp;
    Position currentPosition = Position(LatitudeDegree(0, 0), LongitudeDegree(0, 0));
    unsigned short accuracy = -1;
    unsigned short satellitesAvailable = 0;
};



#endif //ANKERALARM_2_GPS_H
