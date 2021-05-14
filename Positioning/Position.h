
#ifndef ANKERALARM_POSITION_H
#define ANKERALARM_POSITION_H


#include "LatitudeDegree.h"
#include "LongitudeDegree.h"
#include <Arduino.h>
#include <Vector.h>

class Position {
public:

	Position(const LatitudeDegree &latitude, const LongitudeDegree &longitude) : latitude(latitude),
																				 longitude(longitude) {}

	friend Position getMedian(const Vector<Position> &p);

	double distanceTo(const Position &p) const;

	void setPosition(LatitudeDegree &x, LongitudeDegree &y);

	const LatitudeDegree &getLatitude() const;

	const LongitudeDegree &getLongitude() const;

	Vector<const char*> toString() const;

private:
	LatitudeDegree latitude;
	LongitudeDegree longitude;
};


#endif //ANKERALARM_POSITION_H
