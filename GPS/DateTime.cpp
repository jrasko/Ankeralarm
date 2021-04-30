#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const string &dateString) {
    short d, m, y = 0;

    d = String(dateString.substr(0, 2).c_str()).toInt();
    m = String(dateString.substr(2, 2).c_str()).toInt();
    y = String(dateString.substr(4, 2).c_str()).toInt();

    day = d;
    month = m;
    year = y;
}

void DateTime::updateTime(const string &timeString) {
    short min, h = 0;
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
    char buf[16];
    sprintf(buf,"%u.%u.%u",day ,month ,year);
    ary.push_back(string(buf));
    sprintf(buf,"%u:%u:%f",hours,minutes,seconds);
    ary.push_back(string(buf));
    return ary;
}
