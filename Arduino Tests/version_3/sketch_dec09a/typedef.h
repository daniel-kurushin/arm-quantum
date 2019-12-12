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
    ZAXIS, ARM, HAND
};

enum ENZRotState 
{
    Z_IDLE, LESS, GREATER, INPOS, ROTFAIL
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

const String tm_msgGS[10] = {
    "INIT", 
    "READY", 
    "ROTZ", 
    "MOVEARM", 
    "MOVEHAND", 
    "STOP", 
    "XBAT", 
    "UNXBAT", 
    "MEASURE", 
    "ERR"
};

void imhostep(int dir);
void do_init();
void telemetry(int RS, int GS, char c, int cmd, int len, int val, int nval, int high, int low);
ENZRotState z_rotate(int pos);
float z_measure();

const int Z_MIN = 52
const int Z_MIDDLE = 257
const int Z_MAX = 452

ENReaderState RS = SYNC0;
ENGlobalState GS = INIT;
int cmd, len, val, nval;
uint8_t low, high;
int values[10]; // сюда значения
int pos = 0;    // индекс
ENZRotState z_rot_state = Z_IDLE;
int z_oldpos = 0;

#endif

