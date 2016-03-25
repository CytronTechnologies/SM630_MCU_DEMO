#include "Include.h"

extern unsigned char NowKey;				//
extern unsigned int  Tc;					//
extern unsigned char Timer;					//
extern unsigned char Timer2;				//
extern unsigned char BellTimer;
extern unsigned char Rx_Cnt;				//

extern	bit		ReceiveOK;					//


sbit FINGER_POWER=P1^6;						//

unsigned char FingerRecord[26];				//
unsigned char xdata CommBuf[MAX_BUF_NUMBER];//
unsigned char xdata SCC;					//
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
/*
//
void FingerReset(void)
{
        FingerOff();
        DelayNmS(50);
        FingerOn();
        DelayNmS(250);
}
*/
//
void FingerInit(void)
{
        UARTInit();
        FingerOff();

        memset(FingerRecord,0,sizeof(FingerRecord));//
}
//
void Clear_Uart_Variable(void)
{
		ReceiveOK = 0;
		Rx_Cnt = 0;	
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
		return	0;
}

//
//
//      OK£º
//      
unsigned char EmptyFinger(void)
{
        unsigned char Command = C_EMPTY_FINGER;

		Clear_Uart_Variable();
		SendCommand(C_COMMAND,1,&Command);

		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4])				//
		{
			if((C_ANSWER==CommBuf[2])&&(0x01==CommBuf[4]))
			{
				;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
		}

		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4]) 					//
		{
			if((C_ANSWER==CommBuf[2])&&(C_EMPTY_FINGER==CommBuf[4]))
			{				
				return OK;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
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

		Clear_Uart_Variable();
		SendCommand(C_COMMAND,Number+4,CommBuf);

		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4])				//
		{
			if((C_ANSWER==CommBuf[2])&&(0x01==CommBuf[4]))
			{
				;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
		}

		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4])					//
		{
			if((C_ANSWER==CommBuf[2])&&(C_WRITE_FLASH==CommBuf[4]))
			{				
				return OK;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
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
		//
		Clear_Uart_Variable();
		SendCommand(C_COMMAND,4,CommBuf);

		//
		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4]) 				//
		{
			if((C_ANSWER==CommBuf[2])&&(0x01==CommBuf[4]))
			{
				;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
		}

		//
		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if(0==Tc)	return	FALSE;

		if(SCC==CommBuf[CommBuf[3]+4]) 					//
		{
			if((C_ANSWER==CommBuf[2])&&(C_READ_FLASH==CommBuf[4]))
			{
                memcpy(p,&CommBuf[5],Number);//				
				return OK;	
			}
			else
			{
				return	ANSWER_NUMBER_E;
			}
		}
		else
		{
			return	C_GET_FAIL;
		}

        return FALSE;
}
