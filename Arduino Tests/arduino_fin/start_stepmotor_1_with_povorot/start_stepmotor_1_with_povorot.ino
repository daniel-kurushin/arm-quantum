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


int dg, pot, fff;
int V, dx1, dx2, dx, x, x0, x1;
const int DX = 30;
void setup()
{

  fff = 0;
  Serial.begin(9600);
  myStepper1.setSpeed(200);
  set();
}

int x_to_pot(int x)
{
  return 259 - (97 * x) / 45;
}

int pot_to_x(int pot)
{
  return (45 * (259 - pot)) / 97;
}

void loop()
{
  if (s_is_av())
  {
    int a = s_to_int();
    if (a != 0)
    {
      x1 = a;
      x0 = pot_to_x(analogRead(A0));
      fff = 1;
    }
  }
  if (fff)
  {
    x = pot_to_x(analogRead(A0));
    dx1 = abs(x - x0);
    dx2 = abs(x - x1);
    if (dx1 < DX or dx2 < DX)
    {
      dx = min(dx1, dx2);
      myStepper1.setSpeed(40 + 5 * dx);
    }
    else
    {
      myStepper1.setSpeed(200);
    }

    s_println(6, x, x0, x1, dx1, dx2, dx);
    if (x1 > x + 2)
    {
      myStepper1.step( 20);
    }
    else if (x1 < x - 2)
    {
      myStepper1.step(-20);
    }
    else
    {
      Stepper1_stop();
      fff = 0;
      delay(100);
    }
  }
}
