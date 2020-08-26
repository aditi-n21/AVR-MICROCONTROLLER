#include<reg51.h>
void delay(void);
void main()
{
	unsigned char arr[]="012345ABCD";
	unsigned char i;
	while(1)
{
for(i=0;i<10;i++)
{
P1=arr[i];
delay();	
}
}
}
void delay(void)
{
	unsigned int i;
	for(i=0;i<50000;i++);
}
