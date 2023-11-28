#include <reg51.h>  // 包含reg51头文件

sbit OSC = P1^0;  // 定义OSC为P1口的第0位

void ET0_ISR(void) interrupt 3  // 定时器0的中断服务函数
{
    unsigned int i;
    i++;
    if(i == 1)
    {
        OSC = 0;  // 36us低电平脉冲，表示开始
    }
    else if (i == 5)
    {
        OSC = 1;  // 360us高电平脉冲，表示结束
        i=0;      // 清零计数器
    }
}

void main()
{
    TMOD = 0x20;   // 设置T0工作模式为方式2，8位自动重装载
    TH1 = 256 - 80;  // 设定初值，生成约36us的脉冲
    TL1 = TH1;    
    EA = 1;        // 允许总中断
    TR1 = 1;       // 启动T0
    ET1 = 1;       // 允许T0中断
    while(1);      // 程序主循环
}

