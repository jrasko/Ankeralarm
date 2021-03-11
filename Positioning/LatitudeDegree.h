
#ifndef ANKERALARM_LATITUDEDEGREE_H
#define ANKERALARM_LATITUDEDEGREE_H


#include <sstream>

class LatitudeDegree {

public:
    explicit LatitudeDegree(const std::string &koordString, char direction);

    explicit LatitudeDegree(float degrees);

    LatitudeDegree(const LatitudeDegree &d) {
        degrees= d.degrees;
    }

    float getDegrees() const {
        return degrees;
    }

    friend LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2);


    float toMeters() const;

private:
    float degrees;
};


#endif //ANKERALARM_LATITUDEDEGREE_H
