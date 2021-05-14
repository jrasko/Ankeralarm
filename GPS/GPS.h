
#ifndef ANKERALARM_2_GPS_H
#define ANKERALARM_2_GPS_H

#include <Arduino.h>
#include <Vector.h>
#include "gpsData.h"
#include "../Positioning/Position.h"
#include "DateTime.h"

class GPS {

public:
	bool update(const gpsData &data);

	unsigned short getGPSQuality() const;

	const DateTime &getLastTimeStamp() const;

	double getHDOP() const;

	unsigned long getFixAge() const;

	unsigned short getSatellitesAvailable() const;

	const Position &getCurrentPosition() const;


private:
	DateTime lastTimeStamp;
	Position currentPosition = Position();
	unsigned short gpsStatus = 0;
	double HDOP = 50.0;
	unsigned short satellitesAvailable = 0;
	unsigned long lastInputTime = 0;
};


#endif //ANKERALARM_2_GPS_H
