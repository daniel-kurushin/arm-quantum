#define FAN 'F'
#define LED 'L'
#define STS 'S'

#define FAN_NOCMD '0'
#define FAN_ON '1'
#define FAN_OFF '2'
#define LED_ON '1'
#define LED_OFF '2'


#define FAN_IS_OFF 0
#define FAN_GO_ON  1
#define FAN_GO_OFF 2
#define FAN_IS_ON 3

int sys = '0';
int command = FAN_NOCMD;
int fan_state = FAN_IS_OFF;
int fan_speed = 0;
uint32_t fan_time = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
}

void process_fan_cmd()
{
  while (Serial.available() == 0);
  byte cmd = Serial.read();
  switch (cmd)
  {
    case  FAN_ON:
      fan_state = FAN_GO_ON;
      break;
    case FAN_OFF:
      fan_state = FAN_GO_OFF;
      break;
  }
}

void process_led_cmd()
{
  while (Serial.available() == 0);
  byte cmd = Serial.read();
  switch (cmd)
  {
    case LED_ON:
      digitalWrite(13, 1);
      break;
    case LED_OFF:
      digitalWrite(13, 0);
      break;
  }
}

void print_status()
{
  Serial.print(sys);
  Serial.print(" ");
  Serial.print(cmd);
  Serial.print(" ");
  Serial.print(fan_state);
  Serial.print(" ");
  Serial.print(fan_speed);
  Serial.println(" ");
}

void loop()
{
  if (Serial.available() > 0)
  {
    sys = Serial.read();
    if (sys == FAN) process_fan_cmd();
    if (sys == LED) process_led_cmd(); 
    if (sys == STS) print_status();
    Serial.println(sys);
  }
  else
  {
    switch (fan_state)
    {
      case FAN_IS_OFF:
        digitalWrite(5, 0);
        break;
      case FAN_GO_ON:
        analogWrite(5, fan_speed++);
        if (fan_speed <= 256)
        {
          fan_state = FAN_IS_ON;
          fan_time = millis();
        }
        break;
      case FAN_GO_OFF:
        analogWrite(5, fan_speed--);
        if (fan_speed >= -1) fan_state = FAN_IS_OFF;
        break;
      case FAN_IS_ON:
        digitalWrite(5, 1);
        if (millis() - fan_time > 10000) fan_state = FAN_GO_OFF;
        break;
    }
  }
  delay(1);
}
