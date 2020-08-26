/*
 * seveenteen_ques.c
 *
 * Created: 8/22/2015 1:19:52 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRD|=(1<<PD3)|(1<<PD6);
    while(1)
    {
       PORTD|=(1<<PD3);
	   _delay_ms(500);
	   PORTD&=~(1<<PD3);
	   _delay_ms(500);
	   PORTD|=(1<<PD6);
	   _delay_ms(500);
	   PORTD&=~(1<<PD6);
	   _delay_ms(500);
    }
}