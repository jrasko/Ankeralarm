#ifndef ANKERALARM_LATITUDEDEGREE_H
#define ANKERALARM_LATITUDEDEGREE_H

#include <sstream>
#include <cmath>
#include <Arduino.h>

using namespace std;

class LatitudeDegree {

public:
	explicit LatitudeDegree(const std::string &koordString, char direction);

	explicit LatitudeDegree(double deg);

	LatitudeDegree(const LatitudeDegree &d) {
		degrees = d.degrees;
	}

	double getDegrees() const {
		return degrees;
	}

	friend LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2);


	double toMeters() const;

private:
	double degrees;
};


#endif //ANKERALARM_LATITUDEDEGREE_H
