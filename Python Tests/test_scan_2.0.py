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
def photo():
    cap = cv.VideoCapture(1)
    for i in range(30):
        cap.read()    
    ret, frame = cap.read()
    cv.imwrite('Photo Test/v2.0/test.png', frame)   
    cap.release()   
    cv.imshow    
    r2=cv.imread('Photo Test/v2.0/test.png') # изображение с камеры
    return r2        


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


class Objects() :
    def  __init__ (self,object_,index,x1,y1):
        ''' 
        serch-найти обьект на снимке
        show-вывести на экран найденный объект
        plt_-вывести снимок в plt
        ardu_connect- подключиться к ардуино(COM порт,частота)
        ardu_disconnect- отключиться от ардуино
        ardu_x-отправить на ардуино угол поворота на объект по оси X(команда ардуино)
        ardu_y-отправить на ардуино угол поворота на объект по оси Y(команда ардуино)

        '''
        self.object_=object_ # номер искомого изображеня
        self.index=index# количество видов изображения
        self.x1=x1 # ширина окна сканера
        self.y1=y1 # высота окна сканера
        self.r2=r2
        
        # команды по поиску изображения
    def search(self):
        '''найти объект на снимке'''
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
                        self.r1=r1 # искомое изображение 
                        self.r2_1=r2_1# найденное изображение
                        self.r2_2=r2_2# найденное изображение в 16 на 16
                        self.X_pix=X_pix# коардината центра изображения в пикселях по оси X
                        self.Y_pix=Y_pix# коардината центра изображения в пикселях по оси Y
                        break
                if compare(r1,r2_2) <= coefficient: # если объект найден
                    break
            if compare(r1,r2_2) <= coefficient: # если объект найден                
                break
        if compare(r1,r2_2) >= coefficient:
            print('обьект не найден :(')
            
    def show(self):
        '''вывести найденное изображение на экран'''
        try:
            if compare(self.r1,self.r2_2) <= coefficient:# если изображение найдено
                cv.imshow('обьект',self.r2_1) # выводим найденное изображение
                cv.waitKey(0) 
                cv.destroyAllWindows()
            elif compare(self.r1,self.r2_2) >= coefficient: # изображение не найдено
                print('обьект не найден :(')
        except AttributeError:
            pass 
    def plt_(self):
        '''вывести изображение в plt'''
        try:
            plt.imshow(cv.cvtColor(self.r2, cv.COLOR_BGR2RGB))
        except AttributeError:
            pass 
        
    #команды ардуино  
    def ardu_connect(self,com=3,serial=9600):
        '''подключение к ардуино'''
        self.com=com # номер ком порта
        self.serial=serial # частота
        self.arduino = Serial('COM%s' %self.com, self.serial, timeout=2)
        sleep(1)
        print("Connected to arduino!")
    def ardu_disconnect(self):
        '''отключение от ардуино'''
        self.arduino.close()
        print ('Disconnected to arduino')
    def ardu_x (self,command):
        '''отправка угла поворота на ардуино по оси X'''
        try:
            self.command=command # номер команды ардуино
            X_degree=int((0+self.X_pix)/2/degree_x) # угол поворота камеры по оси X
            if X_degree >180:
                X_degree=180
            print('градусы X =',X_degree) 
            sleep(1)
            self.arduino.write(bytes([command,X_degree]))# отправляем на ардуино угол поворота
            sleep(1)
        except AttributeError:
            pass        
    def ardu_y (self,command):
        '''отправка угла поворота на ардуино по оси Y'''
        try:
            self.command=command # номер команды ардуино
            Y_degree=int((0+self.Y_pix)/2/degree_y) # угол поворота камеры по оси Y
            print('градусы Y =',Y_degree)
            sleep(1)
            self.arduino.write(bytes([command,Y_degree]))# отправляем на ардуино угол поворота
            sleep(1)
        except AttributeError:
            pass 
    
            

objects=Objects(1,1,x1,y1)
objects.ardu_connect()   
r2=photo()
objects.search()
objects.show()
objects.plt_()
objects.ardu_x(9)
objects.ardu_y(9)
objects.ardu_disconnect() 
   












