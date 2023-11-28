#include <REGX52.H>
#include "Delay.h"
#include "MatrixKey.h"

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

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
	P0=NixieTable[Number];	
	Delay(1);				
	P0=0x00;				
}


char KeyNum=-1;

void main()
{
	unsigned int num1=0,num2=0;
	char location=0;
	unsigned char list[]={0,0,0,0,0}; 
	unsigned char loop = 200;
	unsigned char show[]={0,0,0};
	unsigned char i = 0 ;
	while(1)
	{
		
		KeyNum=MatrixKey()-1;
		if(KeyNum>=0&&KeyNum<15){
				list[location]=KeyNum;
				while(loop>0){
					if(KeyNum>=0&&KeyNum<=9) Nixie(8,KeyNum);
					loop--;
				}
				loop = 200;
			  location++;
		}
		
		if(KeyNum==15){
			for( i=0;i<5;i++){
				list[i]=0;
			}
			location=0;
			}
		
		
		if(location==5){
				location=0;
				num1 = list[0]*10+list[1];
				num2 = list[3]*10+list[4];
			
				
				if(list[2]==10){
						show[2] = (num1+num2)/100;
						show[1] = (num1+num2)/10;
						show[0] = (num1+num2)%10;
				}
					
				if(list[2]==11){
						show[2] = (num1-num2)/100;
						show[1] = (num1-num2)/10;
						show[0] = (num1-num2)%10;
				}
					
			  if(list[2]==12){
						show[2] = (num1*num2)/100;
						show[1] = (num1*num2)/10;
						show[0] = (num1*num2)%10;
				}
		
		  	if(list[2]==13){
						show[2] = (num1/num2)/100;
						show[1] = (num1/num2)/10;
						show[0] = (num1/num2)%10;
			}
				
				while(MatrixKey()==0){
					Nixie(6,show[2]);
					Nixie(7,show[1]);
					Nixie(8,show[0]);
					
				}
				
		}
		
	}
}
