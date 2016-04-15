#include <avr/interrupt.h>
#include <avr/io.h>

#define LED 3

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

volatile uint16_t tick;

void setupTimers() {
  // calibration...
  // OSCCAL = 0x00; // lowest...
  OSCCAL -= 6;
  // OSCCAL = 0x7f; // highest?...

  // CTC mode. set WGM01
  TCCR0A clr(WGM00);  
  TCCR0A set(WGM01);
  TCCR0B clr(WGM02);
  
  // divide by 64
  TCCR0B set(CS00);
  TCCR0B set(CS01);
  TCCR0B clr(CS02);
  
  // top value in ctc mode...
  OCR0A = 125; // 8,000,000 / 64 / 125 = 1ms
  
  TIMSK set(OCIE0A); // set timer to interrupt on match...
}

void setupAttiny() {
  DDRB set(LED);
  PORTB clr(LED);
  cli();
  setupTimers();
  sei();
}

void loopAttiny() {
  for (;;) {
    if(tick > 9) {
      PORTB inv(LED);
      tick = 0;
    }
  }
}

int main() {
  setupAttiny();
  loopAttiny();
}

ISR (TIMER0_COMPA_vect) {
  // PORTB inv(LED);
  tick++;
}
