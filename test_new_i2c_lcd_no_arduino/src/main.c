// ATtiny85 I2C pins:
// * ATtiny Pin 5 (PB0) = SDA on LCD i2c (pulled high with 4.7k)
// * ATtiny Pin 7 (PB2) = SCK on LCD i2c (pulled high with 4.7k)
// datasheet for HT16K33 - http://www.holtek.com.tw/documents/10179/e946432c-cb5f-4b76-a150-8f7587a584f0

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "USI_TWI_Master.h"

#define BRIGHTNESS 1 // 0=dim, 15=max

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

// #define ADDR 0x70 // for LED I2C backpack
#define ADDR 0x27 // for I2C LCD

static uint8_t _buf[18];

// bits are in odd order- this "humanizes" them - see http://mythopoeic.org/adafruit-trinket-i2c/ for origin
uint8_t humanizeBits(uint8_t x) {
  // reverse order of bits
  x = x >> 4 | x << 4; // swap higher and lower nibbles...
  x = (x & 0xCC) >> 2 | (x & 0x33) << 2;
  x = (x & 0xAA) >> 1 | (x & 0x55) << 1;
  return (x >> 1) | (x << 7); // rotate and put least sig bit back in front
}

uint8_t sendAddr(uint8_t x) {
  return x << 1;
}

uint8_t receiveAddr(uint8_t x) {
  return x << 1 | 1;
}

void i2cCmd(uint8_t x) {
  _buf[0] = sendAddr(ADDR);
  _buf[1] = x;
  USI_TWI_Start_Transceiver_With_Data(_buf, 2);
}

void i2cClear() {
  memset(_buf, 0, sizeof(_buf));
  _buf[0] = sendAddr(ADDR);
  USI_TWI_Start_Transceiver_With_Data(_buf, 18);
}

void i2cAllOn() {
  memset(_buf, 0x0F, sizeof(_buf));
  _buf[0] = sendAddr(ADDR);
  USI_TWI_Start_Transceiver_With_Data(_buf, 18);  
}

void i2cTestDisplay() {
  memset(_buf, 0, sizeof(_buf));
  _buf[0] = sendAddr(ADDR);

  // _buf[1] = 0b11111111; // nothing

  _buf[2]  = 0x3F; // 1 line
  _buf[4]  = 0xC0; // 2 line
  _buf[6]  = 0xD2; // 3 line
  _buf[8]  = 0xC0; // 4 line
  _buf[10] = 0xD2; // 5 line
  _buf[12] = 0xDE; // 6 line
  _buf[14] = 0xC0; // 7 line
  _buf[16] = 0x3F; // 8 line
  
  // _buf[2]  = humanizeBits(0b01111110); // first line
  // _buf[4]  = humanizeBits(0b10000001); // second line
  // _buf[6]  = humanizeBits(0b10100101); // third line
  // _buf[8]  = humanizeBits(0b10000001); // fourth line
  // _buf[10] = humanizeBits(0b10100101); // fifth line
  // _buf[12] = humanizeBits(0b10111101); // sixth line
  // _buf[14] = humanizeBits(0b10000001); // seventh line
  // _buf[16] = humanizeBits(0b01111110); // eighth line

  USI_TWI_Start_Transceiver_With_Data(_buf, 18); 
}

void setupDisplay() {
  i2cClear();
  i2cCmd(0x21); // display on
  i2cCmd(0xE0); // dim setting
  i2cCmd(0x81); // display on
}

void setupAttiny() {
  /* set up I2C communication library */
  USI_TWI_Master_Initialise();
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
