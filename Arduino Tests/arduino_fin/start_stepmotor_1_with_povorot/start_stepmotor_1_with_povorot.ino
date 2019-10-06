#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

#define s_begin Serial.begin
#define s_print Serial.print
#define s_is_av Serial.available
#define s_read  Serial.read
#define s_to_int Serial.parseInt

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания

void set()
{
  analogWrite(8, 255);
  analogWrite(9, 255);

}


void Stepper1_stop()
{
  digitalWrite(44, 0);
  digitalWrite(42, 0);
  digitalWrite(40, 0);
  digitalWrite(38, 0);
}

void s_println(int n_args, ...)
{
  va_list ap;
  va_start(ap, n_args);
  for (int i = 1; i < n_args; i++)
  {
    s_print(va_arg(ap, int));
    s_print(", ");
  }
  s_print(va_arg(ap, int));
  s_print("\n");
  va_end(ap);
}


void setup()
{
  
  Serial.begin(9600);
  set();
}

void loop()
{
  int dg, pot;
  
  if (s_is_av())
  {
    x = s_to_int();
    if (t++ % 2 == 0)
    {
      num_motor = x;
    }
    else
    {
      num_step = x;
      s_println(2, 666, dg);
      t = 0;
    }
  }
  // 90 - 65, 0 - 241,-90 - 435
  pot = 259 - (97* dg)/45;
  if ( pot > analogRead(A0)
  {
    while (pot < analogRead(A0))
    {
      myStepper1.step(-25);
    }
  }
  else 
  {
    while(pot > analogRead(A0))
    {
      myStepper1.step(25);
    }
  }
  Stepper1_stop();
  
  delay (100);
}
