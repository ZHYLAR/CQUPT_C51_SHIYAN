#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"
#include "Delay.h"

sbit Beep = P1^5;
void main()
{
	Beep=1;
	Timer0Init();
	while(1)
	{
	}
}