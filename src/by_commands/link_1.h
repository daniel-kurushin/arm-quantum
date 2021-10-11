#define link1_en   53
#define link1_dir  51
#define link1_step 49

#include <Arduino.h>

void link1_init();
void link1_up();
void link1_dn();
void link1_release();
int  link1_angle_to_pos(float angle);
void link1_rotate(float angle);

