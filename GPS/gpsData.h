
#ifndef ANKERALARM_2_GPSDATA_H
#define ANKERALARM_2_GPSDATA_H

#include <vector>
#include <string>
#include <vector>
#include <stdexcept>

class gpsData {
private:
    std::vector<std::string> data;
public:
    std::vector<std::string> getData() {
        return data;
    }

    explicit gpsData(const char *myGPSString);

    bool dirty = false;
};


bool gpsChecksumOk(const char *gpsMessage);

bool validateGPSString(const char proofIt[]);

#endif //ANKERALARM_2_GPSDATA_H
