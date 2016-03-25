#include "Include.h"

extern	unsigned char xdata CommBuf[MAX_BUF_NUMBER];//
extern	unsigned char xdata SCC;					//
extern	unsigned char Timer;
unsigned char	Rx_Cnt=0;							//

bit		ReceiveOK = 0;								//


//
//
void UARTInit(void)
{
        SCON=0X50;    //
        T2CON=0X30;
        RCAP2H=0XFF;
        RCAP2L=0XFA;
        TH2=0XFF;
        TL2=0XFA;
		ES = 1;
        TR2 = 1;
}

//
void UARTSendByte(unsigned char i)
{
	SBUF=i;
	while(0==TI) {;}
        TI=0;
}

void	IRQ_UartGet(void)	interrupt	4
{
	unsigned char	i;
	
	if(RI==1)
	{
		RI = 0;
		i = SBUF;

	 	if(!ReceiveOK)
		{
			if(0==Rx_Cnt)
			{
				if(PKG_MARK1==i)
				{
					Timer = UART_OUT_TIME;
					CommBuf[Rx_Cnt++] = i;
					SCC = i;
				}			  
			}
			else if(1==Rx_Cnt)
			{
				if(PKG_MARK2==i)
				{
					CommBuf[Rx_Cnt++] = i;
					SCC += i;
				}
				else
				{
					Rx_Cnt = 0;
				}
			}	
			else if(Rx_Cnt<4)
			{
				CommBuf[Rx_Cnt++] = i;
				SCC += i; 		
			}
			else if(Rx_Cnt<CommBuf[3]+4)
			{						   				
				CommBuf[Rx_Cnt++] = i;
				SCC +=i;
			}
			else if(Rx_Cnt==CommBuf[3]+4)
			{
				CommBuf[Rx_Cnt++] = i;				
				ReceiveOK = 1;
			}			
		}
	}		
}