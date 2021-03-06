#include "LongitudeDegree.h"

#define toDEG (3.14159265/180)

LongitudeDegree::LongitudeDegree(const String &koordString, char direction) {
	unsigned char deg = koordString.substring(0, 3).toInt();
	double min = koordString.substring(3).toDouble();

	double jdeg = min / 60.0 + deg;
	if (direction == 'W') {
		jdeg = -jdeg;
	}
	degrees = jdeg;
}

LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2) {
	return LongitudeDegree(dg1.degrees - dg2.degrees);
}

double LongitudeDegree::toMeters(double latdeg = 0) const {
	const double mile = degrees < 0 ? -1852.216 : 1852.216;
	return degrees * 60 * mile * cos(latdeg * toDEG);
}

LongitudeDegree::LongitudeDegree(double deg) {
	degrees = deg;
}
