import matplotlib.pyplot as plt
import serial


plt.ion()
plt.figure(figsize=(16,5))
plt.grid(alpha=0.2)
readings = []

with serial.Serial('/dev/cu.usbmodem14201', 9600) as stream:
    while True:
        line = stream.readline()
        reading = int(line.strip())
        readings.append(reading)
        plt.plot(readings, marker='o', color='blue')
        plt.pause(0.1)
        
