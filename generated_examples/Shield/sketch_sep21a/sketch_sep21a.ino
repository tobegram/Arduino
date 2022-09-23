#include <SPI.h> // Einbinden der SD Bibliothek
#include <SD.h> // Einbinden der SD Bibliothek
#include <Wire.h> // Einbinden der SPI Bibliothek
#include "RTClib.h" // Einbinden der Adafruit DS1307 RTC Bibliothek
#define MeasureDelay 5000 // Pause in ms zwischen einzelnen Messungen
const String LogFileName = "/Daten.csv";
const int chipSelect = 10; // Für Datenlogger Modul am Arduino Uno so lassen
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
void setup(){
  Serial.begin(9600); // Öffne serielle Schnittsatelle
  while (!Serial) { // Warte auf seriellen Port
}
Serial.print("\nInitalisierung SD Karte ");
if (!SD.begin(chipSelect))
{
Serial.println("ist fehlgeschlagen!");
while (1);
}
Serial.println("ist erfolgreich.");
if (! rtc.begin())
{
Serial.println("RTC nicht an I2C Bus gefunden!");
while (1);
}
if (! rtc.isrunning())
{
Serial.println("RTC laueft nicht! Bitte initalisieren!");
while (1);
}
Serial.println("RTC funktionsbereit!");
if (!(SD.exists(LogFileName)))
{
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
File LogFilePtr = SD.open(LogFileName,FILE_WRITE); // Datei zum Schreiben öffnen. Es kann jeweils nur 1 Datei
// gleichzeitig geschrieben werden !
if (LogFilePtr) // Wenn Datei zum schreiben bereit ist, schreibe Kopfzeile (Header) hinein
{
LogFilePtr.println("Zeitstempel;Wert Analogport 1;Wert Analogport 2;Wert Analogport 3");
Serial.println("Log Datei im FS neu erzeugt.");
LogFilePtr.close(); // Datei schließen
}
}
}
void loop(void)
{
DateTime now = rtc.now(); // Hole aktuelle Uhrzeit aus RTC
String dataString = ""; // erzeuge neuen Eintrag für CSV Datei
dataString = String(daysOfTheWeek[now.dayOfTheWeek()]) + "," + (String(now.day())) + "." + now.month();
dataString += String(".") + now.year() + " " + now.hour() +":" + now.minute()+ ":" + now.second()+ ";"; // Erzeuge
//Zeitstempel
// Lese die Werte der übriggebliebenen 3 Analogeingänge und füge sie dem String hinzu (A4 und A5 für I2C Bus
//genutzt)
for (int analogPin = 0; analogPin < 3; analogPin++)
{
int sensor = analogRead(analogPin);
dataString += String(sensor);
if (analogPin < 2)
{
dataString += ";";
}
}
File LogFilePtr = SD.open(LogFileName, FILE_WRITE); // Datei zum Schreiben öffnen.
if (LogFilePtr) // Wenn Datei zum schtreiben bereit ist, schreibe hinein
{
LogFilePtr.println(dataString);
LogFilePtr.close(); // Datei schließen
Serial.println(dataString); // Aus serieller schnittstelle auch ausgeben
}
else
{
Serial.println("Fehler beim oeffnen");
}
delay(MeasureDelay);
}
