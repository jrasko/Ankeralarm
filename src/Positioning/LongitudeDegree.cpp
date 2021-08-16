#include "LongitudeDegree.h"

#define toDEG (3.14159265/180)

LongitudeDegree::LongitudeDegree(const String &koordString, char direction) {
	unsigned char deg = koordString.substring(0, 3).toInt();
	double min = koordString.substring(3).toDouble();

	long jdeg = deg * 60 * 100000 + (long) (min * 100000);
	if (direction == 'W') {
		jdeg = -jdeg;
	}
	this->degrees = jdeg;
}

LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2) {
	return LongitudeDegree(dg1.degrees - dg2.degrees);
}

double LongitudeDegree::toMeters(double latdeg = 0) const {
	const double mile = degrees < 0 ? -1852.216 : 1852.216;
	return ((double) this->degrees / 100000) * mile * cos(latdeg * toDEG);
}

void operator+=(LongitudeDegree &dg, const long degrees) {
	dg.degrees += degrees;
}

