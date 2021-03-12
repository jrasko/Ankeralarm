
#include <iomanip>
#include "Position.h"

/**
 * Calculates the distance between this Object and p in metres
 * @param p the Positon which is compared with this pos
 * @return the distance from Position to p in meters
 */
float Position::distanceTo(const Position &p) const {

    LatitudeDegree dlat = this->latitude - p.latitude;
    LongitudeDegree dlong = this->longitude - p.longitude;

    float avgDeg = (latitude.getDegrees() + p.latitude.getDegrees()) / 2;
    return sqrt(dlat.toMeters() * dlat.toMeters() + dlong.toMeters(avgDeg) * dlong.toMeters(avgDeg));
}

void Position::setPosition(LatitudeDegree &x, LongitudeDegree &y) {
    latitude = x;
    longitude = y;
}

Position getMedian(const vector<Position> &p) {
    float latDeg = 0;
    float lonDeg = 0;

    for (const auto &i : p) {
        latDeg += i.latitude.getDegrees();
        lonDeg += i.longitude.getDegrees();
    }
    latDeg /= p.size();
    lonDeg /= p.size();

    return {LatitudeDegree(latDeg), LongitudeDegree(lonDeg)};
}

string Position::toString() const {
    string output;

    double lat = (double) latitude.getDegrees();
    unsigned short latDegree, latMinutes, latSeconds;
    char latDir = (lat > 0) ? 'N' : 'S';
    //lat = std::abs(lat);     //Ruft den Fehler: 50,00, 0, hervor
    char buff[20];

    latDegree = (unsigned short) lat;
    lat -= latDegree;
    lat *= 60;
    latMinutes = (unsigned short) lat;
    lat -= latMinutes;
    lat *= 60;
    latSeconds = (unsigned short) (lat + 0.500001);

    sprintf(buff,"lat: %2.0d,%2.0d,%2.0d %c \r\n", latDegree, latMinutes, latSeconds, latDir);  
    output.assign(buff);    

    double lon = (double) longitude.getDegrees();
    unsigned short lonDegree, lonMinutes, lonSeconds;
    char lonDir = (lon > 0) ? 'E' : 'W';
    //lon = std::abs(lon);

    lonDegree = (unsigned short) lon;
    lon -=  lonDegree;
    lon *= 60;
    lonMinutes = (unsigned short) lon;
    lon -= lonMinutes;
    lon *= 60;
    lonSeconds = (unsigned short) (lon + 0.500001);
    
    sprintf(buff,"lon:%3.0d,%2.0d,%2.0d %c", lonDegree,lonMinutes,lonSeconds,lonDir);    
    output.append(buff);

    return output;
}

const LatitudeDegree &Position::getLatitude() const {
    return latitude;
}

const LongitudeDegree &Position::getLongitude() const {
    return longitude;
}


