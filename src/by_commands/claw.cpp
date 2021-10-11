#include "claw.h"

Servo servo_claw;
int claw_state;

void claw_init()
{
	servo_claw.attach(12);
	claw_open(); 
	delay(1000);
	claw_close();
}

void claw_open()
{
	servo_claw.write(CLAW_OPEN);
	claw_state = CLAW_OPEN;
}

void claw_close()
{
	servo_claw.write(CLAW_CLOSE);
	claw_state = CLAW_CLOSE;
}