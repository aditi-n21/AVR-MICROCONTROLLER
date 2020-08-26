#include<reg51.h>
sbit sw = P1^0;
sbit sw1 = P1^1;
sbit sw2 = P1^2;
sbit sw3 = P1^3;
sbit mot1A=P2^0;
sbit mot1B=P2^1;
sbit mot2A=P2^2;
sbit mot2B=P2^3;
void delay(unsigned char);
void main()
{	 sw=sw1=sw2=sw3=1;
     mot1A=mot1B=mot2A=mot2B==0;
	 while(1)
   {
   	 while(sw==0)
	     {
		 mot1A=1;
		 mot1B=0;
		 delay(10);
		 mot2A=1;
		 mot2B=0;
		 delay(10);
		 }
	 while(sw1==0)
	 	{
	     mot1A=1;
		 mot1B=0;
		 delay(10);
		 mot2A=0;
		 mot2B=0;
		 delay(10);
		}
while(sw2==0)
	     {
		 mot1A=0;
		 mot1B=0;
		 delay(10);
		 mot2A=1;
		 mot2B=0;
		 delay(10);
		 }
while(sw3==0)
	     {
		 mot1A=0;
		 mot1B=1;
		 delay(10);
		 mot2A=0;
		 mot2B=1;
		 delay(10);
		 }
   
   
   }
}
void delay(unsigned char msec)   // Function for delay
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<msec;i++)
		for(j=0;j<1275;j++);
} 