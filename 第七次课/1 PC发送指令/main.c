/*

本程序主要是控制单片机的串口通信，实现以下功能：
接收4字节的数据，将其存储到数组中；
根据接收到的数据，控制P2口输出控制信号，控制LED灯的亮灭；
当接收到0x11时，调用beep()函数实现蜂鸣器响铃；
当接收到4个特定的字节时，将LED闪烁10次，并清空数组。 */

#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
unsigned char NI[9]={0xfe,0xfd,0xfb,0xf7,0xed,0xdf,0xbf,0x7f,0x00};
char key=0;
sbit BEEP = P1^5;
unsigned int a=0;
char arr[5]={0,0,0,0};
char j = 0,index;


void shanshuo(){
		P2 = 0xff;
		Delay(200);
		P2 = 0;
		Delay(200);	
}


void beep(){
	while(a){
			BEEP = 1;
			Delay(1);
			BEEP = 0;
			Delay(1);
			UART_Init();
			a=SBUF;
	}
}


void main()
{
	UART_Init();	
	P2 = 0XFF;
	while(1)
	{
		//P2 = 0;
		if(arr[3]==0x01&&arr[2]==0x23&&arr[1]==0x45&&arr[0]==0x67)
			{
				for(index=0;index<10;index++){
					shanshuo();
				}
				for(index=0;index<4;index++){
					arr[index] = 0;
					P2 = 0xff;
				}
			}
	}
}

void UART_Routine() interrupt 4
{
	if(RI==1)				
	{
		arr[3] = arr[2];
		arr[2] = arr[1];
		arr[1] = arr[0];
		arr[0] = SBUF;
		a=SBUF;
		if(SBUF==1)
		{
			P2=NI[0];
		}
		if(SBUF==2)
		{
			P2=NI[1];
		}
		if(SBUF==3)
		{
			P2=NI[2];
		}
		if(SBUF==4)
		{
			P2=NI[3];
		}
		if(SBUF==5)
		{
			P2=NI[4];
		}
		if(SBUF==6)
		{
			P2=NI[5];
		}
		if(SBUF==7)
		{
			P2=NI[6];
		}
		if(SBUF==0x11)
		{
			beep();
		}
		if(SBUF==0){
			
		}
		for(index=0;index<4;index++){
			UART_SendByte(arr[index]);
		}
		
		RI=0;				
	}
}
