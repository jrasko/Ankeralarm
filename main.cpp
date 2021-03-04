#include <iostream>
#include <string>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"

using namespace std;

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
#define F_CPU 16000000UL  // Systemtakt in Hz - Definition als unsigned long beachten 
                         // Ohne ergeben sich unten Fehler in der Berechnung
#endif

//---defines--------------------------------------------------

//---UART-Interface (Sereielle Schnittstelle für GPS Modul)
#define BAUD 9600UL      // Baudrate
// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
#define RX_Buffer_SIZE 128  //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128  //einstelleng der gößes des sende Buffers;

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif

// ----IO-definition-----------------------------------------
#define ledPin 14  					//LED pin 14
#define debug_led 13 				// onboard Led
#define lcd_beleuchtung 11 			// hintergundbeleuchtung des LCDs 
#define schalter 7 					//Schalter 1
#define summer 12 					//Summer
#define encoder_a 2 				//encoder pin 2 (32)
#define encoder_b 3 				//encoder pin 3
#define encoder_button 4 			//encoder pin 4
#define LED_rot 9  					//RG-LED pin 8
#define LED_grun 10 				//RG-LED pin 9      


//---global variables-----------------------------------------
char serialBuffer[TX_Buffer_SIZE]; // Buffer für UART Übertragung
char rxBuffer[RX_Buffer_SIZE];	 // Buffer für UART Emfang

uint8_t serialReadPos = 0; //variablen für den Ringbuffer
uint8_t serialWritePos = 0; 
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0; 

volatile int encoderWert = 0;
GPS myGPS;

//----Funktionsprototypen------------------------------------
bool NMEA_read(string &currentString);

void alarm();

int main() {

    DateTime t1(31, 7, 20, 0, 0, 0);
    DateTime t2(1, 8, 20, 0, 0, 0);
    DateTime s = t2 - t1;
    cout << s.getDay() << "." << s.getMonth() << "." << s.getYear() << " " << s.getHours() << ":" << s.getMinutes()
         << ":" << s.getSeconds() << endl;
    cout << myGPS.getAccuracy() << endl;

   // myGPS.update(gpsData);

}



void updateGPSData() {
    string currentDataString;
    if (NMEA_read(currentDataString)) {
        try {
            myGPS.update(gpsData(currentDataString.c_str()));
        } catch (exception &e) { 
            return;
        }
        
    }
}

void loop() {

    updateGPSData(); //Timing der updatefunktion ist wichting. entweder ausglöst durch intrupt oder ca alle 10s(update rate des gps Moduls)

    if (myGPS.getGPSQuality() > 1) {
        //LCD Outputs


    }
    else{
        //print no GPS
    }


    //GPS angeschaltet
    while (/* alarmmode */ random()) {
        vector<Position> posCollection;

        for (int i = 0; i < 4; ++i) {
            updateGPSData();
            posCollection.push_back(myGPS.getCurrentPosition());
        }
        const Position startPosition = getMedian(posCollection);

        //Radius einstellen
        unsigned int radius = 100;

        // Abstand zur Ursprungsposition testen.
        while (random()) {
            updateGPSData();
            if (startPosition.distanceTo(myGPS.getCurrentPosition()) > radius) {
                alarm();
            }
        }


    }


}

void alarm() {
    // Aktiviere Alarm
}

bool
NMEA_read(string &currentString) {                      // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
    char nextChar = '\0';
    bool newDataAvailable;
    bool string_complete = false;
    //bool newValidNMEA = false;
    //
    if (rxReadPos != rxWritePos) {
        nextChar = rxBuffer[rxReadPos];

        if (nextChar == '$' && !newDataAvailable) {
            newDataAvailable = true;
        } else {
            return false;
        }
        //Checking for new Data incoming
        //Expanding of the CurrentDataString with the current char
        if (newDataAvailable) {
            currentString += nextChar; //zusammen bauen des Strings
        }
        //String is finished
        if (nextChar == '\r') {
            currentString += '\r';
            currentString += '\n';

            string_complete = true; // wird aktiviert wenn ein NEMA datensatz eingegenen ist
            newDataAvailable = false; // für datenverarbeitung  
            //hier muss ein Timer eingestezt werden der bei einem Abrruch der Verbindung newDataAvaliable auf false setzet 
        }

        rxReadPos++;

        if (rxReadPos >= RX_Buffer_SIZE) {
            rxReadPos = 0;
        }

    }
    
    return false;
}

void interrupt_init(void){

    cli(); //disable Intrrupts 

    //---config des UART-Interface (Sereielle Schnittstelle für GPS Modul)------------
    UBRR0H = UBRR_VAL >> 8;   //Festlegung der Baudrate
    UBRR0L = UBRR_VAL & 0xFF;

    UCSR0B = (1<<TXEN0)|(1<<RXEN0) | (1<<TXCIE0)|(1<<RXCIE0); // Aktivierung von Tx | Interrupt aktivierung bei RXCn flage=true 
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);  // Asynchron 8N

    //---config des Encoders Interrupts-----------------------------------------------
    EICRA = (1<< ISC01) | (1<< ISC00);

    //---config der Timer-------------------------------------------------------------
    
    // Timer 1	
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 3036;                                  // Timer nach obiger Rechnung vorbelegen so das t=1s
    TCCR1B |= (1 << CS12);                          // 256 als Prescale-Wert spezifizieren
    TIMSK1 |= (1 << TOIE1);                         // Timer Overflow Interrupt aktivieren  
    
    sei(); //enable Interrupts
}
//---Interruptrutine------------------------------------------
ISR(INT0_vect){

    //---------------Encoder-------------------------------------------
    static unsigned long lastInterruptTime = 5;
    unsigned long interruptTime = millis();
    int messungPin1 = 0, messungPin1Alt = 0;
    // If interrupts come faster than 5ms, assume it's a bounce and ignore
    if (interruptTime - lastInterruptTime > 1) {        
        messungPin1 = digitalRead(encoder_a);
        if ((messungPin1 == HIGH) && (messungPin1Alt == LOW)) {
            if (digitalRead(encoder_b) == HIGH) {
                encoderWert++;
                } else {
                encoderWert--;				
            }			
        }
        messungPin1Alt = messungPin1;

        //Restrict value from 0 to +200
        //radius = min(200, max(0,radius));	
    }
    // Keep track of when we were here last (no more than every 5ms)
    lastInterruptTime = interruptTime;
}
ISR(TIMER1_OVF_vect){
	
	//------------------------------GPS-Status LED---------------------------
	
	TCNT1 = 3036;   // Timer vorbelegt so dass delta_T= 1s
	switch(myGPS.getGPSQuality()){
		case 0:
		digitalWrite(LED_rot, digitalRead(LED_rot) ^ 1);
		digitalWrite(LED_grun, LOW);
		break;
		case 1:
		digitalWrite(LED_grun, LOW);
		digitalWrite(LED_rot, HIGH);
		break;
		case 2:
		digitalWrite(LED_grun, HIGH);
		digitalWrite(LED_rot, HIGH);
		break;
		case 3:
		digitalWrite(LED_grun, HIGH);
		digitalWrite(LED_rot, LOW);		
		break;
		case 4:
		digitalWrite(LED_grun, digitalRead(LED_grun) ^ 1);
		digitalWrite(LED_rot, LOW);
		break;
	}
}
