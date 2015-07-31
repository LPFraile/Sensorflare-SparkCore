# Sensorflare-SparkCore

Sensorflare library to include your Spark Core device from Particle on Sensorflare platform.

DigitalOutput class:
--
This class describes the elements that will be controlled with digital output.  Every object is then associated with the specific pin that will be remote control.

-   SensorFlare::DigitalOut ObjectName (DigitalPin): It is the constructor of the DigitalOut class. Instance an object of the DigitalOut class called ObjectName and assigned it the pin DigitalPin. DigitalPin must be referenced as are named on the Spark Core board (D0, D1, D2, D3, D4, D5, D6 or D7) in which is connected the specific actuator that want to be remote controlled.
-   ObjectName.begin(): The “begin()” method must be called on the setup() function in order to start to control remotely the specific digital pin as output.

PWMOut class:
--
This class defines the output elements that will be controlled remotely by a PWM signal. A parameter from 0 to 255 chose the duty cycle of the signal output.

-   SensorFlare::PWMOut ObjectName(PWMOutput): It is the constructor of the PWMOut class. Will be instanced and object of the PWMOut class called ObjectName for each PWM output that is used and assigned it the corresponding pin PWMPin . PWMPin must be one of the pins that provides this functionality on Spark Core board and namely with the typically name on the board (A0, A1, A4, A5, A6, A7, D0 or D1) in which is connected the specific PWM actuator that want to be remote controlled.    
-   ObjectName.begin():The begin method must be called on setup() function in order to start to control remotely the specific output pin with a PWM signal.

VarPublish class: 
--
This class is used to publish variables on Sensorflare platform.

-   SensorFlare::VarPublish ObjectName("VariableName"):It is the default constructor of the VarPublish class. Instance an object, called ObjectName, for each variable that will be published on Sensorflare platform with the name VariableName.The name is limited to 12 characters. The variable will be public on the cloud which means that another Spark Core user can access it.
-   SensorFlare::VarPublish ObjectName("VariableName",”PRIVATE”):It is a second constructor of the VarPublish class. Instance and object called ObjectName for each variable that will be published on the Sensorflare platform with the name VariableName.The name is limited to 12 characters. The variable will be private upload on the cloud which means that only the user can access it.
-   ObjectName.Publish(Variable, period):The Publish method will publish the specific Variable every period time with the name that has been chosen before "VariableName". Two kinds of variables can be published: int or float.

# Code example for PWM signal control
Include the SensorFlare library 
```cpp
#include "sensorflare.h"
```
Initialize objects from the library:One object of the class "PWMOut" is initialized for 
every PWM output that will be remote control
```cpp
SensorFlare::PWMOut pwm(A0);
```
Call the begin() method of the object on the setup() function to initialize the elemnet.
```cpp
void setup() {
    pwm.begin();
}
```

# Code example for Digital Outputs control

Include the SensorFlare library 
```cpp
#include "sensorflare.h"
```
Initialize objects from the library:One object of the class "DigitalOut" is initialized for every digital output that will be remote control. DO, D1, D2 and D3 will be the remote control digital pins in this case
```cpp
SensorFlare::DigitalOut outputPin1(D0);
SensorFlare::DigitalOut outputPin2(D1);
SensorFlare::DigitalOut outputPin3(D2);
SensorFlare::DigitalOut outputPin4(D3);
```
Call the begin() method on the setup() functions for every object of the classes "DigitalOut" to be wired up correct and available the remote control fuctionality.
```cpp
void setup() {
    outputPin1.begin();
    outputPin2.begin();
    outputPin3.begin();
    outputPin4.begin();
}
```

# Code example for observe variables of our code remotly on Sensorflare
Include the SensorFlare library 
```cpp
#include "sensorflare.h"
```
Initialize objects from the library: One object of the class "VarPublish" is initialized for every variable
that will be published in order to access remotly from Sensorflare. Both methods initialized the variable that 
will be published as PUBLIC. 
```cpp
SensorFlare::VarPublish varTem("temperature");
SensorFlare::VarPublish varPir("pir","PUBLIC");
```
For initialized the variable that will be published as PRIVATE

SensorFlare::VarPublish varLight("light","PRIVATE");
```
The Publish(Variable,period) method will be called on loop() function for every object that represent each variable which want to be published by associated the respective Variable and a Period on seconds 
```cpp
void loop() {
    ...
    int status;
    float temperature;
    int light;
    ...
    //Publish the variable at the called method time
    varPir.Publish(status,0); 
    //Publish the variables every 15 seconds.
    varTem.Publish(temperature,15);
    varLight.Publish(light,15);
}
```
