#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>

#include "settings.h"

#define FW_VERSION 6

#define NUM_LEDS 500
#define DATA_PIN 12

#define SLEEP_SECONDS 5

CRGB leds[NUM_LEDS];
String mac;

String versionPath() {
  mac = WiFi.macAddress();
  mac.replace(":", "-");
  String path = SETTINGS_OTA_VERSION_ADDRESS_PREFIX + mac + SETTINGS_OTA_VERSION_ADDRESS_SUFFIX;
  Serial.print("path: ");
  Serial.println(path);
  return(path);
}


String newFirmwareAvailable() {
  Serial.println("checking for new firmware...");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected...");
    HTTPClient http;
    http.begin(versionPath());
    int httpCode = http.GET();
    if (httpCode > 0) {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + 50;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      http.end();   // close connection...
      int version = root["version"];
      const char* firmwareFile = root["firmwareFile"];
      if(FW_VERSION != version) {
        Serial.println("new firmware available...");
        Serial.println(firmwareFile);
        return(firmwareFile);
      }
    }
  }
  Serial.println("NO new firmware available...");
  return("false");
}

void checkForNewFirmware(String newAvail) {
  if(newAvail != "false") {
    Serial.println("starting update...");
    String path = SETTINGS_OTA_VERSION_ADDRESS_PREFIX;
    path = path + mac + "/" + newAvail;
    Serial.print("new firmware located at: ");
    Serial.println(path);

    t_httpUpdate_return ret = ESPhttpUpdate.update(path);
    switch(ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;
      }
  }
}

void setup() {
  delay(5000);

  Serial.begin(115200);

  WiFi.begin(SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(100);

  checkForNewFirmware(newFirmwareAvailable());
}

uint16_t loopCounter = 0;
uint8_t currentLed = 0;

void loop() {
  fill_solid( &(leds[0]), NUM_LEDS, CRGB::Black);
  leds[currentLed] = CRGB::Green;
  leds[currentLed+10] = CRGB::Red;
  leds[currentLed+20] = CRGB::White;
  leds[currentLed+30] = CRGB::Yellow;
  leds[currentLed+40] = CRGB::Blue;
  FastLED.show();
  currentLed++;
  currentLed > NUM_LEDS ? 0 : currentLed;
  if(loopCounter == 12000) {
    Serial.print("new firmware? ");
    // checking for new firmware every 60 seconds... make this larger in production...
    checkForNewFirmware(newFirmwareAvailable());
    loopCounter = 0;
  }
  loopCounter++;
  delay(5);
}
