
#ifndef ANKERALARM_2_GPSDATA_H
#define ANKERALARM_2_GPSDATA_H

#include <vector>
#include <string>

class gpsData {
private:
    std::vector<std::string> data;
    bool dirty = false;
public:
    std::vector<std::string> getData() const {
        return data;
    }

    explicit gpsData(const char *myGPSString);

    bool isValid() const {
        return !dirty;
    }
};


bool gpsChecksumOk(const char *gpsMessage);

bool validateGPSString(const char proofIt[]);

#endif //ANKERALARM_2_GPSDATA_H
