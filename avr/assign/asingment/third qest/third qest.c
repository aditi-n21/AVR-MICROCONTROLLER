/*
 * third_qest.c
 *
 * Created: 8/19/2015 11:15:53 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	unsigned int i;
	DDRB=0xFF;
    for(i=0;i<200;i++)
    {
		PORTB=0x00;
		_delay_ms(500);
		PORTB=0xFF;
		_delay_ms(500);
        //TODO:: Please write your application code 
    }
}