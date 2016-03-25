#include <REG52.H>
#include <intrins.h>//
#include <string.h>//

void DelayNuS(unsigned char i);
void DelayNmS(unsigned char i);

void EnableInterrupt(void);
void DisInterrupt(void);


#define FALSE 0
#define OK 1
#define TIMEOUT 2


#include "Led.h"
#include "Bell.h"
#include "Key.h"
#include "Timer.h"
#include "UART.h"
#include "Finger.h"
#include "Module.h"
#include "Command.h"

