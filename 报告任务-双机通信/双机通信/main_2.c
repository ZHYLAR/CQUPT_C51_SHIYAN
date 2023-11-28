#include "reg51.h"
#include <LCD1602.h>
//�궨��
#define uchar unsigned char
#define uint unsigned int
//��ʱ����
void time(uint ucMs);
//���ڳ�ʼ��
void initUart(unsigned int baud);
//��������
uchar ucCounter;

void main(void)
{
	uchar i=1;
	uchar receive;
	time(1);
	initUart(9600);//���ڳ�ʼ��
	//LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
	LCD_Init();
//	LCD_ShowNum(1,1,20222,5);
//	LCD_ShowNum(1,6,10071,5);
	while(1)
	{
		while(RI==0);//����8Ϊ��1
		RI=0;
		receive=SBUF; //�����ź�
		LCD_ShowNum(1,i,(int)receive,1);
		i++;
		if(i==12){i=1;LCD_ShowString(1,1,"           ");}
		//SBUF=receive;//�����ܵķ���ȥ
		//while(TI==0);//����8λ��1
		//TI=0;
		//P2=receive;//�������ʾ�ź�
	}
}

//���ڳ�ʼ��
void initUart(unsigned int baud)
{
	SM0=1;SM1=0;REN=1;//8λ�����ʿɱ䣬�����ڽ����ź�
	TMOD|=0X20;//��ʱ��1Ϊ8λ�Զ���װ��
	PCON=0X00;//��SMOD==0
	TR1=1;//�򿪶�ʱ��1
	EA=1;ET1=1;//�򿪴����ж�
	TH1=256-11059200/12/32/baud;//���ö�ʱ����ֵ
	TL1=256-11059200/12/32/baud;//���ö�ʱ����ֵ
}

//��ʱ����
void time(uint ucMs)
{
	while(ucMs!=0)
	{
		for(ucCounter=0;ucCounter<239;ucCounter++);
		ucMs-=1;
	}
}
