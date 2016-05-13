#include <avr/io.h>
#include <util/delay.h>

#define OUTPUT 1
#define HIGH 1
#define LOW 1

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

int ledPin = PB5;

int main(void) {
  DDRB set(ledPin);
  for(;;) {
    PORTB set(ledPin);
    _delay_ms(500);
    PORTB clr(ledPin);
    _delay_ms(500);
  }
}