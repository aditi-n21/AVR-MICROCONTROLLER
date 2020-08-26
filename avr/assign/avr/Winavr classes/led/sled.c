#include<avr/io.h>
#include<util/delay.h>
#define led 5
int main(void)
{
    DDRA=0xff;
	while(1)
	{
	PORTA|=(1<<led);
	_delay_ms(2000);
	PORTA&=~(1<<led);
	_delay_ms(2000);
	
	}
}
