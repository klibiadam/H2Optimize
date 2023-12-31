
#include "thingProperties.h"
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <DFRobot_ESP_EC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
#define ONE_WIRE_BUS 18               
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;
 
float voltage;
void setup() {
Serial.begin(115200);
  EEPROM.begin(32);//needed EEPROM.begin to store calibration k in eeprom
  ec.begin();
  ads.setGain(GAIN_ONE);
  ads.begin();
  sensors.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
 
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}
void loop() {
  ArduinoCloud.update();
  voltage = ads.readADC_SingleEnded(0) / 10;
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);  // read your temperature sensor to execute temperature compensation
  ecValue = ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
  tDS = ((ecValue * 1000) / 2);
 
  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC");
  
  Serial.print("TDS:");
  Serial.print(tDS, 2);
  Serial.println("PPM");
 
  Serial.print("EC:");
  Serial.println(ecValue, 2);
 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 2);
  display.print("T:");
  display.print(temperature, 2);
  display.drawCircle(85, 2, 2, WHITE); // put degree symbol ( ° )
  display.setCursor(90, 2);
  display.print("C");
  
  display.setCursor(0, 25);
  display.print("TDS:");
  display.print(tDS, 2);
  display.setCursor(100, 25);
  display.setTextSize(1);
  display.print("PPM");
 
 display.setTextSize(2);
  display.setCursor(0, 50);
  display.print("EC:");
  display.print(ecValue, 2);
  display.display();
  delay(1500);
  display.clearDisplay();
 
  ec.calibration(voltage, temperature); // calibration process by Serail CMD
  
  
}
