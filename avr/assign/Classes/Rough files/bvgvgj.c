#include<reg51.h>
void delay(void);
void main()
{
	unsigned char i;
	while(1)
	{
		for(i=0;i<255;i++)
		{
			P1=i;
			delay();
		}
	}
}
void delay(void)
{
	unsigned int j;
			for(j=0;j<50000;j++);


}