// Simple I2C test for ebay 128x64 oled.
// Uses the standard Wire.h class as we think the BME680 will already use wire. was: Use smaller faster AvrI2c class in place of Wire.
// Edit AVRI2C_FASTMODE in SSD1306Ascii.h to change the default I2C frequency.
// 2019-05-17 added Bill Greiman's comment regarding the addition of "Wire.begin()"  now working at 100Khz

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C  // 0x3C alt add = 0x3D
SSD1306AsciiWire oled;    // create an "oled" object

//------------------------------------------------------------------------------
// Setup displays variable names and units.
//  We still have to identify the location and length for variable values.
//  We should in the future create functions to do the length and position calc.

void setup() {

  Wire.begin();
  Wire.setClock(100000);
  
  oled.begin(&SH1106_128x64, I2C_ADDRESS);
  oled.setFont(Arial_bold_14);  
  oled.clear();

// Fill display so we can see what is being cleared.
  oled.println("----------------");
  oled.println("----------------");
  oled.println("----------------");
  oled.println("----------------");
  delay(1000);
  oled.clearField(0,0,127);
  oled.clearField(0,3,127);
  

//                (C,R)
  oled.SSD1306Ascii::setCursor(0,0);
  oled.print("Temp");       // leaves cursor at next char in row.
  oled.SSD1306Ascii::setCursor(6*15,0);
  oled.print("24,5");
  oled.SSD1306Ascii::setCursor(8*15,0);
  oled.print("G");
  

  oled.SSD1306Ascii::setCursor(0,4);  // note rows are 8 pixels and our font is 16 pixels
  oled.print("Humidity");       // leaves cursor at next char in row.
  oled.SSD1306Ascii::setCursor(7*14,4);
  oled.print("76");
  oled.SSD1306Ascii::setCursor(8*15,4);
  oled.print("%");
  oled.clearField(8*8,2,7);
  
  
} 

void loop() {}
