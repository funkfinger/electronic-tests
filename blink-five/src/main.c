#include <avr/io.h>
#include <util/delay.h>

#define LED0 PORTB0
#define LED1 PORTB1
#define LED2 PORTB2
#define LED3 PORTB3
#define LED4 PORTB4

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

void setup() {
  DDRB set(DDB0);
  DDRB set(DDB1);
  DDRB set(DDB2);
  DDRB set(DDB3);
  DDRB set(DDB4);
  PORTB = 0x00;
}

void loop() {
  for(;;) {
    PORTB = 0b00000001;
    _delay_ms(100);
    PORTB = 0b00000010;
    _delay_ms(100);
    PORTB = 0b00000100;
    _delay_ms(100);
    PORTB = 0b00001000;
    _delay_ms(100);
    PORTB = 0b00010000;
    _delay_ms(100);
    PORTB = 0b00000000;
    _delay_ms(500);
  }
}

int main() {
  setup();
  loop();
}
