# -*- coding: utf-8 -*-
"""
Created on Mon Aug 12 13:41:28 2019

@author: korot
"""
import os
from sys import stderr 
from serial import Serial, SerialException
from time import sleep
import cv2 as cv
from matplotlib import pyplot as plt
from PIL import Image
import math
from requests import get, post

Coefficient = 0.18# коэффицент сравнения
Step=10# шаг в пикселях
Compress=16 # сжатие изображения 

prefabs = ['red cube', 'blue cube']

dictionary = {
    'возьми':'',
    'зелёный':'green ',
    'красный':'red ',
    'синий':'blue ',
    'куб':'cube ',
    'шар':'sphere ',
    'sphere':'sphere ',
    'cube':'cube ',
    'blue':'blue ',
    'red':'red ',
    'green':'green ',
    'изоленту':'cube ',
    'синюю':'blue '
} 


# сделать снимок
def photo():
    cap = cv.VideoCapture(0)
    for i in range(30):
        cap.read()    
    ret, frame = cap.read()
    cv.imwrite('test.png', frame)   
    cap.release()   
    cv.imshow    
    r2=cv.imread('test.png') 
    return r2        

def translate(command):
    request = ''
    for i in range(len(command)):
        command[i] = command[i].lower()
        request += dictionary[command[i]]
    return request

def prepare_coomand(*args):
    b = 48;
    arduino = connect_1()
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
    
    b = args[0] + 48;
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
    b = args[1] + 48;
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))

    if len(args)>2:
        for b in args[2:]:
            arduino.write(b.to_bytes(length=2, byteorder='big', signed=True))       
    
    b = 102;
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
    arduino.write(b.to_bytes(length=1, byteorder='big', signed=False))
    disconnect_1(arduino)

def simple_command(command):
    if command.lower() == 'stop':
        prepare_coomand(1,2)
    elif command.lower() == 'default':
        print('True')
        prepare_coomand(1,1)

def type_command(command, manipulator):
    if len(command) == 1:
        simple_command(command[0])
    elif len(command) == 3:
        arduino = connect_1()
        arduino.write(b"1")
        arduino.write(b"0")
        disconnect_1(arduino)
    elif len(command) == 2:
        #arduino = connect_1()
        command = get('http://127.0.0.1:5000/coord').text.split()
        print(command)
        prepare_coomand(1,3,int(command[0]),int(command[1]),int(command[2]))
        #onSend(arduino,int(command[0]),int(command[1]),int(command[2]),int(command[3]),int(command[4]))
        #disconnect_1(arduino)
    else:
        pass

    post('http://127.0.0.1:5000/command',{'command':''})

def search(manipulator):
    default_rotate = []
    arduino = connect_1()
    for i in range(10):
        for i in range(len(prefabs)):
            x,y = manipulator.search_object(prefabs[i])
            if (x != 0) or (y != 0):
                arduino.write()


# сравнение        
def compare(r1, r2_2):
    sum_dif = 0.0
    for y in range(Compress):
        for x in range (Compress):
            for channel in range (3):
                p1=int(r1 [y][x][channel])
                p2=int(r2_2 [y][x][channel])
                dif = abs (p1-p2)
                sum_dif +=dif/255
    return sum_dif /(16*16*3)

def connect_1(com='com10',serial=9600):
    arduino = Serial(com, serial)
    sleep(3)
    return arduino

def disconnect_1(arduino):
    arduino.close()

def onSend(arduino,n,c,x,y,z):
    n = n.to_bytes(1, 'little')
    c = c.to_bytes(1, 'little')
    x = x.to_bytes(2, 'little', signed=1)
    y = y.to_bytes(2, 'little', signed=1)
    z = z.to_bytes(2, 'little', signed=1)
    
    send(arduino,n, c, x, y, z)

def send(arduino,n, c, x, y, z):
    print("1")
    arduino.write(b"00%s%s%s%s%s0" % (c, n, x, y, z))
    print("2")



class Manipulator():
    def  __init__ (self):
        #print(time, self, file=stderr)
        self.r2=photo()
        im2 = Image.open('test.png')
        (self.x,self.y) = im2.size
        
    def search_object(self,object_serch):
        #найти объект на снимке
        self.x_degree=0
        self.y_degree=0
        self.object_file=object_serch
        for Y1 in range (0,self.y,Step): 
            print('конец строки', file=stderr)
            for X1 in range (0,self.x,Step):
                for path, dirs, files in os.walk(self.object_file):
                    for f in files:
                        i = '%s/%s' % (path, f)
                        self.r1=cv.imread(i)
                        im1 = Image.open("%s/%s" % (path, f))
                        (x1,y1) = im1.size
                        self.r2_1=self.r2[Y1:Y1+y1,X1:X1+x1]
                        self.r2_2=cv.resize(self.r2_1,(Compress,Compress)) 
                        self.r1=cv.resize(self.r1,(Compress,Compress))
                        compare(self.r1,self.r2_2) 
                        print (i,'  ',compare(self.r1, self.r2_2), file=stderr)
                    if compare(self.r1,self.r2_2) <= Coefficient: 
                        print('обьект найден :)', file=stderr) 
#//////////////////////////////////////////////////////////////////////////////
#расчет расположения обьекта на фото            
                        self.X_pix=X1+(y1/2)
                        self.Y_pix=Y1+(x1/2)
                        print('X',self.X_pix,"/",'Y',self.Y_pix, file=stderr)
#//////////////////////////////////////////////////////////////////////////////
#расчет угла поворота  
                        #self.a1=(self.Y_pix)
                        #self.b1=(self.X_pix)
                        #self.a2=(self.x/2)-self.a1
                        #self.b2=(self.y-self.b1)
                        #self.tg_A=(self.b2/self.a2)
                        #print( 'tg',self.tg_A)
                        
                        self.x_degree=int((0+self.X_pix)/2/(self.x/360)) 
                        if self.x_degree >180:
                             self.x_degree=180
                        self.y_degree=int((0+self.Y_pix)/2/(self.y/360)) 
                        
                        break
#//////////////////////////////////////////////////////////////////////////////                    
                if compare(self.r1,self.r2_2) <= Coefficient: 
                    break
            if compare(self.r1,self.r2_2) <= Coefficient:
                break
        if compare(self.r1,self.r2_2) >= Coefficient:
            print('обьект не найден :(', file=stderr)
        return self.x_degree, self.y_degree
    
    def show_object(self):
        #вывести найденное изображение на экран
        try:
            if compare(self.r1,self.r2_2) <= Coefficient:
                cv.imshow('обьект',self.r2_1) 
                cv.waitKey(0) 
                cv.destroyAllWindows()
            elif compare(self.r1,self.r2_2) >= Coefficient: 
                print('не удалось показать изображение :(', file=stderr)
        except AttributeError:
            pass       
        
    def show_diagram_photo(self):
        #вывести изображение в plt
        try:
            print('разрешение -','(',self.x,'/',self.y,')')
            plt.imshow(cv.cvtColor(self.r2, cv.COLOR_BGR2RGB))
        except AttributeError:
            print('не удалось показать диаграмму :(', file=stderr)
                 
    def connect(self,com='com9',serial=9600):
        #подключение к ардуино
        self.com = com # номер ком порта
        self.serial = serial # частота
        try:
            self.arduino = Serial(self.com, self.serial, timeout=2) 
            sleep(1)
            print("Connected to arduino! :)", file=stderr)
            send(3,1,10,20,30)
        except SerialException:
            print("Error connecting to arduino!!! :(", file=stderr)
            
            
    def disconnect(self):
        #отключение от ардуино
        self.arduino.close()
        print ('Disconnected  arduino!', file=stderr)
        
    def moveX(self,x):
        #отправка угла поворота на ардуино по оси X
        try:
            print('градусы X =',x) 
            self.arduino.write(bytes([9,x]))
            sleep(1)
            print('движение по X ', file=stderr)
        except AttributeError:
            print('Arduino:X не отправлен', file=stderr)    
            
    def moveY(self,y):
        #отправка угла поворота на ардуино по оси Y
        try:
            print('градусы Y =',y, file=stderr)
            sleep(1)
            self.arduino.write(bytes([9,y]))
            sleep(1)
            print('движение по Y', file=stderr)
        except AttributeError:
            print ('Arduino:Y не отправлен', file=stderr)
    def send(self, n, c, x, y, z):
        manipulator.arduino.write(b"00%s%s%s%s%s0" % (c, n, x, y, z))
    
    
    

if __name__ == '__main__':
    manipulator=Manipulator()
    while True:
        try:
            command = get('http://127.0.0.1:5000/command').text.split()
            type_command(command,manipulator)
            #x,y = manipulator.search_object(request)
            #manipulator.show_object()
            #manipulator.show_diagram_photo()
            #manipulator.moveX(x)
            #manipulator.moveY(y)
            sleep(1)
        except:
            print("Command not recognized")
            sleep(1)