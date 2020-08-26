#include<reg51.h>
#define led P2
void delay(unsigned char);
void main()
{
		while(1)
		{
			led=0x00;
			delay(100);
			led=0xff;
			delay(100);
}


}
void delay(unsigned char msec)
{
  unsigned char i;
	unsigned int j;
	for(i=0;i<msec;i++)
	for(j=0;j<1275;j++);
}