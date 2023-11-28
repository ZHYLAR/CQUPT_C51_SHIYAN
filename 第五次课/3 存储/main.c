#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char KeyNum; 
int Num,Num2;

void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,10);
	while(1)
	{
		KeyNum=Key();
		Num = 20222;
		Num2 = 10071;
		
		if(KeyNum==3)	//K3按键，向AT24C02写入数据
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);
			AT24C02_WriteByte(1,Num/256);
			Delay(5);
			AT24C02_WriteByte(2,Num2%256);
			Delay(5);
			AT24C02_WriteByte(3,Num2/256);
			Delay(5);
			
			LCD_ShowString(2,1,"Write OK");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
		if(KeyNum==4)	//K4按键，从AT24C02读取数据
		{
			Num=AT24C02_ReadByte(0);
			Num|=AT24C02_ReadByte(1)<<8;
			Num2 = AT24C02_ReadByte(2);
			Num2|=AT24C02_ReadByte(3)<<8;
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowNum(1,6,Num2,5);
			LCD_ShowString(2,1,"Read OK ");
			Delay(1000);
			LCD_ShowString(2,1,"        ");
		}
	}
}
