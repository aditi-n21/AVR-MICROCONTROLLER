#include<reg51.h>

void delay_ms(int time)		// Time delay function
{
	int i,j;
 	for(i=0;i<time;i++)
  	for(j=0;j<1275;j++);
}

void main()
{
//	char num[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};		//(cathode) Hex values corresponding to digits 0 to 9
	char num[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};		//(anode)
	int c;
	while(1)
	{
		for(c=0;c<10;c++)
		{
	//	P2=num[c]; // cathode
		P1=num[c]; // anode
		delay_ms(200);
		}
	}
}