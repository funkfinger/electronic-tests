#include <avr/interrupt.h>
#include <avr/io.h>

#define BUTTON 1
#define LED 3

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)


void setupButton() {
  DDRB clr(BUTTON); // button is input...
  PCMSK set(BUTTON); // turn interrupt on...
  GIMSK set(PCIE);
}

void setup() {
  cli();
  setupButton();
  DDRB set(LED);
  PORTB set(LED);
  sei();
}

void loop() {
  for(;;) {
  }
}

int main() {
  setup();
  loop();
}


ISR (PCINT0_vect) {
  PORTB inv(LED);
}
