#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const String &dateString) {
	unsigned char d, m = 0;
	unsigned short y = 0;
	d = dateString.substring(0, 2).toInt();
	m = dateString.substring(2, 2).toInt();
	y = dateString.substring(4, 2).toInt();

	day = d;
	month = m;
	year = y;
}

void DateTime::updateTime(const String &timeString) {
	unsigned char min, h = 0;
	double sec = 0;


	h = timeString.substring(0, 2).toInt();
	min = timeString.substring(2, 2).toInt();
	sec = timeString.substring(4, 5).toDouble();

	hours = h;
	minutes = min;
	seconds = sec;
}

Vector<String> DateTime::toString() const {
	Vector<String> ary;
	unsigned char h = hours;
	unsigned char d = day;
	unsigned char m = month;
	unsigned short y = year;

	h += UTCFactor;
	if (h >= 244) {
		h = 24 - (256 - h);
		d--;
		if (d == 0) {
			if (m == 1) {
				d = 31;
				m = 12;
				y--;
			} else if (m == 3 && isLeapYear(y)) {
				d = 29;
				m = 2;
			} else {
				d = monthLength[(m - 2)];
				m--;
			}
		}
	} else if (h >= 24) {
		h -= 24;
		d++;
		if (d > monthLength[m - 1] || (d == 29 && m == 2 && isLeapYear(y))) {
			d = 1;
			m++;
			if (m > 12) {
				m = 1;
				y++;
			}
		}
	}
	char buff[16];
	char buff1[16];
	char buff2[5];

	sprintf(buff, "%02u.%02u.%02u", d, m, y);
	ary.push_back(buff);
	dtostrf(seconds, 5, 2, buff2);
	sprintf(buff1, "%02u:%02u:%s", h, minutes, buff2);
	ary.push_back(buff1);
	return ary;
}

void DateTime::setUTCFactor(unsigned char factor) {
	UTCFactor = factor;
}

unsigned char DateTime::getUTCFactor() const {
	return UTCFactor;
}



