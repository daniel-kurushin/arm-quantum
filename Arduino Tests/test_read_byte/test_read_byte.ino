#define s_begin Serial.begin
#define s_print Serial.print
#define s_is_av Serial.available
#define s_read Serial.read
#define s_to_int Serial.parseInt

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


void setup()
{
  pinMode(13, 1);
  s_begin(9600);
}

int rs = 0;
int sys_n;
int cmd_n;
int nbytes = 0;
int led_state = 0;
byte b;
byte first_byte;
byte second_byte;
int x;

void loop()
{
  if (s_is_av() > 0)
  {
    b = s_read();
    switch (rs)
    {
      case 0:
        if (b == 48) rs++;
        break;
      case 1:
        if (b == 48) rs++;
        else rs = 0;
        break;
      case 2:
        sys_n = b;
        rs++;
        break;
      case 3:
        cmd_n = b;
        rs++;
        break;
      case 4:
        first_byte = b;
        rs++;
        break;
      case 5:
        second_byte = b;
        rs++;
        break;
      case 6:
        x = first_byte;
        x = x << 8;
        x |= second_byte;
        rs++;
        break;
      /*case 4:
        switch (sys_n)
        {
          case 49:
            switch (cmd_n)
            {
              case 50:

                led_state = 1;
                nbytes = 5;
                break;
              case 51:

                led_state = 0;
                nbytes = 5;
                break;
            }
            break;
        }
        rs ++;
        break;
      case 5:
        if (rs == nbytes)
        {
          digitalWrite(13, led_state);
          rs = 0;
        }
        else
        {
          rs = 0;
        }
        break;*/
    }
    s_println(7, b, rs, sys_n, cmd_n, first_byte, second_byte, x);
  }
  //s_println(6, b, rs, sys_n, cmd_n, nbytes, led_state);
  //s_println(7, b, rs, sys_n, cmd_n, first_byte, second_byte, x);
  //delay(1000);
}
