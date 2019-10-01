/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int R1[] = {190, 197, 204, 211, 218, 225, 232, 239, 246, 253, 260};
int X1[] = {319, 305, 289, 269, 247, 221, 192, 152, 118, 71, 14};
int Y1[] = {180, 207, 234, 260, 226, 312, 336, 360, 381, 400, 414};

int R2[] = {225, 238, 251, 264, 277, 290, 303, 316, 329, 342, 355};
int X2[] = {69, 149, 190, 231, 265, 294, 320, 343, 363, 380, 394};  
int Y2[] = {-416, -394, -376, -353, -328, -301, -274, -244, -214, -182, -142};
  
int R3[] = {200, 207, 214, 221, 228, 235, 242, 249, 256, 263, 270};
int X3[] = {86, 100, 108, 113, 116, 119, 120, 120, 119, 117, 115};  
int Y3[] = {83, 66,  52,  40,  28,  17,  6,   -5, -15, -25, -35};

int x, y;

void setup()
{
    //cin>>x;
    //cin>>y;
    x = 500;
    y = -260;
}

int mind = 1000;
int minr1;
int minr2;
int minr3;

void loop()
{
    for(int i = 0; i<11; i++)
    {
        for(int j = 0; j<11; j++)
        {
            for(int k = 0; k<11; k++)
            {
                int x0 = X1[i] + X2[j] + X3[k];
                int y0 = Y1[i] + Y2[j] + Y3[k];
                float d = sqrt(pow(x0 - x, 2) + pow(y0 - y, 2));
                
                if(d<mind)
                {
                    cout<<mind<<endl;
                    mind = d;
                    minr1 = R1[i];
                    minr2 = R2[j];
                    minr3 = R3[k];
                }
            }
        }
    }
    cout<<minr1<<" "<<minr2<<" "<<minr3<<endl;
}

int main()
{
    setup();
    while(1)
    {
        loop();
        return 0;
    }
    
}

