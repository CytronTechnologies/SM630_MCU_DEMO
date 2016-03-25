#include "Include.h"

//
//P32 P33 P34 P35 

//


sbit K_CANCEL=P3^2;
sbit K_UP=P3^3;
sbit K_DOWN=P3^4;
sbit K_ENTER=P3^5;

unsigned char NowKey=NO_KEY;

void KeyTest(void)
{
        while(1)
        {
                if(NowKey != NO_KEY)
                {
                        //
                        BellOn();
                        DelayNmS(200);
                        BellOff();
                        //
                        NowKey = NO_KEY;
                }
        }
}