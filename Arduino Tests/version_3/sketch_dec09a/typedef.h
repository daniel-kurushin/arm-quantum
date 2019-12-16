#ifndef typedef_h
#define typedef_h

enum ENReaderState
{
    SYNC0, SYNC1, CMD, LEN, VALLOW, VALHIGH, END, ERR
}; 

enum ENGlobalState
{
    INIT, READY, ROTZ, MOVE0, MOVE1, MOVE2 , STOP, XBAT, UNXBAT, MEASURE, FAIL
};

enum ENInitState 
{
    PORTS, ZAXIS, STEPPER1, STEPPER2, STEPPER3, INIT_OK
};

enum ENZRotState 
{
    Z_IDLE, LESS, GREATER, INPOS, ROTFAIL
};

enum CMD
{
    CMD_NONE, CMD_MOVE_XYZ, CMD_MEASURE, CMD_XBAT, CMD_UNXBAT
};

const String tm_msgRS[ 8] = 
{
    "SYNC0", 
    "SYNC1", 
    "CMD", 
    "LEN", 
    "VALLOW", 
    "VALHIGH", 
    "END", 
    "ERR"
};

const String tm_msgGS[11] = {
    "INIT", 
    "READY", 
    "ROTZ", 
    "MOVE0", 
    "MOVE1", 
    "MOVE2", 
    "STOP", 
    "XBAT", 
    "UNXBAT", 
    "MEASURE", 
    "ERR"
};

const String tm_msgCMD[5] = {
    "CMD_NONE",
    "CMD_MOVE_XYZ", 
    "CMD_MEASURE", 
    "CMD_XBAT", 
    "CMD_UNXBAT"
};

ENInitState do_init();
void telemetry(int RS, int GS, char c, int cmd, int len, int val, int nval, int high, int low);

float z_measure();
void reverse(int x, int y);
void all_steppers_off();
int z_stepper_go(float target_pos);
int x, y, z, l;
int xvat;

ENReaderState RS = SYNC0;
ENGlobalState GS = INIT;
int cmd, len, val, nval;
uint8_t low, high;
int values[10]; // сюда значения
int pos = 0;    // индекс
ENZRotState z_rot_state = Z_IDLE;
int z_oldpos = 0;

#endif

