#include <Stepper.h>

const int stepsPerRevolution = 200;

int get_current_position()
{
  int arr2[61] = {
    10,  44,  79, 114, 148, 183, 234, 
    285, 336, 387, 438, 500, 561, 623, 
    685, 747, 773, 799, 825, 852, 878, 
    886, 893, 901, 908, 916, 922, 927, 
    933, 938, 944, 946, 949, 952, 955, 
    958, 960, 963, 966, 969, 972, 974, 
    976, 978, 980, 983, 986, 989, 993, 
    996,1000,1002,1005,1007,1010,1013,
    1015,1017,1019,1021,1023
  };

  int dx, min_dx, min_i;

  int x=analogRead(A0);
  min_dx = 1023;
  for (int i = 0; i < 61; i++)
  {
    dx = abs(arr2[i] - x);
    if (dx < min_dx) 
    {
      min_dx = dx;
      min_i = i;
    }
  }

  return min_i;

}

Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9);

void setup() 
{
  myStepper.setSpeed(100);
  pinMode( 5, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite( 5, 1);
  digitalWrite(10, 1);
//  analogWrite( 5, 255);
//  analogWrite(10, 255);
}

void loop() 
{
  int goal = 30;

  int steps = goal - get_current_position();

  myStepper.step(steps * (200 / 8));

}

