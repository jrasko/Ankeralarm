#ifndef F_CPU
/* In neueren Version der WinAVR/Mfile Makefile-Vorlage kann
   F_CPU im Makefile definiert werden, eine nochmalige Definition
   hier wuerde zu einer Compilerwarnung fuehren. Daher "Schutz" durch
   #ifndef/#endif 

   Dieser "Schutz" kann zu Debugsessions führen, wenn AVRStudio 
   verwendet wird und dort eine andere, nicht zur Hardware passende 
   Taktrate eingestellt ist: Dann wird die folgende Definition 
   nicht verwendet, sondern stattdessen der Defaultwert (8 MHz?) 
   von AVRStudio - daher Ausgabe einer Warnung falls F_CPU
   noch nicht definiert: */
#warning "F_CPU war noch nicht definiert, wird nun nachgeholt mit 16000000"
#define F_CPU 16000000UL // Systemtakt in Hz - Definition als unsigned long beachten
// Ohne ergeben sich unten Fehler in der Berechnung
#endif

#include <string>
#include <util/delay.h>

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "GPS/GPS.h"
#include "GPS/gpsData.h"
#include "GUI/Utils.h"
#include "GUI/GPSInfo.h"

#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/wdt.h>

using namespace std;

//---defines--------------------------------------------------

#define buttonDebounceTime 10 //in ms
#define maxIncomingMessageLength 100

//---UART-Interface (Sereielle Schnittstelle für GPS Modul)
#define BAUD 9600UL // Baudrate
// Berechnungen
#define UBRR_VAL ((F_CPU + BAUD * 8) / (BAUD * 16) - 1) // clever runden
#define BAUD_REAL (F_CPU / (16 * (UBRR_VAL + 1)))       // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL * 1000) / BAUD)          // Fehler in Promille, 1000 = kein Fehler.
//On Change Note the Definition in NMEARead.h
#define RX_Buffer_SIZE 128                              //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128                              //einstelleng der gößes des sende Buffers;

#if ((BAUD_ERROR < 990) || (BAUD_ERROR > 1010))
#error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch!
#endif

#define EEPROM_DEF 0xFF //EEPORM 

// ----IO-definition-----------------------------------------

#define ledPin 0         //LED pin 14                       PC0
#define debug_led 5       //onboard Led                     PB5
//#define lcd_beleuchtung 3 //backlight LCD                   PB3
#define returnButton 7         //Schalter 1                 PD7  PCINT 23
#define snozeButton 6			//							PD6
#define summer 4          //Summer                          PB4
#define encoder_a 2       //encoder pin 2 (32)              PD2                     
#define encoder_b 3        //encoder pin 3                  PD3
#define encoder_button 4   //encoder pin 4                  PD4
#define LED_RED 1          //RG-LED pin 8                   PB1
#define LED_GREEN 2  //RG-LED pin 9                         PB2

//---global variables-----------------------------------------

char serialBuffer[TX_Buffer_SIZE]; // Buffer für UART Übertragung
char rxBuffer[RX_Buffer_SIZE];     // Buffer für UART Emfang

uint8_t serialReadPos = 0; //variablen für den Ringbuffer
uint8_t serialWritePos = 0;
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

volatile bool encoderButtonFlag = 0;
volatile bool returnButtonFlag = 0;
volatile bool snoozeButtonFlag = false;
volatile char encoderSpinFlag = 0;

uint8_t brightness EEMEM = 150; //EEPROM variable


// SoftwareSerial mySoftwareSerial(6, 7); //Rx Tx //zur Debugging

//----Funktionsprototypen------------------------------------
//bool NMEA_read(string &currentString);

void alarm();

void interrupt_init(); //UART init
void appendSerial(char c); //UART recive
void serialWrite(char *c); //UART transmit

//---LCD init------------------------------------------------
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
Anzeige a(lcd);


unsigned char debug = 0;

void setup() {
	a.props.eepromBrightnes = &brightness;
	a.props.readEEPROM();
	//analogWrite(lcd_beleuchtung, eeprom_read_byte(&brightness)); //einschlaten der Beleuchtung
	lcd.begin(16, 2);
	lcd.display();
	lcd.write("Ankeralarm V2");
	lcd.write("T.Zwiener");
	_delay_ms(1000);
	interrupt_init();

	a.props.gpsdata.init(&serialReadPos, &serialWritePos, &rxReadPos, &rxWritePos, serialBuffer, rxBuffer);

	//-------------IO-config-------------------------------------------------
	//Output Config
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2)| (1 << DDB3) | (1 << DDB5);  //LED_RED  LED_GREEN  LCD Bachklight  Onbord LED
	DDRC |= (1 << DDC0); // LED pin14

	//Input Config
	DDRB &= ~(1 << DDB4);
	DDRD &= ~((1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD7)| (1<<DDD6));//Input PD2 PD3 PD4 PD7
	PORTD |= (1 << PORTB4) | (1 << PORTD7) | (1 << PORTB6); //Kofiguration encoderButton  returnButton PullUp

	pinMode(11, OUTPUT);

	a.activate(new GPSInfo);

}

// void updateGPSData() {
// 	if (NMEA_read(currentDataString)) {
// 		const gpsData &data = gpsData(currentDataString.c_str());
// 		currentDataString.clear();
// 		if (!data.isValid()) {
// 			// Ignoriere nicht valide Daten
// 			return;
// 		}
// 		//Update bei korrekten Daten
// 		a.props.myGPS.update(data);
// 	}
// }

void loop() {
	a.props.updateGPSData(); //Timing der updatefunktion ist wichting. entweder ausglöst durch intrupt oder ca alle 10s(update rate des gps Moduls)

	if (a.props.alarmActive) {
		unsigned long distance = a.props.centralPosition.distanceTo(a.props.myGPS.getCurrentPosition());
		bool alarmIsLow = true;
		while (distance > a.props.alarmRadius) {
			if (alarmIsLow){
				alarmIsLow = false;
				
				PORTB |=(1<<PORTB4);
			}

			if ((PIND &(1<<PIND6))==0){
				PORTB &=~(1<<PORTB4);
				snoozeButtonFlag = false;
				a.props.alarmActive = false;
				break;
			}
			
		}
	}

	while (encoderSpinFlag > 0) {
		a.encoderRight();
		encoderSpinFlag--;
	}
	while (encoderSpinFlag < 0) {
		a.encoderLeft();
		encoderSpinFlag++;
	}

	if (returnButtonFlag && (PIND & (1 << PIND7)) != 0) { //falling edge detection
		a.buttonReturn();
		returnButtonFlag = false;
	}

	if (encoderButtonFlag && (PIND & (1 << PIND4)) != 0) { //falling edge detection
		a.encoderPush();
		encoderButtonFlag = false;
	}

	if (a.props.myGPS.getGPSQuality() > 1) {
		//LCD Outputs
	} else {
		//print no GPS
	}

	//GPS angeschaltet
//    while (/* alarmmode */ random() < 0.5) {
//        vector<Position> posCollection;
//
//        for (int i = 0; i < 4; ++i) {
//            updateGPSData();
//            posCollection.push_back(a.props.myGPS.getCurrentPosition());
//        }
//        const Position startPosition = getMedian(posCollection);
//
//        //Radius einstellen
//        unsigned int radius = 100;
//
//        // Abstand zur Ursprungsposition testen.
//        while (random() < 0.5) {
//            updateGPSData();
//            if (startPosition.distanceTo(a.props.myGPS.getCurrentPosition()) > radius) {
//                alarm();
//            }
//        }
//    }
}



//----UART-Interface (Sereielle Schnittstelle für GPS Modul)------------------------
void appendSerial(char c) { //Transmit
	serialBuffer[serialWritePos] = c;
	serialWritePos++;

	if (serialWritePos >= TX_Buffer_SIZE) {
		serialWritePos = 0;
	}
}

void serialWrite(char c[]) { //receive
	for (uint8_t i = 0; i < strlen(c); i++) {
		appendSerial(c[i]);
	}
	if (UCSR0A & (1 << UDRE0)) {
		UDR0 = 0;
	}
}

ISR(USART_TX_vect){
		//receive Ring-Buffer
		if (serialReadPos != serialWritePos){
			UDR0 = serialBuffer[serialReadPos];
			serialReadPos++;
			if (serialReadPos >= TX_Buffer_SIZE) {
				serialReadPos = 0;
			}
		}
}

ISR(USART_RX_vect){
		//Transmit Ring-Buffer
		rxBuffer[rxWritePos] = UDR0;
		rxWritePos++;
		if (rxWritePos >= RX_Buffer_SIZE){
			rxWritePos = 0;
		}
}

void interrupt_init(void) {

	cli(); //disable Intrrupts

	//---config des UART-Interface (Sereielle Schnittstelle für GPS Modul)------------
	UBRR0H = UBRR_VAL >> 8; //Festlegung der Baudrate
	UBRR0L = UBRR_VAL & 0xFF;

	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << TXCIE0) |
			 (1 << RXCIE0);                 // Aktivierung von Tx | Interrupt aktivierung bei RXCn flage=true
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Asynchron 8N

	//---config des Encoders Interrupts-----------------------------------------------
	EIMSK = (1 << INT0);
	EICRA = (1 << ISC01) | (1 << ISC00);

	PCICR |= (1 << PCIE2);    //Pin change Interrupt aktiviern
	PCMSK2 |= (1 << PCINT20) | (1 << PCINT23); //Pin change Interrupt Maskieren für Pin 4 (PCINT 20)

	//---config der Timer-------------------------------------------------------------

	// Timer 1 //Status LEDs
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 3036;           // Timer nach obiger Rechnung vorbelegen so das t=1s
	TCCR1B |= (1 << CS12);  // 256 als Prescale-Wert spezifizieren
	TIMSK1 |= (1 << TOIE1); // Timer Overflow Interrupt aktivieren

	// Timer 2 //Dispaly Timeout



	//--Watchdog Timer------------------------------

	// WDTCSR |= (1<<WDCE) | (1<<WDE);
	// WDTCSR = (1<<WDIE)|(1<<WDE) | (1<<WDP3); // 4s / no interrupt, system reset

	sei(); //enable Interrupts
}

//---Interruptrutine------------------------------------------
ISR(INT0_vect){
		//---------------Encoder-------------------------------------------
		static unsigned long lastInterruptTime = buttonDebounceTime;
		unsigned long interruptTime = millis();
		bool messungPin1 = 0, messungPin1Alt = 0;
		// If interrupts come faster than 5ms, assume it's a bounce and ignore
		if (interruptTime - lastInterruptTime > 1)    {

			messungPin1 = ((PIND & (1 << encoder_a)) == 0) ? 0 : 1;
			if ((messungPin1 == HIGH) && (messungPin1Alt == LOW)) {
				if ((PIND & (1 << PIND3)) != 0) {
					encoderSpinFlag--;
				} else {
					encoderSpinFlag++;
				}
			}
			messungPin1Alt = messungPin1;

			//Restrict value from 0 to +200
			//radius = min(200, max(0,radius));
		}
		// Keep track of when we were here last (no more than every 5ms)
		lastInterruptTime = interruptTime;
}

ISR(PCINT2_vect)
		{
				static unsigned long lastInterruptTime = 100;
				unsigned long interruptTime = millis();
				if (interruptTime - lastInterruptTime > 1)
				{
					if ((PIND & (1 << encoder_button)) == 0) {
						encoderButtonFlag = true;
					}
					if ((PIND & (1 << returnButton)) == 0) {
						returnButtonFlag = true;
					}

				}
				lastInterruptTime = interruptTime;
		}

ISR(TIMER1_OVF_vect)
		{

				//------------------------------GPS-Status LED---------------------------

				TCNT1 = 3036; // Timer vorbelegt so dass delta_T= 1s

		switch (a.props.myGPS.getGPSQuality()){
			case 0:
				PORTB ^= (1 << LED_RED); //toggle LED_RED
			PORTB &= ~(1 << LED_GREEN); //write LED_GREEN LOW
			break;

			case 1:
				PORTB &= ~(1 << LED_GREEN); //write LED_GREEN LOW
			PORTB |= (1 << LED_RED);
			break;

			case 2:
				PORTB |= (1 << LED_GREEN); //write LED_GREEN HIGH
			PORTB |= (1 << LED_RED);
			break;

			case 3:
				PORTB |= (1 << LED_GREEN); //write LED_GREEN HIGH
			PORTB &= ~(1 << LED_RED);
			break;

			case 4:
				PORTB ^= (1 << LED_GREEN);
			PORTB &= ~(1 << LED_RED);
			break;
		}

		}
