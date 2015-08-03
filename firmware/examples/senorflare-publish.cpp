/*"name": "sensorflare",
Author: "LPFraile <lidiapf0@gmail.com>",
License: "BSD",
Version: "0.0.1",
Description: "Include your Particle Core on Sensorflare"
File: Examplo:Publish on your Sensorflare account some variables of the code upload on your Particle core.
*/
//Include the Sensorflare library 
#include "sensorflare/sensorflare.h"

//Initialize objects from the library

//One object of the class "PWMOut" is initialized for 
//every PWM output that will be remote control
SensorFlare::PWMOut pwm(A0);

//One object of the class "VarPublish" is initialized for every variable
//that will be published in order to access remotely from the cloud
//The argument that name the variable has a maximum of 12 characters
//Both methods initialized the variable that will be published as PUBLIC 
SensorFlare::VarPublish varTem("temperature");
SensorFlare::VarPublish varPir("pir","PUBLIC");
//Initialized the variable that will be published as PRIVATE
SensorFlare::VarPublish varLight("light","PRIVATE");

//The variables to publish must be declared
float temperature;
float light;
int status;

// Initialize the different variables that will be used in the program
int tem_pin=A3;
int light_pin=A4;
int pir_pin=D0;
int new_status;
bool change;

void setup() {
    
//Call the begin() functions for every object of the classes "DigitalOut", "PWMout"
//and VarPublish to be wired up correct and available.

    pwm.begin();
    varTem.begin(temperature);
    varLight.begin(light);
    varPir.begin(status);
//Set the extra pins that are used on the program, but are not controlled remotely
    pinMode(pir_pin,INPUT);

}

void loop() {
    
    // Temperature sensor
    float tem= analogRead(tem_pin); // read the value from the sensor
    // The returned value from the Core is going to be in the range from 0 to 4095
    // Calculate the voltage from the sensor reading
    float voltage = (tem * 3.3) / 4095;
    float deg =voltage* 100; // multiply by 100 to get degrees in K
    float temperature = deg - 273.15; // subtract absolute zero to get degrees Celsius
    
    //Luminosity
    float photocell= analogRead(light_pin); // read the value from the sensor
    // The returned value from the Core is going to be in the range from 0 to 4095
    // Calculate the voltage from the sensor reading
    float Vphotocell = ((photocell * 3.3) / 4095);
    float rl=(Vphotocell*10)/(3.3-Vphotocell);//Photoresistor value in KΩ
    float value=500/rl;//luminosity 
    int light= (int) value;    
    
    //Find the change of state of the PIR sensor. Recognize move
    new_status=digitalRead(pir_pin);
    if (status!=new_status){
        status=new_status;
        change=TRUE;
    }
    
    //Publish every time that exist a change in the pin on which is connect the output of the PIR
    if (change==TRUE) {
        varPir.Publish(status,0);//Publish the variable at the called method time 
        change=FALSE;
    }
    
    //Publish the variables every 15 seconds.
    varTem.Publish(temperature,15);
    varLight.Publish(light,15);

}
