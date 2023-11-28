//#include <REGX52.H>
//#include <INTRINS.H>
//#include "delay.h"
////蜂鸣器端口：
//sbit Buzzer=P1^5;

///**
//  * @brief  蜂鸣器私有延时函数，延时500us
//  * @param  无
//  * @retval 无
//  */
//void Buzzer_Delay500us()		//@12.000MHz
//{
//	unsigned char i;

//	_nop_();
//	i = 247;
//	while (--i);
//}

///**
//  * @brief  蜂鸣器发声
//  * @param  ms 发声的时长，范围：0~32767
//  * @retval 无
//  */
//void Buzzer_Time(unsigned int ms)
//{
//	unsigned int i;
//	while(1){
//		Buzzer=1;
//		Delay(1);
//		Buzzer=0;
//		Delay(1);
//		if (externalInterruptFlag) {
//            // 处理外部中断触发的操作
//            Buzzer = 0;  // 停止蜂鸣器响铃
//						externalInterruptFlag = 0;
//            break;       // 跳出循环
//		}
//	}
////	for(i=0;i<ms*2;i++)
////	{
////		Buzzer=!Buzzer;
////		Buzzer_Delay500us();
////	}
//}
