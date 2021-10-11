#include <Arduino.h>

#define link2_5v   47
#define link2_en_  35
#define link2_cw   33
#define link2_clk  45

void link2_init();
void link2_release();
void link2_up();
void link2_dn();
int  link2_angle_to_pos(float angle);
void link2_rotate(float angle);