#include "DateTime.h"

/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param dateString with the format "ddmmyy"
 * @attention DATA IS NOT CHECKED FOR CONSISTENCY
 */
void DateTime::updateDate(const string &dateString) {
    short d, m, y = 0;

    stringstream(dateString.substr(0, 2)) >> d;
    stringstream(dateString.substr(2, 2)) >> m;
    stringstream(dateString.substr(4, 2)) >> y;

    day = d;
    month = m;
    year = y;
}

void DateTime::updateTime(const string &timeString) {
    short min, h = 0;
    double sec = 0;

    // stringstream(timeString.substr(0, 2)) >> h;
    // stringstream(timeString.substr(2, 2)) >> min;
    // stringstream(timeString.substr(4, 5)) >> sec;
    stringstream("12") >> h;
    stringstream("45") >> min;
    stringstream("11.23") >> sec;

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
