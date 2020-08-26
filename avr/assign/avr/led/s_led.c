/*
 * led.c
 *
 * Created: 30-07-2012 PM 8:56:02
 *  Author: MANOJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define led PC0
int main(void)
{
    DDRC=0x01;
	//MCUCSR|=(1<<JTD);
	//MCUCSR|=(1<<JTD);
    while(1)
    {
        PORTC|=(1<<led);
		_delay_ms(1000); 
		PORTC&=(0<<led);
		_delay_ms(1000); 

    }
}