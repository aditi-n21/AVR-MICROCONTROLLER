/*
 * twovelve_ques.c
 *
 * Created: 8/21/2015 9:47:14 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRB&=~(1<<PB3);
	PORTB|=(1<<PB3);
	DDRB|=(1<<PB7);
    while(1)
    {
	if(bit_is_clear(PINB,PB3))//	if(PINB&(1<<PB3))
		{
	PORTB|=(1<<PB7);
		}        
	else
	{
		PORTB&=~(1<<PB7);
		}//TOD;O:: Please write your application code 
    }
}