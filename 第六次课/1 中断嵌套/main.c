
//流水灯效果，两种外部中断实现了不同的闪烁效果。
#include <REGX52.H>  // 包含单片机头文件
#define uchar unsigned char  // 定义无符号字符类型
#define uint unsigned int    // 定义无符号整型类型
	
uchar liushui_code[9] = {0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};  // 定义流水码数组

void Delay_ms(uint ms)
{
	uchar i;
	while(ms--)
		for(i=0;i<123;i++);
}
// 延时函数，延时ms毫秒

void main()
{

	EX0 = 1;  // 使能外部中断0
	EX1 = 1;  // 使能外部中断1
	EA = 1;   // 全局中断使能
	
	PX0 = 0;  // 设置外部中断0的优先级为低
	PX1 = 1;  // 设置外部中断1的优先级为高


	IT0 = 1;  // 设置外部中断0为下降沿触发
	IT1 = 1;  // 设置外部中断1为下降沿触发
	
	while(1)
	{
		uint i;
		for(i=0;i<9;i++)
		{
			Delay_ms(500);  // 延时500毫秒
			P2 = liushui_code[i];  // 将流水码输出到P2口
		}
	
	}
}
// 主函数，循环输出流水灯效果


void int0(void)  interrupt 0 using 0
{
	while(1)
	{
		P2 = 0x0f;  // 将P2口设置为低四位为高电平，高四位为低电平
		Delay_ms(500);  // 延时500毫秒
		P2 = 0xf0;  // 将P2口设置为低四位为低电平，高四位为高电平
		Delay_ms(500);  // 延时500毫秒
	
	}

}
// 外部中断0的中断服务函数，实现了一个交替闪烁的效果


void int1(void)  interrupt 2 using 1
{
	uint m;
	for(m=0;m<6;m++)
	{
		P2 = 0xff;  // 将P2口设置为全高电平
		Delay_ms(500);  // 延时500毫秒
		P2 = 0;  // 将P2口设置为全低电平
		Delay_ms(500);  // 延时500毫秒
	}

}
// 外部中断1的中断服务函数，实现了一个闪烁的效果

