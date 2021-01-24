#include "typedef.h"
#include "reverse.h"
#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200
#define RESOLUTION 61

void all_steppers_off()
{
  for (int i = 38; i < 54; i++) digitalWrite(i, 0);
}

/***************** Z-axis *********************/
Stepper z_stepper(STEPS_PER_REVOLUTION, 44, 42, 40, 38);

float z_old_pos = 0;

float z_measure()
{
  float r = 0;
  for (int i = 0; i < 10; i++)
  {
    r += analogRead(A0);
  }
  return r * 0.0450366 - 114.753273;
}

int z_stepper_go(float target_pos)
{
  float pos = z_measure();
  float delta_a = target_pos - pos;
  float delta_b = z_old_pos - pos;
  int dz = (delta_a < -2) ? 1 : (delta_a > 2) ? -1 : 0;
  if (dz)
  {
    uint8_t spd = min(60, max(20, min(abs(delta_a) * 2, abs(delta_b) * 2)));
    z_stepper.setSpeed(spd);
    z_stepper.step(dz * 25);

  }
  else
  {
    all_steppers_off();
    z_old_pos = target_pos;
  }
  return dz;
}

/******************* stepper 1 ************************/
float old_pos_1 = 0;

float meazure_1 = 0;

Stepper stepper_1(STEPS_PER_REVOLUTION, 52, 50, 48, 46);

int stepper1_go(float target_pos)
{
  float pos = meazure_1;
  float delta_a = target_pos - pos;
  float delta_b = old_pos_1 - pos;

  int dx = (delta_a < 0) ? -1 : (delta_a > 0) ? 1 : 0;

  if (dx)
  {
    uint8_t spd = min(200, max(100, min(abs(delta_a) * 15, abs(delta_b) * 15)));
    stepper_1.setSpeed(spd);
    stepper_1.step(dx * 25);
    meazure_1 += dx;
  }
  else
  {
    all_steppers_off();
    old_pos_1 = target_pos;
  }

  return dx;
}

/************************** stepper 2 ************************/
float old_pos_2 = 0;

float meazure_2 = 0;

Stepper stepper_2(STEPS_PER_REVOLUTION, 45, 43, 41, 39);

int stepper2_go(float target_pos)
{
  float pos = meazure_2;
  float delta_a = target_pos - pos;
  float delta_b = old_pos_2 - pos;

  int dx = (delta_a < 0) ? -1 : (delta_a > 0) ? 1 : 0;

  if (dx)
  {
    uint8_t spd = min(250, max(150, min(abs(delta_a) * 20, abs(delta_b) * 20)));
    stepper_2.setSpeed(spd);
    stepper_2.step(-dx * 25);
    meazure_2 += dx;
  }
  else
  {
    all_steppers_off();
    old_pos_2 = target_pos;
  }

  return dx;
}

/*************** stepper 3 ********************************/
float old_pos_3 = 0;

float meazure_3 = 0;

Stepper stepper_3(STEPS_PER_REVOLUTION, 53, 51, 49, 47);

int stepper3_go(float target_pos)
{
  float pos = meazure_3;
  float delta_a = target_pos - pos;
  float delta_b = old_pos_3 - pos;

  int dx = (delta_a < 0) ? -1 : (delta_a > 0) ? 1 : 0;

  if (dx)
  {
    uint8_t spd = min(250, max(150, min(abs(delta_a) * 20, abs(delta_b) * 20)));
    stepper_3.setSpeed(spd);
    stepper_3.step(-dx * 25);
    meazure_3 += dx;
  }
  else
  {
    all_steppers_off();
    old_pos_3 = target_pos;
  }

  return dx;
}

/********************** sonic **********************/

void meazure_d(int trig, int echo)
{
  long duration;

  pinMode(trig, 1);
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(5);
  digitalWrite(trig, 0);

  pinMode(echo, 0);
  duration = pulseIn(echo, 1);

  distance = duration;

  delayMicroseconds(5);
}


/************************** reverse ***********************/

void reverse(int x, int y)
{
  int mind = 10000;
  for (int i = 0; i < 497; i++)
  {

    float d = sqrt(pow(X[i] - x, 2) + pow(Y[i] - y, 2));

    if (d < mind)
    {
      mind = d;
      r1 = R2[i];
      r2 = R3[i];
      r3 = R4[i];
    }


  }
}

ENInitState do_init()
{
  static ENInitState state = INIT_OK;
  switch (state)
  {
    case PORTS:
      for (int i = 2; i < 10; i++)
      {
        analogWrite(i, 255);
      }
      state = ZAXIS;
      break;
    case ZAXIS:
      if (z_stepper_go(0) == 0) state = STEPPER1;
      break;
    case STEPPER1:
      if (stepper1_go(-60) == 0)
      {
        meazure_1 = 60;
        old_pos_1 = 60;
        state = STEPPER2;
      }
      break;
    case STEPPER2:
      if (stepper2_go(140) == 0)
      {
        meazure_1 = 132;
        old_pos_1 = 132;
        state = STEPPER3;
      }
      break;
    case STEPPER3:
      if (stepper3_go(-70) == 0)
      {
        meazure_1 = 68;
        old_pos_1 = 68;
        state = INIT_OK;
      }
      break;
    case INIT_OK:
      all_steppers_off();
      break;
  }
  return state;
}

void telemetry(int RS, int GS, char c, int cmd, int len, int val, int nval, int high, int low, int x, int y, int z, float l, int xvat)
{
  static long t0;

  if (millis() - t0 < 1000) return;
  t0 = millis();

  Serial.print(tm_msgRS[RS]);
  Serial.print("\t");
  Serial.print(tm_msgGS[GS]);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print(tm_msgCMD[cmd]);
  Serial.print("\t");
  Serial.print(len);
  Serial.print("\t");
  Serial.print(val);
  Serial.print("\t");
  Serial.print(nval);
  Serial.print("\t");
  Serial.print(high);
  Serial.print("\t");
  Serial.print(low);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
  Serial.print(l);
  Serial.print("\t");
  Serial.print(xvat);
  Serial.print("\n");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("RS\tGS\tc\tcmd\tlen\tval\tnval\thigh\tlow\tx\ty\tz\tl\txvat");
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  delay(100);
}

void loop()
{
  char c = ' ';
  if (Serial.available())
  {
    c = Serial.read();
    switch (RS)
    {
      case SYNC0:
        RS = (c == '0') ? SYNC1 : ERR;
        break;
      case SYNC1:
        RS = (c == '0') ? CMD : ERR;
        break;
      case CMD:
        cmd = c;
        RS = LEN;
        break;
      case LEN:
        len = c;
        val = 0;
        RS = VALLOW;
        nval = 0;
        pos = 0;
        break;
      case VALLOW:
        low = c;
        RS = VALHIGH;
        break;
      case VALHIGH:
        high =  c;
        val = high * 256 + low;
        if (++nval < len)
        {
          values[pos++] = val;
          RS = VALLOW;
        } else
        {
          RS = END;
        }
        break;
      case END:
        values[pos++] = val;
        RS = (c == '0') ? SYNC0 : ERR;
        if (RS == SYNC0) GS = CMD_REC;
        break;
      case ERR:
        break;
    }
  }
  switch (GS)
  {
    case INIT:
      if (do_init() == INIT_OK) GS = READY;
      break;
    case READY:
      break;
    case CMD_REC:
      switch (cmd)
      {
        case CMD_MOVE_XYZ:
          x = values[0];
          y = values[1];
          z = values[2];
          GS = ROTZ;
          break;
        case CMD_MEASURE:
          break;
        case CMD_XBAT:
          xvat = 1;
          break;
        case CMD_UNXBAT:
          xvat = 0;
          break;
      }
      break;
    case ROTZ:
      if (z_stepper_go(z) == 0)
      {
        reverse(x, y);
        GS = MOVE0;
      }
      break;
    case MOVE0:
      if (stepper1_go(r1) == 0)
      {
        GS = MOVE1;
      }
      break;
    case MOVE1:
      if (stepper2_go(r2) == 0)
      {
        GS = MOVE2;
      }
      break;
    case MOVE2:
      if (stepper3_go(r3) == 0)
      {
        GS = MEASURE;
      }
      break;
    case STOP:
      break;
    case XBAT:
      break;
    case UNXBAT:
      break;
    case MEASURE:
      break;
    case FAIL:
      break;
  }
  meazure_d(53,52);
  telemetry(RS, GS, c, cmd, len, val, nval, high, low, x, y, z, distance, xvat);
}
