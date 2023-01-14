
#include "MicroBit.h"

MicroBit uBit;

MicroBitButton buttonA (MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB (MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);
MicroBitThermometer thermometer;

void Temperatur();
void Buzzer (int Volume);

int main() {
    uBit.init();

    int temperature = 0;
    int buzzerTone = 512;
    int Motor = 900;
    int Volume;
    int wert;
    
    uBit.io.P13.isDigital();
    uBit.io.P13.isInput();
//Lüfter
    uBit.io.P0.isOutput();
    uBit.io.P0.isAnalog();
//Buzzer
    uBit.io.P1.isOutput();
    uBit.io.P1.isAnalog();
//LED - Rot
    uBit.io.P2.isOutput();
    uBit.io.P2.isDigital();
//LED - Gelb
    uBit.io.P8.isOutput();
    uBit.io.P8.isDigital();
//LED - Grün
    uBit.io.P12.isOutput();
    uBit.io.P12.isDigital();


while(1){
        
        temperature = (thermometer.getTemperature());

    if (temperature < 21){
        Temperatur();
        uBit.io.P0.setAnalogValue(0);
        uBit.io.P1.setAnalogValue(0);
        uBit.io.P2.setDigitalValue(0);
        uBit.io.P8.setDigitalValue(0);
        uBit.io.P12.setDigitalValue(1);

    } else if (temperature >22){
        while (thermometer.getTemperature() > 22) {
            uBit.display.print(thermometer.getTemperature());
            uBit.io.P0.setAnalogValue(1023);
            Buzzer(500);
}
        wert = uBit.io.P13.getDigitalValue();
        uBit.display.print(wert);
        if(wert==1){
            uBit.display.print("HEY");
        }
        Temperatur();
        uBit.io.P0.setAnalogValue(1023);
        Buzzer(300);
        uBit.io.P2.setDigitalValue(1);
        uBit.io.P8.setDigitalValue(0);
        uBit.io.P12.setDigitalValue(0);
        

    } else {
        Temperatur();
        uBit.io.P0.setAnalogValue(0);
        uBit.io.P1.setAnalogValue(0);
        uBit.io.P2.setDigitalValue(0);
        uBit.io.P8.setDigitalValue(1);
        uBit.io.P12.setDigitalValue(0);
    }
}

    release_fiber();
    }

void Temperatur () {
    uBit.display.scroll (thermometer.getTemperature());}

void Buzzer (int Volume){
     uBit.io.P0.setAnalogValue(1023);
    uBit.io.P1.setAnalogValue(512);
    uBit.io.P1.setAnalogPeriod(1);
    uBit.sleep(Volume);
    uBit.io.P0.setAnalogValue(1023);
    uBit.io.P1.setAnalogValue(0);
    uBit.io.P1.setAnalogPeriod(0);
}
