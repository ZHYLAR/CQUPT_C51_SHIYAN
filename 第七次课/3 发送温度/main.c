#include "Delay.h"
#include "UART.h"
#include "DS18B20.h"
#include <REGX52.H>

float T;
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Nixie(unsigned char Location,Number)
{
	switch(Location)		//位码输出
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
	P0=NixieTable[Number];	//段码输出
	Delay(1);				//显示一段时间
	P0=0x00;				//段码清0，消影
}

void main()
{
	int i = 0;
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(1000);			//等待转换完成
	T=DS18B20_ReadT();	//读取温度
	UART_Init();			//串口初始化
	while(1)
	{
		DS18B20_ConvertT();	//转换温度
	   T=DS18B20_ReadT();	//读取温度
		UART_SendByte((int)T/10+48);	//串口发送一个字节
		UART_SendByte((int)T%10+48);	//串口发送一个字节
		UART_SendByte(32);	//串口发送一个字节
//		for(i=500;i>0;i--){
//		Nixie(2,(int)T%10);
//		Nixie(1,(int)T/10);
//		}
		Delay(1000);		//延时1秒
	}
}
