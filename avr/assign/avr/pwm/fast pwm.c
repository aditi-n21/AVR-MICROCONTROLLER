/*
 * fast_pwm.c
 *
 * Created: 16-08-2012 PM 6:58:28
 *  Author: MANOJ
 */ 

// Program  to use fast PWM (Pulse Width Modulation) Mode of AVR microcontroller Timer
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
 
#define FREQ 12000000
#define duty_cycle 50		// duty cycle require
#define prescaler 8
 
#define OCR_value ((duty_cycle*256)/100)  //OCR value calculation
 
void t0_pwm_init(void);
void t2_fastpwm_init(void);
 
int main()
{			
	t0_pwm_init();	 
	t2_fastpwm_init();
	sei();
	while(1);
}
 
void t0_pwm_init()		// initialization for Phase Correct PWM signal using timer 0
{
	// WGM0[1:0]= 01, for Phase Correct PWM mode
	// COM0[1:0]= 10, to select non inveting mode
	// CS0[2:0] =010. for prescaler=8
		 
	TCCR0=(1<<WGM00)|(2<<COM00)|(2<<CS00);
	DDRB|=(1<<PB3);		// selcet OC0 as output pin
	TIMSK|=(1<<OCIE0);	//enable Output compare interrupt
}
 
void t2_fastpwm_init()	// initialization for Phase Correct PWM signal using timer 2
{		
	// WGM2[1:0]= 11, for Fast PWM mode
	// COM2[1:0]= 10, to select non inveting mode
	// CS2[2:0] =010. for prescaler=8
 
	TCCR2=(1<<WGM20)|(1<<WGM21)|(2<<COM20)|(2<<CS20);
	DDRD|=(1<<PD7);		// selcet OC2 as output pin
	TIMSK|=(1<<OCIE2);	//enable Output compare interrupt
}
 
ISR(TIMER0_COMP_vect)			// interrupt subroutine
{
	OCR0=OCR_value;			// put OCR value
}
 
ISR(TIMER2_COMP_vect)			// interrupt subroutine
{
	OCR2=OCR_value;			// put OCR value
}
 
