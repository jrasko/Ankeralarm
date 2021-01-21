#include "GPS.h"

/**
 * Updates the Attributes of the GPS Object
 * @param data includes a vector of strings which is build from the raw GPS Data
 */
void GPS::update(gpsData data) {
    vector<string> v = data.getData();
    if (v.size() != 13 && v.size() != 15) {
        throw invalid_argument("Invalid gpsData Object!");
    }
    if (v[0]=="$GPGGA") {
        //GPRMC
        lastTimeStamp = DateTime(v[1], v[9]);
        LatitudeDegree lat(v[3], v[4][0]);
        LongitudeDegree lon(v[5], v[6][0]);

    } else if(v[0]=="$GPRMC"){
        //GPGGA
        LatitudeDegree lat(v[2], v[3][0]);
        LongitudeDegree lon(v[4], v[5][0]);
        currentPosition = Position(lat, lon);

        stringstream(v[6]) >> accuracy;
        stringstream(v[7]) >> satellitesAvailable;
    } else{
        throw invalid_argument("Invalid gpsData Object!");
    }

}
/**
 * TODO
 * @return a number as indicator for the Quality of the GPS Signal
 */
unsigned short GPS::getGPSQuality() {

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

