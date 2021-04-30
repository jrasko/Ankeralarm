#include "GPS.h"

/**
 * Updates the Attributes of the GPS Object
 * @param data includes a vector of strings which is build from the raw GPS Data
 */
void GPS::update(const gpsData &data) {
     vector<string> v = data.getData();
    if (!data.isValid() || (v.size() != 13 && v.size() != 15)) {
        return;
    }
    if (v[0] == "$GPRMC") {
        //GPRMC
        lastTimeStamp.updateTime(v[1]);
        lastTimeStamp.updateDate(v[9]);
        LatitudeDegree lat(v[3], v[4][0]);
        LongitudeDegree lon(v[5], v[6][0]);
        currentPosition = Position(lat, lon);
    } else if (v[0] == "$GPGGA") {
        //GPGGA
        lastTimeStamp.updateTime(v[1]);
        LatitudeDegree lat(v[2], v[3][0]);
        LongitudeDegree lon(v[4], v[5][0]);
        currentPosition = Position(lat, lon);

        gpsStatus = String(v[6].c_str()).toInt();
        satellitesAvailable = String(v[7].c_str()).toInt();
        HDOP = String(v[8].c_str()).toDouble();
    }
    lastInputTime = millis(); 
}

/**
 * Calulates a number as indicator for the Quality of the GPS Signal
 * @return 0 -> No GPS Data available, 1 -> No Fix, 2-6 -> Indicator for the Quality, 2 is the badest and 5 the best Quality
 */
unsigned short GPS::getGPSQuality() const {
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
    if (currentFixAge >= 20 * 1000 || satellitesAvailable <= 3 || HDOP >= 10) {
        return 2;
    }

    if (currentFixAge >= 15 * 1000) {
        return 3;
    }
    if (currentFixAge >= 12 * 1000) {
        if (HDOP < 1.0) {
            return 5;
        }
        if (HDOP < 2.5) {
            return 4;
        }
        return 3;
    }
    //FixAge ist zwischen 10 und 12
    if (HDOP < 1.0) {
        return 6;
    }
    if (HDOP < 2.5) {
        return 5;
    }
    return 4;
}

const DateTime &GPS::getLastTimeStamp() const {
    return lastTimeStamp;
}

double GPS::getHDOP() const {
    return HDOP;
}

unsigned short GPS::getSatellitesAvailable() const {
    return satellitesAvailable;
}

const Position &GPS::getCurrentPosition() const {
    return currentPosition;
}

unsigned long GPS::getFixAge() const {
    return millis()-lastInputTime;
}

