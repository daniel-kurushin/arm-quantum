#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200

Servo servo;

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46); // большой двигатель вверх
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39); // двигатель верхний пред кусь
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47); // двигатель верхний на кусь

byte b;
int rs = 0;
int rs_coord = 0;
int r_sys = 0, r_cmd = 0, e_sys = 0, e_cmd = 0;
int f_b_x, s_b_x, f_b_y, s_b_y, f_b_z, s_b_z;
int x, y, z;

int r1, r2, r3, r4;
const int k = 25;

int motor = 2;
int steps = 0;

void setup()
{
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  myStepper3.setSpeed(60);
  myStepper4.setSpeed(60);

  servo.attach(10);

  Serial.begin(9600);

  analogWrite(2, 255);
  analogWrite(3, 255);
  analogWrite(4, 255);
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);

  //  digitalWrite(FAN1, 1);
  //  digitalWrite(LIGHT, 1);
  //  digitalWrite(VACUUM, 1);
}

void log()
{
  Serial.println("b\trs\tr_sys\tr_cmd\te_sys\te_cmd");
  Serial.print(b);      Serial.print("\t");
  Serial.print(rs);     Serial.print("\t");
  Serial.print(r_sys);  Serial.print("\t");
  Serial.print(r_cmd);  Serial.print("\t");
  Serial.print(e_sys);  Serial.print("\t");
  Serial.print(e_cmd);  Serial.print("\t");
  Serial.println("");
  
  Serial.println("f_b_x\ts_b_x\tx\tf_b_y\ts_b_y\ty\tf_b_z\ts_b_z\tz");
  Serial.print(f_b_x);  Serial.print("\t");
  Serial.print(s_b_x);  Serial.print("\t");
  Serial.print(x);      Serial.print("\t");
  Serial.print(f_b_y);  Serial.print("\t");
  Serial.print(s_b_y);  Serial.print("\t");
  Serial.print(y);      Serial.print("\t");
  Serial.print(f_b_z);  Serial.print("\t");
  Serial.print(s_b_z);  Serial.print("\t");
  Serial.print(z);      Serial.print("\t");
  Serial.println("");
  Serial.println("");
}

void initialization()
{
  switch (motor)
  {
    case 2:
      {
        myStepper2.step(-10);
        if (steps++ > 150)
        {
          motor = 3;
          steps = 0;
        }
//        motor = 3;
        break;
      }
    case 3:
      {
        myStepper3.step(-10);
        if (steps++ > 330)
        {
          motor = 4;
          steps = 0;
        }
//        motor = 4;
        break;
      }
    case 4:
      {
        myStepper4.step(10);
        if (steps++ > 170)
        {
          motor = 0;
          steps = 0;
        }
//        motor = 0;
        break;
      }
  }

  if (motor == 0)
  {
    Serial.println("servo");
    stepper2_stop();
    stepper3_stop();
    stepper4_stop();
    servo.write(0);
    motor = 2;
    steps = 0;
    e_cmd = 0;
    e_sys = 0;
    log();
  }
}

void stepper1_stop()
{
  digitalWrite(44, 0);
  digitalWrite(42, 0);
  digitalWrite(40, 0);
  digitalWrite(38, 0);
}
void stepper2_stop()
{
  digitalWrite(52, 0);
  digitalWrite(50, 0);
  digitalWrite(48, 0);
  digitalWrite(46, 0);
}
void stepper3_stop()
{
  digitalWrite(45, 0);
  digitalWrite(43, 0);
  digitalWrite(41, 0);
  digitalWrite(39, 0);
}
void stepper4_stop()
{
  digitalWrite(53, 0);
  digitalWrite(51, 0);
  digitalWrite(49, 0);
  digitalWrite(47, 0);
}

void stepper2_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 60) pos = 60;
  if (pos != r2)
  {
    myStepper2.step(-(pos - r2)*k);
  }
  stepper2_stop();
  r2 = pos;
}

void stepper3_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 132) pos = 132;
  if (pos != r3)
  {
    myStepper3.step(-(pos - r3)*k);
  }
  stepper3_stop();
  r3 = pos;
}

void stepper4_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 68) pos = 68;
  if (pos != r4)
  {
    myStepper4.step((pos - r4)*k);
  }
  stepper4_stop();
  r4 = pos;
}

void loop()
{

  if (Serial.available() > 0)
  {
    b = Serial.read();

    switch (rs)
    {
      case 0:
      {
        if (b == 48)
        {
          rs++;
        }
        else
        {
          b = 5;
          Serial.println("not first synchro");
        }
        break;
      }
      case 1:
      {
        if (b == 48)
        {
          rs++;
        }
        else
        {
          rs = 0;
          Serial.println("not second synchro ");
        }
        break;
      }
      case 2:
        if (r_sys == 0)
          r_sys = b;
        else
        {
          switch (r_sys)
          {
            case 49:
              {
                if (r_cmd == 0)
                {
                  r_cmd = b;
                  switch (r_cmd) //without parametrs
                  {
                    case 49:
                    {
                      //inicialization
                      rs++;
                      break;
                    }
                    case 50:
                    {
                      //stop
                      rs++;
                      break;
                    }
                  }
                }
                else
                {
                  switch (r_cmd)//with parametrs
                  {
                    case 51:
                      {
                        //coordinates
                        switch(rs_coord)
                        {
                          // X //
                          case 0:
                          {
                            f_b_x = b;
                            rs_coord++;
                            break;
                          }
                          case 1:
                          {
                            s_b_x = b;
                            x = f_b_x;
                            x = x << 8;
                            x = x | s_b_x;
                            rs_coord++;
                            break;
                          }
                          // Y //
                          case 2:
                          {
                            f_b_y = b;
                            rs_coord++;
                            break;
                          }
                          case 3:
                          {
                            s_b_y = b;
                            y = f_b_y;
                            y = y << 8;
                            y = y | s_b_y;
                            rs_coord++;
                            break;
                          }
                          // Z //
                          case 4:
                          {
                            f_b_z = b;
                            rs_coord++;
                            break;
                          }
                          case 5:
                          {
                            s_b_z = b;
                            z = f_b_z;
                            z = z << 8;
                            z = z | s_b_z;
                            rs++;
                            rs_coord = 0;
                            break;
                          }
                        }                        
                        
                        break;
                      }
                    default:
                      {
                        Serial.println("number command  not found ");
                        r_sys = 0;
                        r_cmd = 0;
                        rs = 0;
                      }
                  }
                }
              }
              break;
            default:
              {
                Serial.println("number system  not found ");
                r_sys = 0;
                r_cmd = 0;
                rs = 0;
              }
          }
        }
        break;
/*
              case 50://position x, y, z
                switch (rs)
                {
                  case 5:
                    first_byte_x = b;
                    rs++;
                    break;
                  case 6:
                    second_byte_x = b;
                    x = first_byte_x;
                    x = x << 8;
                    x = x | second_byte_x;
                    rs=0;
                    break;
        //                  case 7:
        //                    first_byte_y = b;
        //                    rs++;
        //                    break;
        //                  case 8:
        //                    second_byte_y = b;
        //                    rs++;
        //                    break;
        //                  case 9:
        //                    first_byte_z = b;
        //                    rs++;
        //                    break;
        //                  case 10:
        //                    second_byte_z = b;
        //                    rs++;
        //                    break;
        //                  case 11:
        //
        //                    rs++;
        //                    break;
        //                  case 12:
        //                    y = first_byte_y;
        //                    y = y << 8;
        //                    y = y | second_byte_y;
        //                    rs++;
        //                    break;
        //                  case 13:
        //                    z = first_byte_z;
        //                    z = z << 8;
        //                    z = z | second_byte_z;
        //                    rs++;
        //                    break;
                }
*/
      case 3:
        if (b == 102) rs++;
        else
        {
          rs = 0;
          r_sys = 0;
          r_cmd = 0;
          Serial.println("not first end synchro ");
        }
        break;
      case 4:
        rs = 0;
        if (b == 102)
        {
          e_sys = r_sys;
          e_cmd = r_cmd;
          r_sys = 0;
          r_cmd = 0;
          Serial.println("command successful recive ");
        }
        else
        {
          Serial.println("not second end synchro ");
          r_sys = 0;
          r_cmd = 0;
        }
        break;
    }
    log();
  }
  else
  {

    //еще нужно деление на выполненную и в процессе

    switch (e_sys)
    {
      case 49:
        switch (e_cmd)
        {
          case 49:
            initialization();
            Serial.print("inicialization step ");
            Serial.print(steps);
            Serial.println("");
            break;
          case 50:
            stepper1_stop();
            stepper2_stop();
            stepper3_stop();
            stepper4_stop();
            motor = 2;
            steps = 0;
            e_cmd = 0;
            e_sys = 0;
            log();
            Serial.println("stop");
            break;
          case 51:
            Serial.println("Stepper_go");
            e_cmd = 0;
            e_sys = 0;
            log();
            break;
          default:
            Serial.println("command not selected");
        }
        break;

//      default://inaction
//        Serial.println("system not selected");
//        delay(1000);
    }
  }

}
