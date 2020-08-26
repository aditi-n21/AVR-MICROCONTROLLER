/*
 * eight_ques.c
 *
 * Created: 8/19/2015 11:47:35 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{

	DDRB=0xFF;
	PORTB=0xff;
	DDRD=0xFF;
	unsigned char temp;
    while(1)
    {
	temp=PINB;
	
		_delay_ms(800);
		
        //TODO:: Please write your application code 
    	PORTD=temp;
	}	
}