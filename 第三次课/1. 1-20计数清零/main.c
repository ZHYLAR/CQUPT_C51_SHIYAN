#include <REGX52.H>

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//段选

//延时
void Delay(unsigned int xms)
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


//位选
void Nixie(unsigned char Location,Number)
{
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//????
	Delay(1);				
	P0=0x00;				
}



void main()
{
	unsigned int i;
	i=0;
	while(1)
	{

		if(P3_1==0){
			Delay(20);
			while(P3_1==0);
			Delay(20);	
			i++;
		}
		
			if(i<10){
				
				while(1){
					Nixie(8,i);
					Nixie(7,0);
					if(P3_1==0){
						break;
					}
				}
			}
			
			if(i>=10&&i<=20){
				while(1){
					Nixie(8,i%10);
					Nixie(7,i/10);
					if(P3_1==0){
							break;
					}
				}
			}
			
			if(i>20){
				i=0;
			}
		
	}
}
