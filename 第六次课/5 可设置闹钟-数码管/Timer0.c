#include <REGX52.H>

/**
  * @brief  定时器0初始化，100us@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer0_Init(void)
{
	TMOD &= 0x80;		//设置定时器模式
	TMOD |= 0xF0;		//设置定时器模式
	TL0 = 0xA0;		//设置定时初值
	TH0 = 0x15;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

/*void Timer1Init(void)		//1毫秒@12.000MHz
{
	TMOD |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x30;		//设置定时初值
	TH1 = 0xD3;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	EA=1;
	PT1=0;
}*/


/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
