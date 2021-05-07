#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const string &dateString) {
	unsigned char d, m = 0;
	unsigned short y = 0;
	d = String(dateString.substr(0, 2).c_str()).toInt();
	m = String(dateString.substr(2, 2).c_str()).toInt();
	y = String(dateString.substr(4, 2).c_str()).toInt();

	day = d;
	month = m;
	year = y;
}

void DateTime::updateTime(const string &timeString) {
	unsigned char min, h = 0;
	double sec = 0;


	h = String(timeString.substr(0, 2).c_str()).toInt();
	min = String(timeString.substr(2, 2).c_str()).toInt();
	sec = String(timeString.substr(4, 5).c_str()).toDouble();

	hours = h;
	minutes = min;
	seconds = sec;
}

vector<string> DateTime::toString() const {
	vector<string> ary;
	char buff1[16];
	char buff2[5];
	unsigned char h = UTCFactor;
	unsigned char d = day;
	unsigned char m = month;
	unsigned short y = year;

	h += UTCFactor;
	if (h >= 24) {
		h -= 24;
		d++;
		if (d > monthLength[m - 1] || !(d == 29 && m == 2 && isLeapYear(y))) {
			m++;
			if (m > 12) {
				m -= 12;
				y++;
			}
		}
	}

	sprintf(buff1, "%02u.%02u.%02u", d, m, y);
	ary.push_back(buff1);
	sprintf(buff1, "%02u:%02u:%s", h, minutes, dtostrf(seconds, 5, 2, buff2));
	ary.push_back(buff1);
	return ary;
}

void DateTime::setUTCFactor(unsigned char factor) {
	UTCFactor = factor;
}

unsigned char DateTime::getUTCFactor() const {
	return UTCFactor;
}



