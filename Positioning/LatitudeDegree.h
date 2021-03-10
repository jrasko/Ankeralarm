
#ifndef ANKERALARM_LATITUDEDEGREE_H
#define ANKERALARM_LATITUDEDEGREE_H


#include <sstream>

class LatitudeDegree {

public:
    explicit LatitudeDegree(const std::string &koordString, char direction);

    explicit LatitudeDegree(long double degrees);

    LatitudeDegree(int degrees, long double minutes);

    LatitudeDegree(const LatitudeDegree &d) {
        degrees= d.degrees;
    }

    long double getDegrees() const {
        return degrees;
    }

    friend LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2);


    long double toMeters() const;

private:
    long double degrees;
};


#endif //ANKERALARM_LATITUDEDEGREE_H
