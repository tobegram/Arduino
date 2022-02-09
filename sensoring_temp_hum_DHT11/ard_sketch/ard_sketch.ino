//DHT Bibliothek laden
#include "DHT.h" 
#include <OneWire.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN 2 //Der Sensor wird an PIN 2 angeschlossen    

#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

//cs or the save select pin from the sd shield is connected to 10.
const int chipSelect = 10; 

//Der Sensor wird ab jetzt mit „dth“ angesprochen
DHT dht(DHTPIN, DHTTYPE); 

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
  //setup SD card
  // see if the SD card is present and can be initialized:
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  // write header into csv file
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.print("Datum");
  dataFile.print(",");
  dataFile.println("Temperatur");

  // doublecheck on serial monitor
  Serial.print("Datum");
  Serial.print(",");
  Serial.println("Temperatur");

}

void loop() {
  
  delay(2000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)

  
  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern
  
  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern
  
  Serial.println(Temperatur);
  Serial.println(Luftfeuchtigkeit);
  
  //read the time
  now = RTC.now();
  
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
    dataFile.print(",");

    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  //delay(60000); // this will log the temperature every minute.
  delay(3000);



  
}
