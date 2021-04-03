#include "Arduino.h"

class Device{
    protected:
    unsigned int pin;
    unsigned int typeId :4;
    unsigned int numberId: 4;

    public:
    int id(){
        int id = typeId;
        id = id << 4;
        id += this->numberId;
        return id;
    }

    virtual void begin();
    virtual void executeCodeWithId(byte code, byte id){};
};

class OutputDevice: public Device{
    public:
    virtual void begin(){
        pinMode(this->pin, OUTPUT);
    }
};

class InputDevice: public Device{
    public:
    virtual void begin(){
        pinMode(this->pin, INPUT);
    }
};

class Switch: public OutputDevice{
    private:
    const byte onCode = 0x01;
    const byte offCode = 0x02;

    public:
    Switch(int pin, int numberId){
        this->typeId = 0x1;
        
        this->pin = pin;
        this->numberId = numberId;
    }

    virtual void executeCodeWithId(byte code, byte id){
        if (id != this->id()){
            return;
        }
  
        if (code == this->onCode){
            this->on();
        } else if (code == this->offCode){
            this->off();
        }
    }

    bool state(){
        return digitalRead(this->pin);
    }

    void on(){
      digitalWrite(this->pin, HIGH);
    }

    void off(){
      digitalWrite(this->pin, LOW);
    }
};

class AnalogSwitch: public OutputDevice{
    public:
    AnalogSwitch(int pin, int numberId){
        this->typeId = 0x1;
        
        this->pin = pin;
        this->numberId = numberId;
    }

    virtual void executeCodeWithId(byte code, byte id){
        analogWrite(this->pin, code);
    }

    int value(){
        return digitalRead(this->pin);
    }
};

class DigitalSensor: public InputDevice{
    public:
    DigitalSensor(int pin, int numberId){
        this->typeId = 0x02;

        this->pin = pin;
        this->numberId = numberId;
    }

    int value(){
        return digitalRead(this->pin);
    }
};











