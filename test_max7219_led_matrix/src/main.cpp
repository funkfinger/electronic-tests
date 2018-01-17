#include <Arduino.h>

// Demo of MAX7219_Dot_Matrix library - sideways scrolling
// Author: Nick Gammon
// Date: 2 October 2015

// Scrolls a pixel at a time.

#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>
const byte chips = 4;

// 4 chips (display modules), hardware SPI with load on D10
MAX7219_Dot_Matrix display(chips, 10);  // Chips / LOAD

const char message[] = "Testing 1234567890";

void setup(){
  display.begin();
  display.setIntensity(8);
}  // end of setup

unsigned long lastMoved = 0;
unsigned long MOVE_INTERVAL = 40;  // mS
int  messageOffset;

void updateDisplay() {
  display.sendSmooth(message, messageOffset);

  // next time show one pixel onwards
  if(messageOffset++ >= (int)(strlen (message) * 8))
    messageOffset = - chips * 8;
}  // end of updateDisplay

void loop() {

  // update display if time is up
  if(millis() - lastMoved >= MOVE_INTERVAL) {
    updateDisplay();
    lastMoved = millis();
  }

  // do other stuff here

}  // end of loop
