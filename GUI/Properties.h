
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#include "../GPS/GPS.h"

#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs



class Properties {
public:
    GPS myGPS;
    bool alarmActive;    
    // TODO init with EPROM, set Display in setup
    uint8_t *eepromBrightnes;
    unsigned char displayBrighness = 0;
    unsigned char displayTimeout = 0;

    void setDisplayBrightness(unsigned char brightness){
        // TODO
        analogWrite(lcd_beleuchtung, brightness);
    }

    void setDisplayTimeout(unsigned char timeout){
        // TODO     //Nicht mit Timer möglich, da Timer 2 fürs Display Benötigt wird!
        
    }

    void writeEEPROM(unsigned char value){
        eeprom_write_byte(eepromBrightnes, value);
    }    

    void readEEPROM(){
        unsigned char brigh; 
        brigh = eeprom_read_byte(eepromBrightnes);
        setDisplayBrightness(brigh);
    }

};

#endif //ANKERALARM_PROPERTIES_H
