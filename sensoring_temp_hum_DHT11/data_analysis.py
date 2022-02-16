import imp
from shutil import which
import matplotlib.pyplot as plt
import csv
from datetime import datetime
from matplotlib.dates import DayLocator, HourLocator, DateFormatter, drange

filename = 'sensoring_temp_hum_DHT11/arbeitszimmer.csv'
#filename = 'sensoring_temp_hum_DHT11/küche.csv'
#filename = 'sensoring_temp_hum_DHT11/schlafzimmer.csv'
#filename = 'sensoring_temp_hum_DHT11/wohnzimmer.csv'

with open(filename) as file:
    reader = csv.reader(file)
    header_row = next(reader)
    
    # takes date, temperature and huminity from csv file
    dates, temps, hums = [], [], []
    for row in reader:
        date = datetime.strptime(row[0], '%m %d %H:%M:%S %Y')
        temp = float(row[1])
        hum = float(row[2])
        dates.append(date)
        temps.append(temp)
        hums.append(hum)
        
       
fig = plt.figure()
plt.style.use('seaborn')
tempx = fig.add_subplot(211)
tempx.set_title("Temperaturkurve vom DHT11")
tempx.plot(dates, temps, c='red')
humx = fig.add_subplot(212)
humx.plot(dates, hums, c='blue')
humx.set_title("Feuchtekurve vom DHT11")

# format the temp-diagramm
plt.xlabel('', fontsize=8)
fig.autofmt_xdate()
plt.tick_params(axis='both', which='major', labelsize=12)

plt.show()




