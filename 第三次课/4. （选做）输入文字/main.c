#include <REGX52.H>

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



unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=1;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=5;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=9;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=2;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=6;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=14;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=3;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=11;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=15;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=8;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=12;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=16;}
	
	return KeyNumber;
}


unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x76,0x40};

	//H:0x76 -:0x40


void Nixie(unsigned char Location,Number)
{
	if(Location>=1&&Location<=8){
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
}else{
		Delay(1);
}
}


void main()
{
	unsigned char i,j=100;
	//unsigned int num1=0,num2=0;
	char location=0;
	unsigned char list[]={0,0,0,0,0,0,0}; 
	unsigned char loop = 200;
	char KeyNum=-1;
	
	
	while(1)
	{
		KeyNum=MatrixKey()-1;
		
		if(KeyNum>=0&&KeyNum<12){
				list[location]=KeyNum;
				while(loop>0){
					if(KeyNum>=0&&KeyNum<=11) Nixie(8,KeyNum);
					loop--;
				}
				loop = 200;
			  location++;
		}
		
	
		//xian shi 
		if(location==7){
			location=0;
			while(MatrixKey()==0){
				for(i=0;i<15;i++){
					j=80;
					while(j>0){
						Nixie(8-i,list[0]);
						Nixie(9-i,list[1]);
						Nixie(10-i,list[2]);
						Nixie(11-i,list[3]);
						Nixie(12-i,list[4]);
						Nixie(13-i,list[5]);
						Nixie(14-i,list[6]);
						j--;
					}
					
			}
				
		}
			
	}
}
	

}