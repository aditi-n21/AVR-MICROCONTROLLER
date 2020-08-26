/*
 * quest_eleveen.c
 *
 * Created: 8/21/2015 8:46:26 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRB|=(1<<PB4);
    while(1)
    {
		PORTB|=(1<<PB4); 
		_delay_ms(200);       //TODO:: Please write your application code 
    PORTB&=~(1<<PB4);
    _delay_ms(200);
	}
}