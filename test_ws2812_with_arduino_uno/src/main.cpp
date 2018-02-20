#include <Arduino.h>
#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

uint8_t hue = 0;

void loop() {
  hue += 20;
  fill_solid( &(leds[0]), NUM_LEDS, CHSV( hue, 255, 255));
  // leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  fill_solid( &(leds[0]), NUM_LEDS, CRGB( 0, 0, 0));
  // leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}
