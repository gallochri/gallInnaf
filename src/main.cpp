#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <SFE_MicroOLED.h>
#include <ThingSpeak.h>

#include "user_config.h"

#define PIN_RESET 255
#define DC_JUMPER 0

MicroOLED oled(PIN_RESET, DC_JUMPER);
int status = WL_IDLE_STATUS;
WiFiClient client;

void printTitle(String title, int font) {
    int middleX = oled.getLCDWidth() / 2;
    int middleY = oled.getLCDHeight() / 2;
    oled.clear(PAGE);
    oled.setFontType(font);
    // Try to set the cursor in the middle of the screen
    oled.setCursor(0, middleY - (oled.getFontWidth() / 2));
    // Print the title:
    oled.print(title);
    oled.display();
    delay(1500);
    oled.clear(PAGE);
}

void setup() {
    WiFi.begin(ssid,pass);
    ThingSpeak.begin(client);
    Serial.begin(115200);
    oled.begin();
    oled.clear(ALL);
    oled.display();
}

void loop() {
    int sensorValue = analogRead(A0);
    Serial.print(sensorValue);
    int sensorON = digitalRead(D5);
    Serial.print(" Digital output:");
    Serial.println(sensorON);
    printTitle("Value:" + String(sensorValue), 0);
    ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);
    delay(1000*60);
}

