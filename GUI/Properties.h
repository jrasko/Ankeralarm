
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs
#define RX_Buffer_SIZE 128  //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128  //einstelleng der gößes des sende Buffers;
#define maxIncomingMessageLength 100

#include "../GPS/GPS.h"


class Properties {
public:
    GPS myGPS;
    bool alarmActive = false;
    Position centralPosition = Position(LatitudeDegree(0),LongitudeDegree(0));
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

   

};

#endif //ANKERALARM_PROPERTIES_H
