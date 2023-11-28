#include <REGX52.H>

//unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//¶ÎÑ¡

unsigned char ledtable[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

//ÑÓÊ±
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




void main()
{
	unsigned char i=0;
	//P2 = ledtable[1];
	
	while(1){
		
	
	//4 ge LED shanshuo
	if(P3_0==0){
		Delay(80);
		if(P3_1==1){
			i=5;
			while(i>0){
			//P2 = ledtable[0];//test state code
				P2 = 0x55;//  01010101;
				Delay(250);
				P2 = 0xFF;
				Delay(250);
			i--;
			}
		}
	}
	

	
	 if(P3_1==0){
		Delay(80);
		if(P3_0==1){
			i=10;
			while(i>0){
			//P2 = ledtable[1];
				P2 = 0;
				Delay(250);
				P2 = 0XFF;
				Delay(250);
				i--;
			}
		}
	}
	
	
	 if(P3_1==0){
		//Delay(10);
		if(P3_0==0){
			i=7;
			
			while(P3_1==0&&P3_0==0){
				P2 = ledtable[i];
				Delay(200);
				i--;
				if(i==-1){
					i=7;
				}
			}
			
		}
	}
	

		if(P3_1==1&&P3_0==1){
			P2 = ledtable[0];
			Delay(300);
			P2 = 0xFF;
			Delay(200);
		}
	
	
	}
	
	
	
}
