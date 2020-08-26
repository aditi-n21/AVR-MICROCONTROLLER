/*
 * two_qest.c
 *
 * Created: 8/19/2015 9:16:59 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB=0xFF;
    while(1)
    {
       PORTB=0x00;
	   _delay_ms(1000);
	    PORTB=0xFF;
	    _delay_ms(1000);  //TODO:: Please write your application code 
    }
}