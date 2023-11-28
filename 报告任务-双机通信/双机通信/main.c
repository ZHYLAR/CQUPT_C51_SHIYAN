//#include "reg51.h"
#include <regx52.h>
#include <MatrixKey.h>
#include <Delay.h>
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
	uchar counter=0;
	uchar keynum;
	time(1);
	initUart(9600);//串口进行初始化
	while(1)
	{
		while(1){
		keynum = MatrixKey();
		if(keynum>0) 
			{
				SBUF=keynum;//将参数给寄存器
				break;
			}
		}
		//SBUF=counter;
		while(TI==0);//发送中断，发送8位时为1
		TI=0;//软件置0
		//while(RI==0);//接受中断，接受8位时为1
		//RI=0;//软件置0
		//counter++;
		//time(500);//延时
//		if(SBUF==counter)//如果接受到的等于counter
//		{
//			P2=counter;//数码管显示counter
//			if(++counter>15)counter=0;//大于15清零
//			time(500);//延时
//		}
	}
}


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

