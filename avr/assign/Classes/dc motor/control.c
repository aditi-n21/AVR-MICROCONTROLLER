#include<reg51.h>
sbit sw = P1^0;
sbit sw1 = P1^1;
sbit sw2 = P1^2;
sbit sw3 = P1^3;
sbit mot=P2^0;
void delay(unsigned char);
void timer(unsigned char);
void main()
{	 
     TMOD=0x20;
	 TH1=0xd2;
	 mot=0;
	 while(1)
   {
   	 while(sw==0)
	     {
		 mot=1;
		 timer(25);
		 delay(10);
		 mot=0;
		 timer(75);
		 delay(10);
		 }
	 while(sw1==0)
	 	{
	     mot=1;
		 timer(50);
		 delay(10);
		 mot=0;
		 timer(50);
		 delay(10);
		}
while(sw2==0)
	     {
		 mot=1;
		 timer(75);
		 delay(10);
		 mot=0;
		 timer(25);
		 delay(10);
		 }
while(sw3==0)
	     {
		 mot=1;
		 timer(100);
		 delay(10);
		 }
   
   
   }
}
void timer(unsigned char msec)	 // Function for timer
{
	unsigned char i;
	TR1=1;
	for(i=0;i<msec;i++)
	{
		while(TF1==0);
		TF1=0;
	}
	TR1=0;
}
void delay(unsigned char msec)   // Function for delay
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<msec;i++)
		for(j=0;j<1275;j++);
} 