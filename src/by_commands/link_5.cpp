#include "link_5.h"

Servo servo_link5;

void link5_init()
{
	servo_link5.attach( 8);
	servo_link5.write( 90);
}