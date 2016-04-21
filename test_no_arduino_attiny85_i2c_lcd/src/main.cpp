// largely based on https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/
// ATtiny85 I2C pins:
// * ATtiny Pin 5 = SDA on LCD i2c (pulled high with 4.7k)
// * ATtiny Pin 7 = SCK on LCD i2c (pulled high with 4.7k)

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <TinyWireM.h>
#include <LiquidCrystal_attiny.h>

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

#define LED 3

#define GPIO_ADDR     0x27

LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines

const unsigned long nameInterval = 3000;
volatile uint32_t tick = 0;

void setupTimers() {
  // calibration...
  // OSCCAL = 0x00; // lowest...
  OSCCAL -= 4;
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
  
  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.print("Starting up...");
}

void printName() {
  lcd.clear();
  lcd.print("LINE 1: ");
  lcd.print(tick);
  lcd.setCursor(0, 1);
  lcd.print("LINE 2: ");
  lcd.print(tick);
}


void loopAttiny() {
  for(;;) {
    printName();
    _delay_ms(1000);
  }
}

int main(void) {
  setupAttiny();
  loopAttiny();
  return(0);
}

ISR (TIMER0_COMPA_vect) {
  // PORTB inv(LED);
  tick++;
}
