
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <Arduino.h>
#include "math.h"

class LongitudeDegree {

public:
	explicit LongitudeDegree(const String &koordString, char direction);

	explicit LongitudeDegree(long deg);

	LongitudeDegree(const LongitudeDegree &d) {
		degrees = d.degrees;
	}

	long getDegrees() const {
		return degrees;
	}

	friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

	double toMeters(double latdeg) const;

private:
	long degrees;
};


#endif //ANKERALARM_LONGITUDEDEGREE_H
