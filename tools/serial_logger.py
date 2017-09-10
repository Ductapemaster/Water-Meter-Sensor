#!/Users/Ductapemaster/anaconda/envs/python_serial_logger/bin/python3

import serial
import time

port = '/dev/tty.wchusbserial1410'
baud = 115200
file_path = input("File: ")

f = open(file_path + ".csv", "w+")
s = serial.Serial(port, baud)

while True:
    line = s.readline()

    # ser.readline returns a binary, convert to string
    # Remove any trailing whitespace and newlines
    line = line.decode("utf-8").strip()
    
    print(line)
    f.write(line + "\n")