import pandas as pd
import csv

filename = 'temp_hum_sensoring_DHT11/data.csv'
with open(filename) as file:
    reader = csv.reader(file)
    header_row = next(reader)
    print(header_row)

data = pd.read_csv("data.csv", sep=',')

print(data) 