#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>

#include "SSD1306_minimal.h"

#define DEG "\xa7" "C"

SSD1306_Mini oled;

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
    
//Byte array of bitmap of 76 x 56 px:
const unsigned char img_logo [] PROGMEM = {

  0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 0xC1, 0xE1, 0xE1,
  0xE1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0x71, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x81, 0xC1, 0xC1, 0xE1, 0xE1, 0xF1, 0xF1, 0xF1, 0xE1, 0xE1, 0xC1, 0xC1, 0x81,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1,
  0xF1, 0x01, 0x01, 0x01, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0x01, 0x01, 0x01,
  0x01, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0xF1, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
  0x1F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8,
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFC, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x7E, 0x7E, 0x7E,
  0x3E, 0x3E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x1E, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x3F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE,
  0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x7F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF8, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x03,
  0x00, 0x00, 0x00, 0xE0, 0xF1, 0xF1, 0xF1, 0xF9, 0xF9, 0xF1, 0xF1, 0xF1, 0xE0, 0x00, 0x00, 0xE0,
  0xF1, 0xF1, 0xF1, 0xF9, 0xF9, 0xF1, 0xF1, 0xF1, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xF1, 0xF1, 0xF1,
  0xF9, 0xF9, 0xF1, 0xF1, 0xF1, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x41,
  0x41, 0x43, 0x43, 0x43, 0x43, 0x43, 0x41, 0x41, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x40, 0x41, 0x43, 0x43, 0x43, 0x43, 0x41, 0x41, 0x41, 0x40, 0x40, 0x40, 0x40, 0x41,
  0x43, 0x43, 0x43, 0x43, 0x41, 0x41, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x43, 0x43, 

  
};


void splash(){

  oled.startScreen();
  oled.clear();
  
  oled.drawImage( img_logo, 10,10, 95, 39 );
  // oled.cursorTo(0,7);
  // oled.printString( "http://CoPiino.cc");
  
  _delay_ms(5000);
  
  oled.clear();
  oled.cursorTo(15,1);
  oled.printString( "HELLO!!!");
    
  oled.cursorTo(30,3);
  oled.printString( "WHAT WHAT!");


  oled.cursorTo(0,7);
  oled.printString( "http://jaywiggins.com");
  
  
  
}


void heartBeat(){
  // static char big=1;
  // static long startTime=0;
  // long currentTime;
  //
  // // get current time
  // currentTime= millis();
  //
  // // update if 1000ms passed
  // if ((currentTime - startTime) > 200){
  //   startTime= currentTime;
  //
  //
  //   // ---
  //   big=1-big;
  //   if (big){
  //     oled.drawImage( img_heart_big, 10, 5, 17, 2);
  //   } else {
  //     oled.drawImage( img_heart_small, 10, 5, 17, 2);
  //   }
  //
  // }
}


void prepareDisplay(){

  unsigned int i,k;
  unsigned char ch[5];
  
  oled.clear();
  oled.startScreen();
  
  
  oled.cursorTo(0,0);
  oled.printString( "ATTiny");
  oled.cursorTo(5,1);
  oled.printString( "Standard Font");
  oled.cursorTo(10,2);
  oled.printString( "abcdef...xyz");

  oled.drawImage( img_thermometer, 50,4, 5, 3 );
  oled.cursorTo(60, 5);
  oled.printString( "+15" DEG );
  oled.cursorTo(67, 6);
  oled.printString( "63%");
  
  oled.drawImage( img_heart_small, 10, 5, 17, 2);
  

}

char getTemperature(){
   return rand(); 
}

char getHumidity(){
   return rand(); 
}

void setup(){
  // pinMode(3, INPUT);
  
  oled.init(0x3c);
  oled.clear();

  _delay_ms(1000);
  
  splash();
  
  _delay_ms(8000);

  prepareDisplay();
  
}    

 
void loop(){

  static long startTime=0;
  long currentTime;
  
  
  // // get current time
  // currentTime= millis();
  //
  // // update if 1000ms passed
  // if ((currentTime - startTime) > 1000){
  //   startTime= currentTime;
  //   char buf[10];
  //
  //   // ---
  //   // update temperature
  //   char temperature= getTemperature();
  //
  //   // sprintf(buf, "%+0.2hd" DEG , temperature);
  //   buf = "hello....";
  //
  //   // set cursor
  //   oled.cursorTo(60, 5);
  //
  //   // print to display
  //   oled.printString( buf );
  //
  //
  //   // ---
  //   // update humidity
  //   char humidity= getHumidity();
  //
  //   sprintf(buf, "%0.2hd\%", humidity);
  //
  //   // set cursor
  //   oled.cursorTo(67, 6);
  //
  //   // print to display
  //   oled.printString( buf );
  //
  //
  //
  // }
  //
  // heartBeat();
  //
  
} 


int main(void) {
  setup();
  loop();
}
