/*
 * _50_perc_duty_cycel.c
 *
 * Created: 9/18/2015 1:30:10 PM
 *  Author: vipul
 */ 


#include <avr/io.h>
void delay()
{
	TCNT0=0x00; //no efectebel by if i want tcnt0 value change in normal mode tccr0=0x01;  
	TCCR0=0x01;     // tccr0=0x01; use for normal mode 
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