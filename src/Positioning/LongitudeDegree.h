
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <Arduino.h>

class LongitudeDegree {

public:
	explicit LongitudeDegree(const String &koordString, char direction);

	explicit LongitudeDegree(long deg) {
		this->degrees = deg;
	}

	LongitudeDegree(const LongitudeDegree &d) {
		this->degrees = d.degrees;
	}

	long getDegrees() const {
		return this->degrees;
	}

	friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

	friend void operator+=(LongitudeDegree &dg, long degrees);

	double toMeters(double latdeg) const;

private:
	long degrees;
};


#endif //ANKERALARM_LONGITUDEDEGREE_H
