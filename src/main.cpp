#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <SFE_MicroOLED.h>
#include <BlynkSimpleEsp8266.h>

#include "user_config.h"

#define PIN_RESET 255
#define DC_JUMPER 0

MicroOLED oled(PIN_RESET, DC_JUMPER);
WidgetLED led1(V0);

void printTitle(String title, int font) {
    int middleX = oled.getLCDWidth() / 2;
    int middleY = oled.getLCDHeight() / 2;
    oled.clear(PAGE);
    oled.setFontType(font);
    // Try to set the cursor in the middle of the screen
    oled.setCursor(0,middleY - (oled.getFontWidth() / 2));
    // Print the title:
    oled.print(title);
    oled.display();
    delay(1500);
    oled.clear(PAGE);
}

void setup() {
    Serial.begin(115200);
    oled.begin();
    oled.clear(ALL);
    oled.display();
    Blynk.begin(auth,ssid,pass,domain,port);
}

void loop() {
    Blynk.run();
    int sensorValue = analogRead(A0);
    Serial.print(sensorValue);
    int sensorON = digitalRead(D5);
    Serial.print(" Digital output:");
    Serial.println(sensorON);
    if (sensorON == 0){
        led1.on();
    } else {
        led1.off();
    }
    printTitle("Value:" + String(sensorValue), 0);
    delay(100);
}
