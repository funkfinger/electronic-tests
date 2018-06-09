/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>
#include <TimeLib.h>

#include "settings.h"

#define TIME_OFFSET -25200
#define UPDATE_INTERVAL 60000

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "time.google.com", TIME_OFFSET, UPDATE_INTERVAL);

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
    Serial.begin(115200);
    delay(2000);

    // We start by connecting to a WiFi network
    WiFi.mode (WIFI_STA);
    WiFi.begin (SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

    timeClient.begin();
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println(__DATE__);
    Serial.println(__TIME__);

    // load time from network if rtc has lost power...
    if (rtc.lostPower()) {
        Serial.println("RTC lost power- set time from NTP");
        timeClient.update();
        setTime(timeClient.getEpochTime());
        rtc.adjust(DateTime(year(), month(), day(), hour(), minute(), second()));
    }


    DateTime now = rtc.now();
    setTime(now.unixtime());
    delay(500);
}


void loop() {
  Serial.print(year(), DEC);
  Serial.print('/');
  Serial.print(month(), DEC);
  Serial.print('/');
  Serial.print(day(), DEC);
  Serial.print(" (");
  Serial.print(monthStr(month()));
  Serial.print(") ");
  Serial.print(hour(), DEC);
  Serial.print(':');
  Serial.print(minute(), DEC);
  Serial.print(':');
  Serial.print(second(), DEC);
  Serial.println();

  delay(5000);
}
