// command to set fuses with avr dragon...
// avrdude -c dragon_hvsp -p attiny85 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -P usb
// ~/.platformio/packages/tool-avrdude/avrdude -c dragon_hvsp -p attiny85 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -P usb -C ./avrdude.conf

#include <avr/io.h>
#include <util/delay.h>

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x)
#define inv(x) ^=(1<<x)


void setup() {
  DDRB = 0b11111111; // set port b to output...
  PORTB = 0b00000000; // turn off port b
}

void loop() {
  for(;;) {
    PORTB++; // count up...
    _delay_ms(500);
  }
}

int main() {
  setup();
  loop();
}
