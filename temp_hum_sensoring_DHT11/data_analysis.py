import imp
from shutil import which
import matplotlib.pyplot as plt
import csv
from datetime import datetime

filename = 'temp_hum_sensoring_DHT11/data.csv'
with open(filename) as file:
    reader = csv.reader(file)
    header_row = next(reader)
    
    # takes date and temperature from csv file
    dates, temps = [], []
    for row in reader:
        date = datetime.strptime(row[0], '%a %b  %d %H:%M:%S %Y')
        temp = float(row[1])
        dates.append(date)
        temps.append(temp)
        
       

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.plot(dates, temps, c='red')

# format the diagramm
plt.title("Temperaturkurve vom DHT11", fontsize=24)
plt.xlabel('', fontsize=16)
fig.autofmt_xdate()
plt.ylabel('Temperatur (°C)', fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)

plt.show()