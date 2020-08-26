#include<reg51.h>
void delay (unsigned int msec);
void main()
{
unsigned char i,a,b,c;
a=0x01;
c=a;
while(1)
{
for(i=0;i<8;i++)
{
b=~a;
P2=b;
c=c<<1;
a=c;
delay(100);
}
}
}
void delay(unsigned int msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)
for(j=0;j<1275;j++);
}
