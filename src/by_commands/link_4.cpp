#include "link_4.h"

Servo servo_link4;

void link4_init()
{
	servo_link4.attach(10);
	servo_link4.write(100);//90
}