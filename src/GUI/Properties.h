
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#define lcd_beleuchtung 11 // Hintergrundbeleuchtung des LCDs
#define RX_Buffer_SIZE 128  //einstellung der Größe des empfangs Buffers
#define TX_Buffer_SIZE 128  //einstellung der größes des sende Buffers;
#define maxIncomingMessageLength 100

#include "../GPS/GPS.h"
#include <Arduino.h>
#include "NMEARead.h"

// Singleton
class Properties {
private:
	String currentDataString;

	// Singleton: Avoid multiple Objects
	Properties() = default;

public:
	GPS myGPS;
	NMEARead gpsdata;
	Position centralPosition;

	bool alarmActive = false;
	bool timeoutActive = false; //FIXME eventuell redundant
	unsigned long lastInteraction = millis();
	unsigned char alarmRadius = 25;
	unsigned char displayBrightness = 255;
	unsigned char displayTimeout = 60;
	uint8_t *eepromBrightness = nullptr;

	static void setDisplayBrightness(unsigned char brightness) {
		analogWrite(lcd_beleuchtung, brightness);
	}

	void checkSleepTimer() {
		if (displayTimeout == 0){
			if (timeoutActive){
				setDisplayBrightness(displayBrightness);
				timeoutActive = false;
			}
			return;
		}
		// Activate Timeout
		if (millis() - lastInteraction > displayTimeout * 1000 && !timeoutActive) {
			setDisplayBrightness(0);
			timeoutActive = true;
		}
		// Deactivate Timeout
		if(millis() - lastInteraction < displayTimeout * 1000 && timeoutActive){
			setDisplayBrightness(displayBrightness);
			timeoutActive = false;
		}
	}

	void readBrightnessFromEEPROM() {
		unsigned char brightness = eeprom_read_byte(eepromBrightness);
		displayBrightness = brightness;
		setDisplayBrightness(brightness);
	}

	void writeBrightnessInEEPROM() const {
		eeprom_write_byte(eepromBrightness, displayBrightness);
	}

	bool updateGPSData() {
		if (gpsdata.NMEA_read(currentDataString)) {
			gpsData data = gpsData(currentDataString.c_str());
			currentDataString = "";
			return myGPS.update(data);
		}
		return false;
	}

	// Singleton: Avoid Copies of Object
	Properties(const Properties &) = delete;

	Properties &operator=(const Properties &) = delete;

	// Get singleton
	static Properties &getInstance() {
		static Properties _instance;
		return _instance;
	}

};

#endif //ANKERALARM_PROPERTIES_H
