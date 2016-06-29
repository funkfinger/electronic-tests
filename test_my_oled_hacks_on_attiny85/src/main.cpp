#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>

#include "display.h"

// #include "SSD1306_minimal.h"

//byte array of bitmap 5x24px
const unsigned char  img_thermometer[] PROGMEM = {
  
  0x00, 0xfe, 0x03, 0xfe, 0x50,
  0x00, 0xff, 0x00, 0xff, 0x55,
  0x60, 0x9f, 0x80, 0x9f, 0x65,
   
};

//byte array of bitmap 17x16 px
const unsigned char  img_heart_small[] PROGMEM = {

    0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00
};

//byte array of bitmap 17x16 px
const unsigned char  img_heart_big[] PROGMEM = {

    0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00
};   

const unsigned char img_box[] PROGMEM = {
  0b11111111,
  // 0b11111111,
  // 0b11111111,
  // 0b11111111,
  // 0b11111111,
  // 0b11111111,
  // 0b11111111,
  0b11000011,
  0b11000011,
  0b11000011,
  0b11000011,
  0b11000011,
  0b11000011,
  0b11111111
};


void prepareDisplay(){

  unsigned int i,k;
  unsigned char ch[5];
  
  startScreen();
  
  // cursorTo(0,0);
  // printString( "ATTiny");
  // cursorTo(5,1);
  // printString( "Standard Font");
  // cursorTo(10,2);
  // printString( "abcdef...xyz");
  //
  // drawImage( img_thermometer, 50,4, 5, 3 );
  // cursorTo(60, 5);
  // printString( "+15" );
  // cursorTo(67, 6);
  // printString( "63%");
  
  // drawImage( img_heart_small, 10, 5, 17, 2);
  drawImage2( img_box, 0, 0, 127, 63);

  // sendCommand( 0b10100101 );
  

} 


void setup(){
  // pinMode(3, INPUT);
  
  displayInit(0x3c);
  clear();

  _delay_ms(1000);
  prepareDisplay();
  
}    

 
void loop(){
  for(;;) {
    // sendCommand(0b10101111);
    // _delay_ms(100);
    // sendCommand( 0b10100101 );
    // _delay_ms(100);
  }
} 


int main(void) {
  setup();
  loop();
}
