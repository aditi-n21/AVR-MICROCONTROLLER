/*
 * seveen_ques.c
 *
 * Created: 8/19/2015 11:39:18 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRB=0xFF;
	DDRD=0xFF;
    while(1)
    {
		PORTB=0xFF;
		_delay_ms(250);
		PORTB=0x00;
		_delay_ms(250);
		PORTD=0xFF;
		_delay_ms(250);
		PORTD=0x00;
		_delay_ms(250);
        //TODO:: Please write your application code 
    }
}