#include <iostream>
#include <string>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"

using namespace std;

bool NMEA_read(string &currentString);

void alarm();

int main() {
    GPS myGps;

    DateTime t1(31, 7, 20, 0, 0, 0);
    DateTime t2(1, 8, 20, 0, 0, 0);
    DateTime s = t2 - t1;
    cout << s.getDay() << "." << s.getMonth() << "." << s.getYear() << " " << s.getHours() << ":" << s.getMinutes()
         << ":" << s.getSeconds() << endl;
    cout << myGps.getAccuracy() << endl;

}

GPS gpsData;

void updateGPSData() {
    string currentDataString;
    if (NMEA_read(currentDataString)) {
        try {
            gpsData.update(currentDataString.c_str());
        } catch (exception &e) {
            return;
        }
    }
}

void loop() {

    updateGPSData();

    if (gpsData.getGPSQuality() > 1) {
        //LCD Outputs
    }


    //GPS angeschaltet
    while (/* alarmmode */ random()) {
        vector<Position> posCollection;

        for (int i = 0; i < 4; ++i) {
            updateGPSData();
            posCollection.push_back(gpsData.getCurrentPosition());
        }
        const Position startPosition = getMedian(posCollection);

        //Radius einstellen
        unsigned int radius = 100;

        // Abstand zur Ursprungsposition testen.
        while (random()) {
            updateGPSData();
            if (startPosition.distanceTo(gpsData.getCurrentPosition()) > radius) {
                alarm();
            }
        }


    }


}

void alarm() {
    // Aktiviere Alarm
}

bool
NMEA_read(string &currentString) {                      // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
    char nextChar = '\0';
    bool newDataAvailable;
    bool string_complete = false;
    newValidNMEA = false;
    //
    if (rxReadPos != rxWritePos) {
        nextChar = rxBuffer[rxReadPos];

        if (nextChar == '$' && !newDataAvailable) {
            newDataAvailable = true;
        } else {
            return false;
        }
        //Checking for new Data incoming
        //Expanding of the CurrentDataString with the current char
        if (newDataAvailable) {
            currentString += nextChar; //zusammen bauen des Strings
        }
        //String is finished
        if (nextChar == '\r') {
            currentString += '\r';
            currentString += '\n';


            string_complete = true; // wird aktiviert wenn ein NEMA datensatz eingegenen ist
            newDataAvailable = false; // für datenverabeitug

        }

        rxReadPos++;

        if (rxReadPos >= RX_Buffer_SIZE) {
            rxReadPos = 0;
        }

    }
    if (string_complete) {
        //digitalWrite(debug_led, LOW);
        //char data[Combine.length()];
        //GNSS_3.toCharArray(data, Combine.length()+1); // umwandeln des Strings in ein char Array
        //serialWrite(data);

        for (int i = 0; i < GNSS_2.length(); i++) {
            if (gps.encode(GNSS_2.charAt(i))) {
                newValidNMEA = true;
                newValidNMEA_dataTime = millis();
            } else {
                newValidNMEA = false;
            }
        }
        for (int i = 0; i < GNSS_1.length(); i++) {
            if (gps.encode(GNSS_1.charAt(i))) {
                //newValidNMEA = true;
                //newValidNMEA_dataTime = millis();
            } else {
                //newValidNMEA=false;
            }

        }
        string_complete = false;
        currentString = "";
        return true;
    }
    return false;
}
