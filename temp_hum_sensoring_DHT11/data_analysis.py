from shutil import which
import matplotlib.pyplot as plt
import csv

filename = 'temp_hum_sensoring_DHT11/data.csv'
with open(filename) as file:
    reader = csv.reader(file)
    header_row = next(reader)
  
    temps = []
    for row in reader:
        temp = float(row[1])
        temps.append(temp)
        
       

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.plot(temps, c='red')

# format the diagramm
plt.title("Temperaturkurve vom DHT11", fontsize=24)
plt.xlabel('', fontsize=16)
plt.ylabel('Temperatur (°C)', fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)

plt.show()