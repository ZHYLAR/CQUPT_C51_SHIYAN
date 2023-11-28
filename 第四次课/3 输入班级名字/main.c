#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "MatrixKey.h"

	//LCD_ShowChar(1,1,'A');			//在1行1列显示字符A
	//LCD_ShowString(1,3,"Hello");	//在1行3列显示字符串Hello
	//LCD_ShowNum(1,9,1,1);			//在1行9列显示数字66，长度为2
	//LCD_ShowSignedNum(1,12,-88,2);	//在1行12列显示有符号数字-88，长度为2
	//LCD_ShowHexNum(2,1,0xA5,2);		//在2行1列显示十六进制数字0xA5，长度为2
	//LCD_ShowBinNum(2,4,0xA5,8);		//在2行4列显示二进制数字0xA5，长度为8
//	LCD_ShowChar(2,13,0xDF);		//在2行13列显示编码为0xDF的字符
	//LCD_ShowChar(2,14,'C');			//在2行14列显示字符C
	
void main()
{
	int KeyNum=0;//-1 represent that no num is sent
	int i=1;
	int k=0;
	char chara[3]={' ',' ',' '};
	LCD_Init();						//LCD初始化
	
	while(1)
	{
		KeyNum=MatrixKey()-1;
		if(KeyNum>=0&&i<9){
			LCD_ShowNum(1,i+5,KeyNum,1);
			KeyNum=-1;
			i++;
		}
		if(i==9){
			if(KeyNum==12){
				LCD_ShowChar(2,4,'Z');
			}
			if(KeyNum==13){
				LCD_ShowChar(2,5,'H');
			}
			if(KeyNum==14){
				LCD_ShowChar(2,6,'Y');
			}
			
		}
		
	}
}
