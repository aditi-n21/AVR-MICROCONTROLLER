/*
 * _1khz_frequency_genrate.c
 *
 * Created: 9/25/2015 1:19:35 PM
 *  Author: vipul
 */ 


#include <avr/io.h>
void delay()
{
	TCNT0=0x88; // tcnt value 256-63=193 aproxi=0xc1; 
	TCCR0=0x0a; // for cs0=011; valuse for prescaler 64mhz;
	while((TIFR&(1<<TOV0))==0);
	TIFR|=(1<<TOV0);
	TCCR0=0X00;
}
int main(void)
{
	DDRB|=(1<<PB5);
	while(1)
	{
		PORTB|=(1<<PB5);
		delay();
		PORTB&=~(1<<PB5);
		delay();
	}
}