#include <reg51.h>
sbit led2=P3^7;
sbit  led1=P1^2;

void main()
{	
int i=0;
while(1)
{
led1=1;
led2=1;
for(i=0; i<30000; i++);
led1=0;
led2=0;
for(i=0; i<30000; i++);

}

}