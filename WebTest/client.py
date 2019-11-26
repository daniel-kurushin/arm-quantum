from serial import *
from time import sleep
from requests import *

connect_flag = False
send_command = ''

def get_com():
	try:
		res = get('http://127.0.0.1:5000/connect')
		return res.text
	except:
		res = -1
		return res

def get_command():
    command = get('http://127.0.0.1:5000/command')
    return command.text

def prepeare_command(send_command):
	b = 48
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	b = int(send_command[2]) + 48
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	b = int(send_command[3]) + 48
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	b = 102
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	ARM.write(b.to_bytes(length=1, byteorder='big', signed=False))
	
def serial_print():
	recive = str(ARM.readline())
	t = ("b'", "\\r\\n'", "\\n'")

	for i in t:
		recive = recive.replace(i, '')
		
	l = recive.split('\\t')
	# print(l)
	if len(l) > 1:
		for i in l:
			print(i, end = "\t")
		print()
	else:
		print(l[0])

while True:
    while connect_flag == False:
    	
    	com = str(get_com())
    
    	try:
    		ARM = Serial(com,9600)
    		sleep(2)
    		print('Done')
    		connect_flag = True
    	except:
    		print('Error')
    
    	sleep(1)
    
    while connect_flag == True:
    	send_command = '0011ff'
    	prepeare_command(send_command)
    	for i in range(40):
    		serial_print()
    	send_command = '0012ff'
    	prepeare_command(send_command)
    	connect_flag = False
    	