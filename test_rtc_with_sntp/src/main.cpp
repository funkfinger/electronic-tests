#include <Arduino.h>

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <NTPClient.h>
#include <RTClib.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <Wire.h>

#include "settings.h"

RTC_DS3231 rtc;

WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;

#define TIME_OFFSET -25200
#define UPDATE_INTERVAL 60000

NTPClient timeClient(ntpUDP, "time.google.com", TIME_OFFSET, UPDATE_INTERVAL);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

  Serial.begin(115200);

  delay(5000); // wait for console opening

  // We start by connecting to a WiFi network
  WiFiMulti.addAP(SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);
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

  delay(1000);


  // now check rtc module...
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }


  uint32_t epoch = 0;

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    Serial.println("setting epoch / unix time from ntp server...");
    timeClient.update();
    delay(1000);

    epoch = timeClient.getEpochTime();
    Serial.print("Epoch Time = ");
    Serial.println(epoch);
    Serial.print("formatted time = ");
    Serial.println(timeClient.getFormattedTime());

    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(epoch));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
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
