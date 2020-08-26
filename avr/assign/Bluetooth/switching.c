#include<reg51.h>

#define dtmf P0
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;


void main()
{
   P2=0x00;
  dtmf=0x0f;
  while(1)
  {
  	 if(dtmf==0x08)
	     {
		  led1=1;led2=0;led3=0;led4=0;
		 }
  	else if(dtmf==0x04)
	     {
		  led1=0;led2=1;led3=0;led4=0;
		 }
	else if(dtmf==0x0c)
	     {
		  led1=0;led2=0;led3=1;led4=0;
		 }
	else if(dtmf==0x02)
	     {
		  led1=0;led2=0;led3=0;led4=1;
		 }
	else if(dtmf==0x0a)
	     {
		  led1=1;led2=1;led3=1;led4=1;
		 }
   	else
	     {
		  led1=0;led2=0;led3=0;led4=0;
		 }
  }
}