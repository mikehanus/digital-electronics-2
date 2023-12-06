#include <Arduino.h>
#include <time.h>


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(A0));
}
