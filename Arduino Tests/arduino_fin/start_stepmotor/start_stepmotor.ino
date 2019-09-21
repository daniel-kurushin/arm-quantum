#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

#define fan1 37 //вентилятор верхний
#define fan2 35 //вентилятор нижний
#define vacuum 33 //пылесос

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46); // большой двигатель вверх
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39); // двигатель верхний пред кусь
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47); // двигатель верхний на кусь

int num_motor = 0;
int num_step = 0;

void set()
{
  analogWrite(2, 255);
  analogWrite(3, 255);
  analogWrite(4, 255);
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);

  digitalWrite(fan1,1);
  digitalWrite(fan2,1);
}

void setup()
{
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  myStepper3.setSpeed(60);
  myStepper4.setSpeed(60);
  
  Serial.begin(9600);
}


void loop()
{
   set();
   
   if (Serial.available() > 0)
   {
     num_motor = Serial.read();
     num_step = Serial.read();
     //Serial.println("motor is", num_motor, "step is:", num_step);
   }
   switch(num_motor)
   {
     case 1:
     myStepper1.step(num_step);
     delay(500);
     break;
     
     case 2:
     myStepper2.step(num_step);
     delay(500);
     break;
     
     case 3:
     myStepper3.step(num_step);
     delay(500);
     break;
     
     case 4:
     myStepper4.step(num_step);
     delay(500);
     break;
     
   }
   /*
   myStepper1.step(250);
   delay(500);
   myStepper1.step(-250);
   delay(500);
   
   myStepper2.step(250);
   delay(500);
   myStepper2.step(-250);
   delay(500);
   
   myStepper3.step(250);
   delay(500);
   myStepper3.step(-250);
   delay(500);
   
   myStepper4.step(250);
   delay(500);
   myStepper4.step(-250);
   delay(500);
   */
}
