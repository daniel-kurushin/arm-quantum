from serial import Serial

arduino = Serial('/dev/ttyUSB0', 9600, timeout =1)
 
while 1:
    x = 600
    arduino.write(x.to_bytes(length=2, byteorder='little'))
    print (arduino.read())
