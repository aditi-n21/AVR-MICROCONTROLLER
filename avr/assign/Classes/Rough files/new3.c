#include<reg51.h>
void delay(void);
void main()
{
	while(1)
{
P2=0x00;
delay();
P2=0xFF;
delay();

}
}
void delay(void)
{
	unsigned int i;
	for(i=0;i<50000;i++);
}
