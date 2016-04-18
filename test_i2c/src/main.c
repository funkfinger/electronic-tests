#include <avr/io.h>
#include <util/delay.h>
#include <uWireM.h>

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

#define LED PORTB3

static uint8_t _buf[18];

void lcdCmd(const uint8_t x) {
  // _buf[0] = uWireM_addr_send(0x27);
  _buf[0] = 0x4e;
  _buf[1] = x;
  if (!uWireM_xfer(_buf, 2)) {
   PORTB set(LED);
  };
}

void setupAttiny() {
  DDRB set(LED);
  PORTB clr(LED);
  uWireM_init();
}

void loopAttiny() {
  for(int x = 0; x < 10; x++) {
    PORTB set(LED);
    _delay_ms(250);
    PORTB clr(LED);
    _delay_ms(250);
  }
  
  lcdCmd(0xFF);
  _delay_ms(1000);
  lcdCmd(0x00);

  for(;;) {
    PORTB set(LED);
    _delay_ms(25);
    PORTB clr(LED);
    _delay_ms(25);
  }
}

int main() {
  setupAttiny();
  loopAttiny();
}
