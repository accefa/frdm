#!/bin/python

################################################################################
# accefa
#
# author: ninux (nino.ninux@gmail.com)
################################################################################

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
import curses

# check arguments
show = False
if len(sys.argv) == 2:
    opt = str(sys.argv)
    if str(sys.argv[1]) == "-s":
        show = True

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
cmd_CLS1 = ["help", "status"]
cmd_BLDC = ["BLDC help", "BLDC status", "BLDC on", "BLDC off", 
    "BLDC setrpm 0", "BLDC reset", "BLDC init"]
cmd_STP = ["STP help", "STP status", "STP on", "STP off", "STP move 0",
    "STP reset"]
cmd_DC = ["DC help", "DC status", "DC on", "DC off", "DC up", "DC down",
    "DC setpwm 0", "DC reset"]

cmd_all = cmd_CLS1 + cmd_BLDC + cmd_STP + cmd_DC

for item in cmd_all:
    print("executing \"" + item + "\" ...")
    checkCommand(item, show)

# close the serial interface
ser.close()
print("closed the connection to " + device)
