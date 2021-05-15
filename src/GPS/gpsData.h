
#ifndef ANKERALARM_2_GPSDATA_H
#define ANKERALARM_2_GPSDATA_H

#include <Arduino.h>
#include <Vector.h>

/**
 * Splits the gps data string into a string array and sets the dirty flag, if the checksum is not valid
 */
class gpsData {
private:
	String data[20];
	bool dirty = false;
public:
	const String *getData() const {
		return data;
	}

	explicit gpsData(const char *myGPSString);

	bool isValid() const {
		return !dirty;
	}

};


bool gpsChecksumOk(const char *gpsMessage);

bool validateGPSString(const char proofIt[]);

#endif //ANKERALARM_2_GPSDATA_H
