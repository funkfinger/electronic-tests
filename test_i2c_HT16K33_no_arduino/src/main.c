// largely based on https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/
// ATtiny85 I2C pins:
// * ATtiny Pin 5 (PB0) = SDA on LCD i2c (pulled high with 4.7k)
// * ATtiny Pin 7 (PB2) = SCK on LCD i2c (pulled high with 4.7k)

#include <avr/io.h>
#include <util/delay.h>
#include <uWireM.h>

#define BRIGHTNESS 4 // 0=dim, 15=max

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

#define ADDR 0x70

static uint8_t _buf[18];

// bits are in odd order- this "humanizes" them - see http://mythopoeic.org/adafruit-trinket-i2c/ for origin
uint8_t humanizeBits(uint8_t x) {
  // reverse order of bits
  x = x >> 4 | x << 4; // swap higher and lower nibbles...
  x = (x & 0xCC) >> 2 | (x & 0x33) << 2;
  x = (x & 0xAA) >> 1 | (x & 0x55) << 1;
  return (x >> 1) | (x << 7); // rotate and put least sig bit back in front
}

void i2cCmd(x) {
  _buf[0] = uWireM_addr_send(ADDR);
  _buf[1] = x;
  uWireM_xfer(_buf, 2);
}

void i2cClear() {
  memset(_buf, 0, sizeof(_buf));
  _buf[0] = uWireM_addr_send(ADDR);
  uWireM_xfer(_buf, 18);
}

void i2cAllOn() {
  memset(_buf, 0x0F, sizeof(_buf));
  _buf[0] = uWireM_addr_send(ADDR);
  uWireM_xfer(_buf, 18);  
}

void i2cTestDisplay() {
  memset(_buf, 0, sizeof(_buf));
  _buf[0] = uWireM_addr_send(ADDR);

  // _buf[1] = 0b11111111; // nothing

  _buf[2]  = humanizeBits(0b01111110); // first line
  _buf[4]  = humanizeBits(0b10000001); // second line
  _buf[6]  = humanizeBits(0b10100101); // third line
  _buf[8]  = humanizeBits(0b10000001); // fourth line
  _buf[10] = humanizeBits(0b10100101); // fifth line
  _buf[12] = humanizeBits(0b10111101); // sixth line
  _buf[14] = humanizeBits(0b10000001); // seventh line
  _buf[16] = humanizeBits(0b01111110); // eighth line

  

  uWireM_xfer(_buf, 18); 
}

void setupDisplay() {
  i2cClear();
  i2cCmd(0x21); // display on
  i2cCmd(BRIGHTNESS); // dim setting
  i2cCmd(0x81); // display on
}

void setupAttiny() {
  /* set up I2C communication library */
  uWireM_init();
  setupDisplay();
}

void loopAttiny() {
  for(;;) {
    _delay_ms(500);
    i2cTestDisplay();
    _delay_ms(500);
    i2cClear();    
  }
}

int main() {
  setupAttiny();
  loopAttiny();
}
