# import the needed extensions for python3
import serial
from serial import Serial, SEVENBITS, STOPBITS_ONE, PARITY_NONE
import time
from time import sleep
import sys

# configure messages
MSG_HELLO = "hello world\n"
MSG_ROTATE = "rotate\n"

# configure the serial connection
baudrate = 38400
device = '/dev/ttyACM0'

# open the serial connection (check with dmesg)
ser = serial.Serial(device, baudrate)
ser.flushInput()
ser.flushOutput()

# check the serial connection
if ser.isOpen() == True:
    print("established connection with " + device)
else:
    print("connecting to " + device + " failed")
    print("closing application...")
    sys.exit()

# write the test message
ser.write(MSG_HELLO.encode())

# wait for transmission
# sleep(1)

# read and print answer
answer = ser.readline()

# close the serial connection
ser.close()
