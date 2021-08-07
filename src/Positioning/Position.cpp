
#include "Position.h"

/**
 * Calculates the distance between this Object and p in metres
 * @param p the Position which is compared with this pos
 * @return the distance from Position to p in meters
 */
double Position::distanceTo(const Position &p) const {

	LatitudeDegree dlat = latitude - p.latitude;
	LongitudeDegree dlong = longitude - p.longitude;

	long avgDeg = (latitude.getDegrees() + p.latitude.getDegrees()) / 2;
	return sqrt(dlat.toMeters() * dlat.toMeters() +
				dlong.toMeters((double) avgDeg / 6000000.) * dlong.toMeters((double) avgDeg / 6000000.));
}

/**
 * Calculates the centre from a list of coordinates
 * @param p list of coordinates
 * @param size of the list (p.size() returns always 0)
 * @return the center coordinate
 */
Position getMedian(const Vector<Position> &p, unsigned char size) {
	long latDeg = 0;
	long lonDeg = 0;

	for (unsigned char i = 0; i < size; ++i) {
		latDeg += p[i].latitude.getDegrees();
		lonDeg += p[i].longitude.getDegrees();
	}
	latDeg /= size;
	lonDeg /= size;

	return {LatitudeDegree(latDeg), LongitudeDegree(lonDeg)};
}

/**
 * returns a dynamic char[34] representation of the position
 * @return
 */
const char *Position::toString() const {
	long lat = latitude.getDegrees();
	long lon = longitude.getDegrees();
	unsigned char latDegree, latMinutes, latSeconds, lonDegree, lonMinutes, lonSeconds;
	char latDir = (lat >= 0) ? 'N' : 'S';
	char lonDir = (lon >= 0) ? 'E' : 'W';
	if (lat < 0) {
		lat = -lat;
	}
	latDegree = (unsigned char) (lat / 6000000);
	lat -= 6000000 * latDegree;
	latMinutes = (unsigned char) (lat / 100000);
	lat -= 100000 * latMinutes;
	latSeconds = (unsigned char) ((double) lat * 60.0 / 100000 + 0.5001);

	if (lon < 0) {
		lon = -lon;
	}
	lonDegree = (unsigned char) (lon / 6000000);
	lon -= 6000000 * lonDegree;
	lonMinutes = (unsigned char) (lon / 100000);
	lon -= 100000 * lonMinutes;
	lonSeconds = (unsigned char) ((double) lon * 60.0 / 100000 + 0.5001);

	char *ary = new char[34];

	sprintf(ary, "lat: %02d,%02d,%02d%c   lon:%03d,%02d,%02d%c", latDegree, latMinutes, latSeconds, latDir, lonDegree,
			lonMinutes, lonSeconds, lonDir);
	ary[16] = '\0';
	return ary;
}

const LatitudeDegree &Position::getLatitude() const {
	return latitude;
}

const LongitudeDegree &Position::getLongitude() const {
	return longitude;
}


