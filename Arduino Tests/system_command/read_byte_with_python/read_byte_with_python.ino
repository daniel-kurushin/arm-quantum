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

byte a, first_byte, second_byte;
int rs = 0;
uint16_t y;
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
 if (Serial.available() > 0 )
 {
   a = Serial.read();
   switch(rs)
   {
    case 0:
    first_byte = a;
    rs++;
    break;
    case 1:
    sekond_byte = a;
    rs++;
    break;
    case 2:
    y = first_byte;
    y = y << 8;
    y = y | second_byte;
    break;
   }
   Serial.write(y);
 }
}
