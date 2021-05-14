#include "LatitudeDegree.h"


LatitudeDegree::LatitudeDegree(const String &koordString, char direction) {
	unsigned char deg = koordString.substring(0, 2).toInt();
	double min = koordString.substring(2, 10).toDouble();

	double jdeg = min / 60.0 + deg;
	if (direction == 'S') {
		jdeg = -jdeg;
	}
	degrees = jdeg;
}


LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
	return LatitudeDegree(dg1.degrees - dg2.degrees);
}

//Returns Distance to Point Zero
double LatitudeDegree::toMeters() const {
	const double mile = degrees < 0 ? -1852.216 : 1852.216;
	return degrees * 60 * mile;
}


LatitudeDegree::LatitudeDegree(double deg) {
	degrees = deg;
}


