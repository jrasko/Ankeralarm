#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const String &dateString) {
	day = dateString.substring(0, 2).toInt();
	month = dateString.substring(2, 4).toInt();
	year = dateString.substring(4, 6).toInt();
}

void DateTime::updateTime(const String &timeString) {
	unsigned char h = timeString.substring(0, 2).toInt();
	unsigned char min = timeString.substring(2, 4).toInt();
	double sec = timeString.substring(4, 9).toDouble();

	hours = h;
	minutes = min;
	seconds = sec;
}

const char *DateTime::toString() const {
	unsigned char h = hours;
	unsigned char d = day;
	unsigned char m = month;
	unsigned char y = year;

	h += UTCFactor;
	// In case of negative h
	if (h >= 244) {
		h = 24 - (256 - h);
		d--;
		if (d == 0) {
			if (m == 1) {
				d = 31;
				m = 12;
				y--;
				if (y == 255) {
					y = 0;
				}
			} else if (m == 3 && isLeapYear(y)) {
				d = 29;
				m = 2;
			} else {
				d = monthLength[(m - 2)];
				m--;
			}
		}
	} else if (h >= 24) {
		// In case of positive h
		h -= 24;
		d++;
		if (d > monthLength[m - 1] || (d == 29 && m == 2 && isLeapYear(y))) {
			d = 1;
			m++;
			if (m > 12) {
				m = 1;
				y++;
				if (h > 99) {
					h = 0;
				}
			}
		}
	}
	char *buff = new char[5];
	char *ary = new char[34];
	dtostrf(seconds, 5, 2, buff);
	if (buff[0] == ' ') {
		buff[0] = '0';
	}
	sprintf(ary, "%02u.%02u.%02u         %02u:%02u:%s", d, m, y, h, minutes, buff);
	delete[] buff;
	ary[16] = '\0';
	return ary;
}

void DateTime::setUTCFactor(const char factor) {
	UTCFactor = factor;
}

char DateTime::getUTCFactor() const {
	return UTCFactor;
}

bool DateTime::hasReached(unsigned char hour, unsigned char minute) const {
	unsigned char h = this->hours + UTCFactor;
	if (h >= 244) {
		h = 24 - (256 - h);
	}
	return hour == h && minute == this->minutes;
}



