#include "Include.h"

//
//
//

sbit LED_RED=P1^1;
sbit LED_BLUE=P1^0;

void LedInit(void)
{
        LedRedOff();
        LedBlueOff();
}

void LedRedOn(void)
{
        LED_RED=0;
}

void LedRedOff(void)
{
        LED_RED=1;
}

void LedBlueOn(void)
{
        LED_BLUE=0;
}

void LedBlueOff(void)
{
        LED_BLUE=1;
}

void LedTest(void)
{
        while(1)
        {
                LedRedOn();
                DelayNmS(200);
                LedRedOff();
                DelayNmS(200);
                LedBlueOn();
                DelayNmS(200);
                LedBlueOff();
                DelayNmS(200);
        }
}