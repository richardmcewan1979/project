#need to go into venv due to PySerial module

import serial
import time


print("start")
port="/dev/tty.HC-06-DevB"
bluetooth=serial.Serial(port,9600)
print("Connected")
bluetooth.flushInput()
for i in range(400): #send 10 pings to the blutooth
	print("ping")
	bluetooth.write(b"BOOP "+str.encode(str(i))) #these need to be bytes not unicode, plus a number
	input_data=bluetooth.readline()
	print(input_data.decode()) #these bytes are coming in
	time.sleep(0.1)
bluetooth.close()#otherwise the connection will remain open and clog up the devthingabob
print("Done")
