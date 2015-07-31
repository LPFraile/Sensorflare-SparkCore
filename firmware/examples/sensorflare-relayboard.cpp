/*"name": "sensorflare",
Author: "LPFraile <lidiapf0@gmail.com>",
License: "BSD",
Version: "0.0.1",
Description: "Include your Particle Core on Sensorflare"
File: Example: Control trough your Sensorflare account the digital outputs of your Particle Core
*/
//Include the Sensorflare library 
#include "sensorflare/sensorflare.h"

//Initialize objects from the library
//One object of the class "DigitalOut" is initialized for 
//every digital output that will be remote control
SensorFlare::DigitalOut outputPin1(D0);
SensorFlare::DigitalOut outputPin2(D1);
SensorFlare::DigitalOut outputPin3(D2);
SensorFlare::DigitalOut outputPin4(D3);

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


