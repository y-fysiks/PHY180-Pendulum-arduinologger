#include "Rotary.h"

Rotary r = Rotary(2, 3);

volatile int counter = 0;

const int interval = 10;

unsigned long now;
unsigned long prevNow;

// const int pinA = 6
// const int pinB = 5

void setup() {
    Serial.begin(250000);
    r.begin();
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
    sei();
}

void loop() {
    now = millis();
    // Send the value of counter
    if (now - prevNow >= interval) {
        Serial.print(now);
        Serial.print(" ");
        Serial.print(counter);
        Serial.print("\n");
        prevNow = now;
    }
}

ISR(PCINT2_vect) {
  unsigned char result = r.process();
  if (result == DIR_NONE) {
    // do nothing
  }
  else if (result == DIR_CW) {
    counter++;
  }
  else if (result == DIR_CCW) {
    counter--;
  }
}