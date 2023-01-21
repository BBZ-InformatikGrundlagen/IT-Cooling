#include "MicroBit.h"

MicroBit uBit;

//Dem Microbit sagen, dass der Thermostat benutzt wird.
MicroBitThermometer thermometer;

//Funktion für die Temperaturnachfrage.
void Temperatur();
//Funktion für den Buzzer mit der frei zu wählenden Dauer des piepsens.
void Buzzer (int dauer);
//Funktion für LED ansteuerung, so muss nicht jedesmal uBit.io.Px.... eingegeben werden.
void setLED (int rot, int gelb, int grün);

int main() {
    uBit.init();
    //Lüfter Analoges Output
    uBit.io.P0.isOutput();
    uBit.io.P0.isAnalog();
    //Buzzer Analoges Output
    uBit.io.P1.isOutput();
    uBit.io.P1.isAnalog();
    //LED - Rot Digitales Output
    uBit.io.P2.isOutput();
    uBit.io.P2.isDigital();
    //LED - Gelb Digitales Output
    uBit.io.P8.isOutput();
    uBit.io.P8.isDigital();
    //LED - Grün Digitales Output
    uBit.io.P12.isOutput();
    uBit.io.P12.isDigital();

    while(1) {
        
        // "temp" definieren als Temperatur.
        int temp = uBit.thermometer.getTemperature();
        //Temperatur wiedergabe auf Display.
            Temperatur();
        // Wenn Temperatur tiefer/gleich wie 21°C
        if (temp <= 21) {
            //Grünes LED AN, Rot/Gelb AUS.
            setLED( 0, 0, 1);
            // Lüfter & Buzzer AUS.
            uBit.io.P0.setAnalogValue(0);
            uBit.io.P1.setAnalogValue(0);

        //Wenn Temperatur Höher als 21°C UND tiefer/gleich wie 23°C
        } else if (temp > 21 && temp <= 23) {
            //Gelbes LED AN, Rot/Grün AUS.
            setLED( 0, 1, 0);
            // Lüfter & Buzzer AUS.
            uBit.io.P0.setAnalogValue(300);
            uBit.io.P0.setAnalogPeriod(100);
            uBit.io.P1.setAnalogValue(0);

        //Wenn Temperatur höher wie 23°C.
        } else {
            //Lüfter AN mit Wert von 1023. 
            uBit.io.P0.setAnalogValue(1023);
            uBit.io.P0.setAnalogPeriod(100);
            //Rotes LED AN, Gelb/Grün AUS
            setLED( 1, 0, 0);
            //Funktion für den Buzzer mit einer Signallänge von 0.8Sek.
                Buzzer(800);
                }
            }
        uBit.sleep(200);
        }
    
    
//Funktion Temperatur.
void Temperatur () {
    uBit.display.scroll (thermometer.getTemperature());}

//Funktion Buzzer.
void Buzzer (int dauer){
    uBit.thermometer.getTemperature();
    uBit.io.P1.setAnalogValue(512);
    uBit.io.P1.setAnalogPeriod(1);
    Temperatur();
    uBit.sleep(dauer);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriod(0);
    uBit.sleep(dauer);
    uBit.thermometer.getTemperature();
}

//Funktion LED.
void setLED(int rot, int gelb, int grün){
    uBit.io.P2.setDigitalValue(rot);
    uBit.io.P8.setDigitalValue(gelb);
    uBit.io.P12.setDigitalValue(grün);}