
#include "Position.h"

/**
 * Calculates the distance between this Object and p in metres
 * @param p the Positon which is compared with this pos
 * @return the distance from Position to p in meters
 */
double Position::distanceTo(const Position &p) const {

    LatitudeDegree dlat = this->latitude - p.latitude;
    LongitudeDegree dlong = this->longitude - p.longitude;

    double avgDeg = (latitude.getDegrees() + p.latitude.getDegrees()) / 2;
    return sqrt(dlat.toMeters() * dlat.toMeters() + dlong.toMeters(avgDeg) * dlong.toMeters(avgDeg));
}

void Position::setPosition(LatitudeDegree &x, LongitudeDegree &y) {
    latitude = x;
    longitude = y;
}

Position getMedian(const vector<Position> &p) {
    double latDeg = 0;
    double lonDeg = 0;

    for (const auto &i : p) {
        latDeg += i.latitude.getDegrees();
        lonDeg += i.longitude.getDegrees();
    }
    latDeg /= p.size();
    lonDeg /= p.size();

    return {LatitudeDegree(latDeg), LongitudeDegree(lonDeg)};
}

vector<string> Position::toString() const {
    vector<string> ary;
    string currentString;
    double lat = latitude.getDegrees();
    double lon = longitude.getDegrees();
    unsigned short latDegree, latMinutes, latSeconds, lonDegree, lonMinutes, lonSeconds;
    char buff[20];
    char latDir = (lat > 0) ? 'N' : 'S';
    char lonDir = (lon > 0) ? 'E' : 'W';

    if (lat < 0) {
        lat = -lat;
    }
    latDegree = (unsigned short) lat;
    lat = 60.0 * (lat - latDegree);
    latMinutes = (unsigned short) lat;
    lat = 60.0 * (lat - latMinutes);
    latSeconds = (unsigned short) (0.5001 + lat);

    sprintf(buff, "lat: %02d,%02d,%02d%c", latDegree, latMinutes, latSeconds, latDir);
    currentString.assign(buff);
    ary.push_back(currentString);
    currentString.clear();

    if (lon < 0) {
        lon = -lon;
    }
    lonDegree = (unsigned short) lon;
    lon = 60.0 * (lon - lonDegree);
    lonMinutes = (unsigned short) lon;
    lon = 60.0 * (lon - lonMinutes);
    lonSeconds = (unsigned short) (0.5001 + lon);

    sprintf(buff, "lon:%03d,%02d,%02d%c", lonDegree, lonMinutes, lonSeconds, lonDir);
    currentString.append(buff);
    ary.push_back(currentString);
    return ary;
}

const LatitudeDegree &Position::getLatitude() const {
    return latitude;
}

const LongitudeDegree &Position::getLongitude() const {
    return longitude;
}


