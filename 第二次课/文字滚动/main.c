#include <REGX52.H>



unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x76,0x40};

	//H:0x76 -:0x40

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
	
	Nixie(8-i,10);
	Nixie(9-i,1);
	Nixie(10-i,11);
	Nixie(11-i,2);
	Nixie(12-i,0);
	Nixie(13-i,2);
	Nixie(14-i,3);
	
	while(1)
	{
			for(i=0;i<15;i++){
				
					j=100;
					while(j>0){
						Nixie(8-i,10);
						Nixie(9-i,1);
						Nixie(10-i,11);
						Nixie(11-i,2);
						Nixie(12-i,0);
						Nixie(13-i,2);
						Nixie(14-i,3);
						j--;
					}
			}
	}
}
