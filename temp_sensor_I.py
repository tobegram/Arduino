from base64 import encode
from encodings import utf_8
from fileinput import close
import serial
import time
import csv

# Erzeugen der CSV Datei
data_file = 'data.csv'

# Initialisieren der Daten-Liste und schreiben des Tabellenkopfes in die csv Datei
data_list = ["Datum", "Temperatur [°C]", "Feuchte [%]"]



# Arduino Objekt wird erzeugt
# Print Statement zur Kontrolle des Kommunikation zum Arduino
board = serial.Serial('COM5', 9600)
time.sleep(2)
print("Loop startet")

# Schleife für ankommendes Datenpaket
for i in range(6):
    list_a = []  # Liste durchläuft 2x loop, um Temp und Feuchte zu speichern
    
    list_a.append(time.ctime())
    for i in range(2):
        buffer = board.readline()
        data_raw = buffer.decode()
        data_clean = data_raw[:-3]
        list_a.append(data_clean)
    
    data_list.append(list_a)
    print(data_list)
    
            
    
    
    with open(data_file, 'w') as file:
        writer = csv.writer(file, delimiter=',')
        writer.writerow(data_list)
    
    file.close

print("Loop endet")


