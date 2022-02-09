//DHT Bibliothek laden
#include "DHT.h" 
#include <OneWire.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

// Konfiguration des DHT11 sensors
#define DHTPIN 2 //Sensor auf Pin 2
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

//cs or the save select pin from the sd shield is connected to 10.
const int shield_pin = 10; 

float celsius;
RTC_DS1307 RTC;
File dataFile;
DateTime now;

void setup() {
  Serial.begin(9600); //Serielle Verbindung starten
  dht.begin(); //DHT11 Sensor starten

//setup clock
  Wire.begin();
  RTC.begin();
  //check if Real Time Clock is on
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // uncomment it & upload to set the time, date and start run the RTC!
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  // see if the SD card is present and can be initialized:
  Serial.print("Initializing SD card...");
  if (!SD.begin(shield_pin)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  // write header into csv file
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.print("Datum");
  dataFile.print(",");
  dataFile.print("Temperatur");
  dataFile.print(",");
  dataFile.println("Luftfeuchtigkeit");

  // doublecheck on serial monitor
  Serial.print("Temperatur");
  Serial.print(",");
  Serial.println("Luftfeuchtigkeit");

}

void loop() {
  
  delay(2000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)

  
  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern
  
  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern
  //read the time
  now = RTC.now();

 
  Serial.print(Temperatur);
  Serial.print(",");
  Serial.println(Luftfeuchtigkeit);
  
  
  
  //open file to log data in.
  dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  // log the temperature and time.
  if (dataFile) {
    
    dataFile.print(now.month(),DEC);
    dataFile.print(" ");
    dataFile.print(now.day(),DEC);
    dataFile.print(" ");
    dataFile.print(now.hour(),DEC);
    dataFile.print(":");
    dataFile.print(now.minute(),DEC);
    dataFile.print(":");
    dataFile.print(now.second(),DEC);
    dataFile.print(" ");
    dataFile.print(now.year(),DEC);
    dataFile.print(",");
    dataFile.print(Temperatur);
    dataFile.print(",");
    dataFile.print(Luftfeuchtigkeit);
    dataFile.println(",");

    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.csv (SD card??)");
  }
  //delay(60000); // this will log the temperature every minute.
  delay(3000);



  
}
