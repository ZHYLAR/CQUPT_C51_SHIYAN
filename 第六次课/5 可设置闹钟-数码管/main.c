#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"
#include "display.h"
//#include "Buzzer.h"

unsigned char second=50,min,hour,min0,hour0=12,count,second0;
unsigned int i,is;

sbit key0=P3^1;
sbit key1=P3^0;
sbit key2=P3^2;
sbit key3=P3^3;
sbit buzzer=P1^5;

unsigned char now_alock = 0;
unsigned char externalInterruptFlag = 0;
void externalInterrupt1() interrupt 2 {
		//P2 = 0;
		if(!now_alock){externalInterruptFlag = 0;}
		
		if(now_alock){
			externalInterruptFlag = 1;
			now_alock = 0;
		}  // 设置标志位，表示触发了外部中断
}

void Buzzer_Time(unsigned int ms)
{
	unsigned int s;
	unsigned int i;
	now_alock = 1;
	while(1){
		buzzer=1;
		Delay(1);
		buzzer=0;
		Delay(1);
		if (externalInterruptFlag) {
				s = second;
          // 处理外部中断触发的操作
        buzzer=0; // 停止蜂鸣器响铃
        break;       // 跳出循环
		}
	}
}

//矩阵键盘扫描
unsigned char Keyscan()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=1;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=5;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=9;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=2;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=6;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=3;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=11;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=8;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=12;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=16;}
	
	return KeyNumber;
}

//设置闹钟 key16视作输入0
void set(void)
{
	unsigned char keynum,temp,key_num;
	keynum=2;
	while(1)
	{
		if(key2==0)
		{
			keynum=2;
		}
		if(key3==0)
		{
			keynum=3;
		}
		if(key1==0)
		{
			keynum=1;
		}
		display(1, hour0/10);
		display(2, hour0%10);
		display(3, 10);
		display(4, min0/10);
		display(5, min0%10);
		display(6, keynum);
		display(7, second0/10);
		display(8, second0%10);
		if(key0==0)
		{
			return;
		}
		temp=Keyscan();
		if(temp)
		{
			if((temp<10||temp==16)&&keynum==2)
			{
				if(temp==16)
				{
					min0=min0*10;
				}
				else
				{
					min0=min0*10+temp;
				}
			}
			if((temp<10||temp==16)&&keynum==3)
			{
				if(temp==16)
				{
					hour0=hour0*10;
				}
				else
				{
					hour0=hour0*10+temp;
				}
			}
			if((temp<10||temp==16)&&keynum==1)
			{
				if(temp==16)
				{
					second0=second0*10;
				}
				else
				{
					second0=second0*10+temp;
				}
			}
		}
	}
}

void main()
{
	EA = 1;
	IT1 = 1;
	EX1 = 1;
	PX1 = 1;
	is=1;
	Timer0_Init();
	buzzer=0;
	while(1)
	{
		display(1, hour/10);
		display(2, hour%10);
		display(3, 10);
		display(4, min/10);
		display(5, min%10);
		display(6, 10);
		display(7, second/10);
		display(8, second%10);
		if(key0==0)
		{
			set();
		}
	}
}

//定时器服务函数
void Timer0_Routine(void) interrupt 1
{
	TL0 = 0xA0;		//设置定时初值
	TH0 = 0x15;		//设置定时初值
	if(i==200)	//计数值小于比较值
	{
		second++;
		i=0;
		if(second==60)
		{
			min++;
			if(min==60)
			{
				hour++;
				min=0;
				if(hour==24)
				{
					hour=0;
				}
			}
			second=0;
		}
		if(min==min0&&hour0==hour&&is)
		{
			Buzzer_Time(500);
		}
		if(P3_0==0)
		{
			is=0;
		}
	}
	i++;
}
