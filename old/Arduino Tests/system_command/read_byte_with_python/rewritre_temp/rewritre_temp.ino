#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200

Servo servo;

Stepper myStepper1(STEPS_PER_REVOLUTION, 44, 42, 40, 38); // двигатель поворотного основания
Stepper myStepper2(STEPS_PER_REVOLUTION, 52, 50, 48, 46); // большой двигатель вверх
Stepper myStepper3(STEPS_PER_REVOLUTION, 45, 43, 41, 39); // двигатель верхний пред кусь
Stepper myStepper4(STEPS_PER_REVOLUTION, 53, 51, 49, 47); // двигатель верхний на кусь

const int X[] =  {620, 378, 340, 604, 623, 682, 672, 596, 552, 599, 366, 645, 625, 673, 683, 595, 681, 626, 592, 424, 541, 526, 644, 616, 351, 672, 508, 467, 455, 662, 598, 559, 630, 673, 681, 661, 522, 661, 660, 538, 644, 462, 407, 576, 503, 645, 477, 650, 645, 418, 638, 490, 647, 444, 625, 589, 673, 621, 674, 386, 450, 673, 624, 535, 563, 471, 500, 642, 431, 629, 582, 450, 645, 646, 673, 683, 488, 536, 391, 661, 621, 626, 663, 673, 557, 509, 360, 585, 649, 597, 593, 664, 448, 663, 681, 681, 646, 428, 673, 674, 659, 659, 643, 674, 554, 431, 397, 681, 622, 609, 579, 411, 565, 460, 338, 603, 630, 569, 682, 683, 470, 538, 597, 674, 622, 673, 648, 626, 624, 590, 673, 682, 389, 619, 494, 612, 648, 673, 640, 674, 585, 683, 596, 340, 327, 504, 514, 564, 620, 345, 443, 644, 681, 408, 657, 659, 625, 649, 439, 342, 453, 346, 590, 368, 553, 673, 587, 485, 682, 649, 641, 682, 672, 646, 497, 598, 506, 629, 681, 664, 674, 615, 398, 486, 601, 485, 540, 367, 613, 619, 682, 674, 651, 363, 650, 459, 673, 596, 438, 591, 646, 658, 623, 661, 682, 621, 682, 683, 502, 611, 661, 370, 456, 568, 682, 674, 623, 449, 661, 662, 662, 621, 461, 682, 603, 663, 322, 556, 640, 674, 641, 507, 640, 479, 595, 673, 549, 392, 511, 683, 302, 429, 624, 323, 643, 673, 673, 530, 673, 673, 683, 497, 568, 623, 434, 682, 674, 682, 662, 681, 673, 631, 682, 432, 683, 612, 682, 370, 352, 639, 642, 683, 647, 646, 590, 663, 313, 638, 543, 602, 660, 673, 562, 673, 468, 641, 566, 682, 674, 606, 452, 505, 622, 642, 359, 537, 476, 620, 539, 674, 511, 643, 661, 663, 673, 389, 465, 674, 603, 446, 597, 434, 660, 673, 601, 513, 627, 660, 560, 513, 512, 673, 644, 599, 663, 555, 557, 403, 682, 382, 534, 646, 673, 577, 547, 615, 620, 466, 674, 682, 587, 433, 682, 681, 663, 644, 482, 592, 672, 557, 682, 478, 334, 507, 622, 673, 420, 615, 520, 674, 674, 587, 579, 544, 660, 337, 644, 560, 648, 566, 682, 662, 641, 659, 437, 402, 649, 525, 643, 649, 416, 682, 306, 488, 644, 570, 616, 613, 682, 592, 673, 365, 395, 335, 649, 548, 517, 524, 642, 662, 544, 661, 323, 356, 406, 616, 460, 673, 662, 497, 507, 659, 419, 645, 499, 660, 471, 558, 477, 647, 672, 662, 547, 644, 673, 426, 617, 618, 517, 364, 627, 297, 363, 625, 673, 649, 373, 674, 528, 648, 542, 483, 586, 358, 673, 443, 602, 397, 673, 354, 681, 673, 519, 645, 447, 446, 599, 628, 682, 661, 521, 626, 475, 534, 561, 512, 683, 498, 681, 562, 682, 623, 480, 598, 582, 673, 643, 581, 436, 339, 625, 682, 643, 566, 588, 556, 682, 494, 424, 673, 674, 333, 596, 545, 555, 583, 683} ;
const int Y[] =  {2, -37, -132, 123, 65, 296, 72, 42, -53, 66, -69, 122, 99, 181, 209, 19, 360, 100, -16, -132, -112, 49, 83, -43, -103, 98, -40, 22, -26, 207, 59, 6, 171, 160, 396, 175, 30, 155, 127, -132, 90, 4, -179, 130, -65, 108, -171, 238, 118, -146, -32, -122, 167, -56, 86, -33, 245, 34, 370, -11, -35, 239, 89, -145, 32, 38, -82, 26, -101, 154, -97, -41, 128, 143, 148, 240, -125, -142, 1, 151, 27, 113, 280, 127, -20, -34, -86, -67, 228, 45, 5, 306, -44, 289, 393, 368, 152, -120, 249, 382, 55, 76, 69, 213, -30, -105, 15, 416, 38, -120, -121, -163, 39, -5, -134, 113, 181, 72, 233, 176, 34, -125, 52, 333, 41, 191, 183, 110, 66, -26, 262, 259, -2, -1, -103, -82, 201, 199, 8, 324, -70, 205, 35, -128, -162, -62, -8, 39, 20, -120, -59, 80, 389, -172, 11, 73, 103, 234, -81, -129, -29, -114, -16, -66, -34, 307, -43, -137, 287, 220, 30, 313, 102, 119, -84, 65, -46, 148, 356, 315, 298, -47, -201, -141, 92, -144, -119, -63, -71, -5, 215, 337, 273, -68, 251, -8, 285, 32, -77, -19, 136, 14, 52, 138, 257, 30, 226, 137, -72, -96, 161, -57, -14, 68, 351, 302, 55, -48, 169, 166, 190, 23, 1, 274, 103, 224, -173, -23, 1, 349, 12, -40, -14, -165, 25, 212, -70, 4, -18, 237, -214, -114, 72, -171, 73, 253, 116, 71, 268, 215, 191, -94, 65, 69, -96, 363, 296, 282, 176, 381, 156, 198, 260, -98, 180, -93, 347, -54, -107, -17, 55, 219, 157, 142, -22, 267, -193, -42, -106, 100, 130, 225, 23, 120, 25, 23, 49, 307, 320, 146, -35, -53, 30, 40, -83, -135, -177, 16, -129, 270, -27, 66, 123, 254, 145, -224, 13, 202, 110, -57, 55, -89, 137, 134, 86, -12, 124, 120, 3, -18, -21, 294, 97, 63, 261, -27, -7, -190, 335, -22, -154, 129, 184, -135, -76, -51, 6, 16, 256, 286, -50, -102, 201, 365, 240, 104, -149, -9, 113, -14, 253, -168, -149, -50, 51, 177, -144, -54, 17, 362, 283, -57, -114, -103, 116, -140, 87, 12, 207, 55, 305, 209, 15, 44, -80, 33, 205, 45, 55, 215, -149, 187, -206, -131, 94, 82, -40, -79, 239, -5, 105, -66, 12, -143, 211, -77, 4, 39, 33, 189, -96, 152, -167, -88, 44, -33, -2, 235, 227, -90, -43, 58, -140, 115, -84, 98, -192, -10, 59, 160, 46, 217, -80, 76, 138, -119, -19, -8, 7, -72, 126, -225, -78, 96, 233, 224, -45, 319, 61, 191, -102, -153, -53, -89, 131, -69, 96, -204, 229, -94, 424, 258, 14, 101, -50, -53, 69, 140, 355, 179, 27, 107, -180, 96, 13, -15, 166, -81, 384, 25, 320, 58, -159, 56, -90, 187, 62, -108, -87, -138, 80, 344, 79, 52, -39, -17, 318, -107, -122, 195, 328, -145, 39, -89, -30, -87, 155} ;
const int R2[] =  {33, 47, 37, 57, 53, 53, 33, 57, 33, 47, 43, 50, 60, 40, 33, 40, 53, 47, 33, 30, 40, 57, 47, 37, 43, 37, 43, 60, 47, 50, 53, 53, 57, 33, 53, 53, 50, 47, 47, 33, 40, 53, 30, 60, 43, 50, 37, 57, 53, 33, 33, 37, 47, 53, 47, 37, 57, 43, 60, 57, 57, 50, 57, 33, 53, 57, 33, 33, 50, 60, 33, 50, 57, 43, 43, 30, 40, 30, 57, 50, 37, 60, 57, 37, 40, 50, 37, 43, 53, 53, 40, 57, 53, 60, 57, 57, 60, 30, 53, 60, 33, 40, 47, 37, 50, 40, 53, 57, 40, 30, 30, 40, 47, 50, 40, 53, 60, 53, 37, 37, 60, 40, 60, 60, 37, 43, 57, 50, 40, 43, 53, 50, 60, 37, 43, 33, 53, 37, 37, 57, 33, 37, 50, 47, 33, 40, 50, 60, 43, 37, 57, 37, 60, 37, 33, 30, 57, 60, 40, 33, 50, 43, 47, 40, 53, 60, 47, 40, 37, 60, 43, 50, 33, 40, 50, 60, 50, 53, 57, 60, 57, 40, 30, 30, 60, 33, 33, 50, 37, 40, 40, 57, 60, 57, 57, 53, 57, 40, 50, 37, 50, 30, 40, 37, 40, 47, 43, 33, 37, 33, 53, 43, 60, 57, 50, 53, 37, 43, 47, 37, 40, 40, 57, 37, 50, 47, 33, 43, 30, 57, 33, 57, 30, 30, 47, 50, 37, 53, 60, 33, 30, 37, 47, 30, 43, 50, 33, 60, 60, 47, 37, 33, 60, 50, 43, 50, 47, 53, 40, 57, 37, 57, 37, 47, 33, 30, 53, 53, 33, 33, 47, 37, 43, 57, 40, 57, 30, 30, 33, 53, 43, 50, 50, 30, 57, 37, 50, 43, 60, 60, 43, 43, 33, 33, 47, 37, 30, 47, 30, 47, 43, 37, 37, 57, 33, 30, 57, 33, 57, 40, 57, 50, 50, 30, 53, 53, 50, 40, 43, 47, 50, 60, 47, 50, 50, 47, 53, 30, 53, 57, 30, 43, 37, 30, 43, 30, 30, 53, 47, 50, 40, 37, 40, 60, 57, 53, 40, 40, 37, 47, 43, 33, 30, 40, 53, 43, 30, 33, 50, 57, 47, 33, 37, 30, 43, 33, 43, 60, 60, 57, 57, 60, 30, 30, 53, 60, 50, 60, 33, 53, 37, 40, 33, 33, 50, 57, 33, 30, 43, 37, 30, 53, 57, 37, 57, 30, 50, 53, 40, 53, 37, 37, 40, 53, 60, 40, 60, 53, 57, 43, 47, 30, 40, 43, 37, 33, 33, 43, 60, 53, 30, 53, 33, 40, 40, 43, 40, 43, 60, 47, 60, 30, 40, 50, 43, 57, 57, 50, 57, 50, 43, 30, 43, 40, 33, 40, 57, 33, 47, 47, 60, 57, 53, 43, 47, 50, 57, 60, 47, 50, 53, 53, 33, 60, 47, 57, 33, 47, 53, 60, 43, 47, 37, 43, 40, 47, 40, 30, 47, 30, 40, 57, 50, 60, 43, 50, 57, 33, 47, 40, 53, 40, 47, 43, 37, 37, 30} ;
const int R3[] =  {74, 2, 2, 60, 74, 132, 118, 60, 45, 60, 2, 89, 74, 118, 132, 60, 132, 74, 60, 16, 45, 31, 89, 74, 2, 118, 31, 16, 16, 103, 60, 45, 74, 118, 132, 103, 31, 103, 103, 45, 89, 16, 16, 45, 31, 89, 31, 89, 89, 16, 89, 31, 89, 16, 74, 60, 118, 74, 118, 2, 16, 118, 74, 45, 45, 16, 31, 89, 16, 74, 60, 16, 89, 89, 118, 132, 31, 45, 2, 103, 74, 74, 103, 118, 45, 31, 2, 60, 89, 60, 60, 103, 16, 103, 132, 132, 89, 16, 118, 118, 103, 103, 89, 118, 45, 16, 2, 132, 74, 74, 60, 16, 45, 16, 2, 60, 74, 45, 132, 132, 16, 45, 60, 118, 74, 118, 89, 74, 74, 60, 118, 132, 2, 74, 31, 74, 89, 118, 89, 118, 60, 132, 60, 2, 2, 31, 31, 45, 74, 2, 16, 89, 132, 16, 103, 103, 74, 89, 16, 2, 16, 2, 60, 2, 45, 118, 60, 31, 132, 89, 89, 132, 118, 89, 31, 60, 31, 74, 132, 103, 118, 74, 16, 31, 60, 31, 45, 2, 74, 74, 132, 118, 89, 2, 89, 16, 118, 60, 16, 60, 89, 103, 74, 103, 132, 74, 132, 132, 31, 74, 103, 2, 16, 45, 132, 118, 74, 16, 103, 103, 103, 74, 16, 132, 60, 103, 2, 45, 89, 118, 89, 31, 89, 31, 60, 118, 45, 2, 31, 132, 2, 16, 74, 2, 89, 118, 118, 31, 118, 118, 132, 31, 45, 74, 16, 132, 118, 132, 103, 132, 118, 74, 132, 16, 132, 74, 132, 2, 2, 89, 89, 132, 89, 89, 60, 103, 2, 89, 45, 60, 103, 118, 45, 118, 16, 89, 45, 132, 118, 60, 16, 31, 74, 89, 2, 45, 31, 74, 45, 118, 31, 89, 103, 103, 118, 16, 16, 118, 60, 16, 60, 16, 103, 118, 60, 31, 74, 103, 45, 31, 31, 118, 89, 60, 103, 45, 45, 16, 132, 2, 45, 89, 118, 60, 45, 74, 74, 16, 118, 132, 60, 16, 132, 132, 103, 89, 31, 60, 118, 45, 132, 31, 2, 31, 74, 118, 16, 74, 31, 118, 118, 60, 60, 45, 103, 2, 89, 45, 89, 45, 132, 103, 89, 103, 16, 2, 89, 31, 89, 89, 16, 132, 2, 31, 89, 45, 74, 74, 132, 60, 118, 2, 2, 2, 89, 45, 31, 31, 89, 103, 45, 103, 2, 2, 2, 74, 16, 118, 103, 31, 31, 103, 16, 89, 31, 103, 31, 45, 16, 89, 118, 103, 45, 89, 118, 16, 74, 74, 31, 2, 74, 2, 2, 74, 118, 89, 2, 118, 31, 89, 45, 31, 60, 2, 118, 16, 60, 16, 118, 2, 132, 118, 31, 89, 16, 16, 60, 74, 132, 103, 31, 74, 31, 31, 45, 31, 132, 31, 132, 45, 132, 74, 31, 60, 60, 118, 89, 60, 16, 2, 74, 132, 89, 45, 60, 45, 132, 31, 16, 118, 118, 2, 60, 45, 45, 60, 132} ;
const int R4[] =  {21, 15, 35, 21, 61, 61, 68, 61, 8, 15, 21, 48, 68, 41, 35, 15, 28, 21, 8, 15, 61, 21, 55, 55, 41, 68, 21, 35, 15, 35, 41, 48, 21, 28, 8, 61, 8, 48, 61, 48, 28, 21, 41, 8, 35, 55, 68, 15, 61, 35, 61, 41, 15, 55, 28, 28, 68, 41, 15, 35, 55, 48, 61, 55, 35, 15, 8, 35, 68, 41, 48, 35, 68, 15, 68, 8, 55, 41, 28, 61, 21, 61, 21, 55, 15, 41, 8, 68, 8, 48, 21, 8, 48, 28, 21, 35, 68, 8, 55, 8, 48, 61, 61, 15, 55, 35, 8, 8, 28, 68, 48, 68, 8, 15, 48, 15, 28, 15, 35, 61, 28, 68, 68, 35, 15, 48, 41, 28, 15, 48, 48, 68, 41, 35, 55, 61, 21, 21, 55, 28, 35, 48, 41, 68, 41, 21, 28, 55, 48, 28, 68, 21, 35, 61, 68, 28, 55, 28, 21, 21, 28, 48, 55, 8, 68, 48, 68, 61, 8, 35, 68, 41, 55, 15, 68, 61, 48, 21, 41, 15, 41, 68, 55, 28, 48, 41, 41, 41, 68, 48, 55, 21, 8, 68, 8, 28, 48, 8, 55, 21, 41, 55, 21, 21, 35, 55, 61, 68, 15, 68, 68, 15, 55, 28, 21, 28, 8, 15, 41, 8, 8, 35, 35, 15, 8, 15, 48, 28, 35, 15, 41, 68, 41, 41, 35, 61, 28, 15, 68, 21, 61, 28, 35, 35, 48, 41, 48, 21, 68, 48, 55, 15, 41, 48, 41, 15, 8, 68, 15, 28, 41, 8, 21, 55, 48, 55, 35, 48, 8, 55, 68, 41, 8, 61, 35, 28, 48, 55, 35, 21, 48, 55, 28, 35, 21, 48, 15, 21, 41, 21, 8, 28, 8, 28, 41, 61, 48, 61, 35, 21, 15, 28, 28, 35, 35, 68, 28, 8, 28, 8, 55, 61, 68, 28, 28, 41, 21, 41, 15, 21, 35, 55, 48, 28, 8, 41, 55, 48, 41, 41, 48, 21, 28, 55, 55, 35, 8, 15, 28, 55, 48, 21, 61, 48, 41, 68, 68, 28, 61, 35, 48, 55, 21, 15, 68, 55, 21, 48, 15, 8, 15, 28, 68, 21, 55, 28, 41, 68, 41, 35, 68, 68, 28, 41, 68, 21, 8, 35, 21, 15, 48, 68, 68, 35, 61, 21, 41, 48, 55, 15, 41, 55, 21, 41, 28, 8, 21, 15, 55, 55, 41, 15, 68, 68, 15, 61, 48, 61, 48, 48, 35, 35, 55, 28, 21, 28, 68, 21, 15, 41, 68, 41, 21, 35, 61, 55, 55, 61, 55, 35, 55, 68, 15, 35, 28, 21, 55, 8, 15, 15, 68, 35, 61, 21, 41, 15, 35, 68, 41, 48, 15, 61, 28, 35, 28, 41, 48, 48, 8, 48, 21, 41, 61, 8, 21, 55, 55, 55, 15, 61, 15, 41, 61, 8, 68, 61, 41, 41, 48, 15, 8, 48, 68, 48, 55, 48, 61, 21, 68, 35, 15, 55, 28, 61, 8, 55, 48} ;

int minx, miny, minr1, minr2, minr3, minr4;//minr1 not used

byte b;
int rs = 0;
int rs_coord = 0;
int r_sys = 0, r_cmd = 0, e_sys = 0, e_cmd = 0;
int f_b_x, s_b_x, f_b_y, s_b_y, f_b_z, s_b_z;
int x, y, z;

int r1, r2, r3, r4;
const int k = 25;

int motor = 2;
int steps = 0;


void setup()
{
  servo.write(50);
  
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  myStepper3.setSpeed(60);
  myStepper4.setSpeed(60);

  servo.attach(10);

  Serial.begin(9600);

  analogWrite(2, 255);
  analogWrite(3, 255);
  analogWrite(4, 255);
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(7, 255);
  analogWrite(8, 255);
  analogWrite(9, 255);

  //  digitalWrite(FAN1, 1);
  //  digitalWrite(LIGHT, 1);
  //  digitalWrite(VACUUM, 1);
}

void log()
{
  Serial.println("b\trs\tr_sys\tr_cmd\te_sys\te_cmd");
  Serial.print(b);      Serial.print("\t");
  Serial.print(rs);     Serial.print("\t");
  Serial.print(r_sys);  Serial.print("\t");
  Serial.print(r_cmd);  Serial.print("\t");
  Serial.print(e_sys);  Serial.print("\t");
  Serial.print(e_cmd);  Serial.print("\t");
  Serial.println("");
  
  Serial.println("f_b_x\ts_b_x\tx\tf_b_y\ts_b_y\ty\tf_b_z\ts_b_z\tz");
  Serial.print(f_b_x);  Serial.print("\t");
  Serial.print(s_b_x);  Serial.print("\t");
  Serial.print(x);      Serial.print("\t");
  Serial.print(f_b_y);  Serial.print("\t");
  Serial.print(s_b_y);  Serial.print("\t");
  Serial.print(y);      Serial.print("\t");
  Serial.print(f_b_z);  Serial.print("\t");
  Serial.print(s_b_z);  Serial.print("\t");
  Serial.print(z);      Serial.print("\t");
  Serial.println("");
  Serial.println("");
}

void initialization()
{
//  switch (motor)
//  {
//    case 2:
//      {
//        myStepper2.step(-10);
//        if (steps++ > 150)
//        {
//          motor = 3;
//          steps = 0;
//          stepper2_stop();
//        }
//        break;
//      }
//    case 3:
//      {
//        myStepper3.step(-10);
//        if (steps++ > 330)
//        {
//          motor = 4;
//          steps = 0;
//          stepper3_stop();
//        }
//        break;
//      }
//    case 4:
//      {
//        myStepper4.step(10);
//        if (steps++ > 170)
//        {
//          motor = 0;
//          steps = 0;
//          stepper4_stop();
//        }
//        break;
//      }
//  }
//
//  if (motor == 0)
//  {
    r2 = 60;
    stepper2_go(59);
    r3 = 132;
    stepper3_go(130);
    r4 = 68;
    stepper4_go(60);

    Serial.println(r2);
    Serial.println(r3);
    Serial.println(r4);
    
    servo.write(50);
    
//    stepper2_stop();
//    stepper3_stop();
//    stepper4_stop();
    
    motor = 2;
    steps = 0;
    e_cmd = 0;
    e_sys = 0;
    log();
  //}
}

void stepper1_stop()
{
  digitalWrite(44, 0);
  digitalWrite(42, 0);
  digitalWrite(40, 0);
  digitalWrite(38, 0);
}
void stepper2_stop()
{
  digitalWrite(52, 0);
  digitalWrite(50, 0);
  digitalWrite(48, 0);
  digitalWrite(46, 0);
}
void stepper3_stop()
{
  digitalWrite(45, 0);
  digitalWrite(43, 0);
  digitalWrite(41, 0);
  digitalWrite(39, 0);
}
void stepper4_stop()
{
  digitalWrite(53, 0);
  digitalWrite(51, 0);
  digitalWrite(49, 0);
  digitalWrite(47, 0);
}

void stepper2_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 60) pos = 60;
  if (pos != r2)
  {
    myStepper2.step(-(pos - r2)*k);
  }
  stepper2_stop();
  r2 = pos;
}

void stepper3_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 132) pos = 132;
  if (pos != r3)
  {
    myStepper3.step(-(pos - r3)*k);
  }
  stepper3_stop();
  r3 = pos;
}

void stepper4_go(int pos)
{
  if (pos < 0) pos = 0;
  if (pos > 68) pos = 68;
  if (pos != r4)
  {
    myStepper4.step((pos - r4)*k);
  }
  stepper4_stop();
  r4 = pos;
}

void reverse(int x, int y)
{
  int mind = 10000;
  for (int i = 0; i < 498; i++)
  {

    float d = sqrt(pow(X[i] - x, 2) + pow(Y[i] - y, 2));

    if (d < mind)
    {
      mind = d;
      minx = X[i];
      miny = Y[i];
      minr2 = R2[i];
      minr3 = R3[i];
      minr4 = R4[i];
    }
  }
}

void loop()
{

  if (Serial.available() > 0)
  {
    b = Serial.read();

    switch (rs)
    {
      case 0:
      {
        if (b == 48)
        {
          rs++;
        }
        else
        {
          b = 5;
          Serial.println("not first synchro");
        }
        break;
      }
      case 1:
      {
        if (b == 48)
        {
          rs++;
        }
        else
        {
          rs = 0;
          Serial.println("not second synchro ");
        }
        break;
      }
      case 2:
        if (r_sys == 0)
          r_sys = b;
        else
        {
          switch (r_sys)
          {
            case 49:
              {
                if (r_cmd == 0)
                {
                  r_cmd = b;
                  switch (r_cmd) //without parametrs
                  {
                    case 49:
                    {
                      //inicialization
                      rs++;
                      break;
                    }
                    case 50:
                    {
                      //stop
                      rs++;
                      break;
                    }
                    case 52:
                    {
                      //servo close
                      rs++;
                      break;
                    }
                    case 53:
                    {
                      //servo open
                      rs++;
                      break;
                    }
                  }
                }
                else
                {
                  switch (r_cmd)//with parametrs
                  {
                    case 51:
                      {
                        //coordinates
                        switch(rs_coord)
                        {
                          // X //
                          case 0:
                          {
                            f_b_x = b;
                            rs_coord++;
                            break;
                          }
                          case 1:
                          {
                            s_b_x = b;
                            x = f_b_x;
                            x = x << 8;
                            x = x | s_b_x;
                            rs_coord++;
                            break;
                          }
                          // Y //
                          case 2:
                          {
                            f_b_y = b;
                            rs_coord++;
                            break;
                          }
                          case 3:
                          {
                            s_b_y = b;
                            y = f_b_y;
                            y = y << 8;
                            y = y | s_b_y;
                            rs_coord++;
                            break;
                          }
                          // Z //
                          case 4:
                          {
                            f_b_z = b;
                            rs_coord++;
                            break;
                          }
                          case 5:
                          {
                            s_b_z = b;
                            z = f_b_z;
                            z = z << 8;
                            z = z | s_b_z;
                            rs++;
                            rs_coord = 0;
                            break;
                          }
                        }                        
                        
                        break;
                      }
                    default:
                      {
                        Serial.println("number command  not found ");
                        r_sys = 0;
                        r_cmd = 0;
                        rs = 0;
                      }
                  }
                }
              }
              break;
            default:
              {
                Serial.println("number system  not found ");
                r_sys = 0;
                r_cmd = 0;
                rs = 0;
              }
          }
        }
        break;

      case 3:
        if (b == 102) rs++;
        else
        {
          rs = 0;
          r_sys = 0;
          r_cmd = 0;
          Serial.println("not first end synchro ");
        }
        break;
      case 4:
        rs = 0;
        if (b == 102)
        {
          e_sys = r_sys;
          e_cmd = r_cmd;
          r_sys = 0;
          r_cmd = 0;
          Serial.println("command successful recive ");
        }
        else
        {
          Serial.println("not second end synchro ");
          r_sys = 0;
          r_cmd = 0;
        }
        break;
    }
    log();
  }
  else
  {
    switch (e_sys)
    {
      case 49:
        switch (e_cmd)
        {
          case 49:
            initialization();
            Serial.print("inicialization step ");
            Serial.print(steps);
            Serial.println("");
            break;
          case 50:
            stepper1_stop();
            stepper2_stop();
            stepper3_stop();
            stepper4_stop();
            motor = 2;
            steps = 0;
            e_cmd = 0;
            e_sys = 0;
            log();
            Serial.println("stop");
            break;
          case 51:
            Serial.println("Stepper_go");
            reverse(x, y);
            Serial.println(r2);
            Serial.println(minr2);
            Serial.println();
            stepper2_go(minr2);
            Serial.println(r3);
            Serial.println(minr3);
            Serial.println();
            stepper3_go(minr3);
            Serial.println(r3);
            Serial.println(minr4);
            Serial.println();
            stepper4_go(minr4);
            e_cmd = 0;
            e_sys = 0;
            log();
            break;
          case 52:
            Serial.println("servo close");
            servo.write(50);
            e_cmd = 0;
            e_sys = 0;
            log();
            break;
          case 53:
            Serial.println("servo open");
            servo.write(20);
            e_cmd = 0;
            e_sys = 0;
            log();
            break;
          default:
            Serial.println("command not selected");
        }
        break;

//      default://inaction
//        Serial.println("system not selected");
//        delay(1000);
    }
  }

}
