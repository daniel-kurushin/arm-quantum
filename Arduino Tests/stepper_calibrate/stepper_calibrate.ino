#include <Stepper.h>

#define POT A0
#define INIT 0
#define GO_LEFT 1
#define POISK 2
#define WORK 3

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

Stepper myStepper(STEPS_PER_REVOLUTION, 2, 4, 5, 7);


int state = INIT;
int init_state = INIT;

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
  
  a = Serial.read();
  
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
  if ( a = min_i)
  {
    myStepper.step(-25);
  }
  else
  {
    myStepper.step(0);
  }
  
}


void setup()
{
  Serial.begin(9600);
  myStepper.setSpeed(60);
  Serial.println("===============================");
}

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
      if (not can_go_left()) init_state = POISK;
      break;
    case POISK:
      poisk();
      state = WORK;
      delay (50000);
      break;
    }
    
    break;
  case WORK:
    ;
    break;
  }
}





