#define MAX_FINGER 208//
#define MAX_BUF_NUMBER 133//
#define MAX_LR_NUMBER 128//



void FingerOn(void);
void FingerOff(void);
void FingerInit(void);
void Clear_Uart_Variable(void);
unsigned char SendCommand(unsigned char BaoBS,unsigned char Number,unsigned char *p);

unsigned char EmptyFinger(void);
unsigned char WriteFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL);
unsigned char ReadFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL);

