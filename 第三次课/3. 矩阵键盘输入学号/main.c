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


char KeyNum=-1;//-1 represent that no num is sent

void main()
{
	char location=0;
	unsigned char list[]={0,0,0,0,0,0,0,0}; 
	unsigned char loop = 200;
	while(1)
	{
		KeyNum=MatrixKey()-1;
		if(KeyNum>=0){
				list[location]=KeyNum;
				
				while(loop>0){
					Nixie(8,KeyNum);
					loop--;
				}
				loop = 200;
			
				//Nixie(location,list[location]);
			  location++;
		}
		if(location==8){
				location=0;
				while(MatrixKey()==0){
					Nixie(1,list[0]);
					Nixie(2,list[1]);
					Nixie(3,list[2]);
					Nixie(4,list[3]);
					Nixie(5,list[4]);
					Nixie(6,list[5]);
					Nixie(7,list[6]);
					Nixie(8,list[7]);
				}
		}
		
		
	}
}
