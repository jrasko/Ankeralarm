#include "GPS.h"

/**
 * Updates the Attributes of the GPS Object
 * @param data includes a vector of strings which is build from the raw GPS Data
 */
void GPS::update(const gpsData &data) {
    vector<string> v = data.getData();
    if (v.size() != 13 && v.size() != 15) {
        return ;
    }    
    if (v[0]=="$GPGGA") {
        //GPRMC
        lastTimeStamp = DateTime(v[1], v[9]);
        LatitudeDegree lat(v[3], v[4][0]);
        LongitudeDegree lon(v[5], v[6][0]);
        currentPosition = Position(lat,lon);

    } else if(v[0]=="$GPRMC"){
        //GPGGA
        LatitudeDegree lat(v[2], v[3][0]);
        LongitudeDegree lon(v[4], v[5][0]);
        currentPosition = Position(lat, lon);

        stringstream(v[6]) >> accuracy;
        stringstream(v[7]) >> satellitesAvailable;
    }
}

/**
 * Calulates a number as indicator for the Quality of the GPS Signal
 * @return 0 -> No GPS Data available, 1 -> No Fix, 2-5 -> Indicator for the Quality, 2 is the badest and 5 the best Quality
 */
unsigned short GPS::getGPSQuality() const {
    unsigned short fixAge;
    //Test auf eingehende Daten
    //Test auf letzten Timestamp
    if (accuracy <= 100)
        return 0;
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

