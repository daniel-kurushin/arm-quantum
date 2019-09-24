#define trig 12
#define echo 11

void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

int state = 0;
uint32_t dt = 0;
uint32_t duration = 0;
uint32_t measuring = 0;

int cs = 0;
uint32_t t0 = 0;
int measuring_state = 0;

/*int mm = 0;
int i = 0;*/

void loop()
{
  switch(state)
  {
  case 0:
    measuring_state = 0;
    digitalWrite(trig, 0);
    if(micros() - dt > 5)
    {
      state = 1;
      dt = micros();
    }
    else
      dt = micros();        
    break;

  case 1:
    digitalWrite(trig, 1);
    if(micros() - dt > 10)
    {
      state = 2;
      dt = micros();
    }
    else
      dt = micros();
    break;

  case 2:
    digitalWrite(trig, 0);
    if(digitalRead(echo) == 1)
    {
      dt = micros();
      state = 3;
    }
    else if(micros() - dt > 1000000)
      state = 5;
    break;

  case 3:
    if(digitalRead(echo) == 0)
      state = 4;
    break;

  case 4:
    duration = micros() - dt;
    measuring = duration*0.17;
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
      /*if (i==0)
      {
         Serial.print ("distance ");
         Serial.println (mm);
      }*/
      
      Serial.println(measuring);
      /*i++;
      if(i>9)
      {
        mm = mm + 10;
      }*/
      cs = 0;      
      break;
  }

}


