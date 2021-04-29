
#ifndef ANKERALARM_2_DATE_H
#define ANKERALARM_2_DATE_H

#include <sstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class DateTime {

public:
    void updateDate(const string &dateString);

    void updateTime(const string &timeString);

    vector<string> toString() const;


private:
    double seconds = 0.0;
    short minutes = 0;
    short hours = 0;

    short day = 0;
    short month = 0;
    short year = 0;

};


#endif //ANKERALARM_2_DATE_H
