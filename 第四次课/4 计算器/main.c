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
unsigned int length(unsigned int res){
	if(res>=100){
		return 3;
	}
	else if(res<100&&res>=10){
		return 2;
	}
	else if(res<10){
		return 1;
	}
}

void main()
{
	int KeyNum=0;//-1 represent that no num is sent
	int i=1;
	char op = 0;
	unsigned int n1,n2,res;
	unsigned int n[5]={0};
	LCD_Init();
	while(1)
	{
		KeyNum=MatrixKey()-1;
		
		if(KeyNum==10){
			op='+';
		  LCD_ShowChar(1,i,op);
			KeyNum=-1;
			n[i-1] = op;
			i++;
		}
		else if(KeyNum==11){
			op='-';
			LCD_ShowChar(1,i,op);
			n[i-1] = op;
			KeyNum=-1;
			i++;
		}
		else if(KeyNum==12){
			op='*';
			LCD_ShowChar(1,i,op);	
			n[i-1] = op;
			KeyNum=-1;
			i++;
		}
		else if(KeyNum==13){
			op='/';
			LCD_ShowChar(1,i,op);
			n[i-1] = op;
			KeyNum=-1;
			i++;
		}
			

		else if(KeyNum>=0&&KeyNum<10){
			LCD_ShowNum(1,i,KeyNum,1);
			n[i-1] = KeyNum;
			KeyNum=-1;
			i++;
		}
		if(i==6){
			
			n1 = 10*n[0]+n[1];
			n2 = 10*n[3]+n[4];
			switch(op){
				case '+':
					res = n1+n2;
					break;
				case '-':
					res = n1-n2;
					break;
				case '*':
					res = n1*n2;
					break;
				case '/':
					res = n1/n2;
					break;
			}
			LCD_ShowNum(2,1,res,length(res));		
			i=1;
			while(1){
				if(MatrixKey()!=0)
					{
						LCD_ShowString(1,1,"          ");
						LCD_ShowString(2,1,"          ");
						break;
					}
			}
			
			
		}
	}
}
