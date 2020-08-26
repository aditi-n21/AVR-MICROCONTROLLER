#include<pic.h>
#include<htc.h>
void delay();
#define s1 RD0
#define s2 RD1
#define seg PORTC	//CA as a 7-segment
void main()
{
unsigned char ar[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90,'\0'};
	unsigned char i=0;
	TRISC=0x00;
	seg=ar[i];
	while(1)
	{
		if(s1==0)
		{
		 while(s1==0);
			if(i!=9)
			i++;
			seg=ar[i];
		}
		if(s2==0)
		{
		 while(s2==0);
			if(i!=0)
			i--;
			seg=ar[i];
		}
	}
	
}

void delay()
{
	unsigned int i,j;
	for(i=0;i<2;i++)
	 for(j=0;j<65535;j++);
}