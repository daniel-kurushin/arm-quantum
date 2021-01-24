from serial import *
from time import sleep
from requests import *
from threading import Thread

connect_flag = False
command = '-1'
in_progress = False

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

def print_com():
	while True:
		pass

def send_to_arduino():
	while True:
		send_command = get_command()
		try:
			prepeare_command(send_command)
			post('http://127.0.0.1:5000/command', data={'command':''})
		except:
			pass
		

message = Thread(target=send_to_arduino,daemon=True)
com_print = Thread(target=print_com,daemon=True)
while connect_flag == False:
	
	com = str(get_com())

	try:
		ARM = Serial(com,9600)
		sleep(2)
		print('Done')
		connect_flag = True
	except:
		pass

	sleep(1)

message.start()
com_print.start()

while True:
	sleep(0.0001)
