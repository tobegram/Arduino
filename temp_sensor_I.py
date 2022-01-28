from fileinput import close
import serial
import time
import csv

# Erzeugen der CSV Datei
data_file = 'data.csv'

# Initialisieren der Daten-Liste und schreiben des Tabellenkopfes in die csv Datei
data_list = ["Datum", "Temperatur [°C]", "Feuchte [%]"]

with open(data_file, 'w') as file:
        writer = csv.writer(file)
        writer.writerow(data_list)

# Arduino Objekt wird erzeugt
# Print Statement zur Kontrolle des Kommunikation zum Arduino
board = serial.Serial('COM5', 9600)
time.sleep(2)
print("Loop startet")

# Schleife für ankommendes Datenpaket
for i in range(6):
    list_a = []
    list_abc = []
    list_a.append(time.ctime())
    for i in range(2):
        buffer = board.readline()
        data_raw = buffer.decode()
        data_clean = data_raw[:-3]
        list_a.append(data_clean)
    list_abc.extend(list_a)
    print(list_abc)
    data_list.extend(list_abc)
    print(data_list)
            
    """
    with open(data_file, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data_list)"""

print("Loop endet")


