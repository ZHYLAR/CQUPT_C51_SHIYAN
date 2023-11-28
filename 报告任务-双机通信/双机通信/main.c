//#include "reg51.h"
#include <regx52.h>
#include <MatrixKey.h>
#include <Delay.h>
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
	uchar counter=0;
	uchar keynum;
	time(1);
	initUart(9600);//���ڽ��г�ʼ��
	while(1)
	{
		while(1){
		keynum = MatrixKey();
		if(keynum>0) 
			{
				SBUF=keynum;//���������Ĵ���
				break;
			}
		}
		//SBUF=counter;
		while(TI==0);//�����жϣ�����8λʱΪ1
		TI=0;//�����0
		//while(RI==0);//�����жϣ�����8λʱΪ1
		//RI=0;//�����0
		//counter++;
		//time(500);//��ʱ
//		if(SBUF==counter)//������ܵ��ĵ���counter
//		{
//			P2=counter;//�������ʾcounter
//			if(++counter>15)counter=0;//����15����
//			time(500);//��ʱ
//		}
	}
}


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

