#include "GPS.h"
#include <Arduino.h>

/**
 * Updates the Attributes of the GPS Object
 * @param data includes a vector of strings which is build from the raw GPS Data
 */
void GPS::update(const gpsData &data) {
    vector<string> v = data.getData();
    if (!data.isValid() ||( v.size() != 13 && v.size() != 15)) {
        return;
    }

    if (v[0] == "$GPRMC") {
        //GPRMC
        lastTimeStamp = DateTime(v[1], v[9]);
        LatitudeDegree lat(v[3], v[4][0]);
        LongitudeDegree lon(v[5], v[6][0]);
        currentPosition = Position(lat, lon);

    } else if (v[0] == "$GPGGA") {
        //GPGGA
        LatitudeDegree lat(v[2], v[3][0]);
        LongitudeDegree lon(v[4], v[5][0]);
        currentPosition = Position(lat, lon);
        stringstream(v[6]) >> accuracy;
        stringstream(v[7]) >> satellitesAvailable;
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
    if (currentFixAge >= maxFixAge) {
        // Seit einiger zeit keine validen Daten vorhanden, verlust des fixes
        return 1;
    }
    if (currentFixAge >= 20 * 1000 || satellitesAvailable <= 3 || accuracy >= 500) {
        return 2;
    }

    if (currentFixAge >= 15) {
        return 3;
    }
    if (currentFixAge >= 12) {
        if (accuracy < 100) {
            return 5;
        }
        if (accuracy < 250) {
            return 4;
        }
        return 3;
    }
    //FixAge ist zwischen 10 und 12
    if (accuracy < 100) {
        return 6;
    }
    if (accuracy < 250) {
        return 5;
    }
    return 4;
}

const DateTime &GPS::getLastTimeStamp() const {
    return lastTimeStamp;
}

unsigned short GPS::getAccuracy() const {
    return accuracy;
}

unsigned short GPS::getSatellitesAvailable() const {
    return satellitesAvailable;
}

const Position &GPS::getCurrentPosition() const {
    return currentPosition;
}

