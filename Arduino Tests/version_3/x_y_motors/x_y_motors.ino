#include <Stepper.h>
#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

Stepper z_stepper(STEPS_PER_REVOLUTION, 44, 42, 40, 38);
Stepper stepper_1(STEPS_PER_REVOLUTION, 52, 50, 48, 46);
Stepper stepper_2(STEPS_PER_REVOLUTION, 45, 43, 41, 39);
Stepper stepper_3(STEPS_PER_REVOLUTION, 53, 51, 49, 47);

float z_old_pos = 0;

float old_pos_1 = 0;
float old_pos_2 = 0;
float old_pos_3 = 0;

float meazure_1 = 0;
float meazure_2 = 0;
float meazure_3 = 0;

float z_measure()
{
  float r = 0;
  for (int i = 0; i < 10; i++)
  {
    r += analogRead(A0);
  }
  return r * 0.0450366 - 114.753273;
}

void z_stepper_stop()
{
  digitalWrite(44, 0);
  digitalWrite(42, 0);
  digitalWrite(40, 0);
  digitalWrite(38, 0);
}

void stepper1_stop()
{
  digitalWrite(52, 0);
  digitalWrite(50, 0);
  digitalWrite(48, 0);
  digitalWrite(46, 0);
}

void z_stepper_step(int steps)
{
  Serial.println(steps);
  delay(100);
}

void z_stepper_setSpeed(int steps, int a, int b)
{
  Serial.print(steps);
  Serial.print(" ");
  Serial.print(a);
  Serial.print(" ");
  Serial.println(b);
  delay(100);
}

void stepper1_step(int steps)
{
  Serial.println(steps);
  delay(100);
}

void stepper1_setSpeed(int steps, int a, int b, int c, int d)
{
  Serial.print(steps);
  Serial.print(" ");
  Serial.print(a);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.print(c);
  Serial.print(" ");
  Serial.println(d);
  delay(100);
}

int z_stepper_go(float target_pos)
{
  float pos = z_measure();
  float delta_a = target_pos - pos;
  float delta_b = z_old_pos - pos;
  int dz = (delta_a < -1) ? 1 : (delta_a > 1) ? -1 : 0;
  if (dz)
  {
    uint8_t spd = min(60, max(20, min(abs(delta_a) * 2, abs(delta_b) * 2)));
    //        z_stepper_setSpeed(spd, delta_a, delta_b);
    z_stepper.setSpeed(spd);
    //        z_stepper_step(dz * 25);
    z_stepper.step(dz * 25);

  }
  else
  {
    z_stepper_stop();
    z_old_pos = target_pos;
  }
  return dz;
}

int stepper1_go(float target_pos)
{
  float pos = meazure_1;
  float delta_a = target_pos - pos;
  float delta_b = old_pos_1 - pos;

  int dx = (delta_a < 0) ? -1 : (delta_a > 0) ? 1 : 0;

  if (dx)
  {
    uint8_t spd = min(200, max(100, min(abs(delta_a) * 15, abs(delta_b) * 15)));
//    stepper1_setSpeed(spd, delta_a, delta_b, meazure_1, target_pos);
//    stepper1_step(dx * 25);
    stepper_1.setSpeed(spd);
    stepper_1.step(dx * 25);
    meazure_1 += dx;
  }
  else
  {
    stepper1_stop();
    old_pos_1 = target_pos;
  }

  return dx;
}

void setup()
{
  Serial.begin(9600);
  analogWrite(2, 255);
  analogWrite(3, 255);
  analogWrite(4, 255);
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);
  delay(1000);
}

long a_time = 0;
int pos[5] = {60, 0, 40, 20, 30};
int p = 0;

void loop()
{
  while (stepper1_go(-60) != 0);
  meazure_1 = 0;
  old_pos_1 = 0;
  delay(2000);
  while (stepper1_go(60) != 0);
  while (1) delay(10);
}
