#include <GyverOLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "RTClib.h"
#include <SD.h>

#define SENSOR_PIN 2 // Arduino pin connected to DS18B20 sensor's DQ pin

// Set Objects and variables
GyverOLED<SSH1106_128x64> oled;
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library
String tempString;
RTC_DS1307 rtc;
DateTime now;
const int shield_pin = 10;
File dataFile;


void setup() {
  Serial.begin(9600);
  oled.init();            // initialize the OLED
  tempSensor.begin();     // initialize the sensor
  tempString.reserve(10); // to avoid fragmenting memory when using String
  RTC.begin();            // initialize real time clock

  // Check if RTC is working and ready to run
  Serial.println("Initializing Real time clock.....");
  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // RTC is adjusted to current time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  // Check if SD is working and ready to run
  Serial.print("Initializing SD Card.....")
  if (!SD.begin(shield_pin)) {
    Serial.println("SD card failed or not present!")
    return;
  }
  // Create or open log file and set header
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.print("Datum");
  dataFile.print(",");
  dataFile.println("Temperatur");

  Serial.println("SD card initialized.")
  delay(2000);         // wait for initializing
}

void loop() {
  tempSensor.requestTemperatures();                   // send the command to get temperatures
  float tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  tempString  = String(tempCelsius, 2);               // two decimal places
  Serial.println(tempString);                         // print the temperature in Celsius to Serial Monitor
  
  
  display_on_oled();                                  // Call function

  delay(1000);
}

// Show the temperature on OLED display
void display_on_oled(){
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
}