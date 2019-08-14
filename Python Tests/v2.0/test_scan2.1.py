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


Coefficient = 0.11# коэффицент сравнения
Step=10# шаг в пикселях
Compress=16 # сжатие изображения 


# сделать снимок
def photo():
    cap = cv.VideoCapture(1)
    for i in range(30):
        cap.read()    
    ret, frame = cap.read()
    cv.imwrite('test.png', frame)   
    cap.release()   
    cv.imshow    
    r2=cv.imread('test.png') 
    return r2        


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


class Manipulator():
    def  __init__ (self):
        #print(time, self, file=stderr)
        self.r2=photo()
        im2 = Image.open('test.png')
        (self.x,self.y) = im2.size
        
    def search_object(self,object_serch):
        '''найти объект на снимке'''
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
                        self.X_pix=X1+(y1/2)
                        self.Y_pix=Y1+(x1/2)
                        print('X',self.X_pix,"/",'Y',self.Y_pix, file=stderr)
                        self.x_degree=int((0+self.X_pix)/2/(self.x/360)) 
                        if self.x_degree >180:
                            self.x_degree=180
                        self.y_degree=int((0+self.Y_pix)/2/(self.y/360)) 
                        break
                if compare(self.r1,self.r2_2) <= Coefficient: 
                    break
            if compare(self.r1,self.r2_2) <= Coefficient:
                break
        if compare(self.r1,self.r2_2) >= Coefficient:
            print('обьект не найден :(', file=stderr)
        return self.x_degree, self.y_degree 
    def show_object(self):
        '''вывести найденное изображение на экран'''
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
        '''вывести изображение в plt'''
        try:
            plt.imshow(cv.cvtColor(self.r2, cv.COLOR_BGR2RGB))
        except AttributeError:
            print('не удалось показать диаграмму :(', file=stderr)
                 
    def connect(self,com=7,serial=9600):
        '''подключение к ардуино'''
        self.com = com # номер ком порта
        self.serial = serial # частота
        try:
            self.arduino = Serial('COM%s' %self.com, self.serial, timeout=2)
            sleep(1)
            print("Connected to arduino!", file=stderr)
        except SerialException:
            print("Error connecting to arduino!", file=stderr)
            
            
    def disconnect(self):
        '''отключение от ардуино'''
        self.arduino.close()
        print ('Disconnected  arduino', file=stderr)
        
    def moveX(self,x):
        '''отправка угла поворота на ардуино по оси X'''
        try:
            print('градусы X =',x) 
            sleep(1)
            self.arduino.write(bytes([9,x]))
            sleep(1)
            print('движение по X ', file=stderr)
        except AttributeError:
            print('Arduino:нет изображения', file=stderr)    
            
    def moveY(self,y):
        '''отправка угла поворота на ардуино по оси Y'''
        try:
            print('градусы Y =',y, file=stderr)
            sleep(1)
            self.arduino.write(bytes([9,y]))
            sleep(1)
            print('движение по Y', file=stderr)
        except AttributeError:
            print ('Arduino:нет изображения', file=stderr)
    

if __name__ == '__main__':
    manipulator=Manipulator()
    manipulator.connect()
    x,y = manipulator.search_object('bottle')
    manipulator.show_object()
    manipulator.show_diagram_photo()
    manipulator.moveX(x)
    manipulator.moveY(y)
    manipulator.disconnect()
    
      
   
    