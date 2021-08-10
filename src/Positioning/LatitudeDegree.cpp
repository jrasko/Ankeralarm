#include "LatitudeDegree.h"


LatitudeDegree::LatitudeDegree(const String &koordString, char direction) {
	unsigned char deg = koordString.substring(0, 2).toInt();
	double min = koordString.substring(2).toDouble();

	long jdeg = deg * 60 * 100000 + (long) (min * 100000);
	if (direction == 'S') {
		jdeg = -jdeg;
	}
	this->degrees = jdeg;
}


LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2) {
	return LatitudeDegree(dg1.degrees - dg2.degrees);
}

//Returns Distance to Point Zero
double LatitudeDegree::toMeters() const {
	const double mile = this->degrees < 0 ? -1852.216 : 1852.216;
	return mile * ((double) this->degrees / 100000);
}



