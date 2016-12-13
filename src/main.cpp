#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SFE_MicroOLED.h>

#define PIN_RESET 255
#define DC_JUMPER 0

MicroOLED oled(PIN_RESET, DC_JUMPER);

void printTitle(String title, int font) {
    int middleX = oled.getLCDWidth() / 2;
    int middleY = oled.getLCDHeight() / 2;

    oled.clear(PAGE);
    oled.setFontType(font);
    // Try to set the cursor in the middle of the screen
    oled.setCursor(0,
                   middleY - (oled.getFontWidth() / 2));
    // Print the title:
    oled.print(title);
    oled.display();
    delay(1500);
    oled.clear(PAGE);
}

/*Sketch per rilevare l'umidita' del terreno (valore analogico)*/
void setup() {
    Serial.begin(115200);
    oled.begin();
    oled.clear(ALL);
    oled.display();
}

void loop() {
    int sensorValue = analogRead(A0); //Legge il valore analogico
    Serial.print(sensorValue); //Stampa a schermo il valore
    int sensorON = digitalRead(D5);
    Serial.print(" Digital output:");
    Serial.println(sensorON);
    printTitle("Value:" + String(sensorValue), 0);
    delay(2000); //Attende due secondi
}
