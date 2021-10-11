#include "link_1.h"

double link1_current_angle = 0;
int link1_current_pos = 0;

void link1_init()
{
    pinMode(link1_en,   1);
    pinMode(link1_dir,  1);
    pinMode(link1_step, 1);

    // for (int i = 0; i < 1300; ++i)
    // {
    //     link1_up();
    // }
    // link1_release();
    link1_current_pos = 0;
}

int link1_angle_to_pos(float angle)
{
    double a =     0.0153215;
    double b =    -3.7365337;
    double c =   269.8232838;
    double d = -6047.3376623;

    float pos = a * pow(angle, 3) + b * pow(angle, 2) + c * angle + d;
    return round(pos);
}

void link1_rotate(float angle)
{
    int steps = link1_angle_to_pos(angle) - link1_current_pos;
    int d_pos = (steps > 0) ? 1 : -1;
    for (int i = 0; i < abs(steps); i++)
    {
        (steps > 0) ? link1_up() : link1_dn();
        link1_current_pos += d_pos;
    }
    link1_current_angle = angle;
    link1_release();
}

void link1_up()
{
  digitalWrite(link1_en, 0);
  digitalWrite(link1_dir, 0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(link1_step, !digitalRead(link1_step));
    delayMicroseconds(1000);
  }
}

void link1_dn()
{
  digitalWrite(link1_en, 0);
  digitalWrite(link1_dir, 1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(link1_step, !digitalRead(link1_step));
    delayMicroseconds(1000);
  }
}


void link1_release()
{
    digitalWrite(link1_en, 1);
    digitalWrite(link1_dir, 0);
    digitalWrite(link1_step, 0);
}

