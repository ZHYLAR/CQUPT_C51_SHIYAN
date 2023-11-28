//波特率2400、接收8位学号显示在数码管
#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
unsigned char NI[9]={0xfe,0xfd,0xfb,0xf7,0xed,0xdf,0xbf,0x7f,0x00};
unsigned char a,b;
char key=0;
//sbit BEEP = P1^5;
unsigned char arr[8]={0,0,0,0,0,0,0,0};
unsigned char index;

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Nixie(unsigned char Location,Number)
{
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	
	Delay(1);				
	P0=0x00;				
}

void main()
{
	UART_Init();		//串口初始化
	P2 = 0XFF;
	//UART_SendByte(0xff);
	while(1)
	{
		for(b=1;b<=8;b++){
			Nixie(9-b,arr[b-1]);
		}
	}
}

void UART_Routine() interrupt 4
{
	if(RI==1)					//如果接收标志位为1，接收到了数据
	{
		//UART_SendByte(SBUF);
		for(a=7;a>0;a--){
			arr[a] = arr[a-1];
		}
		arr[0] = SBUF;
		
		for(index=0;index<8;index++){
			UART_SendByte(arr[index]);
		}
		RI=0;					//接收标志位清0
	}
}
