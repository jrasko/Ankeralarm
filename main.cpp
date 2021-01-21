
#include <iostream>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"

using namespace std;

int main() {
    GPS myGps;

    Time t1(10, 52, 16);
    Time t2(9, 56, 5);
    Time s = t1 - t2;
    cout << s.getHours() << ":" << s.getMinutes() << ":" << s.getSeconds() << endl;
    cout << myGps.getAccuracy() << endl;

}
