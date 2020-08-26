#include<reg51.h>
#define seg P1
#define seg1 P3
void delay(unsigned int msec);
void main()
{
int i,j;
unsigned char array[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
while(1)
{
for(i=0;i<10;i++)
{
for(j=0;j<10;j++)
{
seg=array[i];
seg1=array[j];
delay(100);
}
}
}
}
void delay(unsigned int msec)
{
unsigned int j,k;
for(j=0;j<msec;j++)
for(k=0;k<1275;k++);
}