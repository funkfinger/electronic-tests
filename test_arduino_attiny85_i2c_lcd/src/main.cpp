/*
 * Interactive nametag sketch for ATtiny85. Based on the Digispark
 * ATtiny LCD example and the Adafruit "Measuring Sound Levels" example.
 * Every 12000 milliseconds will change the display from my name to my website.
 * On the second line, will measure and display sound levels.
 * For more info check: https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/
 * ATtiny85 I2C pins:
 * ATtiny Pin 5 = SDA on DS1621  & GPIO
 * ATtiny Pin 7 = SCK on DS1621  & GPIO
 */

#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
#include <LiquidCrystal_attiny.h>          // for LCD w/ GPIO MODIFIED for the ATtiny85

#define GPIO_ADDR     0x27
LiquidCrystal_I2C lcd(GPIO_ADDR, 16, 2); // set address & 16 chars / 2 lines

const unsigned long nameInterval = 3000;
unsigned long prevNameChange = 0;
short state = 1;

void setup() {
  lcd.init();                           // initialize the lcd
  lcd.backlight();                      // Print a message to the LCD.
  lcd.print("Starting up...");
}

void printName() {
  if (millis() - prevNameChange > nameInterval) {
    lcd.setCursor(0, 0);
    if (state) {
      lcd.clear();
    } else {
      lcd.print("LINE 1: ");
      lcd.print(millis());
      lcd.setCursor(0, 1);
      lcd.print("LINE 2: ");
      lcd.print(millis());
    }
    prevNameChange = millis();
    state = !state;
  }
}


void loop() {
  printName();
}

