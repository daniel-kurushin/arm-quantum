#include <Stepper.h>

#define POT A0
#define INIT 0
#define GO_LEFT 1
#define POISK 2
#define WORK 3
#define MIN 1
#define SPED 2
#define READY 4
#define VALUE_RECEIVED 5
#define GO 6
#define VALUE_REACHED 7
#define GO_RIGHT 8

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

Stepper myStepper(STEPS_PER_REVOLUTION, 2, 4, 5, 7);


int state, work_state = INIT;
int init_state = INIT;
int value, current_value, stp = 0;  

int num[RESOLUTION];

int getPotValue(int Ax)
{
  return analogRead(Ax)/2;
}



bool can_go_left()
{

  int x0 = getPotValue(POT);
  myStepper.step(-50);
  int x1 = getPotValue(POT);
  Serial.print("<- ");
  Serial.print(x0);
  Serial.print(" ");
  Serial.println(x1);
  return x0 >= x1; 
}

bool can_go_right()
{
  int x0 = getPotValue(POT);
  myStepper.step(50);
  int x1 = getPotValue(POT);
  Serial.print("-> ");
  Serial.print(x0);
  Serial.print(" ");
  Serial.println(x1);
  return x0 <= x1;
}

void poisk()
{
  for (int i = 0; i < 61; i++)
  {
    num[i] = analogRead(A0);
    myStepper.step(25);
  }
  Serial.println("=============================");
  delay (500);
  for (int i = 0; i < 61; i++)
  {
    Serial.println(num[i]);
  }
  delay (1000);
}

void work()
{
  int dx, min_dx, min_i;
  int a = 0;
  int c = analogRead(A0);
  Serial.println("Calibrate is done. Ready to take valyes");
  switch (work_state)
  {
  case INIT:
    if (Serial.available() > 0)
    {
      a = Serial.read();
      Serial.println(a);
      work_state = MIN;
    }

    break;
  case MIN:

    min_dx = 1023;
    for ( int i = 0; i<61; i++)
    {
      dx = abs(num[i] - c);
      if (dx< min_dx) 
      {
        min_dx = dx;
        min_i = i;
      }
    }
    work_state = SPED;
    break; 
  case SPED:
    if  ( a == min_i)
    {
      myStepper.step(0);
    }
    else
    {
      myStepper.step(-25);
    }
    work_state = INIT;
    break;
  }

}


void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(60);
  Serial.println("===============================");
}

int i;

void loop()
{
  analogWrite(3, 255);
  analogWrite(6, 255);
  switch (state)
  {
  case INIT:

    switch (init_state)
    {
    case INIT:
      init_state = GO_LEFT;
      break;
    case GO_LEFT:
      if (not can_go_left()) 
      {
        i = 0;        
        init_state = POISK;
      }
      break;
    case POISK:
      num[i++] = analogRead(A0);
      myStepper.step(25);
      if (i > 61) 
      {
        init_state = READY;
      }

      break;
    case READY:
      state = WORK;
      break;
    }
  case WORK:
    switch (work_state)
    {
    case READY:
      if (Serial.available() > 0)
      {
        value = Serial.read();
        state = VALUE_RECEIVED;
      }
      break;
    case VALUE_RECEIVED:
      if (current_value < value)
      {
        work_state = GO_LEFT;
      } 
      else if (current_value > value)
      {
        work_state = GO_RIGHT;
      }
      else 
      {
        work_state = VALUE_REACHED;
      }
      break;
    case GO_LEFT:
      stp = 25;
      break;
    case GO_RIGHT:
      stp = -25;
      break;
    case GO:
      myStepper.step(stp);
      if (value == current_value)
      {
        work_state = VALUE_REACHED;
      }
      break;
      case VALUE_REACHED:
      work_state = READY;
      break;
    }
    break;
  }
}











