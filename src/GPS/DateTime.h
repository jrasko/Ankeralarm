
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H

#include <Arduino.h>
#include <Vector.h>

class DateTime {

public:
	void updateDate(const String &dateString);

	void updateTime(const String &timeString);

	const char *toString() const;

	void setUTCFactor(char factor);

	char getUTCFactor() const;

private:
	static inline bool isLeapYear(unsigned char y) {
		return (y % 4 == 0 && y != 0);
	}

	const unsigned char monthLength[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	unsigned char seconds = 0;
	unsigned char minutes = 0;
	unsigned char hours = 0;

	unsigned char day = 1;
	unsigned char month = 1;
	unsigned char year = 0;

	char UTCFactor = 0;

};


#endif //ANKERALARM_2_DATE_H
