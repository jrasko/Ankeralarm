
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <cmath>

using namespace std;
class Time{

public:
    short getHours() const;

    short getMinutes() const;

    double getSeconds() const;

    explicit Time(string &timeString);

    Time(short hours, short minutes, double seconds);

    friend Time operator-(Time &d1, Time &d2);


private:
    short hours;
    short minutes;
    double seconds;
};


#endif //ANKERALARM_2_DATE_H
