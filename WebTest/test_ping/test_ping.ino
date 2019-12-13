int LED = 13;
char data;
byte input;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() {
  data = Serial.available();
  
  if (data != 0){
    input = Serial.read();
    Serial.println(input);
    if (input == '1'){
      digitalWrite(LED,HIGH);
    }
    else if (input == '2'){
      digitalWrite(LED,LOW);
    }
  }
  
}
