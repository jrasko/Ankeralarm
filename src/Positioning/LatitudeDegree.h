#ifndef ANKERALARM_LATITUDEDEGREE_H
#define ANKERALARM_LATITUDEDEGREE_H

#include <Arduino.h>

class LatitudeDegree {

public:
	explicit LatitudeDegree(const String &koordString, char direction);

	explicit LatitudeDegree(long deg);

	LatitudeDegree(const LatitudeDegree &d) {
		degrees = d.degrees;
	}

	long getDegrees() const {
		return degrees;
	}

	friend LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2);


	double toMeters() const;

private:
	long degrees;
};


#endif //ANKERALARM_LATITUDEDEGREE_H
