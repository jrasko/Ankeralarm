
#include <iostream>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"

using namespace std;

int main() {
    GPS myGps;

    DateTime t1(31, 7, 20, 0, 0, 0);
    DateTime t2(1, 8, 20, 0, 0, 0);
    DateTime s = t2 - t1;
    cout << s.getDay() << "." << s.getMonth() << "." << s.getYear() << " " << s.getHours() << ":" << s.getMinutes()
         << ":" << s.getSeconds() << endl;
    cout << myGps.getAccuracy() << endl;

}
