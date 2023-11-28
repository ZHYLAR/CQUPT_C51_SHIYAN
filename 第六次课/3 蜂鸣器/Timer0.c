#include <REGX52.H>
sbit Beep = P1^5;

/**
  * @brief  定时器0初始化，1毫秒@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer0Init(void)
{
	
	TMOD = 0x02;		//设置定时器模式
	TL0 = 256-176;		//设置定时初值
	TH0 = 256-176;		//设置定时重载值
	TF0 = 0;		//清除TF0标志
	ET0=1;
	EA=1;
  TR0 = 1;		 //启动定时器0
	
}

//定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count = 0,a = 0 ,b=0;

	if(!a)
	{			
		b++;
		if(b==5)
		{
		    Beep=~Beep;
            b=0;
		}
		T0Count++;
		if(T0Count==5264)
		{
			a=1;
		}	
	}
}


