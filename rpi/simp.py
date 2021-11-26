from serial import Serial
import time

ser = Serial("/dev/ttyUSB0", 115200)
ser.close()
ser.open()
time.sleep(2)
command = "1+15.00"
command = command.encode(encoding="ascii")

ser.write(command)
while(True):
	print(">>", ser.readline().decode())