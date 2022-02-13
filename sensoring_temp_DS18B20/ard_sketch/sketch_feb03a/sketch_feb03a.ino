#include <OneWire.h>
#include <SPI.h> // SPI Bus for communication with SD card
#include <SD.h>   // libary for SD writing and Reading
#include <Wire.h>
#include "RTClib.h"

//cs or the save select pin from the sd shield is connected to 10.
const int chipSelect = 10; 

// temperature sensor on pin 2
OneWire  d_pin(2);  


float celsius;
RTC_DS1307 RTC;
File dataFile;
DateTime now;

void setup(void) {
  Serial.begin(9600);

  Wire.begin();
  
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

void loop(void) {
  
  // read temperature
  pickUpTemperature();
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
    dataFile.println(celsius);
    
    
    
   
    dataFile.close();
    
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  //delay(60000); // this will log the temperature every minute.
  delay(3000);
}


// fuction with check the temperature sensor and update the tempeature. 
void pickUpTemperature(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
 
  
  if ( !d_pin.search(addr)) {
    
    d_pin.reset_search();
    delay(250);
    return;
  }
  
  
  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    // for  Chip = DS18S20
    case 0x10:
      type_s = 1;
      break;
    // for  Chip = DS18B20
    case 0x28:
      type_s = 0;
      break;
    // for  Chip = DS1822
    case 0x22:
      type_s = 0;
      break;
    
    //Device is not a DS18x20 family
    default:
      return;
  } 

  d_pin.reset();
  d_pin.select(addr);
  d_pin.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = d_pin.reset();
  d_pin.select(addr);    
  d_pin.write(0xBE);         // Read Scratchpad

  
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = d_pin.read();
   
  }

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  
  Serial.print(now.month(),DEC);
  Serial.print(" ");
  Serial.print(now.day(),DEC);
  Serial.print(" ");
  Serial.print(now.hour(),DEC);
  Serial.print(":");
  Serial.print(now.minute(),DEC);
  Serial.print(":");
  Serial.print(now.second(),DEC);
  Serial.print(" ");
  Serial.print(now.year(),DEC);
  Serial.print(",");
  Serial.println(celsius);
  
  
}
