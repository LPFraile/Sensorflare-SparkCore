//Include the SensorFlare library 
#include "sensorflare.h"

//Initialize objects from the library
//One object of the class "DigitalOut" is initialized for 
//every digital output that will be remote control
SensorFlare::DigitalOut outputPin1(D1);
SensorFlare::DigitalOut outputPin2(D2);
SensorFlare::DigitalOut outputPin3(D3);
SensorFlare::DigitalOut outputPin4(D4);

void setup() {
    
// Call the begin() functions for every object of the classes "DigitalOut" and 
//"PWMout" to be wired up correct and available.
    outputPin1.begin();
    outputPin2.begin();
    outputPin3.begin();
    outputPin4.begin();

}

void loop() {
    

}
