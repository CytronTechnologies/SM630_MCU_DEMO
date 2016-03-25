#include "Include.h"

extern unsigned char FingerRecord[26];//

//
void DisplayOK(void)
{
        unsigned char i = 0;

        for(i=0;i<3;i++)
        {
                BellOn();
                LedBlueOn();
                DelayNmS(50);
                BellOff();
                LedBlueOff();
                DelayNmS(50);
        }
}

//
void DisplayFail(void)
{
        unsigned char i = 0;

        for(i=0;i<2;i++)
        {
                BellOn();
                LedRedOn();
                DelayNmS(200);
                BellOff();
                LedRedOff();
                DelayNmS(200);
        }
}

//
void DisplayErr(void)
{
        unsigned char i = 0;

        for(i=0;i<2;i++)
        {
                BellOn();
                LedRedOn();
                LedBlueOn();
                DelayNmS(200);
                BellOff();
                LedRedOff();
                LedBlueOff();
                DelayNmS(200);
        }
}

//
void DisplayOutTime(void)
{
        unsigned char i = 0;

        for(i=0;i<3;i++)
        {
                BellOn();
                LedRedOn();
                DelayNmS(200);
                BellOff();
                LedRedOff();
                DelayNmS(200);
        }
}

//
void EmptyFingerModule(void)
{
        //1 
        memset(FingerRecord,0,sizeof(FingerRecord));

        FingerOn();
        BellOn();
        DelayNmS(200);
        BellOff();

        //2 
        if(OK == WriteFingerFlash(FingerRecord,sizeof(FingerRecord),0,0))
        {
        }
        else
        {
                DisplayErr();
                FingerOff();
                return;
        }

        //3 
        if(OK == EmptyFinger())
        {
                DisplayOK();
        }
        else
        {
                DisplayErr();
        }

        FingerOff();
}

void SearchFingerModule(void)
{
        unsigned char SearchResult = 0;
        unsigned char SearchReturn = 0;

        FingerOn();
		BellOn();
        DelayNmS(200);
		BellOff();

        //
        SearchReturn = SearchFinger(&SearchResult,250);

        if(ANSWER_SEARCH_OK == SearchReturn)//
        {
                DisplayOK();
        }
        else
        {
                if((ANSWER_SEARCH_FAIL == SearchReturn)||(ANSWER_FAIL == SearchReturn))//
                {
                        DisplayFail();
                }
                else
                {
                        if(ANSWER_OUT_TIME == SearchReturn)
                        {
                                DisplayOutTime();//
                        }
                        else
                        {
                                DisplayErr();//
                        }
                }
        }

        FingerOff();
}

void AddFingerModule(void)
{
        unsigned char i = 0;
        unsigned char AH = 0;//
        unsigned char AL = 0;//
        unsigned char t = 0;

        FingerOn();
		BellOn();
        DelayNmS(200);
		BellOff();

        //
        if(ReadFingerFlash(FingerRecord,sizeof(FingerRecord),0,0) != OK)
        {
                DisplayErr();
                FingerOff();
                return;
        }

        //2 
        for(i = 0;i<MAX_FINGER;i++)
        {
                AH = i/8;
                AL = i%8;
                t = FingerRecord[AH]<<(7-AL);
                t = t>>7;
                if(0 == t)
                {
                        //
                        break;
                }
        }

        if(i == MAX_FINGER)
        {
                //
                DisplayFail();
                FingerOff();
                return;
        }

        //3
        t = AddFinger(0,i,250);
        if(ANSWER_OK == t)
        {
                DisplayOK();//
        }
        else
        {
                if(ANSWER_OUT_TIME == t)//
                {
                        DisplayOutTime();
                        FingerOff();
                        return;
                }
                else
                {
                        if(FALSE == t)//
                        {
                                DisplayErr();
                                FingerOff();
                                return;
                        }
                        else
                        {
                                DisplayFail();//
                                FingerOff();
                                return;
                        }
                }
        }

        //4 
        FingerRecord[AH] |= 1<<AL;
        if(OK == WriteFingerFlash(FingerRecord,sizeof(FingerRecord),0,0))
        {
        }
        else
        {
                DisplayErr();
                FingerOff();
                return;
        }

        FingerOff();//
}
