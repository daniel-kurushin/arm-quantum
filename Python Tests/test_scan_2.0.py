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
coefficient = 0.17# коэффицент сравнения
x1=130 # ширина окна сканера
y1=160 # высота окна сканера
degree_x = 1.65 # количество пикселей в одном градусе x
degree_y = 2.6 # количество пикселей в одном градусе y


C=16 # сжатие изображения 
S=9600 # частота arduino Serial


# сделать снимок
cap = cv.VideoCapture(1)
for i in range(30):
    cap.read()    
ret, frame = cap.read()
cv.imwrite('Photo Test/v2.0/test.png', frame)   
cap.release()   
cv.imshow    
r2=cv.imread('Photo Test/v2.0/test.png') # изображение с камеры


# подключение к ардуино
arduino = Serial('COM3', S, timeout=2)
sleep(1)
arduino.write(bytes([9,90]))# отправляем на ардуино угол поворота
sleep(1)
print("Connected to arduino!")


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


# найти объект   
for Y1 in range (0,y,step): # цикл по y
    print('конец строки')
    for X1 in range (0,x,step): # цикл по x       
        r2_1=r2[Y1:Y1+y1,X1:X1+x1] # вырезаем изображение
        r2_2 = cv.resize(r2_1,(C,C)) # обработка
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
    X_pix=int((0+X_pix)/2/degree_x) # находим угол поворота камеры X
    if X_pix >180:
        X_pix=180
    print('градусы X =',X_pix) 
    Y_pix=int((0+Y_pix)/2/degree_y) # находим угол поворота камеры Y
    print('градусы Y =',Y_pix)
    sleep(1)
    arduino.write(bytes([9,X_pix]))# отправляем на ардуино угол поворота
    sleep(1)       
plt.imshow(cv.cvtColor(r2, cv.COLOR_BGR2RGB)) # выводим изображение в plt
arduino.close()   












