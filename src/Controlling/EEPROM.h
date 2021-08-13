#ifndef ANKERALARM_5_0_EEPROM_H
#define ANKERALARM_5_0_EEPROM_H


class EEPROM {
public:
	uint8_t *eepromBrightness = nullptr;
	uint8_t *eepromTimeout = nullptr;
	uint8_t *eepromUTCFactor = nullptr;

	enum EEPROMData {
		BRIGHTNESS, TIMEOUT, UTCFACTOR
	};

	void init(uint8_t *brightness, uint8_t *timeout, uint8_t *utcFactor) {
		eepromBrightness = brightness;
		eepromTimeout = timeout;
		eepromUTCFactor = utcFactor;
	}

	void writeInEEPROM(EEPROMData type, unsigned char value) const {
		switch (type) {
			case BRIGHTNESS:
				eeprom_write_byte(eepromBrightness, value);
				break;
			case TIMEOUT:
				eeprom_write_byte(eepromTimeout, value);
				break;
			case UTCFACTOR:
				eeprom_write_byte(eepromUTCFactor, value);
				break;
		}
	}

	unsigned char readFromEEPROM(EEPROMData type) const {
		switch (type) {
			case BRIGHTNESS:
				return eeprom_read_byte(eepromBrightness);
			case TIMEOUT:
				return eeprom_read_byte(eepromTimeout);
			case UTCFACTOR:
				return eeprom_read_byte(eepromUTCFactor);
			default:
				return 0;
		}
	}
};

#endif //ANKERALARM_5_0_EEPROM_H
