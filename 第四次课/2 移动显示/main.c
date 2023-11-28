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


#include <string.h>
void substring(const char* input, char* output, int a, int b) {
    int len = strlen(input);
    int index = 0;  // 输出字符串的索引
		int i;
    if (a < 0) {
        a = 0;
    }
    if (b >= len) {
        b = len - 1;
    }
    if (a > b) {
        for (i = a; i < len && index < 16; i++) {
            output[index++] = input[i];
        }
        for (i = 0; i <= b && index < 16; i++) {
            output[index++] = input[i];
        }
    } else {
        for (i = a; i <= b && index < 16; i++) {
            output[index++] = input[i];
        }
    }
    output[index] = '\0';  // 手动添加字符串结束符
}



void main()
{
	char list[] = "welcome to cqupt   ";
	char output[] = "welcome to cqupt";
	unsigned char i=0,a=0,b=16;
	unsigned char mod;
	LCD_Init();	
	//LCD_ShowString(1,0,list);
	while(1){
		substring(list, output,(0+i)%16,(15+i)%16);
		i++;
		LCD_ShowString(1,1,output);
		Delay(2000);
		if(i>16){
			i=0;
		}
	}
		
		
	}

