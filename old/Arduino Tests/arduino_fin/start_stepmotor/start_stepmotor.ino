#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

#define FAN1 37 //вентилятор верхний
#define LIGHT 35 //подсветка
#define VACUUM 33 //пылесос
#define SIRENA 13

#define s_begin Serial.begin
#define s_print Serial.print
#define s_is_av Serial.available
#define s_read  Serial.read
#define s_to_int Serial.parseInt

Servo servo; // серво для кусь

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46); // большой двигатель вверх
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39); // двигатель верхний пред кусь
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47); // двигатель верхний на кусь


int num_motor = 0;
int num_step = 0;
int t = 0;
int x = 0;

void Stepper1_stop()
{
  digitalWrite(44, 0);
  digitalWrite(42, 0);
  digitalWrite(40, 0);
  digitalWrite(38, 0);
}
void Stepper2_stop()
{
  digitalWrite(52, 0);
  digitalWrite(50, 0);
  digitalWrite(48, 0);
  digitalWrite(46, 0);
}
void Stepper3_stop()
{
  digitalWrite(45, 0);
  digitalWrite(43, 0);
  digitalWrite(41, 0);
  digitalWrite(39, 0);
}
void Stepper4_stop()
{
  digitalWrite(53, 0);
  digitalWrite(51, 0);
  digitalWrite(49, 0);
  digitalWrite(47, 0);
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

  digitalWrite(FAN1, 1);
  digitalWrite(LIGHT, 1);
  digitalWrite(VACUUM, 1);
}

void setup()
{
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  myStepper3.setSpeed(60);
  myStepper4.setSpeed(60);

  s_begin(9600);
  servo.attach(10);
}

void loop()
{
  set();

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
      s_println(3, 666, num_motor, num_step);
      t = 0;
    }
  }

  switch(num_motor)
  {
  case 1:
    myStepper1.step(num_step);
    num_step = 0;
    Stepper1_stop();
    delay(500);
    break;

  case 2:
    myStepper2.step(num_step);
    Stepper2_stop();
    num_step = 0;
    delay(500);
    break;

  case 3:
    myStepper3.step(num_step);
    Stepper3_stop();
    num_step = 0;
    delay(500);
    break;

  case 4:
    myStepper4.step(num_step);
    Stepper4_stop();
    num_step = 0;
    delay(500);
    break;

  case 5:
    servo.write(0);
    delay(2000);

    num_step = 0;
    break;
  case 6:
    servo.write(90);
    delay(5000);
    num_step = 0;
    break;
  } 

}


