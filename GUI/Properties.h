
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs
#define RX_Buffer_SIZE 128  //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128  //einstelleng der gößes des sende Buffers;
#define maxIncomingMessageLength 100

#include "../GPS/GPS.h"
#include <Arduino.h>
#include "NMEARead.h"


class Properties {
private:
	String currentDataString;
public:
	NMEARead gpsdata;
	GPS myGPS;
	bool alarmActive = false;
	unsigned char alarmRadius = 25;
	Position centralPosition = Position(LatitudeDegree(0), LongitudeDegree(0));
	unsigned char displayBrighness = 0;
	unsigned char displayTimeout = 0;
	uint8_t *eepromBrightnes;

	static void setDisplayBrightness(unsigned char brightness) {
		analogWrite(lcd_beleuchtung, brightness);
	}

	void setDisplayTimeout(unsigned char timeout) {
		// Nicht mit Timer möglich, da Timer 2 fürs Display Benötigt wird!
	}

	void readEEPROM() {
		unsigned char brightness = eeprom_read_byte(eepromBrightnes);
		displayBrighness = brightness;
		setDisplayBrightness(brightness);
	}

	void writeEEPROM() const {
		eeprom_write_byte(eepromBrightnes, displayBrighness);
	}

	void updateGPSData() {
		if (/* gpsdata.NMEA_read(currentDataString) */ true) {
			currentDataString = "$GPGGA,192822.00,5035.56591,N,00720.91370,E,1,10,0.83,330.9,M,46.9,M,,*52";
			gpsData data = gpsData(currentDataString.c_str());
			currentDataString = "";
			myGPS.update(data);
		}
	}


};

#endif //ANKERALARM_PROPERTIES_H
