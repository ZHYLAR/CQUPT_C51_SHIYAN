#include <REGX52.H>

/**
  * @brief  串口初始化，4800bps@12.000MHz
  * @param  无
  * @retval 无
  */
//void UART_Init()
//{

//	PCON &= 0x7F;		//波特率不倍速
//	SCON = 0x50;		//8位数据,可变波特率
//	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xF4;		//设定定时初值
//	TH1 = 0xF4;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1
//}


void UART_Init(void)		//2400bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xE6;		//设定定时初值
	TH1 = 0xE6;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA = 1;
	ES = 1;
}



/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/
