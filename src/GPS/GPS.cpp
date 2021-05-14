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
 * Calulates a number as indicator for the Quality of the GPS Signal
 * @return 0 -> No GPS Data available, 1 -> No Fix, 2-6 -> Indicator for the Quality, 2 is the badest and 5 the best Quality
 */
unsigned char GPS::getGPSQuality() const {
	const unsigned long maxFixAge = 30 * 1000; //30 secs
	if (lastInputTime == 0) {
		// Von Anfang an keine validen Daten vorhanden
		return 0;
	}
	unsigned long currentFixAge = millis() - lastInputTime;
	if (gpsStatus == 0 || currentFixAge >= maxFixAge) {
		// Seit einiger zeit keine validen Daten vorhanden, verlust des fixes
		return 1;
	}
	if (currentFixAge >= 12 * 1000 || satellitesAvailable <= 3 || HDOP >= 10) {
		return 2;
	}
	//FixAge ist zwischen 10 und 12
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

