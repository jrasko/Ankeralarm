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
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "GPS/GPS.h"
#include "GPS/gpsData.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "GUI/Utils.h"
#include "GUI/GPSInfo.h"

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
#define RX_Buffer_SIZE 128                              //einstellung der Größe des emfangs Buffers
#define TX_Buffer_SIZE 128                              //einstelleng der gößes des sende Buffers;

#if ((BAUD_ERROR < 990) || (BAUD_ERROR > 1010))
#error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch!
#endif

// ----IO-definition-----------------------------------------
#define ledPin 14          //LED pin 14
#define debug_led 13       // onboard Led
#define lcd_beleuchtung 11 // hintergundbeleuchtung des LCDs
#define returnButton 7         //Schalter 1 PD7  PCINT 23
#define summer 12          //Summer
#define encoder_a 2        //encoder pin 2 (32)
#define encoder_b 3        //encoder pin 3
#define encoder_button 4   //encoder pin 4
#define LED_rot 9          //RG-LED pin 8
#define LED_grun 10        //RG-LED pin 9

//---global variables-----------------------------------------
char serialBuffer[TX_Buffer_SIZE]; // Buffer für UART Übertragung
char rxBuffer[RX_Buffer_SIZE];     // Buffer für UART Emfang

uint8_t serialReadPos = 0; //variablen für den Ringbuffer
uint8_t serialWritePos = 0;
uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

volatile bool encoderButtonFlag = 0;
volatile bool returnButtonFlag = 0;
volatile int encoderSpinFlag = 0;

string currentDataString;

// SoftwareSerial mySoftwareSerial(6, 7); //Rx Tx //zur Debugging

//----Funktionsprototypen------------------------------------
bool NMEA_read(string &currentString);

void alarm();

void interrupt_init(); //UART init

void appendSerial(char c); //UART recive
void serialWrite(char *c); //UART transmit

//---LCD init------------------------------------------------
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
Anzeige a(lcd);

void setup() {

    analogWrite(lcd_beleuchtung, 150); //einschlaten der Beleuchtung
    lcd.begin(16, 2);
    lcd.display();
    lcd.write("Ankeralarm V2");
    lcd.write("T.Zwiener");
    delay(1000);
    interrupt_init();

    //-------------IO-config-------------------------------------------------

    pinMode(ledPin, OUTPUT);
    // pinMode(schalter, INPUT_PULLUP);
    pinMode(summer, OUTPUT);
    pinMode(encoder_a, INPUT);
    pinMode(encoder_b, INPUT);
    pinMode(encoder_button, INPUT_PULLUP);
    pinMode(LED_rot, OUTPUT);
    pinMode(LED_grun, OUTPUT);
    pinMode(debug_led, OUTPUT);
    pinMode(returnButton, INPUT_PULLUP);

    a.activate(new GPSInfo);
}

void updateGPSData() {
    if (NMEA_read(currentDataString)) {
        const gpsData &data = gpsData(currentDataString.c_str());
        currentDataString.clear();
        if (!data.isValid()) {
            // Ignoriere nicht valide Daten
            return;
        }
        //Update bei korrekten Daten
        a.props.myGPS.update(data);
    }
}

void loop() {

    updateGPSData(); //Timing der updatefunktion ist wichting. entweder ausglöst durch intrupt oder ca alle 10s(update rate des gps Moduls)
    //lcd.write(a.props.myGPS.getCurrentPosition().toString().c_str());

    while (encoderSpinFlag > 0) {
        a.encoderRight();
        encoderSpinFlag--;
    }
    while (encoderSpinFlag < 0) {
        a.encoderLeft();
        encoderSpinFlag++;
    }

    if (returnButtonFlag && digitalRead(returnButton)) {
        a.buttonReturn();
        returnButtonFlag = false;
    }

    if (encoderButtonFlag && digitalRead(encoder_button)) { //falling edge detection
        a.encoderPush();
        digitalWrite(LED_grun, digitalRead(LED_grun) ^ 1);
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

bool NMEA_read(string &currentString) { // Auslesen des "Ringspeichers" und sortieren der NMEA Sätze
    char nextChar;
    static bool newDataAvailable = false;
    static int countIncomingChars = 0;

    if (rxReadPos == rxWritePos) {
        //No Data available
        return false;
    }
    // Hier ansetzen falls letzter eingehender char benötigt wird
    nextChar = rxBuffer[rxReadPos];
    if (nextChar == '$') {
        // Beginning of a new DataString
        newDataAvailable = true;
    }
    if (!newDataAvailable) {
        rxReadPos++;
        if (rxReadPos >= RX_Buffer_SIZE) {
            rxReadPos = 0;
        }
        return false;
    }

    currentString.push_back(nextChar);

    if (nextChar == '\r') {
        //String is complete
        newDataAvailable = false;
        countIncomingChars = 0;
        return true;
    }
    countIncomingChars++;
    rxReadPos++;
    if (rxReadPos >= RX_Buffer_SIZE) {
        rxReadPos = 0;
    }
    if (countIncomingChars >= maxIncomingMessageLength) {
        newDataAvailable = false;
        countIncomingChars = 0;
        return false;
    }
    return false;
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

char peekChar(void) {
    char ret = 'n';
    if (rxReadPos != rxWritePos) {
        ret = rxBuffer[rxReadPos];
    }
    return ret;
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

    // Timer 1
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 3036;           // Timer nach obiger Rechnung vorbelegen so das t=1s
    TCCR1B |= (1 << CS12);  // 256 als Prescale-Wert spezifizieren
    TIMSK1 |= (1 << TOIE1); // Timer Overflow Interrupt aktivieren

    sei(); //enable Interrupts
}

//---Interruptrutine------------------------------------------
ISR(INT0_vect){
        //---------------Encoder-------------------------------------------
        static unsigned long lastInterruptTime = buttonDebounceTime;
        unsigned long interruptTime = millis();
        int messungPin1 = 0, messungPin1Alt = 0;
        // If interrupts come faster than 5ms, assume it's a bounce and ignore
        if (interruptTime - lastInterruptTime > 1)
        {
            messungPin1 = digitalRead(encoder_a);
            if ((messungPin1 == HIGH) && (messungPin1Alt == LOW)) {
                if (digitalRead(encoder_b) == HIGH) {
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
                    if (digitalRead(encoder_button) == 0) {
                        encoderButtonFlag = true;
                    }
                    if (digitalRead(returnButton) == 0) {
                        returnButtonFlag = true;
                        digitalWrite(LED_rot, HIGH);
                    }

                }
                lastInterruptTime = interruptTime;
        }

ISR(TIMER1_OVF_vect)
        {

                //------------------------------GPS-Status LED---------------------------

                TCNT1 = 3036; // Timer vorbelegt so dass delta_T= 1s
                /*
                switch (a.props.myGPS.getGPSQuality()){
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
                */
        }
