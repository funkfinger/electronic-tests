#ATTiny85 I2C LCD Library

A library that utilizes the [I2C library for ATtiny85](http://playground.arduino.cc/Code/USIi2c) so to control an I2C LCD screen. Largely based on the Digispark library. This library was supposed to be seamlessly working as the old [LiquidCrystal I2C by Malpartida](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home) with normal arduinos and attinys. However because my Arduino 1.6.1 IDE wanted me to include the regular Wire library in every sketch and also some old sketches of mine wouldn't work with this version, I decided to turn this into a dedicated ATtiny85 library for controlling the LCD screen through an I2C connection. Some minor changes, just to enforce separation of concerns in other words. Don't forget the 4.7 ΚΩ resistors between the SDA and SCK lines and the Vcc.

Using this library, I made an [Interactive name tag](https://platis.solutions/blog/2015/03/22/diy-interactive-name-tag/), the sketch of which I have included under the /examples folder.

The Digispark repository used to have many other libraries I didn't use and therefore want to include, but they are in the Git history if you want to "revive" them.