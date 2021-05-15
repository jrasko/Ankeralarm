
#ifndef ANKERALARM_POSITION_H
#define ANKERALARM_POSITION_H


#include "LatitudeDegree.h"
#include "LongitudeDegree.h"
#include <Arduino.h>
#include <Vector.h>
#include <math.h>

class Position {
public:
	Position() : latitude(0), longitude(0) {}

	Position(const LatitudeDegree &latitude, const LongitudeDegree &longitude) : latitude(latitude),
																				 longitude(longitude) {}

	friend Position getMedian(const Vector<Position> &p, unsigned char size);

	double distanceTo(const Position &p) const;

	const LatitudeDegree &getLatitude() const;

	const LongitudeDegree &getLongitude() const;

	const char *toString() const;

private:
	LatitudeDegree latitude;
	LongitudeDegree longitude;
};


#endif //ANKERALARM_POSITION_H
