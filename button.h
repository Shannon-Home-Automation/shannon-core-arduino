#include "Arduino.h"

class Button{
    private:
    int pin;
    bool state = false;

    public:
    void update();
    Button(int pin);
    void (*pushDownAction)(void);
    void (*pushUpAction)(void);

    Button(int pin){
        this->pin = pin;
    }

    void begin(){
        pinMode(this->pin, INPUT);
    }

    void update(){
        bool newState = digitalRead(this->pin);

        if (this->state == newState){
            return;
        }

        if (newState == true){
            if (pushDownAction){
                this->pushDownAction();
            }
        } else {
            if (pushUpAction){
                this->pushUpAction();
            }
        }
        
        this->state = newState;
        delay(100);
    }
};
