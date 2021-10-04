#include <Servo.h>
#include <Stepper.h>
#include "pins.h"

// from https://raw.githubusercontent.com/Honepa/stanislav/main/joystick_run/joystick_run.ino
#define STEPS 200

#define INIT     0
#define ST_LED1  1
#define ST_LED2  2
#define ST_LED3  3
#define ST_LED4  4
#define ST_LED5  5

Stepper mot3(STEPS, 37, 39, 41, 43);
Servo servo1;
Servo servo2;
Servo servo3;


int serv1_pos =  0;
int serv2_pos =  0;
int serv3_pos =  0;

int state = 0;
int joy_x, joy_y, joy_knok = 0;

void motor_stop()
{
  digitalWrite(37, 0);
  digitalWrite(39, 0);
  digitalWrite(41, 0);
  digitalWrite(43, 0);

  digitalWrite(mot1_en, 1);
  digitalWrite(mot1_dir, 0);
  digitalWrite(mot1_step, 0);

  digitalWrite(mot2_5v, 0);
  digitalWrite(mot2_en_, 0);
  digitalWrite(mot2_cw, 0);
  digitalWrite(mot2_clk, 0);

}
void mot3_right()
{
  mot3.step(10);
}
void mot3_left()
{
  mot3.step(-10);
}
void mot2_up()
{
  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v, 1);
  digitalWrite(mot2_cw, 0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot2_clk, !digitalRead(mot2_clk));
    delayMicroseconds(1000);
  }
}

void mot2_down()
{
  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v, 1);
  digitalWrite(mot2_cw, 1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot2_clk, !digitalRead(mot2_clk));
    delayMicroseconds(1000);
  }
}

void mot1_up()
{
  digitalWrite(mot1_en, 0);
  digitalWrite(mot1_dir, 0);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot1_step, !digitalRead(mot1_step));
    delayMicroseconds(1000);
  }
}

void mot1_down()
{
  digitalWrite(mot1_en, 0);
  digitalWrite(mot1_dir, 1);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(mot1_step, !digitalRead(mot1_step));
    delayMicroseconds(1000);
  }
}

void servo1_up()
{
  if (serv1_pos < 270) serv1_pos++;
  servo1.write(serv1_pos);
  delay(10);
}

void servo1_down()
{
  if (serv1_pos >   0) serv1_pos--;
  servo1.write(serv1_pos);
  delay(10);
}

void servo2_up()
{
  if (serv2_pos < 180) serv2_pos++;
  servo2.write(serv2_pos);
  delay(10);
}

void servo2_down()
{
  if (serv2_pos >   0) serv2_pos--;
  servo2.write(serv2_pos);
  delay(10);
}

void servo3_up()
{
  if (serv3_pos < 270) serv3_pos++;
  servo3.write(serv3_pos);
  delay(10);
}

void servo3_down()
{
  if (serv3_pos >   0) serv3_pos--;
  servo3.write(serv3_pos);
  delay(10);
}

void setup()
{
  Serial.begin(9600);
  pinMode(mot1_en,   1);
  pinMode(mot1_dir,  1);
  pinMode(mot1_step, 1);

  pinMode(mot2_5v,  1);
  pinMode(mot2_en_, 1);
  pinMode(mot2_cw,  1);
  pinMode(mot2_clk, 1);
  pinMode(A5, INPUT_PULLUP);

  pinMode(led1, 1);
  pinMode(led2, 1);
  pinMode(led3, 1);
  pinMode(led4, 1);
  pinMode(led5, 1);

  digitalWrite(mot1_en,  0);

  digitalWrite(mot2_en_, 1);
  digitalWrite(mot2_5v,  1);
  //1 -2
  //2 - 3
  //3 - 1
  servo1.attach( 9);
  servo2.attach( 10);
  servo3.attach( 8);
  mot3.setSpeed(30);

  servo1.write(serv1_pos);
  servo2.write(serv2_pos);
  servo3.write(serv3_pos);

  Serial.begin(9600);
}

void loop()
{
  joy_x =    analogRead(x);
  joy_y =    analogRead(y);
  if (analogRead(knok) < 30)
  {
    joy_knok = 1;
  }
  else
  {
    joy_knok = 0;
  }
  switch (state)
  {
    case INIT:
      {
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
        digitalWrite(led4, 0);
        digitalWrite(led5, 0);
        if (joy_knok)
        {
          state = ST_LED1;
          joy_knok = 0;
        }

        break;
      }
    case ST_LED1:
      {
        digitalWrite(led1, 1);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
        digitalWrite(led4, 0);
        digitalWrite(led5, 0);
        if (joy_knok)
        {
          motor_stop();
          state = ST_LED2;
          joy_knok = 0;
          delay(150);
        }
        if ((joy_y > 700) and (joy_x > 350) and (joy_x < 700))
        {
          mot1_up();
        }
        else if ((joy_y < 350) and (joy_x > 350) and (joy_x < 700))
        {
          mot1_down();
        }
        else if ((joy_x > 700) and (joy_y > 350) and (joy_y < 700))
        {
          mot3_right();
        }
        else if ((joy_x < 350) and (joy_y > 350) and (joy_y < 700))
        {
          mot3_left();
        }
        else
        {
          motor_stop();
        }
        break;
      }
    case ST_LED2:
      {
        digitalWrite(led1, 0);
        digitalWrite(led2, 1);
        digitalWrite(led3, 0);
        digitalWrite(led4, 0);
        digitalWrite(led5, 0);
        if (joy_knok)
        {
          motor_stop();
          state = ST_LED3;
          joy_knok = 0;
          delay(150);
        }
        if ((joy_y > 700) and (joy_x > 350) and (joy_x < 700))
        {
          mot2_up();
        }
        else if ((joy_y < 350) and (joy_x > 350) and (joy_x < 700))
        {
          mot2_down();
        }
        else if ((joy_x > 700) and (joy_y > 350) and (joy_y < 700))
        {
          mot3_right();
        }
        else if ((joy_x < 350) and (joy_y > 350) and (joy_y < 700))
        {
          mot3_left();
        }
        else
        {
          motor_stop();
        }
        break;
      }
    case ST_LED3:
      {
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 1);
        digitalWrite(led4, 0);
        digitalWrite(led5, 0);
        if (joy_knok)
        {
          motor_stop();
          state = ST_LED4;
          joy_knok = 0;
          delay(150);
        }
        if ((joy_y > 700) and (joy_x > 350) and (joy_x < 700))
        {
          servo1_up();
        }
        else if ((joy_y < 350) and (joy_x > 350) and (joy_x < 700))
        {
          servo1_down();
        }
        else if ((joy_x > 700) and (joy_y > 350) and (joy_y < 700))
        {
          //x_rgt
          mot3_right();
        }
        else if ((joy_x < 350) and (joy_y > 350) and (joy_y < 700))
        {
          //x_left
          mot3_left();
        }
        else
        {
          motor_stop();
        }
        break;
      }
    case ST_LED4:
      {
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
        digitalWrite(led4, 1);
        digitalWrite(led5, 0);
        if (joy_knok)
        {
          motor_stop();
          state = ST_LED5;
          joy_knok = 0;
          delay(150);
        }
        if ((joy_y > 700) and (joy_x > 350) and (joy_x < 700))
        {
          //y_up
          servo2_up();
        }
        else if ((joy_y < 350) and (joy_x > 350) and (joy_x < 700))
        {
          //y_down
          servo2_down();
        }
        else if ((joy_x > 700) and (joy_y > 350) and (joy_y < 700))
        {
          //x_rgt
          mot3_right();
        }
        else if ((joy_x < 350) and (joy_y > 350) and (joy_y < 700))
        {
          //x_left
          mot3_left();
        }
        else
        {
          motor_stop();
        }
        break;
      }
    case ST_LED5:
      {
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
        digitalWrite(led4, 0);
        digitalWrite(led5, 1);
        if (joy_knok)
        {
          motor_stop();
          state = ST_LED1;
          joy_knok = 0;
          delay(150);
        }
        if ((joy_y > 700) and (joy_x > 350) and (joy_x < 700))
        {
          //y_up
          servo3_up();
        }
        else if ((joy_y < 350) and (joy_x > 350) and (joy_x < 700))
        {
          //y_down
          servo3_down();
        }
        else if ((joy_x > 700) and (joy_y > 350) and (joy_y < 700))
        {
          //x_rgt
          mot3_right();
        }
        else if ((joy_x < 350) and (joy_y > 350) and (joy_y < 700))
        {
          //x_left
          mot3_left();
        }
        else
        {
          motor_stop();
        }
        break;
      }
  }
}
