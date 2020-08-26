

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRA=0xff;
	DDRD=0xff;
	PORTD=0xaa;
	PORTA=0x55;
	TCNT0=20;
	TCCR0=0x06;
	TIMSK=(1<<TOIE0);
sei();
while(1)
{
	
	PORTD=~PORTD;
	_delay_ms(300);

}
	}
	ISR(TIMER0_OVF_vect)
	{
		TCNT0=20;
	PORTA=~PORTA;
	}