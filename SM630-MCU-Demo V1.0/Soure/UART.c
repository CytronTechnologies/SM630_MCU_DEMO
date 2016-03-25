#include "Include.h"

//UART
//
void UARTInit(void)
{
        SCON=0X50;    //232  COM init 
        T2CON=0X30;
        RCAP2H=0XFF;
        RCAP2L=0XFA;
        TH2=0XFF;
        TL2=0XFA;
        TR2=1;
}

//
void UARTSendByte(unsigned char i)
{
	SBUF=i;
	while(0==TI) {;}
        TI=0;
}

//
unsigned char UARTGetByte(void)
{
        while(0==RI) {;}
        RI=0;
        return SBUF;
}