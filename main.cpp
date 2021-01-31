
#include <iostream>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"

using namespace std;

bool NMEA_read(string &currentString);

int main() {
    GPS myGps;

    DateTime t1(31, 7, 20, 0, 0, 0);
    DateTime t2(1, 8, 20, 0, 0, 0);
    DateTime s = t2 - t1;
    cout << s.getDay() << "." << s.getMonth() << "." << s.getYear() << " " << s.getHours() << ":" << s.getMinutes()
         << ":" << s.getSeconds() << endl;
    cout << myGps.getAccuracy() << endl;

}

void loop() {
    //VORHER Deklarieren
    GPS gpsData;

    //Loopfunktion
    string currentDataString;
    //
    if (NMEA_read(currentDataString)) {
        try{
            gpsData.update(currentDataString.c_str());
        } catch (exception& e){
            //Fehler beim Parsen
        }
    }



}

bool NMEA_read(string &currentString) {                      // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
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
            currentString.trim();
            currentString += '\r';
            currentString += '\n';

            if (currentString.substring(1, 6) == "GPRMC") {
                GNSS_1 = currentString;

            }

            if (currentString.substring(1, 6) == "GPGGA") {
                GNSS_2 = currentString;
            }


            currentString = "";
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
