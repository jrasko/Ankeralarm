#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#include "../GPS/GPS.h"

#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs



class Properties {
public:
    GPS myGPS;
    bool alarmActive = false;
    unsigned char displayBrighness = 0;
    unsigned char displayTimeout = 0;
    unsigned char UTCFactor = 0;

    // TODO init with EPROM, set Display in setup
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
