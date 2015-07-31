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

-   SensorFlare::VarPublish ObjectName("VariableName"):It is the default constructor of the VarPublish class. Instance an object, called ObjectName, for each variable that will be published on Sensorflare platform with the name VariableName. This name must be at least 12 characters and the variable will be public on the cloud which means that another Spark Core user can access it.
-   SensorFlare::VarPublish ObjectName("VariableName",”PRIVATE”):It is a second constructor of the VarPublish class. Instance and object called ObjectName for each variable that will be published on the Sensorflare platform with the name VariableName. This name must be at least 12 characters and the variable will be private upload on the cloud which means that only the user can access it.
-   ObjectName.Publish(Variable, period):The Publish method will publish the specific Variable every period time with the name that has been chosen before "VariableName". Two kinds of variables can be published: int or float.
