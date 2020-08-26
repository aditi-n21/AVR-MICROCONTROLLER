/*
 * External.c
 *
 * Created: 3/13/2014 1:24:13 PM
 *  Author: MANOJ
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_interrupts();

ISR(INT1_vect)
{
	PORTC=~PORTC;
	_delay_ms(100);
}
int main(void)
{
	DDRC=DDRA=0xff;
	PORTC=0xff;
	init_interrupts();
    while(1)
	{
		PORTA=0x55;
		_delay_ms(500);
		PORTA=0xAA;
		_delay_ms(500);
	}
      
}

void init_interrupts()
{
	cli();  //clear all interrupts
	GICR=(1<<INT1);  // into enable
	MCUCR=(1<<ISC10);
	sei();  //enable all
}
