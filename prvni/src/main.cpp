#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#define BMP_SCK 18
#define BMP_MISO 19
#define BMP_MOSI 23
#define BMP_CS 16

#define SD_CS 13

//SPIClass spi = SPIClass(VSPI);

Adafruit_BMP280 bme(BMP_CS);


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB

#define LOOP_PERIOD 35 // Display updates every 35 ms

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;



void setup() {

    Serial.begin(115200);
    Serial.println(F("BMP280 test"));

    tft.init();
    tft.setRotation(0); //landscape
    tft.fillScreen(TFT_BLACK);
    //tft.setFont(Times_New_Roman66x53);
    tft.setTextColor(TFT_CYAN);
    tft.setCursor(20,30);
    tft.print("Hello World!");
    // zabezpečit
    bme.begin();
    //spi.begin(BMP_SCK, BMP_MISO, BMP_MOSI, SD_CS);

    SD.begin(SD_CS);

}
//-------------------------------------------------------------------------------------

int indexes = 0;
void loop(void) {
    
        Serial.print("Temperature = ");
        float temp = bme.readTemperature();
        Serial.print(temp);
        Serial.println(" *C");
 
        Serial.print("Pressure = ");
        float pres = Serial.print(bme.readPressure());
        Serial.print(pres);
        Serial.println(" Pa");

        Serial.println();

        //tft.setRotation(rotation);
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(20,30);
        tft.print("Co je ty velka pyco: ");
        tft.print(temp);
        tft.setCursor(20,50);
        tft.print("Je mi hodně: ");
        tft.print(pres);
        tft.print("\n");
        tft.print("SD Card: ");
        tft.print(SD.cardType());
        tft.print("\n"); 
        delay(5000);

}