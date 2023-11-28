/*

��������Ҫ�ǿ��Ƶ�Ƭ���Ĵ���ͨ�ţ�ʵ�����¹��ܣ�
����4�ֽڵ����ݣ�����洢�������У�
���ݽ��յ������ݣ�����P2����������źţ�����LED�Ƶ�����
�����յ�0x11ʱ������beep()����ʵ�ַ��������壻
�����յ�4���ض����ֽ�ʱ����LED��˸10�Σ���������顣 */

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
