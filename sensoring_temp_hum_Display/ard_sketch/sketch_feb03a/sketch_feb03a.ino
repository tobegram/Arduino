// Hardware: Arduino + DatenLogger Modul Data Recorder Shield
// Temperature sensor: DHT11; wires: 3,3V, Ground, DigitalPin 2
// Display: OLED 128 x 64 SSD1306; wires 5V, Ground, SDA>>SDA, SCK>>SCL
 

// Bibliotheken für das Display
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"


// Bibliotheken für den TempFechte Sendor
#include "DHT.h" 

// Bibliotheken für das Shield
#include "RTClib.h" // Einbinden der Adafruit DS1307 RTC Bibliothek
#include <SD.h> // Einbinden der SD Bibliothek
#include <SPI.h> // Einbinden der SD Bibliothe
#include <Wire.h> // Einbinden der SPI Bibliothek

// Konfiguration des DHT11 sensors
#define DHTPIN 2 
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);


// Konfigurieren der OLED
#define I2C_ADDRESS 0x3C  // 0x3C alt add = 0x3D
SSD1306AsciiWire oled;    // create an "oled" object


// Konfigurieren vom Shield
RTC_DS1307 rtc;
DateTime now;
File dataFile;
const int shield_pin = 10; // Für Datenlogger Modul am Arduino Uno so lassen

void setup() {
  
  //Initilaize all components
  Serial.begin(9600);
  dht.begin();     
  Wire.begin();
  Wire.setClock(100000);
  oled.begin(&SH1106_128x64, I2C_ADDRESS);
  rtc.begin();            // initialize real time clock
  
  // Setup OLED and run first pixel show
  oled.setFont(Arial_bold_14);  
  oled.clear();
  oled.println("----------------");
  oled.println("----------------");
  oled.println("----------------");
  oled.println("----------------");
  delay(1000);
  oled.clear();
  oled.home();


  // Check if RTC is working and ready to run
  oled.println("Init ");
  oled.SSD1306Ascii::setCursor(0,2);
  oled.println("Real time ");
  oled.SSD1306Ascii::setCursor(0,4);
  oled.println("clock.....");
  if (!rtc.isrunning()) {
    oled.println(F("RTC is NOT running!"));
    // RTC is adjusted to current time
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(2000);
  oled.clear();
  oled.home();

  
  DateTime time = rtc.now();
  oled.SSD1306Ascii::setCursor(0,2);
  oled.println("TIMESTAMP");
  delay(2000);
  oled.clear();
  oled.home();
  oled.println(time.timestamp(DateTime::TIMESTAMP_DATE));
  delay(2000);
  oled.clear();
  oled.home();
  

  // Check if SD is working and ready to run
  oled.print(F("Initit SD Card....."));
  delay(1000);
  if (!SD.begin(shield_pin)) {
    oled.println("SD card failed!");
    return;
  }

  // Create or open log file and set header
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.print("Datum");
  dataFile.print(",");
  dataFile.println("Temperatur");

  oled.home();
  oled.println("SD card");
  oled.SSD1306Ascii::setCursor(0,4);
  oled.println("initialized.");
  delay(2000);
  oled.clear();
  oled.home();
}

void loop() {
  int hum = dht.readHumidity(); 
  float temp = dht.readTemperature();
  
  oled.SSD1306Ascii::setCursor(0,0);
  oled.print("Temp");       // leaves cursor at next char in row.
  oled.SSD1306Ascii::setCursor(6*14,0);
  oled.print(temp);
  oled.SSD1306Ascii::setCursor(8*15,0);
  oled.print("G");
  

  oled.SSD1306Ascii::setCursor(0,4);  // note rows are 8 pixels and our font is 16 pixels
  oled.print("Humidity");       // leaves cursor at next char in row.
  oled.SSD1306Ascii::setCursor(7*14,4);
  oled.print(hum);
  oled.SSD1306Ascii::setCursor(8*15,4);
  oled.print("%");
  oled.clearField(8*8,2,7);
  
                       
  
  

  delay(1000);


}
