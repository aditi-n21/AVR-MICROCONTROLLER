#include<reg51.h>
void delay(unsigned int);

void main(void)
{
    while(1)
	{
	  P2=0x00;
	  delay(250);
	  P2=0xFF;
	   delay(250);
	}

}
void delay(unsigned int a)
{
  unsigned int i,j;
  for(i=0;i<a;i++)
	  for(j=0;j<1275;j++);

}