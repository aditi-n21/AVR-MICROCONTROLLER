#include<reg51.h>
#define seg P1
void delay(unsigned int msec);
void main()
{
while(1)
{
seg=0xc0;
delay(100);
seg=0xf9;
delay(100);
seg=0xa4;
delay(100);
seg=0x99; 
delay(100);
seg=0x92;
delay(100);
seg=0x82;
delay(100);
seg=0xf8;
delay(100);
seg=0x80;
delay(100);
seg=0x90;
delay(100);
}
}
void delay(unsigned int msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)
{
for(j=0;j<1275;j++);
}}