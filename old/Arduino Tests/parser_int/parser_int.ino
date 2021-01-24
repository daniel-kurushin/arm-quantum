#include <stdarg.h>

#define s_begin Serial.begin
#define s_print Serial.print
#define s_is_av Serial.available
#define s_read  Serial.read
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
  s_begin(9600);
}

void execute(int m, int steps)
{

}

int m = 0;
int s = 0;
int t = 0;
int x = 0;

void loop()
{
  if (s_is_av())
  {
    x = s_to_int();
    if (t++ % 2 == 0)
    {
      m = x;
    }
    else
    {
      s = x;
      s_println(3, 666, m, s);
      t = 0;
    }
  }
}
