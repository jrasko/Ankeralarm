
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

    float lat = latitude.getDegrees();
    unsigned short latDegree, latMinutes, latSeconds;
    char latDir = (lat > 0) ? 'N' : 'S';
    lat = std::abs(lat);

    latDegree = (int) lat;
    lat -= latDegree;
    lat *= 60;
    latMinutes = (int) lat;
    lat -= latMinutes;
    lat *= 60;
    latSeconds = (int) (lat + 0.500001);
    stringstream s1;
    s1 << "lat: " << setfill('0') << std::setw(2) << latDegree << "," << setfill('0') << std::setw(2) << latMinutes
       << "," << setfill('0') << std::setw(2) << latSeconds << latDir;
    output += s1.str();
    output += "\r\n";

    float lon = this->longitude.getDegrees();
    unsigned short lonDegree, lonMinutes, lonSeconds;
    char lonDir = (lon > 0) ? 'E' : 'W';
    lon = std::abs(lon);

    lonDegree = (int) lon;
    lon -= lonDegree;
    lon *= 60;
    lonMinutes = (int) lon;
    lon -= lonMinutes;
    lon *= 60;
    lonSeconds = (int) (lon + 0.500001);
    stringstream s2;
    s2 << "lon:" << setfill('0') << std::setw(3) << lonDegree << "," << setfill('0') << std::setw(2) << lonMinutes
       << "," << setfill('0') << std::setw(2) << lonSeconds << lonDir;
    output += s2.str();

    return output;
}

const LatitudeDegree &Position::getLatitude() const {
    return latitude;
}

const LongitudeDegree &Position::getLongitude() const {
    return longitude;
}


