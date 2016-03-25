#define MAX_FINGER 208//
#define MAX_BUF_NUMBER 133//
#define MAX_LR_NUMBER 128//

void FingerOn(void);
void FingerOff(void);
void FingerInit(void);



unsigned char EmptyFinger(void);
unsigned char WriteFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL);
unsigned char SearchFinger(unsigned char *p,unsigned char OutTime);
unsigned char ReadFingerFlash(unsigned char *p,unsigned char Number,unsigned char AddrH,unsigned char AddrL);
unsigned char AddFinger(unsigned char AddrH,unsigned char AddrL,unsigned char OutTime);
