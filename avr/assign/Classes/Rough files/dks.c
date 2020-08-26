#include<reg51.h>
#define led P2
void delay(unsigned char msec);
void main()
{
while(1)
{
led=0xCF;
delay(100);
led=0x3F;
delay(100);
led=0x0C;
delay(100);
led=0x03;
delay(100);
}
}
void delay(unsigned char msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)

for(j=0;j<1275;j++);
}
