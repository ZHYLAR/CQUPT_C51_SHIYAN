#include <reg51.h>  // ����reg51ͷ�ļ�

sbit OSC = P1^0;  // ����OSCΪP1�ڵĵ�0λ

void ET0_ISR(void) interrupt 3  // ��ʱ��0���жϷ�����
{
    unsigned int i;
    i++;
    if(i == 1)
    {
        OSC = 0;  // 36us�͵�ƽ���壬��ʾ��ʼ
    }
    else if (i == 5)
    {
        OSC = 1;  // 360us�ߵ�ƽ���壬��ʾ����
        i=0;      // ���������
    }
}

void main()
{
    TMOD = 0x20;   // ����T0����ģʽΪ��ʽ2��8λ�Զ���װ��
    TH1 = 256 - 80;  // �趨��ֵ������Լ36us������
    TL1 = TH1;    
    EA = 1;        // �������ж�
    TR1 = 1;       // ����T0
    ET1 = 1;       // ����T0�ж�
    while(1);      // ������ѭ��
}

