#include <Servo.h>

#define COMMAND_ROTATE 9
#define SERVO_PIN 3

Servo servo1;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
  servo1.attach(SERVO_PIN);
}

void loop() {
  if (Serial.available() > 0) {
    if Serial.available()
    byte command = Serial.read();
    if (command == COMMAND_ROTATE) {
      byte deg = Serial.read();
      servo1.write(deg);
    }
  }
}
