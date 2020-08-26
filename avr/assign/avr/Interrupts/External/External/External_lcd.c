/*
 * External.c
 *
 * Created: 3/13/2014 1:24:13 PM
 *  Author: MANOJ
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_ports()
{
	DDRA=0xff;
	PORTA=0x55;
}
void init_interrupts()
{
	cli();
	GICR=(1<<INT0);
	MCUCR=(3<<ISC00);
	sei();
}
ISR(INT0_vect)
{
	PORTA=~PORTA;
	_delay_ms(100);
}
int main(void)
{
	init_ports();
    while(1)
    {
		init_interrupts();
	}
    
}