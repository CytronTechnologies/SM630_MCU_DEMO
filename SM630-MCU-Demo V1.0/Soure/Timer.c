#include "Include.h"

//Timer0
//

unsigned char Timer = 0;
unsigned char Timer2 = 0;
unsigned char BellTimer = 0;
extern unsigned char NowKey;//

sbit K_CANCEL=P3^2;
sbit K_UP=P3^3;
sbit K_DOWN=P3^4;

//
void EnableT0(void)
{
	ET0=1;
}

//
void DisT0(void)
{
	ET0=0;
}

//Timer0
void Timer0Start(void)
{
	TR0=1;
}

//Timer0
void Timer0Stop(void)
{
	TR0=0;
}

//Timer0
void Timer0Init(void)
{
	TMOD|=1;//
	TH0=0;
	TL0=0;

	EnableT0();
	Timer0Start();
}

unsigned int Tc=0;//

unsigned char KeyStep[4]={0,0,0,0};//

//
//0  
//1  
//2  

//
void ISRTimer0(void) interrupt 1
{
	TH0=0;
	TL0=0;

        //
        //-------------------------------------------------
        if(0==K_CANCEL)
        {
                if(1==KeyStep[0])
                {
                        KeyStep[0]=2;//
                        NowKey=EMPTY_KEY;//
                }
                else
                {
                        KeyStep[0]=1;
                }
        }
        else
        {
                if(NowKey!=EMPTY_KEY)
                {
                        KeyStep[0]=0;
                }
        }
        if(0==K_UP)
        {
                if(1==KeyStep[1])
                {
                        KeyStep[1]=2;//
                        NowKey=ADD_KEY;//
                }
                else
                {
                        KeyStep[1]=1;
                }
        }
        else
        {
                if(NowKey!=ADD_KEY)
                {
                        KeyStep[1]=0;
                }
        }
        if(0==K_DOWN)
        {
                if(1==KeyStep[2])
                {
                        KeyStep[2]=2;//
                        NowKey=SEARCH_KEY;//
                }
                else
                {
                        KeyStep[2]=1;
                }
        }
        else
        {
                if(NowKey!=DEL_KEY)
                {
                        KeyStep[2]=0;
                }
        }
        //-------------------------------------------------


	if(Tc>0)
	{
		Tc++;
	}

        if(Timer>0)
        {
                Timer--;
        }
        if(Timer2>0)
        {
                Timer2--;
        }

        if(BellTimer>0)
        {
                BellTimer--;
                if(0 == BellTimer)
                {
                        BellOff();
                }
        }
}