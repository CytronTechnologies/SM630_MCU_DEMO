#include "Include.h"

extern unsigned char NowKey;//

extern unsigned char Timer;//
extern unsigned char Timer2;//
extern unsigned char BellTimer;

sbit FINGER_POWER=P1^6;//

unsigned char FingerRecord[26];//
unsigned char xdata CommBuf[MAX_BUF_NUMBER];//

//
void FingerOn(void)
{
        FINGER_POWER=0;
        DelayNuS(10);
}

//
void FingerOff(void)
{
        FINGER_POWER=1;
        DelayNuS(10);
}

//
void FingerReset(void)
{
        FingerOff();
        DelayNmS(50);
        FingerOn();
        DelayNmS(250);
}

//
void FingerInit(void)
{
        UARTInit();
        FingerOff();

        memset(FingerRecord,0,sizeof(FingerRecord));//
}

//
//
//
//      Number:
//      p£º
//      OutTime£º
//
//      1£º
//      0£º
//      2£º
unsigned char ReceiveData(unsigned char *p,unsigned char OutTime)
{
        unsigned char Sum = 0;
        unsigned char i = 0;
        unsigned char Number = 0;

        Timer = OutTime;
        RI = 0;

        //
        while(1)
        {
                if(1 == RI)
                {
                        RI = 0;
                        if(SBUF == 'M')
                        {
                                *p = 'M';
                                Sum += *p;
                                p++;
                                Timer = 2;//
                                break;
                        }
                        else
                        {
                                return FALSE;//
                        }
                }
                if(0 == Timer)
                {
                        return TIMEOUT;//
                }
        }
        while(1)
        {
                if(1 == RI)
                {
                        RI = 0;
                        if(SBUF == 'X')
                        {
                                *p = 'X';
                                Sum += *p;
                                p++;
                                Timer = 2;//
                                break;
                        }
                        else
                        {
                                return FALSE;//
                        }
                }
                if(0 == Timer)
                {
                        return TIMEOUT;//
                }
        }

        //
        while(1)
        {
                if(1 == RI)
                {
                        RI = 0;
                        *p = SBUF;
                        Sum += *p;
                        p++;
                        Timer = 2;//
                        break;
                }
                if(0 == Timer)
                {
                        return TIMEOUT;//
                }
        }

        //
        while(1)
        {
                if(1 == RI)
                {
                        RI = 0;
                        *p = SBUF;
                        Sum += *p;
                        Number = *p;
                        p++;
                        Timer = 2;//
                        break;
                }
                if(0 == Timer)
                {
                        return TIMEOUT;//
                }
        }

        //
        for(i = 0;i<Number;i++)
        {
                while(1)
                {
                        if(1 == RI)
                        {
                                RI = 0;
                                *p = SBUF;
                                Sum += *p;
                                p++;
                                Timer = 2;//
                                break;
                        }
                        if(0 == Timer)
                        {
                                return TIMEOUT;//
                        }
                }
        }

        //
        while(1)
        {
                if(1 == RI)
                {
                        RI = 0;
                        *p = SBUF;
                        if(Sum == *p)
                        {
                                return OK;
                        }
                        return FALSE;
                }
                if(0 == Timer)
                {
                        return TIMEOUT;//
                }
        }
}

//
//
//
//      BaoBS£º
//      Number£º
//      p£º
//
//      1£º
//      0£º
//      2£º
unsigned char SendCommand(unsigned char BaoBS,unsigned char Number,unsigned char *p)
{
        unsigned char i = 0;
        unsigned char Sum = 0;
        unsigned char* pt = p;

        if(Number>MAX_LR_NUMBER)
        {
                return FALSE;//
        }

        //
        UARTSendByte('M');
        Sum += 'M';
        UARTSendByte('X');
        Sum += 'X';

        //
        UARTSendByte(BaoBS);
        Sum += BaoBS;

        //
        UARTSendByte(Number);
        Sum += Number;

        //
        for(i = 0;i<Number;i++)
        {
                UARTSendByte(*p);
                Sum += *p;
                p++;
        }

        //
        UARTSendByte(Sum);

        //
        i = ReceiveData(pt,5);

        if((OK == i) && (pt[4] == C_GET_OK))
        {
                return OK;
        }

        if(pt[4] == C_GET_FAIL)
        {
                return FALSE;
        }

        return TIMEOUT;
}

//
//
//      AddrH£º
//      AddrL£º
//      OutTime£º
//
//      
unsigned char AddFinger(unsigned char AddrH,unsigned char AddrL,unsigned char OutTime)
{
        unsigned char i = 0;
        CommBuf[0] = C_ADD_FINGER;
        CommBuf[1] = AddrH;
        CommBuf[2] = AddrL;

        i = SendCommand(C_COMMAND,3,CommBuf);//

        if(i != OK)
        {
                return FALSE;
        }

        if(OK == ReceiveData(CommBuf,OutTime))
        {
                if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_ADD_FINGER == CommBuf[4]))
                {
                        //
                        if(ANSWER_OK == CommBuf[5])
                        {
                                //
                                BellOn();
                                BellTimer = 6;//
                        }
                        else
                        {
                                return CommBuf[5];//
                        }
                }
                else
                {
                        return FALSE;
                }                
        }
        else
        {
                return FALSE;
        }

        if(OK == ReceiveData(CommBuf,OutTime))
        {
                if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_ADD_FINGER == CommBuf[4]))
                {
                        //
                        return CommBuf[5];//
                }
                else
                {
                        return FALSE;
                }                
        }
        else
        {
                return FALSE;
        }
}

//
//
//      p£º
//      OutTime£º
//
//      
unsigned char SearchFinger(unsigned char *p,unsigned char OutTime)
{
        unsigned char i = 0;
        CommBuf[0] = C_SEARCH_FINGER;
        CommBuf[1] = 0;
        CommBuf[2] = 0;
        CommBuf[3] = 0;
        CommBuf[4] = MAX_FINGER;//

        i = SendCommand(C_COMMAND,5,CommBuf);//

        if(i != OK)
        {
                return FALSE;
        }
        
        //
        if(OK == ReceiveData(CommBuf,OutTime))
        {
                if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_SEARCH_FINGER == CommBuf[4]))
                {
                        //
                        if(ANSWER_OK == CommBuf[5])
                        {
                                //
                                BellOn();
                                BellTimer = 6;//
                        }
                        else
                        {
                                return CommBuf[5];//
                        }
                }
                else
                {
                        return FALSE;
                }
        }
        else
        {
                return FALSE;
        }

        if(OK == ReceiveData(CommBuf,OutTime))
        {
                if((C_ANSWER == CommBuf[2])&&(C_SEARCH_FINGER == CommBuf[4]))
                {
                        //
                        if(ANSWER_SEARCH_OK == CommBuf[5])
                        {
                                //
                                *p = CommBuf[7];
                                return CommBuf[5];//
                        }
                        else
                        {
                                return CommBuf[5];//
                        }
                }
                else
                {
                        return FALSE;
                }
        }
        else
        {
                return FALSE;
        }

}

//
//
//      
//      
unsigned char EmptyFinger(void)
{
        unsigned char Command = C_EMPTY_FINGER;

        //
        if(SendCommand(C_COMMAND,1,&Command)!=OK)
        {
                return FALSE;
        }
        
        if(OK == ReceiveData(CommBuf,5))
        {
                if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_EMPTY_FINGER == CommBuf[4]))
                {
                        return OK;
                }
        }
        return FALSE;
}

//
//
//      p£º
//      Number£º
//      AddrH£º
//      AddrL£º
//
//      OK£º
//    
unsigned char WriteFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL)
{
        CommBuf[0] = C_WRITE_FLASH;
        CommBuf[1] = AddrH;
        CommBuf[2] = AddrL;
        CommBuf[3] = Number;

        memcpy(&CommBuf[4],p,Number);

        if(SendCommand(C_COMMAND,Number+4,CommBuf)!=OK)//
        {
                return FALSE;
        }
        
        if(OK == ReceiveData(CommBuf,5))
        {
                if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_WRITE_FLASH == CommBuf[4]))
                {
                        return OK;
                }
        }
        return FALSE;
}

//
//
//      p£º
//      Number£º
//      AddrH£º
//      AddrL£º
//
//      OK£º
//      
unsigned char ReadFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL)
{
        unsigned char Command = C_READ_FLASH;

        CommBuf[0] = C_READ_FLASH;
        CommBuf[1] = AddrH;
        CommBuf[2] = AddrL;
        CommBuf[3] = Number;

        if(SendCommand(C_COMMAND,4,CommBuf)!=OK)//
        {
                return FALSE;
        }
     
        if(OK == ReceiveData(CommBuf,5))
        {
                if((C_ANSWER == CommBuf[2])&&(C_READ_FLASH == CommBuf[4]))
                {
                        memcpy(p,&CommBuf[5],Number);//
                        return OK;
                }
        }
        return FALSE;
}
