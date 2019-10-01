#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

#define FAN1 37 //вентилятор верхний
#define LIGHT 35 //подсветка
#define VACUUM 33 //пылесос
#define SIRENA 13

#define INIT 0
#define WORK 1

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

int R1[] = {
  190, 197, 204, 211, 218, 225, 232, 239, 246, 253, 260};
int X1[] = {
  319, 305, 289, 269, 247, 221, 192, 152, 118, 71, 14};
int Y1[] = {
  180, 207, 234, 260, 226, 312, 336, 360, 381, 400, 414};

int R2[] = {
  225, 238, 251, 264, 277, 290, 303, 316, 329, 342, 355};
int X2[] = {
  69, 149, 190, 231, 265, 294, 320, 343, 363, 380, 394};  
int Y2[] = {
  -416, -394, -376, -353, -328, -301, -274, -244, -214, -182, -142};

int R3[] = {
  200, 207, 214, 221, 228, 235, 242, 249, 256, 263, 270};
int X3[] = {
  86, 100, 108, 113, 116, 119, 120, 120, 119, 117, 115};  
int Y3[] = {
  83, 66,  52,  40,  28,  17,  6,   -5, -15, -25, -35};

int minr1, minr2, minr3;
int a =0;
int state = 0;
int num_motor = 0;
int num_step = 0;
int t = 0;
int r1, r2, r3, r4;
const int k = 25;

void reverse(int x, int y)
{
  int mind = 10000;
  for(int i = 0; i < 11; i++)
  {
    for(int j = 0; j<11; j++)
    {
      for(int k = 0; k<11; k++)
      {
        int x0 = X1[i] + X2[j] + X3[k];
        int y0 = Y1[i] + Y2[j] + Y3[k];
        float d = sqrt(pow(x0 - x, 2) + pow(y0 - y, 2));

        if(d<mind)
        {
          mind = d;
          minr1 = R1[i];
          minr2 = R2[j];
          minr3 = R3[k];
        }
      }
    }
  }
}

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

void Stepper1_go(int pos)
{

  if (pos != r2)
  {
    myStepper1.step((pos-r2)*k);
  }
  Stepper1_stop();
  r1 = pos;
}

void Stepper2_go(int pos)
{
  if (pos < 190) pos = 190;
  if (pos > 260) pos = 260; 
  if (pos != r2)
  {
    myStepper2.step(-(pos-r2)*k);
  }
  Stepper2_stop();
  r2 = pos;
}

void Stepper3_go(int pos)
{
  if (pos < 225) pos = 225;
  if (pos > 355) pos = 355; 
  if (pos != r3)
  {
    myStepper3.step(-(pos-r3)*k);
  }
  Stepper3_stop();
  r3 = pos;
}

void Stepper4_go(int pos)
{
  if (pos < 200) pos = 200;
  if (pos > 270) pos = 270; 
  if (pos != r4)
  {
    myStepper4.step((pos-r4)*k);
  }
  Stepper4_stop();
  r4 = pos;
}

void initialization()
{
  r2 = 260;
  myStepper2.step(-1500);
  Stepper2_go(253);

  r3 = 355; 
  myStepper3.step(-3300);
  Stepper3_go(342);

  r4 = 270;
  myStepper4.step(1700);
  Stepper4_go(263);

  servo.write(0);


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

  switch (state)
  {
  case INIT:
    initialization();
    state = WORK;
    break;

  case WORK:
    if (s_is_av())
    {
      int x, y, a;
      a = s_to_int();
      if (t++ % 2 == 0)
      {
        x = a;
      }
      else
      {
        y = a;
        s_println(3, 666, x, y);
        reverse(x,y);
        Stepper3_go(355);
        Stepper2_go(minr1);
        Stepper3_go(minr2);
        Stepper4_go(minr3); 
        t = 0;
      }
    }

    /* switch(num_motor)
    {
    case 1:
      Stepper1_go(dis);
      dis = 0;
      delay(500);
      break;

    case 2:
      Stepper1_go(dis);
      dis = 0;
      delay(500);
      break;

    case 3:
      Stepper3_go(dis);
      dis = 0;
      delay(500);
      break;

    case 4:
      Stepper4_go(dis);
      dis = 0;
      delay(500);
      break;

    case 5:
      servo.write(0);
      delay(2000);
      num_step = 0;
      break;
    case 6:
      servo.write(90);
      delay(2000);
      num_step = 0;
      break;
    } 
    break; */
  } 
}





