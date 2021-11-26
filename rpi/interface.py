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
	print("Zero operand instruction detected")
try:
	operand2 = sys.argv[3]
except:
	print("One operand instruction detected")

#############INSTRUCTION DEFINITIONS#####################
command_string = ""
if(instruction == "movb"):
	command_string = "0-" + operand1
elif(instruction == "movf"):
	command_string = "0+" + operand1
elif(instruction == "strl"):
	command_string = "1+" + operand1
elif(instruction == "strr"):
	command_string = "1-" + operand1

#############SENDING COMMAND TO ARDUINO##################
port = "/dev/ttyUSB0"
baudrate = 115200
try:
	ser = Serial(port, baudrate)
	ser.close()
	ser.open()
	time.sleep(2)
	command_string = command_string.encode()
	print(command_string)
	ser.write(command_string)
	received_string = ""
	#while(received_string != command_string.decode().strip()):
	try:
		ser.write(command_string)
		received_string = ser.readline()
		received_string = received_string.decode().strip()
		print("String received from device at", port)
		print("\x1B[94m", received_string, "\x1B[0m")
		print("Comparison result: ", received_string != command_string.decode().strip())
	except:
		print("\x1B[91mError occurred while communicating with device at ", port, "\x1B[0m")
		received_string = ""
		#continue
except:
	print("\x1B[91mError occurred while communicating with device at", port, "\x1B[0m")