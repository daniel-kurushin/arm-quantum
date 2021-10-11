#include "link_0.h"
#include "link_1.h"
#include "link_2.h"
#include "link_3.h"
#include "link_4.h"
#include "link_5.h"
#include "claw.h"

void setup() 
{
    Serial.begin(9600);
    link0_init();
    link1_init();
    link2_init();
    link3_init();
    link4_init();
    link5_init();
    claw_init();
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  //dw({13},{1});
  delay(100);
  //dw({13},{0});
  delay(100);
}
