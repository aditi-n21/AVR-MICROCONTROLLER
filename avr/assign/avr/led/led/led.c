/*
 * led.c
 *
 * Created: 30-07-2012 PM 8:56:02
 *  Author: MANOJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#define led 0
int main(void)
{
    DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD=0xff;
	//MCUCSR|=(1<<JTD);
	//MCUCSR|=(1<<JTD);
    while(1)
    {
        PORTA=0X00;   //TODO:: Please write your application code
		PORTB=0X00;   //TODO:: Please write your application code
		PORTC=0X55;   //TODO:: Please write your application code
		PORTD=0X00;   //TODO:: Please write your application code
		_delay_ms(1000); 
		PORTA=0XFF;   //TODO:: Please write your application code
		PORTB=0XFF;   //TODO:: Please write your application code
		PORTC=0XAA;   //TODO:: Please write your application code
		PORTD=0XFF;   //TODO:: Please write your application code
		_delay_ms(1000); 

    }
}