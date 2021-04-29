#include "DateTime.h"
#include <Arduino.h>
/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const string &dateString) {
    short d, m, y = 0;

    d = String(dateString.substr(0, 2)).toInt();
    m = String(dateString.substr(2, 2)).toInt();
    y = String(dateString.substr(4, 2)).toInt();

    day = d;
    month = m;
    year = y;
}

void DateTime::updateTime(const string &timeString) {
    short min, h = 0;
    double sec = 0;

    h = String(timeString.substr(0, 2)).toInt();
    min = String(timeString.substr(2, 2)).toInt();
    sec = String(timeString.substr(4, 5)).toDouble;

    hours = h;
    minutes = min;
    seconds = sec;
}

vector<string> DateTime::toString() const {
    vector<string> ary;
    return ary;
}
