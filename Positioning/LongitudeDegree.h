
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <Arduino.h>

class LongitudeDegree {

public:
	explicit LongitudeDegree(const String &koordString, char direction);

	explicit LongitudeDegree(double deg);

	LongitudeDegree(const LongitudeDegree &d) {
		degrees = d.degrees;
	}

	double getDegrees() const {
		return degrees;
	}


	friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

	double toMeters(double latdeg) const;

private:
	double degrees;
};


#endif //ANKERALARM_LONGITUDEDEGREE_H
