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
	adjustTime();
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
	adjustTime();
}

vector<string> DateTime::toString() const {
	vector<string> ary;
	char buf[16];
	sprintf(buf, "%02u.%02u.%02u", day, month, year);
	ary.push_back(buf);
	sprintf(buf, "%02u:%02u:%f", hours, minutes, seconds);
	ary.push_back(buf);
	return ary;
}

void DateTime::setUTCFactor(unsigned char factor) {
	UTCFactor = factor;
}

void DateTime::adjustTime() {
	hours++;
	if (hours < 24) {
		return;
	}
	hours -= 24;
	day++;
	if (day <= monthLength[month - 1] || (day == 29 && month == 2 && isLeapYear(year))) {
		return;
	}
	month++;
	if (month <= 12) {
		return;
	}
	year++;
}



