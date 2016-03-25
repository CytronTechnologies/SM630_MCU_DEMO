#include "Include.h"

extern unsigned char FingerRecord[26];				//
extern unsigned char xdata CommBuf[MAX_BUF_NUMBER];	//
extern unsigned char xdata SCC;						//
extern unsigned char BellTimer;
extern unsigned int  Tc;							//
extern unsigned char NowKey;						//
extern	bit	ReceiveOK; 								//

/**********************************/
bit	Deal_Flag = 0;	 //
/**********************************/

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

        //
        if(OK == WriteFingerFlash(FingerRecord,sizeof(FingerRecord),0,0))
        {
        }
        else
        {
                DisplayErr();
                FingerOff();
                return;
        }

        //
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

        CommBuf[0] = C_SEARCH_FINGER;
        CommBuf[1] = 0;
        CommBuf[2] = 0;
        CommBuf[3] = 0;
        CommBuf[4] = MAX_FINGER;//

		Clear_Uart_Variable();
        SendCommand(C_COMMAND,5,CommBuf);//
		

		//
		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();

		if((SCC==CommBuf[CommBuf[3]+4])&&Tc)	//
		{
			if((C_ANSWER==CommBuf[2])&&(0x01==CommBuf[4]))
			{ 
				//					
				Tc = 14;				 // 
			}
			else
			{
				DisplayErr();
                FingerOff();
				return;
			}
		}
		else
		{
			DisplayErr();
            FingerOff();
			return;
		}


		//
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();

		if((SCC==CommBuf[CommBuf[3]+4])&&Tc)				//
		{
            if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_SEARCH_FINGER == CommBuf[4]))
            {
                    //
					switch(CommBuf[5])
					{
						//
						case ANSWER_OK:
							//
							Tc = 14;
							Deal_Flag = 1;
                            BellOn();
                            BellTimer = 6;//
							break;

						case ANSWER_OUT_TIME:
							DisplayOutTime();
	                        break;

						case ANSWER_FAIL:
						case ANSWER_NUMBER_E:
							DisplayFail();//
							break; 
					}
					if(!Deal_Flag)
					{
						Deal_Flag = 0;
                        FingerOff();							
						return;
					}
            }
            else
            {
					DisplayErr();
		            FingerOff();
					return;
            }
		}
		else
		{
			DisplayErr();
            FingerOff();
			return;
		}		

		//
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();

		if((SCC==CommBuf[CommBuf[3]+4])&&Tc)	   	//
		{
            if((C_ANSWER == CommBuf[2])&&(C_SEARCH_FINGER == CommBuf[4]))
            {
                //
				switch(CommBuf[5])
				{
					//
					case ANSWER_SEARCH_OK:
						DisplayOK();
						break;

					case ANSWER_OUT_TIME:
						DisplayOutTime();
                        break;

					case ANSWER_FAIL:
					case ANSWER_SEARCH_FAIL:
						DisplayFail();//
						break; 
				}

            }
            else
            {	  
				DisplayErr();
            }
		}
		else
		{
			DisplayErr();
		}

        FingerOff();							
}


void AddFingerModule(void)
{
        static unsigned char i;
        static unsigned char AH;//
        static unsigned char AL;//
        unsigned char t = 0;
	 
        FingerOn();
		BellOn();
        DelayNmS(200);
		BellOff();

		P1 &=~0x04;
        //1 
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
                DisplayErr();
                FingerOff();
                return;
        }
		//
        CommBuf[0] = C_ADD_FINGER;
        CommBuf[1] = 0;
        CommBuf[2] = i;

		Clear_Uart_Variable();
        SendCommand(C_COMMAND,3,CommBuf);//

		//
		Tc = 2;
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();

		if((SCC==CommBuf[CommBuf[3]+4])&&Tc) 	//
		{
			if((C_ANSWER==CommBuf[2])&&(0x01==CommBuf[4]))
			{
				//
				Tc = 14;	
			}
			else
			{	
				//
				DisplayErr();
                FingerOff();
				return;
			}
		}
		else
		{
			DisplayErr();
            FingerOff();
			return;
		}

		//
		while(!ReceiveOK&&Tc);
		Clear_Uart_Variable();
		if((SCC==CommBuf[CommBuf[3]+4])&&Tc)					//
		{
            if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_ADD_FINGER == CommBuf[4]))
            {
                //					
				switch(CommBuf[5])
				{
					case ANSWER_OK:
						Tc = 30;
					    BellOn();
                        BellTimer = 6;		//
						Deal_Flag = 1;
						break;

					case ANSWER_OUT_TIME:
						DisplayOutTime();	//
                        break;

					case ANSWER_NUMBER_E:
						DisplayFail();		//
						break;
				}
				if(!Deal_Flag)
				{
					Deal_Flag = 0;
                    FingerOff();					
					return;
				}
            }
            else
            {
				//
				DisplayErr();
                FingerOff();					
                return;
            } 				
		}
		else
		{
			DisplayErr();
            FingerOff();
			return;
		}		


		//
		while(!ReceiveOK&&Tc);
		UARTSendByte(Tc);
		Clear_Uart_Variable();
		if((SCC==CommBuf[CommBuf[3]+4])&&Tc) 					//
		{
            if((C_ANSWER == CommBuf[2])&&(0x02 == CommBuf[3])&&(C_ADD_FINGER == CommBuf[4]))
            {
                //					
				switch(CommBuf[5])
				{
					case ANSWER_OK:
						P1 |= 0x04;
						DisplayOK();

				        //
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
				        FingerRecord[AH] |= 1<<AL;
						t = WriteFingerFlash(FingerRecord,sizeof(FingerRecord),0,0);
						UARTSendByte(t);
				        if(OK == t)
				        {
							;
				        }
						else
						{
							
				        	DisplayErr();							
						}
						break;

					case ANSWER_OUT_TIME:
						DisplayOutTime();
                        break;

					case ANSWER_FAIL:
					case ANSWER_NUMBER_E:
						DisplayFail();//
						break;
				}
            }
            else
            {	
				//
				DisplayErr();					
            } 				
		}
		else
		{
			DisplayErr();
		}													
		
        FingerOff();						
}
