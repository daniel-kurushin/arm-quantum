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

void telemetry(int RS, int GS, char c, int cmd, int len, int val, int nval, int high, int low)
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
  Serial.print(cmd);
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
  Serial.print("\n");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("RS\tc\tcmd\tlen\tval\tnval\thigh\tlow");
}

void loop()
{
  char c;
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
        RS = (c == '0') ? SYNC0 : ERR;
        break;
    }
  }
  switch (GS)
  {
    case INIT:
      if (do_init() == INIT_OK) GS = READY;
      break;
    case READY:
      GS = ROTZ;
      break;
    case ROTZ:
      if (z_stepper_go(-20) == 0) GS = MOVE0;
      break;
    case MOVE0:
      break;
    case MOVE1:
      break;
    case MOVE2:
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
  telemetry(RS, GS, c, cmd, len, val, nval, high, low);
}
