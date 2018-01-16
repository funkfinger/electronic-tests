/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "settings.h"

WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;

#define TIME_OFFSET -25200
#define UPDATE_INTERVAL 60000

NTPClient timeClient(ntpUDP, "time.google.com", TIME_OFFSET, UPDATE_INTERVAL);


void setup() {
    Serial.begin(115200);
    delay(2000);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP(SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
  timeClient.update();
  Serial.println(timeClient.getEpochTime());
  Serial.println(timeClient.getFormattedTime());
  Serial.println(timeClient.getHours());
  delay(5000);
}
