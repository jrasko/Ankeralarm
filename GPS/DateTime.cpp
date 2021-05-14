#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const String &dateString) {
	unsigned char d = dateString.substring(0, 2).toInt();
	unsigned char m = dateString.substring(2, 2).toInt();
	unsigned short y = dateString.substring(4, 2).toInt();

	day = d;
	month = m;
	year = y;
}

void DateTime::updateTime(const String &timeString) {
	unsigned char h = timeString.substring(0, 2).toInt();
	unsigned char min = timeString.substring(2, 2).toInt();
	double sec = timeString.substring(4, 5).toDouble();

	hours = h;
	minutes = min;
	seconds = sec;
}

const char *DateTime::toString() const {
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
	char buff[5];
	char *ary = new char[34];
	dtostrf(seconds, 5, 2, buff);
	sprintf(ary, "%02u.%02u.%02u       %02u:%02u:%s", d, m, y, h, minutes, buff);
	ary[16] = '\0';
	return ary;
}

void DateTime::setUTCFactor(unsigned char factor) {
	UTCFactor = factor;
}

unsigned char DateTime::getUTCFactor() const {
	return UTCFactor;
}



