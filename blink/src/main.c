#include <avr/io.h>
#include <util/delay.h>

#define LED PORTB3

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

void setup() {
  DDRB set(DDB3);
  PORTB clr(LED);
}

void loop() {
  for(;;) {
    PORTB inv(LED);
    _delay_ms(500);
  }
}

int main() {
  setup();
  loop();
}
