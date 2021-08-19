
#ifndef ANKERALARM_PROPERTIES_H
#define ANKERALARM_PROPERTIES_H

#define lcd_beleuchtung 11 // Hintergrundbeleuchtung des LCDs
#define RX_Buffer_SIZE 128  //einstellung der Größe des empfangs Buffers
#define TX_Buffer_SIZE 128  //einstellung der größes des sende Buffers;
#define maxIncomingMessageLength 100

#include "../GPS/GPS.h"
#include <Arduino.h>
#include "NMEARead.h"
#include "EEPROM.h"

// Singleton
class Properties {
private:
	String currentDataString;

	// Singleton: Avoid multiple Objects
	Properties() = default;

public:
	Properties(const Properties &) = delete;

	Properties &operator=(const Properties &) = delete;

	// Generals
	GPS myGPS;
	NMEARead gpsdata;
	Position centralPosition;
	EEPROM eeprom;

	// Timeout
	bool timeoutActive = false;
	unsigned long lastInteraction = millis();

	// Alarm
	bool alarmActive = false;
	unsigned char alarmRadius = 25;

	// Display Props
	unsigned char displayBrightness = 255;
	unsigned char displayTimeout = 60;


	static void setDisplayBrightness(unsigned char brightness) {
		analogWrite(lcd_beleuchtung, brightness);
	}

	void checkSleepTimer() {
		if (displayTimeout == 0) {
			if (timeoutActive) {
				setDisplayBrightness(displayBrightness);
				timeoutActive = false;
			}
			return;
		}
		// Activate Timeout
		if (millis() - lastInteraction > ((unsigned long) displayTimeout) * 1000 && !timeoutActive) {
			setDisplayBrightness(0);
			timeoutActive = true;
		}
		// Deactivate Timeout
		if (millis() - lastInteraction < ((unsigned long) displayTimeout) * 1000 && timeoutActive) {
			setDisplayBrightness(displayBrightness);
			timeoutActive = false;
		}
	}

	void initFromEEPROM() {
		displayBrightness = eeprom.readFromEEPROM(eeprom.BRIGHTNESS);
		setDisplayBrightness(displayBrightness);

		displayTimeout = eeprom.readFromEEPROM(eeprom.TIMEOUT);
		myGPS.getLastTimeStamp().setUTCFactor((char) eeprom.readFromEEPROM(eeprom.UTCFACTOR));
	}

	bool updateGPSData() {
		if (gpsdata.NMEA_read(currentDataString)) {
			gpsData data = gpsData(currentDataString.c_str());
			currentDataString = "";
			return myGPS.update(data);
		}
		return false;
	}

	// Get singleton
	static Properties &getInstance() {
		static Properties _instance;
		return _instance;
	}

};

#endif //ANKERALARM_PROPERTIES_H
