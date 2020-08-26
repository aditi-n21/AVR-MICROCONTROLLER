#include<reg51.h>
sbit seg1=P3^0;
sbit seg2=P3^1;

delay_ms(int time)		// Time delay function
{
	int i,j;
 	for(i=0;i<time;i++)
  	for(j=0;j<1275;j++);
}

void main()
{	unsigned char i,j;
	char num[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};		// Hex values corresponding to digits 0 to 9
	while(1)
		{
		for(i=0;i<10;i++)
		{
		seg1=1;
		seg2=1;
		P1=num[i];
		for(j=0;j<10;j++)
		  {
			P2=num[j];
			delay_ms(50);
		  }
		}
}
}	