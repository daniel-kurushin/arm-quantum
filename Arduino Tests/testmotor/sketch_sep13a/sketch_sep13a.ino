#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61


Stepper myStepper1(STEPS_PER_REVOLUTION, 53, 51, 49, 47);
Stepper myStepper2(STEPS_PER_REVOLUTION, 45, 43, 41, 39);

void circle_right()
{
  myStepper2.step(25);
  delay (1500);
  myStepper2.step(-25);
  delay (1500);
}

void kran()
{
  myStepper1.step(25);
  delay(2000);
  myStepper1.step(-25);
  delay(2000);
}

void setup()
{
  Serial.begin(9600);
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
   
  Serial.println("===============================");
}

void loop () 
{
  analogWrite(2,255);
  analogWrite(3,255);
  analogWrite(4,255);
  analogWrite(5,255);
  myStepper2.step(125);
  delay(1000);
  myStepper2.step(-125);
  delay (1000);
  
 myStepper1.step(125);
  delay(1000);
  myStepper1.step(-125);
  delay(1000); 

}


