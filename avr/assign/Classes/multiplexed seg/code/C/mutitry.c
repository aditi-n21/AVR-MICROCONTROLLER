#include<reg51.h>
#define disp P2
sbit seg1=P1^0;
sbit seg2=P1^1;

void delay(unsigned char msec);
unsigned char num[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};	

void main()
{ unsigned char i,j,k;
 seg1=seg2=0;
  while(1)
  {
  for(j=0;j<10;j++)
	{  
  	for(i=0;i<10;i++)
	{ 
	  	seg2=1;
	  disp=num[i];
	delay(50);
	   seg1=1; 
	      disp=num[j];
delay(5);
	   seg1=0;
	  seg2=0;
	    }
   }
  }
}
void delay(unsigned char msec)
{
unsigned int p,q;
for(p=0;p<msec;p++)
  for(q=0;q<1275;q++);
}
