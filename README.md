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
