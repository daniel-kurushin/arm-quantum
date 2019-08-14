# -*- coding: utf-8 -*-
"""
Created on Mon Jul 29 17:37:08 2019

@author: korot
"""
from serial import Serial, SerialException
import cv2 as cv
from matplotlib import pyplot as plt

R2=cv.imread('Photo Test/v1.0/11.jpg') # искомое изображение
R3=cv.imread('Photo Test/v1.0/test4.jpg') # изображение на котором ищем


pixel_y1 = 0       
pixel_y2 = 480     # ширина изображения в пикселях
pixel_y3 = 480
     
pixel_x1 = 3000    # длинна изображения в пикселях 
step = 15          # отступ в пикселях
pas = 3            # количество шагов по Y 

R2=cv.resize(R2,(16,16))

def compare(R2, R3_2):#сравнение 
    sum_dif = 0.0
    for y in range(16):
        for x in range (16):
            for channel in range (3):
                p1=int(R2 [y][x][channel])
                p2=int(R3_2 [y][x][channel])
                dif = abs (p1-p2)
                sum_dif +=dif/255
    return sum_dif /(16*16*3)
'''
for i in range(100): # проверка COM порта 
    try:
        ser=Serial('COM%s'  % i ,9600,timeout=1)
        ser.sleep(1)
        ser.write(0)       
        if ser.read ():
            break
    except SerialException:
        print(i)
        pass
    except Exception as e:
        raise e
'''       


    
for counter in range(pas):#количество шагов по y
    for pixel_x in range(0,pixel_x1,step):#количество шагов по x     
        R3_1 = R3[pixel_y1:pixel_y2, (0+pixel_x):(pixel_y3+pixel_x)] # вырезаем изображение
        R3_2 = cv.resize(R3_1,(16,16)) # обработка и сравнение
        compare(R2,R3_2)
        print (compare(R2,R3_2))
        if compare(R2,R3_2) <= 0.09:
            break
        elif pixel_x >= pixel_x1-100: #длина строки
            print('конец строки') # увеличиваем Y
            pixel_y1+=480
            pixel_y2+=480
            break        
    if compare(R2,R3_2) <= 0.09: # изображение найдено
        print('обьект найден :)')
        X_pix=pixel_x+240         # находим коардинаты центра изображения 
        Y_pix=(counter+1)*480-240
        
        print('X',X_pix,"/",'Y',Y_pix)
        cv.line(R3, (pixel_x+240, (counter+1)*480-240), (0, 0), (0, 0, 255), 10) # обводим изображение 
        cv.rectangle(R3,(pixel_x,(480*(counter+1)-240)+240),(pixel_x+480,(480*(counter+1)-240)-240),(0, 0, 255), 10)   
        break
    
            
if compare(R2,R3_2) >= 0.09: # изображение не найдено
   print('обьект не найден :(')     
elif compare(R2,R3_2) <= 0.09:# если изображение найдено  
    plt.imshow(cv.cvtColor(R3, cv.COLOR_BGR2RGB))    
    cv.imshow('обьект',R3_1)   
    cv.waitKey(0) 
    cv.destroyAllWindows()
'''    
X_pix=int((X_pix-1500)/16) # находим угол поворота камеры
print('градусы =',X_pix)  
ser.write(bytes[9,X_pix])# отправляем на ардуино
ser.sleep(1)
ser.close() 
ser.sleep(1)    
'''
     
     
     

    
    
    

