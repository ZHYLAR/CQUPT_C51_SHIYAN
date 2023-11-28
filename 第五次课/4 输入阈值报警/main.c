#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "MatrixKey.h"

float T;
int KeyNum=0;//-1 represent that no num is sent
unsigned char set_t=100;
unsigned char loop = 0;
char list[] = {-1,-1};
void main()
{
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(1000);			//等待转换完成
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	while(1)
	{
		KeyNum=MatrixKey()-1;
		
		if(KeyNum>=0&&loop<2){
			LCD_ShowNum(1,loop+14,KeyNum,1);
			list[loop] = KeyNum;
			KeyNum=-1;
			loop++;
		}
		
		if(list[0]>=0&&list[1]>=0){
			set_t = 10*list[0]+list[1];
		}
		
		DS18B20_ConvertT();	//转换温度
		T=DS18B20_ReadT();	//读取温度
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(2,1,'-');	//显示负号
			T=-T;			//将温度变为正数
		}else				//如果温度大于等于0
		{
			LCD_ShowChar(2,1,'+');	//显示正号
		}
		LCD_ShowNum(2,2,T,3);		//显示温度整数部分
		LCD_ShowChar(2,5,'.');		//显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*100)%100,2);//显示温度小数部分
		
		
		if(T>set_t){
			P2 = 0xff;
			Delay(300);
			P2 = 0x00;
			Delay(300);
		}
	
	}
}

