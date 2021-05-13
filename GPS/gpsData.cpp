
#include "gpsData.h"

bool gpsChecksumOk(const char *gpsMessage) {
	const char hex[] = "0123456789ABCDEF";
	if (*gpsMessage != '$') return false;
	short v = 0;
	while (true) {
		short b = *++gpsMessage;
		if (b == '*') {
			break;
		}
		if (b == '\0') {
			return false;
		}
		v ^= b;
	}
	unsigned char digit0 = hex[(v & 0xf0) >> 4];
	unsigned char digit1 = hex[(v & 0x0f)];
	return !(gpsMessage[1] != digit0 || gpsMessage[2] != digit1);
}

bool validateGPSString(const char *proofIt) {
	Vector<String> v;
	int k = 0;
	while (true) {
		String currentString;
		while (proofIt[k] != ',' && proofIt[k] != '\0') {
			currentString.concat(proofIt[k]);
			k++;
		}
		v.push_back(currentString);
		if (proofIt[k] == '\0') {
			break;
		}
		k++;
	}
	if (v[0] == "$GPGGA") {
		if (v[6] != "1") {
			return false;
		}
	} else if (v[0] == "$GPRMC") {
		if (v[2][0] != 'A') {
			return false;
		}
	} else {
		return false;
	}
	return gpsChecksumOk(proofIt);
}

gpsData::gpsData(const char *myGPSString) {
	if (!validateGPSString(myGPSString)) {
		dirty = true;
		return;
	}
	unsigned short k = 0;
	Vector<String> v;
	for (int i = 0; i < 15; ++i) {
		String currentString;
		currentString.reserve(10);
		while (myGPSString[k] != ',' && myGPSString[k] != '\0') {
			currentString.concat(myGPSString[k]);
			k++;
		}
		v.push_back(currentString);
		k++;
	}
	data = v;
}

