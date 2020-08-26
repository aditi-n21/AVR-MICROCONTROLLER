/*
 * steppermotor.c
 *
 * Created: 22-01-2014 18:27:52
 *  Author: USER
 */ 

#include <avr/io.h>
#include <util/delay.h>

void stepperf(void);
void stepperb(void);

int main(void)
{
	DDRD = 0x0f;
//PORTD = 0x0f;
    while(1)
	{
		stepperf();
		_delay_ms(50);
		stepperb();
		_delay_ms(50);
	}
}
void stepperf(void)
	   {
		unsigned char i;
		for(i=0;i<20;i++)
		{ 
		PORTD |= (1<<PD0);
        PORTD &= ~(1<<PD1);
		PORTD &= ~(1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(10);
		
        PORTD &= ~(1<<PD0);
		PORTD |= (1<<PD1);
		PORTD &= ~(1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(20);
		PORTD &= ~(1<<PD0);
        PORTD &= ~(1<<PD1);
		PORTD |= (1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(20);
		 PORTD &= ~(1<<PD0);
		PORTD &= ~(1<<PD1);
		PORTD &= ~(1<<PD2);
       PORTD |= (1<<PD3);
		_delay_ms(20);
	}
}
void stepperb(void)
	   {
		unsigned char i;
		for(i=0;i<20;i++)
		{ 
		PORTD &= ~(1<<PD0);	
		PORTD &= ~(1<<PD1);
		PORTD &= ~(1<<PD2);
		PORTD |= (1<<PD3);
		_delay_ms(20);
		
        PORTD &= ~(1<<PD0);
		PORTD &= ~(1<<PD1);
		PORTD |= (1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(20);
		PORTD &= ~(1<<PD0);
		PORTD |= (1<<PD1);
        PORTD &= ~(1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(20);
		PORTD |= (1<<PD0);
        PORTD &= ~(1<<PD1);
		PORTD &= ~(1<<PD2);
        PORTD &= ~(1<<PD3);
		_delay_ms(20);
	}
}