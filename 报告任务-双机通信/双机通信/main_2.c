#include "reg51.h"
#include <LCD1602.h>
//宏定义
#define uchar unsigned char
#define uint unsigned int
//延时函数
void time(uint ucMs);
//串口初始化
void initUart(unsigned int baud);
//参数定义
uchar ucCounter;

void main(void)
{
	uchar i=1;
	uchar receive;
	time(1);
	initUart(9600);//串口初始化
	//LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
	LCD_Init();
//	LCD_ShowNum(1,1,20222,5);
//	LCD_ShowNum(1,6,10071,5);
	while(1)
	{
		while(RI==0);//接受8为置1
		RI=0;
		receive=SBUF; //接受信号
		LCD_ShowNum(1,i,(int)receive,1);
		i++;
		if(i==12){i=1;LCD_ShowString(1,1,"           ");}
		//SBUF=receive;//将接受的发出去
		//while(TI==0);//发送8位置1
		//TI=0;
		//P2=receive;//数码管显示信号
	}
}

//串口初始化
void initUart(unsigned int baud)
{
	SM0=1;SM1=0;REN=1;//8位波特率可变，允许串口接受信号
	TMOD|=0X20;//定时器1为8位自动重装载
	PCON=0X00;//让SMOD==0
	TR1=1;//打开定时器1
	EA=1;ET1=1;//打开串口中断
	TH1=256-11059200/12/32/baud;//设置定时器初值
	TL1=256-11059200/12/32/baud;//设置定时器初值
}

//延时函数
void time(uint ucMs)
{
	while(ucMs!=0)
	{
		for(ucCounter=0;ucCounter<239;ucCounter++);
		ucMs-=1;
	}
}
