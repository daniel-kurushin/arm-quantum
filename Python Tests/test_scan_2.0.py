# -*- coding: utf-8 -*-
"""
Created on Wed Aug  7 22:05:30 2019

@author: korot
"""


from serial import Serial
from time import sleep
import cv2 as cv
from matplotlib import pyplot as plt


x=640 # ширина в пикселях 
y=480 # высота в пикселях
step=10# шаг в пикселях
object_= 1 # номер искомого изображеня
index= 1 # количество видов изображения
coefficient = 0.18# коэффицент сравнения
x1=140 # ширина окна сканера
y1=160 # высота окна сканера
degree_x = 1.65 # количество пикселей в одном градусе x
degree_y = 2.6 # количество пикселей в одном градусе y
com=3
serial=9600 # частота arduino Serial

C=16 # сжатие изображения 


# сделать снимок
cap = cv.VideoCapture(1)
for i in range(30):
    cap.read()    
ret, frame = cap.read()
cv.imwrite('Photo Test/v2.0/test.png', frame)   
cap.release()   
cv.imshow    
r2=cv.imread('Photo Test/v2.0/test.png') # изображение с камеры


class Arduino():
    '''com-номер ком порта 
     serial-частота
     X_pix-угол по оси X 
     command-номер команды
     degree_x-количество пикселей в одном градусе x
     degree_y-количество пикселей в одном градусе y'''
     
    def  __init__ (self,com=3,serial=9600,):
        self.com=com
        self.serial=serial
    def connect(self):
        '''подключение к ардуино'''
        self.arduino = Serial('COM%s' %self.com, self.serial, timeout=2)
        sleep(1)
        print("Connected to arduino!")
    def disconnect(self):
        '''отключение от ардуино'''
        self.arduino.close()
        print ('Disconnected to arduino')
    def x (self,command,X_pix,degree_x):
        '''отправка угла поворота на ардуино по оси X'''
        self.degree_x=degree_x
        self.command=command
        self.X_pix=X_pix
        X_pix=int((0+X_pix)/2/degree_x) # находим угол поворота камеры X
        if X_pix >180:
            X_pix=180
        print('градусы X =',X_pix) 
        sleep(1)
        self.arduino.write(bytes([command,X_pix]))# отправляем на ардуино угол поворота
        sleep(1)
    def y (self,command,Y_pix,degree_y):
        '''отправка угла поворота на ардуино по оси Y'''
        self.degree_y=degree_y
        self.command=command
        self.Y_pix=Y_pix
        Y_pix=int((0+Y_pix)/2/degree_y) # находим угол поворота камеры Y
        print('градусы Y =',Y_pix)
        sleep(1)
        self.arduino.write(bytes([command,Y_pix]))# отправляем на ардуино угол поворота
        sleep(1)
        
        
# сравнение        
def compare(r1, r2_2):
    sum_dif = 0.0
    for y in range(C):
        for x in range (C):
            for channel in range (3):
                p1=int(r1 [y][x][channel])
                p2=int(r2_2 [y][x][channel])
                dif = abs (p1-p2)
                sum_dif +=dif/255
    return sum_dif /(16*16*3)


arduino=Arduino(com,serial)
arduino.connect()   


# найти объект 
for Y1 in range (0,y,step): # цикл по y
    print('конец строки')
    for X1 in range (0,x,step): # цикл по x       
        r2_1=r2[Y1:Y1+y1,X1:X1+x1] # вырезаем изображение
        r2_2=cv.resize(r2_1,(C,C)) # обработка
        for i in range(1,index+1):# сравниваем изображения
            r1=cv.imread('Photo Test/v2.0/%s.%s.jpg' % ( object_ , i ) )# искомые изображения
            r1=cv.resize(r1,(C,C)) # обработка 
            compare(r1,r2_2) # сравнение
            print (i,'  ',compare(r1, r2_2))
            if compare(r1,r2_2) <= coefficient: # если объект найден
                print('обьект найден :)')             
                X_pix=X1+(y1/2) # находим коардинаты центра изображения 
                Y_pix=Y1+(x1/2)
                print('X',X_pix,"/",'Y',Y_pix)                   
                break
        if compare(r1,r2_2) <= coefficient: # если объект найден
            break
    if compare(r1,r2_2) <= coefficient: # если объект найден
        break           
 

if compare(r1,r2_2) >= coefficient: # изображение не найдено
   print('обьект не найден :(') 
elif compare(r1,r2_2) <= coefficient:# если изображение найдено
    cv.imshow('обьект',r2_1) # выводим найденное изображение
    cv.waitKey(0) 
    cv.destroyAllWindows()  
    arduino.x(9,X_pix,degree_x)# отправляем на ардуино команду
    arduino.y(9,Y_pix,degree_y)# отправляем на ардуино команду 
plt.imshow(cv.cvtColor(r2, cv.COLOR_BGR2RGB)) # выводим изображение в plt
arduino.disconnect()   












