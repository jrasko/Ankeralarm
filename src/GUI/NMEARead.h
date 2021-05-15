
#ifndef NMEA_READ_H
#define NMEA_READ_H

#include <Arduino.h>

#define RX_Buffer_SIZE 128 //einstellung der Größe des empfangs Buffers

#define TX_Buffer_SIZE 128 //einstellung der größe des sende Buffers;

class NMEARead {
private:
	char *serialBuffer = nullptr; // Buffer für UART Übertragung
	char *rxBuffer = nullptr;     // Buffer für UART Empfang
	uint8_t *serialReadPos = nullptr;
	uint8_t *serialWritePos = nullptr;
	uint8_t *rxReadPos = nullptr;
	uint8_t *rxWritePos = nullptr;
public:
	bool NMEA_read(String &currentString) { // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
		char nextChar;
		static bool newDataAvailable = false;
		static int countIncomingChars = 0;

		if (*rxReadPos == *rxWritePos) {
			//No Data available
			return false;
		}
		// Hier ansetzen falls letzter eingehender char benötigt wird
		nextChar = rxBuffer[*rxReadPos];
		if (nextChar == '$') {
			// Beginning of a new DataString
			newDataAvailable = true;
		}
		if (!newDataAvailable) {
			*rxReadPos = *rxReadPos + 1;
			if (*rxReadPos >= RX_Buffer_SIZE) {
				*rxReadPos = 0;
			}
			return false;
		}

		currentString.concat(nextChar);

		if (nextChar == '\r') {
			//String is complete
			newDataAvailable = false;
			countIncomingChars = 0;
			return true;
		}
		countIncomingChars++;
		*rxReadPos = *rxReadPos + 1;
		if (*rxReadPos >= RX_Buffer_SIZE) {
			*rxReadPos = 0;
		}
		if (countIncomingChars >= maxIncomingMessageLength) {
			newDataAvailable = false;
			countIncomingChars = 0;
			return false;
		}
		return false;
	}

	void init(uint8_t *_serialReadPos, uint8_t *_serialWritePos, uint8_t *_rxReadPos, uint8_t *_rxWritePos,
			  char _serialBuffer[TX_Buffer_SIZE], char _rxBuffer[RX_Buffer_SIZE]) {
		serialReadPos = _serialReadPos;
		serialWritePos = _serialWritePos;
		rxReadPos = _rxReadPos;
		rxWritePos = _rxWritePos;
		serialBuffer = _serialBuffer;
		rxBuffer = _rxBuffer;
	}

};

#endif