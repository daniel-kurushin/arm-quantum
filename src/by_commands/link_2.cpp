#include "link_2.h"

double link2_current_angle = 0;
int link2_current_pos = 0;

void link2_init()
{
    pinMode(link2_5v,  1);
    pinMode(link2_en_, 1);
    pinMode(link2_cw,  1);
    pinMode(link2_clk, 1);

    // for (int i = 0; i < 3000; ++i)
    // {
    //     link2_up();
    // }
    // for (int i = 0; i < 100; ++i)
    // {
    //     link2_dn();
    // }
    // delay(5000);
    // link2_current_pos = 0;

    // link2_rotate(80);
    // Serial.println(link2_current_pos);
    // delay(5000);
    // link2_rotate(60);
    // Serial.println(link2_current_pos);
    // delay(5000);
    // link2_rotate(30);
    Serial.println(link2_current_pos);

    link2_release();
}

int link2_angle_to_pos(float angle)
{
    double a =  -0.0012061;
    double b =   0.1699394;
    double c =  20.0653030;
    double d =   0.0;

    float pos = a * pow(angle, 3) + b * pow(angle, 2) + c * angle + d;
    return round(pos);
}

void link2_rotate(float angle)
{
    int steps = link2_angle_to_pos(angle) - link2_current_pos;
    int d_pos = (steps > 0) ? 1 : -1;
    for (int i = 0; i < abs(steps); i++)
    {
        (steps > 0) ? link2_dn() : link2_up();
        link2_current_pos += d_pos;
    }
    link2_current_angle = angle;
    link2_release();
}

void link2_release()
{
  digitalWrite(link2_5v,  1);
  digitalWrite(link2_en_, 0);
  digitalWrite(link2_cw,  0);
  digitalWrite(link2_clk, 0);
}

void link2_up()
{
  digitalWrite(link2_en_, 1);
  digitalWrite(link2_5v,  1);
  digitalWrite(link2_cw,  0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(link2_clk, !digitalRead(link2_clk));
    delayMicroseconds(1000);
  }
}

void link2_dn()
{
  digitalWrite(link2_en_, 1);
  digitalWrite(link2_5v,  1);
  digitalWrite(link2_cw,  1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(link2_clk, !digitalRead(link2_clk));
    delayMicroseconds(1000);
  }
}