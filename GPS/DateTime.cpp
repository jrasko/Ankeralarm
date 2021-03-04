#include "DateTime.h"
#include <stdexcept>


using namespace std;


/**
 * Constructor - Creates a DateTime Objekt from given Parameters
 * @param timeString with the format "hhmmss.ss"
 * @param datestring with the format "ddmmyy"
 */
DateTime::DateTime(const string &timeString, const string &datestring) {

    short min, h, d, m, y = 0;
    double sec = 0;


    if (timeString.size() != 9 || datestring.size() != 6) {
        dirty = true;
        return ;
    }

    stringstream(timeString.substr(0, 2)) >> h;
    stringstream(timeString.substr(2, 2)) >> min;
    stringstream(timeString.substr(4, 5)) >> sec;

    stringstream(datestring.substr(0, 2)) >> d;
    stringstream(datestring.substr(2, 2)) >> m;
    stringstream(datestring.substr(4, 2)) >> y;

    if (h < 0 || h > 24 || min < 0 || min >= 60 || sec < 0 || sec >= 60 ||
        d < 1 || d > 31 || m < 1 || m > 12 || y < 0 || y > 99) {
        //throw invalid_argument("Invalid Argument!"); 
        return ;    
    }
    hours = h;
    minutes = min;
    seconds = sec;

    day = d;
    month = m;
    year = y;

}


/**
 * Calculates the Difference between the 2 parameters
 * @param d1 The first Date, where d2 gets subtracted from
 * @param d2 The Second Date, gets substracted from d1
 * @return a Date Object which has the difference of days as day, the difference of months as month and so on
 */
DateTime operator-(const DateTime &d1, const DateTime &d2) {
    short monthLength[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //Prüfe auf Schaltjahr
    if ((d1.year % 4 == 0 && d1.year % 100 != 0) || d1.year % 400 == 0) {
        monthLength[1] = 29;
    }
    double sec = 0;
    short min = d1.minutes - d2.minutes;
    short h = d1.hours - d2.hours;

    short d = d1.getDay() - d2.getDay();
    short m = d1.getMonth() - d2.getMonth();
    short y = d1.getYear() - d2.getYear();

    if (sec < 0) {
        sec += 60;
        min--;
    }
    if (min < 0) {
        min += 60;
        h--;
    }
    if (h < 0) {
        h += 24;
        d--;
    }
    if (d < 0) {
        m--;
        if (d2.month <= 1) {
            d += 32;
        } else {
            d += monthLength[d2.month - 1];
        }
    }
    if (m < 0) {
        y--;
        m += 13;
    }
    if (y < 0) {
        y += 100;
    }

    return {d, m, y, h, min, sec};
}

/**
 * Constructor which initializes all fields
 * ATTENTION!! Correct number of days is not completely checked!
 */
DateTime::DateTime(short day, short month, short year, short hours, short minutes, double seconds) {
    if (hours < 0 || hours > 24 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60 ||
        day < 0 || day > 31 || month < 0 || month > 12 || year < 0 || year > 99) {
        dirty = true;
        return ;
    }
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;

    this->day = day;
    this->month = month;
    this->year = year;
}

short DateTime::getHours() const {
    return hours;
}

short DateTime::getMinutes() const {
    return minutes;
}

double DateTime::getSeconds() const {
    return seconds;
}

short DateTime::getDay() const {
    return day;
}

short DateTime::getMonth() const {
    return month;
}

short DateTime::getYear() const {
    return year;
}

