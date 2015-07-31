/*"name": "sensorflare",
Author: "LPFraile <lidiapf0@gmail.com>",
License: "BSD",
Version: "0.0.1",
Description: "Include your Particle Core on Sensorflare"
File: source file
*/
#include "sensorflare.h"
//Structure to keep in EEPROM memory the value of output pins
struct dataStruct
{
    int digitalPin[8];
    struct pwmPin{
        int pin;
        int value;
    };
    pwmPin pwmoutput[8];
};

union {
    dataStruct outputData;
    char eeArray[sizeof(outputData)];
} EEPROMData;

char stringvalue[40];
// Constructor
//Constructor of Digital Output controller elements
SensorFlare::DigitalOut::DigitalOut(int _number)
{
    number = _number;
    state = LOW;
}
//Constructor of PWM Output controller elements
SensorFlare::PWMOut::PWMOut(int _number)
{
    number = _number;
 
}
//Constructor of Variable publish element by defult PUBLIC
SensorFlare::VarPublish::VarPublish(String _name)
{
    name = _name;
    name.toCharArray(Arrayname,name.length()+1);
    lastTime=0UL;
    property="PUBLIC";
}
//Constructor of Variable publish element by choose between PUBLIC and PRIVATE
SensorFlare::VarPublish::VarPublish(String _name,String _property)
{
    name = _name;
    name.toCharArray(Arrayname,name.length()+1);
    lastTime=0UL;
    property=_property;
}
//Initializers that should be called in the `setup()` function
//Initizalize the pin as output and the last value received 
void SensorFlare::DigitalOut::begin()
{
    pinMode(number, OUTPUT);
    Spark.function("digital",controlPin);
    //Initialize the output with the last receive value from SensorFlare    
    readEEPROM();
    digitalWrite(number,EEPROMData.outputData.digitalPin[number]);
  
}
//Initizalize the pin as PWM output and the last value received
void SensorFlare::PWMOut::begin()
{
    pinMode(number, OUTPUT);
    Spark.function("pwm",controlPWM);
    //Initialize the output with the last receive value from Sensorflare    
    readEEPROM();
    analogWrite(number,EEPROMData.outputData.digitalPin[number]);
    for (int i=0;i<8;i++){
        if (EEPROMData.outputData.pwmoutput[i].pin==number)
        {
            analogWrite(number,EEPROMData.outputData.pwmoutput[i].value);
            value=EEPROMData.outputData.pwmoutput[i].value;
        }
    }

}
//Initizalize the int variables
void SensorFlare::VarPublish::begin(int _val)
{
    Spark.variable(Arrayname, &_val, INT);
}
//Initizalize the float variables
void SensorFlare::VarPublish::begin(float _val)
{
    Spark.variable(Arrayname, &_val, INT);
}
// Main API functions that the library provides
// typically called in `loop()`
//Method that publish the variable (int) _val every _period time
int SensorFlare::VarPublish::Publish(int _val, int _periode)
{
     var_int=_val;
     periode=_periode*1000;
     unsigned long now = millis();
    if (property=="PRIVATE"){
        if (now-lastTime>periode) {
        lastTime = now;
        sprintf(stringvalue,"%u",var_int);
        Spark.publish(name,stringvalue,60,PRIVATE);
       }
       return 0;
    }
    else if (property=="PUBLIC"){
        if (now-lastTime>periode) {
        lastTime = now;
        sprintf(stringvalue,"%u",var_int);
        Spark.publish(name,stringvalue);
       }
       return 1;
    }
    else{
        return -1;//Return -1 if the variable could be publish because a mistake on the property
    }
}

//Method that publish the variable (float) _val every _period time
int SensorFlare::VarPublish::Publish(float _val, int _periode)
{
     var_float=_val;
     periode=_periode*1000;
     unsigned long now = millis();
    if (property=="PRIVATE"){
        if (now-lastTime>periode) {
        lastTime = now;
        sprintf(stringvalue,"%f",var_float);
        Spark.publish(name,stringvalue,60,PRIVATE);
       }
       return 0;
    }
    else if (property=="PUBLIC"){
        if (now-lastTime>periode) {
        lastTime = now;
        sprintf(stringvalue,"%f",var_float);
        Spark.publish(name,stringvalue);
       }
       return 1;
    }
    else{
        return -1;
    }
}

//Function for open/close pin
//The structure of the receive command is pin: state where state is on or off
int controlPin(String command) {
    int index=command.indexOf(":");
     String pinout=command.substring(0,index);
     String state=command.substring(index+1);
     int pin=pinout.toInt();
    
    if (state=="on") {
        digitalWrite(pin,HIGH);
        EEPROMData.outputData.digitalPin[pin]=1;
        writeEEPROM();
        return 1;
    }
    else if (state=="off") {
        digitalWrite(pin,LOW);
        EEPROMData.outputData.digitalPin[pin]=0;
        writeEEPROM();
        return 0;
    }
    else {
        //EEPROMData.eevar.state[pin]=-1;
        return -1;//return -1 if the command received has not the correct structure
    }
    
}

//Function that control the specific brightness of the led conected to specific pwmpin.
//the structure of the command is pwmpin:brightness
int controlPWM(String command) {
     int index=command.indexOf(":");
     String pwmpin=command.substring(0,index);
     String val=command.substring(index+1);
     int pin=pwmpin.toInt();
     int value=val.toInt();
    if (value<256&&value>=0){
        analogWrite(pin,value);
        if (pin==10){
            EEPROMData.outputData.pwmoutput[2].pin=pin;
            EEPROMData.outputData.pwmoutput[2].value=value;
         }
        else if (pin==11){
            EEPROMData.outputData.pwmoutput[3].pin=pin;
            EEPROMData.outputData.pwmoutput[3].value=value;
        }
        else if (pin>13&&pin<18){
            EEPROMData.outputData.pwmoutput[pin-10].pin=pin;
            EEPROMData.outputData.pwmoutput[pin-10].value=value;
        }
        else if (pin<2){
            EEPROMData.outputData.pwmoutput[pin].pin=pin;
            EEPROMData.outputData.pwmoutput[pin].value=value;
        }
        writeEEPROM();
        return value;
    }
    else{
        return -1;// return -1 if the pin sended on the command is not the PWM output ones
    }
}

//function to read from the EEPROM
void readEEPROM(void) {
    for (int i=0; i<sizeof(dataStruct); i++) {
        EEPROMData.eeArray[i] = EEPROM.read(i);
    }    
}
//function to write on the EEPROM
void writeEEPROM(void) {
    for (int i=0; i<sizeof(dataStruct); i++) {
        EEPROM.write(i, EEPROMData.eeArray[i]);
    }    
}
