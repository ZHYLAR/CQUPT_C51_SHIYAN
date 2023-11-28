#include <REGX52.H>
void Delay(unsigned int xms);
void light(unsigned char mode);
void Delay500ms();


void Delay(unsigned int xms) //延时函数
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Delay500ms(){
		Delay(500);
}

void light(unsigned char mode){
			
	//左流动
	if(mode&1){ 
			P2=0xFE;//1111 1110
			Delay(100);
			P2=0xFD;//1111 1101
			Delay(100);
			P2=0xFB;//1111 1011
			Delay(100);
			P2=0xF7;//1111 0111
			Delay(100);
			P2=0xEF;//1110 1111
			Delay(100);
			P2=0xDF;//1101 1111
			Delay(100);
			P2=0xBF;//1011 1111
			Delay(100);
			P2=0x7F;//0111 1111
	}else{
			P2=0x7F;//1111 1110
			Delay(100);
			P2=0xBF;//1111 1101
			Delay(100);
			P2=0xDF;//1111 1011
			Delay(100);
			P2=0xEF;//1111 0111
			Delay(100);
			P2=0xF7;//1110 1111
			Delay(100);
			P2=0xFB;//1101 1111
			Delay(100);
			P2=0xFD;//1011 1111
			Delay(100);
			P2=0xFE;//0111 1111
	}
			
}

unsigned char LEDNum;

void main()
{
	
	//P2=~0x01;				//turn on LED1
	while(1)
	{
		light(1);
		light(2);
		}
	}


