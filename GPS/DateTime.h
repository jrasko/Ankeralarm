
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H

#include <sstream>
#include <cmath>

using namespace std;

class DateTime {

public:
    DateTime()= default;

    DateTime(const string &timeString, const string &datestring);

    DateTime(short day, short month, short year, short hours, short minutes, double seconds);

    short getDay() const;

    short getMonth() const;

    short getYear() const;

    short getHours() const;

    short getMinutes() const;

    double getSeconds() const;

    friend DateTime operator-(const DateTime &d1, const DateTime &d2);




private:
    double seconds = 0;
    short minutes = 0;
    short hours = 0;

    short day = 0;
    short month = 0;
    short year = 0;

};


#endif //ANKERALARM_2_DATE_H
