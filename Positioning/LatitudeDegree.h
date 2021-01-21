
#ifndef ANKERALARM_LATITUDEDEGREE_H
#define ANKERALARM_LATITUDEDEGREE_H


#include <sstream>
#include <ostream>

class LatitudeDegree  {

public:
    LatitudeDegree(char direction, int degrees, long double minutes);

    explicit LatitudeDegree(const std::string& koordString);

    explicit LatitudeDegree(const std::string& koordString, char direction);

    LatitudeDegree(int degrees, long double minutes);

    LatitudeDegree(const LatitudeDegree &d) {
        degrees = d.degrees;
        minutes = d.minutes;
    }
    int getDegrees() const {
        return degrees;
    }

    long double getMinutes() const {
        return minutes;
    }


    friend LatitudeDegree operator-(const LatitudeDegree &dg1, const LatitudeDegree &dg2);

    long double toMeters() const;

private:
    int degrees;
    long double minutes;
};



#endif //ANKERALARM_LATITUDEDEGREE_H
