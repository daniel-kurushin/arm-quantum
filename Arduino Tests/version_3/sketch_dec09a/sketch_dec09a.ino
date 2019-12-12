#include "typedef.h"

void do_init()
{
    static ENInitState state = ZAXIS;
    switch (state)
    {
        case ZAXIS:
            z_rotate(0);
            break;
        case ARM:
        break;
        case HAND:
        break;
    }
}

float z_measure()
{
    return analogRead(A0) * 0.4291 -113.3067;
}

ENZRotState z_rotate(int pos)
{
    if (z_oldpos != pos) {
        
    }
}

void imhostep(int dir)
{ // имитация шага любого двигателя
  delay(1);
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
      do_init();
      break;
    case READY:
      break;
    case ROTZ:
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
