import sys				#required for getting command line arguments
from serial import Serial
import time

instruction = ""
operand1  = ""
operand2 = ""
try:
	instruction = sys.argv[1]
except:
	print("No instruction detected!")
	exit(0)
try:
	operand1 = sys.argv[2]
except:
	print("Zero operand instruction")
try:
	operand2 = sys.argv[3]
except:
	print("One operand instruction")

#############INSTRUCTION DEFINITIONS#####################
command_string = ""
if(instruction == "movb"):
	print("")
elif(instruction == "movf"):
	print("")
elif(instruction == "strl"):
	command_string = "1+" + operand1
elif(instruction == "strr"):
	command_string = "1-" + operand1

#############SENDING COMMAND TO ARDUINO##################
ser = Serial("/dev/ttyUSB0", 115200)
ser.close()
ser.open()
time.sleep(2)
command_string = command_string.encode()
print(command_string)
ser.write(command_string)
received_string = ""
while(received_string != command_string.decode().strip()):
	try:
		ser.write(command_string)
		received_string = ser.readline()
		received_string = received_string.decode().strip()
		print(received_string != command_string.decode().strip())
	except:
		received_string = ""
		continue