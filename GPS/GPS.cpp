#include "GPS.h"


void GPS::update(gpsData data) {
    vector<string> v = data.getData();
    if (v.size()!= 13 && v.size() != 15){
        throw invalid_argument("Fehler beim Vektor");
    }
    if (v.size() == 13) {
        //GPRMC
        lastTimeStamp = Time(v[1]);
        LatitudeDegree lat(v[3], v[4][0]);
        LongitudeDegree lon(v[5], v[6][0]);

    } else {
        //GPGGA

        lastTimeStamp = Time(v[1]);
        LatitudeDegree lat(v[2], v[3][0]);
        LongitudeDegree lon(v[4], v[5][0]);
        currentPosition = Position(lat, lon);

        stringstream(v[6]) >> accuracy;
        stringstream(v[7]) >> satellitesAvailable;
    }

}

unsigned short GPS::getGPSQuality() {

    return 0;
}

const Time &GPS::getLastTimeStamp() const {
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

