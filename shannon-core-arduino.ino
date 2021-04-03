#include "devices.h"
#include "Arduino.h"

Switch foo(17, 0xe);

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(foo.id(), BIN);
    delay(5000);
}