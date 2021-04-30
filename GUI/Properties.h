
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs
#define RX_Buffer_SIZE 128  //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128  //einstelleng der gößes des sende Buffers;
#define maxIncomingMessageLength 100

#include "../GPS/GPS.h"


class Properties {
private:
    string currentDataString;
    char serialBuffer[TX_Buffer_SIZE]; // Buffer für UART Übertragung
    char rxBuffer[RX_Buffer_SIZE];     // Buffer für UART Emfang
    uint8_t serialReadPos = 0; //variablen für den Ringbuffer
    uint8_t serialWritePos = 0;
    uint8_t rxReadPos = 0;
    uint8_t rxWritePos = 0;

public:
    GPS myGPS;
    bool alarmActive = false;
    Position centralPosition;
    unsigned char displayBrighness = 0;
    unsigned char displayTimeout = 0;
    uint8_t *eepromBrightnes;

    static void setDisplayBrightness(unsigned char brightness){
        analogWrite(lcd_beleuchtung, brightness);
    }

    void setDisplayTimeout(unsigned char timeout){
        // Nicht mit Timer möglich, da Timer 2 fürs Display Benötigt wird!
    }

    void readEEPROM(){
        unsigned char brightness = eeprom_read_byte(eepromBrightnes);
        displayBrighness = brightness;
        setDisplayBrightness(brightness);
    }

    void writeEEPROM(){
        eeprom_write_byte(eepromBrightnes, displayBrighness);
    }

private:
    bool NMEA_read(string &currentString) { // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
        char nextChar;
        static bool newDataAvailable = false;
        static int countIncomingChars = 0;

        if (rxReadPos == rxWritePos) {
            //No Data available
            return false;
        }
        // Hier ansetzen falls letzter eingehender char benötigt wird
        nextChar = rxBuffer[rxReadPos];
        if (nextChar == '$') {
            // Beginning of a new DataString
            newDataAvailable = true;
        }
        if (!newDataAvailable) {
            rxReadPos++;
            if (rxReadPos >= RX_Buffer_SIZE) {
                rxReadPos = 0;
            }
            return false;
        }

        currentString.push_back(nextChar);

        if (nextChar == '\r') {
            //String is complete
            newDataAvailable = false;
            countIncomingChars = 0;
            return true;
        }
        countIncomingChars++;
        rxReadPos++;
        if (rxReadPos >= RX_Buffer_SIZE) {
            rxReadPos = 0;
        }
        if (countIncomingChars >= maxIncomingMessageLength) {
            newDataAvailable = false;
            countIncomingChars = 0;
            return false;
        }
        return false;
    }

public:
    bool updateGPSData() {
        if (NMEA_read(currentDataString)) {
            const gpsData &data = gpsData(currentDataString.c_str());
            currentDataString.clear();
            if (!data.isValid()) {
                // Ignoriere nicht valide Daten
                return false;
            }
            //Update bei korrekten Daten
            myGPS.update(data);
            return true;
        }
        return false;
    }

};

#endif //ANKERALARM_PROPERTIES_H
