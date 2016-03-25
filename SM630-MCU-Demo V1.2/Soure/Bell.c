#include "Include.h"

//
//

extern unsigned char BellTimer;

sbit BELL=P1^7;

void BellInit(void)
{
        BellOff();
}

void BellOn(void)
{
        BellTimer = 0;
        BELL=0;
}

void BellOff(void)
{
        BELL=1;
}
/*
void BellTest(void)
{
        while(1)
        {
                BellOn();
                DelayNmS(200);
                BellOff();
                DelayNmS(200);
        }
} */