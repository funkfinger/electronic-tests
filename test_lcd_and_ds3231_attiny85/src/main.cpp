#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <TinyWireM.h>
#include <LiquidCrystal_attiny.h>

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines


#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)
#define chkBit(x) & (1<<(x))

volatile uint32_t mills;

#define HT_ADDR 0x70


void setupTimers() {

  // timer 0 - used for ticks...
  TCCR0A set(WGM01); // CTC mode. set WGM01
  
  // divide by 64
  TCCR0B set(CS00);
  TCCR0B set(CS01);
  TCCR0B clr(CS02);
  
  OCR0A = 125; // 8,000,000 / 64 / 125 = 1ms
  TIMSK set(OCIE0A); // set timer to interrupt

  // calibration...
  // OSCCAL = 0x00; // lowest...
  OSCCAL -= 1;
  // OSCCAL = 0x7f; // highest?...

}

void setup(void) {
  // stop interrupts...
  cli();
  setupTimers();

  // start interrupts...
  sei();

  TinyWireM.begin();

  TinyWireM.beginTransmission(HT_ADDR);
  TinyWireM.send(0x21);
  TinyWireM.endTransmission();

  TinyWireM.beginTransmission(HT_ADDR);
  TinyWireM.send((0xE0));
  TinyWireM.endTransmission();

  TinyWireM.beginTransmission(HT_ADDR);
  TinyWireM.send(0x83); // display on, blink 2hz
  TinyWireM.endTransmission();

  // TinyWireM.beginTransmission(HT_ADDR);
  // TinyWireM.send(0x00);
  // TinyWireM.send(0x01);
  // TinyWireM.endTransmission();



  // lcd.init();                           // initialize the lcd
  // lcd.backlight();                      // Print a message to the LCD.
  // lcd.print("Starting up...");
  // _delay_ms(500);
  
  
  
  
}

void loop() {
  // lcd.clear();
  // for(;;) {
  //   lcd.setCursor(0, 0);
  //   lcd.print(mills);
  // }
}

int main() {
  setup();
  loop();
}

ISR (TIMER0_COMPA_vect) {
  mills++;
}

