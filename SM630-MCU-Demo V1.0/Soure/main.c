#include "Include.h"

//---------------------------------------------------------
//
//---------------------------------------------------------

//---------------------------------------------------------
/*
This demo is for Miaxis SM-630 module on 51 platform, to realize fingerprint enrollment, clearance and search. Users can make revisions and develop own fingerprint system. If more funtions needed, please refer to this demo, and read the user manual carefully. 
*/
//---------------------------------------------------------

//---------------------------------------------------------
//
//---------------------------------------------------------

//---------------------------------------------------------
//Version��V1.0
//Date��20070816
//Author��Yang
//---------------------------------------------------------

extern unsigned char NowKey;// 
extern unsigned char xdata CommBuf[MAX_BUF_NUMBER];// 

// 
void EnableInterrupt(void)
{
	EA = 1;
}

// 
void DisInterrupt(void)
{
	EA = 0;
}

// 
void SystemInit(void)
{
        FingerInit();
        UARTInit();
        Timer0Init();
        BellInit();
        LedInit();

        // 
        EnableInterrupt();

		//
		BellOn();
		LedRedOn();
		LedBlueOn();
		DelayNmS(200);
		LedRedOff();
		LedBlueOff();
		BellOff();
}

void main(void)
{
        SystemInit();

        while(0)
        {
                KeyTest();
                LedTest();
                BellTest();
        }

        while(1)
        {
                switch (NowKey)
                {
                        case ADD_KEY:
                                AddFingerModule();
                                NowKey = NO_KEY;
                                break;
                        case EMPTY_KEY:
                                EmptyFingerModule();
                                NowKey = NO_KEY;
                                break;
                        case SEARCH_KEY:
                                SearchFingerModule();
                                NowKey = NO_KEY;
                                break;
                        default:
                                break;
                }
        }
}
