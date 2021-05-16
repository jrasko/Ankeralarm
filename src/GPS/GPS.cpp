#include "GPS.h"

/**
 * Updates the Attributes of the GPS Object
 * @param data includes a vector of strings which is build from the raw GPS Data
 */
bool GPS::update(const gpsData &data) {
	const String *v = data.getData();
	bool hasUpdated = false;
	if (!data.isValid()) {
		return false;
	}
	if (v[0] == "$GPRMC") {
		//GPRMC
		if (v[2] != "A"){
			//invalid data
			return false;
		}
		lastTimeStamp.updateTime(v[1]);
		lastTimeStamp.updateDate(v[9]);
		LatitudeDegree lat(v[3], v[4][0]);
		LongitudeDegree lon(v[5], v[6][0]);
		currentPosition = Position(lat, lon);
		hasUpdated = true;
	} else if (v[0] == "$GPGGA") {
		//GPGGA
		gpsStatus = v[6].toInt();
		if (gpsStatus == 0){
			// invalid data
			return false;
		}
		lastTimeStamp.updateTime(v[1]);
		LatitudeDegree lat(v[2], v[3][0]);
		LongitudeDegree lon(v[4], v[5][0]);
		currentPosition = Position(lat, lon);

		satellitesAvailable = v[7].toInt();
		HDOP = v[8].toDouble();
		hasUpdated = true;
	}
	lastInputTime = millis();
	return hasUpdated;
}

/**
 * Calculates a number as indicator for the Quality of the GPS Signal
 * @return 0 -> No GPS Data available, 1 -> No Fix, 2-4 -> Indicator for the Quality, 2 is the badest and 4 the best Quality
 */
unsigned char GPS::getGPSQuality() const {
	const unsigned long maxFixAge = 30 * 1000; //30 secs
	const unsigned long currentFixAge = millis() - lastInputTime;

	if (lastInputTime == 0 || currentFixAge >= 90 * 1000) {
		// No valid data available from the beginning or 2 mins no Fix
		return 0;
	}
	if (gpsStatus == 0 || currentFixAge >= maxFixAge) {
		// No valid data available for some time, loss of the fix
		return 1;
	}
	if (currentFixAge >= 12 * 1000 || satellitesAvailable <= 3 || HDOP >= 10) {
		return 2;
	}
	//FixAge is under 12 seconds
	if (HDOP < 1.1) {
		return 4;
	}
	if (HDOP < 2.0) {
		return 3;
	}
	return 2;
}

DateTime &GPS::getLastTimeStamp() {
	return lastTimeStamp;
}

double GPS::getHDOP() const {
	return HDOP;
}

unsigned char GPS::getSatellitesAvailable() const {
	return satellitesAvailable;
}

const Position &GPS::getCurrentPosition() const {
	return currentPosition;
}

unsigned long GPS::getFixAge() const {
	return millis() - lastInputTime;
}

