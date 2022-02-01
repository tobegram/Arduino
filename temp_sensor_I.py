from base64 import encode
from encodings import utf_8
from fileinput import close
import serial
import time
import csv

# Erzeugen der CSV Datei
data_file = 'data.csv'

# Erstellen einer leeren List für Datem vom Arduino
data_list = []

# Arduino Objekt wird erzeugt
# Print Statement zur Kontrolle des Kommunikation zum Arduino
board = serial.Serial('COM5', 9600)
time.sleep(2)
print("Loop startet")

# Schleife für ankommendes Datenpaket
for i in range(100):
    list_a = []  # Liste durchläuft 2x loop, um Temp und Feuchte zu speichern.
    
    list_a.append(time.ctime())
    for i in range(2):
        buffer = board.readline()
        data_raw = buffer.decode()
        data_clean = data_raw[:-3]
        list_a.append(data_clean)
    
    data_list.append(list_a)
    

with open(data_file, 'w', encoding='UTF8', newline="") as file:
    header = ['Datum', 'Temperatur', 'Feuchte']
    writer = csv.writer(file)
    writer.writerow(header)
    writer.writerows(data_list)
    

print("Loop endet")


