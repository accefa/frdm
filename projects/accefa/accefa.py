################################################################################
# accefa
#
# author: ninux (nino.ninux@gmail.com)
################################################################################

#!/bin/python

def checkCommand(cmd, show):
    if (show):
        print("testing <" + cmd + ">")
    cmd = cmd + "\n\n"
    term = "accefa>"
    ser.write(cmd.encode('utf-8'))
    sleep(1)
    answer = ser.readline()
    while (answer.find(term.encode('utf-8')) < 0):
        answer = answer.decode('utf-8')
        answer = answer.replace("\n", "")
        if (answer != "" and show):
            print("\t" + answer)
        answer = ser.readline()
    return True

# load libs and extensions
import serial
import time
from time import sleep
import sys

# configure the serial interface
device = "/dev/ttyACM0"
baudrate = 38400

# open the serial interface
ser = serial.Serial(device, baudrate)

# check the serial connection
if ser.isOpen() == True:
    print("connected to " + device)
else:
    printf("connection to " + device + "failed")
    sys.exit()

# define command list
commands = ["help", "status", "BLDC help",
            "BLDC status", "BLDC init", "BLDC reset"]

for item in commands:
    print("executing \"" + item + "\" ...")
    checkCommand(item, False)

# close the serial interface
ser.close()
print("closed the connection to " + device)
