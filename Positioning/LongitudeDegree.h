
#ifndef ANKERALARM_LONGITUDEDEGREE_H
#define ANKERALARM_LONGITUDEDEGREE_H

#include <sstream>
#include <cmath>

using namespace std;

class LongitudeDegree {

public:
    explicit LongitudeDegree(const std::string &koordString, char direction);

    explicit LongitudeDegree(float degrees);

    LongitudeDegree(const LongitudeDegree &d) {
        degrees = d.degrees;
    }

    float getDegrees() const {
        return degrees;
    }


    friend LongitudeDegree operator-(const LongitudeDegree &dg1, const LongitudeDegree &dg2);

    float toMeters(float latdeg) const;

private:
    float degrees;
};


#endif //ANKERALARM_LONGITUDEDEGREE_H
