
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <stdexcept>
#include <sstream>
#include <ostream>
#include <cmath>

using namespace std;

class LongitudeDegree  {

public:

    LongitudeDegree(char direction, int degrees, long double minutes);

    explicit LongitudeDegree(const std::string &koordString);

    explicit LongitudeDegree(const std::string& koordString, char direction);

    LongitudeDegree(int degrees, long double minutes);

    LongitudeDegree(const LongitudeDegree &d) {
        degrees = d.degrees;
        minutes = d.minutes;
    }
    int getDegrees() const {
        return degrees;
    }

    long double getMinutes() const {
        return minutes;
    }


    friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

    long double toMeters(long double latdeg) const;

private:
    int degrees;
    long double minutes;
};



#endif //ANKERALARM_LONGITUDEDEGREE_H
