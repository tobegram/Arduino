# Import Libaries
import serial
import matplotlib.pyplot as plt
from drawnow import *

# Create temperature list
temps = []

# Creats an object for serial input from Arduino
sensor = serial.Serial('Com5', 9600)

# Tell mathplot that data is in interactive mode
plt.ion()

# Configure graph
def create_graph():
    plt.title('Temperaturkurve dynamisch')
    plt.ylabel('Temp in °C')
    plt.plot(temps, 'ro-')
    
    
# main loop takes temp data from Arduino and draw it as a graph
while True:
    # Waiting until data is received
    while (sensor.inWaiting() == 0):
        pass
    dataString = sensor.readline()
    temp = float(dataString)
    temps.append(temp)
    drawnow(create_graph)
