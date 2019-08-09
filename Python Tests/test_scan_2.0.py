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
object_= 2 # номер искомого изображеня
index= 1 # количество видов изображения
coefficient = 0.17# коэффицент сравнения
x1=100 # ширина окна сканера
y1=160 # высота окна сканера
degree_x = 1.65 # количество пикселей в одном градусе x
degree_y = 2.6 # количество пикселей в одном градусе y


# подключение к ардуино
def ardu():
    arduino = Serial('COM7', 9600, timeout=2)
    sleep(1)
    print("Connected to arduino!")
    arduino.write(bytes([9,90]))# возвращаем в начальное положение
    sleep(1)


# сделать снимок
def photo():
    cap = cv.VideoCapture(1)
    for i in range(30):
        cap.read()    
    ret, frame = cap.read()
    cv.imwrite('test.png', frame)   
    cap.release()   
    cv.imshow    
    R2=cv.imread('test.png') # изображение с камеры
return R2
    
           
# сравнение изображений
def compare(R1, R2_2):
    sum_dif = 0.0
    for y in range(16):
        for x in range (16):
            for channel in range (3):
                p1=int(R1 [y][x][channel])
                p2=int(R2_2 [y][x][channel])
                dif = abs (p1-p2)
                sum_dif +=dif/255
    return sum_dif /(16*16*3)


# найти объект   
def find(x,y,x1,x2,steep,object_,index): 
    for Y1 in range (0,y,step): # цикл по y
        print('конец строки')
        for X1 in range (0,x,step): # цикл по x
            R2_1=R2[Y1:Y1+y1,X1:X1+x1] # вырезаем изображение
            R2_2 = cv.resize(R2_1,(16,16)) # обработка
            for i in range(1,index+1):# сравниваем изображения
                R1=cv.imread('%s.%s.jpg' % ( object_ , i ) )# искомые изображения
                R1=cv.resize(R1,(16,16)) # обработка 
                compare(R1,R2_2) # сравнение
                print (i,'  ',compare(R1, R2_2))
                if compare(R1,R2_2) <= coefficient: # если объект найден
                    print('обьект найден :)')
                    cv.imshow('обьект',R2_1) # выводим найденное изображение
                    cv.waitKey(0) 
                    cv.destroyAllWindows() 
                    X_pix=X1+(y1/2) # находим коардинаты центра изображения 
                    Y_pix=Y1+(x1/2)                   
                    print('X',X_pix,"/",'Y',Y_pix)
                    X_pix=int((0+X_pix)/2/degree_x) # находим угол поворота камеры X
                    if X_pix >180:
                        X_pix=180 
                    print('градусы X =',X_pix)
                    Y_pix=int((0+Y_pix)/2/degree_y) # находим угол поворота камеры X
                    print('градусы Y =',Y_pix) 
                    break
            if compare(R1,R2_2) <= coefficient: # если объект найден
                break
        if compare(R1,R2_2) <= coefficient: # если объект найден
            break
    return R1,R2,R2_2,R2_1,X_pix,Y_pix            

 
 # показать изображение найденного  объекта   
def object1(R2_1,coefficent)
    if compare(R1,R2_2) <= coefficient:# если изображение найдено     
        cv.imshow('обьект',R2_1) # выводим найденное изображение
        cv.waitKey(0) 
        cv.destroyAllWindows() 
    else:
        print('объект не найден :(')


# повернуть манипулятор на объект по X
def ardu_X(X_pix):
     arduino.write(bytes([9,X_pix]))# отправляем на ардуино угол поворота
     sleep(0.5) 
        

find()

if compare(R1,R2_2) >= coefficient: # изображение не найдено
   print('обьект не найден :(') 
elif compare(R1,R2_2) <= coefficient:# если изображение найдено
    cv.imshow('обьект',R2_1) # выводим найденное изображение
    cv.waitKey(0) 
    cv.destroyAllWindows()  
    X_pix=int((0+X_pix)/2/degree_x) # находим угол поворота камеры X
    if X_pix >180:
        X_pix=180
    print('градусы X =',X_pix) 
    Y_pix=int((0+Y_pix)/2/degree_y) # находим угол поворота камеры Y
    print('градусы Y =',Y_pix) 
    
plt.imshow(cv.cvtColor(R2, cv.COLOR_BGR2RGB)) # выводим изображение в plt     
    
    



arduino.close()   











