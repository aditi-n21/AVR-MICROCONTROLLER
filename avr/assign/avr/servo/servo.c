/*
 * servo.c
 *
 * Created: 16-08-2012 PM 7:12:53
 *  Author: MANOJ
 */ 

// Program to rotate servo at the step of 20 degree.
#include<avr/io.h>
#include<util/delay.h>
 
#define motor PORTD
#define servo PD6
 
void degree(unsigned int );
 
int main(void)
{
	unsigned int degree_value,time;
	DDRD=0b01000000;
	for(degree_value=0;degree_value<180;degree_value +=20)
	for(time=0;time<50;time++)
	{
		degree(degree_value);
	}
	return 0;
}
 
void degree(unsigned int k)
{
	k=50+(k*10);
	motor= (1<< servo);
	_delay_us(k);
	motor = (0<<servo);
	_delay_ms(18);
}
 