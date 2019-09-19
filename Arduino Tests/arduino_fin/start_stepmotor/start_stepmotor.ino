#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

#define fan1 37 //вентилятор верхний
#define fan2 35 //вентилятор нижний
#define vacuum 33 //пылесос

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38);
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46);
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39);
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47);

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
}


void loop()
{
   set();
   
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
   /*
   myStepper4.step(250);
   delay(500);
   myStepper4.step(-250);
   delay(500);
   */
}




