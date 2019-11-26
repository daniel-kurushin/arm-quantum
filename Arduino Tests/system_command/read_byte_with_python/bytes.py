from serial import Serial
import sys
import time

arduino = Serial('/dev/ttyUSB0', 9600, timeout =1)

def prepare_coomand(*args):
	b = 48;
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
	b = args[0] + 48;
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
	b = args[1] + 48;
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))

	if len(args)>2:
		b = args[2];
		arduino.write(b.to_bytes(length=2, byteorder='big', signed=True))
		# b = args[3];
		# arduino.write(b.to_bytes(length=2, byteorder='big', signed=True))
		# b = args[4];
		# arduino.write(b.to_bytes(length=2, byteorder='big', signed=True))
	
	b = 102;
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
	arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))


def serial_print():
	recive = str(arduino.readline())
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


if __name__ == "__main__":
	serial_print()
	serial_print()
	# prepare_coomand(1,1)#initialization
	# for i in range(680):
	# 	serial_print()

	# prepare_coomand(1,2)#stop
	# for i in range(25):
	# 	serial_print()

	prepare_coomand(1,3,-300)
	for i in range(40):
		serial_print()

	# prepare_coomand(1,3,300, 400, -90)
	# for i in range(40):
	# 	serial_print()


