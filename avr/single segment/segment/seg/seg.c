

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void int_ports()
{
	DDRA=0xff;
	PORTA=0x55;
}  
void int_interrupt()
{
	cli();
	GICR=(1<<INT0);
	MCUCR=(3<<ISC00);
	sei();
}
ISR(INT0_vect)
{
	PORTA=~PORTA;
	_delay_ms(200);
}
int main(void)
{

	   while(1)
    {
	int_interrupt();
	
	int_ports();
}
}