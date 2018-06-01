/*
 *  This sketch sends a message to a TCP server
 *
 */

 // #include <Arduino.h>

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

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, lets set the time!");
        timeClient.update();
        setTime(timeClient.getEpochTime());
        Serial.print("hour() ");
        Serial.println(hour());
        rtc.adjust(DateTime(year(), month(), day(), hour(), minute(), second()));

        // following line sets the RTC to the date & time this sketch was compiled
        // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // rtc.adjust(DateTime(timeClient.getYear(), timeClient.getMonth(), timeClient.getDate(), timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds()));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    delay(500);
}


void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(5000);
}
