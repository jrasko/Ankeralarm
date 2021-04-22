
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H

#include <sstream>
#include <cmath>

using namespace std;

class DateTime {

public:
    DateTime() = default;

    void updateDate(const string &dateString);

    void updateTime(const string &timeString);

    void toString();
//    friend DateTime operator-(const DateTime &d1, const DateTime &d2);


private:
    double seconds = 0;
    short minutes = 0;
    short hours = 0;

    short day = 0;
    short month = 0;
    short year = 0;

};


#endif //ANKERALARM_2_DATE_H
