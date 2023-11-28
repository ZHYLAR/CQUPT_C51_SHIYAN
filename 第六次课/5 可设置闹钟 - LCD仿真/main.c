#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"
#include "Delay.h"
#include "MatrixKey.h"
sbit BEEP = P2^0;


bit externalInterruptFlag = 0;
void externalInterrupt1() interrupt 2 {
    externalInterruptFlag = 1;  // 设置标志位，表示触发了外部中断
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	//_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlashFlag;
unsigned char alockH = 0,alockM = 0,alockS = 0;
void timer(char a,char b,char c){
		//char i;
		if(DS1302_Time[3]==alockH&&DS1302_Time[4]==alockM&&DS1302_Time[5]==alockS){   
				while (1)
				{
						BEEP = 1; // ???????
						Delay1ms();
						BEEP = 0; // ???????
						Delay1ms();
						if (externalInterruptFlag) {
            // 处理外部中断触发的操作
            BEEP = 1;  // 停止蜂鸣器响铃
						externalInterruptFlag = 0;
            break;       // 跳出循环
						}
				}
		}
}

void TimeShow(void)//时间显示功能
{
	DS1302_ReadTime();//读取时间
	timer(DS1302_Time[3],DS1302_Time[4],DS1302_Time[5]);
	LCD_ShowNum(1,1,alockH,2);//显示年
	LCD_ShowNum(1,4,alockM,2);//显示月
	LCD_ShowNum(1,7,alockS,2);//显示日
	
	LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
}

void TimeSet(unsigned char key)//时间设置功能
{
	TimeSetSelect = key;
//	if(KeyNum==2)//按键2按下
//	{
//		TimeSetSelect++;//设置选择位加1
//		TimeSetSelect%=6;//越界清零
//	}
	if(KeyNum==3)//按键3按下
	{
		DS1302_Time[TimeSetSelect]++;//时间设置位数值加1
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}//年越界判断
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}//大月
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}//小月
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}//闰年2月
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}//平年2月
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}//时越界判断
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}//分越界判断
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}//秒越界判断
	}
	if(KeyNum==4)//按键3按下
	{
		DS1302_Time[TimeSetSelect]--;//时间设置位数值减1
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}//年越界判断
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}//大月
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}//小月
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}//闰年2月
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}//平年2月
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}//时越界判断
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}//分越界判断
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}//秒越界判断
	}
	//更新显示，根据TimeSetSelect和TimeSetFlashFlag判断可完成闪烁功能
	//if(TimeSetSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}
	//else {LCD_ShowNum(1,1,DS1302_Time[0],2);}
	//if(TimeSetSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
	//else {LCD_ShowNum(1,4,DS1302_Time[1],2);}
	//if(TimeSetSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
	//else {LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,DS1302_Time[5],2);}
}



void main()
{
	unsigned char key=3;
	char MKN = 0;
	unsigned char alockTime[] = {0,0,0,0,0,0};
	unsigned char index_alockTime,loop;
	index_alockTime = 0;
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	LCD_ShowString(1,1,"  :  :  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");
	LCD_ShowString(1,11,"alarmT");
	LCD_ShowString(2,11,"nowT");
	EA = 1;      // 允许全局中断
  EX1 = 1;     // 允许外部中断1
  IT1 = 1;     // 设置为边沿触发方式（可以根据需要修改为电平触发方式）
	DS1302_SetTime();//设置时间
	
	while(1)
	{
		KeyNum=Key();//读取键码
		if(KeyNum==1)//按键1按下
		{
			if(MODE==0){MODE=1;TimeSetSelect=0;}//功能切换
			else if(MODE==1){MODE=0;DS1302_SetTime();}
		}
		if(KeyNum==2)//按键2按下
	{
		key++;//设置选择位加1
		if(key==6)key=3;//越界清零
	}
		switch(MODE)//根据不同的功能执行不同的函数
		{
			case 0:TimeShow();break;
			case 1:TimeSet(key);break;
		}
		//timer();
		
		MKN = MatrixKey();
		if(MKN){
			switch(MKN){
				case 5:
					MKN = 4;
					break;
				case 6:
					MKN = 5;
					break;
				case 7:
					MKN = 6;
					break;
				case 9:
					MKN = 7;
					break;
				case 10:
					MKN = 8;
					break;
				case 11:
					MKN = 9;
					break;
				case 14:
					MKN = 100;
					break;
			}
			if(MKN>=1&&MKN<=100){
					if(MKN==100){MKN=0;}
					alockTime[index_alockTime] = MKN;
					index_alockTime++;
					if(index_alockTime==6){index_alockTime = 0;}
					
					alockH = 10*alockTime[0]+alockTime[1];
					alockM = 10*alockTime[2]+alockTime[3];
					alockS = 10*alockTime[4]+alockTime[5];
					
					if(alockH>23){index_alockTime--;alockH=0;}
					if(alockM>59){index_alockTime--;alockM=0;}
					if(alockS>59){index_alockTime--;alockS=0;}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)//每500ms进入一次
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;//闪烁标志位取反
	}
}
