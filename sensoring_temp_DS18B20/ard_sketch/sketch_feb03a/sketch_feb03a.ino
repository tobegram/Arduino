// Hardware: Arduino + DatenLogger Modul Data Recorder Shield
// Temperature sensor: DS18B20; wires: 3,3V, Ground, DigitalPin 2
// Display: OLED 128 x 64 SSD1306; wires 5V, Ground, SDA>>SDA, SCK>>SCL
// 


#include <GyverOLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 2 // Arduino pin connected to DS18B20 sensor's DQ pin


GyverOLED<SSH1106_128x64> oled;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

String tempString;

void setup() {
  Serial.begin(9600);
  oled.init();            // initialize the OLED
  tempSensor.begin();     // initialize the sensor
  tempString.reserve(10); // to avoid fragmenting memory when using String

  delay(2000);         // wait for initializing
}

void loop() {
  tempSensor.requestTemperatures();             // send the command to get temperatures
  float tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  tempString  = String(tempCelsius, 2); // two decimal places
  Serial.println(tempString); // print the temperature in Celsius to Serial Monitor
  
  
  oled.clear();
  oled.home();
  oled.setScale(3);
  oled.setCursor(0, 3);
  oled.print(tempCelsius);
  oled.circle(100, 27, 3);
  oled.setScale(3);
  oled.setCursor(108, 3);
  oled.print("C");
  oled.update();
  

  delay(1000);
}
