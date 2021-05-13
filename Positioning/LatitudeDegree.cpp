#include "LatitudeDegree.h"


LatitudeDegree::LatitudeDegree(const std::string &koordString, char direction) {
	unsigned char deg = 0;
	double min = 0;
	deg = String(koordString.substr(0, 2).c_str()).toInt();
	min = String(koordString.substr(2, 10).c_str()).toDouble();

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


