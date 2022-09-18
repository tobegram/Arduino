import csv
from email import header
from fileinput import filename

filename = 'temp_sensoring_DS18B20/data.csv'
with open(filename) as file:
    reader = csv.reader(file)
    header_row = next(reader)
    print(header_row)