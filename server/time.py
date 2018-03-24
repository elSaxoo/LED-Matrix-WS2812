import serial
import time

serialport = serial.Serial("/dev/ttyAMAO", 115200)

while True:
    data = serialport.read_until()
    if data == 0xFF:
        t = time.time()
        print(t)
        serialport.write(t)

    print (str(data))