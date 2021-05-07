
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H

#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <Arduino.h>

using namespace std;

class DateTime {

public:
	void updateDate(const string &dateString);

	void updateTime(const string &timeString);

	vector<string> toString() const;

	void setUTCFactor(unsigned char factor);

private:
	void adjustTime();

	static inline bool isLeapYear(unsigned short y) {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 != 0);
	}

private:
	const unsigned char monthLength[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	double seconds = 0.0;
	unsigned char minutes = 0;
	unsigned char hours = 0;

	unsigned char day = 0;
	unsigned char month = 0;
	unsigned short year = 0;

	unsigned char UTCFactor = 0;

};


#endif //ANKERALARM_2_DATE_H
