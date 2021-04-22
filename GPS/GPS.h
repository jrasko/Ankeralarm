
#ifndef ANKERALARM_2_GPS_H
#define ANKERALARM_2_GPS_H

#include <vector>
#include "gpsData.h"
#include "../Positioning/Position.h"
#include "DateTime.h"

using namespace std;

class GPS {

public:

    void update(const gpsData &data);

    unsigned short getGPSQuality() const;

    const DateTime &getLastTimeStamp() const;

    double getHDOP() const;

    unsigned long getFixAge() const;

    unsigned short getSatellitesAvailable() const;

    const Position &getCurrentPosition() const;


private:
    //    Maybe deprecated
    //    TinyGPS gps;
    DateTime lastTimeStamp;
    Position currentPosition = Position(LatitudeDegree(0), LongitudeDegree(0));
    unsigned short gpsStatus = 0;
    double HDOP = 50;
    unsigned short satellitesAvailable = 0;
    unsigned long lastInputTime = 0;
};


#endif //ANKERALARM_2_GPS_H
