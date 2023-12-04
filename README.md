# H2Optimize
# Water Quality Monitoring System with TDS Sensor & ESP32

## Introduction
This Arduino sketch is developed for an IoT-based Water Quality Monitoring System using a TDS sensor, ESP32 microcontroller, and Arduino IoT Cloud. The system enables real-time monitoring of Total Dissolved Solids (TDS) levels, Electrical Conductivity (EC) values, and water temperature. The data is accessible online through the Arduino IoT Cloud, allowing users to observe water quality from anywhere globally. Additionally, the system supports data storage on the cloud for further analysis.

## Components
- ESP32 microcontroller
- TDS sensor
- OneWire temperature sensor
- DallasTemperature library
- DFRobot_ESP_EC library
- Adafruit_ADS1X15 library
- Adafruit_SSD1306 library
- OLED display (SSD1306)
- Arduino IoT Cloud

## Features
- Real-time monitoring of TDS levels, EC values, and water temperature.
- Online access to water quality data through the Arduino IoT Cloud.
- Cloud storage for historical data analysis.

## Wiring
- Temperature sensor: Connect to GPIO pin 18 (ONE_WIRE_BUS).
- TDS and EC sensor: Connected to analog pin 0.
- OLED display: Connected via I2C (SDA, SCL pins).

## Libraries
Install the following libraries using the Arduino Library Manager:
- DallasTemperature
- DFRobot_ESP_EC
- Adafruit_SSD1306
- Adafruit_GFX
- Adafruit_ADS1X15

## Configuration
Update the `thingProperties.h` file with your Arduino IoT Cloud credentials and property definitions.

## Usage
1. Upload the sketch to your ESP32.
2. Open the Serial Monitor to view temperature, TDS, and EC data.
3. Monitor the OLED display for real-time information.
4. Access water quality data online via the Arduino IoT Cloud.
5. Analyze historical data stored on the cloud for insights.

## Considerations
- Adjust GPIO pin numbers and sensor configurations based on your setup.
- Ensure the ESP32 is connected to the internet for IoT Cloud communication.

## Acknowledgments
- This project leverages the power of IoT to enhance water quality monitoring.
- Thanks to the Arduino community for providing libraries and examples.
