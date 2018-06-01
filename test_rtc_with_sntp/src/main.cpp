#include <Arduino.h>

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <RTClib.h>
#include <SPI.h>
// #include <string.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <Wire.h>

#include "settings.h"

// OLED reqs...
#define OLED_RESET 4
#define OLDE_ADDRESS 0x3c
Adafruit_SSD1306 display(OLED_RESET);

RTC_DS3231 rtc;

ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;

#define TIME_OFFSET -25200
#define UPDATE_INTERVAL 60000

NTPClient timeClient(ntpUDP, "time.google.com", TIME_OFFSET, UPDATE_INTERVAL);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void printToDisp3(const char* str) {
  display.setTextSize(2);
  display.setCursor(0,20);
  display.println(str);
  display.display();
}

void printToDisp2(const char* str) {
  display.setCursor(0,10);
  display.println(str);
  display.display();
}

void printToDisp(const char* str) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(str);
  display.display();
}

void setupOled() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.display(); // adafruit splashscreen - not sure how I feel about them including with lib...
  delay(2000);
  printToDisp("Hello function!");
  delay(1000);
}


void setup () {

  setupOled();

  Serial.begin(115200);

  delay(5000); // wait for console opening

  // We start by connecting to a WiFi network
  WiFiMulti.addAP(SETTINGS_NETWORK_SSID, SETTINGS_NETWORK_PASS);
  Serial.println();
  printToDisp("Wait for WiFi... ");
  Serial.print("Wait for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  String ip = WiFi.localIP().toString();
  printToDisp(ip.c_str());


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
    for (int i = 0; i < 5; i += 1) { // doing multiple times, seems to need to 'settle'
      timeClient.update();
      delay(5000);

      epoch = timeClient.getEpochTime();
      Serial.print("Epoch Time = ");
      Serial.println(epoch);
      Serial.print("formatted time = ");
      Serial.println(timeClient.getFormattedTime());
    }
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(epoch));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();

    String t = "";
    t += now.year();
    t += "/";
    t += now.month();
    t += "/";
    t += now.day();
    printToDisp(t.c_str());

    t = "";
    t += daysOfTheWeek[now.dayOfTheWeek()];
    printToDisp2(t.c_str());

    String period = " AM";
    uint8_t periodOffset = 0;
    if (now.hour() > 12) {
      period = " PM";
      periodOffset = 12;
    }

    t = "";
    t += now.hour() - periodOffset;
    t += ":";
    if (now.minute() < 10) t += "0";
    t += now.minute();
    t += ":";
    if (now.second() < 10) t += "0";
    t += now.second();
    t += period;
    printToDisp3(t.c_str());

    delay(500);
}
