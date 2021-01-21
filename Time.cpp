#include "Time.h"


//using namespace std;

Time::Time(string &timeString) {

    short h = 0;
    short min = 0;
    double sec = 0;

    if (timeString.size() != 9) {
        throw std::invalid_argument("Invalid Argument!");
    }

    stringstream(timeString.substr(0, 2)) >> h;
    stringstream(timeString.substr(2, 2)) >> min;
    stringstream(timeString.substr(4, 5)) >> sec;

    if (h < 0 || h > 24 || min < 0 || min >= 60 || sec < 0 || sec >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    hours = h;
    minutes = min;
    seconds = sec;

}

Time operator-(Time &d1, Time &d2) {
    double sec = d1.seconds - d2.seconds;
    short min = d1.minutes - d2.minutes;
    short h = d1.hours - d2.hours;
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
    }
    return {h, min, sec};
}

Time::Time(short hours, short minutes, double seconds) {
    if (hours < 0 || hours > 24 || minutes < 0 || minutes >= 60 || seconds < 0 || seconds >= 60) {
        throw std::invalid_argument("Invalid Argument!");
    }
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
}

short Time::getHours() const {
    return hours;
}

short Time::getMinutes() const {
    return minutes;
}

double Time::getSeconds() const {
    return seconds;
}

