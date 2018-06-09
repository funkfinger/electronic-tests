#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>


#include "settings.h"

#define NUM_LEDS 8
#define DATA_PIN 12

#define FW_VERSION 1

CRGB leds[NUM_LEDS];

String versionPath() {
  String mac;
  mac = WiFi.macAddress();
  mac.replace(':', '-');
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
      http.end();   //Close connection
      int version = root["version"]; // 1
      const char* firmwareFile = root["firmwareFile"]; // "firmware-1.bin"
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

void setup() {
  delay(5000);

  Serial.begin(115200);

  WiFi.begin(SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  fill_solid( &(leds[0]), NUM_LEDS, CRGB::Yellow);
  FastLED.show();
  Serial.print("new firmware? ");
  Serial.println(newFirmwareAvailable());
  delay(2000);
}
