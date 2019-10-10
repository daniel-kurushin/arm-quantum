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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available() > 0 )
 {
   byte x = Serial.read();
   Serial.write(x);
 }
}
