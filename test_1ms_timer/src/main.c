#include <avr/interrupt.h>
#include <avr/io.h>

#define LED 3

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

uint8_t tick;

// TODO: calibrate with OSCCAL
void setupTimers() {  

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
  for(;;) {
  }
}

int main() {
  setupAttiny();
  loopAttiny();
}

ISR (TIMER0_COMPA_vect) {
  PORTB inv(LED);
  tick++;
}
