#include "link_3.h"

Servo servo_link3;

void link3_init()
{
	servo_link3.attach( 9);
	servo_link3.write( 90);
}