#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200

Servo servo; // серво для кусь

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46); // большой двигатель вверх
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39); // двигатель верхний пред кусь
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47); // двигатель верхний на кусь

int device = 0;
int command = 0;
int value = 0;

void setup()
{
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  myStepper3.setSpeed(60);
  myStepper4.setSpeed(60);

  servo.attach(10);

  Serial.begin(9600);
}


void loop()
{ 
  if(Serial.available())
  {  

    device = Serial.parseInt();
    Serial.println(device);
    switch(device)
    {
    case 0://двигатель в опорном
      command = Serial.parseInt();
      switch(command)
      {
      case 0://диагностика
        break; 
      case 1://разжатие
        value = Serial.parseInt();
        myStepper1.step(value);
        break; 
      case 2://сжатие
        value = Serial.parseInt();
        myStepper1.step(-value);
        break; 
      case 3://стоп
        digitalWrite(44, 0);
        digitalWrite(42, 0);
        digitalWrite(40, 0);
        digitalWrite(38, 0); 
        break; 
      case 4://удержание
        digitalWrite(44, 1);
        digitalWrite(42, 1);
        digitalWrite(40, 1);
        digitalWrite(38, 1);   
        break; 
      }
      break;
////////////////////////////////////////////////////////////////
      case 1://двигатель стрела
      command = Serial.parseInt();
      switch(command)
      {
      case 0://диагностика
        break; 
      case 1://разжатие
        value = Serial.parseInt();
        myStepper1.step(value);
        break; 
      case 2://сжатие
        value = Serial.parseInt();
        myStepper1.step(-value);
        break; 
      case 3://стоп
        digitalWrite(52, 0);
        digitalWrite(50, 0);
        digitalWrite(48, 0);
        digitalWrite(46, 0); 
        break; 
      case 4://удержание
        digitalWrite(52, 1);
        digitalWrite(50, 1);
        digitalWrite(48, 1);
        digitalWrite(46, 1);   
        break; 
      }
      break;
////////////////////////////////////////////////////////////////      
      case 2://двигатель рукоять
      command = Serial.parseInt();
      switch(command)
      {
      case 0://диагностика
        break; 
      case 1://разжатие
        value = Serial.parseInt();
        myStepper1.step(value);
        break; 
      case 2://сжатие
        value = Serial.parseInt();
        myStepper1.step(-value);
        break; 
      case 3://стоп
        digitalWrite(45, 0);
        digitalWrite(43, 0);
        digitalWrite(41, 0);
        digitalWrite(39, 0); 
        break; 
      case 4://удержание
        digitalWrite(45, 1);
        digitalWrite(43, 1);
        digitalWrite(41, 1);
        digitalWrite(39, 1);   
        break; 
      }
      break;
////////////////////////////////////////////////////////////////
      case 3://двигатель схвата
      command = Serial.parseInt();
      Serial.println(command);
      switch(command)
      {
      case 0://диагностика
        break; 
      case 1://разжатие
        value = Serial.parseInt();
        Serial.println(value);
        myStepper1.step(value);
        break; 
      case 2://сжатие
        value = Serial.parseInt();
        myStepper1.step(-value);
        break; 
      case 3://стоп
        digitalWrite(53, 0);
        digitalWrite(51, 0);
        digitalWrite(49, 0);
        digitalWrite(47, 0); 
        break; 
      case 4://удержание
        digitalWrite(53, 1);
        digitalWrite(51, 1);
        digitalWrite(49, 1);
        digitalWrite(47, 1);   
        break; 
      }
      break;
////////////////////////////////////////////////////////////////
    case 4://серва
      command = Serial.parseInt();
      Serial.println(command);
      switch(command)
      {
      case 0://диагностика
        break; 
      case 1://разжатие
        
        myStepper1.step(value);
        break; 
      case 2://сжатие
        value = Serial.parseInt();
        servo.write(value);
        break; 
      case 3://стоп
        
        break; 
      case 4://удержание
         
        break; 
      }
      break;
    default:
      Serial.write("err");
      break;
    }
  }
}



