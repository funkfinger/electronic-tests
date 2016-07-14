int led = PORTB1;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for(;;) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
