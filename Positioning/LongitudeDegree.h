
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <stdexcept>
#include <sstream>
#include <ostream>
#include <cmath>

using namespace std;

class LongitudeDegree {

public:

    LongitudeDegree(char direction, int degrees, long double minutes);

    explicit LongitudeDegree(const std::string &koordString);

    explicit LongitudeDegree(const std::string &koordString, char direction);

    explicit LongitudeDegree(long double degrees);

    LongitudeDegree(int degrees, long double minutes);

    LongitudeDegree(const LongitudeDegree &d) {
        degrees = d.degrees;
    }

    long double getDegrees() const {
        return degrees;
    }


    friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

    long double toMeters(long double latdeg) const;

private:
    long double degrees;
};


#endif //ANKERALARM_LONGITUDEDEGREE_H
