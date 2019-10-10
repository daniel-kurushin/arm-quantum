#define TRIG 12
#define ECHO 11

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

int state = 0;
uint32_t dt = 0;
uint32_t duration = 0;
uint32_t measuring = 0;

int cs = 0;
uint32_t t0 = 0;
int measuring_state = 0;

int mm = 0;

void loop()
{
  switch(state)
  {
  case 0:
    measuring_state = 0;
    digitalWrite(TRIG, 0);
    if(micros() - dt > 5)
    {
      state = 1;
      dt = micros();
    }
    else
      dt = micros();        
    break;

  case 1:
    digitalWrite(TRIG, 1);
    if(micros() - dt > 10)
    {
      state = 2;
      dt = micros();
    }
    else
      dt = micros();
    break;

  case 2:
    digitalWrite(TRIG, 0);
    if(digitalRead(ECHO) == 1)
    {
      dt = micros();
      state = 3;
    }
    else if(micros() - dt > 1000000)
      state = 5;
    break;

  case 3:
    if(digitalRead(ECHO) == 0)
      state = 4;
    break;

  case 4:
    duration = micros() - dt;
    measuring = duration;
    measuring_state = 1;
    state = 0;
    break;

  case 5:
    state = 0;      
    measuring_state = 2;
    break; 
  }

  /////////////////////////////////////////

  switch (cs)
  {
  case 0:
    if (millis() - t0 > 500)
    {
      cs = 1;
    }
    break;

  case 1:
    t0 = millis();
    Serial.print((int) mm++ / 100);
    Serial.print("\t");
    Serial.println(measuring);
    cs = 0;      
    break;
  }

}


