/*
 * waveform.c
 *
 * Created: 16-08-2012 PM 7:07:25
 *  Author: MANOJ
 */ 

// Program to Generate waveform using AVR Microcontroller (Atmega16) Timers
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void t0_init(void);
 
#define FREQ 12000000	// crsytal freqeuncy
#define PRECSALER 8		
#define F_OUT 5000		// output frequency
#define OCR0_VALUE ((((FREQ/2)/PRECSALER)/F_OUT)-1)	 
int main()
{				
	t0_init();			// timer initialize
	sei();				// enable global interrupts
	while(1);
}
 
void t0_init()
{
	// WGM0[1:0]= 10, for CTC mode
	// COM0[1:0]= 01, to toggle OC0 on compare match
	// CS0[2:0] =010. for prescaler 8
	 		
	TCCR0=(1<<WGM01)|(1<<COM00)|(1<<CS01);
	DDRB|=(1<<PB3);			// select as output pin 
	TIMSK|=(1<<OCIE0);		//enable output compare interrupt			
}
 
ISR(TIMER0_COMP_vect)			// interrupt subroutine
{
	OCR0=(uint8_t)OCR0_VALUE;	//put OCR value
}