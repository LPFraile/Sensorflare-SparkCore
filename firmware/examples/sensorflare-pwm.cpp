//Include the SensorFlare library 
#include "sensorflare.h"

//Initialize objects from the library

//One object of the class "PWMOut" is initialized for 
//every PWM output that will be remote control
SensorFlare::PWMOut pwm(A0);



void setup() {
    
// Call the begin() functions for every object of the classes "DigitalOut" and 
//"PWMout" to be wired up correct and available.

    pwm.begin();
    

}

void loop() {
    
 

}