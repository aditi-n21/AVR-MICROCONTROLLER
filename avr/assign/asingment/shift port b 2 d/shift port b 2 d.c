/*
 * shift_port_b_2_d.c
 *
 * Created: 8/19/2015 12:13:59 PM
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
	   _delay_ms(500);
	   PORTB=0x00;
	   _delay_ms(50);
	   PORTD=0xFF;
	   _delay_ms(500);
	   PORTD=0x00;
	   _delay_ms(50);
	   
    }
}