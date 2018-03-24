import serial
import datetime

serialport = serial.Serial("/dev/ttyAMAO", 115200, timeout=0.5)

while True:
    command = serialport.read()
    print str(command)