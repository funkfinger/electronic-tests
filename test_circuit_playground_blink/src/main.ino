
#include "Adafruit_CircuitPlayground.h"

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.redLED(HIGH);
  delay(20);
  CircuitPlayground.redLED(LOW);
  delay(1000);

  Serial.print("Temperature ");
  Serial.print(CircuitPlayground.temperature());
  Serial.println(" *C");
}