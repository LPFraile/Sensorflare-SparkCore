#ifndef SENSORFLARE
#define SENSORFLARE

namespace SensorFlare
{
    //One instance for each digital pin to remorte control as output 
    class DigitalOut
    {
        private:
        int number;//pin
        bool state;// 1 on 0 off
        public:
        DigitalOut(int _number);
        void begin();
    };
    //One instance for each digital pin to remorte control as PWM output
    class PWMOut
    {
        private:
        int number;//pin
        int value;//duty cycle
        public:
        PWMOut(int _number);
        void begin();
    };
    //one instance for each variable to be remote access
    class VarPublish
    {
        private:
        String name;
        String property;
        int periode; 
        int var_int;
        float var_float;
        String var_string;
        unsigned long lastTime;
        public:
        VarPublish(String _name);
        VarPublish(String _name, String _property);
        int Publish(int _val, int _periode);
        int Publish(float _val, int _periode);
    
    };
}

int controlPin(String command); 
int controlPWM(String command);
void readEEPROM(void);
void writeEEPROM(void);
#endif
